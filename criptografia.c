#include "criptografia.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "auxiliar.h"

#define MOD 29
#define MAX_COLS 500

char alfabeto[] = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    '.', ',', '#'
};
int alfabeto_tam = 29;

static int mod_pos(int x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x; 
}

/* ============== OPERAÇÕES PARA PREPARAR O TEXTO PARA CRIPTOGRAFIA ============== */
void deixar_maiusculo(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) texto[i] = toupper((unsigned char)texto[i]);
}

int detectar_acento(char letra) {
    if (strchr("ÃÕ", letra)) return -1;
    if (strchr("ÁÉÍÓÚ", letra)) return -2;
    if (strchr("ÂÊÎÔÛ", letra)) return -3;
    if (strchr("ÀÈÌÒÙ", letra)) return -4;
    if (strchr("Ç", letra)) return -5;
    return 0;
}

void tirar_acento(char *texto, int *tamanho, int marcadores[2][MAX_COLS]) {
    if ((*tamanho) % 2 != 0) {
        (*tamanho)++;
        texto[*tamanho] = '#';
        (*tamanho)++;
        texto[*tamanho] = '\0';
    }

    int metade = *tamanho / 2;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < MAX_COLS; j++)
            marcadores[i][j] = 0;

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

        if (i < metade) marcadores[0][i] = marcador;
        else marcadores[1][i - metade] = marcador;
    }

    texto[*tamanho] = '\0';
}

/* ============ OPÇÃO 2 DO MENU ============ */
void obter_texto(char *texto, int *tamanho, int marcadores[2][MAX_COLS]) {
    printf("\nDigite o texto que deseja criptografar:\n > ");
    if (!fgets(texto, *tamanho + 2, stdin)) {
        texto[0] = '\0';
        *tamanho = 0;
        return;
    }
    *tamanho = strlen(texto);
    if (*tamanho > 0 && texto[*tamanho - 1] == '\n') {
        texto[*tamanho - 1] = '\0';
        (*tamanho)--;
    }

    deixar_maiusculo(texto);
    tirar_acento(texto, tamanho, marcadores);
}

void numerar_texto(char *texto, int tamanho, int texto_numerado[2][MAX_COLS]) {
    if (tamanho % 2 != 0) {
        texto[tamanho] = '#';
        tamanho++;
        texto[tamanho] = '\0';
    }

    int colunas = tamanho / 2;

    for (int i = 0; i < colunas; i++) {
        int indice_char1 = i * 2;
        int indice_char2 = i * 2 + 1;

        int valor1 = 29;
        for (int j = 0; j < alfabeto_tam; j++) {
            if (texto[indice_char1] == alfabeto[j]) {
                valor1 = j + 1;
                break;
            }
        }

        int valor2 = 29;
        for (int j = 0; j < alfabeto_tam; j++) {
            if (texto[indice_char2] == alfabeto[j]) {
                valor2 = j + 1;
                break;
            }
        }

        texto_numerado[0][i] = valor1;
        texto_numerado[1][i] = valor2;
    }
}

/* ============ OPÇÃO 3 DO MENU ============ */
void criptografar(int matriz_cript[2][2],
                  int texto_enumerado[2][MAX_COLS],
                  int texto_criptografado[2][MAX_COLS],
                  int tamanho, int marcadores[2][MAX_COLS]) {
    int colunas = tamanho / 2;

    for (int i = 0; i < colunas; i++) {
        int x1 = texto_enumerado[0][i];
        int y1 = texto_enumerado[1][i];

        int x = x1 - 1;
        int y = y1 - 1;

        int c0 = matriz_cript[0][0] * x + matriz_cript[0][1] * y;
        int c1 = matriz_cript[1][0] * x + matriz_cript[1][1] * y;

        c0 = mod_pos(c0);
        c1 = mod_pos(c1);

        texto_criptografado[0][i] = c0 + 1;
        texto_criptografado[1][i] = c1 + 1;
    }
}

char* obter_texto_codificado_marcado(int texto_criptografado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho) {
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

    if (pos > 0) texto_codificado[pos - 1] = '\0';
    else texto_codificado[0] = '\0';
    return texto_codificado;
}

/* ======================= DESCRIPTOGRAFAR ======================= */
const char* aplicar_acento(char base, int marcador) {
    if (marcador == -1 && base == 'A') return "Ã";
    if (marcador == -1 && base == 'O') return "Õ";

    if (marcador == -2 && base == 'A') return "Á";
    if (marcador == -2 && base == 'E') return "É";
    if (marcador == -2 && base == 'I') return "Í";
    if (marcador == -2 && base == 'O') return "Ó";
    if (marcador == -2 && base == 'U') return "Ú";

    if (marcador == -3 && base == 'A') return "Â";
    if (marcador == -3 && base == 'E') return "Ê";
    if (marcador == -3 && base == 'I') return "Î";
    if (marcador == -3 && base == 'O') return "Ô";
    if (marcador == -3 && base == 'U') return "Û";

    if (marcador == -4 && base == 'A') return "À";
    if (marcador == -4 && base == 'E') return "È";
    if (marcador == -4 && base == 'I') return "Ì";
    if (marcador == -4 && base == 'O') return "Ò";
    if (marcador == -4 && base == 'U') return "Ù";

    if (marcador == -5 && base == 'C') return "Ç";

    static char s[2] = {0,0};
    s[0] = base;
    s[1] = '\0';
    return s;
}
static void concatenar(char *destino, const char *origem, size_t tamanho_max) {
    size_t tamanho_destino = strlen(destino);
    size_t tamanho_origem = strlen(origem);

    if (tamanho_destino + tamanho_origem + 1 > tamanho_max) {
        if (tamanho_destino < tamanho_max - 1) {
            strncat(destino, origem, tamanho_max - tamanho_destino - 1);
        }
    } else {
        strcat(destino, origem);
    }
}

void descriptografar(int matriz_inv[2][2], int texto_criptografado[2][MAX_COLS],
                    int texto_numerado[2][MAX_COLS], int tamanho) {
    int colunas = tamanho / 2;

    for (int i = 0; i < colunas; i++) {
        int a1 = texto_criptografado[0][i];
        int b1 = texto_criptografado[1][i];

        int a = a1 - 1;
        int b = b1 - 1;

        int r0 = matriz_inv[0][0] * a + matriz_inv[0][1] * b;
        int r1 = matriz_inv[1][0] * a + matriz_inv[1][1] * b;

        r0 = mod_pos(r0);
        r1 = mod_pos(r1);

        texto_numerado[0][i] = r0 + 1;
        texto_numerado[1][i] = r1 + 1;
    }
}

char* obter_texto_descriptografado(int texto_numerado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho) {
    static char texto_final[2000];
    texto_final[0] = '\0';
    int metade = tamanho / 2;

    for (int i = 0; i < metade; i++) {
        int indice1 = texto_numerado[0][i] - 1;
        int indice2 = texto_numerado[1][i] - 1;
        char base1 = (indice1 >= 0 && indice1 < alfabeto_tam) ? alfabeto[indice1] : '?';
        char base2 = (indice2 >= 0 && indice2 < alfabeto_tam) ? alfabeto[indice2] : '?';
        concatenar(texto_final, aplicar_acento(base1, marcadores[0][i]), sizeof(texto_final));
        concatenar(texto_final, aplicar_acento(base2, marcadores[1][i]), sizeof(texto_final));
    }
    return texto_final;
}
