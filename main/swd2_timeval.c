/*thanks
https://mcommit.hatenadiary.com/entry/2017/09/23/222902
*/
#include "swd2_timeval.h"

void add_timeval_us(struct timeval *time , uint64_t add_us){
    uint64_t micro = 1000000;
    uint64_t add_tv_sec = add_us/micro;
    uint64_t add_tv_usec = add_us % micro;

    time->tv_sec += add_tv_sec;
    time->tv_usec += add_tv_usec;
}