#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
    int fds[2];
    char buffer[100];
    int pid;

    pipe(fds);

    pid = fork();

    if(pid == 0){
        close(fds[1]);
        int n = read(fds[0], buffer, sizeof(buffer));
        write(1, buffer, n);
        close(fds[0]);
        exit(0);
    }
    else{
        close(fds[0]);
        char *msg = "Hello child\n";
        write(fds[1], msg, strlen(msg));
        close(fds[1]);
        wait(0);
        exit(0);
    }
}
