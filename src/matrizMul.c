#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>       // Librería para manejo de hilos


/*  Variables globales para acceder desde la función que ejecutan los 
hilos, estos no compiten por el acceso ya que cada hilo trabaja en una
posición distinta de la matriz resultado, no requiere sincronización que 
haría más complejo el código
*/
int n;
int **A, **B, **C;

typedef struct {     //Estructura para pasar múltiples argumentos a la función del hilo
    int i, j;
} args_t;

void* compute_element(void* arg) {  // Función que ejecuta cada hilo
    args_t* a = (args_t*)arg;       // Cast del argumento a la estructura
    int i = a->i, j = a->j;
    int res = 0;
    for(int k = 0; k < n; k++) {
        res |= (A[i][k] & B[k][j]);
    }
    C[i][j] = res;
    free(a);                        // Liberar memoria de los argumentos
    return NULL;
}

int main() {
    printf("Ingrese el tamaño n de las matrices: ");
    scanf("%d", &n);

        // Reserva dinámica de memoria para las matrices con malloc
    A = malloc(n * sizeof(int*));    
    for(int i = 0; i < n; i++) A[i] = malloc(n * sizeof(int));

    B = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) B[i] = malloc(n * sizeof(int));

    C = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) C[i] = malloc(n * sizeof(int));

    printf("Ingrese la matriz A (%dx%d):\n", n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    printf("Ingrese la matriz B (%dx%d):\n", n, n);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    const int MAX_THREADS = 4;  // Número máximo de hilos concurrentes 
    pthread_t threads[MAX_THREADS];
    int thread_count = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            args_t* a = malloc(sizeof(args_t));
            a->i = i;
            a->j = j;
            // Crear un hilo para calcular C[i][j]
            pthread_create(&threads[thread_count], NULL, compute_element, a);
            thread_count++;
            if(thread_count == MAX_THREADS) {
                for(int k = 0; k < MAX_THREADS; k++) {
                    pthread_join(threads[k], NULL);
                }
                thread_count = 0;
            }
        }
    }
    // Unir los hilos restantes
    for(int k = 0; k < thread_count; k++) {
        pthread_join(threads[k], NULL);
    }

    printf("Matriz resultado C:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Liberar memoria
    for(int i = 0; i < n; i++) free(A[i]);
    free(A);
    for(int i = 0; i < n; i++) free(B[i]);
    free(B);
    for(int i = 0; i < n; i++) free(C[i]);
    free(C);

    return 0;
}