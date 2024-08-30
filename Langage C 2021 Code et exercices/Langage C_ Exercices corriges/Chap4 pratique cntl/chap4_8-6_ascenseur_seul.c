#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//pour décoller l'immeuble de la marge
const int DECX=5;
const int DECY=5;

int NBETAGE; // nombre etage de l'immeuble
int COULEUR;    // couleur de l'immeuble

void    creer_immeuble      (int min, int max);
void    affiche_immeuble    (int posascenseur);
void    affiche_etage       (int y, int color);
int     select_etage        (void);
int     move                (int y, int etage);

void    gotoxy              (int x, int y);
void    textcolor           (int color);

/****************************************************
****************************************************/
int main()
{
int posasc=0, etage=0;

    srand(time(NULL));
    creer_immeuble(10,20);
    affiche_immeuble(posasc);

    while(etage>=0){

        etage=select_etage();
        posasc=move(posasc,etage);

    }
    gotoxy(DECX,DECY+NBETAGE+2);
    return 0;
}
/****************************************************
avoir l'immeuble
****************************************************/
void creer_immeuble(int min, int max)
{
    NBETAGE=rand()%(max-min)+min;
    COULEUR=1+rand()%15;
}
/****************************************************
afficher l'immeuble
****************************************************/
void affiche_immeuble(int posasc)
{
int y;
    for(y=0; y<NBETAGE; y++)
        affiche_etage(y, COULEUR);
    affiche_etage(posasc, COULEUR<<4); // <<4 equivalent à multiplier par 16
}
/****************************************************
afficher un etage
****************************************************/
void affiche_etage(int y, int color)
{
int posy;
    posy=NBETAGE-y; // inverser pour partir du bas
    gotoxy(DECX,DECY+posy);
    textcolor(color);
    printf("%2d",y);
}
/****************************************************
sélectionner un étage à atteindre
****************************************************/
int select_etage()
{
int etage;
    // afficher le sélecteur
    textcolor(10);
    gotoxy(DECX*2,DECY+NBETAGE/2);
    printf("Entrer etage : ");
    // récupération de l'étage
    scanf("%d",&etage);
    rewind(stdin);

    if(etage>=NBETAGE)
        etage=NBETAGE-1;

    return etage;
}
/****************************************************
se rendre à l'étage séléctioné
****************************************************/
int move(int y, int etage)
{
int pas;
    pas=(y<etage) ? 1 : -1;

    if(etage>=0){
        while (y!=etage){
            // effacer ascenseur
            affiche_etage(y,COULEUR);
            y+=pas;  // bouger ascenseur
            // afficher ascenseur
            affiche_etage(y,COULEUR<<4);
        }
    }
    return y;
}
/**********************************************
tools curseur écriture
( tools : en quelque sorte, ne fait pas partie
 de l'algorithme spécifique à la tour infernale)
**********************************************/
void gotoxy(int x, int y)
{
COORD c;

    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/**********************************************
tools couleur
**********************************************/
void textcolor(int color)
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}


/****************************************************
****************************************************/
