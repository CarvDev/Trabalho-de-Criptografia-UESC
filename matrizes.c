#include "matrizes.h"
#include <stdio.h>
#include "auxiliar.h"

#define MOD 29

static int mod_pos(int x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x; // retorna um valor entre 0 e 28, evitando problema da descriptografia
}
static int mod_inv(int a) {
    int am = mod_pos(a);
    if (am == 0) return -1; // sem inverso
    for (int i = 1; i < 29; i++) {
        if ((am * i) % 29 == 1) return i;
    }
    return -1; // não invertível
}

int calcular_determinante(int (*mat)[MAT]) {
    int determinante = (mat [0][0] * mat [1][1]) - (mat [1][0] * mat [0][1]);
    return determinante;
}

void preencher_mat_cript(int (*mat)[MAT]) {
    do {
        
        for (int linha = 0; linha < MAT; linha++) {
            
            for (int coluna = 0; coluna < MAT; coluna++) {
                mat[linha][coluna] = gerar_num();
            }
        }

    } while (calcular_determinante(mat) == 0); 
    //recria a matriz, caso o seu determinante seja 0, evitando uma futura divisão por 0
} 

void preencher_mat_decript(int (*mat_cript)[MAT], int (*mat_decript)[MAT]) {
    int a = mat_cript[0][0];
    int b = mat_cript[0][1];
    int c = mat_cript[1][0];
    int d = mat_cript[1][1];
    int det = calcular_determinante(mat_cript);
    int detm = mod_pos(det);

    int inv_det = mod_inv(detm);
    if (inv_det == -1) {
        
        printf("Erro: determinante não invertível modulo 29\n");
        return;
    }

    int adj[MAT][MAT];
    adj[0][0] =  d;
    adj[0][1] = -b;
    adj[1][0] = -c;
    adj[1][1] =  a;

    for (int i = 0; i < MAT; i++) {
        for (int j = 0; j < MAT; j++) {
            mat_decript[i][j] = mod_pos(inv_det * adj[i][j]);
        }
    }
}