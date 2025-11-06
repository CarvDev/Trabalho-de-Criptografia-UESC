#ifndef MATRIZES_H
#define MATRIZES_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAT 2

// essa função gera números de 1 a 30
int gerar_num();

// essa função preenche a matriz com os números aleatórios gerados
void preencher_mat_cript(int mat[MAT][MAT]);

// essa função calcula a determinante
int calcular_determinante(int mat[MAT][MAT]);

// essa função calcula a matriz de descriptografia
void preencher_mat_decript(int mat_cript[MAT][MAT], float mat_decript[MAT][MAT]);

// imprime a matriz (para testes)
void imprimir_matriz_float(float mat[MAT][MAT]);
void imprimir_matriz_int(int mat[MAT][MAT]);

#endif