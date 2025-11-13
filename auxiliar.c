#include <stdio.h>
#include <stdlib.h>

#define MIN 1 // número mínimo capaz de ser gerado aleatoriamente
#define MAX 28 // número máximo capaz de ser gerado aleatoriamente

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int gerar_num() {
    int num = rand() % MAX + MIN;
    
    return num;
}

void limpar_tela(int op) {
    if (op == 1){
        printf("\n Aperte Enter para continuar ");
        getchar();
    }
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}