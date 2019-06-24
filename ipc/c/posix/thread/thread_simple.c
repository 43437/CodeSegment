#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "err_handle.h"

typedef struct 
{
    int val;
    char str[256];
}thr_param;

typedef struct
{
    int val;
    char str[256];
}thr_val;


void *thr_fn1(void* arg)
{
    thr_param* th_param=(thr_param*)arg;
    printf("thread 1 args, val=%d, str=%s\n", th_param->val, th_param->str);

    free(th_param);
    thr_val* th_val=(thr_val*)malloc(sizeof(thr_val));
    th_val->val=1;
    strncpy(th_val->str, "return from thread 1.", 256);
    return ((void*)th_val);
}

int main(void)
{
    int err;
    pthread_t tid1;
    void *tret;
    thr_param *th1_param=(thr_param*)malloc(sizeof(thr_param));
    th1_param->val=101;
    strncpy(th1_param->str, "param from main. ", 256);

    err = pthread_create(&tid1, NULL, thr_fn1, (void*)th1_param);
    if (0!=err)
    {
        err_exit(err, "can't create thread 1.");
    }

    err=pthread_join(tid1, &tret);
    if (0!=err)
    {
        err_exit(err, "can't join thr1 thread. ");
    }
    
    thr_val* thr_return=(thr_val*)tret;
    printf("thread 1 return, val=%d, str=%s\n", thr_return->val, thr_return->str);
    free(thr_return);

    exit(0);
}