#include "user/user.h"

int main(int argc, char *argv[])
{
    int fd1[2], fd2[2];
    char buf[1];
    pipe(fd1), pipe(fd2);
    int pid;
    if ((pid = fork()) == -1)
    {
        fprintf(2, "fork error\n");
        exit(-1);
    }
    else if (pid == 0)
    {
        read(fd1[0], buf, 1);
        printf("%d: received ping\n",getpid());
        write(fd2[1], buf, 1);
    }
    else
    {
        write(fd1[1], "1", 1);
        read(fd2[0], buf, 1);
        printf("%d: received pong\n",getpid());
    }
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[0]);
    close(fd2[1]);
    exit(0);
}