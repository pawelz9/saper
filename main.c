#include<stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct saper
{
	//r wiersze c kolumny mines ile min lacznie w planszy
	int r;
	int c;
	int mines;
	int **tab;
}saper;

saper *init(int r, int c,int mines ){	
	saper* A=(saper*)malloc(sizeof(saper));
	A->r=r;
	A->c=c;
	A->mines=mines;
	//przypisanie 2 wymiarowej tablicy pamieci
	A->tab=(int**)calloc(r,sizeof(int*));
	for(int i=0;i<r;i++)
		A->tab[i]=(int *)calloc(c,sizeof(int));
	return A;
}

//zwalnianie pamieci
void free_saper(saper* A) {
    for (int i = 0; i < A->r; i++) {
        free(A->tab[i]);
    }
    free(A->tab);
    free(A);
}

//w losowa wspolrzedna przypisujemy mine
saper *assign(saper *A)
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
void sasiady(saper *A,int **tab2){
	//tab2 liczy ile min w sasiedztwie jak jest mina w dokola wspolrzednej w tab to do tab2 dopisujamy ++


}

saper *start(saper *A){
	char x;
	int k=1;
	int r,c,mines;
	printf ("GRA saperER\n");
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
	//plansza <=> A
	saper*A=NULL;
	A=start(A);
	A=assign(A);
	//tab2 liczy ile min dokola
	//tworzenie 2 wymiarowe tab2
	int **tab2=(int**)calloc(A->r,sizeof(int*));
	for(int i=0;i<A->r;i++)
		tab2=(int *)calloc(A->c,sizeof(int));
	sasiady(A,tab2);
	free_saper(A);
	return 0;
}
