#include "err_handle.h"

void err_exit(int err, const char* err_str)
{
    printf("err=%d, %s\n", err, err_str);
}