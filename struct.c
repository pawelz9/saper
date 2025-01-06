#include <stdio.h>
#include <stdlib.h>

#include "struct.h"


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
    for (int i = 0; i < plansza->r; i++) {
        for (int j = 0; j < plansza->c; j++) {
            plansza->rys[i][j] = '.'; // Każde pole na początku jest nieodkryte
        }
    }
    return plansza;
}

int sasiady(saper *plansza, int **tab2) {
    // tab2 liczy ile min w sasiedztwie, jak jest mina wokoło współrzędnej w tab, to do tab2 dopisujemy ++
    for (int i = 0; i < plansza->r; i++) {
        for (int j = 0; j < plansza->c; j++) {

            // W prawo
            if (j + 1 < plansza->c && plansza->tab[i][j + 1] == 'M')
                tab2[i][j]++;
            // Prawy dół (skośnie)
            if (j + 1 < plansza->c && i + 1 < plansza->r && plansza->tab[i + 1][j + 1] == 'M')
                tab2[i][j]++;
            // W dół
            if (i + 1 < plansza->r && plansza->tab[i + 1][j] == 'M')
                tab2[i][j]++;
            // W lewy dół
            if (i + 1 < plansza->r && j > 0 && plansza->tab[i + 1][j - 1] == 'M')
                tab2[i][j]++;
            // W lewo
            if (j > 0 && plansza->tab[i][j - 1] == 'M')
                tab2[i][j]++;
            // Lewa góra
            if (j > 0 && i > 0 && plansza->tab[i - 1][j - 1] == 'M')
                tab2[i][j]++;
            // Góra
            if (i > 0 && plansza->tab[i - 1][j] == 'M')
                tab2[i][j]++;
            // Prawa góra
            if (i > 0 && j + 1 < plansza->c && plansza->tab[i - 1][j + 1] == 'M')
                tab2[i][j]++;
        }
    }
    return plansza;
}


