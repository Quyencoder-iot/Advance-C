	.file	"BSS.c"
	.text
	.globl	p1  //p1  bien toan cu
	.data       // p1 phan vung data
	.align 8
p1:
	.long	5
	.long	0
	.globl	p2  // p2 bien toan cuc
	.bss         // p2 o phan vung bss
	.align 8
p2:
	.space 8
	.globl	p3
	.align 8
p3:
	.space 8
	.globl	a
	.align 4
a:
	.space 4
	.globl	b
	.align 4
b:
	.space 4
	.globl	ptr
	.align 8
ptr:
	.space 8
	.globl	str
	.section .rdata,"dr"
.LC0:
	.ascii "hello world\0"
	.data
	.align 8
str:
	.quad	.LC0
.lcomm global,4,4
.lcomm global_2,4,4
.lcomm p4,8,8
	.globl	e
	.section .rdata,"dr"
	.align 4
e:
	.space 4
	.text
	.globl	test
	.def	test;	.scl	2;	.type	32;	.endef
	.seh_proc	test
test:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	$10, -4(%rbp)
	nop
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC1:
	.ascii "a: %d\12\0"
.LC2:
	.ascii "global: %d\12\0"
.LC3:
	.ascii "chuoi: %s\12\0"
	.text
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
	movl	a(%rip), %eax
	movl	%eax, %edx
	leaq	.LC1(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	global(%rip), %eax
	movl	%eax, %edx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movq	str(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	printf
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
.lcomm local_2.1,4,4
.lcomm local.0,4,4
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
