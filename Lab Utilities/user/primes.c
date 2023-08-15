#include "user/user.h"

int is_prime(int n)
{
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)return 0;
    return 1;
}

void pipeline(int *fd)
{
    int n = 0;
    read(fd[0], &n, sizeof(int));
    if (n == 0)
        return;
    printf("prime %d\n", n);
    int p[2];
    pipe(p);
    if (fork())
    {
        int x = 0;
        while (read(fd[0], &x, sizeof(int)) > 0)
            if (is_prime(x))
                write(p[1], &x, sizeof(int));
        close(fd[0]);
        close(p[0]);
        close(p[1]);
        wait(0);
    }
    else
    {
        close(fd[0]);
        close(p[1]);
        pipeline(p);
        close(p[0]);
    }
}

int main()
{
    int fd[2];
    pipe(fd);
    for (int i = 2; i <= 35; i++)
        write(fd[1], &i, sizeof(int));
    if (fork())
    {
        close(fd[0]);
        close(fd[1]);
        wait(0);
    }
    else
    {
        close(fd[1]);
        pipeline(fd);
        close(fd[0]);
    }
    exit(0);
}