	.file	"counters.cpp"
	.section	.rodata
.LC0:
	.string	"counters.cpp"
.LC1:
	.string	"x.fd >= 0"
	.text
	.type	_ZL11initCounterR11hwCounter_tm, @function
_ZL11initCounterR11hwCounter_tm:
.LFB36:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	-40(%rbp), %rax
	movzbl	(%rax), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L1
	movq	-40(%rbp), %rax
	addq	$8, %rax
	movl	$96, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	memset
	movq	-40(%rbp), %rax
	movzbl	48(%rax), %edx
	andl	$-2, %edx
	movb	%dl, 48(%rax)
	movq	-40(%rbp), %rax
	movl	$0, 8(%rax)
	movq	-40(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, 16(%rax)
	movl	$0, -20(%rbp)
	movl	$-1, -16(%rbp)
	movl	$-1, -12(%rbp)
	movq	$0, -8(%rbp)
	movq	-40(%rbp), %rax
	leaq	8(%rax), %rsi
	movq	-8(%rbp), %rdi
	movl	-12(%rbp), %ecx
	movl	-16(%rbp), %edx
	movl	-20(%rbp), %eax
	movq	%rdi, %r9
	movl	%ecx, %r8d
	movl	%edx, %ecx
	movl	%eax, %edx
	movl	$298, %edi
	movl	$0, %eax
	call	syscall
	movl	%eax, %edx
	movq	-40(%rbp), %rax
	movl	%edx, 4(%rax)
	movq	-40(%rbp), %rax
	movl	4(%rax), %eax
	testl	%eax, %eax
	jns	.L3
	movl	$_ZZL11initCounterR11hwCounter_tmE19__PRETTY_FUNCTION__, %ecx
	movl	$17, %edx
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	__assert_fail
.L3:
	movq	-40(%rbp), %rax
	movb	$1, (%rax)
.L1:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE36:
	.size	_ZL11initCounterR11hwCounter_tm, .-_ZL11initCounterR11hwCounter_tm
	.globl	_Z9initTicksR11hwCounter_t
	.type	_Z9initTicksR11hwCounter_t, @function
_Z9initTicksR11hwCounter_t:
.LFB37:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZL11initCounterR11hwCounter_tm
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE37:
	.size	_Z9initTicksR11hwCounter_t, .-_Z9initTicksR11hwCounter_t
	.globl	_Z9initInsnsR11hwCounter_t
	.type	_Z9initInsnsR11hwCounter_t, @function
_Z9initInsnsR11hwCounter_t:
.LFB38:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZL11initCounterR11hwCounter_tm
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE38:
	.size	_Z9initInsnsR11hwCounter_t, .-_Z9initInsnsR11hwCounter_t
	.section	.rodata
.LC2:
	.string	"rc == sizeof(x.buffer)"
	.text
	.globl	_Z8getTicksR11hwCounter_t
	.type	_Z8getTicksR11hwCounter_t, @function
_Z8getTicksR11hwCounter_t:
.LFB39:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L7
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_Z9initTicksR11hwCounter_t
.L7:
	movq	-24(%rbp), %rax
	leaq	104(%rax), %rcx
	movq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	$8, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	cmpq	$8, %rax
	je	.L8
	movl	$_ZZ8getTicksR11hwCounter_tE19__PRETTY_FUNCTION__, %ecx
	movl	$41, %edx
	movl	$.LC0, %esi
	movl	$.LC2, %edi
	call	__assert_fail
.L8:
	movq	-24(%rbp), %rax
	movq	104(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE39:
	.size	_Z8getTicksR11hwCounter_t, .-_Z8getTicksR11hwCounter_t
	.globl	_Z8getInsnsR11hwCounter_t
	.type	_Z8getInsnsR11hwCounter_t, @function
_Z8getInsnsR11hwCounter_t:
.LFB40:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	-24(%rbp), %rax
	movzbl	(%rax), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	.L11
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_Z9initInsnsR11hwCounter_t
.L11:
	movq	-24(%rbp), %rax
	leaq	104(%rax), %rcx
	movq	-24(%rbp), %rax
	movl	4(%rax), %eax
	movl	$8, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	cltq
	cmpq	$8, %rax
	je	.L12
	movl	$_ZZ8getInsnsR11hwCounter_tE19__PRETTY_FUNCTION__, %ecx
	movl	$57, %edx
	movl	$.LC0, %esi
	movl	$.LC2, %edi
	call	__assert_fail
.L12:
	movq	-24(%rbp), %rax
	movq	104(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE40:
	.size	_Z8getInsnsR11hwCounter_t, .-_Z8getInsnsR11hwCounter_t
	.section	.rodata
	.align 32
	.type	_ZZL11initCounterR11hwCounter_tmE19__PRETTY_FUNCTION__, @object
	.size	_ZZL11initCounterR11hwCounter_tmE19__PRETTY_FUNCTION__, 41
_ZZL11initCounterR11hwCounter_tmE19__PRETTY_FUNCTION__:
	.string	"void initCounter(hwCounter_t&, uint64_t)"
	.align 32
	.type	_ZZ8getTicksR11hwCounter_tE19__PRETTY_FUNCTION__, @object
	.size	_ZZ8getTicksR11hwCounter_tE19__PRETTY_FUNCTION__, 32
_ZZ8getTicksR11hwCounter_tE19__PRETTY_FUNCTION__:
	.string	"uint64_t getTicks(hwCounter_t&)"
	.align 32
	.type	_ZZ8getInsnsR11hwCounter_tE19__PRETTY_FUNCTION__, @object
	.size	_ZZ8getInsnsR11hwCounter_tE19__PRETTY_FUNCTION__, 32
_ZZ8getInsnsR11hwCounter_tE19__PRETTY_FUNCTION__:
	.string	"uint64_t getInsns(hwCounter_t&)"
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
