	.file	"OG.c"
	.text
	.comm	sizex,4,4
	.comm	table,2097152,32
	.comm	temp_word,46,32
	.comm	file_in_mem,8,8
	.comm	hashval,4,4
	.comm	copy,4,4
	.comm	clusters,4,4
	.globl	check
	.type	check, @function
check:
.LFB4006:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	$5381, -8(%rbp)
	movb	$0, -9(%rbp)
	movzbl	-9(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movzbl	-9(%rbp), %eax
	cltq
	leaq	temp_word(%rip), %rcx
	addq	%rcx, %rax
	orl	$538976288, %edx
	movl	%edx, (%rax)
	jmp	.L2
.L3:
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-9(%rbp), %eax
	cltq
	leaq	temp_word(%rip), %rcx
	addq	%rcx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	addb	$4, -9(%rbp)
	movzbl	-9(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movzbl	-9(%rbp), %eax
	cltq
	leaq	temp_word(%rip), %rcx
	addq	%rcx, %rax
	orl	$538976288, %edx
	movl	%edx, (%rax)
.L2:
	movzbl	-9(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	leal	-16843009(%rax), %ecx
	movzbl	-9(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	notl	%eax
	andl	%ecx, %eax
	andl	$-2139062144, %eax
	testl	%eax, %eax
	je	.L3
	movzbl	-9(%rbp), %edx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	je	.L4
	movzbl	-9(%rbp), %eax
	leaq	1(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L5
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movzbl	-9(%rbp), %eax
	leal	1(%rax), %edx
	movb	%dl, -9(%rbp)
	movzbl	%al, %eax
	cltq
	leaq	temp_word(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movzbl	%al, %eax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	jmp	.L4
.L5:
	movzbl	-9(%rbp), %eax
	leaq	2(%rax), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	testb	%al, %al
	jne	.L6
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-9(%rbp), %eax
	cltq
	leaq	temp_word(%rip), %rcx
	addq	%rcx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	addb	$2, -9(%rbp)
	jmp	.L4
.L6:
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	addq	%rax, %rdx
	movzbl	-9(%rbp), %eax
	cltq
	leaq	temp_word(%rip), %rcx
	addq	%rcx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	addq	%rdx, %rax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movzbl	-9(%rbp), %eax
	addl	$2, %eax
	cltq
	leaq	temp_word(%rip), %rdx
	movzbl	(%rax,%rdx), %eax
	movzbl	%al, %eax
	addq	%rcx, %rax
	movq	%rax, -8(%rbp)
	addb	$3, -9(%rbp)
.L4:
	movq	-8(%rbp), %rax
	shrq	$12, %rax
	xorq	-8(%rbp), %rax
	andl	$524287, %eax
	movq	%rax, -8(%rbp)
	movq	-8(%rbp), %rax
	movl	%eax, hashval(%rip)
	movzbl	-9(%rbp), %eax
	leal	1(%rax), %edx
	movb	%dl, -9(%rbp)
	movzbl	%al, %eax
	cltq
	leaq	temp_word(%rip), %rdx
	movb	$10, (%rax,%rdx)
	jmp	.L7
.L10:
	movzbl	-9(%rbp), %eax
	movq	file_in_mem(%rip), %rdx
	movq	-8(%rbp), %rcx
	leaq	0(,%rcx,4), %rsi
	leaq	table(%rip), %rcx
	movl	(%rsi,%rcx), %ecx
	movl	%ecx, %ecx
	addq	%rdx, %rcx
	movq	%rax, %rdx
	leaq	temp_word(%rip), %rsi
	movq	%rcx, %rdi
	call	memcmp@PLT
	testl	%eax, %eax
	jne	.L8
	movl	hashval(%rip), %eax
	movl	%eax, %eax
	leaq	0(,%rax,4), %rdx
	leaq	table(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%eax, copy(%rip)
	movl	hashval(%rip), %ecx
	movq	-8(%rbp), %rax
	leaq	0(,%rax,4), %rdx
	leaq	table(%rip), %rax
	movl	(%rdx,%rax), %eax
	movl	%ecx, %edx
	leaq	0(,%rdx,4), %rcx
	leaq	table(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	copy(%rip), %eax
	movq	-8(%rbp), %rdx
	leaq	0(,%rdx,4), %rcx
	leaq	table(%rip), %rdx
	movl	%eax, (%rcx,%rdx)
	movl	$1, %eax
	jmp	.L9
.L8:
	movl	clusters(%rip), %eax
	addl	$1, %eax
	movl	%eax, clusters(%rip)
	movq	-8(%rbp), %rax
	movabsq	$-7046029254386353131, %rdx
	imulq	%rdx, %rax
	shrq	$45, %rax
	movq	%rax, -8(%rbp)
.L7:
	movq	-8(%rbp), %rax
	leaq	0(,%rax,4), %rdx
	leaq	table(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	jne	.L10
	movl	$0, %eax
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4006:
	.size	check, .-check
	.globl	hash
	.type	hash, @function
hash:
.LFB4007:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4007:
	.size	hash, .-hash
	.section	.rodata
.LC0:
	.string	"Error opening file"
	.text
	.globl	load
	.type	load, @function
load:
.LFB4008:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movq	%rdi, -200(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$2097152, %edx
	movl	$0, %esi
	leaq	table(%rip), %rdi
	call	memset@PLT
	movl	$0, sizex(%rip)
	movq	-200(%rbp), %rax
	movl	$384, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, -172(%rbp)
	leaq	-160(%rbp), %rdx
	movl	-172(%rbp), %eax
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	fstat@PLT
	cmpl	$-1, %eax
	jne	.L14
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	jmp	.L29
.L14:
	movq	-112(%rbp), %rax
	movq	%rax, %rsi
	movl	-172(%rbp), %eax
	movl	$0, %r9d
	movl	%eax, %r8d
	movl	$2, %ecx
	movl	$1, %edx
	movl	$0, %edi
	call	mmap@PLT
	movq	%rax, file_in_mem(%rip)
	movq	$5381, -168(%rbp)
	movl	$1, -180(%rbp)
	movl	$0, -176(%rbp)
	jmp	.L16
.L28:
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movq	(%rax), %rax
	movabsq	$2314885530818453536, %rdx
	andq	%rax, %rdx
	movabsq	$2314885530818453536, %rax
	cmpq	%rax, %rdx
	jne	.L17
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$4, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$8, -176(%rbp)
	jmp	.L16
.L17:
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L18
	addl	$1, -176(%rbp)
	jmp	.L19
.L18:
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$1, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L20
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$2, -176(%rbp)
	jmp	.L19
.L20:
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$2, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L21
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$3, -176(%rbp)
	jmp	.L19
.L21:
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$3, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L22
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$2, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$4, -176(%rbp)
	jmp	.L19
.L22:
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$4, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L23
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$5, -176(%rbp)
	jmp	.L19
.L23:
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$5, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L24
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$4, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$6, -176(%rbp)
	jmp	.L19
.L24:
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$6, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L25
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$4, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$7, -176(%rbp)
	jmp	.L19
.L25:
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$7, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	cmpb	$10, %al
	jne	.L19
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rdx
	movl	-176(%rbp), %eax
	cltq
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$4, %rdx
	addq	%rdx, %rax
	movzwl	(%rax), %eax
	movzwl	%ax, %eax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	movq	-168(%rbp), %rax
	salq	$5, %rax
	movq	%rax, %rdx
	movq	-168(%rbp), %rax
	leaq	(%rdx,%rax), %rcx
	movq	file_in_mem(%rip), %rax
	movl	-176(%rbp), %edx
	movslq	%edx, %rdx
	addq	$6, %rdx
	addq	%rdx, %rax
	movzbl	(%rax), %eax
	movsbq	%al, %rax
	addq	%rcx, %rax
	movq	%rax, -168(%rbp)
	addl	$8, -176(%rbp)
.L19:
	movq	-168(%rbp), %rax
	shrq	$12, %rax
	xorq	-168(%rbp), %rax
	andl	$524287, %eax
	movq	%rax, -168(%rbp)
	jmp	.L26
.L27:
	movq	-168(%rbp), %rax
	movabsq	$-7046029254386353131, %rdx
	imulq	%rdx, %rax
	shrq	$45, %rax
	movq	%rax, -168(%rbp)
.L26:
	movq	-168(%rbp), %rax
	leaq	0(,%rax,4), %rdx
	leaq	table(%rip), %rax
	movl	(%rdx,%rax), %eax
	testl	%eax, %eax
	jne	.L27
	movq	-168(%rbp), %rax
	leaq	0(,%rax,4), %rcx
	leaq	table(%rip), %rdx
	movl	-180(%rbp), %eax
	movl	%eax, (%rcx,%rdx)
	movq	$5381, -168(%rbp)
	movl	sizex(%rip), %eax
	addl	$1, %eax
	movl	%eax, sizex(%rip)
	movl	-176(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -180(%rbp)
.L16:
	movl	-176(%rbp), %eax
	movslq	%eax, %rdx
	movq	-112(%rbp), %rax
	cmpq	%rax, %rdx
	jl	.L28
	movl	-172(%rbp), %eax
	movl	%eax, %edi
	call	close@PLT
	movq	file_in_mem(%rip), %rax
	subq	$1, %rax
	movq	%rax, file_in_mem(%rip)
	movl	$1, %eax
.L29:
	movq	-8(%rbp), %rsi
	xorq	%fs:40, %rsi
	je	.L30
	call	__stack_chk_fail@PLT
.L30:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4008:
	.size	load, .-load
	.globl	size
	.type	size, @function
size:
.LFB4009:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	sizex(%rip), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4009:
	.size	size, .-size
	.section	.rodata
.LC1:
	.string	"Clusters: %i\n"
	.text
	.globl	unload
	.type	unload, @function
unload:
.LFB4010:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	clusters(%rip), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$1, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4010:
	.size	unload, .-unload
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
