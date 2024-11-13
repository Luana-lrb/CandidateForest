#include "file.h"



FILE* abrirArq( char *nomeDoArq){
    FILE *fp = fopen(nomeDoArq,"r");
    if (fp == NULL){
        printf("Nao foi possivel ler o arquivo");
        return 0;
    }
    return fp;
}

void inicializarEstruturas(FILE *fp, char *nomeDoArq, Candidato *vetor, int MAX, Apontador *arv, ArvAVL *arvAVL){
    clock_t iniciot, fimt; 
    double tempoGasto;
    
    if(strcmp(nomeDoArq, "completo") == 0){
        fp = abrirArq("arquivosCSV/eleicoes2024.csv");
        
        iniciot = clock();
        lerEPreencher(fp, vetor); 
        shellSort(vetor, MAX);
        fimt = clock();
        tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
        printf("Preencher por pesquisa binaria: %lf\n", tempoGasto);

        fp = abrirArq("arquivosCSV/eleicoes2024.csv");
        iniciot = clock();
        lerEPreencherArv(fp, arv);
        fimt = clock();
        tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
        printf("Preencher por Arvore Binaria nao Balanceada: %lf\n", tempoGasto);

        fp = abrirArq("arquivosCSV/eleicoes2024.csv");
        iniciot = clock();
        lerEPreencherArvAVL(fp, arvAVL);
        fimt = clock();
        tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
        printf("Preencher por Arvore AVL: %lf\n", tempoGasto);

    } else {
        fp = abrirArq("arquivosCSV/minSemAcento.csv");
        iniciot = clock();
        lerEPreencher(fp, vetor); 
        shellSort(vetor, MAX);
        fimt = clock();
        tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
        printf("Preencher por pesquisa binaria: %lf\n", tempoGasto);

        fp = abrirArq("arquivosCSV/minSemAcento.csv");
        iniciot = clock();
        lerEPreencherArv(fp, arv);
        fimt = clock();
        tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
        printf("Preencher por Arvore Binaria nao Balanceada: %lf\n", tempoGasto);

        fp = abrirArq("arquivosCSV/minSemAcento.csv");
        iniciot = clock();
        lerEPreencherArvAVL(fp, arvAVL);
        fimt = clock();
        tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
        printf("Preencher por Arvore AVL: %lf\n", tempoGasto);
    }
}