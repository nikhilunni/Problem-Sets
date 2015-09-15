# syscall constants
PRINT_INT = 1
PRINT_CHAR = 11
PRINT_STRING = 4

.data
null_str: .asciiz "(null) "
.align 2
test0:	.word	p0xd7c050	p0xd7c210	p0xd7c030
p0xd7c030:	.word	73
p0xd7c050:	.word	p0xd7c090	p0xd7c150	p0xd7c070
p0xd7c070:	.word	45
p0xd7c090:	.word	p0xd7c0d0	p0xd7c110	p0xd7c0b0
p0xd7c0b0:	.word	9
p0xd7c0d0:	.word	0	0	p0xd7c0f0
p0xd7c0f0:	.word	74
p0xd7c110:	.word	0	0	p0xd7c130
p0xd7c130:	.word	26
p0xd7c150:	.word	p0xd7c190	p0xd7c1d0	p0xd7c170
p0xd7c170:	.word	8
p0xd7c190:	.word	0	0	p0xd7c1b0
p0xd7c1b0:	.word	86
p0xd7c1d0:	.word	0	0	p0xd7c1f0
p0xd7c1f0:	.word	99
p0xd7c210:	.word	p0xd7c250	p0xd7c310	p0xd7c230
p0xd7c230:	.word	15
p0xd7c250:	.word	p0xd7c290	p0xd7c2d0	p0xd7c270
p0xd7c270:	.word	7
p0xd7c290:	.word	0	0	p0xd7c2b0
p0xd7c2b0:	.word	4
p0xd7c2d0:	.word	0	0	p0xd7c2f0
p0xd7c2f0:	.word	16
p0xd7c310:	.word	p0xd7c350	p0xd7c390	p0xd7c330
p0xd7c330:	.word	44
p0xd7c350:	.word	0	0	p0xd7c370
p0xd7c370:	.word	92
p0xd7c390:	.word	0	0	p0xd7c3b0
p0xd7c3b0:	.word	92
.align 2
test1:	.word	p0xd7c410	p0xd7c5d0	p0xd7c3f0
p0xd7c3f0:	.word	53
p0xd7c410:	.word	p0xd7c450	p0xd7c510	p0xd7c430
p0xd7c430:	.word	63
p0xd7c450:	.word	p0xd7c490	p0xd7c4d0	p0xd7c470
p0xd7c470:	.word	39
p0xd7c490:	.word	0	0	p0xd7c4b0
p0xd7c4b0:	.word	23
p0xd7c4d0:	.word	0	0	p0xd7c4f0
p0xd7c4f0:	.word	31
p0xd7c510:	.word	p0xd7c550	p0xd7c590	p0xd7c530
p0xd7c530:	.word	75
p0xd7c550:	.word	0	0	p0xd7c570
p0xd7c570:	.word	10
p0xd7c590:	.word	0	0	p0xd7c5b0
p0xd7c5b0:	.word	69
p0xd7c5d0:	.word	p0xd7c610	p0xd7c6d0	p0xd7c5f0
p0xd7c5f0:	.word	41
p0xd7c610:	.word	p0xd7c650	p0xd7c690	p0xd7c630
p0xd7c630:	.word	15
p0xd7c650:	.word	0	0	p0xd7c670
p0xd7c670:	.word	52
p0xd7c690:	.word	0	0	p0xd7c6b0
p0xd7c6b0:	.word	76
p0xd7c6d0:	.word	p0xd7c710	p0xd7c750	p0xd7c6f0
p0xd7c6f0:	.word	15
p0xd7c710:	.word	0	0	p0xd7c730
p0xd7c730:	.word	36
p0xd7c750:	.word	0	0	p0xd7c770
p0xd7c770:	.word	74


.text
# print int and space ##################################################
#
# argument $a0: number to print
# returns       nothing

print_int_and_space:
    li      $v0, PRINT_INT  # load the syscall option for printing ints
    syscall         # print the number

    li      $a0, ' '        # print a blank space
    li      $v0, PRINT_CHAR # load the syscall option for printing chars
    syscall         # print the char
    
    jr      $ra     # return to the calling procedure

# print string ########################################################
#
# argument $a0: string to print
# returns       nothing

print_string:
    li      $v0, PRINT_STRING   # print string command
    syscall                 # string is in $a0
    jr      $ra

# print newline ########################################################
#
# no arguments
# returns       nothing

print_newline:
    li      $a0, '\n'       # print a newline char.
    li      $v0, PRINT_CHAR
    syscall 
    jr      $ra



# print int ptr binary tree ########################################################
#
# argument $a0: int ptr binary tree
# argument $a1: is_root
# returns       nothing
print_int_ptr_binary_tree:
    bne     $a0, $0, pipbt_go
    jr      $ra
pipbt_go:
    sub     $sp, $sp, 12
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)
    sw      $s1, 8($sp)
    move    $s0, $a0
    move    $s1, $a1

    lw      $t0, 8($s0)
    beq     $t0, $0, pipbt_null
    lw      $a0, 0($t0)
    jal     print_int_and_space
    j       pipbt_rec
pipbt_null:
    la      $a0, null_str
    jal     print_string

pipbt_rec:
    lw      $a0, 0($s0)
    move    $a1, $0
    jal     print_int_ptr_binary_tree

    lw      $a0, 4($s0)
    move    $a1, $0
    jal     print_int_ptr_binary_tree

    beq     $s1, $0, pipbt_done
    jal     print_newline

pipbt_done:
    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    lw      $s1, 8($sp)
    add     $sp, $sp, 12
    jr      $ra

# main function ########################################################
#
#  this will test 'tweak_int'
#
#########################################################################
.globl main
main:
    sub     $sp, $sp, 4
    sw      $ra, 0($sp)     # save $ra on stack

    la      $a0, test0
    li      $a1, 71
    lw      $a2, 8($a0)
    lw      $a2, 0($a2)
    jal     tweak_int
    la      $a0, test0
    li      $a1, 1
    jal     print_int_ptr_binary_tree
    la      $a0, test1
    li      $a1, 30
    lw      $a2, 8($a0)
    lw      $a2, 0($a2)
    jal     tweak_int
    la      $a0, test1
    li      $a1, 1
    jal     print_int_ptr_binary_tree

    lw      $ra, 0($sp)
    add     $sp, $sp, 4
    jr      $ra