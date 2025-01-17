#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rysuj.h"


int pierwsze_wywolanie = 1;



void odkrywaj_dfs(saper *plansza, int **tab2, int r, int c) { 
    if (r < 0 || r >= plansza->r || c < 0 || c >= plansza->c)
        return;

    if (plansza->rys[r][c] != '.' || plansza->tab[r][c] == 'M')
        return;

    plansza->rys[r][c] = '0' + tab2[r][c];
    if (tab2[r][c] > 0 && pierwsze_wywolanie == 0)
        return;

    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        pierwsze_wywolanie = 0;
        odkrywaj_dfs(plansza, tab2, r + dr[i], c + dc[i]);
        pierwsze_wywolanie = 1;
    }
}

void plansza_do_pliku(saper *plansza, int **tab2,FILE *zapis_planszy,char *nazwa_gracza){
    static int numer_planszy = 1;

    fprintf(zapis_planszy,"\n======= PLANSZA PO RUCHU #%d GRACZA %s ======= \n\n",numer_planszy,nazwa_gracza);
    fprintf(zapis_planszy,"   ");
    for (int j = 0; j < plansza->c; j++){
        fprintf(zapis_planszy," %2d", j);
    }
    fprintf(zapis_planszy,"\n   ");
    for (int j = 0; j < plansza->c; j++){
        fprintf(zapis_planszy,"---");
    }
    fprintf(zapis_planszy,"\n");

    for (int i = 0; i < plansza->r; i++) {
        fprintf(zapis_planszy,"%2d|", i);
        for (int j = 0; j < plansza->c; j++) {
            char znak = plansza->rys[i][j];
            //char znak = plansza->rys[i][j] ? plansza->rys[i][j] : '.';
            fprintf(zapis_planszy," %c ", znak);
        }
        fprintf(zapis_planszy,"|\n");
    }

    fprintf(zapis_planszy,"   ");
    for (int j = 0; j < plansza->c; j++)
        fprintf(zapis_planszy,"---");
    fprintf(zapis_planszy,"\n");
    numer_planszy ++;
}

int rysuj(saper *plansza, int **tab2,FILE *zapis_planszy,char *nazwa_gracza) {
    int odkryte=0;
    printf("\n======= PLANSZA GRY =======\n\n");

    printf("   ");
    for (int j = 0; j < plansza->c; j++){
        printf(" %2d", j);
    }
    printf("\n   ");
    for (int j = 0; j < plansza->c; j++){
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < plansza->r; i++) {
        printf("%2d|", i);
        for (int j = 0; j < plansza->c; j++) {
            char znak = plansza->rys[i][j];
            //char znak = plansza->rys[i][j] ? plansza->rys[i][j] : '.';
            printf(" %c ", znak);
            if(plansza->rys[i][j]!='.' && plansza->rys[i][j]!='F' )
                odkryte++;
        }
        printf("|\n");
    }

    printf("   ");
    for (int j = 0; j < plansza->c; j++)
        printf("---");
    printf("\n");

    plansza_do_pliku(plansza,tab2,zapis_planszy,nazwa_gracza);

    return odkryte;
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
