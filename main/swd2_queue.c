#include "swd2_queue.h"

//static const char *TAG = "queue";

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
    if (que->num > 0) {
        *deq_data = que->data[que->head];
        que->head = (que->head + 1) % QUEUE_SIZE;
        que->num --;
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

void copyQueue(queue_t *que, data_t *copy_data, int copy_qty)
{
    //num<copy_qtyのときは、copy_qtyのnum<の部分をnull埋めして返す
    //copy_qty<numのときは、copy_qtyまでコピーして埋めて返す
    for (int i = 0; i < copy_qty; i++)
    {
        if (i < que->num) {
            copy_data[i] = que->data[que->head+i];
        } else {
            copy_data[i].tv_sec = 0;
            copy_data[i].tv_usec = 0;
        }
    }
    
}

void clearQueue(queue_t *que){
    que->num = que->head = 0;
}

void queuePrint_timeval(queue_t *que)
{
    int i;

    printf("[");
    for (i = 0; i < QUEUE_SIZE; i++) {
        if (que->num > 0 && ((que->head < (que->head + que->num) % QUEUE_SIZE) ^ (que->head <= i) ^ (i < (que->head + que->num) % QUEUE_SIZE))) {
            printf("%6ld", que->data[i].tv_sec);
        } else {
            printf("%6c", '.');
        }
    }
    printf("]\n");
    printf("[");
    for (i = 0; i < QUEUE_SIZE; i++) {
        if (que->num > 0 && ((que->head < (que->head + que->num) % QUEUE_SIZE) ^ (que->head <= i) ^ (i < (que->head + que->num) % QUEUE_SIZE))) {
            printf("%6ld", que->data[i].tv_usec);
        } else {
            printf("%6c", '.');
        }
    }
    printf("]\n");
}