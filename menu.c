#include <stdio.h>
#include "menu.h"

void mostra_menu() {
    printf("Digite a opcao desejada:\n"
        " 1. Criar uma matriz de criptografia\n"
        " 2. Criar um texto para ser criptografado\n"
        " 3. Criptografar Texto\n"
        " 4. Descriptografar Texto\n"
        " 5. Sair do sistema\n");
}

int obter_opcao(int limite) {
    int opc;
    while (1) {
        opc = 0; // (re)definindo opção como 0, por segurança
        
        printf("> "); // caractere '>' para melhorar a exibição no terminal
        scanf("%d", &opc);

        // verificando se a opção digitada está dentro do escopo do menu 
        if (opc >= 1 && opc <= limite) {
            break; // se a opção estiver dentro escopo, quebra o loop
        } else {
            // caso estiver fora, imprime mensagem de erro e continua no loop
            printf("[Opção inválida]\nTente novamente...\n\n");
        }
    }
    return opc;
}