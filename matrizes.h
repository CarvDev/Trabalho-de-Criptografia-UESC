#ifndef MATRIZES_H
#define MATRIZES_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ELEMENTOS_MATRIZ 2

// essa função gera números de 1 a 30
int gerar_num();

// essa função preenche a matriz com os números aleatórios gerados
void preencher_matriz_cript(int matriz[ELEMENTOS_MATRIZ][ELEMENTOS_MATRIZ]);

// essa função calcula a determinante
int cacular_determinante(int matriz[ELEMENTOS_MATRIZ][ELEMENTOS_MATRIZ]);

// essa função calcula a matriz inversa
void calcular_inversa(int matriz[ELEMENTOS_MATRIZ][ELEMENTOS_MATRIZ]);

// essa função calcula a matriz de descriptografia
void preencher_matriz_decript(int matriz_cript[ELEMENTOS_MATRIZ][ELEMENTOS_MATRIZ]);
#endif