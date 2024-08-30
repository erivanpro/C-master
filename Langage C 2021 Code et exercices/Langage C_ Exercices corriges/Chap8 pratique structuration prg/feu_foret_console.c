#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.c>

// taille du terrain
#define TX  80
#define TY  24

// les deux plans en miroir
int P[TY][TX];
int NP[TY][TX];

// les différentes valeurs possibles
enum {VIDE,BOIS,FEU,CENDRE};

// pour définir un seuil statistique
#define MAXI   1000
#define SEUIL  0.6*MAXI

// réservé activité du feu
int cmpt_feu=0;

void     init_bois      (void);
int      mise_a_feu     (void);
void     propagation    (void);
void     affiche_plan   (void);

/*******************************************************************
*******************************************************************/
int main()
{
int fin=0;
   srand(time(NULL));
   while (fin!='q'){
      if(kbhit()){
         fin = getch();
         init_bois();
         cmpt_feu = mise_a_feu();
      }
      if(cmpt_feu){
         propagation();
         affiche_plan();
      }
   }
   return 0;
}
/*******************************************************************
initialisation du bois
*******************************************************************/
void init_bois()
{
int x,y;
   for (y=0; y<TY; y++)
      for (x=0; x<TX; x++){
         if ((rand()%MAXI)<SEUIL)
            P[y][x]=BOIS;
         else
            P[y][x]=VIDE;
      }
}
/*******************************************************************
initialisation du feu : la deuxième colone
*******************************************************************/
int mise_a_feu()
{
int y,x=1,cmpt=0;

   for ( y=0; y<TY; y++)          //
      if (P[y][x]==BOIS){
         P[y][x]=FEU;
         cmpt++;
      }
   memcpy(NP,P,sizeof(int)*TY*TX);  //

   return cmpt;                     //
}
/*******************************************************************
propagation
*******************************************************************/
void propagation()
{
int x,xo,xe,y,yn,ys;
   for (y=0; y<TY; y++){
      yn=(y-1+TY)%TY;      // nord
      ys=(y+1)%TY;         // sud
      for (x=0; x<TX; x++){
         xo=(x-1+TX)%TX;   // ouest
         xe=(x+1)%TX;      // est
         if(P[y][x]==BOIS){ // si bois et
            if (P[yn][x]==FEU || P[ys][x]==FEU || // feu autour
                P[y][xo]==FEU || P[y][xe]==FEU   ){
                  NP[y][x]=FEU; // passe en feu en miroir
                  cmpt_feu++;
            }
         }
         else if(P[y][x]==FEU){ // mais si feu
            NP[y][x]=CENDRE;     // passe à cendre en miroir
            cmpt_feu--;
         }
      }
   }
   // recopie miroir
   memcpy(P,NP,sizeof(int)*TY*TX);
}
/*******************************************************************
affichage
*******************************************************************/
void affiche_plan()
{
int y,x;
   for (y=0; y<TY; y++){
      for (x=0; x<TX; x++){
         switch(P[y][x]){
            case VIDE   : textcolor(0);      break;
            case BOIS   : textcolor(6*16);   break;
            case FEU    : textcolor(12*16);  break;
            case CENDRE : textcolor(7*16);  break;
         }
         gotoxy(x,y);
         putchar(' ');
      }
   }
}
/*******************************************************************
*******************************************************************/

