# syscall constants
PRINT_INT = 1
PRINT_CHAR = 11
PRINT_STRING = 4

.data
blah_string: .asciiz "blah"
foo_string: .asciiz "foo"
hoopy_string: .asciiz "hoopy"
frood_string: .asciiz "frood"
oxy_string: .asciiz "oxy"
moron_string: .asciiz "moron"
super_string: .asciiz "super"
calafragilistic_string: .asciiz "calafragilistic"
latency_string: .asciiz "latency"
bandwidth_string: .asciiz "bandwidth"

.align 2
node5: .word blah_string foo_string 0 0
node4: .word hoopy_string frood_string 0 node5
node3: .word oxy_string moron_string 0 node4
node2: .word super_string calafragilistic_string 0 node3
node1: .word latency_string bandwidth_string 0 node2

.text
# print int and space ##################################################
#
# argument $a0: number to print
# returns       nothing

print_int_and_space:
	li	$v0, PRINT_INT	# load the syscall option for printing ints
	syscall			# print the number

	li   	$a0, ' '       	# print a black space
	li	$v0, PRINT_CHAR	# load the syscall option for printing chars
	syscall			# print the char
	
	jr	$ra		# return to the calling procedure

# print string ########################################################
#
# argument $a0: string to print
# returns       nothing

print_string:
	li	$v0, PRINT_STRING	# print string command
	syscall	     			# string is in $a0
	jr	$ra

# print newline ########################################################
#
# no arguments
# returns       nothing

print_newline:
	li	$a0, '\n'		# print a newline char.
	li	$v0, PRINT_CHAR
	syscall	
	jr	$ra

# my strlen  ##################################################
#
# argument $a0: string whose length we want to know
# returns       length of string
#
# int 
# my_strlen(const char *str) {
#   int length = 0;
#   while (str[length] != '\0') {
# 	 length ++;
#   }
#   return length;
# }

.globl my_strlen
my_strlen:
	li	$v0, 0			# length = 0  (in $v0 'cause return val)
my_strlen_loop:
	add	$t1, $a0, $v0		# &str[length]
	lb	$t2, 0($t1)		# str[length]
	beq	$t2, $0, my_strlen_done
	
	add	$v0, $v0, 1		# length ++
	j 	my_strlen_loop

my_strlen_done:
	jr	$ra

# main function ########################################################
#
#  this will test '' and 'rotate_string_in_place'
#
#########################################################################

.globl main
main:
	sub	$sp, $sp, 4
	sw	$ra, 0($sp)		# save $ra on stack

	la	$a0, 0			
	jal	find_longest_string	# find_longest_string(NULL)
	move	$a0, $v0
	jal	print_int_and_space	# prints 0
	jal	print_newline
	
	la	$a0, node5
	jal	find_longest_string	# find_longest_string(node5)
	move	$a0, $v0
	jal	print_string		# prints "blah"
	jal	print_newline
	
	la	$a0, node1		
	jal	find_longest_string	# find_longest_string(node1)
	move	$a0, $v0
	jal	print_string		# prints "calafragilistic"
	jal	print_newline

	lw	$ra, 0($sp)
	add	$sp, $sp, 4
	jr	$ra

