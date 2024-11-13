#include "arvBin.h"

void lerEPreencherArv(FILE *file, Apontador *arv){
    char linha[252]; 
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
    long int i = 0;

    // Preencher um registro e inserir ele na arvore, apan

    //Tiramos a primeira linha q não tem conteudo
    if(i == 0) fgets(linha, sizeof(linha), file);

    while(fgets(linha, sizeof(linha), file) != NULL) { 
        
        CandidatoArv *c = (CandidatoArv *)malloc(sizeof(CandidatoArv));
        
        strcpy(estado,strtok(linha,";"));
        strcpy(cidade,strtok(NULL,";"));
        strcpy(numeroUrna,strtok(NULL,";"));
        strcpy(cargo, strtok(NULL,";"));
        strcpy(nome, strtok(NULL,";"));
        strcpy(nomeNaUrna, strtok(NULL,";"));
        strcpy(partido, strtok(NULL,";"));
        strcpy(genero, strtok(NULL,";"));
        strcpy(escolaridade, strtok(NULL,";"));
        strcpy(raca, strtok(NULL,";"));
        
        strcpy(c->estado,estado);
        strcpy(c->cidade,cidade);
        strcpy(c->numeroUrna,numeroUrna);
        strcpy(c->cargo, cargo );
        strcpy(c->nome, nome);
        strcpy(c->nomeNaUrna, nomeNaUrna);
        strcpy(c->partido, partido);
        strcpy(c->genero, genero);
        strcpy(c->escolaridade, escolaridade);
        strcpy(c->raca, raca);
    
        i++;

        insereArv(arv, c);
    }

    fclose(file);
}

void insereArv(Apontador *p, CandidatoArv *c){ 

    if(*p == NULL){
        No *novo;
        novo = (No*)malloc(sizeof(No));
        if(novo == NULL){
            return;
        } 
        novo->candidato = c;
        novo->Esq = NULL;
        novo->Dir = NULL;
        *p = novo;
        return;
    }

    No *atual = *p;
    int cmp = maiorArvBin(c, atual->candidato);
    if(cmp == 0) insereArv(&(atual->Esq), c);
    else if(cmp == 1)insereArv(&(atual->Dir), c);

}


int maiorArvBin(CandidatoArv *a, CandidatoArv *b){ // a > b = 1 ; a < b = 0 ; a == b = 2
    int cmp;
    cmp = strcmp(a->estado, b->estado); 
    if (cmp < 0) return 0;   
    else if (cmp > 0) return 1;
    else {
        cmp = strcmp(a->cidade, b->cidade);
        if (cmp < 0) return 0; 
        else if (cmp > 0) return 1;
        else{
            cmp = strcmp(a->numeroUrna, b->numeroUrna);
            if (cmp < 0) return 0; 
            else if (cmp > 0) return 1;   
        }
    }
    return 2; 
}


void Inicializa(Apontador *Dicionario){
    Dicionario = NULL;
}

int Vazio(Apontador *Dicionario){
    return (Dicionario == NULL); 
}

void imprimeCentral(Apontador p){
    if (p == NULL) return;
    imprimeCentral (p->Esq);
    imprimeCandidatoArv(p->candidato);
    imprimeCentral (p->Dir);
}

void imprimeEstado(Apontador p, char *estado){
    if (p == NULL) return;
    imprimeEstado (p->Esq, estado);
    int cmp = strcmp(estado, p->candidato->estado);
    if(cmp == 0) imprimeCandidatoArv(p->candidato);
    imprimeEstado (p->Dir, estado);
}

void imprimeCidade(Apontador p, char *cidade){
    if (p == NULL) return;
    imprimeCidade (p->Esq, cidade);
    int cmp = strcmp(cidade, p->candidato->cidade);
    if(cmp == 0) imprimeCandidatoArv(p->candidato);
    imprimeCidade (p->Dir, cidade);
}

TipoDicionario arvBin_Estado(char *estado, Apontador p){ 
    if (p == NULL) { 
        printf("Erro : Registro nao esta presente na arvore\n");
        return NULL;
    }
    if (strcmp(estado, p->candidato->estado) < 0) { 
        arvBin_Estado(estado, p->Esq);
    }
    if (strcmp(estado, p->candidato->estado) > 0)
        arvBin_Estado(estado, p->Dir);
    else
        return p; // retorna a raiz que contém as subárvores com o estado procurado
}

TipoDicionario arvBin_Cidade(char *estado, char *cidade, Apontador p){ 
    if (p == NULL) { 
        printf("Erro : Registro nao esta presente na arvore\n");
        return NULL;
    }
    if (strcmp(estado, p->candidato->estado) < 0) { 
        arvBin_Cidade(estado, cidade, p->Esq);
    }
    else if (strcmp(estado, p->candidato->estado) > 0)
        arvBin_Cidade(estado, cidade, p->Dir);
    else{
        if (strcmp( cidade, p->candidato->cidade) < 0)
            arvBin_Cidade(estado, cidade, p->Esq);

        else if (strcmp(cidade, p->candidato->cidade) > 0)
            arvBin_Cidade(estado, cidade, p->Dir);
        else 
            return p;
    }   
}

TipoDicionario arvBin_Candidato(char *estado, char *cidade, char *numeroUrna, Apontador p){
    if (p == NULL) { 
        printf("Erro : Registro nao esta presente na arvore\n");
        return NULL;
    }
    if (strcmp(estado, p->candidato->estado) < 0) { 
        arvBin_Candidato(estado, cidade, numeroUrna, p->Esq);
    }
    else if (strcmp(estado, p->candidato->estado) > 0)
        arvBin_Candidato(estado, cidade, numeroUrna, p->Dir);
    else{
        if (strcmp( cidade, p->candidato->cidade) < 0)
            arvBin_Candidato(estado, cidade, numeroUrna, p->Esq);

        else if (strcmp(cidade, p->candidato->cidade) > 0)
            arvBin_Candidato(estado, cidade, numeroUrna, p->Dir);
        else {
            if (strcmp( numeroUrna, p->candidato->numeroUrna) < 0)
                arvBin_Candidato(estado, cidade, numeroUrna, p->Esq);

            else if (strcmp(numeroUrna, p->candidato->numeroUrna) > 0)
                arvBin_Candidato(estado, cidade, numeroUrna, p->Dir);
            else 
                return p;
        }     
    }
}

int imprimeCandidatoArv(CandidatoArv *candidato){
    printf("\nUF: %s\nCidade: %s\nNumero de Urna: %s\nCargo: %s\nNome:%s\nNome na urna: %s\nPartido: %s\nGenero: %s\nEscolaridade: %s\nRaca/etnia: %s\n", 
            candidato->estado,candidato->cidade, candidato->numeroUrna, candidato->cargo, candidato->nome, candidato->nomeNaUrna, 
           candidato->partido, candidato->genero, candidato->escolaridade, candidato->raca); 
    return 0;
}

void imprimeCand(Apontador p, char *numeroUrna, char *cidade){
    if (p == NULL) return;
    int cmp = strcmp(numeroUrna, p->candidato->numeroUrna);
    int cid = strcmp(cidade, p->candidato->cidade);
    if(cmp == 0 && cid == 0) imprimeCandidatoArv(p->candidato);
    imprimeCand (p->Esq, numeroUrna, cidade);
    imprimeCand (p->Dir, numeroUrna, cidade);
}

int compFiltroArvBin(Apontador p, char *filtro, int chave){
    if(chave == 1) return strcmp(p->candidato->genero, filtro);
    else if(chave == 2) return strcmp(p->candidato->partido, filtro);
    else if(chave == 3) return strcmp(p->candidato->raca, filtro);
}

void imprimeEstadoArvBin_filtro(Apontador p, char *estado, char *filtro, int chave){
    if (p == NULL) return;
    imprimeEstadoArvBin_filtro (p->Esq, estado, filtro, chave);
    int cmp = strcmp(estado, p->candidato->estado);
    if(cmp == 0 && (compFiltroArvBin(p, filtro, chave) == 0) ){
        imprimeCandidatoArv(p->candidato);
    }
    imprimeEstadoArvBin_filtro (p->Dir, estado, filtro, chave);
}

void imprimeCidadeArvBin_filtro(Apontador p, char *cidade, char *filtro, int chave){
    if (p == NULL) return;
    imprimeCidadeArvBin_filtro (p->Esq, cidade, filtro, chave);
    int cmp = strcmp(cidade, p->candidato->cidade);
    if(cmp == 0 && (compFiltroArvBin(p, filtro, chave) == 0) ){
        imprimeCandidatoArv(p->candidato);
    } 
    imprimeCidadeArvBin_filtro (p->Dir, cidade, filtro, chave);
}


void liberarArvoreBin(Apontador p){
    if (p == NULL) return;
    liberarArvoreBin (p->Esq);
    liberarArvoreBin (p->Dir);
    free(p);
}
