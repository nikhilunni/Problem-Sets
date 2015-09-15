# add your own tests for the full machine here!
# feel free to take inspiration from all.s and/or lwbr2.s

.data
array:	.word	1	255	1024
	
.text
main:
	addi	$10, $0, 255
	la	$2, array
	lw	$3, 0($2)
	lw	$4, 4($2)
	beq	$4, $10, equal

	addi 	$11, $0, 1
	j	end

equal:	addi	$12, $0, 2
end:	addi 	$13, $0, 3
	
