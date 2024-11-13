#include "menu.h"
#include "file.h"

#define MAX 462284

int main(){
    //=================== Usados ao longo do programa ===================

    clock_t iniciot, fimt; // variáveis usadas para marcar o tempo de execução dos programas
    double tempoGasto;
    char tipoArq[10];
    FILE *fp = NULL; 
    int arqInicializado = 0;

    //=================== Vetor da Busca Binária ===================

    int inicio, fim;
    Candidato *vetor = (Candidato*)malloc(sizeof(Candidato)*MAX);

    //=================== Arvore Binaria ===================

    //TipoDicionario arv;
    TipoDicionario *arv = (TipoDicionario *)malloc(sizeof(TipoDicionario)); // Aloca memória para a árvore
    *arv = NULL;
    TipoDicionario raiz;

    //=================== Arvore AVL ===================

    ArvAVL *arvAVL = (ArvAVL*)malloc(sizeof(ArvAVL)); // Aloca memória para a árvore
    *arvAVL = NULL;  // Inicializa a raiz como NULL
    ArvAVL raizAVL;


    // Menu que gerencia o programa
    char op;
    do{
        op = menuPrincipal(); 
        op = tolower(op);       
        switch(op){
            case 'a':
                if(arqInicializado == 0) {
                    printf("Deseja carregar o arquivo completo ou o parcial ?\n=> ");
                    scanf(" %s", tipoArq);
                    if(!strcmp(tipoArq, "completo") || !strcmp(tipoArq, "parcial")){
                        inicializarEstruturas(fp, tipoArq, vetor, MAX, arv, arvAVL);
                        arqInicializado =  1;
                    } else {
                        printf("Tente 'completo' ou 'parcial'\n");
                    }
                }else printf("Ja existe um arquivo carregado!") ;
            break;
            case 'b':
                if(arqInicializado){
                    char c;
                    do{
                        menuListagens(&c);
                        switchList_estado(c, vetor, MAX, raiz, arv, arvAVL, raizAVL);
                    }while(c != 'e');                                                    
                } else printf("Primeiro, abra um arquivo.\n");
            break;
            case 'c':
                if(arqInicializado){
                    char c;
                    do{
                        menuListagens(&c);
                        switchList_cidade(c, vetor, MAX, raiz, arv, arvAVL, raizAVL);
                    }while(c != 'e');                                            
                } else printf("Primeiro, abra um arquivo.\n");
            break;
            case 'd': 
                if(arqInicializado){
                    char estado[3];
                    char cidade[30];
                    char numCand[6];
                    printf("Digite o estado: ");
                    scanf("%3[^\n]", estado);
                    setbuf(stdin, NULL);
                    strUpper(estado);

                    printf("Digite o cidade: ");
                    scanf("%50[^\n]", cidade);
                    setbuf(stdin, NULL);
                    strUpper(cidade);

                    printf("Digite o numero do candidato: ");
                    scanf("%6[^\n]", numCand);
                    setbuf(stdin, NULL);
                    strUpper(numCand);

                    printf("================ BIN SEARCH ================\n\n");

                    iniciot = clock();
                    
                    inicio = binSearch_Estado(vetor, 0, MAX, estado, 1); 
                    fim = inicio;
                    while(!strcmp(vetor[fim].estado, estado)) fim++; 
                    inicio = binSearch_Cidade(vetor, inicio, fim, estado, cidade, 1);
                    fim = inicio;
                    while(!strcmp(vetor[fim].cidade, cidade)) fim++;
                    binSearch_Candidato(vetor, inicio, fim, estado, cidade, numCand);

                    fimt = clock();
                    tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                    printf("Pesquisa binaria por candidato: %lf\n", tempoGasto);

                    printf("================ ABB ================\n\n");
                    iniciot = clock();
                    
                    raiz = arvBin_Candidato(estado, cidade, numCand, *arv);
                    imprimeCandidatoArv(raiz->candidato);

                    fimt = clock();
                    tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                    printf("Pesquisa Arvore nao balanceada por candidato: %lf\n", tempoGasto);


                    printf("================ AVL ================\n\n");
                    iniciot = clock();

                    raizAVL = arvAVL_Candidato(estado, cidade, numCand, *arvAVL);
                    imprimeCandidatoArvAVL(raizAVL->info);

                    fimt = clock();
                    tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                    printf("Pesquisa Arvore AVL por candidato: %lf\n", tempoGasto);

                } else printf("Primeiro, abra um arquivo.\n");
        
                break;
            case 'e':
                printf("Encerrando"); 
                break;
            default:
                printf("Opcao invalida, tente de novo\n"); 
                break;
        }
    }while (op != 'e');

    free(vetor);
    printf(".");
    liberarArvoreBin(*arv);
    *arv = NULL;
    printf(".");
    liberarArvoreAVL(*arvAVL);
    *arvAVL = NULL;
    printf(".");

    return 0;

}
