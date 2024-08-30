/**********************************************************
    VOITURE 5B : CHAQUE VOITURE A SON CIRCUIT
    - création de circuits aléatoires
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
#define MAXVOITURE  60
#define MAXPAS      10

enum{ NORD,EST,SUD,OUEST};

typedef struct{
    int dir, pas;
}t_trait;

typedef struct{
    int startx, starty;     // point de départ du circuit
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
t_trait        init_trait           (int dir, int pas);
t_circuit      create_circuit_alea  (int startx, int starty);
t_voiture      create_voiture       (int startx, int starty,
                                     int c1,int c2,int l);
t_voiture      bouge                (t_voiture v );
int            run                  (t_voiture v );
t_voiture      select_trait         (t_voiture v );
t_voiture      avancer              (t_voiture v);
void           afficher             (t_voiture v,int color);
int            top                  (t_voiture v);
void           gotoxy               (int x, int y);
void           textcolor            (int color);
void           pause                (int x, int y);
/********************************************************
ACTION
********************************************************/
int main()
{
t_voiture v[MAXVOITURE];
int i, fin=0;
int cmpt;   // compter les voitures qui ont fini

    srand(time(NULL));

    // initialisation des voitures (circuit compris)
    for (i=0; i<MAXVOITURE; i++)
        v[i]=create_voiture(rand()%TX,rand()%TY,i,i+10, i+'1');


    while(!fin){

        for(i=0; i<MAXVOITURE; i++)
            v[i]=bouge(v[i]);

        // fin de la boucle si toutes les voitures
        // ont terminé
        for (i=0,cmpt=0; i<MAXVOITURE; i++)
            cmpt+=run(v[i]); // run retourne 0 si arrêtée

        if(cmpt==0)
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

t_circuit create_circuit_alea(int startx, int starty)
{
t_circuit c;
int i,dir,pas,interdit;

    // point de départ du circuit passé en paramètre
    c.startx=startx;
    c.starty=starty;

    // un nombre aléatoire de traits
    c.nbtrait = 1+rand()%MAXTRAIT;

    // nombre aléatoire de tour
    c.nbtour = 1+rand()%4;

    // création de traits aléatoires avec
    // - retour en arrière sur même trait interdit
    // - sortie fenêtre évitée

    interdit=-1;
    // pour chaque trait initialiser dir et pas
    for (i=0; i<c.nbtrait; i++){

        // direction
        dir = rand()%4;
        // contrôler retour en arrière
        if (dir==interdit){
            if(rand()%2)
                dir = (dir+1)%4;
            else
                dir = (dir-1+4)%4;
        }
        // interdit = inverse (retour arrière) pour
        // le trait suivant
        interdit = (dir+2) %4;

        // un nombre de pas
        pas=1+rand()%MAXPAS;
        // contrôler si la voiture reste dans la
        // fenêtre console.
        switch(dir){
            case NORD :
                // si sortie le nombre de pas du trait est 0
                pas = (starty - pas >= 0)? pas: 0;
                starty -= pas;
                break;

            case EST :
                pas = (startx + pas < TX) ? pas : 0;
                startx += pas;
                break;

            case SUD :
                pas = (starty + pas < TY) ? pas : 0;
                starty += pas;
                break;

            case OUEST :
                pas = (startx - pas >= 0) ? pas : 0;
                startx -= pas;
                break;
        }
        c.t[i]=init_trait(dir,pas);
    }
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
    v.c = create_circuit_alea(startx,starty);
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
        v.x=v.c.startx;
        v.y=v.c.starty;
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
