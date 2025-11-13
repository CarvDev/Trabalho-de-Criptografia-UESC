#include <stdio.h>
#include "menu.h"
#include "auxiliar.h"

void mostra_menu() {
    printf("Digite a opcao desejada:\n"
        " 1. Criar uma matriz de criptografia\n"
        " 2. Criar um texto para ser criptografado\n"
        " 3. Criptografar Texto\n"
        " 4. Descriptografar Texto\n"
        " 5. Sair do sistema\n");
}

int obter_opcao(int limite) {
    int opc; // Variável para armazer a opção selecionada
    int scanf_retorno; // Variável para checar o retorno do scanf

    while (1) {
        printf("> "); // caractere '>' para uma melhor exibição do programa no terminal
        
        // Armazena o valor de retorno da função scanf
        scanf_retorno = scanf("%d", &opc);

        // Caso de erro para quando o input NÃO for um número (ex: 'a') (scanf_retorno será 0)
        if (scanf_retorno == 0) {
            printf("[Erro: Digite apenas números]\nTente novamente...\n\n");
            limpar_buffer(); // Limpa o input inválido (ex: 'a\n')
            continue; // Pula para a próxima iteração do loop

        } else break; // Quebra o loop
    }
    
    limpar_buffer(); // Limpa o '\n' no buffer, para não quebrar o fgets()
    return opc; // Retorna a opção selecionada
}