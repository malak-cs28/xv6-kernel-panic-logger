#include "kernel/types.h"
#include "user/user.h"

void mysleep(int seconds)
{
    for(int s = 0; s < seconds; s++){
        for(volatile int i = 0; i < 100000000; i++);
    }
}

int
main(int argc, char *argv[])
{
    if(argc != 2){
        printf("Usage: mysleep <seconds>\n");
        exit(1);
    }

    int seconds = atoi(argv[1]);

    printf("Sleeping for %d seconds...\n", seconds);

    mysleep(seconds);

    printf("Done!\n");

    exit(0);
}
