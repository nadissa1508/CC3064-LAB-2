// tiempo_concurrente_verbose.c (CORREGIDO)
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

int main() {
    pid_t hijo, nieto, bisnieto;
    struct timeval inicio, fin;
    
    // Usar gettimeofday() en lugar de clock() para medir tiempo real
    gettimeofday(&inicio, NULL);
    
    hijo = fork();
    
    if(hijo == 0) {
        // PROCESO HIJO
        nieto = fork();
        
        if(nieto == 0) {
            // PROCESO NIETO
            bisnieto = fork();
            
            if(bisnieto == 0) {
                // PROCESO BISNIETO
                for(int i = 0; i < 1000000; i++) {
                    printf("Bisnieto - Iteración: %d\n", i);
                }
                return 0;
            }
            else {
                // PROCESO NIETO
                for(int i = 0; i < 1000000; i++) {
                    printf("Nieto - Iteración: %d\n", i);
                }
                wait(NULL);
                return 0;
            }
        }
        else {
            // PROCESO HIJO
            for(int i = 0; i < 1000000; i++) {
                printf("Hijo - Iteración: %d\n", i);
            }
            wait(NULL);
            return 0;
        }
    }
    else {
        // PROCESO PADRE
        wait(NULL);
        
        // Medir tiempo real transcurrido
        gettimeofday(&fin, NULL);
        
        // Calcular diferencia en segundos
        double tiempo_transcurrido = (fin.tv_sec - inicio.tv_sec) + 
                                     (fin.tv_usec - inicio.tv_usec) / 1000000.0;
        
        printf("\n=== Tiempo transcurrido (concurrente): %f segundos ===\n", tiempo_transcurrido);
    }
    
    return 0;
}