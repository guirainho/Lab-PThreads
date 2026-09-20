#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

long N;
int num_threads;
long *pontos_no_circulo_por_thread;

void* monte_carlo(void* arg) {
    long id = (long)arg;
    
    // Divisão do trabalho (quantos pontos cada thread vai sortear)
    long pontos_por_thread = N / num_threads;
    long inicio = id * pontos_por_thread;
    long fim = (id == num_threads - 1) ? N : inicio + pontos_por_thread;
    long total_pontos_locais = fim - inicio;
    
    long count_local = 0;
    
    // Semente única para cada thread (evita a serialização e uso de lock do rand() global)
    unsigned int seed = time(NULL) + id;
    
    for (long i = 0; i < total_pontos_locais; i++) {
        // Gera coordenadas x e y entre 0.0 e 1.0 usando rand_r (reentrante)
        double x = (double)rand_r(&seed) / RAND_MAX;
        double y = (double)rand_r(&seed) / RAND_MAX;
        
        // Verifica se o ponto caiu dentro do quadrante do círculo
        if (x * x + y * y <= 1.0) {
            count_local++;
        }
    }
    
    // Guarda o resultado local num array para evitar o uso de um Mutex global
    pontos_no_circulo_por_thread[id] = count_local;
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

    pontos_no_circulo_por_thread = (long*)malloc(num_threads * sizeof(long));
    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));
    
    struct timespec inicio_tempo, fim_tempo;
    clock_gettime(CLOCK_MONOTONIC, &inicio_tempo);

    // Criação das threads
    for (long i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, monte_carlo, (void*)i);
    }

    long total_pontos_no_circulo = 0;
    
    // Junção das threads e soma dos resultados parciais
    for (long i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        total_pontos_no_circulo += pontos_no_circulo_por_thread[i];
    }

    clock_gettime(CLOCK_MONOTONIC, &fim_tempo);
    double tempo = (fim_tempo.tv_sec - inicio_tempo.tv_sec) + (fim_tempo.tv_nsec - inicio_tempo.tv_nsec) / 1e9;

    // Cálculo final probabilístico de Pi
    double pi_estimado = 4.0 * ((double)total_pontos_no_circulo / (double)N);

    printf("[Monte Carlo Pi] N: %ld | Threads: %d | Pi estimado: %.5f | Tempo: %.4f s\n", 
           N, num_threads, pi_estimado, tempo);

    free(pontos_no_circulo_por_thread);
    free(threads);
    return 0;
}