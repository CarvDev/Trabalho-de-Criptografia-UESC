#include <locale.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <wchar.h>

#include "menu.h"
#include "matrizes.h"
#include "criptografia.h"
#include "auxiliar.h"

// para corrigir problema de codificação de carecteres wide no Windows 
#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
#endif

int main(void) {
    // funções básicas para o funcionamento do prorgama:
    setlocale(LC_ALL, ""); // para usar acentos, etc.
    srand(time(NULL)); // semente para os números aleatórios.

    // força o stdin e stdout no Windows a usar o modo "wide" (UTF-16)
    #ifdef _WIN32
        _setmode(_fileno(stdout), _O_U16TEXT);
        _setmode(_fileno(stdin),  _O_U16TEXT);
    #endif

    // declarando variáveis globais:    
    int opcao;
    int matriz_cript[MAT][MAT];
    int matriz_decript[MAT][MAT];

    wchar_t texto[500];
    int tamanho_texto = 500;
    int marcadores[2][500];
    int texto_numerado[2][500];
    
    const wchar_t* texto_cripto;
    int texto_cripto_numerado[2][500];

    wchar_t salvar_texto[1000];
    const wchar_t* texto_descripto;

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
                wprintf(L"\n[Matriz criada com sucesso!]\n");
                limpar_tela(1);
                break;
            case 2:
                limpar_tela(0);
                obter_texto(texto, &tamanho_texto, marcadores);
                numerar_texto(texto, tamanho_texto, texto_numerado);
                wcscpy(salvar_texto, texto);
                texto_criado = 1;
                texto_cripto_criado = 0;
                wprintf(L"\n[Texto criado e numerado com sucesso!]\n");
                limpar_tela(1);
                break;
            case 3:
                limpar_tela(0);
                if(matriz_criada == 1 && texto_criado == 1){

                    criptografar(matriz_cript, texto_numerado, texto_cripto_numerado, tamanho_texto, marcadores);
                    texto_cripto = obter_texto_codificado_marcado(texto_cripto_numerado, marcadores, tamanho_texto);
                
                    texto_cripto_criado = 1;
                    wprintf(L"\n--------------------------------------------------\n");
                    wprintf(L"\nTexto original: %ls\n",salvar_texto);
                    wprintf(L"\nTexto criptografado: %ls\n", texto_cripto);
                    wprintf(L"\n--------------------------------------------------\n");
                    limpar_tela(1);
                    break;
                } else {
                    wprintf(L"\nERRO. Precisa criar a matriz (1) e o texto (2) antes de fazer essa etapa.");
                    limpar_tela(1);
                    break;

                } 
            case 4:
                // limpar_tela(0);
                if(texto_cripto_criado == 1){

                    descriptografar(matriz_decript, texto_cripto_numerado, texto_numerado, tamanho_texto);
                    texto_descripto = obter_texto_descriptografado(texto_numerado, marcadores, tamanho_texto);
                    wprintf(L"\n--------------------------------------------------\n");
                    wprintf(L"\nTexto criptografado: %ls\n", texto_cripto);
                    wprintf(L"\nTexto descriptografado: %ls\n", texto_descripto);
                    wprintf(L"\n--------------------------------------------------\n");
                    limpar_tela(1);
                    break;
                
                } else {
                    wprintf(L"\nERRO. Precisa criptografar um texto (3) antes de fazer essa etapa.");
                    limpar_tela(1);
                    break;
                }
            case 5:
                // limpar_tela(0);
                wprintf(L"\n[Fim do Programa]\n\n");
                break; 
            default:
                wprintf(L"[Opção inválida]\nTente novamente...\n\n");
                break;
        }
    }
    while (opcao != 5);
    
    return 0;   
}