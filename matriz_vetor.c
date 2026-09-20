#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long N;
int num_threads;
float **M;
float *V;
float *R;

void* multiplica_linhas(void* arg) {
    long id = (long)arg;
    
    // Distribuição por blocos de linhas
    long linhas_por_thread = N / num_threads;
    long linha_inicio = id * linhas_por_thread;
    long linha_fim = (id == num_threads - 1) ? N : linha_inicio + linhas_por_thread;

    for (long i = linha_inicio; i < linha_fim; i++) {
        R[i] = 0.0f; // Inicializa o elemento do resultado
        for (long j = 0; j < N; j++) {
            R[i] += M[i][j] * V[j];
        }
    }
    
    return NULL;
}

int main(int argc, char* argv[]) {
    // Validação da entrada conforme diretrizes
    if (argc != 3) {
        printf("Uso: %s <N> <num_threads>\n", argv[0]);
        return 1;
    }

    N = atol(argv[1]);
    num_threads = atoi(argv[2]);

    // Alocação da matriz M (N x N) e vetores V e R
    M = (float**)malloc(N * sizeof(float*));
    for (long i = 0; i < N; i++) {
        M[i] = (float*)malloc(N * sizeof(float));
    }
    V = (float*)malloc(N * sizeof(float));
    R = (float*)malloc(N * sizeof(float));

    // Inicialização genérica para o teste
    for (long i = 0; i < N; i++) {
        V[i] = 2.0f;
        for (long j = 0; j < N; j++) {
            M[i][j] = 1.5f;
        }
    }

    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    struct timespec inicio_tempo, fim_tempo;

    clock_gettime(CLOCK_MONOTONIC, &inicio_tempo);

    // Criação das threads
    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, multiplica_linhas, (void*)i);
    }

    // Junção das threads
    for (long i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_gettime(CLOCK_MONOTONIC, &fim_tempo);
    double tempo = (fim_tempo.tv_sec - inicio_tempo.tv_sec) + (fim_tempo.tv_nsec - inicio_tempo.tv_nsec) / 1e9;

    printf("[Matriz x Vetor] N: %ld | Threads: %d | Tempo: %.4f s\n", N, num_threads, tempo);

    // Libertação de memória
    for (long i = 0; i < N; i++) {
        free(M[i]);
    }
    free(M); free(V); free(R);
    free(threads);

    return 0;
}