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

cs_persons_loop:
	lw	$t1, 0($t0)			# *person
	beq	$t1, 0, cs_done			# !(*person != NULL)
	add	$s2, $s2, 1			# ++population

	lw	$t2, total_salary($s1)		# stats->total_salary
	lw	$t3, salary($t1)		# (*person)->salary
	add	$t2, $t2, $t3			# stats->total_salary + (*person)->salary
	sw	$t2, total_salary($s1)		# stats->total_salary += (*person)->salary

	lbu	$t2, age($t1)			# person_age = (*person)->age
	lbu	$t3, oldest($s1)		# stats->oldest
	ble	$t2, $t3, cs_youngest		# !(person_age > stats->oldest)
	sb	$t2, oldest($s1)		# stats->oldest = person_age

cs_youngest:
	lbu	$t3, youngest($s1)		# stats->youngest
	bge	$t2, $t3, cs_persons_next	# !(person_age < stats->youngest)
	sb	$t2, youngest($s1)		# stats->youngest = person_age

cs_persons_next:
	add	$t0, $t0, 4			# ++persons
	j	cs_persons_loop

cs_done:
	move	$v0, $s2			# return population
	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	lw	$s2, 12($sp)
	lw	$s3, 16($sp)
	add	$sp, $sp, 20
	jr	$ra
