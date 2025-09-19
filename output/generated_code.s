//setup
.text
.global _main
.balign 4

//entry point and stack setup
_main:
	sub sp, sp, #16
	stp x29, x30, [sp, #0]
	add x29, sp, #0

	//Code Gen Starts Here: 

	//move value to register
	mov x0, #4
	//move value to register
	mov x1, #6
	//move value to register
	mov x2, #2
	//binary operation
	mul x3, x1, x2
	//binary operation
	add x1, x0, x3
	//move value to register
	mov x0, #8
	//move value to register
	mov x2, #3
	//binary operation
	sub x3, x0, x2
	//binary operation
	add x0, x1, x3
	//print
	mov x8, x0
	adr x0, integerformatstr
	mov x1, x8
	str x1, [sp]
	bl _printf

	//exit and clean up
	mov x0, #0
	ldp x29, x30, [sp, #16]
	add sp, sp, #16
	ret

//data
integerformatstr:
	.asciz "%d\n"

stringformatstr:
	.asciz "%s\n"