	.file	"goldbach.c"
	.text
	.p2align 4
	.globl	is_prime
	.type	is_prime, @function
is_prime:
.LFB11:
	.cfi_startproc
	xorl	%eax, %eax
	cmpl	$1, %edi
	jle	.L1
	leaq	lp(%rip), %rax
	movslq	%edi, %rdx
	cmpl	%edi, (%rax,%rdx,4)
	sete	%al
.L1:
	ret
	.cfi_endproc
.LFE11:
	.size	is_prime, .-is_prime
	.p2align 4
	.globl	prec
	.type	prec, @function
prec:
.LFB12:
	.cfi_startproc
	leaq	8+lp(%rip), %rdi
	movl	$2, %esi
	xorl	%r8d, %r8d
	leaq	-8(%rdi), %r10
	leaq	pr(%rip), %r9
	.p2align 4,,10
	.p2align 3
.L11:
	movl	(%rdi), %eax
	testl	%eax, %eax
	jne	.L6
	movl	%esi, (%rdi)
	movslq	%r8d, %rax
	addl	$1, %r8d
	movl	%esi, (%r9,%rax,4)
	movl	%esi, %eax
.L7:
	xorl	%ecx, %ecx
	jmp	.L9
	.p2align 4,,10
	.p2align 3
.L14:
	movl	%edx, %eax
	imull	%esi, %eax
	cmpl	$10000000, %eax
	jg	.L8
	cltq
	addq	$1, %rcx
	movl	%edx, (%r10,%rax,4)
	cmpl	%ecx, %r8d
	jle	.L8
	movl	(%rdi), %eax
.L9:
	movl	(%r9,%rcx,4), %edx
	cmpl	%eax, %edx
	jle	.L14
.L8:
	addl	$1, %esi
	addq	$4, %rdi
	cmpl	$10000001, %esi
	jne	.L11
.L15:
	ret
	.p2align 4,,10
	.p2align 3
.L6:
	testl	%r8d, %r8d
	jne	.L7
	addl	$1, %esi
	addq	$4, %rdi
	cmpl	$10000001, %esi
	jne	.L11
	jmp	.L15
	.cfi_endproc
.LFE12:
	.size	prec, .-prec
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"goldbach.c"
.LC1:
	.string	"n%2 == 1"
	.text
	.p2align 4
	.globl	verify_odd_goldbach
	.type	verify_odd_goldbach, @function
verify_odd_goldbach:
.LFB13:
	.cfi_startproc
	movl	%edi, %edx
	shrl	$31, %edx
	leal	(%rdi,%rdx), %eax
	andl	$1, %eax
	subl	%edx, %eax
	cmpl	$1, %eax
	jne	.L17
	leaq	pr(%rip), %r10
	xorl	%r11d, %r11d
	leaq	lp(%rip), %r9
	leaq	2658316(%r10), %r8
.L18:
	movl	(%r10), %esi
	movq	%r10, %rax
	jmp	.L21
	.p2align 4,,10
	.p2align 3
.L19:
	addq	$4, %rax
	cmpq	%rax, %r8
	je	.L29
.L21:
	movl	(%rax), %ecx
	movl	%edi, %edx
	addl	%esi, %ecx
	subl	%ecx, %edx
	cmpl	$1, %edx
	jle	.L19
	movslq	%edx, %rcx
	cmpl	(%r9,%rcx,4), %edx
	jne	.L19
	movl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L29:
	addq	$1, %r11
	addq	$4, %r10
	cmpq	$664579, %r11
	jne	.L18
	xorl	%eax, %eax
	ret
.L17:
	pushq	%rax
	.cfi_def_cfa_offset 16
	leaq	__PRETTY_FUNCTION__.1(%rip), %rcx
	movl	$27, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE13:
	.size	verify_odd_goldbach, .-verify_odd_goldbach
	.section	.rodata.str1.1
.LC2:
	.string	"n%2 == 0"
	.text
	.p2align 4
	.globl	verify_even_goldbach
	.type	verify_even_goldbach, @function
verify_even_goldbach:
.LFB14:
	.cfi_startproc
	testb	$1, %dil
	jne	.L39
	leaq	pr(%rip), %rax
	leaq	lp(%rip), %r8
	leaq	2658316(%rax), %rsi
	jmp	.L33
	.p2align 4,,10
	.p2align 3
.L32:
	addq	$4, %rax
	cmpq	%rsi, %rax
	je	.L40
.L33:
	movl	%edi, %edx
	subl	(%rax), %edx
	cmpl	$1, %edx
	jle	.L32
	movslq	%edx, %rcx
	cmpl	(%r8,%rcx,4), %edx
	jne	.L32
	movl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L40:
	xorl	%eax, %eax
	ret
.L39:
	pushq	%rax
	.cfi_def_cfa_offset 16
	leaq	__PRETTY_FUNCTION__.0(%rip), %rcx
	movl	$38, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE14:
	.size	verify_even_goldbach, .-verify_even_goldbach
	.p2align 4
	.globl	verify_goldbach
	.type	verify_goldbach, @function
verify_goldbach:
.LFB15:
	.cfi_startproc
	movl	%edi, %ecx
	andl	$1, %edi
	jne	.L42
	leaq	pr(%rip), %rax
	leaq	lp(%rip), %r8
	leaq	2658316(%rax), %rdi
	jmp	.L49
	.p2align 4,,10
	.p2align 3
.L43:
	addq	$4, %rax
	cmpq	%rax, %rdi
	je	.L59
.L49:
	movl	%ecx, %edx
	subl	(%rax), %edx
	cmpl	$1, %edx
	jle	.L43
	movslq	%edx, %rsi
	cmpl	(%r8,%rsi,4), %edx
	jne	.L43
.L52:
	movl	$1, %eax
	ret
	.p2align 4,,10
	.p2align 3
.L42:
	movl	%ecx, %edx
	shrl	$31, %edx
	leal	(%rcx,%rdx), %eax
	andl	$1, %eax
	subl	%edx, %eax
	cmpl	$1, %eax
	jne	.L45
	leaq	pr(%rip), %r10
	xorl	%r11d, %r11d
	leaq	lp(%rip), %r9
	leaq	2658316(%r10), %r8
.L46:
	movl	(%r10), %edi
	movq	%r10, %rax
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L47:
	addq	$4, %rax
	cmpq	%r8, %rax
	je	.L61
.L48:
	movl	(%rax), %esi
	movl	%ecx, %edx
	addl	%edi, %esi
	subl	%esi, %edx
	cmpl	$1, %edx
	jle	.L47
	movslq	%edx, %rsi
	cmpl	(%r9,%rsi,4), %edx
	je	.L52
	addq	$4, %rax
	cmpq	%r8, %rax
	jne	.L48
.L61:
	addq	$1, %r11
	addq	$4, %r10
	cmpq	$664579, %r11
	jne	.L46
.L59:
	xorl	%eax, %eax
	ret
.L45:
	pushq	%rax
	.cfi_def_cfa_offset 16
	leaq	__PRETTY_FUNCTION__.1(%rip), %rcx
	movl	$27, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE15:
	.size	verify_goldbach, .-verify_goldbach
	.section	.rodata.str1.1
.LC3:
	.string	"Goldbach verified till: %d\n"
.LC4:
	.string	"Goldbach failed for: %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	xorl	%eax, %eax
	movl	$6, %ebp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	leaq	lp(%rip), %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	call	prec
	.p2align 4,,10
	.p2align 3
.L63:
	testb	$1, %bpl
	jne	.L65
.L86:
	leaq	pr(%rip), %rax
	leaq	2658316(%rax), %rsi
	jmp	.L75
	.p2align 4,,10
	.p2align 3
.L66:
	addq	$4, %rax
	cmpq	%rax, %rsi
	je	.L71
.L75:
	movl	%ebp, %edx
	subl	(%rax), %edx
	cmpl	$1, %edx
	jle	.L66
	movslq	%edx, %rcx
	cmpl	(%rbx,%rcx,4), %edx
	jne	.L66
.L67:
	addl	$1, %ebp
	cmpl	$5001, %ebp
	je	.L82
	imull	$652835029, %ebp, %eax
	rorl	$2, %eax
	cmpl	$8589934, %eax
	ja	.L63
	xorl	%eax, %eax
	movl	%ebp, %esi
	leaq	.LC3(%rip), %rdi
	call	printf@PLT
	testb	$1, %bpl
	je	.L86
.L65:
	leaq	pr(%rip), %r8
	xorl	%r9d, %r9d
	leaq	2658316(%r8), %rdi
.L69:
	movl	(%r8), %esi
	movq	%r8, %rax
	jmp	.L72
	.p2align 4,,10
	.p2align 3
.L70:
	addq	$4, %rax
	cmpq	%rdi, %rax
	je	.L87
.L72:
	movl	(%rax), %ecx
	movl	%ebp, %edx
	addl	%esi, %ecx
	subl	%ecx, %edx
	cmpl	$1, %edx
	jle	.L70
	movslq	%edx, %rcx
	cmpl	(%rbx,%rcx,4), %edx
	je	.L67
	addq	$4, %rax
	cmpq	%rdi, %rax
	jne	.L72
.L87:
	addq	$1, %r9
	addq	$4, %r8
	cmpq	$664579, %r9
	jne	.L69
.L71:
	movl	%ebp, %esi
	leaq	.LC4(%rip), %rdi
	xorl	%eax, %eax
	call	printf@PLT
.L82:
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE16:
	.size	main, .-main
	.section	.rodata
	.align 16
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 21
__PRETTY_FUNCTION__.0:
	.string	"verify_even_goldbach"
	.align 16
	.type	__PRETTY_FUNCTION__.1, @object
	.size	__PRETTY_FUNCTION__.1, 20
__PRETTY_FUNCTION__.1:
	.string	"verify_odd_goldbach"
	.globl	pr
	.bss
	.align 32
	.type	pr, @object
	.size	pr, 2658316
pr:
	.zero	2658316
	.globl	lp
	.align 32
	.type	lp, @object
	.size	lp, 40000004
lp:
	.zero	40000004
	.ident	"GCC: (GNU) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
