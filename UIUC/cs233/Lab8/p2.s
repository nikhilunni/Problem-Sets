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

## int compute_stats(const quinary_tree_t * root, stats_t * stats) {
##     if (root == NULL) {
##         return 0;
##     }
## 
##     int population = 0;
##     for (int i = 0; i < 5; ++i) {
##         population += compute_stats(root->children[i], stats);
##     }
## 
##     if (root->persons != NULL) {
##         for (person_t ** person = root->persons; *person != NULL; ++person) {
##             ++population;
##             stats->total_salary += (*person)->salary;
##             uint8_t person_age = (*person)->age;
##             if (person_age > stats->oldest) {
##                 stats->oldest = person_age;
##             }
##             if (person_age < stats->youngest) {
##                 stats->youngest = person_age;
##             }
##         }
##     }
## 
##     return population;
## }

.globl compute_stats
compute_stats:
	sub	$sp,	$sp,	20
	sw	$ra,	0($sp)
	sw	$a0,	4($sp)
	sw	$a1,	8($sp)
	sw	$s0,	12($sp) 			#s0 = population
	sw	$s1,	16($sp)				#s1 = i
	beq	$a0,	$0,	compute_stats_return1
	move	$s0,	$0
	move	$s1,	$0
compute_stats_loop1:
	bge	$s1,	5,	compute_stats_tag
	lw	$a0,	4($sp)				#restore a0
	sll	$t0,	$s1,	2			#t0 = 4i
	add	$a0,	$a0,	4
	add	$a0,	$a0,	$t0			#a0 = a0+4+4i
	lw	$a0,	0($a0)
	jal	compute_stats
	add	$s0,	$s0,	$v0			#population += compute_stats(root->children[i],...)
	add	$s1,	$s1,	1			#i++
	j	compute_stats_loop1
compute_stats_tag:
	lw	$a0,	4($sp)				#Restore a0
	lw	$a1,	8($sp)				#Restore a1
	lw	$t0,	persons($a0)			#t0 = root->persons/person
	beq	$t0,	$0,	compute_stats_return2
compute_stats_loop2:
	lw	$t1,	0($t0)				#t1 = *person
	beq	$t1,	$0,	compute_stats_return2
	add	$s0,	$s0,	1			# ++population
	lw	$t2,	salary($t1)			#t2 = (*person)->salary
	lw	$t3,	total_salary($a1)		#t3 = stats->total_salary
	add	$t3,	$t2,	$t3
	sw	$t3,	total_salary($a1)
	lbu	$t4,	age($t1)			#t4 = person_age
	lbu	$t5,	oldest($a1)			#t5 = stats->oldest
	lbu	$t6,	youngest($a1)			#t6 = stats->youngest
	bgt	$t4,	$t5,	compute_stats_set_oldest
compute_stats_loop_tag1:
	blt	$t4,	$t6,	compute_stats_set_youngest
compute_stats_loop_tag2:
	add	$t0,	$t0,	4
	j	compute_stats_loop2

compute_stats_set_oldest:
	sb	$t4,	oldest($a1)
	j	compute_stats_loop_tag1
compute_stats_set_youngest:
	sb	$t4,	youngest($a1)
	j	compute_stats_loop_tag2



compute_stats_return1:
	move	$v0,	$0
	j	compute_stats_end
	
compute_stats_return2:
	move	$v0,	$s0
	j	compute_stats_end

compute_stats_end:
	lw	$ra,	0($sp)				#restore $ra
	lw	$s0,	12($sp)
	lw	$s1,	16($sp)
	add	$sp,	$sp,	20
	jr	$ra
	