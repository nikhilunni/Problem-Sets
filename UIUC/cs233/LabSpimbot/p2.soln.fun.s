.data

# person_t offsets
age = 0
salary = 4

# quinary_tree_t offsets
persons = 0
children = 4

# stats_t offsets
oldest = 0
youngest = 1
total_salary = 4
average_salary = 8

.text

compute_stats:
	bne	$a0, 0, cs_main		# !(root == NULL)
	li	$v0, 0
	jr	$ra

cs_main:
	sub	$sp, $sp, 20
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)
	sw	$s3, 16($sp)
	move	$s0, $a0			# root
	move	$s1, $a1			# stats

	li	$s2, 0				# population = 0
	li	$s3, 0				# i = 0

cs_children_loop:
	mul	$t0, $s3, 4			# i * 4
	add	$t0, $s0, $t0			# root + i * 4
	lw	$a0, children($t0)		# root->children[i]
	move	$a1, $s1			# stats
	jal	compute_stats
	add	$s2, $s2, $v0			# population += ...
	add	$s3, $s3, 1			# ++i
	blt	$s3, 5, cs_children_loop	# loop while i < 5

	lw	$t0, persons($s0)		# root->persons (person)
	beq	$t0, 0, cs_done			# !(root->persons != NULL)

	# load into registers for easier computation
	lw	$t1, total_salary($s1)
	lbu	$t2, oldest($s1)      
	lbu	$t3, youngest($s1)    

cs_persons_loop:
	lw	$t4, 0($t0)			# *person
	beq	$t4, 0, cs_persons_done		# !(*person != NULL)
	add	$s2, $s2, 1			# ++population

	lw	$t5, salary($t4)		# (*person)->salary
	add	$t1, $t1, $t5			# total_salary += (*person)->salary

	lbu	$t5, age($t4)			# person_age = (*person)->age
	sgt	$t6, $t5, $t2			# person_age > oldest?
	movn	$t2, $t5, $t6			# if so, oldest = person_age
	slt	$t6, $t5, $t3			# person_age < youngest?
	movn	$t3, $t5, $t6			# if so, youngest = person_age

cs_persons_next:
	add	$t0, $t0, 4			# ++persons
	j	cs_persons_loop

cs_persons_done:
	# store back into stats
	sw	$t1, total_salary($s1)
	sb	$t2, oldest($s1)
	sb	$t3, youngest($s1)

cs_done:
	move	$v0, $s2			# return population
	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	lw	$s2, 12($sp)
	lw	$s3, 16($sp)
	add	$sp, $sp, 20
	jr	$ra
