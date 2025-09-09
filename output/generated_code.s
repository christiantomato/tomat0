.text
.global _main
.balign 4

_main:
	sub sp, sp, #64
	stp x29, x30, [sp, #16]
	mov x29, sp

	adr x0, integerformatstr
	mov x1, #67
	str x1, [sp]
	bl _printf

	mov x0, #0
	ldp x29, x30, [sp, #16]
	add sp, sp, #64
	ret

integerformatstr:
	.asciz "%d\n"
stringformatstr:
	.asciz "%s\n"