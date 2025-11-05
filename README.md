# Trabalho de Criptografia - PR2

Este repositório contém o código-fonte para o trabalho da disciplina, focado na implementação de um sistema de criptografia baseado em matrizes (Criptografia de Hill).

## Objetivo do Projeto

Desenvolver um programa em C que apresente um menu interativo para criptografar e descriptografar mensagens.

## Funcionalidades (Menu Principal)

O programa deve oferecer as seguintes opções:

1.  **Criar uma matriz de criptografia:** Gera uma matriz válida (invertível) e armazena sua matriz inversa.
2.  **Criar um texto para ser criptografado:** Permite ao usuário inserir a mensagem original.
3.  **Criptografar Texto:** Criptografa a mensagem (opção 2) usando a matriz (opção 1).
4.  **Descriptografar Texto:** Descriptografa a mensagem (opção 3) usando a matriz inversa.
5.  **Sair do sistema.**

## Regras de Execução

* **Restrição de Menu:** As opções 3 (Criptografar) e 4 (Descriptografar) devem estar **bloqueadas** e retornar uma mensagem de erro se a matriz de criptografia (opção 1) ainda não tiver sido criada.
* **Restrição de Descriptografia:** A opção 4 só pode ser usada se o texto já tiver sido criptografado.
* **Saída (Criptografar):** Ao selecionar a opção 3, o programa deve mostrar o texto original e o texto criptografado.
* **Saída (Descriptografar):** Ao selecionar a opção 4, o programa deve mostrar o texto criptografado e o resultado da descriptografia.

## Requisitos de Implementação

* **Separação de Arquivos:** As funções para operações de matriz (calcular determinante, encontrar matriz adjunta, calcular inversa, etc.) **não** devem ser implementadas no mesmo arquivo da função `main()`.
* **Arquivo Header:** Deve ser criado um arquivo de cabeçalho (ex: `matrizes.h`) para declarar as funções de matriz.
* **Funções Principais:**
    * `Criptografa`: Deve receber a matriz de criptografia e o texto original.
    * `Descriptografa`: Deve receber o texto criptografado e a matriz inversa.

## Base Teórica (Resumo)

O método utiliza a "Base Teórica" fornecida:

1.  **Conversão:** O texto é convertido em números (A=01, B=02, ..., #=29).
2.  **Matriz M (Mensagem):** Os números são organizados em uma matriz $M$. O número de linhas de $M$ deve ser igual à ordem da matriz de criptografia (ex: 2 linhas se a matriz A for 2x2).
3.  **Criptografar (N):** $N = AM$ (Matriz $N$ é a mensagem criptografada).
4.  **Descriptografar (M):** $M = A^{-1}N$ (A multiplicação pela inversa recupera a matriz $M$ original).
