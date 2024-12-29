#include<stdio.h>
#include <stdlib.h>
#include<time.h>

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

//w losowa wspolrzedna przypisujemy mine
sap *assign(sap *A)
{
	int row,col;
	for(int i=0;i<A->mines;i++){
		row=rand()%A->r;
		col=rand()%A->c;
		if(A->tab[row][col]==1){
			i--;
			continue;
		}
		A->tab[row][col]=1;

	}

	return A;
}

sap *start(sap *A){
	char x;
	int k=1;
	int r,c,mines;
	printf ("GRA SAPER\n");
	printf ("wybierz poziom trudnosci:\n");
	printf ("l-latwy 9x9 10 min\n");
	printf ("s-sredni 16x16 40 min\n");
	printf ("t-trudny 16x30 99 min\n");
	printf ("w-wlasna plansza\n");
	while(k){
		k=0;
		scanf(" %c",&x);
		if(x=='l')
			A=init(9,9,10);
		else if(x=='s')
			A=init(16,16,40);
		else if(x=='t')
			A=init(16,30,99);
		else if (x=='w'){
			printf("\npodaj dlugosc: ");
			scanf("%i",&c);
			printf("podaj szerokosc: ");
			scanf("%i",&r);
		//warunek by realistyczna liczba min
			k=1;
			while(k){
				k=0;
				printf("podaj ilosc min: ");
				scanf("%i",&mines);
				if(mines>r*c*0.7 || mines <1){
					printf("nieprawidlowa ilosc min\n");
					k=1;
				}
			}
			A=init(r,c,mines);
		}
		else{
			printf("nieprawidlowa wartosc wpisz jeszcze raz: ");
			k=1;
		}
	}
	return A;
}
int main()
{
	//ziarno
	srand((unsigned int)time(NULL)^getpid());
	sap*A=NULL;
	A=start(A);
	A=assign(A);

	free_sap(A);
	return 0;
}
