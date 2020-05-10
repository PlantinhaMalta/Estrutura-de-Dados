#include <stdio.h>
#include <string.h>

// Province/State,Country/Region,Lat,Long,Date,Confirmed,Deaths,Recovered
#define TAMs 100
#define TAMc 100

typedef dado{
	char State[TAMs], Country[TAMc], Date[10];
	float lat, longe;
	int conf,death,recov;
}Dado;





int main(){
	
   	char c[350];
   	int i,j;
	Dado exemplo;	

	
	
	FILE *fptr;
	fptr = fopen("covid_19_clean_complete.csv","r");
	
   if (fptr == NULL){ //checando se o arquivo abriu
       printf("Error! opening file");
       return 1;
   }
   
	fscanf(fptr, "%s", c);
	for(i = 0; i<3; i++){
		fscanf(fptr, "%s", c);
		printf("%s \n", c);
	}
	
	strtok(char *str, const char *delim)
	
	for(i = 0; i<3; i++){
   		printf("%c", c[i])	
	}
	
	
	return 0;
}
