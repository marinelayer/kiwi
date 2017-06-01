#include <stdlib.h>

void *memalign(size_t, size_t);

void *aligned_alloc(size_t align, size_t len)
{
	return memalign(align, len);
}
