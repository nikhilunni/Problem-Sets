.text 

## char *
## find_longest_string(string_node_t *node) {
##   if (node == NULL) {
##     return NULL;
##   }
##   char *str = find_longest_string(node->next);
##   int length = (str == NULL) ? 0 : my_strlen(str);
##   for (int i = 0 ; i < 2 ; i ++) {
##     int temp_length = my_strlen(node->strings[i]);
##     if (temp_length > length) {
##       length = temp_length;
##       str = node->strings[i];
##     }
##   }
##   return str;
## }

.globl find_longest_string
find_longest_string:
	bne	$a0, $0, fls_recurse
	li	$v0, 0
	jr	$ra

fls_recurse:
	sub	$sp, $sp, 20		
	sw	$ra, 0($sp)		# save $ra and free up 4 $s registers for
	sw	$s0, 4($sp)		# node
	sw	$s1, 8($sp)		# str
	sw	$s2, 12($sp)		# length
	sw	$s3, 16($sp)		# i
	move	$s0, $a0		# save 'node'

	lw	$a0, 12($a0)		# node->next
	jal	find_longest_string
	move	$s1, $v0		# str
	bne	$v0, $0, fls_else
	li	$s2, 0			# length = 0
	j	fls_loop_prologue
fls_else:	
	move	$a0, $v0		
	jal	my_strlen
	move 	$s2, $v0		# length

fls_loop_prologue:
	li	$s3, 0			# i
fls_loop:
	bge	$s3, 8, fls_done	
	add	$a0, $s0, $s3		# &node->string[i]
	lw	$a0, 0($a0)		# node->string[i]
	jal	my_strlen 		
	ble	$v0, $s2, fls_loop_increment		# if (temp_length > length)
	move	$s2, $v0
	add	$s1, $s0, $s3		# &node->string[i]
	lw	$s1, 0($s1)		# str = node->string[i]
fls_loop_increment:
	add	$s3, $s3, 4		# i += 4
	j	fls_loop	

fls_done:	
	move	$v0, $s1		# return value = str
	lw	$ra, 0($sp)		# restore registers and return
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	lw	$s2, 12($sp)
	lw	$s3, 16($sp)
	add	$sp, $sp, 20
	jr	$ra


