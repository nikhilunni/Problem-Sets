# run with QtSpim -file main.s question_4.s

# void increment_vals(int **A, int *vals, int length) {
#     for (int i = 0; i < length; i += 2) {
#         vals[i] = *A[i] + 17;
#     }
# }
.globl increment_vals
increment_vals:
	li	$t0,	0			#t0 : i
increment_vals_loop:
	bge	$t0,	$a2,	increment_vals_end
	sll	$t3,	$t0,	2		#t3 : 4i
	add	$t1,	$a0,	$t3
	lw	$t1,	0($t1)
	lw	$t1,	0($t1)
	add	$t1,	$t1,	17
	add	$t2,	$a1,	$t3
	sw	$t1,	0($t2)
	add	$t0,	$t0,	2
	j	increment_vals_loop
increment_vals_end:
	jr	$ra
