/**********************************************************
    VOITURE 5 : CHAQUE VOITURE A SON CIRCUIT
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// taille de la zone de jeu
#define TX          80
#define TY          24
#define MAXTRAIT    6
#define MAXVOITURE  6

enum{ NORD,EST,SUD,OUEST};

typedef struct{
    int dir, pas;
}t_trait;

typedef struct{
    t_trait t[MAXTRAIT];
    int nbtrait;
    int nbtour;
}t_circuit;

typedef struct{
    int x,y,idtrait,tour,vit,tmps;
    t_trait t;          // direction et pas
    int lettre;
    int color1,color2;
    t_circuit c;        // chaque voiture a son circuit
}t_voiture;

// les déclarations des fonctions
t_trait        init_trait       (int dir, int pas);
t_circuit      create_circuit1  (void);
t_voiture      create_voiture   (int startx, int starty,
                                 int c1,int c2,int l);
t_voiture      bouge            (t_voiture v );
int            run              (t_voiture v );
t_voiture      select_trait     (t_voiture v );
t_voiture      avancer          (t_voiture v);
void           afficher         (t_voiture v,int color);
int            top              (t_voiture v);
void           gotoxy           (int x, int y);
void           textcolor        (int color);
void           pause            (int x, int y);
/********************************************************
ACTION
********************************************************/
int main()
{
t_voiture v[MAXVOITURE];
int i, fin=0;

    srand(time(NULL));

    // initialisation des voitures (circuit compris)
    for (i=0; i<MAXVOITURE; i++)
        v[i]=create_voiture(i+2,i+2,i,i+10, i+'1');


    while(!fin){

        for(i=0; i<MAXVOITURE; i++)
            v[i]=bouge(v[i]);

        // contrôle fin boucle
        for (i=0; i<MAXVOITURE; i++)
            if(!run(v[i]))
                fin=1;

    }

    pause(0,TY);
    return 0;
}
/********************************************************
CREATION, CIRCUIT, VOITURES
********************************************************/
t_trait init_trait(int dir, int pas)
{
t_trait t;
    t.dir=dir;
    t.pas=pas;
    return t;
}

t_circuit create_circuit1()
{
t_circuit c;
int i;
    // définition du circuit
    for (i=0; i<4; i++)
        c.t[i]=init_trait((i+1)%4, 10);

    c.nbtrait = 4;
    c.nbtour = 2;

    return c;
}
/********************************************************
CREATION VOITURE
********************************************************/
t_voiture create_voiture(int startx, int starty, int c1,
                              int c2, int l)
{
t_voiture v;

    v.x=startx;
    v.y=starty;
    v.t=init_trait(0,0);
    v.idtrait=0;
    v.tour=0;
    v.tmps=0;
    v.vit=0;
    v.color1=c1;
    v.color2=c2;
    v.lettre=l;

    // le circuit de la voiture, toutes auront le même
    v.c = create_circuit1();
    return v;
}
/********************************************************
BOUGER
********************************************************/
/*
la voiture a-t-elle terminé ?
*/
int run(t_voiture v)
{
    return v.tour<v.c.nbtour ;
}
// topage voitures
int top(t_voiture v)
{
    return (clock() > v.tmps + v.vit);
}
/*

*/
t_voiture bouge (t_voiture v)
{
    if(top(v)){
        v.tmps=clock();
        if(v.t.pas==0)
            v=select_trait(v);
        v=avancer(v);
    }
    return v;
}
/*
sélectionner un trait à parcourir
*/
t_voiture select_trait(t_voiture v)
{
   // contrôler si un tour a été effectué
   if(v.idtrait == v.c.nbtrait){
        v.tour++;
        v.idtrait=0;
   }

   // changer la vitesse pour chaque trait
   v.vit=150+rand()%150;

   // sélection du trait donné par le champ idtrait pris
   // comme indice dans le tableau des traits du circuit
   v.t=v.c.t[v.idtrait];

   // préparer pour le tour suivant
   v.idtrait++;

   return v;
}
/*
parcourir le trait courant
*/
t_voiture avancer(t_voiture v)
{
    if(v.t.pas>0){
        v.t.pas--; // un pas de moins

        // effacer
        afficher(v,v.color1);

        // avancer selon direction
        switch(v.t.dir){
            case NORD :     v.y--;  break;
            case EST :      v.x++;  break;
            case SUD :      v.y++;  break;
            case OUEST :    v.x--;  break;
        }

        // ré-afficher
        afficher(v,v.color2);
    }
    return v;
}
/*
afficher une voiture de la couleur color
*/
void afficher(t_voiture v,int color)
{
    gotoxy(v.x,v.y);
    textcolor(color);
    putchar(v.lettre);
}
/********************************************************
OUTILS
********************************************************/
// déplacement curseur
void gotoxy(int x, int y)
{
 COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
// gestion couleur
void textcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
// arrêter la console
void pause(int x, int y)
{
    gotoxy(x, y);
    printf("Appuyez sur Enter pour continuer...");
    rewind(stdin);
    char c = getchar();
}
/********************************************************
********************************************************/
