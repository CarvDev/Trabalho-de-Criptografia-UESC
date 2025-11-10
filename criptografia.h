#ifndef CRIPTOGRAFIA_H
#define CRIPTOGRAFIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>

// ===================== VARIÁVEIS GLOBAIS =====================
extern char alfabeto[];
extern int alfabeto_tam;

// ===================== PREPARAÇÃO DO TEXTO =====================
void deixar_maiusculo(char *texto);
int detectar_acento(char letra);
void tirar_acento(char *texto, int *tamanho, int marcadores[2][500]);

// ===================== ENTRADA E NUMERAÇÃO =====================
void obter_texto(char *texto, int *tamanho, int marcadores[2][500]);
void numerar_texto(char *texto, int tamanho, int texto_numerado[2][500]);

// ===================== CRIPTOGRAFIA =====================
void criptografar(int matriz_cript[2][2], int texto_enumerado[2][500], int texto_criptografado[2][500], int tamanho, int marcadores[2][500]);
char* obter_texto_codificado_marcado(int texto_criptografado[2][500], int marcadores[2][500], int tamanho);

// ===================== DESCRIPTOGRAFIA =====================
wchar_t aplicar_acento(wchar_t base, int marcador);
void descriptografar(float matriz_inv[2][2], int texto_criptografado[2][500], int texto_numerado[2][500], int tamanho);
char* obter_texto_descriptografado(int texto_numerado[2][500], int marcadores[2][500], int tamanho);

#endif // CRIPTOGRAFIA_H
