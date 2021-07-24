.data
arr:
.word -20, -20, -19, -15, -13, -12, -12, -11, -10, -10, -10, -9, -6, -5, -5, -4, -4, -3, -2, -1, 0, 6, 8, 8, 9, 10, 10, 10, 12, 14, 14, 16

key:
.word -9

.text
.globl seqsearch         # 0 indexed
seqsearch:
	push %rbp            # stack setup
	push %r11            # save caller saved registers
	push %r12
	movq %rsp, %rbp

	xorq %rcx, %rcx      # set rcx = 0 (i)
	xorq %r12, %r12      # set it count = 0
	movq $-1, %r11       # set found = -1

innerloop:
	cmpq $32, %rcx       # while(i<32)
	jge exitinner

	incq %r12            # it count ++
	movw (%rsi,%rcx,2), %dx # calc arr[i]
	cmpw %dx, %di        # if(arr[i]==key)
	jne nextiter
	movq %rcx, %r11      # set found=i
	jmp exitinner

nextiter:
	incq %rcx
	jmp innerloop

exitinner:

	movq %rbp, %rsp      # stack cleanup
	popq %r12
	popq %r11
	popq %rbp
	ret

.globl main
main:
	pushq %rbp              # stack setup routine
	movq %rsp, %rbp

	leaq arr(%rip), %rsi    # move array address into rsi
	movzwq key(%rip), %rdi  # move search key into rdi
	call seqsearch

exit:
	pop %rbp                # stack cleanup
	ret
