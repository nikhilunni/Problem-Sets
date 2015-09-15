# syscall constants
PRINT_INT = 1
PRINT_CHAR = 11
PRINT_STRING = 4

.data
.globl newline
newline:    .asciiz "\n"		# useful for printing commands

.align 2
a_string: .asciiz "this is my favorite string"
.align 2
rotated_string: .asciiz "orite stringthis is my fav"
.align 2
not_rotated_string: .asciiz "y favorite strjngthis is m"

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
	la	$a0, newline		# print a newline char.
	li	$v0, PRINT_STRING	
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
#  this will test 'my_strcmp' and 'rotate_string_in_place'
#
#########################################################################


.globl main
main:
	sub	$sp, $sp, 4
	sw	$ra, 0($sp)		# save $ra on stack

	la	$a0, a_string		
	la	$a1, rotated_string		
	jal	puzzle_solve
	move	$a0, $v0
	jal	print_int_and_space	# this should print 12
	
	la	$a0, a_string		
	la	$a1, not_rotated_string		
	jal	puzzle_solve
	move	$a0, $v0
	jal	print_int_and_space	# this should print -1
	jal	print_newline	

	la	$a0, a_string
	jal	rotate_string_in_place_fast
	la	$a0, a_string
	# this should print "his is my favorite stringt"
	jal	print_string		
	jal	print_newline

	lw	$ra, 0($sp)
	add	$sp, $sp, 4
	jr	$ra



