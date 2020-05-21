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
    Mortes proc_mort;

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
    printf("**************** Digite a opcao que voce deseja ordenar seus dados ****************\n\n");
    do
    {
        printf("a)Insertion-Sort\n");
        printf("b)Mergesort\n");
        scanf(" %c",&opc1);
    }
    while(opc1 != 'a' && opc1 != 'b');


    printf("**************** Digite em qual dimensao deseja ordenar ****************\n\n");
    do
    {
        printf("1)Ordenar por nome do pais\n");
        printf("2)Ordenar por latitude (Sul -> Norte)\n");
        printf("3)Ordenar por longitude (Oeste -> Leste)\nOpcao: ");
        scanf(" %c",&opc2);
    }
    while(opc2 != '1' && opc2 != '2' && opc2 != '3');
    start = clock(); //pegando o tempo da ordenacao
    sort(covid_data,0,k-1,opc1,opc2,k);
    end = clock();
    cpu_time_used = ((double)(end - start))/ CLOCKS_PER_SEC;
    printf("\nTempo de execucao da ordenacao foi de %.5lf\n", cpu_time_used);

    p = escreve(covid_data,k);
    if(p)
    {
        printf("Problema no arquivo de saida! Caso queira encerrar o programa, digite 0. Caso queira continuar usando a plataforma\n");
        printf("de acompanhamento, digite qualquer outra coisa\n");
        scanf("%c",&abort);
        if(abort == '0')
            return 0;
    }


    printf("!Dados ordenados e processados!\n\n");//arquivo foi escrito com sucesso

    printf("Montando a tabela hash!\n");
    Bucket *b;
    b = (Bucket*)malloc(k*sizeof(Bucket));
    if(b == NULL)
    {
        printf("Erro alocando memoria\n");
        return 0;
    }

    inicia(b,k);
    hash_data(covid_data, b,k);
/*
    for(i = 0; i < k; i++)  //para printar a tabela hash descomente esse codigo
    {
        if(b[i].virgem != -1)
        {
            printf("%d: %s - %d/%d/%d\n", i,b[i].chave.country, b[i].chave.dia, b[i].chave.mes, b[i].chave.ano);
        }
    }
*/
    flag = 'a';
    printf("Deseja pesquisar algum pais?\ns) Sim\nn) Nao\n");
    scanf(" %c", &flag);

    while(flag != 's' && flag != 'n')
    {
        printf("Escolha uma opcao entre Sim ou Nao\n");
        printf("Deseja pesquisar algum pais?\ns) Sim\nn) Nao\n");
        scanf(" %c", &flag);
    }


    while(flag == 's')
    {

        printf("\nDigite o pais para pesquisar:");
        //fgets misterioso pra pegar uma string do input
        fgets(pais,TAMs,stdin);
        fgets(pais,TAMs,stdin);

        if ((strlen(pais) > 0) && (pais[strlen(pais) - 1] == '\n'))
            pais[strlen(pais) - 1] = '\0';


        mes = pedir_mes();
        dia = pedir_dia(mes);
        ano = pedir_ano();

        printf("Pesquisando por: %s na data %d/%d/%d... \n", pais,dia,mes,ano);
        ind = buscar(b,pais, dia,mes,ano,k);
        if(ind != -1)
        {
            printf("Ficha do pais:\n");
            printf("Indice na tabela hash: %d\n", ind);
            printf("Nome: %s\n", pais);
            printf("Numero de Casos:%d\nNumero de Curas:%d\nNumero de Mortos:%d\n\n", b[ind].chave.conf,b[ind].chave.recov,b[ind].chave.death);
        }
        else
        {
            printf("Pais nao foi encontrado\n\n");
        }
        printf("Deseja pesquisar outro pais?\ns) Sim\nn) Nao\n");
        scanf(" %c", &flag);
        while(flag != 's' && flag != 'n')
        {
            printf("Escolha uma opcao entre Sim ou Nao\n");
            printf("Deseja pesquisar aoutro pais?\ns) Sim\nn) Nao\n");
            scanf(" %c", &flag);
        }

    }

    /*
    printf("**************** Digite alguma opcao de acompanhamento ****************\n\n");
    printf("1)Pais com maior numero de casos confirmados\n");
    printf("2)Pais com maior numero de mortes\n");
    printf("3)Pais com maior numero de casos recuperados\n");
*/


    flag = 'a';
    printf("Deseja pesquisar o pais com maior numero de mortes em um intervalo?\ns) Sim\nn) Nao\n");
    scanf(" %c", &flag);

    while(flag != 's' && flag != 'n')
    {
        printf("Escolha uma opcao entre Sim ou Nao\n");
        printf("Deseja pesquisar o pais com maior numero de mortes em um intervalo?\ns) Sim\nn) Nao\n");
        scanf(" %c", &flag);
    }



    if(flag == 's'){
        while(flag == 's'){
            printf("Primeira data:\n");
            mes = pedir_mes();
            dia = pedir_dia(mes);
            ano = pedir_ano();

            printf("Segunda data:\n");
            mes2 = pedir_mes();
            dia2 = pedir_dia(mes2);
            ano2 = pedir_ano();


            printf("O pais com maior numero de mortes nesse intervalo e:\n");
            procura_morte(covid_data,dia,mes,ano,dia2,mes2,ano2,k);
            printf("Deseja consultar por intervalo novamente?\n");
            scanf(" %c", &flag);
        }
    }



    printf("terminou\n");
    return 0;
}
