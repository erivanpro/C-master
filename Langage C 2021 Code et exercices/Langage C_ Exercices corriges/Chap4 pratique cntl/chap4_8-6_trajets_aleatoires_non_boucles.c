/*
        VOITURE V : chaque voiture possède
        son propre circuit
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define TX          80
#define TY          20
#define NBV_MAX     100       // nombre de voiture
#define NBT_MAX     10         // ombre de traits
// nouvelle structure
typedef struct{
    int dir,pas;
}trait;

typedef struct{
    trait t[NBT_MAX];  // tableau de 6 traits
    int nbTrait;
    int nbTour;

}circuit;

typedef struct{
    int startx, starty, x,y;
    trait t;    // le trait courant
    int idTrait;
    int cmpTour;
    int vit,tmps;
    int color1,color2,lettre;
    circuit c; // le circuit associé à la voiture
}voiture;

trait       init_trait          (int d, int p);
circuit     init_circuit1       (void);
voiture     init_voit           (int startx, int starty,
                                 int c1, int c2, int l);
void        init_all_voit       (voiture v[]);
int         is_suite            (voiture v);
voiture     suite               (voiture v);
int         top                 (voiture v);
voiture     avancer             (voiture v);
voiture     move                (voiture v);
void        move_all            (voiture v[]);
void        affiche_pos         (int x, int y, int l, int color);
void        gotoxy              (int x, int y);
void        textcolor           (int color);
/*****************************************************************
*****************************************************************/
int main()
{
voiture v[NBV_MAX];

    srand(time(NULL));
    init_all_voit(v);
    while( !kbhit())
        move_all(v);

    gotoxy(0,TY);
    return 0;
}
/**********************************************************
creer des circuits (nord=0, est=1,sud=2 ouest=3)
**********************************************************/
/*
initialisation d'un trait
*/
trait init_trait(int d, int p)
{
trait t;
    t.dir=d;
    t.pas=p;
    return t;
}

/***************************************
construction du circuit 1, un simple rectangle.
->initialisation des variables du circuit
*/
circuit creer_circuit_alea()
{
circuit c;
int i;

    c.nbTrait=1+rand()%(NBT_MAX-1);
    //c.nbTour=1+rand()%10; // ne sert plus

    // le tableau des traits qui composent le circuit
    //c.t[0]=init_trait(rand()%4,10); // si retour interdit
    for (i=0; i<c.nbTrait; i++){

        /* //pour interdir retour sur ses pas
        int dir=rand()%4;
        interdit= (c.t[i-1]+2)%4;
        if(dir==interdit){
            if(rand()%2)
                dir=(dir+1)%4
            else
                dir=(dir-1+4)%4
        }
        */
        c.t[i]=init_trait(rand()%4,1+rand()%10);

    }
    return c;
}
/***************************************
initialisation d'une voiture
*/
voiture init_voit(int startx, int starty, int c1, int c2, int l)
{
voiture v;
    v.startx=v.x=startx;
    v.starty=v.y=starty;
    v.color1=c1;
    v.color2=c2;
    v.lettre=l;

    v.cmpTour=0;
    v.idTrait=0;
    v.t=init_trait(0,0);
    v.tmps=v.vit=0;

    v.c = creer_circuit_alea();
    return v;
}
/***************************************
initialisation de toutes les voitures
*/
void init_all_voit(voiture v[])
{
int i;
    for (i=0; i<NBV_MAX; i++)
        v[i]=init_voit(rand()%TX,rand()%TY,0,i+9,'A'+rand()%26);
}
/**********************************************************
Avancer
**********************************************************/

/***************************************
faut-il changer le trait à parcourir ?
*/
int is_suite(voiture v)
{
    return v.t.pas==0; // oui si 1
}
/***************************************
sélection du trait à parcourir
*/
voiture suite(voiture v)
{
    // controler si un tour a été exécuté
    if (v.idTrait==v.c.nbTrait){
        v.cmpTour++; // ne sert plus
        v.idTrait=0;
    }
    // contrôle du temps
    v.tmps=clock();
    // changer la vitesse (la vitesse de la voiture n'est pas constante)
    v.vit=150+rand()%150;

    // prendre définition nouveau trait dans le tableau du circuit
    v.t = v.c.t[ v.idTrait ];

    // préparer pour le trait suivant
    v.idTrait++;

    return v;
}
/***************************************
 topage voiture
*/
int top(voiture v)
{
    return (clock()>v.tmps+v.vit);
}
/***************************************
parcourir le trait courant
*/
voiture avancer(voiture v)
{
    if(v.t.pas--){ //Si un pas faire avancer
        // effacer
        affiche_pos(v.x, v.y, v.lettre, v.color1);
        // selon direction, écran circulaire
        switch(v.t.dir){
            case 0 : v.y = (v.y-1+TY)%TY;  break;
            case 1 : v.x = (v.x+1+TX)%TX;  break;
            case 2 : v.y = (v.y+1+TY)%TY;  break;
            case 3 : v.x = (v.x-1+TX)%TX;  break;
        }

        // afficher à nouvelle position dans un écran
        // circulaire
        affiche_pos(v.x, v.y, v.lettre, v.color2);
    }
    return v;
}
/***************************************
MOVE    : toutes les opérations pour avancer une voiture
*/
voiture move(voiture v)
{
    if (top(v)){
        v.tmps=clock();
        if(is_suite(v))
            v=suite(v);
        v=avancer(v);
    }
    return v;
}
/***************************************
MOVE ALL   : avancer toutes les voitures
*/
void move_all(voiture v[])
{
int i;
    for (i=0; i<NBV_MAX; i++)
        v[i]=move(v[i]);
}
/**********************************************************
Tools
**********************************************************/
/*
afficher une position
*/
void affiche_pos(int x, int y, int l, int color)
{
    gotoxy(x,y);
    textcolor(color);
    putchar(l);
}
void gotoxy(int x, int y)
{
COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
/*
donne ensemble couleur de fond et couleur de face (lettre)
*/
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
/**********************************************************
**********************************************************/
