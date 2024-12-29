#include<stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct saper
{
	int r;
	int c;
	int mines;
	int **tab;
}saper ;

saper *init(int r, int c,int mines ){
	saper* plansza=(saper*)malloc(sizeof(saper));
	plansza->r=r;
	plansza->c=c;
	plansza->mines=mines;
	plansza->tab=(int**)calloc(r,sizeof(int*));
	for(int i=0;i<r;i++)
		plansza->tab[i]=(int *)calloc(c,sizeof(int));
	return plansza;
}
 
void free_saper(saper* plansza) {
    for (int i = 0; i < plansza->r; i++) {
        free(plansza->tab[i]);
    }
    free(plansza->tab);
    free(plansza);
}

//w losowa wspolrzedna przypisujemy mine
void assign(saper **plansza) //ta funkcja powinna byc voidem, bierze structa i go zapelnia minami i tyle
{
	// trzeba to przemyslec czy to musi byc pointer do pointera
	// w mainie zrobiles pointer do structa mimo ze zwykly struct bylby okej
	int row,col;
	for(int i=0;i<(*plansza)->mines;i++){
		row=rand()%(*plansza)->r;
		col=rand()%(*plansza)->c;
		if((*plansza)->tab[row][col]==1){ 
			i--;
		}else{
			(*plansza)->tab[row][col]=1;
		}

	}
	

}

saper *start(saper *plansza){
	char x;
	int k=1;
	int r,c,mines;
	printf ("GRA saper\n");
	printf ("wybierz poziom trudnosci:\n");
	printf ("l-latwy 9x9 10 min\n");
	printf ("s-sredni 16x16 40 min\n");
	printf ("t-trudny 16x30 99 min\n");
	printf ("w-wlasna plansza\n");
	while(k){
		k=0;
		scanf(" %c",&x);
		if(x=='l')
			plansza=init(9,9,10);
		else if(x=='s')
			plansza=init(16,16,40);
		else if(x=='t')
			plansza=init(16,30,99);
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
			plansza=init(r,c,mines);
		}
		else{
			printf("nieprawidlowa wartosc wpisz jeszcze raz: ");
			k=1;
		}
	}
	return plansza;
}
int main()
{
	//ziarno
	srand((unsigned int)time(NULL)^getpid());
	saper *plansza;
	plansza=start(plansza);
	plansza=assign(plansza);

	free_saper(plansza);
	return 0;
}
