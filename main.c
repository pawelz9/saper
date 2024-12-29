#include<stdio.h>


typedef struct sap
{
	int r;
	int c;
	int mines;
	int **tab;
}sap ;

sap *init(int r, int c,int mines ){
	sap* A=(sap*)malloc(sizeof(sap));
	A->r=r;
	A->c=c;
	A->mines=mines;
	A->tab=(int**)calloc(r,sizeof(int*));
	for(int i=0;i<r;i++)
		A->tab[i]=(int *)calloc(c,sizeof(int));
	return A;
} 
void free_sap(sap* A) {
    for (int i = 0; i < A->r; i++) {
        free(A->tab[i]);
    }
    free(A->tab);
    free(A);
}
	
int main()
{
	char x;
	int k;
	int r,c,mines;
	printf ("GRA SAPER\n");
	printf ("wybierz poziom trudnosci:\n");
	printf ("l-latwy 9x9 10 min\n");
	printf ("s-sredni 16x16 40 min\n");
	printf ("t-trudny 16x30 99 min\n");
	printf ("w-wlasna plansza\n");
	while(k!=0){
		k=0;
		scanf("%c",&x);
		if(x=='l')
			init(9,9,10);
		else if(x=='s')
			init(16,16,40);
		else if(x=='t')
			init(16,30,99);
		else if (x=='w'){
			printf("\npodaj dlugosc: ");
			scanf("%i",&c);
			printf("podaj szerokosc: ");
			scanf("%i",&r);
		//warunek by realistyczna liczba min
			printf("podaj ilosc min: ");
			scanf("%i",&mines);
			init(r,c,mines);
		}
		else{
			printf("nieprawidlowa wartosc wpisz jeszcze raz: ");
			k=1;
		}
	}
	return 0;
}
