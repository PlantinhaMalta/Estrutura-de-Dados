#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Province/State,Country/Region,Lat,Long,Date,Confirmed,Deaths,Recovered
#define TAMs 50
#define TAMc 50
#define INFINITY 1000000000 //numero para ser usado como infinito no merge sort
#define INFINITY_CHAR 'z' //ultima letra 


typedef struct dado{
	char state[TAMs], country[TAMc];
	float lat, longe;
	int conf,death,recov,dia,mes,ano;
}Dado;

int tamanho(char arq[]){
  int t = 0,i;
  char c[100];
  FILE* f;
  f = fopen(arq,"r");
  fgets(c, 1000, f);
  for(i = 0; !feof(f) ; i++){
    fgets(c,1000,f);
    t++;
  }
  return t;
  
}


int escreve(Dado d[], int tamanho){
	FILE *out;
	int i;
	char buffer[10];
	
	out = fopen("passa_nois.txt", "w"); //criando o arquivo no modo escrita
	if (out == NULL){ //checando se o arquivo abriu
       return 1; //nao abriu retornando 1
   }
   
   for(i = 0; i<tamanho;i++){
	   	fwrite(d[i].country,1,strlen(d[i].country),out);//imprimindo no arquivo o pais
	   	fwrite("\n",1,1,out);
	   	fwrite("Data:",1,strlen("Data:"),out);//imprimindo no arquivo o pais
	   	fprintf(out,"%d", d[i].dia);
	   	fwrite("/",1,1,out);
		fprintf(out,"%d", d[i].mes);
	  	fwrite("/",1,1,out);
		fprintf(out,"%d", d[i].ano);
		fwrite("\n",1,1,out);   
		fprintf(out,"%.4f",d[i].lat);		
		fwrite("\n",1,1,out);
   }
	fclose(out);
}

void merging(Dado d[], int inicio, int meio,int fim){ // intercala numeros
	int t,i,j,n1,n2;
	n1 = meio - inicio +1; 
	n2 = fim - meio;
	
	Dado *L,*R;
	
	L = (Dado*)malloc((n1+1)*sizeof(Dado)); 
	R = (Dado*)malloc((n2+1)*sizeof(Dado)); 
	
	if(L == NULL || R == NULL) { //checagem para ver se malloc deu certo
      printf("malloc falhou, ex == NULL!\n");
      return;
   }
	
	
	for(i = 0; i < n1; i++){
		
		L[i] = d[i+inicio];
			
	}		
		

	for(j = 0; j<n2; j++){
		
		R[j] = d[j+meio+1];
		
	}
	
	
	i = 0;
	j = 0;
	
	for(t = inicio; i<n1 && j<n2; t++){
		if(strcmp(L[i].country,R[j].country) <= 0){
			
			d[t] = L[i];
			i++;
		}
		else{
			
			d[t] = R[j];
			j++;
		}
	}
	while(i < n1){
		d[t] = L[i];
		i++;
		t++;
	}
	while(j < n2){
		d[t] = R[j];
		j++;
		t++;
	}	
}



void sort(Dado d[], int inicio, int fim ,char opc){
	int meio,ii;
	//printf("inicio %d\nfim %d\n", inicio, fim);
	if(opc == 'a'){ //vetor nao unitario
		if(inicio < fim){ // organizando pelo nome do pais
			meio = (inicio + fim)/2;
			sort(d,inicio,meio,opc);
			sort(d,meio + 1,fim,opc);
			merging(d,inicio,meio,fim);		
		}
	}
		else{ //organizando por latitude ou longitude
			sort(d,inicio,meio,opc);
			sort(d,meio + 1,fim,opc);
		//	intercala_float(d,inicio,meio,fim);
		}
		
		
}


void insercao(Dado d[], int tamanho){
	int i, j;
	Dado x;
	for (i=1; i<tamanho; i++) {
		x = d[i];
		j=i-1;
		while ((j>=0) && (strcmp(x.country,d[j].country) < 0)) {
			d[j+1] = d[j];
			j--;
		}
		d[j+1] = x;
	}
}

int main(){
   	char c[100],aux[20], opcao;
   	int i,j,k,t,q,r,s,v,y,u,count;
    k = tamanho("covid_19_clean_complete.csv");//calculando quantas linhas o arquvo tem	
	
	Dado *ex; //criando ponteiro para malloc
	ex = (Dado*)malloc(k*sizeof(Dado)); //malloc da quantidade das linhas 
	if (ex == NULL) { //checagem para ver se malloc deu certo
      printf("malloc falhou, ex == NULL!\n");
      return 1;
   }
	
	
	
	FILE *fptr; //ponteiro para abrir o arquivo
	fptr = fopen("covid_19_clean_complete.csv","r"); //abrindo o arquivo para ler
	
   if (fptr == NULL){ //checando se o arquivo abriu
       printf("Arquivo nao foi aperto");
       return 0;
   }
   

   
	fscanf(fptr, "%s", c);//pulando o cabecalho
	fgets(c, 1000, fptr);
	int a;
for(i = 0; !feof(fptr) ; i++){
	fgets(c, 1000, fptr);
    	
	
	if(c[0] == ','){ //checando se a linha possui state
      strcpy(ex[i].state,"#"); //caso nao possua, colocar na variavel #
      count = 0;
    //  printf("%s\n", ex[i].state);
	}
	else{
      for(count = 0; c[count] != ','; count++){
        ex[i].state[count] = c[count]; //colocando na variavel o nome do state letra por letra
      }
  	//  ex[i].state[count-1] = '\0';
    //  printf("%s\n",ex[i].state);	
	}  
	
	
	  for(j = 1; c[j + count] != ','; j++){
        ex[i].country[j - 1] = c[j + count]; //colocando na variavel o nome do country letra por letra
      }
  	  ex[i].country[j-1] = '\0';
     // printf("%s\n",ex[i].country);

      for(k = 1; c[k + j + count] != ','; k++){ //indo ate a proxima informacao que comeca apos a virgula
        aux[k-1] = c[k + j + count]; //escrevendo caracter por caracter no aux
      }
      aux[k-1] = '\0';
      ex[i].lat = atof(aux); //transformando a latitude em float e armazenando na variavel
     // printf("%.4f\n",ex[i].lat);
      
      
      for(t = 1; c[t + k + j + count] != ','; t++){
        aux[t-1] = c[t + k + j + count];
      }
      aux[t-1] = '\0';
      ex[i].longe = atof(aux);//transformando a longitude em float e armazenando na variavel
     // printf("%.4f\n",ex[i].longe);
      
	  //transformando mes,dia e ano  em integer e armazenando na variavel
      for(q = 1; c[t + k + j + q + count] != '/'; q++){
        aux[q-1] = c[t + k + j + q + count];
      }
      aux[q-1] = '\0';
      ex[i].mes = atoi(aux);
     // printf("%d/",ex[i].mes);  
      

      for(r = 1; c[t + k + j + q + r + count] != '/'; r++){
        aux[r-1] = c[t + k + j + q + r + count];
      }
      aux[r-1] = '\0';
      ex[i].dia = atoi(aux);
     // printf("%d/",ex[i].dia); 
      

      for(s = 1; c[t + k + j + q + r + s + count] != ','; s++){
        aux[s-1] = c[t + k + j + q + r + s + count];
      }
      aux[s-1] = '\0';
      ex[i].ano = atoi(aux);
     // printf("%d\n",ex[i].ano);     
      
       //transformando confirmed,deaths e recovered  em integer e armazenando na variavel
      for(v = 1; c[t + k + j + q + r + s + v + count] != ','; v++){
        aux[v-1] = c[t + k + j + q + r + s + v + count];
      }
      aux[v-1] = '\0';
      ex[i].conf = atoi(aux);
     // printf("%d\n",ex[i].conf);

      for(y = 1; c[t + k + j + q + r + s + v + y + count] != ','; y++){
        aux[y-1] = c[t + k + j + q + r + s + v + y + count];
      }
      aux[y-1] = '\0';
      ex[i].death = atoi(aux);
     // printf("%d\n",ex[i].death);
	  
      for(u = 1; c[t + k + j + q + r + s + v + y + u + count] != '\n'; u++){
        aux[u-1] = c[t + k + j + q + r + s + v + y + u + count];
	  }
	  
	  aux[u-1] = '\0';
      ex[i].recov = atoi(aux);
     // printf("%d\n",ex[i].recov);     
    }


  


	printf("Ordenar por:\n(a) Pais\n(b) Latitude\n(c) Longitude\n");
	scanf("%c", &opcao);
	k = tamanho("covid_19_clean_complete.csv");//calculando quantas colunas o arquvo tem
	switch (opcao){
    	case 'a':
     		//sort(ex, 0, k-1, opcao);
			insercao(ex,k);
			break;

   		case 'b':
   		//	mergesort(ex.state, ex.lat, 0, k, opcao);
   		break;

		case 'c':
     	//	mergesort(ex.state, ex.longe, 0, k, opcao);		
		break;
   
   		default:
    		printf("Escolha um numero entre a,b e c");
	}
    escreve(ex,k);
	
	return 0;
}
