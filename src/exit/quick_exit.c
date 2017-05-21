#include <stdlib.h>
#include "libc.h"

extern void __funcs_on_quick_exit(void);

_Noreturn void quick_exit(int code)
{
	__funcs_on_quick_exit();
	_Exit(code);
}
