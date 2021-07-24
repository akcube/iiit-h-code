.text

.globl freqcnt
freqcnt:
	movq %rdi, %rdx      
	addq $32, %rdx       # rdx = end of string
	xorq %rcx, %rcx      # clear rcx

loop:
	cmpq %rdi, %rdx      # if end of string exit loop
	je endloop

	movb (%rdi), %cl     # cl = str[i]
	subb $65, %cl        # cl -= 65
	cmpb $0, %cl         # if 0 <= cl < 26 continue
	jl nextiter
	cmpb $26, %cl
	jge nextiter
	incl (%rsi, %rcx, 4) # inc freq[cl]

nextiter:
	incq %rdi
	jmp loop

endloop:
	ret
