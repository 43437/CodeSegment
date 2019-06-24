#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

int main(void)
{
    int err;
    struct timespec tout;
    struct tm* tmp;
    char buf[64];
    pthread_mutex_t lock=PTHREAD_MUTEX_INITIALIZER;

    pthread_mutex_lock(&lock);
    printf("mutex is locked\n");

    clock_gettime(CLOCK_REALTIME, &tout);
    tmp=localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("current time is %s\n",buf);

    tout.tv_sec+=10;
    err=pthread_mutex_timedlock(&lock, &tout);

    clock_gettime(CLOCK_REALTIME, &tout);
    tmp=localtime(&tout.tv_sec);
    strftime(buf, sizeof(buf), "%r", tmp);
    printf("the time is now %s\n",buf);
    
    if (0 == err)
    {
        printf("mutex locked again!\n");
    }
    else
    {
        printf("can't locked again: %s\n", strerror(err));
    }
    
    
}