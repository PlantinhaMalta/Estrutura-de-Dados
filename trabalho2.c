#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Province/State,Country/Region,Lat,Long,Date,Confirmed,Deaths,Recovered
#define TAMs 100
#define TAMc 100

typedef struct dado{
	char state[TAMs], country[TAMc];
	float lat, longe;
	int conf,death,recov;
  int dia,mes,ano;
}Dado;





int main(){
   	char c[350];
   	int i,j,k,t;
	  Dado ex[1000];	
    char q;
	
	FILE *fptr;
	fptr = fopen("covid_19_clean_complete.csv","r");
	
   if (fptr == NULL){ //checando se o arquivo abriu
       printf("Error! opening file");
       return 0;
   }
   
   
   
	fscanf(fptr, "%s", c);
  for(i = 0; !feof(fptr) ; i++){
    fscanf(fptr, "%c", &q);
    printf("%c", q);


  }
	return 0;
}
