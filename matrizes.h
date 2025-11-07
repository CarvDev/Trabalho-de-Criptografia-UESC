#ifndef MATRIZES_H
#define MATRIZES_H

#define MIN 1 // número mínimo capaz de ser gerado aleatoriamente para a matriz
#define MAX 30 // número máximo capaz de ser gerado aleatoriamente para a matriz
#define MAT 2 // número de termos da matriz, horizontal e verticalmente (não mexer por enquanto)

// gera números de 1 a 30
int gerar_num();

// preenche a matriz com os números aleatórios gerados
void preencher_mat_cript(int (*mat)[MAT]);

// calcula a determinante
int calcular_determinante(int (*mat)[MAT]);

// calcula a matriz de descriptografia
void preencher_mat_decript(int (*mat_cript)[MAT], float (*mat_decript)[MAT]);

// imprime matrizes (só para testes)
void imprimir_matriz_float(float (*mat)[MAT]);
void imprimir_matriz_int(int (*mat)[MAT]);

#endif