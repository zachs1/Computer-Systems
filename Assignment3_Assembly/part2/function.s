# your assembly code
.global _start

.options:
	.ascii "Select an operation:\n1 - add\n2 - subtract\n"

.newline:
	.ascii "\n"

.neg:
	.ascii "-"

.data
	ten:		.quad 10
	digits:     	.byte 0,0,0,0,0,0,0,0							
	
.bss
	in1:	.quad 0
	in2:	.quad 0
	in1Neg: .byte 0
	in2Neg: .byte 0
	result: .quad 0
	len1:	.byte 0
	len2:	.byte 0
	option: .quad 0
	
.text

_printOptions:
    movq $1, %rax
	movq $1, %rdi
	leaq .options,%rsi 
	movq $42, %rdx
	syscall
	ret

_readAns:
	movq $0, %rax
	movq $0, %rdi
	movq $option, %rsi
	movq $4, %rdx
	syscall
	movq option, %r8
	subq $0xa30, %r8
	movq %r8, option
	movq $0, %r8
	ret

_getArg1:
	movq $0, %rax
	movq $0, %rdi
	movq $in1, %rsi
	movq $8, %rdx
	syscall	
	ret

_getArg2:
	movq $0, %rax
	movq $0, %rdi
	movq $in2, %rsi
	movq $8, %rdx
	syscall	
	ret

_asciiToHex1:
	movq in1, %r11
	movq $0, %rax
	movq $0, %r8
	movq $0, %r9
	movq $0, %r10		
		
	.divLoop:
		imulq ten			# shift left each loop, if first loop remain 0
		movq $0xFF, %r9
		andq %r11, %r9
		cmpq $0x2d, %r9
		je .negIn1
		subq $0x30, %r9
		addq %r9, %rax
		sarq $8, %r11
		cmpq $0xa, %r11
		jne .divLoop
		jmp .hex1

	.negIn1:
		sarq $8, %r11
		movb $1, in1Neg
		jmp .divLoop
	
	.hex1:	
		cmpq $1, in1Neg
		jne .move1
		imulq $-1, %rax

		.move1:
			movq %rax, in1
			ret

_asciiToHex2:
	movq in2, %r11
	movq $0, %rax
	movq $0, %r8
	movq $0, %r9
	movq $0, %r10		
	
	.divLoop2:
		imulq ten			# shift left each loop, if first loop remain 0
		movq $0xFF, %r9
		andq %r11, %r9
		cmpq $0x2d, %r9
		je .negIn2
		subq $0x30, %r9
		addq %r9, %rax
		sarq $8, %r11
		cmpq $0xa, %r11
		jne .divLoop2
		jmp .hex2

	.negIn2:
		sarq $8, %r11
		movb $1, in2Neg
		jmp .divLoop2
	
	.hex2:
		cmpq $1, in2Neg
		jne .move2
		imulq $-1, %rax
		
		.move2:
			movq %rax, in2
			ret

_sub:
	movq in1, %r8
	movq in2, %r9
	subq %r9, %r8
	movq %r8, result
	ret

_add:
	movq in1, %r8
	movq in2, %r9
	addq %r9, %r8
	movq %r8, result
	ret

# check if we want sub or add
_doOp:
	call _asciiToHex1
	call _asciiToHex2

	movq option, %r8
	cmpq $0x1, %r8
	
	je .add
	
	.sub:	
		call _sub
		ret

	.add:
		call _add
		ret

_printNeg:
	movq $1, %rax           
	movq $1, %rdi          
	leaq .neg, %rsi  
	movq $1, %rdx                   
	syscall                 				    
	ret

_printResult:
		
    movq result,%rax				
    movq $0, %r15
	.ploop:  # Label where will loop from
		testq %rax, %rax
		jns .positive
		call _printNeg
		movq result, %rax
		imulq $-1, %rax

		.positive:
			movq $10, %rdi  # What we'll divide by 
			movq $0, %rdx   # Remainder
			idivq %rdi      # Quotient stored in rax
			movq %rdx, digits(,%r15,1)  # remainder stored in 'digit'
											
			# convert remainder to 'ascii'
			# We add '48' to our digit to do so
			addq $48,digits(,%r15,1)
			# Move to the next digit   
			incq %r15
			# Check if we're done
			cmpq $0,%rax
			jne .ploop						    
			# Here is our second loop for printing the digits in the 
			#correct order
			# In this case I am just looping through the characters
			# we have stored backwards from our counter.
			.chars:
				decq %r15
				leaq digits(,%r15,1),%rsi 
				movq $1,%rax           
				movq $1,%rdi          
				movq $1, %rdx          
				syscall                 																							    
				cmpq $0,%r15
				jne .chars   
																										 
	ret 

_writeNewLine:
    movq $1, %rax           
	movq $1, %rdi          
	leaq .newline, %rsi  
	movq $1, %rdx                   
	syscall                 				    
	ret
																	       
_exit:
	movq $60, %rax
	xor %rdi, %rdi
	syscall

_start:
	call _printOptions
	call _readAns
	call _getArg1
	call _getArg2
	call _doOp
	call _printResult
	call _writeNewLine
	call _exit
	pop %rbp
