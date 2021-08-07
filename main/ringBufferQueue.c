/* 
http://www.cc.kyoto-su.ac.jp/~yamada/ap/queue.html
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define QUEUE_SIZE 10       /* 最大データ数 */
#define SUCCESS     1       /* 成功 */
#define FAILURE     0       /* 失敗 */

typedef int data_t;         /* データ型 */

typedef struct {
    int head;
    int num;
    data_t data[QUEUE_SIZE];
} queue_t;

int enqueue(queue_t *que, data_t enq_data)
{
    if (que->num < QUEUE_SIZE) {
        que->data[(que->head + que->num) % QUEUE_SIZE] = enq_data;
        que->num ++;
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

int dequeue(queue_t *que, data_t *deq_data)
{
    data_t d;
    if (que->num > 0) {
        *deq_data = que->data[que->head];
        que->head = (que->head + 1) % QUEUE_SIZE;
        que->num --;
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

void queuePrint(queue_t *que)
{
    int i;

    printf("queue [");
    for (i = 0; i < QUEUE_SIZE; i++) {
        if (que->num > 0 && ((que->head < (que->head + que->num) % QUEUE_SIZE) ^ (que->head <= i) ^ (i < (que->head + que->num) % QUEUE_SIZE))) {
            printf("%3d", que->data[i]);
        } else {
            printf("%3c", '.');
        }
    }
    printf("]\n");
}

void app_main(void)
{

        int i;
    data_t d;
    queue_t que;

    que.num = que.head = 0;
    for (i = 1; i <= 7; i++) {
        printf("Enqueue%3d :", i);
        if (enqueue(&que, i)) queuePrint(&que);
        else printf("Full queue\n");
    }
    for (i = 1; i <= 4; i++) {
        dequeue(&que, &d);
        printf("Dequeue%3d :", d);
        queuePrint(&que);
    }
    for (i = 8; i <= 15; i++) {
        printf("Enqueue%3d :", i);
        if (enqueue(&que, i)) queuePrint(&que);
        else printf("Full queue\n");
    }
    while(que.num > 0) {
        dequeue(&que, &d);
        printf("Dequeue%3d :", d);
        queuePrint(&que);
    }

    while (true)
    {
        printf("Hello world!\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
