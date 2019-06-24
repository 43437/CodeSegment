#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include "err_handle.h"

struct msg
{
    struct msg* m_next;
    char buf[256];
};

struct msg* workq;

pthread_cond_t qready=PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock=PTHREAD_MUTEX_INITIALIZER;

void* process_msg(void* arg)
{
    struct msg* mp;
    for(;;)
    {
        pthread_mutex_lock(&qlock);
        while (workq==NULL)
        {
            pthread_cond_wait(&qready, &qlock);
        }
        mp=workq;
        workq=workq->m_next;
        pthread_mutex_unlock(&qlock);
        /*now process the message mp */
        mp->buf[255]=0;
        printf("get msg %s\n", mp->buf);
        free(mp);
    }
}

void enqueue_msg(struct msg* mp)
{
    pthread_mutex_lock(&qlock);
    mp->m_next=workq;
    workq=mp;
    pthread_mutex_unlock(&qlock);
    pthread_cond_signal(&qready);
}

int main(void)
{
    char buf[256];
    int err;
    pthread_t tid1;
    err=pthread_create(&tid1, NULL, process_msg, NULL);
    if (0!=err)
    {
        err_exit(err, "create thread failed.\n");
    }
    
    while (1)
    {
        gets(buf);
        struct msg* m=(struct msg*)malloc(sizeof(struct msg));
        strncpy(m->buf, buf, 256);
        enqueue_msg(m);
    }

    return 0;
}