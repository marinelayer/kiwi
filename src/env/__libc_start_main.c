#include <elf.h>
#include <poll.h>
#include <fcntl.h>
#include <signal.h>
#include "syscall.h"
#include "atomic.h"
#include "libc.h"

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

int __libc_start_main(int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv+argc+1;

	__init_libc(envp, argv[0]);

	/* Pass control to the application */
	exit(main(argc, argv, envp));
	return 0;
}
