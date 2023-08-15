#include "user/user.h"
#include "kernel/types.h"

int main(int argv, char *argc[])
{
    if (argv != 2)
    {
        fprintf(2, "Usage:sleep xxx");
        exit(1);
    }
    sleep(atoi(argc[1]));
    exit(0);
}