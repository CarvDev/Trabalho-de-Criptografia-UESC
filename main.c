#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "menu.h"
#include "matrizes.h"

int main(void) {
    setlocale(LC_ALL, "Portuguese"); // para usar acentos, etc.
    // declarando variáveis globais:
    int opcao;
    int matriz_cript[MAT][MAT];
    float matriz_decript[MAT][MAT];
    srand(time(NULL));

    do {
        mostra_menu();
        opcao = obter_opcao(5);
        switch (opcao)
        {
            case 1:
                // implementar opção 1
                preencher_mat_cript(matriz_cript);

                imprimir_matriz_int(matriz_cript);

                preencher_mat_decript(matriz_cript, matriz_decript);

                imprimir_matriz_float(matriz_decript);
                break;
            case 2:
                // implementar opção 2

                break;
            case 3:
                // implementar opção 3

                break;
            case 4:
                // implementar opção 4

                break;
            case 5:
                printf("[Fim do Programa]\n\n");
                break;      
        }
    }
    while (opcao != 5);
    
    return 0;   
}