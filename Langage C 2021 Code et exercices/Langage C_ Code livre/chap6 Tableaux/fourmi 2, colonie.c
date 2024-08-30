/**********************************************************
    FOURMI 2 : UNE COLONIE DE FOURMIS
**********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// en global définition du type de ma structure fourmi
typedef struct {
    float x,y;      // la position de la fourmi
    float dx,dy;    // le déplacement
    int color;      // la couleur
    int lettre;     // l'apparence
}t_fourmi;

// Limites de la zone de jeu
const int TX=80;
const int TY=20;
// nombre max de fourmis
const int MAXFOURMI = 50;

// les actions
t_fourmi   init_fourmi      (void);
void       init_colonie     (t_fourmi f[]);
void       affiche_fourmi   (t_fourmi f, int color);
t_fourmi   avance_fourmi    (t_fourmi f);
void       run_colonie      (t_fourmi f[]);
int        top              (int*start, int dur);
void       gotoxy           (int x, int y);
void       textcolor        (int color);
/*************************************************************
ACTION
*************************************************************/
int main()
{
int start = 0;
t_fourmi all[MAXFOURMI];

    srand(time(NULL));

    init_colonie(all);
    while(!kbhit()){

        if(top(&start, 75))
            run_colonie(all);
    }
    return 0;
}
/*************************************************************
INITIALISATION
*************************************************************/
t_fourmi init_fourmi()
{
t_fourmi f;
    f.x = rand()%TX;
    f.y = rand()%TY;
    f.dx = ((float)rand()/RAND_MAX)*4 - 2;
    f.dy = ((float)rand()/RAND_MAX)*4 - 2;
    f.lettre = 'A'+rand()%26;
    f.color = 1 + rand()%255;
    return f;
}
void init_colonie(t_fourmi f[])
{
int i;
    for (i=0; i<MAXFOURMI; i++)
        f[i]=init_fourmi();
}
/*************************************************************
AFFICHAGE une fourmi
*************************************************************/
void affiche_fourmi(t_fourmi f, int color)
{
    gotoxy(f.x, f.y);
    textcolor(color);
    putchar(f.lettre);
}
/*************************************************************
MOUVEMENT une fourmi
*************************************************************/
t_fourmi avance_fourmi(t_fourmi f)
{
    f.x+=f.dx;
    if (f.x < 0){
        f.x=0;
        f.dx = ((float)rand()/RAND_MAX)*2;
    }
    if (f.x>=TX){
        f.x=TX-1;
        f.dx = ((float)rand()/RAND_MAX)* -2;
    }

    f.y+=f.dy;
    if (f.y < 0){
        f.y=0;
        f.dy = ((float)rand()/RAND_MAX)*2;
    }
    if (f.y>=TY){
        f.y=TY-1;
        f.dy = ((float)rand()/RAND_MAX)* -2;
    }
    return f;
}
/*************************************************************
RUN : animer toutes les fourmis
Le choix est ici d'animer chaque fourmi une par une plutôt
que toute la colonie d'un coup pour éviter l'effet de "page"
avec un léger interval au noir(effacement de toutes les fourmis,
avancer toutes les fourmis,ré-afficher toutes les fourmis)
*************************************************************/
void run_colonie(t_fourmi f[])
{
int i;

    for (i=0; i<MAXFOURMI; i++){
        affiche_fourmi(f[i],0);
        f[i]=avance_fourmi(f[i]);
        affiche_fourmi(f[i],f[i].color);
    }
}
/*************************************************************
OUTILS
*************************************************************/
int top(int*start, int dur)
{
int res=0;
    if(clock()>*start+dur){
        *start=clock();
        res=1;
    }
    return res;
}
void gotoxy(int x, int y)
{
 COORD c;
        c.X=x;
        c.Y=y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
void textcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
/*************************************************************
*************************************************************/
