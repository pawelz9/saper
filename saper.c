#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "gra.h"
#include "struct.h"
#include "rysuj.h"

saper *start(int argc, char *argv[],char *nazwa_gracza) {
    saper *plansza = NULL;
    char x;
    int r,c,m;
    r=c=m=0;
    int opt;
    char nazwa[15]="";

    while((opt=getopt(argc,argv,"lstwr:c:m:n:"))!=-1){
        switch(opt){
        case 'l':
            printf("wybrales poziom latwy 9x9 10min");
            plansza = init(9, 9, 10);
            break;
        case 's':
            printf("wybrales poziom sredni 16x16 40min");
            plansza = init(16, 16, 40);
            break;
        case 't':
            printf("wybrales poziom trudny 16x30 99min");
            plansza = init(16, 30, 99);
            break;
        case 'w':
            printf("wybrales wlasna plansze \nwybierz ilosc wierszy -r ilosc kolumn -c i ilosc min -m");
            break;
        case 'r':
            r = atoi(optarg);
            break;
        case 'c':
            c = atoi(optarg);
            break;
        case 'm':
            m = atoi(optarg);
            break;
        case 'n':
            strncpy(nazwa, optarg, sizeof(nazwa) - 1);
            nazwa[sizeof(nazwa) - 1] = '\0';
            strcpy(nazwa_gracza,nazwa);
            break;
        default:
            printf("nieznany parametr");
            return 0;
        }
    }
    //wchodzi do petli tylko jesli ktos przypisal r
    if(r!=0 || c!=0 || m!=0){
        if(r<0 || r==0){
            printf("nieprawidlowa ilosc wierszy");
            return 0;
        }
        if(c<0 || c==0){
            printf("nieprawidlowa ilosc kolumn");
            return 0;
        }
        if(m<0 || m>0.7*r*c){
            printf("nieprawidlowa ilosc min");
            return 0;
        }
        else
            plansza=init(r,c,m);
    }
    if(nazwa[0]!='\0'){
        strncpy(plansza->nazwa,nazwa,sizeof(nazwa)-1);
        plansza->nazwa[sizeof(plansza->nazwa) - 1] = '\0'; 
        printf("\nNazwa gracza: %s\n", plansza->nazwa);
    } else  {
        printf("\nNie podano nazwy gracza. Ustawiono domyslna nazwe: 'Gracz'.\n");
        strncpy(plansza->nazwa, "Gracz", sizeof(plansza->nazwa) - 1);
        plansza->nazwa[sizeof(plansza->nazwa) - 1] = '\0';
    }
    return plansza;
}

int main(int argc, char *argv[]) {


    srand((unsigned int)time(NULL));

    FILE *wyniki_graczy = fopen("wyniki_graczy","a"); //przy kolejnym wywołaniu plik się nie czyści
    FILE *zapis_planszy = fopen("zapis_planszy","w");

    char *nazwa_gracza = (char*)malloc(15*sizeof(char));

    saper *plansza = start(argc,argv,nazwa_gracza);

    plansza = assign(plansza);
    int **tab2 = (int**)calloc(plansza->r, sizeof(int*));

    for (int i = 0; i < plansza->r; i++)
        tab2[i] = (int *)calloc(plansza->c, sizeof(int));

    sasiady(plansza, tab2);
    rysuj(plansza, tab2,zapis_planszy,nazwa_gracza);
    gra(plansza, tab2,wyniki_graczy,zapis_planszy,nazwa_gracza);

    free_saper(plansza, tab2);
    return 0;
}
