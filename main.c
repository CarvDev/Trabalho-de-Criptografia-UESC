#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// API do Windows
#ifdef _WIN32
    #include <windows.h>
#endif

#include "menu.h"
#include "matrizes.h"
#include "criptografia.h"
#include "auxiliar.h"

int main(void) {
    // funções básicas para o funcionamento do prorgama:
    #ifdef _WIN32
        /* Código para Windows (para forçar a codificação dos caracteres UTF8)
        (para usar acentos, etc.) */
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #else
        // Código para Linux, macOS, etc. (para usar acentos, etc.)
        setlocale(LC_ALL, ""); 
    #endif
    
    srand(time(NULL)); // semente para os números aleatórios.

    // declarando variáveis globais:
    int opcao;
    int matriz_cript[MAT][MAT];
    int matriz_decript[MAT][MAT];
    char texto[500];
    int tamanho_buffer = sizeof(texto); // tamanho máximo do texto
    int tamanho_texto; // tamanho real do texto (será atribuido)
    int marcadores[2][500];
    int texto_numerado[2][500];
    char* texto_cripto;
    int texto_cripto_numerado[2][500];
    char* salvar_texto = NULL;
    char* texto_descripto;

    int matriz_criada = 0;
    int texto_criado = 0;
    int texto_cripto_criado = 0;

    do {
        mostra_menu();
        opcao = obter_opcao(5);
        switch (opcao)
        {
            case 1:
                limpar_tela(0);
                // preenchendo matrizes
                preencher_mat_cript(matriz_cript);
                preencher_mat_decript(matriz_cript, matriz_decript);

                matriz_criada = 1;
                printf("\n[Matriz criada com sucesso!]\n");
                limpar_tela(1);
                break;
            case 2:
                limpar_tela(0);
                obter_texto(texto, &tamanho_texto, tamanho_buffer, marcadores,&salvar_texto);
                numerar_texto(texto, tamanho_texto, texto_numerado);
                texto_criado = 1;
                texto_cripto_criado = 0;
                printf("\n[Texto criado e numerado com sucesso!]\n");
                limpar_tela(1);
                break;
            case 3:
                limpar_tela(0);
                if(matriz_criada == 1 && texto_criado == 1){

                    criptografar(matriz_cript, texto_numerado, texto_cripto_numerado, tamanho_texto, marcadores);
                    texto_cripto = obter_texto_codificado_marcado(texto_cripto_numerado, marcadores, tamanho_texto);
                
                    texto_cripto_criado = 1;
                    printf("\n--------------------------------------------------\n");
                    printf("\nTexto original: %s\n",salvar_texto);
                    printf("\nTexto criptografado: %s\n", texto_cripto);
                    printf("\n--------------------------------------------------\n");
                    limpar_tela(1);
                    break;
                } else {
                    printf("\nERRO. Precisa criar a matriz (1) e o texto (2) antes de fazer essa etapa.");
                    limpar_tela(1);
                    break;

                } 
            case 4:
                limpar_tela(0);
                if(texto_cripto_criado == 1){

                    descriptografar(matriz_decript, texto_cripto_numerado, texto_numerado, tamanho_texto);
                    texto_descripto = obter_texto_descriptografado(texto_numerado, marcadores, tamanho_texto);
                    printf("\n--------------------------------------------------\n");
                    printf("\nTexto criptografado: %s\n", texto_cripto);
                    printf("\nTexto descriptografado: %s\n", texto_descripto);
                    printf("\n--------------------------------------------------\n");
                    limpar_tela(1);
                    break;
                
                } else {
                    printf("\nERRO. Precisa criptografar um texto (3) antes de fazer essa etapa.");
                    limpar_tela(1);
                    break;
                }
            case 5:
                limpar_tela(0);
                printf("\n[Fim do Programa]\n\n");
                break; 
            default:
                printf("[Opção inválida]\nTente novamente...\n\n");
                break;
        }
    }
    while (opcao != 5);
    
    return 0;   
}