#include "menu.h"

char menuPrincipal(){
    char op;
    printf("\n================ MENU ================\n"
                "a) Abrir o arquivo \n"
                "b) Buscar os dados dos candidatos de um dado estado \n"
                "c) Dado um estado, buscar os dados dos candidatos de uma dada cidade\n"
                "d) Dado um estado e uma cidade, buscar os dados do(a) candidato(a) de um dado numero\n"
                "e) Sair\n=> ");

    scanf(" %c", &op);
    setbuf(stdin, NULL);
    return op;
}

void menuListagens(char *op){
    
    printf("\n================ MENU DE LISTAGENS ================\n"
                "a) Imprimir sem filtro \n"
                "b) Filtrar por genero  \n"
                "c) Filtrar por partido \n"
                "d) Filtrar por cor/raca\n"
                "e) Voltar para o menu principal\n=> ");

    scanf(" %c", op);    
    *op = tolower(*op);
    setbuf(stdin, NULL);
}

void strUpper(char *entrada){
    int i = 0;
    while( entrada[i] != '\0'){ 
        entrada[i] = toupper(entrada[i]);    
        i++; 
    }
}

void switchList_estado(char op, Candidato *vetor, int MAX, TipoDicionario raiz, TipoDicionario *arv, ArvAVL *arvAVL, ArvAVL raizAVL ){
    char filtro[20];
    char estado[3];

    clock_t iniciot, fimt; 
    double tempoGasto;
    
    if(op != 'e'){
        printf("Digite o estado: ");
        scanf("%3[^\n]", estado);
        setbuf(stdin, NULL);
    }
    strUpper(estado);

    switch(op){
            case 'a':
                printf("================ BIN SEARCH ================\n\n");
                    iniciot = clock();

                    binSearch_Estado(vetor, 0, MAX, estado, 0);

                    fimt = clock();
                    tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                    printf("Pesquisa binaria por estado, sem filtro: %lf\n", tempoGasto);
                    system("pause");
                    
                    printf("================ ABB ================\n\n");
                    iniciot = clock();

                    raiz = arvBin_Estado(estado, *arv); 
                    imprimeEstado(raiz, estado);
                    fimt = clock();

                    tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                    printf("Pesquisa em Arvore Binaria nao Balanceada por estado, sem filtro: %lf\n", tempoGasto);
                    system("pause");
                    
                    
                    printf("================ AVL ================\n\n");
                    iniciot = clock(); 

                    raizAVL = arvAVL_Estado(estado, *arvAVL);
                    imprimeEstadoAVL(raizAVL, estado);

                    fimt = clock();
                    tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                    printf("Pesquisa em Arvore AVL por estado, sem filtro: %lf\n", tempoGasto);
                    system("pause");
                    
            break;
            case 'b':
                printf("Digite o genero: ");
                scanf("%10[^\n]", filtro);
                setbuf(stdin, NULL);
                strUpper(filtro);

                printf("================ BIN SEARCH ================\n\n");
                iniciot = clock();

                imprimeEstadoBin_filtro(vetor, estado, filtro, MAX, 1);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa binaria por estado, com filtro de genero: %lf\n", tempoGasto);
                system("pause");

                printf("================ ABB ================\n\n");
                iniciot = clock();

                raiz = arvBin_Estado(estado, *arv);
                imprimeEstadoArvBin_filtro(raiz, estado, filtro, 1);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore Binaria nao Balanceada por estado, com filtro de genero: %lf\n", tempoGasto);
                system("pause");

                printf("================ AVL ================\n\n");
                iniciot = clock(); 

                raizAVL = arvAVL_Estado(estado, *arvAVL);
                imprimeEstadoAVL_filtro(raizAVL, estado, filtro, 1);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore AVL por estado, com filtro de genero: %lf\n", tempoGasto);
                system("pause");
            break;
            case 'c': 
                printf("Digite o partido: ");
                scanf("%20[^\n]", filtro);
                setbuf(stdin, NULL);
                strUpper(filtro);                

                printf("================ BIN SEARCH ================\n\n");
                iniciot = clock();

                imprimeEstadoBin_filtro(vetor, estado, filtro, MAX, 2);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa binaria por estado, com filtro de partido: %lf\n", tempoGasto);
                system("pause");

                printf("================ ABB ================\n\n");
                iniciot = clock();

                raiz = arvBin_Estado(estado, *arv);
                imprimeEstadoArvBin_filtro(raiz, estado, filtro, 2);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore Binaria nao Balanceada por estado, com filtro de partido: %lf\n", tempoGasto);
                system("pause");

                printf("================ AVL ================\n\n");
                iniciot = clock(); 

                raizAVL = arvAVL_Estado(estado, *arvAVL);
                imprimeEstadoAVL_filtro(raizAVL, estado, filtro, 2);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore AVL por estado, com filtro de partido: %lf\n", tempoGasto);
                system("pause");
            break;
            case 'd':
                printf("Digite o cor/raca: ");
                scanf("%14[^\n]", filtro);
                strcat(filtro,"\n");
                strUpper(filtro);
                setbuf(stdin, NULL);      

                printf("================ BIN SEARCH ================\n\n");
                iniciot = clock();

                imprimeEstadoBin_filtro(vetor, estado, filtro, MAX, 3);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa binaria por estado, com filtro de cor/raca: %lf\n", tempoGasto);
                system("pause");

                printf("================ ABB ================\n\n");
                iniciot = clock();

                raiz = arvBin_Estado(estado, *arv);
                imprimeEstadoArvBin_filtro(raiz, estado, filtro, 3);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore Binaria nao Balanceada por estado, com filtro de cor/raca: %lf\n", tempoGasto);
                system("pause");         

                printf("================ AVL ================\n\n");
                iniciot = clock(); 

                raizAVL = arvAVL_Estado(estado, *arvAVL);
                imprimeEstadoAVL_filtro(raizAVL, estado, filtro, 3);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore AVL por estado, com filtro de cor/raca: %lf\n", tempoGasto);
                system("pause");
            break;
            case 'e':
                return;
            break;
            default:
                printf("Opcao invalida\n");
                return;
            break;
    }
}

void switchList_cidade(char op, Candidato *vetor, int MAX, TipoDicionario raiz, TipoDicionario *arv, ArvAVL *arvAVL, ArvAVL raizAVL ){
    char filtro[20];
    char cidade[50];
    char estado[3];

    clock_t iniciot, fimt; 
    double tempoGasto;

    if(op != 'e'){
        printf("Digite o estado: ");
        scanf("%3[^\n]", estado);
        setbuf(stdin, NULL);

        printf("Digite o cidade: ");
        scanf("%50[^\n]", cidade);
        setbuf(stdin, NULL);
    }
    strUpper(estado);
    strUpper(cidade);
    
    switch(op){
            case 'a':
                printf("================ BIN SEARCH ================\n\n");
                iniciot = clock();

                int inicio = binSearch_Estado(vetor, 0, MAX, estado, 1); 
                int fim = inicio;
                while(!strcmp(vetor[fim].estado, estado)) fim++; 
                binSearch_Cidade(vetor, inicio, fim, estado, cidade, 0);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa binaria por cidade, sem filtro: %lf\n", tempoGasto);
                system("pause");
                
                printf("================ ABB ================\n\n");
                iniciot = clock();

                raiz = arvBin_Cidade(estado, cidade, *arv);
                imprimeCidade(raiz, cidade);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore Binaria nao Balanceada por cidade, sem filtro: %lf\n", tempoGasto);
                system("pause");
                
                printf("================ AVL ================\n\n");
                iniciot = clock(); 

                raizAVL = arvAVL_Cidade(estado, cidade, *arvAVL);
                imprimeCidadeAVL(raizAVL, cidade);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore AVL por cidade, sem filtro: %lf\n", tempoGasto);
                system("pause");
                
            break;
            case 'b':
                printf("Digite o genero: ");
                scanf("%10[^\n]", filtro);
                setbuf(stdin, NULL);
                strUpper(filtro);
                
                printf("================ BIN SEARCH ================\n\n");
                iniciot = clock();

                imprimeCidadeBin_filtro(vetor, estado, cidade, filtro, MAX, 1);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa binaria por cidade, com filtro de genero: %lf\n", tempoGasto);
                system("pause");
                

                printf("================ ABB ================\n\n");
                iniciot = clock();

                raiz = arvBin_Cidade(estado, cidade, *arv);
                imprimeCidadeArvBin_filtro(raiz, cidade, filtro, 1);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore Binaria nao Balanceada por cidade, com filtro de genero: %lf\n", tempoGasto);
                system("pause");
                

                printf("================ AVL ================\n\n");
                iniciot = clock(); 

                raizAVL = arvAVL_Cidade(estado, cidade, *arvAVL);
                imprimeCidadeAVL_filtro(raizAVL, cidade, filtro, 1);
                
                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore AVL por cidade, com filtro de genero: %lf\n", tempoGasto);
                system("pause");
            break;
            case 'c':
                printf("Digite o partido: ");
                scanf("%20[^\n]", filtro);
                setbuf(stdin, NULL);
                strUpper(filtro);

                printf("================ BIN SEARCH ================\n\n");
                
                iniciot = clock();

                imprimeCidadeBin_filtro(vetor, estado, cidade, filtro, MAX, 2);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa binaria por cidade, com filtro de partido: %lf\n", tempoGasto);
                system("pause");

                printf("================ ABB ================\n\n");
                iniciot = clock(); 

                raiz = arvBin_Cidade(estado, cidade, *arv);
                imprimeCidadeArvBin_filtro(raiz, cidade, filtro, 2);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore Binaria nao Balanceada por cidade, com filtro de partido: %lf\n", tempoGasto);
                system("pause");

                printf("================ AVL ================\n\n");
                iniciot = clock();  

                raizAVL = arvAVL_Cidade(estado, cidade, *arvAVL);
                imprimeCidadeAVL_filtro(raizAVL, cidade, filtro, 2);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore AVL por cidade, com filtro de partido: %lf\n", tempoGasto);
                system("pause");
            break;
            case 'd':
                printf("Digite a cor/raca: ");
                scanf("%14[^\n]", filtro);
                strcat(filtro, "\n");
                setbuf(stdin, NULL);
                strUpper(filtro);

                printf("================ BIN SEARCH ================\n\n");
                iniciot = clock(); 

                imprimeCidadeBin_filtro(vetor, estado, cidade, filtro, MAX, 3);

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa binaria por cidade, com filtro de cor/raca: %lf\n", tempoGasto);
                system("pause");

                printf("================ ABB ================\n\n");
                iniciot = clock(); 

                raiz = arvBin_Cidade(estado, cidade, *arv); 
                imprimeCidadeArvBin_filtro(raiz, cidade, filtro, 3);
                fimt = clock();

                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore Binaria nao Balanceada por cidade, com filtro de cor/raca: %lf\n", tempoGasto);
                system("pause");

                printf("================ AVL ================\n\n");  
                iniciot = clock();   

                raizAVL = arvAVL_Cidade(estado, cidade, *arvAVL);
                imprimeCidadeAVL_filtro(raizAVL, cidade, filtro, 3); 

                fimt = clock();
                tempoGasto = (double)(fimt - iniciot) / CLOCKS_PER_SEC;
                printf("Pesquisa em Arvore AVL por cidade, com filtro de cor/raca: %lf\n", tempoGasto);
                system("pause");
            break;
            case 'e':
                return;
            break;
            default:
                printf("Opcao invalida\n");
                return;
            break;
    }
}