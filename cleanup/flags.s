	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%rbx
	subq	$72, %rsp
	.cfi_offset %rbx, -24
	xorl	%eax, %eax
	movb	$1, -10(%rbp)
	movb	-10(%rbp), %cl
	xchgb	%cl, _flag(%rip)
	movb	%cl, -11(%rbp)
	movb	-11(%rbp), %cl
	andb	$1, %cl
	movb	%cl, -9(%rbp)
	movq	_i@GOTPCREL(%rip), %rdx
	movl	(%rdx), %esi
	movq	_j@GOTPCREL(%rip), %rdi
	movl	%esi, (%rdi)
	movl	(%rdx), %esi
	addl	$3, %esi
	movl	%esi, (%rdx)
	movl	(%rdi), %esi
	movl	(%rdx), %r8d
	movq	_ai@GOTPCREL(%rip), %r9
	movl	(%r9), %ecx
	leaq	L_.str(%rip), %r10
	xorl	%r11d, %r11d
	movb	%r11b, %bl
	movq	%rdi, -24(%rbp)         ## 8-byte Spill
	movq	%r10, %rdi
	movq	%rdx, -32(%rbp)         ## 8-byte Spill
	movl	%r8d, %edx
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movb	%bl, %al
	movq	%r10, -48(%rbp)         ## 8-byte Spill
	movq	%r9, -56(%rbp)          ## 8-byte Spill
	movb	%bl, -57(%rbp)          ## 1-byte Spill
	callq	_printf
	movq	-56(%rbp), %rdi         ## 8-byte Reload
	movl	(%rdi), %ecx
	movq	-24(%rbp), %r9          ## 8-byte Reload
	movl	%ecx, (%r9)
	lock		addl	$3, (%rdi)
	movl	(%r9), %esi
	movq	-32(%rbp), %r10         ## 8-byte Reload
	movl	(%r10), %edx
	movl	(%rdi), %ecx
	movq	-48(%rbp), %rdi         ## 8-byte Reload
	movb	-57(%rbp), %bl          ## 1-byte Reload
	movl	%eax, -64(%rbp)         ## 4-byte Spill
	movb	%bl, %al
	callq	_printf
	movb	$0, -12(%rbp)
	movb	-12(%rbp), %bl
	xchgb	%bl, _flag(%rip)
	movl	-36(%rbp), %ecx         ## 4-byte Reload
	movl	%eax, -68(%rbp)         ## 4-byte Spill
	movl	%ecx, %eax
	movb	%bl, -69(%rbp)          ## 1-byte Spill
	addq	$72, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_flag                   ## @flag
.zerofill __DATA,__common,_flag,1,0
	.comm	_i,4,2                  ## @i
	.comm	_j,4,2                  ## @j
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d %d %d\n"

	.comm	_ai,4,2                 ## @ai

.subsections_via_symbolut


























s
