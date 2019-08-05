#include "err_handle.h"

void err_sys(char* msg)
{
    fprintf(stderr, "%s\n", msg);
}