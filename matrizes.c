#include "matrizes.h"

int gerar_num() {
    srand(time(NULL));
    int num = rand() % 30 + 1;
    
    return num;
}

void preencher_matriz_cript(int matriz[ELEMENTOS_MATRIZ][ELEMENTOS_MATRIZ]) {
    for (int linha = 0; linha < ELEMENTOS_MATRIZ; linha++) {
    
        for (int coluna = 0; coluna < ELEMENTOS_MATRIZ; coluna++) {
            matriz[linha][coluna] = gerar_num();
        }
    }
}


int calcular_determinante(int matriz[ELEMENTOS_MATRIZ][ELEMENTOS_MATRIZ]) {
    int determinante;
    
    int a = matriz [0][0];
    int b = matriz [1][0];
    int c = matriz [0][1];
    int d = matriz [1][1];

    determinante = (a * d) - (b * c);

    return determinante;
}


void preencher_matriz_decript(int matriz_cript[ELEMENTOS_MATRIZ][ELEMENTOS_MATRIZ]) {
    //calculando determinante:
    int determinante = calcular_determinante(matriz_cript);

    // calculando adjunta
    int a = matriz_cript[1][1];
    int b = -1 * matriz_cript[0][1];
    int c = -1 * matriz_cript[1][0];
    int d = matriz_cript[0][0];

    int adjunta[] = {a, b, c, d};

    //calculando inversa
}