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
	mov x0, #1
	//move value to register
	mov x1, #69
	//move value to register
	mov x2, #420
	//move value to register
	mov x3, #21
	//move value to register
	mov x4, #19
	//binary operation
	mul x5, x3, x4
	//binary operation
	sub x3, x2, x5
	//binary operation
	mul x2, x1, x3
	//binary operation
	add x1, x0, x2
	//move value to register
	mov x0, #1000
	//move value to register
	mov x2, #250
	//binary operation
	sdiv x3, x0, x2
	//move value to register
	mov x0, #284
	//binary operation
	add x2, x3, x0
	//binary operation
	add x0, x1, x2
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