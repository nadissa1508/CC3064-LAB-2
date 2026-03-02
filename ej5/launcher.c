#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {

    pid_t p1 = fork();

    if (p1 == 0) {
        execl("./ipc", "ipc", "3", "A", NULL);
    }

    usleep(100000); // 100 ms

    pid_t p2 = fork();

    if (p2 == 0) {
        execl("./ipc", "ipc", "5", "B", NULL);
    }

    wait(NULL);
    wait(NULL);

    return 0;
}