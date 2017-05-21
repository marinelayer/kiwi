#include <signal.h>
#include <errno.h>
#include <string.h>
#include "syscall.h"
#include "libc.h"

#define UC_TRAD                 1
#define UC_FLAVOR               30

static void __sigtramp(
        union __sigaction_u   __sigaction_u,
        int                     sigstyle,
        int                     sig,
        siginfo_t               *sinfo,
        ucontext_t              *uctx)
{
	int ctxstyle = UC_FLAVOR;
	if (sigstyle == UC_TRAD) sa_handler(sig);
	else sa_sigaction(sig, sinfo, uctx);
	syscall(SYS_sigreturn, uctx, ctxstyle);
}

int sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old)
{
	((struct sigaction *)sa)->sa_tramp = &__sigtramp;
	return syscall(SYS_sigaction, sig, sa, old);
}
