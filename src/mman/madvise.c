#include <sys/mman.h>
#include "syscall.h"
#include "libc.h"

int madvise(void *addr, size_t len, int advice)
{
	return syscall(SYS_madvise, addr, len, advice);
}
