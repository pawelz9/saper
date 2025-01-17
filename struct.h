#ifndef _STRUCT_H_
#define _STRUCT_H_

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
saper *init(int r, int c, int mines);
saper *assign(saper *plansza);
void sasiady(saper *plansza, int **tab2);
void free_saper(saper* plansza, int **tablica_pomocnicza);

#endif
