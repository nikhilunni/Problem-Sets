.text 

## const char *
## find_longest_string(const string_node_t *node) {
##   if (node == NULL) {
##     return NULL;
##   }
##   const char *str = find_longest_string(node->next);
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
	sub	$sp,	$sp,	20
	sw	$ra,	0($sp)
	sw	$a0,	4($sp)
	sw	$s0,	8($sp)					#s0 = str
	sw	$s1,	12($sp)					#s1 = i
	sw	$s2,	16($sp)					#s2 = length
	beq	$a0,	$0,	longest_string_return1
	lw	$t5,	0($a0)
	lb	$t5,	0($t5)	#node[0].charAt(0)
	lw	$a0,	12($a0)					#a0 = node->next
	jal	find_longest_string
	move	$s0,	$v0					# str = find_longest_string(node->next)
	bne	$s0,	$0,	find_longest_string_set_length	# if str != NULL
	move	$s2,	$0
find_longest_string2:
	move	$s1,	$0	# i = 0
	j	longest_string_loop

find_longest_string_set_length:
	move	$a0,	$s0
	jal	my_strlen
	move	$s2,	$v0
	j	find_longest_string2
longest_string_loop:
	bge	$s1,	2,	longest_string_return2
	lw	$a0,	4($sp)					#restore node
	sll	$t7,	$s1,	2
	add	$a0,	$a0,	$t7				#a0 = &node->strings[i]
	lw	$a0,	0($a0)
	jal	my_strlen
	move	$t0,	$v0					#t0 = temp_length
	bge	$t0,	$s2,	longest_string_loop2
	add	$s1,	$s1,	1
	j	longest_string_loop

longest_string_loop2:
	move	$s2,	$t0					#length = temp_length
	lw	$a0,	4($sp)					#restore node
	sll	$t7,	$s1,	2
	add	$a0,	$a0,	$t7
	lw	$a0,	0($a0)
	move	$s0,	$a0
	add	$s1,	$s1,	1
	j	longest_string_loop

longest_string_return1:
	move	$v0,	$0
	j	longest_string_end

longest_string_return2:
	move	$v0,	$s0
	j	longest_string_end

longest_string_end:
	lw	$ra,	0($sp)
	lw	$a0,	4($sp)
	lw	$s0,	8($sp)					#s0 = str
	lw	$s1,	12($sp)					#s1 = i
	lw	$s2,	16($sp)					#s2 = length
	add	$sp,	$sp,	20
	jr	$ra


