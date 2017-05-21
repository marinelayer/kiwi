#ifndef	_SYS_MMAN_H
#define	_SYS_MMAN_H
#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define __NEED_mode_t
#define __NEED_size_t
#define __NEED_off_t

#if defined(_GNU_SOURCE)
#define __NEED_ssize_t
#endif

#include <bits/alltypes.h>

#define MAP_FAILED ((void *) -1)

#define MAP_FILE         0x0000
#define	MAP_SHARED       0x0001
#define	MAP_PRIVATE      0x0002
#define	MAP_COPY         MAP_PRIVATE
#define	MAP_FIXED        0x0010
#define	MAP_RENAME       0x0020
#define	MAP_NORESERVE	 0x0040
#define	MAP_RESERVED0080 0x0080
#define	MAP_NOEXTEND     0x0100
#define	MAP_HASSEMAPHORE 0x0200
#define MAP_NOCACHE      0x0400
#define MAP_JIT	         0x0800
#define	MAP_FILE         0x0000
#define	MAP_ANON         0x1000
#define	MAP_ANONYMOUS    MAP_ANON

#define PROT_NONE        0
#define PROT_READ        1
#define PROT_WRITE       2
#define PROT_EXEC        4

#define MS_ASYNC         1
#define MS_INVALIDATE    2
#define MS_SYNC          4

#define MCL_CURRENT      1
#define MCL_FUTURE       2
#define MCL_ONFAULT      4

#define POSIX_MADV_NORMAL     0
#define POSIX_MADV_RANDOM     1
#define POSIX_MADV_SEQUENTIAL 2
#define POSIX_MADV_WILLNEED   3
#define POSIX_MADV_DONTNEED   4

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#define	MADV_NORMAL		POSIX_MADV_NORMAL
#define	MADV_RANDOM		POSIX_MADV_RANDOM
#define	MADV_SEQUENTIAL		POSIX_MADV_SEQUENTIAL
#define	MADV_WILLNEED		POSIX_MADV_WILLNEED
#define	MADV_DONTNEED		POSIX_MADV_DONTNEED
#define	MADV_FREE		5
#define	MADV_ZERO_WIRED_PAGES	6
#define MADV_FREE_REUSABLE	7
#define MADV_FREE_REUSE		8
#define MADV_CAN_REUSE		9
#define MADV_PAGEOUT		10
#endif

void *mmap (void *, size_t, int, int, int, off_t);
int munmap (void *, size_t);

int mprotect (void *, size_t, int);
int msync (void *, size_t, int);

int posix_madvise (void *, size_t, int);

int mlock (const void *, size_t);
int munlock (const void *, size_t);
int mlockall (int);
int munlockall (void);

#ifdef _GNU_SOURCE
#define MREMAP_MAYMOVE 1
#define MREMAP_FIXED 2
void *mremap (void *, size_t, size_t, int, ...);
int remap_file_pages (void *, size_t, int, size_t, int);
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#define MLOCK_ONFAULT   0x01
int madvise (void *, size_t, int);
int mincore (void *, size_t, unsigned char *);
#endif

int shm_open (const char *, int, mode_t);
int shm_unlink (const char *);

#if defined(_LARGEFILE64_SOURCE) || defined(_GNU_SOURCE)
#define mmap64 mmap
#define off64_t off_t
#endif

#ifdef __cplusplus
}
#endif
#endif
