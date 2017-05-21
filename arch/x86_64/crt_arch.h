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
	__asm__("1: rdrand %%rax; jnc 1b;\n" : "=a"(__stack_chk_guard));
}
