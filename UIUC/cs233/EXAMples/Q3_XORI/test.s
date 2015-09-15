.data
array:	.word	1	255	1024	100	200

# every register starts holding the address of "array"
#
# this is a cheat so that we don't need to implement addi and lui in
# our machine.

.text
main:   
	lw	$2,  0($20)	# $2 = 1	(0x1)
	lw	$3,  4($20)	# $3 = 255	(0xff)
	lw	$5, 12($20)	# $5 = 100	(0x64)
	lw	$6, 16($20)	# $6 = 200	(0xc8)

	xori	$7, $2, 17
	xori	$8, $3, 0x15c
	xori	$9, $5, 0x55
	xori	$10, $6, 0xc8

