/************************************************************
*                                                           *
*       CHAPITRE 11 : Récursivité                           *
*                                                           *
*************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de préférence vide sous visual studio)
    - copier toute la page dans le fichier C du nouveau projet (écraser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte immédiatement ajouter
      getchar(); avant le return 0; de fin de main()
      (ou voir Chap 1 / Conserver la fenêtre console ouverte)
    - remettre les commentaires pour tester un autre programme
*/
/****************************************************
*                                                   *
*       1. Fonctions récursives                     *
*                                                   *
*****************************************************/


//Une fonction récursive basique
/*
#include <stdio.h>
void affiche(int n)
{
   if (n>0)
      affiche(n-1);
   printf("%d ",n);
}
int main()
{
   affiche(5);
   return 0;
}
*/
/*
#include <stdio.h>
void affiche(int n)
{
	printf("%d ",n);		// affichage au début
   if (n>0)
      affiche(n-1);
}
int main()
{
   affiche(5);
   return 0;
}
*/
/*
#include <stdio.h>
void affiche(int n)
{
	printf("%d ",n);		// affichage au début
   if (n>0)
      affiche(n-1);
   printf("%d ",n);		// et à la fin
}
int main()
{
   affiche(5);
   return 0;
}
*/
/*
#include <stdio.h>
 void affiche(int n)
{
int i;
	for (i=0; i<=n; i++)
   	   printf("%d ",i);
}
int main()
{
   affiche(5);
   return 0;
}
*/
//--------------------------------------------------
//Pile d'appels et débordement
/*
#include <stdio.h>

void deborde (unsigned int*cmpt)
{
   printf("%d\n",(*cmpt)++);
   deborde(cmpt);
}

int main()
{
unsigned int cmpt=0;
    deborde(&cmpt);
    return 0;
}
*/
//--------------------------------------------------
//Retourner une valeur
/*
#include <stdio.h>

int add(int n)
{
int res=n;
   if (n>0){
     res+=add(n-1);
   }
   return res;
}

int main()
{
   printf("res=%d",add(5));
   return 0;
}
*/
/*
#include <stdio.h>

int add(int n)
{
   if (n>0){
      n+=add(n-1);
   }
   return n;
}
int main()
{
   printf("res=%d",add(5));
   return 0;
}
*/
/*
#include <stdio.h>
int add(int n)
{
   return (n>0) ? n + add(n-1) : 0;
}
int main()
{
   printf("res=%d",add(5));
   return 0;
}
*/
//--------------------------------------------------
/*
#include <stdio.h>
int cmpt(int n, int a)
{
	if (n<a)
      return 0;
  	return 1 + cmpt(n-a, a);
}
int main()
{
    printf("16/5 : %d\n",cmpt(16,5));
    return 0;
}
*/
/*
#include <stdio.h>
int cmpt(int n, int a)
{
   return n < a ? 0 : 1 + cmpt(n-a, a);
}
int main()
{
    printf("16/5 : %d\n",cmpt(16,5));
    return 0;
}
*/
/*
#include <stdio.h>
int res=0;

void cmpt(int n, int a)
{
  if (n>=a){
     res++;
     cmpt(n-a,a);
  }
}
int main()
{
    cmpt(16,5);
    printf("16/5 : %d\n",res);
    return 0;
}
*/
/*
#include <stdio.h>
void cmpt(int n, int a,int*res)
{
  if (n>=a){
     (*res)++;
     cmpt(n-a,a,res);
  }
}
int main()
{
int res=0;
    cmpt(16,5,&res);
    printf("16/5 : %d\n",res);
    return 0;
}
*/
/*
#include <stdio.h>
int cmpt(int n, int a)
{
static int res=0;
  if (n>=a){
     res++;
     cmpt(n-a,a);
  }
  return res;
}
int main()
{
    printf("16/5 : %d\n",cmpt(16,5));
    return 0;
}
*/
//--------------------------------------------------
//Se représenter et analyser le fonctionnement
/*
#include <stdio.h>

void p(int n)
{
	if (n>0){
      p(n-2);
      printf("%3d",n);
      p(n-1);
	}
}

int main()
{
   p(4);
   return 0;
}
*/
//--------------------------------------------------
//Choisir entre itératif ou récursif
/*
#include <stdio.h>

void somme(int*s)
{
int n;
   if (scanf("%d",&n)==1){
      *s+=n;
      somme(s);
   }
}

int main()
{
int res=0;
   printf("entrer des nombres, une lettre pour arrêter  :\n");
   somme(&res);
   printf("resultat : %d\n",res);
   return 0;
}
*/
/*
#include <stdio.h>
void somme(int*s)
{
int n;
   while (scanf("%d",&n)==1)
      *s+=n;
}
int main()
{
int res=0;
   printf("entrer des nombres, une lettre pour arrêter  :\n");
   somme(&res);
   printf("resultat : %d\n",res);
   return 0;
}
*/
/********************************************************
*                                                       *
*       2. Exemples classiques de fonctions récursives  *
*                                                       *
*********************************************************/
//Afficher les chiffres d'un entier
/*
#include <stdio.h>
void chiffreIter (int val)
{
   while (val>0){
       printf("%d_", val%10);
       val/=10;
   }
}

void chiffre(int val)
{
   if (val>0){
      printf("%d_", val%10);
      chiffre(val/10);
   }
}

int main()
{
int nb;
    printf("entrer un nombre :\n");
    scanf("%d",&nb);
    chiffreIter(nb);
    putchar('\n');
    chiffre(nb);
    return 0;
}
*/
//--------------------------------------------------
//Factorielle
/*
#include <stdio.h>
int factIter (int n)
{
int res=1;
   while (n>1)
      res*=n--;  // attention décrémentation après multiplication
   return res;
}

int fact(int n)
{
   if (n==0)
      return 1;
   else
      return n*fact(n-1);
}

int fact_(int n)
{
	return n>1 ? n*fact(n-1) : 1;
}
int main()
{
    printf("%d\n",factIter(5));
    printf("%d\n",fact(5));
    printf("%d\n",fact_(5));
    return 0;
}
*/
//--------------------------------------------------
//Suite de Fibonacci
/*
#include <stdio.h>
int fibIter(int n)
{
int i,res,f1,f2;

   if (n<=1)
      res=n;
   else{
      f2=0;
      f1=1;
      for (i=2; i<=n; i++){
         res=f2+f1;
         f2=f1;
         f1=res;
      }
   }
   return res;
}


int fib(int n)
{
   if (n<=1)
      return n;
   else
      return fib(n-2)+fib(n-1);
}

int fib_(int n)
{
   return n<=1 ? n : fib(n-2)+fib(n-1);
}
int main()
{
    printf("%d\n", fibIter(10));
    printf("%d\n", fib(10));
    printf("%d\n", fib_(10));

    return 0;
}
*/
//--------------------------------------------------
//Changement de base arithmétique d'un nombre
/*
#include <stdio.h>
void conversionIter (int val, int base)
{
int pile[100];
int sommet=0;
   while (val>0){
       pile[sommet++] = val % base;
       val /= base;
   }
   for (--sommet; sommet>=0; sommet--)
      if(pile[sommet]<=9)
         printf("%d",pile[sommet]);
      else
         printf("%c",pile[sommet]-10+'A');
}

void conversion (int val, int base)
{
static char chif[]="0123456789ABCDEF";  // de 0 à 15

   if (val/base != 0)
      conversion(val/base,base);
   printf("%c",chif[val%base]);   // vaut entre 0 et 15 compris
}
int main()
{
int val,base;
    printf("entrer un nombre en base 10 et la nouvelle base :\n");
    scanf("%d%d",&val,&base);
    conversionIter(val,base);
    putchar('\n');
    conversion(val,base);
    return 0;
}
*/
/*
#include <stdio.h>
int convert10Iter (int val, int base)
{
int res,b,r;
   b=1;
   res=val%10;
   while (val>0){
      val=val/10;
      r=val%10;
      b*=base;
      res+=r*b;
   }
   return res;
}

int convert10(int val, int base)
{
   if (val/10 ==0)
      return val%10;
   else
      return convert10(val/10,base)* base + val % 10;
}
int main()
{
    int nb, base;
    printf("entrer un nombre et sa base (hors hexadecimale) :\n");
    scanf("%d%d",&nb,&base);
    printf("en base 10 : %d\n",convert10Iter(nb,base));
    printf("en base 10 : %d\n",convert10(nb,base));
    return 0;
}
*/
//--------------------------------------------------
//Puissance
/*
#include <stdio.h>
int puissance(int x, int n)
{
   if (n==0)
      return 1;
   else
      return x*puissance(x,n-1);
}

int puissance1(int x, int n)
{
   return (n==0) ? 1 :x*puissance1(x,n-1);
}

int puissance2(int x, int n)
{
int res;
   if (n==0)
      res = 1;
   else{
      res=puissance2(x, n/2);
      if(n%2==0) // si pair
         res=res*res;
      else
         res=res*res*x;
   }
   return res;
}
int main()
{
int nb,p;
    printf("entrer unombre et sa puissance :\n");
    scanf("%d%d",&nb,&p);
    printf("%d puissance %d = %d\n", nb,p,puissance(nb,p));
    printf("%d puissance %d = %d\n", nb,p,puissance1(nb,p));
    printf("%d puissance %d = %d\n", nb,p,puissance2(nb,p));
    return 0;
}
*/
//--------------------------------------------------
//PGCD, algorithme d'Euclide
/*
#include <stdio.h>
int pgcdIter1(int x, int y)
{
int t;
   while (x != y){
      if (x < y){
         t = x;
         x = y;
         y = t;
      }
      x -= y;
   }
   return x;
}

int pgcdIter2(int x, int y)
{
int m;
   while(y){
      m=x%y;
      x=y;
      y=m;
   }
	return x;
}

int pgcd1(int x, int y)
{
   if (y)
      return pgcd1(y,x%y);
   else
      return x;
}

int pgcd2(int x, int y)
{
   return (y) ? pgcd2(y,x%y) : x;
}
int main()
{
int nb1, nb2;
    printf("entrer deux nombres :\n");
    scanf("%d%d",&nb1, &nb2);
    printf("PGCD de %d et %d = %d\n",nb1, nb2, pgcdIter1(nb1,nb2));
    printf("PGCD de %d et %d = %d\n",nb1, nb2, pgcdIter2(nb1,nb2));
    printf("PGCD de %d et %d = %d\n",nb1, nb2, pgcd1(nb1,nb2));
    printf("PGCD de %d et %d = %d\n",nb1, nb2, pgcd2(nb1,nb2));
    return 0;
}
*/
//--------------------------------------------------

//Dessins
//Tracé d'une règle graduée : "diviser pour résoudre"
/*
#include <stdio.h>
#include <windows.h>

void gotoxy(int x, int y)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
COORD c;
   c.X=x;
   c.Y=y;
   SetConsoleCursorPosition(h,c);
}

void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}

void trace(int hpos, int h)
{
   gotoxy(hpos,0);
   textcolor(15-h);
   printf("%d",h);
}

void regle(int gauche, int droite, int hauteur)
{
int milieu=(gauche+droite)/2;

   if (hauteur>0){
      trace(milieu,hauteur);
      regle(gauche,milieu,hauteur-1);
      regle(milieu,droite,hauteur-1);
   }
}

void regleIter(int g, int d, int h)
{
int i,pas,j,m;
   for (i=1,pas=1,m=(g+d); i<=h; i++,pas*=2,m/=2)
      for (j=0; j<m;j++)
         trace((pas+pas*j)-1,i);  // -1 pour partir du bord
}

int main()
{
    regle(0,16,4); // puissance de 2, 8 et 3, 16 et 4, 32 et 5 etc.
    gotoxy(0,2);
    system("PAUSE");

    regleIter(0,16,4);
    gotoxy(0,2);
    return 0;
}
*/
//--------------------------------------------------
// Tracés récursifs de cercle ou rectangles
// Utilisation librairie ALLEGRO 5
/*
Le code qui suit necessite l'installation de la librairie graphique ALLEGRO 5
pour avoir les fonctions :
    al_draw_filled_circle(), 
    al_draw_rectangle(), 
    al_map_rgb() 
    al_draw_line().
Le mieux est d'installer la librairie pour le projet en utilisant le package Nuget
Allegro 5 fourni avec ses dépendances (voir chapitre Eléments graphiques avec Allegro)

Sinon le site officiel de la librairie est : https://liballeg.org/
et la documentation : https://liballeg.org/a5docs/trunk/
*/
/*
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}

void RecCercles(int x, int y, int r)
{
    int r2 = r / 2;
    ALLEGRO_COLOR color;
    if (r > 5) {
        color = al_map_rgb(rand() % 256, rand() % 128, rand() % 64);
        al_draw_filled_circle(x, y, r, color);
        RecCercles(x - r2, y, r2);
        RecCercles(x + r2, y, r2);
    }
}
void RecCarre(int x, int y, int c)
{
    int cc = c / 2;
    ALLEGRO_COLOR color;
    if (c > 2) {
        color = al_map_rgb(rand() % 256, rand() % 128, rand() % 64);
        al_draw_rectangle(x - c, y - c, x + c, y + c, color, 2);
        RecCarre(x - c, y - c, cc);
        RecCarre(x + c, y - c, cc);
        RecCarre(x + c, y + c, cc);
        RecCarre(x - c, y + c, cc);
    }
}

/*************************************************************
*************************************************************
int main()
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_KEYBOARD_STATE key;	// clavier simple
    int fin = 0;

    srand(time(NULL));

    // initialisations obligatoires
    if (!al_init()) // général
        erreur("al_init()");
    if (!al_init_primitives_addon())// dessin
        erreur("al_init_primitives_addon()");

    // création fenêtre
    int screenx = 1024;
    int screeny = 768;
    display = al_create_display(screenx, screeny);
    if (!display)
        erreur("create_display(screenx,screeny)");

    // pour utiliser le clavier
    if (!al_install_keyboard())
        erreur("al_install_keyboard()");

    while (!fin) {

        // récupération de l'état du clavier
        al_get_keyboard_state(&key);

        // si touche escape appuyée fin boucle et quitter
        if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
            fin = 1;

        // si Enter changer de couleur
        if (al_key_down(&key, ALLEGRO_KEY_ENTER)) {
            al_clear_to_color(al_map_rgb(rand() % 256,
                rand() % 256, rand() % 256));

            // fonction récursive de dessin de cercles
            RecCercles(screenx / 2, screeny / 2, 300);
        }
        if (al_key_down(&key, ALLEGRO_KEY_SPACE)) {
            al_clear_to_color(al_map_rgb(rand() % 256,
                rand() % 256, rand() % 256));

            RecCarre(screenx / 2, screeny / 2, 150);
        }
        // passer le double buffer à l'écran
        al_flip_display();
    }

    al_destroy_display(display);
    return 0;
}
*/
//--------------------------------------------------
// Tracé d'un arbre
// utilisation de la librairie ALLEGRO 5
/*
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#define PI        3.1416
#define DEGRE     2*PI/360.0

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}

// résultat en utilisant allegro
void segment(int l, int x, int y, int angle, int* rx, int* ry)
{
    int i;
    ALLEGRO_COLOR color;
    *rx = x + l * cos(angle * DEGRE);
    *ry = y - l * sin(angle * DEGRE);
    color = al_map_rgb(rand() % 32, rand() % 256, rand() % 128);
    for (i = 0; i < l / 15; i++)
        al_draw_line(x + i, y, *rx + i, *ry, color, 2);
}

void dessine_arbre(int h, int x, int y, int angle)
{
    int rx, ry, n, i, ev;
    // disymétrie aléatoire sur la taille des segments
     // (entre 0 et 10% en plus de h)
    h = h + 0.1 * (rand() % h);

    segment(h, x, y, angle, &rx, &ry);
    h = h * 2 / 3;
    if (h > 1) {
        // le nombre de branches est compris entre 1 et 7
        n = 1 + rand() % 8;
        ev = 180 / n;
        for (i = 1; i <= n; i++)
            dessine_arbre(h, rx, ry, angle - 90 - ev / 2 + i * ev);
    }
}

/*************************************************************
*************************************************************
int main()
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_KEYBOARD_STATE key;	// clavier simple
    int fin = 0;

    srand(time(NULL));

    // initialisations obligatoires
    if (!al_init()) // général
        erreur("al_init()");
    if (!al_init_primitives_addon())// dessin
        erreur("al_init_primitives_addon()");

    // création fenêtre
    int screenx = 1024;
    int screeny = 768;
    display = al_create_display(screenx, screeny);
    if (!display)
        erreur("create_display(screenx,screeny)");

    // pour utiliser le clavier
    if (!al_install_keyboard())
        erreur("al_install_keyboard()");

    while (!fin) {

        // récupération de l'état du clavier
        al_get_keyboard_state(&key);

        // si touche escape appuyée fin boucle et quitter
        if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
            fin = 1;

        // si Enter changer de couleur
        if (al_key_down(&key, ALLEGRO_KEY_ENTER)) {
            al_clear_to_color(al_map_rgb(rand() % 256,
                rand() % 256, rand() % 256));

            // fonction récursive de dessin d'un arbre
            dessine_arbre(100, 400, 500, 90);
        }

        // passer le double buffer à l'écran
        al_flip_display();
    }

    al_destroy_display(display);
    return 0;
}
*/
//--------------------------------------------------
//Créations et Jeux
//Trouver un chemin dans un labyrinthe
/*
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define TX           26
#define TY           20

static int MAT[TY][TX]={
    {0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0},
   	{0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0},
   	{0,1,1,0,0,1,1,0,1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0},
   	{0,1,0,0,0,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,0,0,1,0},
   	{0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,1,1,0},
   	{0,1,0,0,1,1,1,1,0,0,0,1,0,0,1,0,1,0,1,1,0,1,0,1,0,0},
 	{0,1,1,1,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,0,1,0,1,0,0},
   	{0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,0,0,1,0,1,0,1,0,0},
   	{0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0},
   	{0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,0,1,0,0,0,1,0},
   	{0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,0},
   	{0,1,0,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,1,1,0,1,0},
   	{0,1,1,1,1,0,0,0,0,0,0,0,1,0,2,0,0,1,1,1,0,0,1,0,1,0},
   	{0,0,0,0,1,0,0,1,1,1,1,1,1,0,1,0,0,0,0,1,0,0,1,1,1,0},
   	{0,0,0,0,1,0,0,1,0,0,0,0,1,1,1,1,0,0,1,1,1,1,1,0,0,0},
   	{0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,1,0,0},
   	{0,0,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0},
   	{0,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0},
   	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

#define BUT          2     // pour la couleur du trésor
#define MUR          0     // pour la couleur mur
#define BLEUCLAIR    4
#define ROUGE        11

void gotoxy(int x, int y)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
COORD c;
   c.X=x;
   c.Y=y;
   SetConsoleCursorPosition(h,c);
}

void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}


void affiche_posi(int x, int y, int color)
{
   gotoxy(x,y);
   textcolor( color<<4);
   putchar(' ');
}

void affiche_laby()
{
int x,y;
   for (y=0; y<TY; y++)
      for(x=0; x<TX; x++)
         affiche_posi(x,y,MAT[y][x]);
}

void attendre(int dure)
{
int start=clock();
   while (clock()<start+dure){}
}

int chemin (int x,int y,int olddir)
{
int i,nx,ny;

	// 1
   if (MAT[y][x]==BUT)
      return 1;
	// 2
   if (MAT[y][x]!=MUR ){
      // 3
      attendre(40);
      affiche_posi(x,y,BLEUCLAIR);
	   // 4
      for (i=0;i<4;i++)
         if(i!= (olddir+2)%4 ){
            // 5
            nx=x+(i%2)*(2-i);
            ny=y+((i+1)%2)*(i-1);
		  // 6
            if (chemin(nx,ny,i)){
               // 7
               attendre(45);
               affiche_posi(x,y,ROUGE);
               return 1;
            }
         }
   }
   return 0;
}

int main()
{
    affiche_laby();
    chemin(10,0,2);
    gotoxy(0,TY+1);
    return 0;
}
*/
//--------------------------------------------------
//Création d'un labyrinthe
/*
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define TX           26
#define TY           20
#define BUT          2     // couleur du trésor
#define MUR          0     // couleur mur
#define CHEMIN       1
#define ROUGE        4
#define BLEUCLAIR    11


static int MAT[TY][TX];

void gotoxy(int x, int y)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
COORD c;
   c.X=x;
   c.Y=y;
   SetConsoleCursorPosition(h,c);
}

void textcolor(int color)
{
HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(h,color);
}

void affiche_posi(int x, int y, int color)
{
   gotoxy(x,y);
   textcolor( color<<4);
   printf("%c",'0'+ MAT[y][x]);
}

void affiche_laby()
{
int x,y,color;
   for (y=0; y<TY; y++)
      for(x=0; x<TX; x++){
         //affiche_posi(x,y,MAT[y][x]);
         if (MAT[y][x]==0)
           color=ROUGE;
         else
            color=MAT[y][x];
         affiche_posi(x,y,color);
      }
}

void init_dir(int d[4])
{
int i,i1,i2,tmp;
   for (i=0; i<4; i++)
      d[i]=i;

   for (i=0; i<50;i++){
      i1=rand()%4;
      i2=rand()%4;
      if(i1!=i2){
         tmp=d[i1];
         d[i1]=d[i2];
         d[i2]=tmp;
      }
   }
}

void creuse_laby(int x,int y)
{
int d[4];
int i;

   MAT[y][x]=CHEMIN;
   init_dir(d);
   for (i=0; i<4; i++)
      switch(d[i]){
         case 0 :
            if (y>1 && MAT[y-2][x]== MUR){
                MAT[y-1][x]= CHEMIN;
                creuse_laby(x,y-2);
            }
            break;
         case 1 :
            if (x<TX-2 && MAT[y][x+2]== MUR){
                MAT[y][x+1]= CHEMIN;
                creuse_laby(x+2,y);
            }
            break;
         case 2 :
            if (y<TY-2 && MAT[y+2][x]== MUR){
                MAT[y+1][x]= CHEMIN;
                creuse_laby(x,y+2);
            }
            break;
         case 3 :
            if (x>1 && MAT[y][x-2]== MUR){
                MAT[y][x-1]= CHEMIN;
                creuse_laby(x-2,y);
            }
            break;
      }
}

int main()
{
    srand(time(NULL));
    while (getch()!='q'){
       memset(MAT,0,sizeof(int)*TX*TY);
       creuse_laby(rand()%TX,rand()%TY);
       affiche_laby();
    }

    gotoxy(0,TY+1);
    return 0;
}
*/
//--------------------------------------------------
//Les tours de Hanoï
/*
#include <stdio.h>
#include <stdlib.h>

void deplacement(int n, int d, int i, int a)
{
    if (n>0){
        deplacement(n-1, d,a,i);    // d vers i avec a intermédiaire

        // d vers a avec i intermédiaire
        printf("aller de %d a %d\n",d,a);

        deplacement(n-1,i,d,a);	   // i vers a avec d intermédiare
    }
}

void hanoi(int n,int d, int i, int a)
{
 	if (n==1)
	    printf("aller de %c en %c\n",d,a);
    else{
	        hanoi(n-1,d, a, i);
	        hanoi(1,d, i, a);
	        hanoi(n-1,i, d, i);
	}
}

int main()
{
    deplacement(3, 1, 2, 3);
    printf("--------------------\n");
	hanoi(3, 'D', 'I', 'A');
	return 0;
}
*/
//--------------------------------------------------
//Tableaux et Matrices
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void permuter(int t[], int i, int j)
{
int tmp;
   tmp=t[i]; t[i]=t[j]; t[j]=tmp;
}

int partitionner(int t[], int gauche,int droite)
{
int cle, i, j;
   cle=t[gauche];
   i=gauche+1;
   j=droite;
   while(i<=j){
      while(t[i]<=cle)  i++;
      while(t[j]>cle)   j--;
      if(i<j)
         permuter(t,i++,j--);
   }
   if(t[j]<t[gauche])
      permuter(t,gauche,j);
   return j;
}

void trier(int t[], int gauche, int droite)
{
int pivot;
   if (gauche<droite){
      pivot=partitionner(t,gauche,droite);
      trier(t,gauche,pivot-1);
      trier(t,pivot+1,droite);
   }
}

void init(int t[],int nb)
{
int i;
    for (i=0; i<nb; i++)
        t[i]=rand()%100;
}

void affiche(int t[], int nb)
{
int i;
    for (i=0; i<nb; i++)
        printf("%d\n",t[i]);
}

int main()
{
int tab[10];

    srand(time(NULL));
    init(tab,10);
    affiche(tab,10);
    trier(tab,0,9);
    printf("appres tri :\n");
    affiche(tab,10);
    return 0;
}
*/
