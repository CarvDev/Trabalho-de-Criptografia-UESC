#include <stdlib.h>
#include <wchar.h>

#define MIN 1 // número mínimo capaz de ser gerado aleatoriamente
#define MAX 28 // número máximo capaz de ser gerado aleatoriamente

void limpar_buffer() {
    wint_t c; // wint_t para "wide int type"
    
    // Lê e descarta todos os caracteres até encontrar o '\n'
    while ((c = getwchar()) != L'\n' && c != WEOF);
}

int gerar_num() {
    int num = rand() % MAX + MIN;
    
    return num;
}

void limpar_tela(int op) {
    if (op == 1){
        wprintf(L"\n Aperte Enter para continuar ");
        getwchar();
    }
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}