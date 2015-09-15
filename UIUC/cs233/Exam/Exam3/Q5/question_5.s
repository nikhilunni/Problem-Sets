# run with QtSpim -file main.s question_5.s

# struct node_t {
#     node_t *left;
#     node_t *right;
#     int *data;
# };
# void tweak_int(node_t *root, int save, int spend) {
#     if (root == NULL) {
#         return;
#     }
# 
#     if (root->data != NULL) {
#         if (*(root->data) != save) {
#             save = spend;
#             spend = *(root->data);
#             *(root->data) = save;
#         }
#     }
# 
#     tweak_int(root->left, save, spend);
#     tweak_int(root->right, save, spend);
# }
.globl tweak_int
tweak_int:
	sub	$sp,	$sp,	16
	sw	$ra,	0($sp)
	sw	$a0,	4($sp)
	sw	$a1,	8($sp)
	sw	$a2,	12($sp)
	beq	$a0,	$0,	tweak_int_end
	lw	$t0,	8($a0)			#t0 : root->data
	beq	$t0,	$0,	tweak_int_recurse
	lw	$t1,	0($t0)			#t1 : *(root->data)
	beq	$t1,	$a1,	tweak_int_recurse
	move	$a1,	$a2
	move	$a2,	$t1
	sw	$a1,	0($t0)
tweak_int_recurse:
	sw	$a0,	4($sp)
	sw	$a1,	8($sp)
	sw	$a2,	12($sp)
	lw	$a0,	0($a0)
	jal	tweak_int
	lw	$a0,	4($sp)
	lw	$a1,	8($sp)
	lw	$a2,	12($sp)
	lw	$a0,	4($a0)
	jal	tweak_int
tweak_int_end:
	lw	$a2,	12($sp)
	lw	$a1,	8($sp)
	lw	$a0,	4($sp)
	lw	$ra,	0($sp)
	add	$sp,	$sp,	16
	jr	$ra