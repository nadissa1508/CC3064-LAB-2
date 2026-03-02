#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    clock_t inicio, fin;
    double tiempo;

    inicio = clock();

    pid1 = fork();

    if (pid1 == 0) {  // HIJO
        pid2 = fork();

        if (pid2 == 0) {  // NIETO
            pid3 = fork();

            if (pid3 == 0) {  // BISNIETO
                for(int i = 0; i < 100000000; i++){
                    printf("Bisnieto: %d\n", i);
                }
            } else {  // NIETO
                for(int i = 0; i < 100000000; i++){
                    printf("Nieto: %d\n", i);
                }
                wait(NULL);
            }
        } else {  // HIJO
            for(int i = 0; i < 100000000; i++){
                printf("Hijo: %d\n", i);
            }
            wait(NULL);
        }
    } else {  // PADRE
        wait(NULL);

        fin = clock();
        tiempo = (double)(fin - inicio) / CLOCKS_PER_SEC;
        printf("Tiempo de ejecucion concurrente: %f segundos\n", tiempo);
    }

    return 0;
}