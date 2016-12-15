/* prodcons.h */
#ifndef __PRODCONS_H__
#define __PRODCONS_H__

#include <stdio.h>  
#include <pthread.h> 
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>  

#define BUFFER_SIZE 2048 // 缓冲区数量 

/* 把数据记录到pthread.log ，并添加当前时间 */
#define DBG(fmt, para...)    do \
    { \
        time_t t = time(NULL);  \
        struct tm *tmm = localtime(&t); \
        FILE *g_log_fp = fopen("pthread.log","a");  \
    	if (g_log_fp == NULL)  \
    		printf("open log file error\n");  \
    	else { \
    		fprintf(g_log_fp, "[%d-%02d-%02d %02d:%02d:%02d]" fmt "\n",tmm->tm_year+1900,tmm->tm_mon+1,tmm->tm_mday,tmm->tm_hour,tmm->tm_min,tmm->tm_sec,##para); \
    		fclose(g_log_fp); \
    	} \
    } while(0)  

// 缓冲区相关数据结构 
struct prodcons
{
    char *buffer[BUFFER_SIZE]; /* 实际数据存放的数据*/ 
    pthread_mutex_t lock; /* 互斥体lock 用于对缓冲区的互斥操作 */ 
    int readpos, writepos; /* 读写指针*/ 
    pthread_cond_t notempty; /* 缓冲区非空的条件变量 */ 
    pthread_cond_t notfull; /* 缓冲区未满的条件变量 */ 
    int size;/*缓冲区当前大小*/ 
};

/* 初始化缓冲区结构 */ 
void init(struct prodcons *b);

/* 将产品放入缓冲区*/ 
void put(struct prodcons *b, char *data);

/* 从缓冲区中取出数据*/ 
char *get(struct prodcons *b);

/*  洗牌算法 */
void random(char a[], int n);

#endif