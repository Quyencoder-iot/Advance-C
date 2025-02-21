	.file	"EX1.c"
	.text
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	leaq	48(%rsp), %rbp
	.seh_setframe	%rbp, 48
	.seh_endprologue
	movq	%rcx, 32(%rbp)
	movq	%rdx, 40(%rbp)
	movq	%r8, 48(%rbp)
	movq	%r9, 56(%rbp)
	leaq	40(%rbp), %rax
	movq	%rax, -16(%rbp)
	movq	-16(%rbp), %rbx
	movl	$1, %ecx
	movq	__imp___acrt_iob_func(%rip), %rax
	call	*%rax
	movq	%rbx, %r8
	movq	32(%rbp), %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "Trinh, \0"
.LC1:
	.ascii " sdt:09xxx\12\0"
	.text
	.globl	sv1
	.def	sv1;	.scl	2;	.type	32;	.endef
	.seh_proc	sv1
sv1:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC0(%rip), %rcx
	call	printf
	leaq	.LC1(%rip), %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC2:
	.ascii "Duc, \0"
.LC3:
	.ascii "08xxx\12\0"
	.text
	.globl	sv2
	.def	sv2;	.scl	2;	.type	32;	.endef
	.seh_proc	sv2
sv2:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC2(%rip), %rcx
	call	printf
	leaq	.LC3(%rip), %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC4:
	.ascii "Nam, \0"
.LC5:
	.ascii "06xxx\12\0"
	.text
	.globl	sv3
	.def	sv3;	.scl	2;	.type	32;	.endef
	.seh_proc	sv3
sv3:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leaq	.LC4(%rip), %rcx
	call	printf
	leaq	.LC5(%rip), %rcx
	call	printf
	nop
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC6:
	.ascii "value %d\12\0"
.LC7:
	.ascii "hello world\0"
.LC8:
	.ascii "\12 tong la %d\12\0"
.LC9:
	.ascii "data la: %d\12\0"
.LC10:
	.ascii "data moi la: %d\12\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$80, %rsp
	.seh_stackalloc	80
	.seh_endprologue
	call	__main
	call	sv1
	call	sv2
	call	sv3
	movl	$369, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC6(%rip), %rcx
	call	printf
	leaq	.LC7(%rip), %rcx
	call	printf
	movl	$1, -48(%rbp)
	movl	$2, -44(%rbp)
	movl	$3, -40(%rbp)
	movl	$4, -36(%rbp)
	movl	$6, -32(%rbp)
	movl	$9, -28(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L7
.L8:
	movl	-8(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	addl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L7:
	movl	-8(%rbp), %eax
	cltq
	movl	-48(%rbp,%rax,4), %eax
	testl	%eax, %eax
	jne	.L8
	movl	-4(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC8(%rip), %rcx
	call	printf
	movl	$30, %edx
	leaq	.LC9(%rip), %rcx
	call	printf
	movl	$60, %edx
	leaq	.LC10(%rip), %rcx
	call	printf
	movl	$0, %eax
	addq	$80, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (tdm64-1) 10.3.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
