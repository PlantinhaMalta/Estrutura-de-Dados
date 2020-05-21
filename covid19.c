#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "covid19.h"

#define TAMs 50
#define TAMc 50


//Calcula o tamanho do arquivo, tirando o cabeçalho
int tamanho(char arq[])
{
    int t = 0,i;
    char c[100];
    FILE* f;
    f = fopen(arq,"r");
    fgets(c, 1000, f);
    for(i = 0; !feof(f) ; i++)
    {
        fgets(c,1000,f);
        t++;
    }

    fclose(f);
    return t;
}



//Escreve no arquivo de saída out.txt
int escreve(Dado d[], int tamanho)
{
    FILE *out;
    int i;
    char buffer[10];

    out = fopen("out.txt", "w");
    if (out == NULL)
    {
        return 1;
    }

    for(i = 0; i<tamanho; i++)                                                     //Escrevendo as informações
    {
        fprintf(out,"País: %s\n",d[i].country);                                       //País:
        fprintf(out,"Estado: %s\n",d[i].state);
        fprintf(out,"Data: %d/%d/%d\n",d[i].dia,d[i].mes,d[i].ano);                   //Data:
        if(d[i].lat <= 0)                                                           //Número de Confirmados:
        {
            if(d[i].longe <= 0)                                                    //Número de Mortes:
            {
                fprintf(out,"Lat/Long: %.2fS/%.2fO ",d[i].lat,d[i].longe);     //Número de Recuperados:
            }
            else
            {
                fprintf(out,"Lat/Long: %.2fS/%.2fL ",d[i].lat,d[i].longe);
            }
        }
        else
        {
            if(d[i].longe <= 0)
            {
                fprintf(out,"Lat/Long: %.2fN/%.2fO ",d[i].lat,d[i].longe);
            }
            else
            {
                fprintf(out,"Lat/Long: %.2fN/%.2fL ",d[i].lat,d[i].longe);
            }
        }
        fprintf(out,"\nNúmero de Confirmados: %d\n", d[i].conf);
        fprintf(out,"Número de Mortes: %d\n", d[i].death);
        fprintf(out,"Número de Recuperados: %d\n\n", d[i].recov);
    }
    fclose(out);

    return 0;                                   //Valores de retorno 0:sucesso, 1:erro
}




//Função de intercalar elementos no método mergesort
void merging(Dado *d, int inicio, int meio,int fim, char opc2)
{
    int t,i,j,n1,n2;
    n1 = meio - inicio +1;
    n2 = fim - meio;

    Dado *L,*R;


    L = (Dado*)malloc((n1+1)*sizeof(Dado));
    R = (Dado*)malloc((n2+1)*sizeof(Dado));

    if(L == NULL || R == NULL)
    {
        return;
    }

    //Separando o vetor nas subdivisões à Esquerda
    for(i = 0; i < n1; i++)
    {
        L[i] = d[i+inicio];
    }

    //Separando o vetor nas subdivisões à Direita
    for(j = 0; j<n2; j++)
    {
        R[j] = d[j+meio+1];
    }


    i = 0;
    j = 0;

//Comparação da intercalação por
//Ordenação por país
    if(opc2 == '1')
    {
        for(t = inicio; i<n1 && j<n2; t++)
        {
            if(strcmp(L[i].country,R[j].country) <= 0)
            {
                d[t] = L[i];
                i++;
            }
            else
            {
                d[t] = R[j];
                j++;
            }
        }
        while(i < n1)
        {
            d[t] = L[i];
            i++;
            t++;
        }
        while(j < n2)
        {
            d[t] = R[j];
            j++;
            t++;
        }
    }

//Ordenação por latitude
    if(opc2 == '2')
    {
        for(t = inicio; i<n1 && j<n2; t++)
        {
            if(L[i].lat <= R[j].lat)
            {
                d[t] = L[i];
                i++;
            }
            else
            {
                d[t] = R[j];
                j++;
            }
        }
        while(i < n1)
        {
            d[t] = L[i];
            i++;
            t++;
        }
        while(j < n2)
        {
            d[t] = R[j];
            j++;
            t++;
        }
    }


//Ordenação por longitude
    if(opc2 == '3')
    {
        for(t = inicio; i<n1 && j<n2; t++)
        {
            if(L[i].longe <= R[j].longe)
            {
                d[t] = L[i];
                i++;
            }
            else
            {
                d[t] = R[j];
                j++;
            }
        }
        while(i < n1)
        {
            d[t] = L[i];
            i++;
            t++;
        }
        while(j < n2)
        {
            d[t] = R[j];
            j++;
            t++;
        }
    }

    return;
}


//Função principal do insertion sort
void insercao(Dado d[], int tamanho, char opc2)
{

    int i, j;
    Dado x;
    for (i=1; i<tamanho; i++)
    {
        x = d[i];
        j=i-1;

        //Ordenação por país
        if(opc2 == '1')
        {
            while ((j>=0) && (strcmp(x.country,d[j].country) < 0))
            {
                d[j+1] = d[j];
                j--;
            }
        }

        //Ordenação por latitude
        if(opc2 == '2')
        {
            while ((j>=0) &&  x.lat < d[j].lat)
            {
                d[j+1] = d[j];
                j--;
            }
        }

        //Ordenação por longitude
        if(opc2 == '3')
        {
            while ((j>=0) && x.longe < d[j].longe)
            {
                d[j+1] = d[j];
                j--;
            }
        }

        d[j+1] = x;
    }
    return;

}


//Função principal da ordenação
void sort(Dado d[], int inicio, int fim,char opc1, char opc2, int tamanho)
{
    int meio;

    if(opc1 == 'a')                                     //Insertion-Sort
    {
        insercao(d,tamanho,opc2);
    }
    if(opc1 == 'b')                                    //Mergesort
    {
        if(inicio < fim)
        {
            meio = (inicio + fim)/2;
            sort(d,inicio,meio,opc1,opc2,tamanho);
            sort(d,meio + 1,fim,opc1,opc2,tamanho);
            merging(d,inicio,meio,fim,opc2);
        }
    }
    return;
}



//Função de Leitura e Armazenamento dos Dados
void leitura(Dado *dad, char arq[])
{

    char c[100],aux[20], opcao;
    int i,j,k,t,q,r,s,v,y,u,count,tam;
    //Cálculo do tamanho necessário de dados

    if (dad == NULL)                                        //Problemas de Alocação
    {
        return;
    }

    FILE *fptr;
    fptr = fopen(arq,"r");                                  //Abrindo o arquivo para ler

    if (fptr == NULL)                                       //Problema de abertura do arquivo
    {
        return;
    }
    fgets(c, 1000, fptr);                                   //Tirando o cabeçalho

    for(i = 0; !feof(fptr) ; i++)
    {


        fgets(c, 1000, fptr);


        if(c[0] == ',')                                       //Há estado?
        {
            //Caso nao possua, o nome atribuído será "#""
            strcpy(dad[i].state,"#");
            count = 0;

        }
        else                                                  //Caso possua...
        {
            for(count = 0; c[count] != ','; count++)
            {

                dad[i].state[count] = c[count];
            }
            dad[i].state[count] = '\0';
        }


        for(j = 1; c[j + count] != ','; j++)                  //Nome do país
        {
            dad[i].country[j - 1] = c[j + count];
        }
        dad[i].country[j-1] = '\0';
        for(k = 1; c[k + j + count] != ','; k++)              //Latitude
        {
            aux[k-1] = c[k + j + count];
        }
        aux[k-1] = '\0';
        dad[i].lat = atof(aux);                                //Transformando a latitude lida em float


        for(t = 1; c[t + k + j + count] != ','; t++)          //Longitude
        {
            aux[t-1] = c[t + k + j + count];
        }
        aux[t-1] = '\0';
        dad[i].longe = atof(aux);                              //Transformando a longitude lida em float

        //Aqui transformamos mes,dia e ano  lidos em inteiros separados por '/'
        for(q = 1; c[t + k + j + q + count] != '/'; q++)
        {
            aux[q-1] = c[t + k + j + q + count];
        }
        aux[q-1] = '\0';
        dad[i].mes = atoi(aux);

        for(r = 1; c[t + k + j + q + r + count] != '/'; r++)
        {
            aux[r-1] = c[t + k + j + q + r + count];
        }
        aux[r-1] = '\0';
        dad[i].dia = atoi(aux);

        for(s = 1; c[t + k + j + q + r + s + count] != ','; s++)
        {
            aux[s-1] = c[t + k + j + q + r + s + count];
        }
        aux[s-1] = '\0';
        dad[i].ano = atoi(aux);


        //Número de Confirmados
        for(v = 1; c[t + k + j + q + r + s + v + count] != ','; v++)
        {
            aux[v-1] = c[t + k + j + q + r + s + v + count];
        }
        aux[v-1] = '\0';
        dad[i].conf = atoi(aux);

        //Número de Mortes
        for(y = 1; c[t + k + j + q + r + s + v + y + count] != ','; y++)
        {
            aux[y-1] = c[t + k + j + q + r + s + v + y + count];
        }
        aux[y-1] = '\0';
        dad[i].death = atoi(aux);

        //Número de Recuperados
        for(u = 1; c[t + k + j + q + r + s + v + y + u + count] != '\n'; u++)
        {
            aux[u-1] = c[t + k + j + q + r + s + v + y + u + count];
        }
        aux[u-1] = '\0';
        dad[i].recov = atoi(aux);
    }

    return;
}

void inicia(Bucket b[], int tam)
{
    int i;
    for(i = 0; i < tam; i++)
    {
        b[i].virgem = -1;
    }
}

int hash_posicao(Dado d, int tam, int cont)
{
    int sum,i;
    sum = 0;

    for(i = 0; i<strlen(d.country); i++)
    {
        sum += d.country[i];
    }
    sum += d.dia;
    sum += d.mes;
    sum += d.ano;

    return (sum+cont)%tam;
}


void hash_data(Dado d[], Bucket *b, int tam_arq)
{
    int i,j,k;
    k = 0;
    for(i = 0; i< tam_arq; i++)
    {
        j = hash_posicao(d[i], tam_arq,k);
        if((b[j].virgem == -1)||(b[j].virgem == -2))  // -1 eh virgem -2 nao virgem nao ocupado
        {
            b[j].chave = d[i];
            b[j].virgem = 0; // 0 nao virgem e ocupado
        }
        else if(b[j].virgem == 0)  //colisao
        {
            while(b[j].virgem == 0)
            {
                k++;
                j = hash_posicao(d[i], tam_arq,k);
                //       if(j >= (tam_arq)){
                //         j = 0;
                //   }

            }
            b[j].chave = d[i];
            b[j].virgem = 0;
        }
    }
}

int buscar(Bucket b[],char pais[], int dia, int mes,int ano,int tam)
{
    int i,j;
    Dado d;
    strcpy(d.country,pais);
    d.dia = dia;
    d.mes = mes;
    d.ano = ano;

//    printf("pais %s\ndia %d\nmes %d\nano %d\n", d.country, d.dia,d.mes,d.ano);


    for(i = 0; i<tam; i++)
    {
        j = hash_posicao(d,tam,i);
        if((strcmp(b[j].chave.country, pais) == 0 )&& b[j].chave.dia == dia && b[j].chave.mes == mes && b[j].chave.ano == ano)
        {

            return j;
        }
        else if(b[j].virgem == -1)  //casa virgem
        {
            return -1;
        }

    }

    return -1; //nao encontrou
}

int pedir_mes()
{
    int mes;
    printf("\nDigite um mes entre 1(Janeiro) e 5(Maio):\n"); //pedimos o mes primeiro para filtrar quais meses tem dia 30 ou 31
    scanf("%d", &mes);
    while(mes < 1 || mes > 5)
    {
        printf("\nDigite um mes entre 1(Janeiro) e 5(Maio):\n");
        scanf("%d", &mes);
    }
    return mes;
}

int pedir_dia(int mes)
{
    int dia;
    printf("\nDigite o dia:\n");
    scanf("%d", &dia);
    if(mes == 1)
    {
        while(dia < 22 || dia > 31)
        {
            printf("O mes 1(Janeiro) tem dados computados somente a partir do dia 22.\nDigite um numero entre 22 e 31:\n");
            scanf("%d", &dia);
        }
    }

    else if(mes == 2)
    {
        while(dia < 1 || dia > 29)
        {
            printf("O mes 2(Fevereiro) possui 29 dias.\nDigite um numero entre 1 e 29:\n");
            scanf("%d", &dia);
        }
    }
    else if(mes == 3)
    {
        while(dia < 1 || dia > 31)
        {
            printf("O mes 3(Marco) possui 31 dias.\nDigite um numero entre 1 e 31:\n");
            scanf("%d", &dia);
        }
    }
    else if(mes == 4)
    {
        while(dia < 1 || dia > 30)
        {
            printf("O mes 4(Abril) possui 30 dias.\nDigite um numero entre 1 e 30:\n");
            scanf("%d", &dia);
        }
    }
    else //maio possui dados computados somente ate dia 8
    {
        while(dia < 1 || dia > 8)
        {
            printf("O mes 5(Maio) tem dados computados somente ate dia 8.\nDigite um numero entre 1 e 8:\n");
            scanf("%d", &dia);
        }
    }
    return dia;
}

int pedir_ano()
{
    int ano;
    printf("\nDigite somente a dezena do ano que deseja procurar\nCaso queira procurar por 2020, basta digitar 20:\n");
    scanf("%d", &ano);
    while(ano != 20)
    {
        printf("Por enquanto possuimos somente dados a respeito de 2020.\nDigite o numero 20 para pesquisar sobre os casos desse ano:\n");
        scanf("%d", &ano);
    }

    return ano;
}

void insercao_morte(Mortes m[], int tamanho)
{

    int i, j;
    Mortes x;
    for (i=1; i<tamanho; i++){
        x = m[i];
        j=i-1;

        while ((j>=0) && (x.mortes < m[j].mortes))
            {
                m[j+1] = m[j];
                j--;
            }
        m[j+1] = x;
    }
    return;

}

void procura_morte(Dado d[],int dia,int mes,int ano,int dia2,int mes2,int ano2,int tam){
    int i,k,j_ini,j_final,p,npais;
    Mortes m_final[300],m_ini[300],m_total[300];
    k = 1;


    sort(d,0,tam-1,'b','1',tam);

    strcpy(m_ini[0].pais,d[0].country);
    m_ini[0].mortes = d[0].death;
    strcpy(m_final[0].pais,d[0].country);
    m_final[0].mortes = 0;


    npais = 1;
    j_ini= 0;
    j_final = 0;

    for(p = 1 ; p < tam ; p++){

        if(d[p].dia == dia && d[p].mes == mes && d[p].ano == ano){
            if(strcmp(d[p].country,m_ini[j_ini].pais) == 0){
                m_ini[j_ini].mortes += d[p].death;
            }
            else{
               j_ini++;
               m_ini[j_ini].mortes = d[p].death;
               strcpy(m_ini[j_ini].pais,d[p].country);
               npais++;
            }
        }
       if(d[p].dia == dia2 && d[p].mes == mes2 && d[p].ano == ano2){
            if(strcmp(d[p].country,m_final[j_final].pais) == 0){
                m_final[j_final].mortes += d[p].death;
            }
            else{
               j_final++;
               m_final[j_final].mortes = d[p].death;
               strcpy(m_final[j_final].pais,d[p].country);
            }
        }
    }

    for(i = 0; i < npais; i++){
        strcpy(m_total[i].pais,m_ini[i].pais);
        if(m_ini[i].mortes <= m_final[i].mortes)
            m_total[i].mortes = m_final[i].mortes - m_ini[i].mortes;
        else m_total[i].mortes = m_ini[i].mortes - m_final[i].mortes;
    }
    insercao_morte(m_total,npais);
    i = 1;
    while(m_total[npais-1].mortes == m_total[npais-i].mortes && i <= npais){
        printf("%s : %d\n",m_total[npais-i].pais,m_total[npais-i].mortes);
        i++;
    }
    printf("\n");
}

