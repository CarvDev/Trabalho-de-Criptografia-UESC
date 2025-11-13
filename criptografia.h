#ifndef CRIPTOGRAFIA_H
#define CRIPTOGRAFIA_H

// <wchar.h> é necessário para os tipos wchar_t e size_t
#include <wchar.h> 
#include "auxiliar.h"

#define MOD 29
#define MAX_COLS 500

// ===================== VARIÁVEIS GLOBAIS =====================
extern wchar_t alfabeto[];
extern int alfabeto_tam;

// ===================== PREPARAÇÃO DO TEXTO =====================
void deixar_maiusculo(wchar_t *texto);
int detectar_acento(wchar_t letra);
void tirar_acento(wchar_t *texto, int *tamanho, int marcadores[2][MAX_COLS]);

// ===================== ENTRADA E NUMERAÇÃO =====================
void obter_texto(wchar_t *texto, int *tamanho, int marcadores[2][MAX_COLS]);
void numerar_texto(wchar_t *texto, int tamanho, int texto_numerado[2][MAX_COLS]);

// ===================== CRIPTOGRAFIA =====================
void criptografar(int matriz_cript[2][2], int texto_enumerado[2][MAX_COLS], int texto_criptografado[2][MAX_COLS], int tamanho, int marcadores[2][MAX_COLS]);
char* obter_texto_codificado_marcado(int texto_criptografado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho);

// ===================== DESCRIPTOGRAFIA =====================
const wchar_t* aplicar_acento(wchar_t base, int marcador);
void descriptografar(int matriz_inv[2][2], int texto_criptografado[2][MAX_COLS], int texto_numerado[2][MAX_COLS], int tamanho);
const wchar_t* obter_texto_descriptografado(int texto_numerado[2][MAX_COLS], int marcadores[2][MAX_COLS], int tamanho);

// A função 'concatenar' é static e não deve estar no .h

#endif // CRIPTOGRAFIA_H