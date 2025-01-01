#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

typedef struct saper
{
	//r wiersze c kolumny mines ile min lacznie w planszy
	char nazwa[15];
	int r;
	int c;
	int mines;
	int **tab;
}saper;

saper *init(int r, int c,int mines){	
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
	for(int i=0;i<A->r;i++){
		for(int j=0;j<A->c;j++){
			if(A->tab[i][j]==1)
				continue;
			//w prawo
			if(j+1<A->c && A->tab[i][j+1]==1 )
				tab2[i][j]++;
			//prawy dol (skosnie)
			if(j+1<A->c && i+1<A->r && A->tab[i+1][j+1]==1)
				tab2[i][j]++;
			//w dol
			if(i+1<A->r && A->tab[i+1][j]==1)
				tab2[i][j]++;
			//w lewy dol
			if(i+1<A->r && j>0 && A->tab[i+1][j-1]==1)
				tab2[i][j]++;
			//w lewo
			if(j>0 && A->tab[i][j-1]==1)
				tab2[i][j]++;
			//lewa gora
			if(j>0 && i>0 && A->tab[i-1][j-1]==1)
				tab2[i][j]++;
			//gora
			if(i>0 && A->tab[i-1][j]==1)
				tab2[i][j]++;
			//prawa gora
			if(i>0 && j+1<A->c && A->tab[i-1][j+1]==1)
				tab2[i][j]++;
		}
	}

}

void test(saper *A,int **tab2){
	//nazwa
	printf("\nnazywasz sie %s",A->nazwa);
	//testowo print sasiady
	for(int i=0;i<A->r;i++){
		printf("\n");
		for(int j=0;j<A->c;j++){
			printf(" %i, ",tab2[i][j]);
		}
	}
	printf("\n plansza A");
	//printf planszy A
	for(int i=0;i<A->r;i++){
		printf("\n");
		for(int j=0;j<A->c;j++){
			printf(" %i, ",A->tab[i][j]);
		}
	}

}

int DFS(){
	//jakis dfs lub cos podobnego gdy klikniemy a dokola nie ma bomb to ma odkrywac 
}
void rysuj(saper *A,int **tab2,char z,int r,int c){}
void gra(saper *A,int **tab2){
	char z=' ';
	int r,c;
	//czyszczenie tablicy
	printf("\033[H\033[J");
	printf("\n---GRA SAPER---");
	printf("\nsterowanie:");
	printf("\nwpisz pole jakie chcesz zaznaczyc wedlug schematu");
	printf("\nprzykladowa flaga- f 3 4  stawia flage w 3 wierszu 4 kolumnei");
	printf("\nodkrycie pola przykladowe - o 14 5   odkrywa pole w wierszu 14 kolumnie 5");
	printf("\nwyjscie z gry - q");
	while(z!='q'){
		printf("\nwykonaj ruch: ");
		scanf(" %c",&z);
		if(z=='q')
			break;
		scanf(" %i %i",&r,&c);
		rysuj(A,tab2,z,r,c);
		//dodac liczenie wyniku i wczytanie do pliku wyniku po grze
	}
}
saper *start(saper *A){
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
		getchar();
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
	printf("podaj nazwe: ");
	scanf(" %s",A->nazwa);
	A=assign(A);
	
	//tab2 liczy ile min dokola
	//tworzenie 2 wymiarowe tab2
	int **tab2=(int**)calloc(A->r,sizeof(int*));
	for(int i=0;i<A->r;i++)
		tab2[i]=(int *)calloc(A->c,sizeof(int));
	sasiady(A,tab2);
	//test(A,tab2);
	gra(A,tab2);
	free_saper(A);
	return 0;
}
