#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct  candidato{
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
} Candidato;

void lerEPreencher(FILE *file, Candidato vetor[]);
void shellSort(Candidato vet[], int n);
int binSearch_Estado(Candidato vetor[], int inicio, int fim, char *estado, int chave);
int binSearch_Cidade(Candidato vetor[], int inicio, int fim, char *estado, char *cidade, int chave);
int binSearch_Candidato(Candidato vetor[], int inicio, int fim, char *estado, char *cidade, char *numeroUrna);
int imprimeCandidato(Candidato candidato);
int compFiltroBin(Candidato vetor[], int pos, char *filtro, int chave);
void imprimeEstadoBin_filtro(Candidato vetor[], char *estado, char *filtro, int MAX, int chave);
void imprimeCidadeBin_filtro(Candidato vetor[],char *estado, char *cidade, char *filtro, int MAX, int chave);
int maiorCand(Candidato a, Candidato b);


