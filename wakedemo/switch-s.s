	.arch msp430g2553
	.p2align 1,0
	.text
	
	.extern snowFlakes
	.extern color
	.global jumpTable
cases:
	.word default 		;cases[0]
	.word case1 		;cases[1]
	.word case2 		;cases[2]
	
jumpTable:
	cmp #3, r12
	jhs default
	add r12, r12
	mov cases(r12), r0
case1:
	add #1, &snowFlakes
	mov #5, r12
	cmp &snowFlakes, r12
	jc end	
	mov #5, &snowFlakes
	jmp end
case2:
	add #3, &color
	and #63, &color
default:
end:
	pop r0
	

