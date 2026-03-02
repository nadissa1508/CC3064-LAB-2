// ipc.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define SHM_NAME "/mi_memoria"
#define SIZE 100

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Uso: %s n x\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    char x = argv[2][0];

    int fd;
    int created = 0;

    fd = shm_open(SHM_NAME, O_CREAT | O_EXCL | O_RDWR, 0666);

    if (fd == -1) {
        if (errno == EEXIST) {
            fd = shm_open(SHM_NAME, O_RDWR, 0666);
        } else {
            perror("shm_open");
            exit(1);
        }
    } else {
        created = 1;
        ftruncate(fd, SIZE);
    }

    char *ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // HIJO
        close(pipefd[1]);

        int index = 0;
        char recibido;

        while (read(pipefd[0], &recibido, 1) > 0) {
            ptr[index++] = recibido;
        }

        close(pipefd[0]);
        exit(0);
    } else {
        // PADRE
        close(pipefd[0]);

        for (int i = 0; i < SIZE; i++) {
            if (i % n == 0) {
                write(pipefd[1], &x, 1);
            }
        }

        close(pipefd[1]);
        wait(NULL);

        printf("Contenido memoria compartida:\n");
        for (int i = 0; i < SIZE; i++) {
            if (ptr[i] != 0)
                printf("%c", ptr[i]);
        }
        printf("\n");

        munmap(ptr, SIZE);
        close(fd);

        if (created)
            shm_unlink(SHM_NAME);
    }

    return 0;
}