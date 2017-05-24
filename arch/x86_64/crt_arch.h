__asm__(
".text \n"
".global start \n"
"start: \n"
"	xor %rbp,%rbp \n"
"	mov %rsp,%rdi \n"
"	andq $-16,%rsp \n"
"	call __start_c \n"
);

extern uintptr_t __stack_chk_guard;

__attribute__ ((always_inline)) static void __setup_stack_guard()
{
	__asm__(
		"	movl    $1, %%eax \n"   /* cpuid leaf 1 */
		"	cpuid   \n"
		"	btl     $30, %%ecx \n"  /* ecx.bit[30] rdrand? */
		"	jc      1f \n"
		"	movabsq $0x1234567890abcdef, %%rax \n" /* pwned. */
		"	jmp     2f \n"
		"1:	rdrand  %%rax \n"
		"	jnc     1b;\n"
		"2:"
	  : "=a"(__stack_chk_guard)
	  :
	  : "rbx", "rcx", "rdx"
	);
}
