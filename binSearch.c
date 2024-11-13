#include "binSearch.h"

void lerEPreencher(FILE *file, Candidato vetor[] ){
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
    int i = 0;

    //Tiramos a primeira linha q noa tem conteudo
    if(i == 0) fgets(linha, sizeof(linha), file);

    while(fgets(linha, sizeof(linha), file) != NULL)  { 

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

        strcpy(vetor[i].estado,estado);
        strcpy(vetor[i].cidade,cidade);
        strcpy(vetor[i].numeroUrna,numeroUrna);
        strcpy(vetor[i].cargo, cargo );
        strcpy(vetor[i].nome, nome);
        strcpy(vetor[i].nomeNaUrna, nomeNaUrna);
        strcpy(vetor[i].partido, partido);
        strcpy(vetor[i].genero, genero);
        strcpy(vetor[i].escolaridade, escolaridade);
        strcpy(vetor[i].raca, raca);
    
        i++;
    }
    
    fclose(file);
}


void shellSort(Candidato vet[], int n){
    int i, j, h = 1;
    Candidato aux;
    do{
            h = h * 3 + 1;
    }while(h < n);
    do{
            h /= 3;
            for(i = h; i < n; i++){
                    aux = vet[i];
                    j = i;
                    while(j >= h && maiorCand(vet[j - h], aux) == 1){
                            vet[j] = vet[j - h];
                            j -= h;
                    }
                    vet[j] = aux;
            }
    }while(h > 1);

}

int maiorCand(Candidato a, Candidato b){ // a > b = 1 ; a < b = 0 ; a == b = 2
    int cmp;
    cmp = strcmp(a.estado, b.estado); 
    if (cmp < 0) return 0;   
    else if (cmp > 0) return 1;
    else {
        cmp = strcmp(a.cidade, b.cidade);
        if (cmp < 0) return 0; 
        else if (cmp > 0) return 1;
        else{
            cmp = strcmp(a.numeroUrna, b.numeroUrna);
            if (cmp < 0) return 0; 
            else if (cmp > 0) return 1;   
        }
    }
    return 2; 
}
 


int binSearch_Estado(Candidato vetor[], int inicio, int fim, char *estado, int chave){ 
    int i = (inicio + fim) / 2;

    if (inicio > fim ) 
        return -1;
    if (strcmp(vetor[i].estado, estado) == 0){ 
        int k = i;
        while(strcmp(vetor[k].estado,vetor[i].estado) == 0) k--;
        k++;
        if(chave == 1){
            return k;
        }
        while(strcmp(vetor[k].estado,vetor[i].estado) == 0){ 
            imprimeCandidato(vetor[k]);      
            k++;
        } 
        return 0;
    }    
    if (strcmp(vetor[i].estado, estado) < 0) 
        return binSearch_Estado(vetor, i + 1, fim, estado, chave);
    else 
        return binSearch_Estado(vetor, inicio, i - 1, estado, chave);
}

int binSearch_Cidade(Candidato vetor[], int inicio, int fim, char *estado, char *cidade, int chave){ 
    int i = (inicio + fim) / 2;
    
    if (inicio > fim ) 
        return -1;
    if (strcmp(vetor[i].cidade, cidade) == 0){ 
        int k = i;
        while(strcmp(vetor[k].cidade,cidade) == 0) k--;
        k++;
        if(chave == 1){
            return k;
        }
        while(!strcmp(vetor[k].cidade, cidade)){ 
            imprimeCandidato(vetor[k]);      
            k++;
        } 
    }    
    else if (strcmp(vetor[i].cidade, cidade) < 0) 
        return binSearch_Cidade(vetor, i + 1, fim, estado, cidade, chave);
    else 
        return binSearch_Cidade(vetor, inicio, i - 1, estado, cidade, chave);
    
    return 0;
}

int binSearch_Candidato(Candidato vetor[], int inicio, int fim, char *estado, char *cidade, char *numeroUrna){
    int i = (inicio + fim) / 2;
    if (inicio > fim) return -1;
    if (strcmp(vetor[i].numeroUrna, numeroUrna) == 0){
        imprimeCandidato(vetor[i]); 
        return 0;
    }       
    if (strcmp(vetor[i].numeroUrna, numeroUrna) < 0) 
        return binSearch_Candidato(vetor, i + 1, fim, estado, cidade, numeroUrna);
    else 
        return binSearch_Candidato(vetor, inicio, i - 1, estado, cidade, numeroUrna);
}

int imprimeCandidato(Candidato candidato){
    printf("\nUF: %s\nCidade: %s\nNumero de Urna: %s\nCargo: %s\nNome:%s\nNome na urna: %s\nPartido: %s\nGenero: %s\nEscolaridade: %s\n"
           "Raca/etnia: %s\n", candidato.estado,candidato.cidade, candidato.numeroUrna, candidato.cargo, candidato.nome, candidato.nomeNaUrna, 
           candidato.partido, candidato.genero, candidato.escolaridade, candidato.raca); 
    return 0;
}

int compFiltroBin(Candidato vetor[], int pos, char *filtro, int chave){
    if(chave == 1) return strcmp(vetor[pos].genero, filtro);
    else if(chave == 2) return strcmp(vetor[pos].partido, filtro);
    else if(chave == 3) return strcmp(vetor[pos].raca, filtro);
}

void imprimeEstadoBin_filtro(Candidato vetor[], char *estado, char *filtro, int MAX, int chave){
    int k = binSearch_Estado(vetor, 0, MAX, estado, 1);
    while(!strcmp(vetor[k].estado, estado)){
        if(!compFiltroBin(vetor, k, filtro, chave))
            imprimeCandidato(vetor[k]);         
         
        k++;
    } 
}

void imprimeCidadeBin_filtro(Candidato vetor[],char *estado, char *cidade, char *filtro, int MAX, int chave){
    int inicio = binSearch_Estado(vetor, 0, MAX, estado, 1); 
    int fim = inicio;
    while(!strcmp(vetor[fim].estado, estado)) fim++; 


    int k = binSearch_Cidade(vetor, inicio, fim,estado, cidade, 1);
    while(!strcmp(vetor[k].cidade, cidade)){
        if(!compFiltroBin(vetor, k, filtro, chave))
            imprimeCandidato(vetor[k]);        
         
        k++;
    } 
}