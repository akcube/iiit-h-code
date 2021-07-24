.text
.globl rotate90

# rbp-2 => n-1 | done
# rbp-4 => n/2 | done
# rdi => base arr | done
# rsi => i | done
# rdx => j | done 
# rcx => n-1-i | done
# rax => n-1-j | done
# r9 => row i calc 
# rbx => row n-1-i calc 
# r11 => row j calc 
# r10 => row n-1-j calc 
# r8 => temp 
# r12 => temp2
# r13 => temp3
# r14 => temp4

# arr[i][j] = arr+(2*8*i)+2*j
# arr[i][j] = [arr+[(8*i)+j]*2]

rotate90:
	pushq %rbp
	pushq %rbx
	pushq %r12
	pushq %r13
	pushq %r14
	movq %rsp, %rbp
	subq $16, %rsp
	movw $7, -2(%rbp) 
	movw $4, -4(%rbp) 

	xorq %rsi, %rsi
	xorq %rdx, %rdx
	xorq %rcx, %rcx
	xorq %rax, %rax
	movw -2(%rbp), %cx
	
outerloop:
	cmpw -4(%rbp), %si
	jge exitouter
	movzwq %cx, %rax
	movzwq %si, %rdx
	leaq (%rdx, %rsi, 8), %r9 
	leaq (%rax, %rcx, 8), %rbx 

innerloop:
	cmpw %cx, %dx
	jge nextiter
	leaq (%rcx, %rdx, 8), %r11 
	leaq (%rsi, %rax, 8), %r10 

	movw (%rdi, %r9, 2), %r8w

	movw (%rdi, %r10, 2), %r12w
    movw %r12w, (%rdi, %r9, 2)

	movw (%rdi, %rbx, 2), %r13w
	movw %r13w, (%rdi, %r10, 2)

	movw (%rdi, %r11, 2), %r14w
	movw %r14w, (%rdi, %rbx, 2)
	
	movw %r8w, (%rdi, %r11, 2)

	incw %dx
	decw %ax
	decq %rbx
	incq %r9
	jmp innerloop

nextiter:
	incw %si
	decw %cx
	jmp outerloop

exitouter:
	xorq %rax, %rax
	addq $16, %rsp
	popq %r14
	popq %r13
	popq %r12
	popq %rbx
	popq %rbp
	ret
