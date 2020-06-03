#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
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

    char c[100],aux[20];
    int i,j,k,t,q,r,s,v,y,u,count;
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
    printf("\nDigite um mes entre Janeiro (1) e Maio (5): "); //pedimos o mes primeiro para filtrar quais meses tem dia 30 ou 31
    scanf("%d", &mes);
    while(mes < 1 || mes > 5)
    {
        printf("\nDigite o numero do mes entre Janeiro (1) e Maio (5): ");
        scanf("%d", &mes);
    }
    return mes;
}

int pedir_dia(int mes)
{
    int dia;
    printf("Digite o dia: ");
    scanf("%d", &dia);
    if(mes == 1)
    {
        while(dia < 22 || dia > 31)
        {
            printf("O mes Janeiro tem dados computados somente a partir do dia 22.\nDigite um numero entre 22 e 31:\n");
            scanf("%d", &dia);
        }
    }

    else if(mes == 2)
    {
        while(dia < 1 || dia > 29)
        {
            printf("O mes Fevereiro possui 29 dias.\nDigite um numero entre 1 e 29: ");
            scanf("%d", &dia);
        }
    }
    else if(mes == 3)
    {
        while(dia < 1 || dia > 31)
        {
            printf("O mes Marco possui 31 dias.\nDigite um numero entre 1 e 31: ");
            scanf("%d", &dia);
        }
    }
    else if(mes == 4)
    {
        while(dia < 1 || dia > 30)
        {
            printf("O mes  de Abril possui 30 dias.\nDigite um numero entre 1 e 30: ");
            scanf("%d", &dia);
        }
    }
    else //maio possui dados computados somente ate dia 20
    {
        while(dia < 1 || dia > 20)
        {
            printf("O mes de Maio tem dados computados somente ate dia 20.\nDigite um numero entre 1 e 20: ");
            scanf("%d", &dia);
        }
    }
    return dia;
}

int pedir_ano()
{
    int ano;
    printf("Digite o ano correspondente (somente os dois numeros finais): ");
    scanf("%d", &ano);
    while(ano != 20)
    {
        printf("Por enquanto, possuimos somente dados a respeito de 2020.\nDigite o numero 20 para pesquisar sobre os casos desse ano: ");
        scanf("%d", &ano);
    }

    return ano;
}

void insercao_morte(Pais m[], int tamanho)
{

    int i, j;
    Pais x;
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

void insercao_conf(Pais m[], int tamanho)
{

    int i, j;
    Pais x;
    for (i=1; i<tamanho; i++){
        x = m[i];
        j=i-1;

        while ((j>=0) && (x.confirmados < m[j].confirmados))
            {
                m[j+1] = m[j];
                j--;
            }
        m[j+1] = x;
    }
    return;

}

void insercao_txmort(Pais m[], int tamanho)
{

    int i, j;
    Pais x;
    for (i=1; i<tamanho; i++){
        x = m[i];
        j=i-1;

        while ((j>=0) && (x.confirmados < m[j].confirmados))
            {
                m[j+1] = m[j];
                j--;
            }
        m[j+1] = x;
    }
    return;

}

void insercao_txrecov(Pais m[], int tamanho)
{

    int i, j;
    Pais x;
    for (i=1; i<tamanho; i++){
        x = m[i];
        j=i-1;

        while ((j>=0) && (x.tx_recov < m[j].tx_recov))
            {
                m[j+1] = m[j];
                j--;
            }
        m[j+1] = x;
    }
    return;

}

int preencher_paises(Pais p[], Dado d[],int tamanho, int dia, int mes, int ano){
    int i,j,npais;

    sort(d,0,tamanho-1,'b','1',tamanho);
    strcpy(p[0].pais,d[0].country);
    p[0].mortes = d[0].death;
    p[0].confirmados = d[0].conf;
    p[0].recuperados = d[0].recov;
    npais = 1;
    j = 0;
    for(i = 0; i < tamanho; i++){
        if(dia == d[i].dia && mes == d[i].mes && ano == d[i].ano){
            if(strcmp(d[i].country,p[j].pais) == 0){
                p[j].mortes += d[i].death;
                p[j].confirmados += d[i].conf;
                p[j].recuperados += d[i].recov;

            }else{
                j++;
                p[j].mortes = d[i].death;
                p[j].confirmados = d[i].conf;
                p[j].recuperados = d[i].recov;
                p[j].tx_mort = 0.0;
                p[j].tx_recov = 0.0;
                p[j].var_med = 0.0;
                strcpy(p[j].pais,d[i].country);
                npais++;

            }
        }
    }
    return npais;

}


void procura_morte(Dado d[],int dia,int mes,int ano,int dia2,int mes2,int ano2,int tam){
    int i,npaises;
    Pais m_final[300],m_ini[300],m_total[300];

    npaises = preencher_paises(m_ini,d,tam,dia,mes,ano);
    preencher_paises(m_final,d,tam,dia2,mes2,ano2);

    for(i = 0; i < npaises; i++){
        strcpy(m_total[i].pais,m_ini[i].pais);
        if(m_ini[i].mortes <= m_final[i].mortes)
            m_total[i].mortes = m_final[i].mortes - m_ini[i].mortes;
        else m_total[i].mortes = m_ini[i].mortes - m_final[i].mortes;

    }
    insercao_morte(m_total,npaises);
    i = 1;
    while(m_total[npaises-1].mortes == m_total[npaises-i].mortes && i <= npaises){
        printf("\n%s : %d\n",m_total[npaises-i].pais,m_total[npaises-i].mortes);
        i++;
    }
    printf("\n");
}

void ficha(char pais[], Dado d[], int tam, Bucket b[], int dia, int mes, int ano){
    int ind = buscar(b,pais, dia,mes,ano,tam);
    printf("Indice na tabela hash: %d\n", ind);
    printf("Nome: %s\n", pais);
    printf("Numero de Casos:%d\nNumero de Curas:%d\nNumero de Mortos:%d\n\n", b[ind].chave.conf,b[ind].chave.recov,b[ind].chave.death);
}


void sugestoes(char pais[],Dado d[], int tam){
    int i,j;
    j = 1;
    char paises[10][TAMc];
    strcpy(paises[0],"nulo");
    for(i = 0; i < tam; i++){
        if(d[i].country[0] == toupper(pais[0])){
            if(d[i].country[1] == pais[1]){
                    if(strcmp(paises[j-1],d[i].country) != 0){
                        strcpy(paises[j],d[i].country);
                        printf("\n%s\n",paises[j]);
                        j++;
                    }
            }
        }
    }
    if(j == 1)
        printf("\n#\n");
    printf("\n");
    return;

}

int achou_pais(char pais[],Dado d[], int tam){
    int i;
    for(i = 0; i < tam; i++){

        if(strcmp(pais,d[i].country) == 0){
            return 1;
        }

    }
    return 0;
}


void procura_conf(Dado d[],int dia,int mes,int ano,int dia2,int mes2,int ano2,int tam){
    int i,npaises;
    Pais m_final[300],m_ini[300],m_total[300];

    npaises = preencher_paises(m_ini,d,tam,dia,mes,ano);
    preencher_paises(m_final,d,tam,dia2,mes2,ano2);

    for(i = 0; i < npaises; i++){
        strcpy(m_total[i].pais,m_ini[i].pais);
        if(m_ini[i].confirmados <= m_final[i].confirmados)
            m_total[i].confirmados = m_final[i].confirmados - m_ini[i].confirmados;
        else m_total[i].confirmados = m_ini[i].confirmados - m_final[i].confirmados;

    }

    insercao_conf(m_total,npaises);
    i = 1;
    while(m_total[npaises-1].confirmados == m_total[npaises-i].confirmados && i <= npaises){
        printf("\n%s : %d\n",m_total[npaises-i].pais,m_total[npaises-i].confirmados);
        i++;
    }
    printf("\n");
}


void procura_txmort(Dado d[],int dia,int mes,int ano,int dia2,int mes2,int ano2,int tam){
    int i,npaises;
    Pais m_final[300],m_ini[300],m_total[300];

    npaises = preencher_paises(m_ini,d,tam,dia,mes,ano);
    preencher_paises(m_final,d,tam,dia2,mes2,ano2);


    for(i = 0; i < npaises; i++){
        strcpy(m_total[i].pais,m_ini[i].pais);
        if(m_ini[i].mortes <= m_final[i].mortes){
            m_total[i].mortes = m_final[i].mortes - m_ini[i].mortes;
            m_total[i].recuperados = m_final[i].recuperados - m_ini[i].recuperados;
            m_total[i].confirmados = (m_final[i].confirmados + m_final[i].mortes + m_final[i].recuperados) - (m_ini[i].mortes + m_ini[i].recuperados + m_ini[i].confirmados);
        }else{
            m_total[i].mortes = m_ini[i].mortes - m_final[i].mortes;
            m_total[i].recuperados = m_ini[i].recuperados - m_final[i].recuperados;
            m_total[i].confirmados = (m_ini[i].confirmados + m_ini[i].mortes + m_ini[i].recuperados) - (m_final[i].mortes + m_final[i].recuperados + m_final[i].confirmados);
        }
        if((m_total[i].mortes + m_total[i].confirmados + m_total[i].recuperados) != 0)
            m_total[i].tx_mort = (float)m_total[i].mortes/(float)(m_total[i].confirmados);
        else m_total[i].tx_mort = 0.0;
    }

    insercao_txmort(m_total,npaises);
    i = 1;
    while(m_total[npaises-1].tx_mort == m_total[npaises-i].tx_mort && i <= npaises){
        printf("\n%s : %.2f porcento\tTotal de Casos: %d & Mortes: %d\n",m_total[npaises-i].pais,100*m_total[npaises-i].tx_mort,m_total[npaises-i].confirmados,m_total[npaises-i].mortes);
        i++;
    }
    printf("\n");
}

void procura_txrecov(Dado d[],int dia,int mes,int ano,int dia2,int mes2,int ano2,int tam){
    int i,npaises;
    Pais m_final[300],m_ini[300],m_total[300];

    npaises = preencher_paises(m_ini,d,tam,dia,mes,ano);
    preencher_paises(m_final,d,tam,dia2,mes2,ano2);

    for(i = 0; i < npaises; i++){
        strcpy(m_total[i].pais,m_ini[i].pais);
        if(m_ini[i].mortes <= m_final[i].mortes){
            m_total[i].mortes = m_final[i].mortes - m_ini[i].mortes;
            m_total[i].recuperados = m_final[i].recuperados - m_ini[i].recuperados;
            m_total[i].confirmados = (m_final[i].confirmados + m_final[i].mortes + m_final[i].recuperados) - (m_ini[i].mortes + m_ini[i].recuperados + m_ini[i].confirmados);

        }else{
            m_total[i].mortes = m_ini[i].mortes - m_final[i].mortes;
            m_total[i].recuperados = m_ini[i].recuperados - m_final[i].recuperados;
            m_total[i].confirmados = (m_ini[i].confirmados + m_ini[i].mortes + m_ini[i].recuperados) - (m_final[i].mortes + m_final[i].recuperados + m_final[i].confirmados);
        }

        if((m_total[i].mortes + m_total[i].confirmados + m_total[i].recuperados) == 0)
            m_total[i].tx_recov = 0.0;
        else m_total[i].tx_recov = (float)(m_total[i].recuperados)/(float)(m_total[i].confirmados);
    }

    insercao_txrecov(m_total,npaises);
    i = 1;
    while(m_total[npaises-1].tx_recov == m_total[npaises-i].tx_recov && i <= npaises){
        printf("\n%s : %.2f porcento\tTotal de Casos: %d & Recup.: %d \n",m_total[npaises-i].pais,100*m_total[npaises-i].tx_recov,m_total[npaises-i].confirmados,m_total[npaises-i].recuperados);
        i++;
    }
    printf("\n");
}

void procura_varmed(Dado d[],char country[], int dia,int mes,int ano,int dia2,int mes2,int ano2,int tam){
    int i,npaises,ok;
    Pais m_ini[300],m_final[300],m_total[300];

    npaises = preencher_paises(m_ini,d,tam,dia,mes,ano);
    preencher_paises(m_final,d,tam,dia2,mes2,ano2);

    for(i = 0; i < npaises; i++){
        strcpy(m_total[i].pais,m_ini[i].pais);
        if(strcmp(m_total[i].pais,country) == 0){
            if(m_ini[i].mortes <= m_final[i].mortes){
                m_total[i].mortes = m_final[i].mortes - m_ini[i].mortes;
                m_total[i].recuperados = m_final[i].recuperados - m_ini[i].recuperados;
                m_total[i].confirmados = (m_final[i].confirmados + m_final[i].mortes + m_final[i].recuperados) - (m_ini[i].mortes + m_ini[i].recuperados + m_ini[i].confirmados);
                m_total[i].var_med = (float)m_total[i].confirmados/(float)(m_final[i].confirmados + m_final[i].mortes + m_final[i].recuperados);


            }else{
                m_total[i].mortes = m_ini[i].mortes - m_final[i].mortes;
                m_total[i].recuperados = m_ini[i].recuperados - m_final[i].recuperados;
                m_total[i].confirmados = (m_ini[i].confirmados + m_ini[i].mortes + m_ini[i].recuperados) - (m_final[i].mortes + m_final[i].recuperados + m_final[i].confirmados);
                m_total[i].var_med = (float)m_total[i].confirmados/(float)(m_ini[i].confirmados + m_ini[i].mortes + m_ini[i].recuperados);
            }
        m_total[i].tx_mort = (float)(m_total[i].mortes)/(float)(m_total[i].mortes + m_total[i].confirmados + m_total[i].recuperados);
        m_total[i].tx_recov = (float)(m_total[i].recuperados)/(float)(m_total[i].mortes + m_total[i].confirmados + m_total[i].recuperados);
        printf("\nTaxa de Mortalidade : %.2f porcento\tConf.: %.1f & Mortos: %.1f",100*m_total[i].tx_mort,(float)(m_total[i].mortes + m_total[i].confirmados + m_total[i].recuperados),(float)m_total[i].mortes);
        printf("\nTaxa de Recuperacao : %.2f porcento\tConf.: %.1f & Rec.: %.1f",100*m_total[i].tx_recov,(float)(m_total[i].mortes + m_total[i].confirmados + m_total[i].recuperados),(float)(m_total[i].recuperados));
        printf("\nVariacao do Numero de Casos : %f porcento",100*m_total[i].var_med);
        printf("\n");
        }
    }

    return;
}

