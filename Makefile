# Makefile para o Laboratório de Pthreads
CC = gcc
CFLAGS = -O2 -Wall -pthread

# Alvos principais
all: seq f1 f2 soma_vetores matriz_vetor monte_carlo_pi

# Parte 1: Conta Corrente
seq: contacorrente_seq.c
	$(CC) $(CFLAGS) contacorrente_seq.c -o seq

f1: contacorrente_f1.c
  $(CC) $(CFLAGS) contacorrente_f1.c -o f1

f2: contacorrente_f2.c
	$(CC) $(CFLAGS) contacorrente_f2.c -o f2

# Parte 2: Menu de Problemas
soma_vetores: soma_vetores.c
	$(CC) $(CFLAGS) soma_vetores.c -o soma_vetores

matriz_vetor: matriz_vetor.c
	$(CC) $(CFLAGS) matriz_vetor.c -o matriz_vetor

monte_carlo_pi: monte_carlo_pi.c
	$(CC) $(CFLAGS) monte_carlo_pi.c -o monte_carlo_pi

# Limpeza dos executáveis
clean:
	rm -f seq f1 f2 soma_vetores matriz_vetor monte_carlo_pi
