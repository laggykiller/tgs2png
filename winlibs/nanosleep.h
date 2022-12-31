#ifndef _NANOSLEEP_H
#define _NANOSLEEP_H

#include <time.h>

#if !defined(nanosleep)
int nanosleep(const struct timespec* requested_delay, struct timespec* remaining_delay);
#endif /* !defined(nanosleep) */


#endif /* _NANOSLEEP_H */