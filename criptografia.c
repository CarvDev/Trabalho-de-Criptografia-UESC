#include "matrizes.h"
#include "criptografia.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char alfabeto[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M',
'N','O','P','Q','R','S','T','U','V','W','X','Y','Z','.', ',', '#' };
int alfabeto_tam = 29;

// ============== OPERAÇÕES PARA PREPARAR O TEXTO PARA CRIPTOGRAFIA ==============
void deixar_maiusculo (char *texto) {
    int i = 0;
    while (texto[i] != '\0') {
        texto[i] = toupper(texto[i]);
        i++;
    }
}

int detectar_acento (char letra){
    if (strchr("ÃÕ", letra)) return -1; 
    if (strchr("ÁÉÍÓÚ", letra)) return -2; 
    if (strchr("ÂÊÎÔÛ", letra)) return -3; 
    if (strchr("ÀÈÌÒÙ", letra)) return -4; 
    return 0; 
}

void tirar_acento (char *texto, int tamanho, int marcadores[2][500]){
    int metade = tamanho/2;
    for (int i = 0; i < tamanho; i++) {
        char letra = texto[i];
        int marcador = detectar_acento(letra);

        if (marcador != 0) {
            switch (marcador) {
                case -1: if (letra == 'Ã') letra = 'A'; else if (letra == 'Õ') letra = 'O'; else if (letra == 'Ñ') letra = 'N'; break;
                case -2: if (letra == 'Á') letra = 'A'; else if (letra == 'É') letra = 'E'; else if (letra == 'Í') letra = 'I'; else if (letra == 'Ó') letra = 'O'; else if (letra == 'Ú') letra = 'U'; break;
                case -3: if (letra == 'Â') letra = 'A'; else if (letra == 'Ê') letra = 'E'; else if (letra == 'Î') letra = 'I'; else if (letra == 'Ô') letra = 'O'; else if (letra == 'Û') letra = 'U'; break;
                case -4: if (letra == 'À') letra = 'A'; else if (letra == 'È') letra = 'E'; else if (letra == 'Ì') letra = 'I'; else if (letra == 'Ò') letra = 'O'; else if (letra == 'Ù') letra = 'U'; break;
            }
        }

         texto[i] = letra;

        if (i < metade) {
            marcadores[0][i] = marcador;
        } 
        else {
            marcadores[1][i - metade] = marcador;
        }
    }

    texto[tamanho] = '\0';

}

// ============ OPÇÃO 2 DO MENU ============ 
void obter_texto(char *texto, int *tamanho, int marcadores[2][500]) {
    printf("\nDigite o texto que deseja criptografar:\n > ");
    fgets(texto, *tamanho, stdin);

    *tamanho = strlen(texto);

    if (*tamanho > 0 && texto [*tamanho - 1] == '\n') {
        texto [*tamanho - 1] = '\0';
        (*tamanho) -- ;
    }
    deixar_maiusculo (texto);
    tirar_acento(texto,tamanho,marcadores);
}


void numerar_texto(char *texto, int tamanho, int *texto_numerado[2][500]) {

    if (tamanho % 2 != 0) {
        texto[tamanho] = '#';
        tamanho++;
        texto[tamanho] = '\0';
    }

     int metade = tamanho / 2;

    for (int i = 0; i < tamanho; i++) {
        int valor = 29; 

        for (int j = 0; j < alfabeto_tam; j++) {
            if (texto[i] == alfabeto[j]) {
                valor = j + 1;
                break;
            }
        }

        if (i < metade) {
            texto_numerado[0][i] = valor;
        } else {
            texto_numerado[1][i - metade] = valor;
        }
    }
}
// ============ OPÇÃO 3 DO MENU ============ 
void criptografar(int matriz_cript[2][2], int texto_enumerado[2][500], int texto_criptografado[2][500], int tamanho, int marcadores[2][500]) {
    int colunas = tamanho / 2;

    for (int i = 0; i < colunas; i++) {
        int x = texto_enumerado[0][i];
        int y = texto_enumerado[1][i];

        texto_criptografado[0][i] = matriz_cript[0][0] * x + matriz_cript[0][1] * y;
        texto_criptografado[1][i] = matriz_cript[1][0] * x + matriz_cript[1][1] * y;
    }

    obter_texto_codificado_marcado(texto_criptografado,marcadores,tamanho);
}


char* obter_texto_codificado_marcado(int texto_criptografado[2][500], int marcadores[2][500], int tamanho) {
    static char texto_codificado[5000]; 
    int colunas = tamanho / 2;
    int pos = 0;

    for (int i = 0; i < colunas; i++) {
        for (int linha = 0; linha < 2; linha++) {
            int valor = texto_criptografado[linha][i];
            int marcador = marcadores[linha][i];

            pos += sprintf(&texto_codificado[pos], "%d", valor);

            if (marcador != 0) {
                pos += sprintf(&texto_codificado[pos], "%d", marcador);
            }

            texto_codificado[pos++] = ' ';
        }
    }

    texto_codificado[pos - 1] = '\0'; 
    return texto_codificado;
}



// ======================= DESCRIPTOGRAFAR =======================



