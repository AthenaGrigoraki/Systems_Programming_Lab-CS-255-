# -----------------------------------
# Program x86asm.s
# Compute and print the sum 0+...+N
# -----------------------------------

.code32

	.section .data	# data memory
N:	.long 1000	    # N is a long number with the value 1000
S:	.long 0		    # S is a long numer with the value 0
Msg:	.ascii "The sum from 0 to %d is %d\n\0"


	.section .text	# program memory
.globl main
main:	
	pushl %ebp	    # stores ebp in the stack
	movl %esp, %ebp	# ebp=esp

 	# initialize
    movl N, %ebx	# copies long number N to ebx

 	# compute sum
L1:
	addl %ebx, S	# S+= ebx value
	decl %ebx       # ebx-=1 , decrease by one
	cmpl $0, %ebx   # compares if data in ebx>0 and stores result in internal register
	jng  L2	    	# if ebx<=0 jumps to L2
    movl $L1, %eax	# eax=address of L1
    jmp *%eax   	# jump to address pointed by eax

L2:
	# print result
	pushl S	    	# store S into stack
	pushl N	        # store N into stack
	pushl $Msg  	# store Msg string into stack
	call printf 	# syscall printf
	popl %eax   	# return the Msg from the stack
	popl %eax   	# return N from the stack
	popl %eax   	# return S from the stack

	# exit
	movl $0, %eax  	# set value of eax to zero
    leave	    	#
 	ret             # return 