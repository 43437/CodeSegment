#include <stdio.h>
#include <pthread.h>
#include "err_handle.h"

#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)

struct foo* fh[NHASH];
pthread_mutex_t hashlock=PTHREAD_MUTEX_INITIALIZER;

struct foo
{
    int f_count;
    pthread_mutex_t f_lock;
    int f_id;
    struct foo* f_next; /*protect by hashlock */
    /*more stuff here */
};

struct foo* foo_alloc(int id)   /*alloc the object */
{
    struct foo* fp;
    int idx;
    if ((fp=malloc(sizeof(struct foo)))!=NULL)
    {
        fp->f_count=1;
        fp->f_id=id;
        if (pthread_mutex_init(&fp->f_lock, NULL)!=0)
        {
            free(fp);
            return NULL;
        }
        idx=HASH(id);
        pthread_mutex_lock(&hashlock);
        fp->f_next=fh[idx];
        fh[idx]=fp;
        pthread_mutex_lock(&fp->f_lock);
        pthread_mutex_unlock(&hashlock);
        /*continue initialization. */
        pthread_mutex_unlock(&fp->f_lock);
    }
    else
    {
        fp=NULL;
    }
    return fp;
}

void foo_hold(struct foo* fo)
{
    pthread_mutex_lock(&fo->f_lock);
    ++fo->f_count;
    pthread_mutex_unlock(&fo->f_lock);
}

struct foo* foo_find(int id)
{
    struct foo* fp;
    pthread_mutex_lock(&hashlock);
    for (fp=fh[HASH(id)]; fp!=NULL; fp=fp->f_next)
    {
        if (id==fp->f_id)
        {
            foo_hold(fp);
            break;
        }
    }
    pthread_mutex_unlock(&hashlock);

    return fp;
}

struct foo* foo_find_single(int id)
{
    struct foo* fp;
    pthread_mutex_lock(&hashlock);
    for (fp=fh[HASH(id)]; fp!=NULL; fp=fp->f_next)
    {
        if (id == fp->f_id)
        {
            ++fp->f_count;
            break;
        }
    }
    return fp;
}

void foo_rele(struct foo* fp)
{
    struct foo* tfp;
    int idx;
    pthread_mutex_lock(&fp->f_lock);
    if (1==fp->f_count)
    {
        pthread_mutex_unlock(&fp->f_lock);
        pthread_mutex_lock(&hashlock);
        pthread_mutex_lock(&fp->f_lock);
        if (1==fp->f_count)     //recheck ref
        {
            idx=HASH(fp->f_id);
            tfp=fh[idx];
            if (tfp==fp)
            {
                fh[idx]=fp->f_next;
            }
            else
            {
                while (tfp->f_next!=fp)
                {
                    tfp=tfp->f_next;
                }
                tfp->f_next=fp->f_next;
            }
        }
        else
        {
            pthread_mutex_unlock(&hashlock);
            --fp->f_count;
            pthread_mutex_unlock(&fp->f_count);
        }
        
    }
    else
    {
        --fp->f_count;
        pthread_mutex_unlock(&fp->f_lock);
    }
}

void foo_rele_single(struct foo* fp)
{
    struct foo* tfp;
    int idx;
    pthread_mutex_lock(&hashlock);
    if ((--fp->f_count)==0)
    {
        idx=HASH(fp->f_id);
        tfp=fh[idx];
        if (tfp == fp)
        {
            fh[idx]=fp->f_next;
        }
        else
        {
            while(tfp->f_next!=fp)
            {
                tfp=tfp->f_next;
            }
            tfp->f_next=fp->f_next;
        }
        pthread_mutex_unlock(&hashlock);
        pthread_mutex_destroy(&fp->f_lock);
        free(fp);
    }
    else
    {
        pthread_mutex_unlock(&hashlock);
    }
}

void* thr1(void* arg)
{
    struct foo* fp1=foo_find(1);
    for(int i=0;i<100; ++i)
    {
        foo_hold(fp1);
    }
}

void* thr2(void* arg)
{
    struct foo* fp1=foo_find(1);
    struct foo* fp2=foo_alloc(2);
    for(int i=0;i<30; ++i)
    {
        foo_hold(fp1);
    }
}

void* thr3(void* arg)
{
    struct foo* fp1=foo_find(1);
    struct foo* fp2=foo_alloc(3);
    for(int i=0;i<70; ++i)
    {
        foo_rele(fp1);
    }
}

int main(void)
{
    int err;
    int* tret;
    pthread_t tid1, tid2, tid3;
    foo_alloc(1);
    if ((err=pthread_create(&tid1, NULL, thr1, NULL))!=0)
    {
        err_exit(err, "can't create thread 1.\n");
    }
    if ((err=pthread_create(&tid2, NULL, thr2, NULL))!=0)
    {
        err_exit(err, "can't create thread 2.\n");
    }
    if ((err=pthread_create(&tid3, NULL, thr3, NULL))!=0)
    {
        err_exit(err, "can't create thread 3.\n");
    }

    if (((err=pthread_join(tid1, &tret)))!=0)
    {
        err_exit(err, "can't join thread 1.\n");
    }
    if (((err=pthread_join(tid2, &tret)))!=0)
    {
        err_exit(err, "can't join thread 2.\n");
    }
    if (((err=pthread_join(tid3, &tret)))!=0)
    {
        err_exit(err, "can't join thread 3.\n");
    }

    struct foo* fp=foo_find(1);
    if (NULL!=fp)
    {
        printf("get %d\n", fp->f_id);
    }
    else
    {
        printf("fp 1 is released.\n");
    }
}