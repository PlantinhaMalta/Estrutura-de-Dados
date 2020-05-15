#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Province/State,Country/Region,Lat,Long,Date,Confirmed,Deaths,Recovered
#define TAMs 50
#define TAMc 50

typedef struct dado{
	char state[TAMs], country[TAMc];
	float lat, longe;
	int conf,death,recov;
  int dia,mes,ano;
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



int main(){
   	char c[100];
   	int i,j,k,t,q,r,s,v,y,u,count;
    k = tamanho("covid_19_clean_complete.csv");//calculando quantas colunas o arquvo tem	
	Dado *ex; //criando ponteiro para malloc
	char aux[20];
	
	ex = malloc(k*sizeof(Dado)); //malloc da quantidade das colunas 
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


  k = tamanho("covid_19_clean_complete.csv");//calculando quantas colunas o arquvo tem
  for(i = 1; i<k;i++){
  	printf(" i: %d\n Country: %s\n State: %s\n Latitude: %f\n Longitude: %f\n Confirmados: %d\n Mortes: %d\n Recuperados: %d\n Data: %d/%d/%d \n\n\n",i , ex[i].country, ex[i].state
  	  , ex[i].lat, ex[i].longe, ex[i].conf, ex[i].death, ex[i].recov, ex[i].dia, ex[i].mes, ex[i].ano);
  }	
	
	return 0;
}
