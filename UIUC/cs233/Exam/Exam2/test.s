.data
array:		.word	16	-255	1024	-1

# every register starts holding the address of "array"
#
# this is a cheat so that we don't need to implement addi and lui in
# our machine.

.text
main:   
	lw	$2,  0($20)	# $2 = 16	(0x10)	
	lw	$3,  4($20)	# $3 = -255	(0xffffff01)
	lw	$4,  8($20)	# $4 = 1024	(0x400)
	lw	$5,  12($20)	# $5 = -1	(0xffffffff)

	max	$10, $2, $3
	max	$11, $3, $2
	max	$12, $2, $4
	max	$13, $4, $2
	max	$14, $3, $5
	max	$15, $5, $3
	max	$16, $2, $0
	max	$17, $0, $2
	max	$18, $5, $0
	max	$19, $0, $5



