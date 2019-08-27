#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

void sys_err(const char* str) {
    perror("str");
    exit(1);
}

int main()
{
    pid_t pid;
    char buf[1024];
    int fd[2];
    char* p = "test for pipe\n";
    if (pipe(fd) == -1) {
        sys_err("pipe");
    }
    pid = fork();
    if (pid < 0) {
        sys_err("fork err");
    } else if (pid == 0) {
        int cpid = getpid();
        int fpid = getppid();
        printf("子进程当前pid: %d fpid: %d\n", cpid, fpid);
        // 子进程, 关闭写
        close(fd[1]);
        // 从读管道读数据到buffer, 然后输出到控制台
        int len = read(fd[0], buf, sizeof(buf));
        // STDOUT_FILENO 无缓冲输出
        write(STDOUT_FILENO, buf, len);
        close(fd[0]);
    } else {
        int cpid = getpid();
        int fpid = getppid();
        printf("父进程当前pid: %d fpid: %d\n", cpid, fpid);
        // 父进程
        close(fd[0]);
        write(fd[1], p, strlen(p));
        // 等待子进程结束
        wait(NULL);
        close(fd[1]);
    }
    return 0;
}
