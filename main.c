#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct saper {
	/*
	 r - wiersze, c - kolumny
	 tab - tablica do przechowywania min
	 rys - tablica do wyswietlania na terminal
	*/
    char nazwa[15];
    int r, c, mines;
    char **tab;
    char **rys;
} saper;

int pierwsze_wywolanie = 1;

saper *init(int r, int c, int mines) {
    saper *plansza = (saper *)malloc(sizeof(saper));
    plansza->r = r;
    plansza->c = c;
    plansza->mines = mines;

    plansza->tab = (char **)calloc(r, sizeof(char *));
    plansza->rys = (char **)calloc(r, sizeof(char *));
    for (int i = 0; i < r; i++) {
        plansza->tab[i] = (char *)calloc(c, sizeof(char));
        plansza->rys[i] = (char *)calloc(c, sizeof(char));
    }

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

saper *assign(saper *plansza) {
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

void sasiady(saper *A, int ***tab2) {
    // tab2 liczy ile min w sasiedztwie, jak jest mina wokoło współrzędnej w tab, to do tab2 dopisujemy ++
    for (int i = 0; i < A->r; i++) {
        for (int j = 0; j < A->c; j++) {
            if (A->tab[i][j] == 'M'){
				(*tab2)[i][j] = 9; // Żeby było wiadomo gdzie jest mina w pomocniczej tablicy
                continue;
			}

            // W prawo
            if (j + 1 < A->c && A->tab[i][j + 1] == 'M')
                (*tab2)[i][j]++;
            // Prawy dół (skośnie)
            if (j + 1 < A->c && i + 1 < A->r && A->tab[i + 1][j + 1] == 'M')
                (*tab2)[i][j]++;
            // W dół
            if (i + 1 < A->r && A->tab[i + 1][j] == 'M')
                (*tab2)[i][j]++;
            // W lewy dół
            if (i + 1 < A->r && j > 0 && A->tab[i + 1][j - 1] == 'M')
                (*tab2)[i][j]++;
            // W lewo
            if (j > 0 && A->tab[i][j - 1] == 'M')
                (*tab2)[i][j]++;
            // Lewa góra
            if (j > 0 && i > 0 && A->tab[i - 1][j - 1] == 'M')
                (*tab2)[i][j]++;
            // Góra
            if (i > 0 && A->tab[i - 1][j] == 'M')
                (*tab2)[i][j]++;
            // Prawa góra
            if (i > 0 && j + 1 < A->c && A->tab[i - 1][j + 1] == 'M')
                (*tab2)[i][j]++;
        }
    }
}

void odkrywaj_dfs(saper **plansza, int **tab2, int r, int c) {
    if (r < 0 || r >= (*plansza)->r || c < 0 || c >= (*plansza)->c)
        return;

    if ((*plansza)->rys[r][c] != 0 || (*plansza)->tab[r][c] == 'M')
        return;

    (*plansza)->rys[r][c] = '0' + tab2[r][c];
    if (tab2[r][c] > 0 && pierwsze_wywolanie == 0)
        return;

    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        pierwsze_wywolanie = 0;
        odkrywaj_dfs(plansza, tab2, r + dr[i], c + dc[i]); 
    }
}

void rysuj(saper *plansza, int **tab2) {
    printf("\n======= PLANSZA GRY =======\n\n");

    printf("   ");
    for (int j = 0; j < plansza->c; j++)
        printf(" %2d", j);
    printf("\n   ");
    for (int j = 0; j < plansza->c; j++)
        printf("---");
    printf("\n");

    for (int i = 0; i < plansza->r; i++) {
        printf("%2d|", i);
        for (int j = 0; j < plansza->c; j++) {
            char znak = plansza->rys[i][j] ? plansza->rys[i][j] : '.';
            printf(" %c ", znak);
        }
        printf("|\n");
    }

    printf("   ");
    for (int j = 0; j < plansza->c; j++)
        printf("---");
    printf("\n");
}

void rysowanie_tablicy_pomocniczej(int **tab2,int r, int c) //W razie jakbyś chciał zobaczyć jeszcze tablicę pomocniczą to zrobiłem dodatkową funkcję z tego co usunąłem
{
    char znak;
    printf("\n======= PLANSZA POMOCNICZA =======\n\n");

    // Górna obwódka z numeracją kolumn
    printf("   ");
    for (int j = 0; j <c; j++) {
        printf(" %2d", j);
    }
    printf("\n   ");
    for (int j = 0; j <c; j++) {
        printf("---");
    }
    printf("\n");

    // Zawartość planszy pomocniczej
    for (int i = 0; i <r; i++) {
        printf("%2d|", i);  
        for (int j = 0; j <c; j++) {
            printf(" %d ", tab2[i][j]);
        }
        printf("|\n");
    }

    // Dolna obwódka
    printf("   ");
    for (int j = 0; j < c; j++) {
        printf("---");
    }
    printf("\n\n");
}
void gra(saper *plansza, int **tab2) {
    char z;
    int r, c;

    printf("\n--- GRA SAPER ---\n");
    printf("Aby wyjsc, wpisz 'q'.\n\n");

    while (1) {
        printf("Wykonaj ruch: f r c (flaga) lub o r c (odkryj): ");
        scanf(" %c", &z);

        if (z == 'q') {
            printf("Gra zakonczona.\n");
            break;
        }

        scanf(" %d %d", &r, &c);
        if (r < 0 || r >= plansza->r || c < 0 || c >= plansza->c) {
            printf("Nieprawidlowe wspolrzedne!\n");
            continue;
        }

        if (z == 'f') {
            plansza->rys[r][c] = 'F';
            printf("Postawiono flage na (%d, %d).\n", r, c);
        } else if (z == 'o') {
            if (plansza->tab[r][c] == 'M') {
                printf("Niestety, trafiles na mine! Koniec gry.\n");
                break;
            }
            pierwsze_wywolanie = 1; //Jak zniszczysz tą zmienną to cała funkcja się popsuje uważaj, wszystko tu jest bardzo mocno przemyślane xD
            odkrywaj_dfs(&plansza, tab2, r, c);
        }

        rysuj(plansza, tab2);
    }
}

saper *start() {
    saper *plansza = NULL;
    char x;

    printf("GRA SAPER\n");
    printf("Wybierz poziom trudnosci:\n");
    printf("'l' - latwy (9x9, 10 min)\n's' - sredni (16x16, 40 min)\n't' - trudny (16x30, 99 min)\n'w' - wlasna plansza\n");

    while (1) {
        scanf(" %c", &x);
        if (x == 'l') {
            plansza = init(9, 9, 10);
            break;
        } else if (x == 's') {
            plansza = init(16, 16, 40);
            break;
        } else if (x == 't') {
            plansza = init(16, 30, 99);
            break;
        } else if (x == 'w') {
            int r, c, mines;
            printf("Podaj liczbe wierszy: ");
            scanf("%d", &r);
            printf("Podaj liczbe kolumn: ");
            scanf("%d", &c);
            do {
                printf("Podaj liczbe min: ");
                scanf("%d", &mines);
                if (mines < 1 || mines > r * c * 0.7)
                    printf("Nieprawidlowa liczba min. Sprobuj ponownie.\n");
            } while (mines < 1 || mines > r * c * 0.7);

            plansza = init(r, c, mines);
            break;
        } else {
            printf("Nieprawidlowa opcja. Sprobuj ponownie: ");
        }
    }

    return plansza;
}

int main() {
    srand((unsigned int)time(NULL));

    saper *plansza = start();
    printf("Podaj nazwe gracza: ");
    scanf(" %s", plansza->nazwa);

    plansza = assign(plansza);
    int **tab2 = (int **)calloc(plansza->r, sizeof(int *));
    for (int i = 0; i < plansza->r; i++)
        tab2[i] = (int *)calloc(plansza->c, sizeof(int));

    sasiady(plansza, &tab2);
    rysuj(plansza, tab2);
    gra(plansza, tab2);

    free_saper(plansza, tab2);
    return 0;
}
