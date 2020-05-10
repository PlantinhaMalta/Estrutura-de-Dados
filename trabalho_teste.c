#include <stdio.h>

int main(){
	
	FILE *fptr;
	fptr = fopen("covid_19_clean_complete.csv","r");
	
   if (fptr == NULL){ //checando se o arquivo abriu
       printf("Error! opening file");
       return 1;
   }
   
   	char c[350];
   	
	fscanf(fptr, "%s", c);
   	printf("%s", c);
	
	
	
	return 0;
}
