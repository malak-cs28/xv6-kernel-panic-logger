#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
    int fd[2];
    char msg[] = "Hello";
    char buf[20];

    printf("Before fork\n");

    pipe(fd);

    int pid = fork();

    if(pid < 0){
        printf("Error\n");
        exit(1);
    }

    if(pid == 0){
        // child writes
        close(fd[0]);               // close read end
        write(fd[1], msg, 5);       // send message
        close(fd[1]);
    }
    else{
        // parent reads
        close(fd[1]);               // close write end
        read(fd[0], buf, 5);        // receive message
        write(1, buf, 5);           // print it
        close(fd[0]);

        wait(0);
    }

    exit(0);
}
