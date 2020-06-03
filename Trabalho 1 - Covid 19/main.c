#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "covid19.h"



int main()
{
    char abort,flag, pais[TAMs];
    int k,p,h,i,ind, dia,ano,mes, dia2, mes2, ano2;
    clock_t start, end;
    double cpu_time_used;
    Dado *covid_data;

    k = tamanho("covid_19_clean_complete.csv");

    covid_data = (Dado*)malloc(k*sizeof(Dado));

    leitura(covid_data,"covid_19_clean_complete.csv");
    if(covid_data == NULL)
    {
        printf("Problemas na abertura do programa! Tente novamente.");
        return 0;
    }


    char opc1,opc2;
    printf("\n#############################################\n");
    printf("########## Acompanhamento COVID-19 ##########\n");
    printf("#############################################\n\n");
    printf("Realizado pelos Alunos: Leonardo Perassoli\n                        Gabriel Silva Malta\n\n\n");
    printf("Os dados lidos por esse programa podem ser encontrados na url: https://www.kaggle.com/imdevskp/corona-virus-report\n");
    printf("O intuito do programa e ser uma plataforma de acompanhamento dos dados a respeito da doenca COVID-19. Os metodos de\n");
    printf("ordenacao e estruturacao dos dados sao para fins de avaliacao da materia SCC0224 Estrutura de Dados II do ICMC - USP.\n\n");
    printf("**************** Digite com qual metodo deseja ordenar seus dados ****************\n\n");
    do
    {
        printf("a)Insertion-Sort\n");
        printf("b)Mergesort\n\n");
        printf("Opcao: ");
        scanf(" %c",&opc1);
    }
    while(opc1 != 'a' && opc1 != 'b');


    printf("\n\n**************** Digite em qual dimensao deseja ordenar ****************\n\n");
    do
    {
        printf("1)Ordenar por nome do pais\n");
        printf("2)Ordenar por latitude (Sul -> Norte)\n");
        printf("3)Ordenar por longitude (Oeste -> Leste)\n\nOpcao: ");
        scanf(" %c",&opc2);
    }
    while(opc2 != '1' && opc2 != '2' && opc2 != '3');
    start = clock(); //pegando o tempo da ordenacao
    sort(covid_data,0,k-1,opc1,opc2,k);
    end = clock();
    cpu_time_used = ((double)(end - start))/ CLOCKS_PER_SEC;
    printf("\n\nTempo de execucao da ordenacao foi de %.4lf segundos\n", cpu_time_used);

    p = escreve(covid_data,k);
    if(p)
    {
        printf("\nProblema no arquivo de saida! Caso queira encerrar o programa, digite 0. Caso queira continuar usando a plataforma\n");
        printf("de acompanhamento, digite qualquer outra coisa\n");
        scanf("%c",&abort);
        if(abort == '0'){
            printf("\nObrigado e até logo...\n\n");
            return 0;
        }
    }


    printf("Dados ordenados e processados!\n"); //Arquivo foi escrito com sucesso

    printf("Montando a tabela hash...\n\n");
    Bucket *b;
    b = (Bucket*)malloc(k*sizeof(Bucket));
    if(b == NULL)
    {
        printf("Erro de alocacao de memoria...\n");
        return 0;
    }

    inicia(b,k);
    hash_data(covid_data, b,k);

/*
    for(i = 0; i < k; i++)                                                                      //Para printar a tabela hash descomente esse trecho de código
    {
        if(b[i].virgem != -1)
        {
            printf("%d: %s - %d/%d/%d\n", i,b[i].chave.country, b[i].chave.dia, b[i].chave.mes, b[i].chave.ano);
        }
    }
*/
    int achou;
    do{
        printf("\n\n**************** Menu de Opcoes ****************\n\n");
        flag = 'a';
        printf("1)Pesquisar ficha de um pais (dado uma data)\n");
        printf("2)Pais com maior numero de mortos (dado um periodo)\n");
        printf("3)Pais com maior numero de confirmados (dado um periodo)\n");
        printf("4)Pais com maior taxa de mortalidade (dado um periodo)\n");
        printf("5)Pais com maior taxa de recuperacao (dado um periodo)\n");
        printf("6)Variacao media de confirmados, mortos e recuperados de um pais(dado um periodo)\n");
        printf("7)Sair do programa\n\n");
        printf("Opcao: ");
        scanf(" %c", &flag);

        while(flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7')
        {
            printf("Escolha uma opcao valida\nOpcao: ");
            scanf(" %c", &flag);
        }


        if(flag == '1')
        {
                printf("\n\nDigite o nome do pais para pesquisar:");
                scanf(" %s",pais);
                if ((strlen(pais) > 0) && (pais[strlen(pais) - 1] == '\n'))
                    pais[strlen(pais) - 1] = '\0';
                achou = achou_pais(pais,covid_data,k);
            while(achou == 0){

                if(!achou_pais(pais,covid_data,k)){
                    printf("Nao foi possivel encontrar esse Pais. Algumas sugestoes que podem se assemelhar com o que procura:\n");
                    sugestoes(pais,covid_data,k);
                }
                printf("\n\nDigite o nome do pais para pesquisar:");
                scanf(" %s",pais);
                achou = achou_pais(pais,covid_data,k);
            }


            mes = pedir_mes();
            dia = pedir_dia(mes);
            ano = pedir_ano();

            printf("\nPesquisando por: %s na data %d/%d/20%d... \n\n", pais,dia,mes,ano);
            printf("Ficha do pais:\n");
            ficha(pais,covid_data,k,b,dia,mes,ano);

        }

        if(flag == '2'){
                printf("\nPrimeira Data:\n");
                mes = pedir_mes();
                dia = pedir_dia(mes);
                ano = pedir_ano();

                printf("\nSegunda Data:\n");
                mes2 = pedir_mes();
                dia2 = pedir_dia(mes2);
                ano2 = pedir_ano();


                printf("O pais com maior numero de mortes nesse periodo e:\n");
                procura_morte(covid_data,dia,mes,ano,dia2,mes2,ano2,k);
        }

        if(flag == '3'){
            printf("\nPrimeira Data:\n");
                mes = pedir_mes();
                dia = pedir_dia(mes);
                ano = pedir_ano();

                printf("\nSegunda Data:\n");
                mes2 = pedir_mes();
                dia2 = pedir_dia(mes2);
                ano2 = pedir_ano();


                printf("O pais com maior numero de confirmados nesse periodo e:\n");
                procura_conf(covid_data,dia,mes,ano,dia2,mes2,ano2,k);

        }

        if(flag == '4'){
            printf("\nPrimeira Data:\n");
                mes = pedir_mes();
                dia = pedir_dia(mes);
                ano = pedir_ano();

                printf("\nSegunda Data:\n");
                mes2 = pedir_mes();
                dia2 = pedir_dia(mes2);
                ano2 = pedir_ano();


                printf("O pais com maior taxa de mortalidade nesse periodo e:\n");
                procura_txmort(covid_data,dia,mes,ano,dia2,mes2,ano2,k);
        }

        if(flag == '5'){
            printf("\nPrimeira Data:\n");
                mes = pedir_mes();
                dia = pedir_dia(mes);
                ano = pedir_ano();

                printf("\nSegunda Data:\n");
                mes2 = pedir_mes();
                dia2 = pedir_dia(mes2);
                ano2 = pedir_ano();


                printf("O pais com maior taxa de recuperação nesse periodo e:\n");
                procura_txrecov(covid_data,dia,mes,ano,dia2,mes2,ano2,k);
        }

        if(flag == '6'){
            char input[50];
            printf("Digite o nome do pais:");
            scanf(" %s",input);
            achou = achou_pais(input,covid_data,k);
            while(achou == 0){

                if(!achou_pais(input,covid_data,k)){
                    printf("Nao foi possivel encontrar esse Pais. Algumas sugestoes que podem se assemelhar com o que procura:\n");
                    sugestoes(input,covid_data,k);
                }
                printf("\n\nDigite o nome do pais para pesquisar:");
                scanf(" %s",input);
                achou = achou_pais(input,covid_data,k);
            }
            printf("\n\nPrimeira Data:\n");
                mes = pedir_mes();
                dia = pedir_dia(mes);
                ano = pedir_ano();

                printf("\nSegunda Data:\n");
                mes2 = pedir_mes();
                dia2 = pedir_dia(mes2);
                ano2 = pedir_ano();


                printf("\n%s: entre %d/%d/20%d e %d/%d/20%d\n",input,dia,mes,ano,dia2,mes2,ano2);
                procura_varmed(covid_data,input,dia,mes,ano,dia2,mes2,ano2,k);
        }



    }while(flag != '7');


    printf("Obrigado e Ate Logo...\n");
    return 0;
}
