#include "AVL.h"

void lerEPreencherArvAVL(FILE *file, ArvAVL *arv){
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
        
        CandidatoArvAVL *c = (CandidatoArvAVL *)malloc(sizeof(CandidatoArvAVL));
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

        insereArvAVL(arv, c);
    }

    fclose(file);
}

// Codigo do professor Backes
int insereArvAVL(ArvAVL *p, CandidatoArvAVL *c){ 
    int res;
    
    if(*p == NULL){
        NoAVL *novo;
        novo = (NoAVL*)malloc(sizeof(NoAVL));
        if(novo == NULL){
            return 0;
        }
        novo->info = c;
        novo->alt = 0;
        novo->fesq = NULL;
        novo->fdir = NULL;
        *p = novo;
        return 1;
    }

    
    NoAVL *atual = *p;
    int cmp = maior(c, atual->info);
    if(cmp == 0){ 
        if((res = insereArvAVL(&(atual->fesq), c)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(maior(c, (*p)->fesq->info ) == 0){   
                    rotEE(p);
                } else {
                    rotED(p);
                }
            }
        }
    }else if(cmp == 1){
        if((res = insereArvAVL(&(atual->fdir), c)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(maior(c, (*p)->fdir->info) == 1){
                    rotDD(p);
                } else {
                    rotDE(p);
                }
            }
        }
    } else{
        return 0;
    }
    
    atual->alt = maiorAlt(alturaNo(atual->fesq), alturaNo(atual->fdir)) + 1;
    
    return res;
}

int alturaNo(NoAVL *no){
    if(no == NULL) return -1;
    else
        return no->alt;
}

int fatorBalanceamento_NO(struct NoAVL* no){
    return labs(alturaNo(no->fesq) - alturaNo(no->fdir));
}

int maior(CandidatoArvAVL *a, CandidatoArvAVL *b){ // a > b = 1 ; a < b = 0 ; a == b = 2
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

int maiorAlt(int x, int y){
    if(x > y) return x;
    return y;
}

void rotEE(ArvAVL *arv){
    NoAVL *no;
    no = (*arv)->fesq;
    (*arv)->fesq = no->fdir;
    no->fdir = (*arv);
    (*arv)->alt = maiorAlt(alturaNo((*arv)->fesq), alturaNo((*arv)->fdir)) +1;
    no->alt = maiorAlt(alturaNo(no->fesq), (*arv)->alt) + 1;
    (*arv) = no;
}

void rotDD(ArvAVL *arv){
    NoAVL *no;
    no = (*arv)->fdir;
    (*arv)->fdir = no->fesq;
    no->fesq = (*arv);
    (*arv)->alt = maiorAlt(alturaNo((*arv)->fesq), alturaNo((*arv)->fdir)) +1;
    no->alt = maiorAlt(alturaNo(no->fdir), (*arv)->alt) + 1;
    (*arv) = no;
}

void rotED(ArvAVL *arv){
    rotDD(&(*arv)->fesq);
    rotEE(arv);
}

void rotDE(ArvAVL *arv){
    rotEE(&(*arv)->fdir);
    rotDD(arv);
}

ArvAVL arvAVL_Estado(char *estado, ArvAVL p){ 
    if (p == NULL) { 
        printf("Erro : Registro nao esta presente na arvore\n");
        return NULL;
    }
    if (strcmp(estado, p->info->estado) < 0) { 
        arvAVL_Estado(estado, p->fesq);
    }
    else if (strcmp(estado, p->info->estado) > 0)
        arvAVL_Estado(estado, p->fdir);
    else{
        return p;
    }
}

ArvAVL arvAVL_Cidade(char *estado, char *cidade, ArvAVL p){ 
    if (p == NULL) { 
        printf("Erro : Registro nao esta presente na arvore\n");
        return NULL;
    }
    if (strcmp(estado, p->info->estado) < 0) { 
        arvAVL_Cidade(estado, cidade, p->fesq);
    }
    else if (strcmp(estado, p->info->estado) > 0)
        arvAVL_Cidade(estado, cidade, p->fdir);
    else{
        if (strcmp( cidade, p->info->cidade) < 0)
            arvAVL_Cidade(estado, cidade, p->fesq);

        else if (strcmp(cidade, p->info->cidade) > 0)
            arvAVL_Cidade(estado, cidade, p->fdir);
        else 
            return p;
    }       
}

ArvAVL arvAVL_Candidato(char *estado, char *cidade, char *numeroUrna, ArvAVL p){ 
    if (p == NULL) { 
        printf("Erro : Registro nao esta presente na arvore\n");
        return NULL;
    }
    if (strcmp(estado, p->info->estado) < 0) { 
        arvAVL_Candidato(estado, cidade, numeroUrna, p->fesq);
    }
    else if (strcmp(estado, p->info->estado) > 0)
        arvAVL_Candidato(estado, cidade, numeroUrna, p->fdir);
    else{
        if (strcmp( cidade, p->info->cidade) < 0)
            arvAVL_Candidato(estado, cidade, numeroUrna, p->fesq);

        else if (strcmp(cidade, p->info->cidade) > 0)
            arvAVL_Candidato(estado, cidade, numeroUrna, p->fdir);
        else {
            if (strcmp( numeroUrna, p->info->numeroUrna) < 0)
                arvAVL_Candidato(estado, cidade, numeroUrna, p->fesq);

            else if (strcmp(numeroUrna, p->info->numeroUrna) > 0)
                arvAVL_Candidato(estado, cidade, numeroUrna, p->fdir);
            else 
                return p;
        }
            
    }
        
}

void imprimeEstadoAVL(ArvAVL arv, char *estado){
    if (arv == NULL) return;
    imprimeEstadoAVL (arv->fesq, estado);
    int cmp = strcmp(estado, arv->info->estado);
    if(cmp == 0) imprimeCandidatoArvAVL(arv->info);
    imprimeEstadoAVL (arv->fdir, estado);
}

void imprimeCidadeAVL(ArvAVL arv, char *cidade){
    if (arv == NULL) return;
    imprimeCidadeAVL (arv->fesq, cidade);
    int cmp = strcmp(cidade, arv->info->cidade);
    if(cmp == 0) imprimeCandidatoArvAVL(arv->info);
    imprimeCidadeAVL (arv->fdir, cidade);
}

int compFiltro(ArvAVL arv, char *filtro, int chave){
    if(chave == 1) return strcmp(arv->info->genero, filtro);
    else if(chave == 2) return strcmp(arv->info->partido, filtro);
    else if(chave == 3) return strcmp(arv->info->raca, filtro);
}

void imprimeEstadoAVL_filtro(ArvAVL arv, char *estado, char *filtro, int chave){
    if (arv == NULL) return;
    imprimeEstadoAVL_filtro (arv->fesq, estado, filtro, chave);
    int cmp = strcmp(estado, arv->info->estado); 
    if(cmp == 0 && (compFiltro(arv, filtro, chave) == 0) ){
        imprimeCandidatoArvAVL(arv->info);
    } 
    imprimeEstadoAVL_filtro (arv->fdir, estado, filtro, chave);
}

void imprimeCidadeAVL_filtro(ArvAVL arv, char *cidade, char *filtro, int chave){
    if (arv == NULL) return;
    imprimeCidadeAVL_filtro (arv->fesq, cidade, filtro, chave);
    int cmp = strcmp(cidade, arv->info->cidade);
    if(cmp == 0 && compFiltro(arv, filtro, chave) == 0){
        imprimeCandidatoArvAVL(arv->info);
    }
    imprimeCidadeAVL_filtro (arv->fdir, cidade, filtro, chave);
}


int imprimeCandidatoArvAVL(CandidatoArvAVL *candidato){
    printf("\nUF: %s\nCidade: %s\nNumero de Urna: %s\nCargo: %s\nNome:%s\nNome na urna: %s\nPartido: %s\nGenero: %s\nEscolaridade: %s\nRaca/etnia: %s\n", 
            candidato->estado,candidato->cidade, candidato->numeroUrna, candidato->cargo, candidato->nome, candidato->nomeNaUrna, 
           candidato->partido, candidato->genero, candidato->escolaridade, candidato->raca); 
    return 0;
}


void liberarArvoreAVL(ArvAVL p){
    if (p == NULL) return;
    liberarArvoreAVL (p->fesq);
    liberarArvoreAVL (p->fdir);
    free(p);
}