#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long N;
int num_threads;
float *A, *B, *C_vet; // C_vet para evitar conflito de nomes

void* soma_parcial(void* arg) {
    long id = (long)arg;
    
    // Divisão em blocos contíguos
    long tamanho_bloco = N / num_threads;
    long inicio = id * tamanho_bloco;
    // A última thread assume o resto, caso N não seja múltiplo exato
    long fim = (id == num_threads - 1) ? N : inicio + tamanho_bloco;

    for (long i = inicio; i < fim; i++) {
        C_vet[i] = A[i] + B[i];
    }
    
    return NULL;
}

int main(int argc, char* argv[]) {
    // Validação dos argumentos conforme exigido: ./programa <N> <num_threads>
    if (argc != 3) {
        printf("Uso: %s <N> <num_threads>\n", argv[0]);
        return 1;
    }

    N = atol(argv[1]);
    num_threads = atoi(argv[2]);

    // Alocação dinâmica dos vetores gigantes
    A = (float*)malloc(N * sizeof(float));
    B = (float*)malloc(N * sizeof(float));
    C_vet = (float*)malloc(N * sizeof(float));

    // Preenchimento inicial para o teste
    for (long i = 0; i < N; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    struct timespec inicio_tempo, fim_tempo;

    clock_gettime(CLOCK_MONOTONIC, &inicio_tempo);

    // Criação das threads
    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, soma_parcial, (void*)i);
    }

    // Aguarda a finalização
    for (long i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim_tempo);
    double tempo = (fim_tempo.tv_sec - inicio_tempo.tv_sec) + (fim_tempo.tv_nsec - inicio_tempo.tv_nsec) / 1e9;

    printf("[Soma de Vetores] N: %ld | Threads: %d | Tempo: %.4f s\n", N, num_threads, tempo);

    free(A); free(B); free(C_vet);
    free(threads);
    return 0;
}