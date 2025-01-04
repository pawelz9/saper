#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//nastepne akcje
//int sasiady mozna spowrotem na void chyba
//wszsytko dziala okej poza sprawdzaniem pierwszego podejscia jakos poza zakres cos musi
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

void odkrywaj_dfs(saper *plansza, int **tab2, int r, int c) {
    if (r < 0 || r >= plansza->r || c < 0 || c >= plansza->c)
        return;

    if (plansza->rys[r][c] != 0 || plansza->tab[r][c] == 'M')
        return;

    plansza->rys[r][c] = '0' + tab2[r][c];
    if (tab2[r][c] > 0)
        return;

    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        odkrywaj_dfs(plansza, tab2, r + dr[i], c + dc[i]);
    }
}



int rysuj(saper *plansza, int **tab2) {
    int odkryte=0;
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
            if(plansza->rys[i][j]!=0 && plansza->rys[i][j]!='F' )
                odkryte++;
        }
        printf("|\n");
    }

    printf("   ");
    for (int j = 0; j < plansza->c; j++)
        printf("---");
    printf("\n");
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
int gra(saper *plansza, int **tab2) {
    char z;
    int licz=0;
    int odkryte=0;
    int r, c;
    int k=0;
    int m,n;
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
            //plansza->rys[r][c]=tab2[r][c];
            //pierwszy strzal nie moze byc mina
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
                            pierwsze_wywolanie = 1;
                            odkrywaj_dfs(plansza, tab2, r, c);
                            break;}
                    }
            }
            else if (plansza->tab[r][c] == 'M') {
                printf("Niestety, trafiles na mine! Koniec gry.\n");
                return 0;
            }
            pierwsze_wywolanie = 1; //Jak zniszczysz tą zmienną to cała funkcja się popsuje uważaj, wszystko tu jest bardzo mocno przemyślane xD 
            //lol
            licz++;
            odkrywaj_dfs(plansza, tab2, r, c);
        }
        printf("\nodkryte %i\n",odkryte);
        odkryte=rysuj(plansza, tab2);
        if(odkryte==plansza->r*plansza->c-plansza->mines){
            printf("\ngratulacje wygrales!\n");
            return 0;
        }
    }
}

saper *start(int argc, char *argv[]) {
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
            printf("wybrales poziom latwy 9x9 10min");
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
        printf("\nnie podano nazwy gracza. Ustawiono domyslna nazwe: 'Gracz'.\n");
        strncpy(plansza->nazwa, "Gracz", sizeof(plansza->nazwa) - 1);
        plansza->nazwa[sizeof(plansza->nazwa) - 1] = '\0';
    }
    return plansza;
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));

    saper *plansza = start(argc,argv);

    plansza = assign(plansza);
    int **tab2 = (int **)calloc(plansza->r, sizeof(int *));
    for (int i = 0; i < plansza->r; i++)
        tab2[i] = (int *)calloc(plansza->c, sizeof(int));

    plansza=sasiady(plansza, tab2);
    rysuj(plansza, tab2);
    gra(plansza, tab2);

    free_saper(plansza, tab2);
    return 0;
}
