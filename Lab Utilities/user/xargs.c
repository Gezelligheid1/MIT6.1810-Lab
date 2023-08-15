#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "arguments error");
        exit(-1);
    }
    char buf[128], *p = buf;
    char *arguments[MAXARG];
    for (int i = 0; i < argc; i++)
        arguments[i] = argv[i];
    while (read(0, p, 1) == 1)
    {
        if (p[0] == '\n')
        {
            p[0] = 0;
            arguments[argc] = buf;
            if (fork())
                wait(0);
            else
            {
                exec(argv[1], arguments + 1);
                fprintf(2, "exec %s failed\n", argv[1]);
                exit(0);
            }
            p = buf;
        }
        else
            p++;
    }


    exit(0);
}