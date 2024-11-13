#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct  candidatoArvAVL{
    char estado[3];
    char cidade[50];
    char numeroUrna[6];
    char cargo[13];
    char nome[50];
    char nomeNaUrna[50];
    char partido[20];
    char genero[10];
    char escolaridade[35];
    char raca[15];
} CandidatoArvAVL;

typedef struct NoAVL {
    CandidatoArvAVL *info;
    int alt;
    struct NoAVL *fesq;
    struct NoAVL *fdir;
}NoAVL;

typedef struct NoAVL *ArvAVL;

void lerEPreencherArvAVL(FILE *file, ArvAVL *arv);
int insereArvAVL(ArvAVL *p, CandidatoArvAVL *c);
int alturaNo(NoAVL *no);
int maiorAlt(int x, int y);
int fatorBalanceamento_NO(struct NoAVL* no);
int maior(CandidatoArvAVL *a, CandidatoArvAVL *b);
void rotEE(ArvAVL *arv);
void rotDD(ArvAVL *arv);
void rotED(ArvAVL *arv);
void rotDE(ArvAVL *arv);
ArvAVL arvAVL_Estado(char *estado, ArvAVL p);
ArvAVL arvAVL_Cidade(char *estado, char *cidade, ArvAVL p);
void imprimeEstadoAVL(ArvAVL arv, char *estado);
void imprimeCidadeAVL(ArvAVL arv, char *cidade);
int imprimeCandidatoArvAVL(CandidatoArvAVL *candidato);
ArvAVL arvAVL_Candidato(char *estado, char *cidade, char *numeroUrna, ArvAVL p);
void imprimeEstadoAVL_filtro(ArvAVL arv, char *estado, char *filtro, int chave);
void imprimeCidadeAVL_filtro(ArvAVL arv, char *cidade, char *filtro, int chave);
int compFiltro(ArvAVL arv, char *filtro, int chave);
void liberarArvoreAVL(ArvAVL p);