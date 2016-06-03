	.file	"bits.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"showing bytes read:\nHEX    DEC    BIN"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"\n--------------------------"
.LC2:
	.string	"\n$%02X    %3d    "
.LC3:
	.string	"%d"
	.text
	.p2align 4,,15
	.globl	print_bytes
	.type	print_bytes, @function
print_bytes:
.LFB8:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	xorl	%eax, %eax
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %r12
	movq	%rsi, %rbx
	movl	$.LC0, %edi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	leaq	(%r12,%rbx), %r13
	call	printf
	testq	%rbx, %rbx
	je	.L6
	.p2align 4,,10
	.p2align 3
.L7:
	movzbl	(%r12), %esi
	movl	$.LC2, %edi
	xorl	%eax, %eax
	movl	$7, %ebx
	movl	%esi, %edx
	call	printf
	movzbl	(%r12), %ebp
.L3:
	movl	%ebx, %ecx
	movl	%ebp, %esi
	xorl	%eax, %eax
	sarl	%cl, %esi
	movl	$.LC3, %edi
	subq	$1, %rbx
	andl	$1, %esi
	call	printf
	cmpq	$3, %rbx
	jne	.L3
	movl	$32, %edi
	call	putchar
	.p2align 4,,10
	.p2align 3
.L4:
	movl	%ebx, %ecx
	movl	%ebp, %esi
	xorl	%eax, %eax
	sarl	%cl, %esi
	movl	$.LC3, %edi
	subq	$1, %rbx
	andl	$1, %esi
	call	printf
	cmpq	$-1, %rbx
	jne	.L4
	addq	$1, %r12
	cmpq	%r12, %r13
	jne	.L7
.L6:
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movl	$.LC1, %edi
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	puts
	.cfi_endproc
.LFE8:
	.size	print_bytes, .-print_bytes
	.p2align 4,,15
	.globl	print_bits
	.type	print_bits, @function
print_bits:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movzbl	%dil, %ebp
	movl	$7, %ebx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
.L14:
	movl	%ebx, %ecx
	movl	%ebp, %esi
	xorl	%eax, %eax
	sarl	%cl, %esi
	movl	$.LC3, %edi
	subq	$1, %rbx
	andl	$1, %esi
	call	printf
	cmpq	$3, %rbx
	jne	.L14
	movl	$32, %edi
	call	putchar
	.p2align 4,,10
	.p2align 3
.L15:
	movl	%ebx, %ecx
	movl	%ebp, %esi
	xorl	%eax, %eax
	sarl	%cl, %esi
	movl	$.LC3, %edi
	subq	$1, %rbx
	andl	$1, %esi
	call	printf
	cmpq	$-1, %rbx
	jne	.L15
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE9:
	.size	print_bits, .-print_bits
	.section	.rodata.str1.1
.LC4:
	.string	"rb"
.LC5:
	.string	"ROM"
.LC6:
	.string	"Could not open 'ROM'"
.LC7:
	.string	"ROM size: %lu\n"
.LC8:
	.string	"Failed to allocate memory"
.LC9:
	.string	"error while reading ROM"
.LC10:
	.string	"ORed:  "
.LC11:
	.string	"\nXORed: "
.LC12:
	.string	"\nANDed: "
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	movl	$.LC4, %esi
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	movl	$.LC5, %edi
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	call	fopen
	testq	%rax, %rax
	je	.L33
	xorl	%esi, %esi
	movq	%rax, %r12
	movl	$2, %edx
	movq	%rax, %rdi
	call	fseek
	movq	%r12, %rdi
	call	ftell
	xorl	%edx, %edx
	movq	%rax, %rbx
	xorl	%esi, %esi
	movq	%r12, %rdi
	call	fseek
	movq	%rbx, %rsi
	movl	$.LC7, %edi
	xorl	%eax, %eax
	call	printf
	movq	%rbx, %rdi
	call	malloc
	testq	%rax, %rax
	movq	%rax, %r13
	je	.L34
	movq	%r12, %rcx
	movl	$1, %edx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	fread
	cmpq	%rax, %rbx
	ja	.L35
.L24:
	movq	%rbx, %rsi
	movq	%r13, %rdi
	xorl	%ebp, %ebp
	call	print_bytes
	leaq	-1(%rbx), %rcx
	xorl	%r14d, %r14d
	xorl	%eax, %eax
	xorl	%edx, %edx
	.p2align 4,,10
	.p2align 3
.L30:
	cmpq	%rbx, %rdx
	jnb	.L25
	orb	0(%r13,%rdx), %r14b
	addq	$1, %rdx
.L25:
	cmpq	%rcx, %rax
	jnb	.L26
	xorb	0(%r13,%rax), %bpl
	xorb	1(%r13,%rax), %bpl
	addq	$1, %rax
.L26:
	cmpq	%rbx, %rdx
	jb	.L30
	cmpq	%rcx, %rax
	jb	.L30
	movl	$.LC10, %edi
	xorl	%eax, %eax
	call	printf
	movzbl	%r14b, %edi
	call	print_bits
	movl	$.LC11, %edi
	xorl	%eax, %eax
	call	printf
	movzbl	%bpl, %edi
	call	print_bits
	movl	$.LC12, %edi
	xorl	%eax, %eax
	call	printf
	xorl	%edi, %edi
	call	print_bits
	movl	$10, %edi
	call	putchar
	movq	%r12, %rdi
	call	fclose
	movq	%r13, %rdi
	call	free
	xorl	%eax, %eax
.L19:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
.L35:
	.cfi_restore_state
	movq	%r12, %rdi
	call	ferror
	testl	%eax, %eax
	je	.L24
	movl	$.LC9, %edi
	call	perror
.L23:
	movq	%r12, %rdi
	call	fclose
	movq	%r13, %rdi
	call	free
	movl	$1, %eax
	jmp	.L19
.L34:
	movl	$.LC8, %edi
	call	perror
	jmp	.L23
.L33:
	movl	$.LC6, %edi
	call	perror
	movl	$1, %eax
	jmp	.L19
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.ident	"GCC: (GNU) 6.1.1 20160501"
	.section	.note.GNU-stack,"",@progbits
