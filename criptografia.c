#include "matrizes.h"
#include "criptografia.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

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
    if (strchr("Ç",letra)) return -5;
    return 0; 
}

void tirar_acento(char *texto, int *tamanho, int marcadores[2][500]) {
    int metade = *tamanho / 2;

    for (int i = 0; i < *tamanho && texto[i] != '\0'; i++) {
        unsigned char letra = texto[i];
        int marcador = detectar_acento(letra);

        if (marcador != 0) {
            if (strchr("ÃÁÂÀ", letra)) letra = 'A';
            else if (strchr("ÕÓÔÒ", letra)) letra = 'O';
            else if (strchr("ÉÊÈ", letra)) letra = 'E';
            else if (strchr("ÍÎÌ", letra)) letra = 'I';
            else if (strchr("ÚÛÙ", letra)) letra = 'U';
            else if (strchr("Ç", letra)) letra = 'C';
        }

        texto[i] = letra;

        if (i < metade) {
            marcadores[0][i] = marcador;
        } else {
            marcadores[1][i - metade] = marcador;
        }
    }

    texto[*tamanho] = '\0';
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


void numerar_texto(char *texto, int tamanho, int texto_numerado[2][500]) {

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

wchar_t aplicar_acento(wchar_t base, int marcador) {
    if (marcador == -1 && base == L'A') return L'Ã';
    if (marcador == -1 && base == L'O') return L'Õ';

    if (marcador == -2 && base == L'A') return L'Á';
    if (marcador == -2 && base == L'E') return L'É';
    if (marcador == -2 && base == L'I') return L'Í';
    if (marcador == -2 && base == L'O') return L'Ó';
    if (marcador == -2 && base == L'U') return L'Ú';

    if (marcador == -3 && base == L'A') return L'Â';
    if (marcador == -3 && base == L'E') return L'Ê';
    if (marcador == -3 && base == L'I') return L'Î';
    if (marcador == -3 && base == L'O') return L'Ô';
    if (marcador == -3 && base == L'U') return L'Û';

    if (marcador == -4 && base == L'A') return L'À';
    if (marcador == -4 && base == L'E') return L'È';
    if (marcador == -4 && base == L'I') return L'Ì';
    if (marcador == -4 && base == L'O') return L'Ò';
    if (marcador == -4 && base == L'U') return L'Ù';

    if (marcador == -5 && base == L'C') return L'Ç';

    return base;
}

void descriptografar(float matriz_inv[2][2], int texto_criptografado[2][500], int texto_numerado[2][500], int tamanho) {
    int colunas = tamanho / 2;

    for (int i = 0; i < colunas; i++) {
        int a = texto_criptografado[0][i];
        int b = texto_criptografado[1][i];

        texto_numerado[0][i] = matriz_inv[0][0] * a + matriz_inv[0][1] * b;
        texto_numerado[1][i] = matriz_inv[1][0] * a + matriz_inv[1][1] * b;
    }
}

char* obter_texto_descriptografado(int texto_numerado[2][500], int marcadores[2][500], int tamanho) {
    static char texto_final[1000];
    int metade = tamanho / 2;

    for (int i = 0; i < metade; i++) {
        
        int indice1 = texto_numerado[0][i] - 1;
        int indice2 = texto_numerado[1][i] - 1;

        
        char letra1, letra2;

        if (indice1 >= 0 && indice1 < alfabeto_tam) {
            letra1 = alfabeto[indice1];
        } else {
            letra1 = '?';
        }

        if (indice2 >= 0 && indice2 < alfabeto_tam) {
            letra2 = alfabeto[indice2];
        } else {
            letra2 = '?';
        }

        
        texto_final[2 * i]     = aplicar_acento(letra1, marcadores[0][i]);
        texto_final[2 * i + 1] = aplicar_acento(letra2, marcadores[1][i]);
    }


    texto_final[tamanho] = '\0';
    return texto_final;
}


