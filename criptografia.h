#ifndef CRIPTOGRAFIA_H
#define CRIPTOGRAFIA_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "auxiliar.h"

#define MOD 29
#define MAX_COLS 500

// ===================== VARIÁVEIS GLOBAIS =====================
extern char alfabeto[];
extern int alfabeto_tam;

// ===================== PREPARAÇÃO DO TEXTO =====================
void deixar_maiusculo(char *texto);
int detectar_acento(char letra);
void tirar_acento(char *texto, int *tamanho, int marcadores[2][MAX_COLS]);

// ===================== ENTRADA E NUMERAÇÃO =====================
void obter_texto(char *texto, int *tamanho, int marcadores[2][MAX_COLS]);
void numerar_texto(char *texto, int tamanho, int texto_numerado[2][MAX_COLS]);

// ===================== CRIPTOGRAFIA =====================
void criptografar(int matriz_cript[2][2], int texto_enumerado[2][MAX_COLS], int texto_criptografado[2][MAX_COLS], int tamanho, int marcadores[2][MAX_COLS]);
char* obter_texto_codificado_marcado(int texto_criptografado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho);

// ===================== DESCRIPTOGRAFIA =====================
const char* aplicar_acento(char base, int marcador);
void descriptografar(int matriz_inv[2][2], int texto_criptografado[2][MAX_COLS], int texto_numerado[2][MAX_COLS], int tamanho);
char* obter_texto_descriptografado(int texto_numerado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho);
static void concatenar(char *destino, const char *origem, size_t tamanho_max);
#endif // CRIPTOGRAFIA_H