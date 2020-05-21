#define TAMs 50
#define TAMc 50

typedef struct dado{
	char state[TAMs], country[TAMc];
	float lat, longe;
	int conf,death,recov,dia,mes,ano;
}Dado;

typedef struct bucket{
	Dado chave;
	int virgem;
}Bucket;

typedef struct mortes{
    char pais[TAMc];
    int  mortes;
}Mortes;

int tamanho(char arq[]);

int escreve(Dado d[], int tamanho);

void merging(Dado d[], int inicio, int meio,int fim, char opc2);

void insercao(Dado d[], int tamanho, char opc2);

void sort(Dado d[], int inicio, int fim ,char opc1, char opc2, int tamanho);

void leitura(Dado dad[], char arq[]);

void inicia(Bucket b[], int tam);

int hash_posicao(Dado d, int tam, int cont);

void hash_data(Dado d[], Bucket b[], int tam_arq);

int buscar(Bucket b[],char pais[], int dia, int mes,int ano,int tam);

int pedir_mes();

int pedir_dia(int mes);

int pedir_ano();

void insercao_morte(Mortes m[], int tamanho);

void procura_morte(Dado d[],int dia,int mes,int ano,int dia2,int mes2,int ano2, int tam);
