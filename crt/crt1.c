#include <features.h>
#include <stdint.h>

#include "crt_arch.h"

int main();
_Noreturn int __libc_start_main(int (*)(), int, char **);

void _start_c(long *p)
{
	int argc = p[0];
	char **argv = (void *)(p+1);
	__setup_stack_guard();
	__libc_start_main(main, argc, argv);
}
