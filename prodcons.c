/* prodcons.c */
#include "prodcons.h"

/* 初始化缓冲区结构 */ 
void init(struct prodcons *b)
{
    pthread_mutex_init(&b->lock, NULL);
    pthread_cond_init(&b->notempty, NULL);
    pthread_cond_init(&b->notfull, NULL);
    b->readpos = 0;
    b->writepos = 0;
    b->size=0;
}

/* 将产品放入缓冲区*/ 
void put(struct prodcons *b, char *data)
{
    pthread_mutex_lock(&b->lock); /* 等待缓冲区未满*/ 
    while(b->size==BUFFER_SIZE){
        if ((b->writepos + 1) % BUFFER_SIZE == b->readpos)  {
            pthread_cond_wait(&b->notfull, &b->lock);//进入等待后会释放互斥，使其他线程进入互斥改变状态  
        } 
    }
    /* 写数据,并移动指针 */ 
    b->buffer[b->writepos] = data;
    b->writepos++; 
    if (b->writepos >= BUFFER_SIZE)
        b->writepos = 0;
    b->size++; /* 设置缓冲区非空的条件变量*/ 
    pthread_cond_signal(&b->notempty);
    pthread_mutex_unlock(&b->lock);
} 

/* 从缓冲区中取出数据*/ 
char *get(struct prodcons *b)
{ 
    char *data;
    pthread_mutex_lock(&b->lock); /* 等待缓冲区非空*/ 
    while(b->size==0)
        if (b->writepos == b->readpos)//此时缓冲区为空  
        {
            pthread_cond_wait(&b->notempty, &b->lock);
        } 
    /* 读数据,移动读指针*/ 
    data = b->buffer[b->readpos];
    b->readpos++; 
    if (b->readpos >= BUFFER_SIZE)
        b->readpos = 0;
    b->size--; /* 设置缓冲区未满的条件变量*/ 
    pthread_cond_signal(&b->notfull);
    pthread_mutex_unlock(&b->lock); 
    return data;
} 

/*  洗牌算法 */
void random(char a[], int n)  
{  
    int index, tmp, i;  
    srand(time(NULL));  
    for(i=0; i<n; i++)  
    {  
        index=rand()%(n-i)+i;     
        if(index!=i)  
        {  
            tmp=a[i];  
            a[i]=a[index];  
            a[index]=tmp;  
        }
    }
}