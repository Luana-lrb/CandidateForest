#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "AVL.h"
#include "binSearch.h"
#include "arvBin.h"

char menuPrincipal();
void menuListagens(char *op);
void strUpper(char *entrada);
void switchList_estado(char op, Candidato *vetor, int MAX, TipoDicionario raiz, TipoDicionario *arv, ArvAVL *arvAVL, ArvAVL raizAVL );
void switchList_cidade(char op, Candidato *vetor, int MAX, TipoDicionario raiz, TipoDicionario *arv, ArvAVL *arvAVL, ArvAVL raizAVL );






            