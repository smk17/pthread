/* main.c */
#include "prodcons.h"

struct prodcons buffer; 

/**
 *生产者1
 *每隔2s生产一个消息，数据为26个大写字母
**/
void *producer_1(void *data)
{
    char d[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (1)
    {
        random(d, 26); 
        DBG("P1:%s", d);
        put(&buffer, d);
        sleep(2);
    }
    return NULL;
} 

/**
 *生产者2
 *每隔2s生产一个消息，数据为26个小写字母
**/
void *producer_2(void *data)
{
    char d[26] = "abcdefghijklmnopqrstuvwxyz";
    while (1)
    {
        random(d, 26);
        DBG("P2:%s", d);
        put(&buffer, d);
        sleep(2);
    }
    return NULL;
} 

/**
 *生产者3
 *每隔2s生产一个消息，数据为10个阿拉伯数字
**/
void *producer_3(void *data)
{
    char d[10] = "1234567890";
    while (1)
    {
        random(d, 10);
        DBG("P3:%s", d);
        put(&buffer, d);
        sleep(2);
    }
    return NULL;
} 

/**
 *消费者1
 *每隔3s读取一个消息并显示
**/
void *consumer(void *data)
{ 
    char *d; 
    while (1)
    {
        d = get(&buffer);
        printf("C1:%s \n", d);
        sleep(3);
    } 
    return NULL;
} 

/**
 *如已存在pthread.log文件则清空，反之创建之
**/
void clear_log(){
    FILE *fp = fopen("pthread.log","w+");
    if (fp == NULL)
        printf("open log file error\n"); 
    else {
        fclose(fp);
    }
}

int main(void)
{
    pthread_t th_P1, th_P2, th_P3, th_C1; 
    void *retval;
    clear_log();
    init(&buffer); 
    /* 创建生产者和消费者线程*/ 
    pthread_create(&th_P1, NULL, producer_1, 0);
    pthread_create(&th_P2, NULL, producer_2, 0);
    pthread_create(&th_P3, NULL, producer_3, 0);
    pthread_create(&th_C1, NULL, consumer, 0); 
    /* 等待两个线程结束*/ 
    pthread_join(th_P1, &retval);
    pthread_join(th_P2, &retval);
    pthread_join(th_P3, &retval);
    pthread_join(th_C1, &retval); 
    
    return 0;
}