#include <signal.h>
#include "syscall.h"
#include "libc.h"

int __sigaction(int, const struct sigaction *, struct sigaction *);

void (*signal(int sig, void (*func)(int)))(int)
{
	struct sigaction sa_old, sa = { .sa_handler = func, .sa_flags = SA_RESTART };
	if (__sigaction(sig, &sa, &sa_old) < 0)
		return SIG_ERR;
	return sa_old.sa_handler;
}

