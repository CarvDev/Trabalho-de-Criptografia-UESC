#include "criptografia.h"
#include "auxiliar.h"

#include <stdio.h>
#include <string.h>
#include <wchar.h>  // Para wchar_t, wcschr, fgetws, wcslen, etc.
#include <wctype.h> // Para towupper

#define MOD 29
#define MAX_COLS 500

wchar_t alfabeto[] = {
    L'A',L'B',L'C',L'D',L'E',L'F',L'G',L'H',L'I',L'J',L'K',L'L',L'M',
    L'N',L'O',L'P',L'Q',L'R',L'S',L'T',L'U',L'V',L'W',L'X',L'Y',L'Z',
    L'.',L',', L'#'
};
int alfabeto_tam = 29;

static int mod_pos(int x) {
    x %= MOD;
    if (x < 0) x += MOD;
    return x; 
}

/* ============== OPERAÇÕES PARA PREPARAR O TEXTO PARA CRIPTOGRAFIA ============== */
void deixar_maiusculo(wchar_t *texto) {
    for (int i = 0; texto[i] != L'\0'; i++) texto[i] = towupper(texto[i]);
}

int detectar_acento(wchar_t letra) {
    if (wcschr(L"ÃÕ", letra)) return -1;
    if (wcschr(L"ÁÉÍÓÚ", letra)) return -2;
    if (wcschr(L"ÂÊÎÔÛ", letra)) return -3;
    if (wcschr(L"ÀÈÌÒÙ", letra)) return -4;
    if (wcschr(L"Ç", letra)) return -5;
    return 0;
}

void tirar_acento(wchar_t *texto, int *tamanho, int marcadores[2][MAX_COLS]) {
    if ((*tamanho) % 2 != 0) {
        (*tamanho)++;
        texto[*tamanho] = L'#';
        (*tamanho)++;
        texto[*tamanho] = L'\0';
    }

    int metade = *tamanho / 2;

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < MAX_COLS; j++)
            marcadores[i][j] = 0;

    for (int i = 0; i < *tamanho && texto[i] != L'\0'; i++) {
        wchar_t letra = texto[i];
        int marcador = detectar_acento(letra);

        if (marcador != 0) {
            if (wcschr(L"ÃÁÂÀ", letra)) letra = L'A';
            else if (wcschr(L"ÕÓÔÒ", letra)) letra = L'O';
            else if (wcschr(L"ÉÊÈ", letra)) letra = L'E';
            else if (wcschr(L"ÍÎÌ", letra)) letra = L'I';
            else if (wcschr(L"ÚÛÙ", letra)) letra = L'U';
            else if (wcschr(L"Ç", letra)) letra = L'C';
        }

        texto[i] = letra;

        if (i % 2 == 0) {
            marcadores[0][i / 2] = marcador;
        } else {
            marcadores[1][i / 2] = marcador;
        }
    }

    texto[*tamanho] = L'\0';
}

/* ============ OPÇÃO 2 DO MENU ============ */
void obter_texto(wchar_t *texto, int *tamanho, int marcadores[2][MAX_COLS]) {
    wprintf(L"\nDigite o texto que deseja criptografar:\n > ");
    
    // fgetws para ler wide strings
    if (!fgetws(texto, *tamanho, stdin)) {
        texto[0] = L'\0';
        *tamanho = 0;
        return;
    }
    
    *tamanho = wcslen(texto); 
    if (*tamanho > 0 && texto[*tamanho - 1] == L'\n') {
        texto[*tamanho - 1] = L'\0';
        (*tamanho)--;
    }

    deixar_maiusculo(texto);
    tirar_acento(texto, tamanho, marcadores);
}

void numerar_texto(wchar_t *texto, int tamanho, int texto_numerado[2][MAX_COLS]) {
    if (tamanho % 2 != 0) {
        texto[tamanho] = L'#';
        tamanho++;
        texto[tamanho] = L'\0';
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

const wchar_t* obter_texto_codificado_marcado(int texto_criptografado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho) {
    static wchar_t texto_codificado[5000];
    int colunas = tamanho / 2;
    int pos = 0; // Posição atual na string

    // Garante que a string está vazia antes de começar
    texto_codificado[0] = L'\0';

    for (int i = 0; i < colunas; i++) {
        for (int linha = 0; linha < 2; linha++) {
            int valor = texto_criptografado[linha][i];
            int marcador = marcadores[linha][i];

            // Condicional que evita estourar o buffer, deixando espaço para os próximos números e '\0'
            if (pos >= 4950) break; 

            pos += swprintf(&texto_codificado[pos], 5000 - pos, L"%d", valor);

            if (marcador != 0) {
                if (pos >= 4950) break;

                pos += swprintf(&texto_codificado[pos], 5000 - pos, L"%d", marcador);
            }

            if (pos >= 4950) break;

            texto_codificado[pos++] = L' ';
        }
    }

    if (pos > 0) texto_codificado[pos - 1] = L'\0'; 
    else texto_codificado[0] = L'\0';

    return texto_codificado;
}

/* ======================= DESCRIPTOGRAFAR ======================= */
const wchar_t* aplicar_acento(wchar_t base, int marcador) {
    if (marcador == -1 && base == L'A') return L"Ã";
    if (marcador == -1 && base == L'O') return L"Õ";

    if (marcador == -2 && base == L'A') return L"Á";
    if (marcador == -2 && base == L'E') return L"É";
    if (marcador == -2 && base == L'I') return L"Í";
    if (marcador == -2 && base == L'O') return L"Ó";
    if (marcador == -2 && base == L'U') return L"Ú";

    if (marcador == -3 && base == L'A') return L"Â";
    if (marcador == -3 && base == L'E') return L"Ê";
    if (marcador == -3 && base == L'I') return L"Î";
    if (marcador == -3 && base == L'O') return L"Ô";
    if (marcador == -3 && base == L'U') return L"Û";

    if (marcador == -4 && base == L'A') return L"À";
    if (marcador == -4 && base == L'E') return L"È";
    if (marcador == -4 && base == L'I') return L"Ì";
    if (marcador == -4 && base == L'O') return L"Ò";
    if (marcador == -4 && base == L'U') return L"Ù";

    if (marcador == -5 && base == L'C') return L"Ç";

    static wchar_t s[2] = {0,0};
    s[0] = base;
    s[1] = L'\0';
    return s;
}
static void concatenar(wchar_t *destino, const wchar_t *origem, size_t tamanho_max) {
    size_t tamanho_destino = wcslen(destino);
    size_t tamanho_origem = wcslen(origem);

    if (tamanho_destino + tamanho_origem + 1 > tamanho_max) {
        if (tamanho_destino < tamanho_max - 1) {
            wcsncat(destino, origem, tamanho_max - tamanho_destino - 1);
        }
    } else {
        wcscat(destino, origem);
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

const wchar_t* obter_texto_descriptografado(int texto_numerado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho) {
    static wchar_t texto_final[2000];
    texto_final[0] = L'\0';
    int metade = tamanho / 2;

    for (int i = 0; i < metade; i++) {
        int indice1 = texto_numerado[0][i] - 1;
        int indice2 = texto_numerado[1][i] - 1;
        wchar_t base1 = (indice1 >= 0 && indice1 < alfabeto_tam) ? alfabeto[indice1] : L'?';
        wchar_t base2 = (indice2 >= 0 && indice2 < alfabeto_tam) ? alfabeto[indice2] : L'?';
        concatenar(texto_final, aplicar_acento(base1, marcadores[0][i]), 2000); 
        concatenar(texto_final, aplicar_acento(base2, marcadores[1][i]), 2000); 
        // tamanho_max não pode mais receber sizeof(). Isso causaria um erro, uma vez que o tamanho em bytes de um wchar_t é diferente 
    }
    return texto_final;
}
