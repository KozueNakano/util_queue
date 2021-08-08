#ifndef SWD2_TIMEVAL_H
#define SWD2_TIMEVAL_H

#include <stdio.h>
//#include "esp_log.h"
#include <sys/time.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
void add_timeval_us(struct timeval *time , uint64_t add_us);

#ifdef __cplusplus
}
#endif

#endif // SWD2_TIMEVAL_H