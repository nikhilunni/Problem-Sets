.data

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

#Planet data
.align 2
planets: .space 120

.text

main:
	###Picking a planet###
	lw	$t0,	LANDING_REQUEST		#t0 = planet
	add	$t0,	$t0,	1
	rem	$t0,	$t0,	5		#planet = (planet+1)%5

	###Taking off###
	sw	$t0	TAKEOFF_REQUEST

	###Getting planet information###
	la	$t1, 	planets			#load our planet array
	sw	$t1,	PLANETS_REQUEST
	li	$t2,	24
	mult	$t0,	$t2
	mflo	$t0				#t0 = planet_byte_offset
	add	$t2,	$t0,	$t1		#t2 = planets[planet]
	move	$t1,	$t2			#t1 = planets[planet]
	li	$t3,	150			#t3 = target.x
	add	$t4,	$t2,	orbital_radius
	lw	$t4,	0($t4)			#t4 = orbital_radius
	add	$t4,	$t4,	150		#t4 = target.y
	lw	$t5,	BOT_X			#t5 = me.x
	lw	$t6,	BOT_Y			#t6 = me.y
	blt	$t5,	$t3,	set_less_x
	li	$t2,	180
	sw	$t2,	ANGLE
	li	$t2,	1
	sw	$t2,	ANGLE_CONTROL
	li	$t2,	10
	sw	$t2,	VELOCITY
loop_x:
	lw	$t5,	BOT_X			#refresh me.x
	beq	$t5,	$t3,	main_continue
	j	loop_x
	

set_less_x:	#if me.x < target.x
	li	$t2,	0
	sw	$t2,	ANGLE
	li	$t2,	1
	sw	$t2,	ANGLE_CONTROL
	li	$t2,	10
	sw	$t2,	VELOCITY
	j	loop_x

main_continue:
	blt	$t6,	$t4,	set_less_y
	li	$t2,	270
	sw	$t2,	ANGLE
	li	$t2,	1
	sw	$t2,	ANGLE_CONTROL
	li	$t2,	10
	sw	$t2,	VELOCITY
loop_y:
	lw	$t6,	BOT_Y			#refresh me.y
	beq	$t6,	$t4,	main_wait
	j	loop_y
	
set_less_y:
	li	$t2,	90
	sw	$t2,	ANGLE
	li	$t2,	1
	sw	$t2,	ANGLE_CONTROL
	li	$t2,	10
	sw	$t2,	VELOCITY
	j	loop_y

main_wait:
	li	$t2,	0
	sw	$t2,	VELOCITY
main_wait_loop:
	sw	$t1,	PLANETS_REQUEST
	add	$t3,	$t1,	planet_x
	add	$t4,	$t1,	planet_y
	lw	$t3,	0($t3)			#t3 = targetPlanet.x	
	lw	$t4,	0($t4)			#t4 = targetPlanet.y
	lw	$t5,	BOT_X			#t5 = refresh(me.x)
	lw	$t6,	BOT_Y			#t6 = refresh(me.y)
	beq	$t5,	$t3,	main_mount
	j	main_wait_loop
main_mount:
	bne	$t4,	$t6,	main_wait_loop
	sw	$t3,	LANDING_REQUEST
main_end:
	jr	$ra
