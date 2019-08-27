#include <stdio.h>
#include<unistd.h>

int main()
{
    fork();
    fork() && fork() || fork();
    fork();
    printf("pid: %d\n", getpid());
    sleep(1);
    return 0;
}

