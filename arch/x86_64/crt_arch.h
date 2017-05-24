__asm__(
".text \n"
".global start \n"
"start: \n"
"	xor %rbp,%rbp \n"
"	mov %rsp,%rdi \n"
"	andq $-16,%rsp \n"
"	call __start_c \n"
);
