.section .rodata
output_str:
	.string "%d\n" #this variable stores the output format string for printf
input_str:
	.string "%d" #this variable stores the input format string for scanf
one_fourth:
	.long	0
	.long	1070596096 #this number in binary is the double representation of 1/4
	.align 8
one_half:
	.long	0
	.long	1071644672 #this number in binary is the double representation of 1/2
	.align 8
	

.text
.globl s
.type s, @function 

#this function computes the following expression 
#	floor(sqrt((2*n+(double)1/4)-(double)1/2))
s:
	addl	%edi, %edi 					#adds n to n to get 2*n
	cvtsi2sdl %edi, %xmm0				#converts 2n to double representation
	movsd 	one_fourth(%rip), %xmm1		#loads 1/4 to the xmm1 register
	addsd	%xmm1, %xmm0				#adds 1/4 to 2n
	movsd 	one_half(%rip), %xmm1		#loads 1/2 to the xmm1 register
	subsd	%xmm1, %xmm0				#subtracts 1/2 from the expression
	sqrtsd  %xmm0, %xmm0				#calls the sqrt func in math.h on xmm0
	cvttsd2sil %xmm0, %eax				#converts from double to int representation
	ret 								

.text
.globl solve
.type solve, @function 

solve:
	pushq	%rbp 			#pushes the base pointer onto the stack				
	movq 	%rsp, %rbp 		#sets the new stack base 
	subq	$16, %rsp		#allocates 16 bytes on the frame

	cmpl	$2, %edi		#if n<=2 calculate and return basecase, else recurse
	jle		basecase

	#recursive call
	movl	%edi, -4(%rbp)  #stores n, input to func
	call	s 			    #calculates s(n), result is in %eax
	movl	%eax, -8(%rbp)  #stores sn, the value of s(n)
	xorl	%eax, %eax 		#clears eax
	movl	-4(%rbp), %edi  #loads n into edi
	subl 	-8(%rbp), %edi  #subtracts sn from n, stores result in %edi
	call	solve 			#calculates solve(n-sn) recursively
	addl	%eax, %eax 		#eax now stores 2*(n-sn)
	movl 	%eax, -12(%rbp) #moves calculated value to our ct variable
	movl 	$1, %edx		#loads 1 into edx
	movl	-8(%rbp), %ecx	#moves sn to ecx
	sall	%cl, %edx 		#equivalent to 1<<sn. It calculates 2^sn and stores it in edx
	subl 	$1, %edx		#subtracts 1 from edx. edx now has 2^sn - 1
	addl	%edx, -12(%rbp) #adds 2^sn - 1 to ct
	movl	-12(%rbp), %eax	#loads ct to the return register
	jmp 	exitsolve 		

basecase:
	addl 	%edi, %edi		#calculates 2*n
	subl 	$1, %edi		#subtracts 1 from 2n
	movl 	%edi, %eax		#loads the value of 2n-1 into the return register
	jmp 	exitsolve		

exitsolve:
	leave					#resets rbp 
	ret

.text
.globl main
main:
	pushq	%rbp
	movq	%rsp, %rbp
	
	subq 	$16, %rsp				#allocates 16 bytes of space on the stack
	leaq	-4(%rbp), %rsi 			#gives rbp-4 as the address for scanf to store input in
	leaq	input_str(%rip), %rdi	#supplies the format string as first parameter
	xorl	%eax, %eax				#clears eax			
	call 	__isoc99_scanf@PLT		#calls scanf
	movl 	-4(%rbp), %edi			#loads n into the first parameter register
	xorl	%eax, %eax				#clears eax
	call 	solve					#calls the solve function
	movl	%eax, %esi 				#loads it into the second parameter register
	xorl	%eax, %eax 				#clears eax
	leaq 	output_str(%rip), %rdi 	#supplies the format string as first parameter
	call 	printf@PLT 				#calls printf
	xorl	%eax, %eax 				#sets return value to 0

	leave
	ret
