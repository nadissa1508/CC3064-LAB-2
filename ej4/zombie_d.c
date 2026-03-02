#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t hijo;
    hijo = fork();
    if (hijo == 0)
    {
        // PROCESO HIJO
        printf("Hijo: Mi PID es %d, esperando...\n", getpid());
        sleep(30); 
        printf("Hijo: Comenzando conteo...\n");
        for (int i = 1; i <= 40000000; i++)
        {
            if (i % 100000 == 0)
            {
                printf("Hijo: %d / 40000000\n", i);
            }
        }
        printf("Hijo: Terminé el conteo, finalizando...\n");
        return 0;
    }
    else
    {
        // PROCESO PADRE
        printf("Padre: Mi PID es %d, hijo PID %d\n", getpid(), hijo);
        printf("Padre: Entrando en ciclo infinito (sin wait)...\n");
        while (1)
        {
            sleep(1);
        }
    }
    return 0;
}