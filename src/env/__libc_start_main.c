#include <elf.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include "syscall.h"
#include "atomic.h"
#include "libc.h"

extern uintptr_t __mmap_base;
extern void __init_ssp(void *p);
extern uintptr_t __arch_entropy();
extern uintptr_t __env_entropy(char **envp);

void __init_libc(char **envp, char *pn)
{
	size_t i;
	__environ = envp;
	for (i=0; envp[i]; i++);

	if (pn) {
		__progname = __progname_full = pn;
		for (i=0; pn[i]; i++) if (pn[i]=='/') __progname = pn+i+1;
	}

	struct pollfd pfd[3] = { {.fd=0}, {.fd=1}, {.fd=2} };
	__syscall(SYS_poll, pfd, 3, 0);
	for (i=0; i<3; i++) if (pfd[i].revents&POLLNVAL)
		if (__sys_open("/dev/null", O_RDWR)<0)
			a_crash();
	libc.secure = 1;
}

int __libc_start_main(int (*main)(int,char **,char **,char **), int argc, char **argv)
{
	char **envp = argv+argc+1;

	char **applep = envp;
	while (*applep != 0) applep++;
	applep++;

	uintptr_t entropy = __arch_entropy() ^ __env_entropy(envp);

	__mmap_base += entropy & 0xffff000;

	__init_ssp((void*)&entropy);
	__init_libc(envp, argv[0]);

	/* Pass control to the application */
	exit(main(argc, argv, envp, applep));
	return 0;
}
