#include <stdio.h>
#include <pthread.h>
#include "err_handle.h"

struct foo
{
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
};

struct foo* foo_alloc(int id)
{
    struct foo* fp;
    if ((fp=malloc(sizeof(struct foo)))!=NULL)
    {
        fp->f_count=0;
        fp->f_id=id;
        if (pthread_mutex_init(&fp->f_lock, NULL)!=0)
        {
            free(fp);
            return NULL;
        }
        /**continue initialization */
    }
    return fp;
}

void foo_hold(struct foo* fp)   /*add a reference to the object */
{
    pthread_mutex_lock(&fp->f_lock);
    ++fp->f_count;
    pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo* fp) /*release a reference to the object */
{
    pthread_mutex_lock(&fp->f_lock);
    fp->f_count--;
    if (0==fp->f_count)
    {        
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }
    else
    {
        pthread_mutex_unlock(&fp->f_lock);
    }
    
    
}

void* thr1(void* arg)
{
    struct foo* fo=(struct foo*)arg;
    for (int i=0;i<100; ++i)
    {
        foo_hold(fo);
    }
}

void* thr2(void* arg)
{
    struct foo* fo=(struct foo*)arg;
    for (int i=0;i<40; ++i)
    {
        foo_rele(fo);
    }
}

int main(void)
{
    int err;
    int* tret;
    pthread_t tid1, tid2;
    struct foo* fp=foo_alloc(1);

    err=pthread_create(&tid1, NULL, thr1, (void*)fp);
    if (0!=err)
    {
        err_exit(err, "can't create thread 1.\n");
    }
    err=pthread_create(&tid2, NULL, thr2, (void*)fp);
    if(0!=err)
    {
        err_exit(err, "can't create thread 2.\n");
    }

    err=pthread_join(tid1, &tret);
    if (0!=err)
    {
        err_exit(err, "can't join thread 1.\n");
    }
    err=pthread_join(tid2, &tret);
    if (0!=err)
    {
        err_exit(err, "can't join thread 2.\n");
    }

    if(NULL!=fp)
    {
        printf("ref is %d\n", fp->f_count);
    }
    else
    {
        printf("fp is already released.\n");
    }
    
}