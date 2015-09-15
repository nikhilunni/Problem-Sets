.data
array:	.word	21	462	-273	0

# every register starts holding the address of "array"
#
# this is a cheat so that we don't need to implement addi and lui in
# our machine.

.text
main:
	lw	$2, 0($20)	# $2 = 21	(0x00000015)

	lwsin	$3, 4($20)
	add	$13, $2, $2
	lwsin	$4, 8($20)
	add	$14, $2, $2
	lwsin	$5, 12($20)
	add	$15, $2, $2
