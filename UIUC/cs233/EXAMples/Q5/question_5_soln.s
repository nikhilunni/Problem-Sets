# run with QtSpim -file main.s question_5_soln.s

# struct node_t {
#     node_t *left;
#     node_t *right;
#     int *data;
# };
# int total_tree(node_t *root) {
#     if (root == NULL) {
#         return 0;
#     }
# 
#     int total = 0;
#     if (root->data != NULL) {
#         total += *(root->data);
#     }
# 
#     total += total_tree(root->left);
#     total += total_tree(root->right);
# 
#     return total;
# }
.globl total_tree
total_tree:
    bne     $a0, $0, tt_go
    move    $v0, $0
    jr      $ra
tt_go:
    sub     $sp, $sp, 12
    sw      $ra, 0($sp)
    sw      $s0, 4($sp)
    sw      $s1, 8($sp)
    move    $s0, $a0

    move    $s1, $0
    lw      $t0, 8($s0)
    beq     $t0, $0, tt_rec
    lw      $s1, 0($t0)

tt_rec:
    lw      $a0, 0($s0)
    jal     total_tree
    add     $s1, $s1, $v0

    lw      $a0, 4($s0)
    jal     total_tree
    add     $v0, $s1, $v0

    lw      $ra, 0($sp)
    lw      $s0, 4($sp)
    lw      $s1, 8($sp)
    add     $sp, $sp, 12
    jr      $ra
