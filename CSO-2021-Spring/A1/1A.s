.data
arr: 
.word 16, -15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15

.text
.globl bubblesort
bubblesort:
	xorq %rdx, %rdx              # set rdx (i) to 0

outerloop:
	cmpq $31, %rdx               # i < n-1
	jge endsort
	xorq %rcx, %rcx              # set rcx (j) = 0

innerloop:
	cmpq $31, %rcx               # j < n-1
	jge exitinner

	movw (%rdi,%rcx,2), %si      # calc arr[j]
	movw 2(%rdi,%rcx,2), %r8w    # calc arr[j+1]
	cmpw %si, %r8w               # if(arr[j+1]<=arr[j]) swap
	jg swapend
	movw %r8w, (%rdi,%rcx,2)     # swap
	movw %si, 2(%rdi,%rcx,2)

swapend:
	incq %rcx                   # j++
	jmp innerloop

exitinner:
	incq %rdx                   # i++
	jmp outerloop

endsort:
	ret

.globl main
main:
	pushq %rbp              # stack setup routine
	movq %rsp, %rbp

	leaq arr(%rip), %rdi    # load array address into rdi
	call bubblesort

exit:
	pop %rbp
	ret
