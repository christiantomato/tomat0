//setup
.text
.global _main
.balign 4

//entry point and stack setup
_main:
	sub sp, sp, #48
	stp x29, x30, [sp, #32]
	add x29, sp, #32

	//Code Gen Starts Here: 

	//move value to register
	mov x0, #100
	//store value to stack
	str x0, [x29, #-8]
	//move value to register
	mov x0, #60
	//store value to stack
	str x0, [x29, #-16]
	//move value to register
	mov x0, #40
	//store value to stack
	str x0, [x29, #-24]
	//load value from stack
	ldr x0, [x29, #-8]
	//load value from stack
	ldr x1, [x29, #-16]
	//binary operation
	mul x2, x0, x1
	//load value from stack
	ldr x0, [x29, #-8]
	//load value from stack
	ldr x1, [x29, #-24]
	//binary operation
	mul x3, x0, x1
	//binary operation
	sub x0, x2, x3
	//store value to stack
	str x0, [x29, #-32]
	//load value from stack
	ldr x0, [x29, #-32]
	//print
	mov x8, x0
	adr x0, integerformatstr
	mov x1, x8
	str x1, [sp]
	bl _printf

	//exit and clean up
	mov x0, #0
	ldp x29, x30, [sp, #32]
	add sp, sp, #48
	ret

//data
integerformatstr:
	.asciz "%d\n"

stringformatstr:
	.asciz "%s\n"