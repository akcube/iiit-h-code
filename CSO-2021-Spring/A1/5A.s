.text
.globl hammingdis
hammingdis:
	pushq %rbp
	movq %rsp, %rbp

	xorw %di, %si
	movzwq %si, %rsi
	xorq %rax, %rax

loop:
    cmpw $0, %si
    je endloop
    movw %si, %dx
    andw $1, %dx
    addw %dx, %ax
    shr %si
    jmp loop

endloop:
	leave 
	ret
