#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "menu.h"

int main(void) {
    setlocale(LC_ALL, "Portuguese"); // para usar acentos, etc.
    // declarando variáveis globais:
    int opcao;

    do {
        mostra_menu();
        opcao = obter_opcao(5);
        switch (opcao)
        {
            case 1:
                // implementar opção 1

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