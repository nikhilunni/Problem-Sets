.text 

## int
## puzzle_solve(const char *str1, char *str2) {
##   int length = my_strlen(str1);
##   
##   for (int i = 0 ; i < length ; i ++) {
##     if (my_strcmp(str1, str2) == 0) {
##       return i;
##     }
##    
##     rotate_string_in_place(str2);
##   }
##   return -1;
## }

.globl puzzle_solve
puzzle_solve:
	sub	$sp,	$sp,	20
	sw	$ra,	0($sp)
	sw	$s0,	4($sp)	#str1
	sw	$s1,	8($sp)	#str2
	sw	$s2,	12($sp)	#length
	sw	$s3,	16($sp)	#i
	move	$s0,	$a0
	move	$s1,	$a1
	jal	my_strlen
	move	$s2,	$v0
	move	$s3,	$0
puzzle_loop:
	bge	$s3,	$s2,	puzzle_return1
	move	$a0,	$s0
	move	$a1,	$s1
	jal	my_strcmp
	beq	$v0,	$0,	puzzle_return2
	move	$a0,	$s1
	jal rotate_string_in_place
	add	$s3,	$s3,	1
	j	puzzle_loop

puzzle_return1:
	sub	$v0,	$0,	1
	j	puzzle_end
puzzle_return2:
	move	$v0,	$s3
	j	puzzle_end
puzzle_end:
	lw	$ra,	0($sp)
	lw	$s0,	4($sp)
	lw	$s1,	8($sp)
	lw	$s2,	12($sp)
	lw	$s3,	16($sp)
	add	$sp,	$sp,	20
	jr	$ra

   
## void
## rotate_string_in_place_fast(char *str) {
##   int length = my_strlen(str);
## 
##   // remember the very first character
##   char was_first = str[0];
## 
##   // we're going to tell C that we want to operate on
##   // our array of characters _as if_ it was an array of ints
##   int *str_as_array_of_ints = (int *)str;
##   int length_in_ints = length / 4; // this rounds down
## 
##   for (int i = 0 ; i < length_in_ints ; i ++) {
##     // using unsigneds so I get the correct kind of right shift
##     unsigned first_word = str_as_array_of_ints[i];
##     unsigned second_word = str_as_array_of_ints[i+1];
##     unsigned combined_word = (first_word >> 8) | (second_word << 24);
##     str_as_array_of_ints[i] = combined_word;
##   }
## 
##   for (int i = length_in_ints*4 + 1 ; i < length ; i ++) {
##     char c = str[i];
##     str[i-1] = c;
##   }
## 
##   str[length - 1] = was_first;
## }

.globl rotate_string_in_place_fast
rotate_string_in_place_fast:
	sub	$sp,	$sp,	8
	sw	$ra,	0($sp)
	sw	$a0,	4($sp)
	jal	my_strlen
	lw	$a0,	4($sp)
	lw	$ra,	0($sp)
	add	$t0,	$v0,	$0	#t0 : length
	lb	$t1,	0($a0)		#t1 : was_first
	srl	$t2,	$t0,	2	#t2 : length_in_ints
	move	$t3,	$0		#t3 : i=0
	move	$t4,	$a0		#t4 : pointer to str
rotate_fast_loop:
	bge	$t3,	$t2,	rotate_fast_2
	lw	$t5,	0($t4)		#t5 : first_word
	lw	$t6,	4($t4)		#t6 : second_word 
	srl	$t7,	$t5,	8	#t7 : first_word >> 8
	sll	$t8,	$t6,	24	#t8 : second_word << 24
	or	$t7,	$t7,	$t8	#t7 : (first_word >> 8) | (second_word << 24), t7 : combined word
	sw	$t7,	0($t4)		#str_as_array_of_ints[i] = combined_word
	add	$t4,	$t4,	4	#pointer to str = pointer to str + 1
	add	$t3,	$t3,	1	#i++
	j	rotate_fast_loop

rotate_fast_2:
	sll	$t3,	$t2,	2 	#i = length_in_ints*4
	add	$t3,	$t3,	1	#i = i + 1
	move	$t4,	$a0		#t4 : pointer to str
	add	$t4,	$t4,	$t3	#t4 : pointer = (str+i)
rotate_fast_loop2:
	bge	$t3,	$t0,	rotate_fast_end
	lb	$t5,	0($t4)		#t5 : str[i]
	sb	$t5,	-1($t4)
	add	$t4,	$t4,	1	#pointer to str = pointer to str + 1
	add	$t3,	$t3,	1 	#i++
	j	rotate_fast_loop2
rotate_fast_end:
	sub	$t4,	$t0,	1	#t4 : length-1
	add	$t4,	$t4,	$a0	#t4 : str[length-1]
	sb	$t1,	0($t4)
	add	$sp	$sp,	8
	jr	$ra
