#include <stdint.h>
#include <stdlib.h>
#include "atomic.h"
 
uintptr_t __stack_chk_guard;
 
void __stack_chk_fail(void)
{
	a_crash();
}
