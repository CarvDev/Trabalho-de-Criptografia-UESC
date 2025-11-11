#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "menu.h"
#include "matrizes.h"
#include "criptografia.h"
#include "auxiliar.h"

int main(void) {
    // funções básicas para o funcionamento do prorgama:
    setlocale(LC_ALL, "Portuguese"); // para usar acentos, etc.
    srand(time(NULL)); // semente para os números aleatórios.

    // declarando variáveis globais:
    int opcao;
    int matriz_cript[MAT][MAT];
    float matriz_decript[MAT][MAT];
    char texto[500];
    int tamanho_texto = sizeof(texto);
    int marcadores[2][500];
    int texto_numerado[2][500];
    char* texto_cripto;
    int texto_cripto_numerado[2][500];
    char salvar_texto[1000];
    char* texto_descripto;

    do {
        mostra_menu();
        opcao = obter_opcao(5);
        switch (opcao)
        {
            case 1:
                // preenchendo matrizes
                preencher_mat_cript(matriz_cript);
                preencher_mat_decript(matriz_cript, matriz_decript);

                printf("\n[Matriz criada com sucesso!]\n");
                break;
            case 2:
                obter_texto(texto, &tamanho_texto, marcadores);
                strcpy(salvar_texto, texto);
                numerar_texto(texto, tamanho_texto, texto_numerado);

                printf("\n[Texto criado e numerado com sucesso!]\n");
                break;
            case 3:
                criptografar(matriz_cript, texto_numerado, texto_cripto_numerado, tamanho_texto, marcadores);
                texto_cripto = obter_texto_codificado_marcado(texto_cripto_numerado, marcadores, tamanho_texto);

                printf("Texto original: %s\n",salvar_texto);
                printf("Texto criptografado: %s\n", texto_cripto);
                break; 
            case 4:
                descriptografar(matriz_decript, texto_cripto_numerado, texto_numerado, tamanho_texto);
                texto_descripto = obter_texto_descriptografado(texto_numerado, marcadores, tamanho_texto);

                    printf("Texto criptografado: %s\n", texto_cripto);
                    printf("Texto descriptografado: %s\n", texto_descripto);

                break;
            case 5:
                printf("[Fim do Programa]\n\n");
                break;      
        }
    }
    while (opcao != 5);
    
    return 0;   
}