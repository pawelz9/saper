#include<stdio.h>
#include <stdlib.h>


typedef struct saper
{
	int r;	
	int c;
	int mines;
	int **tab;
}saper ;	//zmienilem nazwe na saper bo latwiej sie czyta

saper *init(int r, int c,int mines ){
	saper *A=(saper*)malloc(sizeof(saper));
	A->r=r;
	A->c=c;
	A->mines=mines;
	A->tab=(int**)calloc(r,sizeof(int*)); 
	for(int i=0;i<r;i++)
		A->tab[i]=(int *)calloc(c,sizeof(int));
	return A;
} 
void free_sap(saper *A) {
    for (int i = 0; i < A->r; i++) {
        free(A->tab[i]);
    }
    free(A->tab);
    free(A);
}
	
int main()
{
	char x;
	int k = 1; //musi byc jakas wartosc k bo inaczej to nie wejdzie do while
	int r,c,mines;
	saper *plansza;

	printf ("GRA SAPER\n");
	
	do{
		printf ("wybierz poziom trudnosci:\n");
		printf ("l-latwy 9x9 10 min\n");
		printf ("s-sredni 16x16 40 min\n");
		printf ("t-trudny 16x30 99 min\n");
		printf ("w-wlasna plansza\n");
		scanf(" %c",&x); // spacja obok %c ignoruje biale znaki jak '\n' wiec trzeba na to uwazac
		if(x=='l')
			plansza = init(9,9,10);
		else if(x=='s')
			plansza = init(16,16,40);
		else if(x=='t')
			plansza = init(16,30,99);
		else if (x=='w'){
			printf("\npodaj dlugosc: ");
			scanf("%i",&c);
			printf("podaj szerokosc: ");
			scanf("%i",&r);
		//warunek by realistyczna liczba min
			printf("podaj ilosc min: ");
			scanf("%i",&mines);
			init(r,c,mines);
		}else{
			printf("Nieprawidlowa wartosc, wpisz jeszcze raz: \n");
			k += 1;
		}
		k -= 1;
	}while(k!= 0);
	
	return 0;
}
