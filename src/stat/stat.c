#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "syscall.h"
#include "libc.h"

int stat(const char *restrict path, struct stat *restrict buf)
{
	return syscall(SYS_stat64, path, buf);
}
