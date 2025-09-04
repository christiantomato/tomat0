.text
.global _main
.align 2

_main:
	mov w0, #10
	bl _printf
	mov w0, #0
	ret
