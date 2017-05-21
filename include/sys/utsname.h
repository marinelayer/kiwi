#ifndef	_SYS_UTSNAME_H
#define	_SYS_UTSNAME_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#define _SYS_NAMELEN    256

struct  utsname {
        char    sysname[_SYS_NAMELEN];
        char    nodename[_SYS_NAMELEN];
        char    release[_SYS_NAMELEN];
        char    version[_SYS_NAMELEN];
        char    machine[_SYS_NAMELEN];
};

int uname (struct utsname *);

#ifdef __cplusplus
}
#endif

#endif
