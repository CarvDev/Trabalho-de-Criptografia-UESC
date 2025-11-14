#include <wchar.h>
#include "menu.h"
#include "auxiliar.h"

void mostra_menu() {
    wprintf(L"Digite a opcao desejada:\n"
        L" 1. Criar uma matriz de criptografia\n"
        L" 2. Criar um texto para ser criptografado\n"
        L" 3. Criptografar Texto\n"
        L" 4. Descriptografar Texto\n"
        L" 5. Sair do sistema\n");
}

int obter_opcao() {
    int opc; // Variável para armazer a opção selecionada
    int scanf_retorno; // Variável para checar o retorno do scanf

    while (1) {
        wprintf(L"> "); // caractere '>' para uma melhor exibição do programa no terminal
        
        // Armazena o valor de retorno da função scanf
        scanf_retorno = wscanf(L"%d", &opc);

        // Caso de erro para quando o input NÃO for um número (ex: 'a') (scanf_retorno será 0)
        if (scanf_retorno == 0) {
            wprintf(L"[Erro: Digite apenas números]\nTente novamente...\n\n");
            limpar_buffer(); // Limpa o input inválido (ex: 'a\n')
            continue; // Pula para a próxima iteração do loop

        } else break; // Quebra o loop
    }
    
    limpar_buffer(); // Limpa o '\n' no buffer, para não quebrar o fgets()
    return opc; // Retorna a opção selecionada
}