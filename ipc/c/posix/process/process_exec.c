#include <unistd.h>
#include <sys/wait.h>

char *env_ini[] = {"USER=unknow", "PATH=/tmp", NULL};

int main(void)
{
    pid_t pid;
    if ((pid=fork())<0)
    {
        ;   //error
    }
    else if (0==pid)
    {
        if (execle("./echoall", "echoall", "myarg1", "MY ARG2", (char*)0, env_ini)<0)
        {
            ;   //error
        }
    }

    if (waitpid(pid, NULL, 0)<0)
    {
        ;   //error
    }
    
    
    if ((pid=fork())<0)
    {
        ;   //error
    }
    else if (/* condition */)
    {
        /* code */
    }
    
    
}