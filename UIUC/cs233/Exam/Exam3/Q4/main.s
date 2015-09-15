# syscall constants
PRINT_INT = 1
PRINT_CHAR = 11
PRINT_STRING = 4

.data
null_str: .asciiz "(null) "
.align 2
test0_A:	.word	p0x10d1050	p0x10d1070	p0x10d1090	p0x10d10b0	p0x10d10d0	p0x10d10f0
p0x10d1050:	.word	77
p0x10d1070:	.word	96
p0x10d1090:	.word	18
p0x10d10b0:	.word	23
p0x10d10d0:	.word	98
p0x10d10f0:	.word	48
.align 2
test0_vals:	.word	7	78	4	69	30	33
.align 2
test1_A:	.word	p0x10d1160	p0x10d1180	p0x10d11a0	p0x10d11c0
p0x10d1160:	.word	31
p0x10d1180:	.word	59
p0x10d11a0:	.word	65
p0x10d11c0:	.word	53
.align 2
test1_vals:	.word	61	7	84	6


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



# print int array ########################################################
#
# argument $a0: int array to print
# argument $a1: length of array
# returns       nothing
print_int_array:
    sub     $sp, $sp, 16
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)
    sw      $s1, 8($sp)
    sw      $s2, 12($sp)
    move    $s0, $a0
    move    $s1, $a1
    move    $s2, $0

pia_loop:
    bge     $s2, $s1, pia_end
    mul     $t0, $s2, 4
    add     $t0, $t0, $s0
    lw      $a0, 0($t0)
    jal     print_int_and_space
    add     $s2, $s2, 1
    j       pia_loop
pia_end:
    jal     print_newline
    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    lw      $s1, 8($sp)
    lw      $s2, 12($sp)
    add     $sp, $sp, 16
    jr      $ra
# main function ########################################################
#
#  this will test 'increment_vals'
#
#########################################################################
.globl main
main:
    sub     $sp, $sp, 4
    sw      $ra, 0($sp)     # save $ra on stack

    la      $a0, test0_A
    la      $a1, test0_vals
    li      $a2, 6
    jal     increment_vals
    la      $a0, test0_vals
    li      $a1, 6
    jal     print_int_array
    la      $a0, test1_A
    la      $a1, test1_vals
    li      $a2, 4
    jal     increment_vals
    la      $a0, test1_vals
    li      $a1, 4
    jal     print_int_array

    lw      $ra, 0($sp)
    add     $sp, $sp, 4
    jr      $ra