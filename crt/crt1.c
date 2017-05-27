#include <features.h>
#include <stdint.h>

#include "crt_arch.h"

int main();
_Noreturn int __libc_start_main(int (*)(), int, char **);
void __rebase_macho(void* mh, intptr_t slide);

void _start_c(long *p, uintptr_t image_base, uintptr_t slide)
{
	int argc = p[0];
	char **argv = (void *)(p+1);
	if (slide > 0) {
		__rebase_macho((void*)image_base, slide);
	}
	__libc_start_main(main, argc, argv);
}
