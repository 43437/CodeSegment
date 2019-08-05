#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "err_handle.h"

void pr_exit(int status)
{
    if (WIFEXITED(status))              //normal exit.
    {
        printf("normal termination, exit status=%d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))       //abnormal exit.
    {
        printf("abnormal termination, signal number=%d\n",WTERMSIG(status));
    }
}

int main(void)
{
    int var=0;
    pid_t pid;
    int status;

    if ((pid=fork())<0)
    {
        err_sys("fork error.");
    } else if (0==pid)
    {
        ++var;
    }
    else
    {
        if (wait(&status)!=pid)        //in parent process
        {
            ;       //err 
        }

        pr_exit(status);
    }
    
    printf("%d\n", var);
}