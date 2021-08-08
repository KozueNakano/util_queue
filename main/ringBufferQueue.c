/* 
http://www.cc.kyoto-su.ac.jp/~yamada/ap/queue.html
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include <stdbool.h>
#include <sys/time.h>
#include "swd2_queue.h"
#include "swd2_timeval.h"
static const char *TAG = "fastATTR";
//https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/memory-types.html#rtc-fast-memory
//RTC_FAST_ATTRにはPRO CPU (core0)からのみアクセスできる。
//https://www.esp32.com/viewtopic.php?t=18220
//app_mainはcore0で実行される。
RTC_FAST_ATTR static bool directionFlag =  true;
data_t d;
RTC_FAST_ATTR queue_t que;

void app_main(void)
{

    //resetInit---------------------------------------------------------
    //リセット要因に応じて初期化操作を行う。deepsleepと電源ON(書き込み)を区別する。
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    if (cause == ESP_SLEEP_WAKEUP_UNDEFINED) {
        ESP_LOGI(TAG, "Not sleep wakeup");
        //que.num = que.head = 0;
        clearQueue(&que);
    }else{
        ESP_LOGI(TAG, "sleep wakeup");
    }
    //---------------------------------------------------------resetInit
    data_t _time;
    gettimeofday(&_time, NULL);
    //UNIX時間の1970年1月1日からの経過秒数
    long sec = _time.tv_sec;
    //マイクロ秒　0から999999までの値を取り、一杯になると秒がカウントアップされていく
    long usec = _time.tv_usec;
    printf("nowTime : %ld %ld\n",sec,usec);
    if (directionFlag == true)
    {
            //printf("Enqueue%3d :", _time);
            if (enqueue(&que, _time)){
                queuePrint_timeval(&que);
            } else {
                printf("Full queue\n");
                directionFlag = false;
            }
    }else{
        if (que.num > 0)
        {
            dequeue(&que, &d);
            //printf("Dequeue%d :", d);
            queuePrint_timeval(&que);
        }else{
            printf("empty queue\n");
            directionFlag = true;
        }
    }

    int copy_qty = que.num;
    data_t copy_data[copy_qty];
    copyQueue(&que, copy_data, copy_qty);
    printf("copy_data\n");
    printf("[");
    for (int i = 0; i < copy_qty; i++)
    {
        printf("%6ld", copy_data[i].tv_sec);
    }
    printf("]\n");
    printf("[");
    for (int i = 0; i < copy_qty; i++)
    {
        printf("%6ld,", copy_data[i].tv_usec);
    }
    printf("]\n");
    //add
    for (int i = 0; i < copy_qty; i++)
    {
        add_timeval_us(&copy_data[i],2000001);
    }
    printf("added_data\n");
    printf("[");
    for (int i = 0; i < copy_qty; i++)
    {
        printf("%6ld", copy_data[i].tv_sec);
    }
    printf("]\n");
    printf("[");
    for (int i = 0; i < copy_qty; i++)
    {
        printf("%6ld,", copy_data[i].tv_usec);
    }
    printf("]\n");

    
    

    printf("queueNum : %d\n",que.num);
    printf("queueHead : %d\n",que.head);

    ESP_LOGI(TAG, "Entering deep sleep");
    const int deep_sleep_sec = 1;
    esp_deep_sleep(1000000LL * deep_sleep_sec);
    esp_deep_sleep_start();
}
