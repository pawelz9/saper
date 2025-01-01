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
	char **tab;
}saper;


saper *init(int r, int c, int mines){
	saper *plansza = (saper*)malloc(sizeof(saper));
	plansza->r = r;
	plansza->c = c;
	plansza->mines = mines;
	// przypisanie 2-wymiarowej tablicy pamieci
	plansza->tab = (char**)calloc(r, sizeof(char*));
	for (int i = 0; i < r; i++)
		plansza->tab[i] = (char*)calloc(c, sizeof(char));
	return plansza;
}

// zwalnianie pamieci
void free_saper(saper* plansza, int **tablica_pomocnicza) {
	if (plansza == NULL){
		printf("Wystapil blad ze zwolnieniem pamieci!\n");
		return;
	}
	if (tablica_pomocnicza == NULL){
		printf("Wystapil blad ze zwolnieniem pamieci!\n");
		return;
	}
	for (int i = 0; i < plansza->r; i++) {
		free(plansza->tab[i]);
	}
	for (int i = 0; i < plansza->r; i++) {
		free(tablica_pomocnicza[i]);
	}
	free(plansza->tab);
	free(plansza);
	free(tablica_pomocnicza);
	printf("Pamiec programu zostala zwolniona! \n");
}

// w losowa wspolrzedna przypisujemy mine
saper *assign(saper *plansza)
{
	int row, col;
	for (int i = 0; i < plansza->mines; i++) {
		row = rand() % plansza->r;
		col = rand() % plansza->c;
		if (plansza->tab[row][col] == 'M') {
			i--;
			continue;
		}
		plansza->tab[row][col] = 'M';
	}

	return plansza;
}

void sasiady(saper *A, int **tab2){
	// tab2 liczy ile min w sasiedztwie jak jest mina w dokola wspolrzednej w tab to do tab2 dopisujamy ++
	for (int i = 0; i < A->r; i++) {
		for (int j = 0; j < A->c; j++) {
			if (A->tab[i][j] == 'M')
				continue;
			// w prawo
			if (j + 1 < A->c && A->tab[i][j + 1] == 'M')
				tab2[i][j]++;
			// prawy dol (skosnie)
			if (j + 1 < A->c && i + 1 < A->r && A->tab[i + 1][j + 1] == 'M')
				tab2[i][j]++;
			// w dol
			if (i + 1 < A->r && A->tab[i + 1][j] == 'M')
				tab2[i][j]++;
			// w lewy dol
			if (i + 1 < A->r && j > 0 && A->tab[i + 1][j - 1] == 'M')
				tab2[i][j]++;
			// w lewo
			if (j > 0 && A->tab[i][j - 1] == 'M')
				tab2[i][j]++;
			// lewa gora
			if (j > 0 && i > 0 && A->tab[i - 1][j - 1] == 'M')
				tab2[i][j]++;
			// gora
			if (i > 0 && A->tab[i - 1][j] == 'M')
				tab2[i][j]++;
			// prawa gora
			if (i > 0 && j + 1 < A->c && A->tab[i - 1][j + 1] == 'M')
				tab2[i][j]++;
		}
	}
}

void rysuj(saper *plansza, int **tab2, char z, int rows, int columns, FILE *ruchy) {
    printf("\nPlansza glowna:\n\n");

    // Gorna obwodka
    printf("  "); 
    for (int j = 0; j < plansza->c; j++) {
        printf(" %2d", j); 
    }
    printf("\n   ");
    for (int j = 0; j < plansza->c; j++) {
        printf("___"); 
    }
    printf("\n");

    // Zawartosc planszy
    for (int i = 0; i < plansza->r; i++) {
        printf("%2d|", i); 
        for (int j = 0; j < plansza->c; j++) {
            char znak = plansza->tab[i][j] == 'F'? plansza->tab[i][j]:plansza->tab[i][j] == 'O'?plansza->tab[i][j]:'.';
            printf(" %c ", znak); 
            fprintf(ruchy, " %c", znak); 
        }
        printf("\n");
    }

    printf("\nPlansza pomocnicza:\n\n");

    // Gorna obwodka
    printf("  ");
    for (int j = 0; j < plansza->c; j++) {
        printf(" %2d", j); 
    }
    printf("\n   ");
    for (int j = 0; j < plansza->c; j++) {
        printf("___"); 
    }
    printf("\n");

    // Zawartosc pomocniczej planszy
    for (int i = 0; i < plansza->r; i++) {
        printf("%2d|", i); 
        for (int j = 0; j < plansza->c; j++) {
            printf(" %d ", tab2[i][j]); 
        }
        printf("\n");
    }

    printf("\n");
}

void gra(saper *plansza, int **tab2, FILE *ruchy, FILE *wyniki) {
	char z = ' ';
	int r, c;
	printf("\n---GRA SAPER---");
	printf("\nZasady sterowania :");
	printf("\nWpisz pole jakie chcesz zaznaczyc wedlug schematu");
	printf("\nPrzyklad zaznaczenia flagi : 'f 3 4' stawia flage w 3 wierszu 4 kolumnie");
	printf("\nPrzyklad odkrycia pola : 'o 14 5'   odkrywa pole w wierszu 14 oraz 5 kolumnie");
	printf("\nAby wyjsc z gry nacisnij 'q' ");
	while (z != 'q') {
		printf("\nWykonaj ruch: ");
		scanf(" %c", &z);
		if (z == 'q') {
			printf("Gra zostala zakonczona...\n");
			break;
		}
		scanf(" %i %i", &r, &c);
		if (z == 'f') {
			printf("Flaga zostala postawiona w wierszu %d oraz kolumnie %d\n", r, c);
			plansza->tab[r][c] = 'F';
		}
		if (z == 'o') {
			printf("Pole zostalo odkryte w wierszu %d oraz kolumnie %d\n", r, c);	
			plansza->tab[r][c] = 'O';
			sasiady(plansza,tab2);
			printf("\n\nObok twojego odkrytego pola jest %d bomby!",tab2[r][c]);
		}
		rysuj(plansza, tab2, z, r, c, ruchy);
	}
}

saper *start(saper *plansza) {
	char x;
	int k = 1;
	int r, c, mines;
	printf("GRA SAPER\n");
	printf("wybierz poziom trudnosci:\n");
	printf(" 'l' - latwy 9x9 10 min\n");
	printf(" 's' - sredni 16x16 40 min\n");
	printf(" 't' - trudny 16x30 99 min\n");
	printf(" 'w' - wlasna plansza\n");
	while (k) {
		k = 0;
		scanf(" %c", &x);
		if (x == 'l')
			plansza = init(9, 9, 10);
		else if (x == 's')
			plansza = init(16, 16, 40);
		else if (x == 't')
			plansza = init(16, 30, 99);
		else if (x == 'w') {
			printf("\npodaj dlugosc: ");
			scanf("%i", &c);
			printf("podaj szerokosc: ");
			scanf("%i", &r);
			k = 1;
			while (k) {
				k = 0;
				printf("podaj ilosc min: ");
				scanf("%i", &mines);
				if (mines > r * c * 0.7 || mines < 1) {
					printf("nieprawidlowa ilosc min\n");
					k = 1;
				}
			}
			plansza = init(r, c, mines);
		} else {
			printf("nieprawidlowa wartosc wpisz jeszcze raz: ");
			k = 1;
		}
	}
	return plansza;
}

int main() {
	FILE *wyniki = fopen("wyniki_graczy.txt", "w");
	FILE *ruchy = fopen("ruchy_graczy.txt", "w");

	srand((unsigned int)time(NULL));
	saper *plansza = NULL;
	plansza = start(plansza);

	printf("Podaj nazwe: ");
	scanf(" %s", plansza->nazwa);
	fprintf(wyniki, "%s : ", plansza->nazwa);

	plansza = assign(plansza);
	int **tab2 = (int**)calloc(plansza->r, sizeof(int*));
	for (int i = 0; i < plansza->r; i++)
		tab2[i] = (int *)calloc(plansza->c, sizeof(int));
	
	sasiady(plansza, tab2);
	gra(plansza, tab2, ruchy, wyniki);
	free_saper(plansza, tab2);
	return 0;
}
