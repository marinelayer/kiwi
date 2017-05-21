#ifndef	_SYS_WAIT_H
#define	_SYS_WAIT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define __NEED_pid_t
#define __NEED_id_t
#include <bits/alltypes.h>

typedef enum {
	P_ALL = 0,
	P_PID = 1,
	P_PGID = 2
} idtype_t;

pid_t wait (int *);
pid_t waitpid (pid_t, int *, int );

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) \
 || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) \
 || defined(_BSD_SOURCE)
#include <signal.h>
int waitid (idtype_t, id_t, siginfo_t *, int);
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#include <sys/resource.h>
pid_t wait3 (int *, int, struct rusage *);
pid_t wait4 (pid_t, int *, int, struct rusage *);
#endif

#define WNOHANG		0x00000001
#define WUNTRACED	0x00000002
#define WEXITED         0x00000004
#define WSTOPPED        0x00000008
#define WCONTINUED      0x00000010
#define WNOWAIT         0x00000020
#define WCOREFLAG       0200


#define	_W_INT(i)	(i)
#define	_WSTATUS(x)	(_W_INT(x) & 0177)
#define	_WSTOPPED	0177		/* _WSTATUS if process is stopped */
#define WEXITSTATUS(x)	((_W_INT(x) >> 8) & 0x000000ff)
#define WSTOPSIG(x)	(_W_INT(x) >> 8)
#define WIFCONTINUED(x) (_WSTATUS(x) == _WSTOPPED && WSTOPSIG(x) == 0x13)
#define WIFSTOPPED(x)	(_WSTATUS(x) == _WSTOPPED && WSTOPSIG(x) != 0x13)
#define WIFEXITED(x)	(_WSTATUS(x) == 0)
#define WIFSIGNALED(x)	(_WSTATUS(x) != _WSTOPPED && _WSTATUS(x) != 0)
#define WTERMSIG(x)	(_WSTATUS(x))
#define WCOREDUMP(x)	(_W_INT(x) & WCOREFLAG)
#define	W_EXITCODE(ret, sig)	((ret) << 8 | (sig))
#define	W_STOPCODE(sig)		((sig) << 8 | _WSTOPPED)

#ifdef __cplusplus
}
#endif
#endif
