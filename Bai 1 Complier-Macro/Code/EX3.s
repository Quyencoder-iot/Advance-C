	.file	"EX3.c"
	.text
	.globl	daoTrangThaiDen
	.def	daoTrangThaiDen;	.scl	2;	.type	32;	.endef
	.seh_proc	daoTrangThaiDen
daoTrangThaiDen:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	cmpl	$0, 32(%rbp)
	jne	.L2
	movl	24(%rbp), %eax
	movl	$1, %r8d
	movl	%eax, %edx
	movl	16(%rbp), %ecx
	call	HAL_GPIO_WritePin
	jmp	.L4
.L2:
	movl	24(%rbp), %eax
	movl	$0, %r8d
	movl	%eax, %edx
	movl	16(%rbp), %ecx
	call	HAL_GPIO_WritePin
.L4:
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	delay
	.def	delay;	.scl	2;	.type	32;	.endef
	.seh_proc	delay
delay:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	nop
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	call	__main
.L7:
	movl	$0, %r8d
	movl	$13, %edx
	movl	$0, %ecx
	call	daoTrangThaiDen
	movl	$1000, %ecx
	call	delay
	jmp	.L7
	.seh_endproc
	.ident	"GCC: (tdm64-1) 10.3.0"
	.def	HAL_GPIO_WritePin;	.scl	2;	.type	32;	.endef
