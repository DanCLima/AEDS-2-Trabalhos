#include <iostream>
#include <fstream>

using namespace std;

#ifndef FUNCOES_H
#define FUNCOES_H

void clarear(string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);
void negativo (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);
void esquerda(string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);
void inversaoh (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);
void inversaov (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);
void escurecer (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);
void direita (string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);
void bordas(string nomearq, string cabecalho, int lin, int col, int tonalidade, int mat[600][600]);


#endif /* FUNCOES_H */

