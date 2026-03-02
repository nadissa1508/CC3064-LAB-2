#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t hijo;
    hijo = fork();

    if(hijo == 0) {
        // PROCESO HIJO
        printf("Hijo: Mi PID es %d. Terminando...\n", getpid());
        return 0;   // Termina inmediatamente
    }
    else {
        // PROCESO PADRE
        printf("Padre: Mi PID es %d, hijo PID %d\n", getpid(), hijo);
        
        while(1) {
            sleep(1);
        }
    }

    return 0;
}