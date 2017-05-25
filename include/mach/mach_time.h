#ifndef	_MACH_TIME_H
#define	_MACH_TIME_H

#include <stdint.h>

struct mach_timebase_info {
	uint32_t numer;
	uint32_t denom;
};

typedef struct mach_timebase_info mach_timebase_info_data_t;

uint64_t mach_absolute_time(void);
int mach_timebase_info(struct mach_timebase_info *info);

#endif
