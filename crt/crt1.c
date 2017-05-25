#include <features.h>
#include <stdint.h>

#include "crt_arch.h"

#define MH_MAGIC_64 0xfeedfacf

int main();
_Noreturn int __libc_start_main(int (*)(), int, char **);

void __rebase_macho(void* mh, intptr_t slide);

void _start_c(long *p, int *start, uintptr_t slide)
{
	int argc = p[0];
	char **argv = (void *)(p+1);
	while (*start != MH_MAGIC_64) start--;
	if (slide > 0) {
		__rebase_macho((void*)start, slide);
	}
	__libc_start_main(main, argc, argv);
}
