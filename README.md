# Laboratório de Pthreads e Concorrência

Repositório contendo os códigos-fonte desenvolvidos para a disciplina de Computação Paralela (Ciência da Computação). O projeto explora a criação de threads, identificação e correção de condições de corrida (Race Conditions) em C usando POSIX Threads, e analisa o impacto do Global Interpreter Lock (GIL) no CPython.

## Autores
* Guilherme Rainho Geraldo
* Marcos Arambasic Rebelo da Silva
* Matheus Alonso Varjão

## Estrutura dos Arquivos
* `contacorrente_*.c`: Simulação bancária demonstrando execução sequencial, condições de corrida e sincronização com Mutex.
* `soma_vetores.c`: Paralelização de operações memory-bound (vetores gigantes).
* `matriz_vetor.c`: Paralelização de multiplicação matriz-vetor.
* `monte_carlo_pi.c`: Estimativa de Pi utilizando threads independentes (CPU-bound) com `rand_r`.
* `seq.py` e `threads.py`: Demonstração da limitação de paralelismo no Python devido ao GIL.
* `Makefile`: Automação da compilação dos códigos em C.

## Como compilar e executar (C)
Requer ambiente Linux (ou WSL) com `gcc`. Para compilar todos os arquivos C de uma vez, basta executar no terminal:
```bash
make
```

## Para limpar os executáveis gerados:
```bash
make clean
```

## Como executar (Python)
Requer pyhon3 instalado:
```bash
python3 seq.py
python3 threads.py
```

