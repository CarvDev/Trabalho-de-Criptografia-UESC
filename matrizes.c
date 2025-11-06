#include "matrizes.h"

int gerar_num() {
    int num = rand() % 30 + 1;
    
    return num;
}

void preencher_mat_cript(int mat[MAT][MAT]) {   
    
    for (int linha = 0; linha < MAT; linha++) {
        
        for (int coluna = 0; coluna < MAT; coluna++) {
            mat[linha][coluna] = gerar_num();
        }
    }
} 

int calcular_determinante(int mat[MAT][MAT]) {
    int determinante;

    while (1) {
        int a = mat [0][0];
        int b = mat [1][0];
        int c = mat [0][1];
        int d = mat [1][1];
        
        determinante = (a * d) - (b * c);
        
        if (determinante != 0) {
            break;
        } else {
            preencher_mat_cript(mat);
        }
    }

    return determinante;
}

void preencher_mat_decript(int mat_cript[MAT][MAT], float mat_decript[MAT][MAT]) {
    //calculando determinante:
    int determinante = calcular_determinante(mat_cript);

    // calculando adjunta
    int a = mat_cript[1][1];
    int b = -1 * mat_cript[0][1];
    int c = -1 * mat_cript[1][0];
    int d = mat_cript[0][0];

    float mat_adjunta[MAT][MAT] = {{a, b}, {c, d}};

    //calculando inversa
    for (int linha = 0; linha < MAT; linha++) {
    
        for (int coluna = 0; coluna < MAT; coluna++) {
            mat_decript [linha][coluna] = (mat_adjunta [linha][coluna] / determinante);
        }
    }
}

void imprimir_matriz_float(float (*mat)[MAT]) {

    for (int linha = 0; linha < MAT; linha++) {
    
        for (int coluna = 0; coluna < MAT; coluna++) {
            printf("%.2f ", mat[linha][coluna]);
        }
        printf("\n");
    }
}

void imprimir_matriz_int(int (*mat)[MAT]) {
    
    for (int linha = 0; linha < MAT; linha++) {
        
        for (int coluna = 0; coluna < MAT; coluna++) {
            printf("%d ", mat[linha][coluna]);
        }
        printf("\n");
    }
}