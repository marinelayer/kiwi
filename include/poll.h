#ifndef	_POLL_H
#define	_POLL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define POLLIN          0x0001
#define POLLPRI         0x0002
#define POLLOUT         0x0004
#define POLLRDNORM      0x0040
#define POLLWRNORM      POLLOUT
#define POLLRDBAND      0x0080
#define POLLWRBAND      0x0100
#define POLLEXTEND      0x0200
#define POLLATTRIB      0x0400
#define POLLNLINK       0x0800
#define POLLWRITE       0x1000
#define POLLERR         0x0008
#define POLLHUP         0x0010
#define POLLNVAL        0x0020

typedef unsigned int nfds_t;

struct pollfd
{
	int fd;
	short events;
	short revents;
};

int poll (struct pollfd *, nfds_t, int);

#ifdef _GNU_SOURCE
#define __NEED_time_t
#define __NEED_struct_timespec
#define __NEED_sigset_t
#include <bits/alltypes.h>
int ppoll(struct pollfd *, nfds_t, const struct timespec *, const sigset_t *);
#endif

#ifdef __cplusplus
}
#endif

#endif
