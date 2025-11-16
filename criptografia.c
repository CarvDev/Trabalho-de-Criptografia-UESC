#include "criptografia.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>   
#include "auxiliar.h"
#include "UTF8.h"

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

// Verifica se um caractere pertence ao alfabeto do projeto.
int eh_do_alfabeto(char c) {

    for (int k = 0; k < alfabeto_tam; k++) {
        if (c == alfabeto[k]) {
            return 1; // Verdadeiro (é do alfabeto)
        }
    }
    return 0; // Falso (não é do alfabeto)
}

// Substitui deixar_maiusculo, detectar_acento e tirar_acento.
void normalizar_texto(char *texto, int *tamanho, int marcadores[2][MAX_COLS]) {
    int tam_original = *tamanho;
    char texto_normalizado[2000]; // Buffer temporário
    int j = 0; // Índice do texto normalizado (caracteres lógicos)
    int i = 0; // Índice do texto original (bytes)

    // 1. Limpa os marcadores
    for (int r = 0; r < 2; r++)
        for (int c = 0; c < MAX_COLS; c++)
            marcadores[r][c] = 0;

    // 2. Loop de normalização (lê bytes, escreve caracteres)
    while (i < tam_original) {
        unsigned char byte1 = (unsigned char)texto[i];
        int marcador = 0;
        char letra_final = '?'; // Default caso não seja do alfabeto

        // É um caractere ASCII simples (1 byte)?
        if (byte1 <= 127) {
            
            // Verifica se é um espaço
            if (byte1 == ' ') {
                letra_final = '#';
            } else {
                letra_final = toupper(byte1); // Converte para maiúscula
            }
            i++; // Avança 1 byte
        
        // É um caractere UTF-8 de 2 bytes (acentos)?
        // 0xC3 é um sinalizador padrão para todo primeiro bit de caractere acentuado
        // && i + 1 < tam_original previne overflow
        } else if (byte1 == 0xC3 && i + 1 < tam_original) {
            unsigned char byte2 = (unsigned char)texto[i+1];
            
            // Til
            if (byte2 == A_TIL || byte2 == a_til) { letra_final = 'A'; marcador = -1; } // Ã
            else if (byte2 == O_TIL || byte2 == o_til) { letra_final = 'O'; marcador = -1; } // Õ
            // Agudo
            else if (byte2 == A_AGUDO || byte2 == a_agudo) { letra_final = 'A'; marcador = -2; } // Á
            else if (byte2 == E_AGUDO || byte2 == e_agudo) { letra_final = 'E'; marcador = -2; } // É
            else if (byte2 == I_AGUDO || byte2 == i_agudo) { letra_final = 'I'; marcador = -2; } // Í
            else if (byte2 == O_AGUDO || byte2 == o_agudo) { letra_final = 'O'; marcador = -2; } // Ó
            else if (byte2 == U_AGUDO || byte2 == u_agudo) { letra_final = 'U'; marcador = -2; } // Ú
            // Circunflexo
            else if (byte2 == A_CIRC || byte2 == a_circ) { letra_final = 'A'; marcador = -3; } // Â
            else if (byte2 == E_CIRC || byte2 == e_circ) { letra_final = 'E'; marcador = -3; } // Ê
            else if (byte2 == I_CIRC || byte2 == i_circ) { letra_final = 'I'; marcador = -3; } // Î
            else if (byte2 == O_CIRC || byte2 == o_circ) { letra_final = 'O'; marcador = -3; } // Ô
            else if (byte2 == U_CIRC || byte2 == u_circ) { letra_final = 'U'; marcador = -3; } // Û
            // Grave
            else if (byte2 == A_GRAVE || byte2 == a_grave) { letra_final = 'A'; marcador = -4; } // À
            else if (byte2 == E_GRAVE || byte2 == e_grave) { letra_final = 'E'; marcador = -4; } // È
            else if (byte2 == I_GRAVE || byte2 == i_grave) { letra_final = 'I'; marcador = -4; } // Ì
            else if (byte2 == O_GRAVE || byte2 == o_grave) { letra_final = 'O'; marcador = -4; } // Ò
            else if (byte2 == U_GRAVE || byte2 == u_grave) { letra_final = 'U'; marcador = -4; } // Ù
            // Cedilha
            else if (byte2 == C_CEDILHA || byte2 == c_cedilha) { letra_final = 'C'; marcador = -5; } // Ç
            else {
                letra_final = '?'; // Para byte desconhecido
            }
            
            i += 2; // Avança 2 bytes
        
        // É outro tipo de caractere UTF-8 (3 ou 4 bytes) ou um byte inválido
        } else {
            letra_final = '?'; // Trata como lixo
            i++;
        }

        // 3. Salva apenas se for parte do alfabeto
        if (eh_do_alfabeto(letra_final)) {
            
            // Armazena no texto normalizado
            texto_normalizado[j] = letra_final;
            
            // Armazena o marcador na posição lógica correta
            int linha = j % 2;  // 0 para o primeiro char do par, 1 para o segundo
            int coluna = j / 2; // O índice do par (coluna da matriz)
            
            if (coluna < MAX_COLS) { // Prevenção de overflow
                marcadores[linha][coluna] = marcador;
            }
            
            j++;
        }
        // Se não for válido (espaço, etc), é simplesmente descartado (não incrementa 'j')
    }
    
    // 4. Termina a string normalizada
    texto_normalizado[j] = '\0';
    *tamanho = j; // O novo tamanho é o número de caracteres lógicos
    
    // 5. Adiciona padding (agora com o tamanho correto)
    if ((*tamanho) % 2 != 0) {
        texto_normalizado[*tamanho] = '#';
        (*tamanho)++;
        texto_normalizado[*tamanho] = '\0';
    }

    // 6. Copia de volta para o buffer original
    strcpy(texto, texto_normalizado);
}

/* ============ OPÇÃO 2 DO MENU ============ */
void obter_texto(char *texto, int *tamanho, int tamanho_buffer,  int marcadores[2][MAX_COLS],char **texto_original) {
    do {
        printf("\nDigite o texto que deseja criptografar:\n > ");
        if (!fgets(texto, tamanho_buffer, stdin)) {
            texto[0] = '\0';
            *tamanho = 0;
             return;
        }

        *tamanho = strlen(texto); // *tamanho se torna o tamanho real do texto
        if (*tamanho > 0 && texto[*tamanho - 1] == '\n') {
            texto[*tamanho - 1] = '\0';
            (*tamanho)--;
        }
        if (*tamanho == 0) {
            printf("\nTexto vazio! Não há nada a criptografar! Digite um texto válido!\n");
            limpar_tela(1);
        }
    
    } while (*tamanho == 0);

    *texto_original = malloc(*tamanho + 1);
    strcpy(*texto_original, texto);  

    normalizar_texto(texto, tamanho, marcadores);
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
                  int tamanho) {
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
