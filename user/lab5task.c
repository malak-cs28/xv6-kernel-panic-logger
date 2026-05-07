#include "kernel/types.h"
#include "user/user.h"

int main() {
    int pid = fork();

    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        printf("Child: executing ls\n");

        char *args[] = {"ls", 0};
        exec("ls", args);

        // if exec fails
        printf("Exec failed\n");
        exit(1);
    } else {
        // Parent process
        wait(0);
        printf("Parent: child finished execution\n");
    }

    exit(0);
}
