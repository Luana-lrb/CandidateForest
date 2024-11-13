#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char TipoChave[10];

typedef struct  candidatoArv{
    char estado[3];
    char cidade[50];
    char numeroUrna[6];
    char cargo[13];
    char nome[50];
    char nomeNaUrna[50];
    char partido[20];
    char genero[10];
    char escolaridade[35];
    char raca[14];
} CandidatoArv;

typedef struct No *Apontador;
typedef Apontador TipoDicionario;

typedef struct No {
  CandidatoArv *candidato;
  Apontador Esq, Dir;
} No;

void lerEPreencherArv(FILE *file, Apontador *arv);
void Inicializa(Apontador *Dicionario);
int Vazio(Apontador *Dicionario);
void imprimeCentral(Apontador p);
void imprimeEstado(Apontador p, char *estado);
void imprimeCidade(Apontador p, char *cidade);
void imprimeCand(Apontador p, char *candidato, char *nome);
int imprimeCandidatoArv(CandidatoArv *candidato);
TipoDicionario arvBin_Estado(char *estado, Apontador p);
TipoDicionario arvBin_Cidade(char *estado, char *cidade, Apontador p);
TipoDicionario arvBin_Candidato(char *estado, char *cidade, char *numeroUrna, Apontador p);

int compFiltroArvBin(Apontador p, char *filtro, int chave);
void imprimeEstadoArvBin_filtro(Apontador p, char *estado, char *filtro, int chave);
void imprimeCidadeArvBin_filtro(Apontador p, char *cidade, char *filtro, int chave);

void strUpper(char *entrada);
int maiorArvBin(CandidatoArv *a, CandidatoArv *b);

void insereArv(Apontador *p, CandidatoArv *c);

void liberarArvoreBin(Apontador p);