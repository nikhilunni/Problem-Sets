.data
.align 2
puzzle_container: .space 8192
pointer:	.space 4
signal:	 .space 4
	
# movement memory-mapped I/O
VELOCITY             = 0xffff0010
ANGLE                = 0xffff0014
ANGLE_CONTROL        = 0xffff0018

# coordinates memory-mapped I/O
BOT_X                = 0xffff0020
BOT_Y                = 0xffff0024

# planet memory-mapped I/O
LANDING_REQUEST      = 0xffff0050
TAKEOFF_REQUEST      = 0xffff0054
PLANETS_REQUEST      = 0xffff0058

# puzzle memory-mapped I/O
PUZZLE_REQUEST       = 0xffff005c
SOLVE_REQUEST        = 0xffff0064

# debugging memory-mapped I/O
PRINT_INT            = 0xffff0080

# interrupt constants
DELIVERY_MASK        = 0x800
DELIVERY_ACKNOWLEDGE = 0xffff0068

# Zuniverse constants
NUM_PLANETS = 5

# planet_info struct offsets
orbital_radius = 0
planet_radius = 4
planet_x = 8
planet_y = 12
favor = 16
enemy_favor = 20
planet_info_size = 24

# puzzle node struct offsets
str = 0
solution = 8
next = 12

#Puzzle container



	
.text

main:
	# your code goes here
	# you'll need to copy-paste the puzzle solving functions from Lab 7
	# for the interrupt-related portions, you'll want to
	# refer closely to example.s - it's probably easiest
	# to copy-paste the relevant portions and then modify them
	# keep in mind that example.s has bugs, as discussed in section
	sub	$sp,	$sp,	16
	sw	$ra,	0($sp)
	sw	$a0,	4($sp)
	sw	$a1,	8($sp)
	sw	$s2,	12($sp)
	li	$t4,	DELIVERY_MASK
	or	$t4,	$t4,	1
	mtc0	$t4,	$12
request:
	la	$t1,	signal
#	sw	$0,	0($t1)
	la	$t0,	puzzle_container
	sw	$t0,	PUZZLE_REQUEST
wait:
	la 	$t1, 	signal
	lw 	$t1, 	0($t1)
	beq	$t1,	1,	solve_puzzle_init
	j	wait
solve_puzzle_init:
	la	$s2,	puzzle_container
solve_puzzle:
	beq	$s2	$0	send
	lw	$a0,	0($s2)
	lw	$a1,	4($s2)
	sw	$s2,	pointer
	jal	puzzle_solve
	lw	$s2,	pointer
	sw	$v0,	solution($s2)
	lw	$s2,	next($s2)
	j	solve_puzzle
send:
	la	$s2,	puzzle_container
	sw	$s2,	SOLVE_REQUEST
#	jr	$ra
	li	$t8,	0
	sw	$t8,	signal
	j	request


print_words:
	li	$v0,	4
	syscall
	la	$a0,	newline
	syscall
	move	$a0,	$a1
	syscall
	la	$a0,	newline
	syscall
	j	$ra





#From the Lab7 solution

###############################	
######Util methods#############
##############################
puzzle_solve:
	sub	$sp, $sp, 20
	sw	$ra, 0($sp)		# save $ra and free up 4 $s registers for
	sw	$s0, 4($sp)		# str1
	sw	$s1, 8($sp)		# str2
	sw	$s2, 12($sp)		# length
	sw	$s3, 16($sp)		# i

	move	$s0, $a0		# str1
	move	$s1, $a1		# str2

	jal	my_strlen

	move 	$s2, $v0		# length
	li	$s3, 0			# i = 0
ps_loop:
	bgt	$s3, $s2, ps_return_minus_1
	move	$a0, $s0		# str1
	move	$a1, $s1		# str2
	jal	my_strcmp
	beq	$v0, $0, ps_return_i
	
	move	$a0, $s1		# str2
	jal	rotate_string_in_place_fast
	add	$s3, $s3, 1		# i ++
	j	ps_loop

ps_return_minus_1:
	li	$v0, -1
	j	ps_done

ps_return_i:
	move	$v0, $s3

ps_done:	
	lw	$ra, 0($sp)		# restore registers and return
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	lw	$s2, 12($sp)
	lw	$s3, 16($sp)
	add	$sp, $sp, 20
	jr	$ra



	

rotate_string_in_place_fast:
	sub	$sp, $sp, 8
	sw	$ra, 0($sp)
	sw	$a0, 4($sp)

	jal	my_strlen
	move	$t0, $v0	# length
	lw	$a0, 4($sp)
	lb	$t1, 0($a0)	# was_first = str[0]

	div	$t3, $t0, 4	# length_in_ints = length / 4;

	li	$t2, 0		# i = 0
	move	$a1, $a0	# making copy of 'str' for use in first loop
rsipf_loop1:
	bge	$t2, $t3, rsipf_loop2_prologue
	lw	$t4, 0($a1)	# unsigned first_word = str_as_array_of_ints[i]
	lw	$t5, 4($a1)	# unsigned second_word = str_as_array_of_ints[i+1]
	srl	$t6, $t4, 8	# (first_word >> 8)
	sll	$t7, $t5, 24	# (second_word << 24)
	or	$t7, $t7, $t6	# combined_word = (first_word >> 8) | (second_word << 24)
	sw	$t7, 0($a1)	# str_as_array_of_ints[i] = combined_word
	add	$t2, $t2, 1	# i ++
	add	$a1, $a1, 4	# str_as_array_of_inst ++
	j	rsipf_loop1		

rsipf_loop2_prologue:
	mul	$t2, $t3, 4
	add	$t2, $t2, 1	# i = length_in_ints*4 + 1
rsipf_loop2:
	bge	$t2, $t0, rsipf_done2
	add	$t3, $a0, $t2	# &str[i]
	lb	$t4, 0($t3)	# char c = str[i]
	sb	$t4, -1($t3)	# str[i - 1] = c
	add	$t2, $t2, 1	# i ++
	j	rsipf_loop2		
	
rsipf_done2:
	add	$t3, $a0, $t0	# &str[length]
	sb	$t1, -1($t3)	# str[length - 1] = was_first
	lw	$ra, 0($sp)
	add	$sp, $sp, 8
	jr	$ra



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


my_strcmp:
	li	$t3, 0		# i = 0
my_strcmp_loop:
	add	$t0, $a0, $t3	# &str1[i]
	lb	$t0, 0($t0)	# c1 = str1[i]
	add	$t1, $a1, $t3	# &str2[i]
	lb	$t1, 0($t1)	# c2 = str2[i]

	beq	$t0, $t1, my_strcmp_equal
	sub	$v0, $t0, $t1	# c1 - c2
	jr	$ra

my_strcmp_equal:
	bne	$t0, $0, my_strcmp_not_done
	li	$v0, 0
	jr	$ra

my_strcmp_not_done:
	add	$t3, $t3, 1	# i ++
	j	my_strcmp_loop

###############################	
######Util methods#############
##############################










	


	
#From handout
.kdata
chunkIH:	.space 20	
puzzle_str:	.asciiz "You got mail!\n"
request_str:	.asciiz "Made a request!\n"
newline:	.asciiz "\n"

.ktext 0x80000180
interrupt_handler:
.set noat
	move	$k1,	$at
.set at
	la	$k0,	chunkIH
	sw	$a0,	0($k0)
	sw	$a1,	4($k0)
	sw	$t0,	8($k0)
	sw	$t1,	12($k0)
	sw	$t2,	16($k0)
done:	
	sw	$a0,	DELIVERY_ACKNOWLEDGE
	la	$t9,	signal
	li 	$t8, 	1
	sw	$t8,	0($t9)	
	la	$k0,	chunkIH
	lw	$a0,	0($k0)
	lw	$a1,	4($k0)
	lw	$t0,	8($k0)
	lw	$t1,	12($k0)
	lw	$t2,	16($k0)
.set noat
	move	$at,	$k1
.set at
	eret


print_first_word:
	li	$v0,	4
	la	$a0,	puzzle_container
	lw	$a0,	0($a0)
	syscall
	la	$a0,	newline
	syscall
	syscall
	syscall
	j	$ra

