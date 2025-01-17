#ifndef _RYSUJ_H_
#define _RYSUJ_H_
#include "struct.h"


void odkrywaj_dfs(saper *plansza, int **tab2, int r, int c);
int rysuj(saper *plansza, int **tab2,FILE *zapis_planszy,char *nazwa_gracza);
void rysowanie_tablicy_pomocniczej(int **tab2,int r, int c);
#endif
