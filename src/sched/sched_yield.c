#include <sched.h>
#include "syscall.h"

int sched_yield()
{
	return mach_syscall(MACH_swtch_pri, 0);
}
