.text

## int 
## my_strcmp(const char *str1, const char *str2) {
##   int i = 0;
## 
##   while (1) {
##     char c1 = str1[i];
##     char c2 = str2[i];
##     
##     if (c1 != c2) {  
##        // if the characters are not equal, return the difference
##        return c1 - c2; 
##     }
##     if (c1 == '\0') { 
##        // if we the end of a string, then we hit the end of both
##        // return 0 to indicate that the strings match
##        return 0;       
##     }
##     // go on to the next character
##     i ++;             
##   }
## }

.globl my_strcmp
my_strcmp:
	add	$t1,	$0	$0 ##1 is i
	move	$t5,	$a0	##t5 is my new a0
	move	$t6,	$a1	##t6 is my new a1
strcmp_loop:
	## $a0 = str1, $a1 = str2
	lb	$t2,	0($t5)	##t2 = str1[i]
	lb	$t3,	0($t6)	##t3 = str2[i]
	bne	$t2,	$t3,	strcmp_return0
	beq	$t2,	$0,	strcmp_return1
	add	$t1,	$t1,	1 ## i++
	add	$t5,	$t5,	1 ##
	add	$t6,	$t6,	1
	j	strcmp_loop
	
strcmp_return0:
	sub	$v0	$t2	$t3
	j	strcmp_end

strcmp_return1:
	move	$v0	$0
	j	strcmp_end


strcmp_end:
	jr	$ra


## void
## rotate_string_in_place(char *str) {
##   int length = my_strlen(str);
##   char was_first = str[0];
##   
##   for (int i = 1 ; i < length ; i ++) {
##     char c = str[i];
##     str[i-1] = c;
##   }
## 
##   str[length - 1] = was_first;
## }

.globl rotate_string_in_place
rotate_string_in_place:
	sub	$sp,	$sp,	8
	sw	$ra,	0($sp)
	sw	$a0,	4($sp)
	jal	my_strlen
	lw	$a0,	4($sp)
	lw	$ra,	0($sp)
	add	$t0,	$v0,	$0	##t0 : length
	lb	$t1,	0($a0)		##t1 : was_first
	add	$t2,	$0,	1	##t2 : i = 1
rotate_loop:
	bge	$t2,	$t0,	rotate_end
	add	$t4,	$a0,	$t2	##t4 : (str+i)
	sub	$t5,	$t4,	1	##t5 : (str+i-1)
	lb	$t6,	0($t4)		##t6 : c
	sb	$t6,	0($t5)
	addi	$t2,	$t2,	1
	j	rotate_loop

rotate_end:
	sub	$t7,	$t0,	1	##t7 : length-1
	add	$t7,	$t7,	$a0	##t7 : str+length-1
	sb	$t1,	0($t7)
	add	$sp,	$sp,	8
	jr	$ra
