#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gra.h"
#include <time.h>
int wynik(saper *plansza,int odkryte){
    int poziom_trudnsoci=0;
    int wynik=0;
    if(plansza->r==9 && plansza->c==9 && plansza->mines==10)
        poziom_trudnsoci=1;
    else if(plansza->r==16 && plansza->c==16 && plansza->mines==40)
        poziom_trudnsoci=2;
    else if(plansza->r==16 && plansza->c==30 && plansza->mines==99)
        poziom_trudnsoci=3;
    else wynik=-1;
    if(wynik!=-1) wynik=poziom_trudnsoci*odkryte;
    
    return wynik;
}

int gra(saper *plansza, int **tab2) {
    char z;
    int wyn=0;
    int licz=0;
    int odkryte=0;
    int r, c;
    int k=0;
    int m,n;
    printf("\n--- GRA SAPER ---\n");
    printf("Aby wyjsc, wpisz 'q'.\n\n");

    while (1) {
        wyn=wynik(plansza,odkryte);
        if(wyn!=-1)
            printf("Aktualny wynik: %i\n",wyn);    
        else if(licz==0)printf("Wybrano niestandardowy poziom trudnosci wynik nie bedzie zlicznay\n");
        
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
            if(plansza->rys[r][c]!='.' && plansza->rys[r][c]!='F')
                printf("to pole zostalo odkryte nie mozna postawic flagi\n");
            //zeby jak drugi raz flage w to smamo pole to usuwalo 
            else if(plansza->rys[r][c]!='F'){
                plansza->rys[r][c] = 'F';
                printf("Postawiono flage na (%d, %d).\n", r, c);}
            else{
                plansza->rys[r][c]='.';
            }
        } else if (z == 'o') {
            if(licz==0 && plansza->tab[r][c]=='M'){
                    for(m=0;m<plansza->r;m++){
                        for(n=0;n<plansza->c;n++){
                            if(plansza->tab[m][n]!='M'){
                                plansza->tab[m][n]='M';
                                plansza->tab[r][c]=0;
                                plansza=sasiady(plansza,tab2);
                                //plansza->rys[m][n]=tab2[m][n];
                                k=1;
                                break;
                            }
                        }
                        if(k==1){
                            odkrywaj_dfs(plansza, tab2, r, c);
                            break;}
                    }
            }
            else if(plansza->rys[r][c]=='F'){
                printf("to pole ma flage zdjemij flage wpisujac f w to samo pole lub wybierz inne pole\n");
            }
            else if (plansza->tab[r][c] == 'M') {
                printf("Niestety, trafiles na mine! Koniec gry.\n");
                return 0;
            }
            licz++;
            odkrywaj_dfs(plansza, tab2, r, c);
        }
        odkryte=rysuj(plansza, tab2);
        //printf("\nodkryte %i\n",odkryte);
        if(odkryte==plansza->r*plansza->c-plansza->mines){
            printf("\ngratulacje wygrales!\n");
            printf("Wynik: %i\n",wynik(plansza,odkryte));
            //zapis do pliku
            return 0;
        }
    }
}



