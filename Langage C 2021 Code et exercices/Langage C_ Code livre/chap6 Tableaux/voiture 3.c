/**********************************************************
    VOITURE 3 : UNE STRUCTURE TRAIT ET UN TABLEAU DE TRAIT
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
// Les quatre directions
enum{ NORD,EST,SUD,OUEST};

/* Pour un circuit :
- 6 traits max
- un trait = une direction et un nombre de pas
- un nombre de traits
- un nombre de tours
*/
// pour avoir un circuit :
typedef struct{
    int dir, pas;
}t_trait;

typedef struct{
    t_trait t[MAXTRAIT]; // 6 traits
    int nbtrait;    // nombre de trait dans le circuit
    int nbtour;     // nombre de tour à faire pour une course
}t_circuit;

/*Pour une voiture :
- une position x,y
- une direction
- un nombre de pas
- un identificateur du trait courant
- un compteur de tours
- une vitesse
- le temps de départ (associé à vitesse)

En option, pour différencier toutes les voitures
avec couleur et apparence :
- une lettre pour l'apparence
- une couleur d'effacement
- une couleur d'affichage
*/
typedef struct{
    int x,y,idtrait,tour,vit,tmps;
    t_trait t;          // direction et pas
    int lettre;         // lettre correspondante
    int color1,color2;  // deux couleurs
}t_voiture;

// les déclarations des fonctions
t_trait        init_trait       (int dir, int pas);
t_circuit      create_circuit1  (void);
t_voiture      create_voiture   (int startx, int starty,
                                 int c1,int c2,int l);
t_voiture      bouge            (t_voiture v,t_circuit c);

int            run              (t_voiture v1,t_voiture v2,
                                 t_voiture v3,t_voiture v4,
                                 t_circuit c);

t_voiture      select_trait     (t_voiture v,t_circuit c);
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
t_circuit c;
t_voiture v1,v2,v3,v4;

    srand(time(NULL));
    c=create_circuit1();
    v1=create_voiture(2,2,0,10,'1');
    v2=create_voiture(3,3,1,11,'2');
    v3=create_voiture(4,4,2,12,'3');
    v4=create_voiture(5,5,3,13,'4');

    while(run(v1,v2,v3,v4,c)){

        v1=bouge(v1,c);
        v2=bouge(v2,c);
        v3=bouge(v3,c);
        v4=bouge(v4,c);

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
    /*c.t[0]=init_trait(EST,10);
    c.t[1]=init_trait(SUD,10);
    c.t[2]=init_trait(OUEST,10);
    c.t[3]=init_trait(NORD,10);
    */
    // peut être remplacé par
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
    return v;
}
/********************************************************
BOUGER
********************************************************/
/*
contrôle de la fin de la course. La course continue tant
qu'aucune voiture n'a fini et s'arrête dés qu'une voiture
a fini
*/
int run(t_voiture v1, t_voiture v2,
        t_voiture v3, t_voiture v4,
        t_circuit c)
{
    return (v1.tour<c.nbtour && v2.tour<c.nbtour &&
            v3.tour<c.nbtour && v4.tour<c.nbtour);
}
// topage voitures
int top(t_voiture v)
{
    return (clock() > v.tmps + v.vit);
}
/*

*/
t_voiture bouge (t_voiture v, t_circuit c)
{
    if(top(v)){
            v.tmps=clock();
            if(v.t.pas==0)
                v=select_trait(v,c);
            v=avancer(v);
    }
    return v;
}
/*
sélectionner un trait à parcourir
*/
t_voiture select_trait(t_voiture v, t_circuit c)
{
   // contrôler si un tour a été effectué
   if(v.idtrait == c.nbtrait){
        v.tour++;
        v.idtrait=0;
   }

   // changer la vitesse pour chaque trait
   v.vit=150+rand()%150;

   // sélection du trait donné par le champ idtrait pris
   // comme indice dans le tableau des traits du circuit
   v.t=c.t[v.idtrait];

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
