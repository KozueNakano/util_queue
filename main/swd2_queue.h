#ifndef SWD2_QUEUE_H
#define SWD2_QUEUE_H

#include <stdio.h>
//#include "esp_log.h"

#define QUEUE_SIZE 10       /* 最大データ数 */
#define SUCCESS     1       /* 成功 */
#define FAILURE     0       /* 失敗 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct timeval data_t;/* データ型 */
typedef struct {
    int head;
    int num;
    data_t data[QUEUE_SIZE];
} queue_t;

int enqueue(queue_t *que, data_t enq_data);
int dequeue(queue_t *que, data_t *deq_data);
void queuePrint_timeval(queue_t *que);
void copyQueue(queue_t *que, data_t *copy_data, int copy_qty);
void clearQueue(queue_t *que);

#ifdef __cplusplus
}
#endif

#endif // SWD2_QUEUE_H