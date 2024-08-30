/****************************************************
*                                                   *
*       Chapitre 6 :    Les tableaux                *
*                                                   *
*****************************************************/

/**************************************
*                                     *
* 1 Tableaux statiques                *
*                                     *
***************************************/
//Parcourir un tableau avec une boucle for
/*
#include <stdlib.h>
#include <stdio.h>

#define NBMAX		5000

int main()
{
int tab[NBMAX];
int i;
	for (i=0; i<NBMAX; i++){
	    tab[i]=rand()%256;
	    printf("tab[%4d]=%4d\n",i,tab[i]);
	}
	return 0;
}
*/

// Trier un tableau
/*
#include <stdlib.h>
#include <stdio.h>

#define N		10

int main()
{
	int tab[N];
	int i,j,tmp;

	// initialisation
	for (i = 0; i<N; i++)
		tab[i] = rand() % 256;
	
	// tri ordre croissant
	for (i = 0; i<N; i++) // pour chaque i
		for (j = i + 1; j<N; j++) // regarder à partir de i+1
		if (tab[j]<tab[i]){ // si élément plus petit
			tmp = tab[i]; // et si oui permuter
			tab[i] = tab[j];
			tab[j] = tmp;
	}

	// affichage résultat
	for (i = 0; i<N; i++)
		printf("%d ",tab[i]);
	putchar('\n');

	return 0;
}
*/
//-----------------------------------
// Précisions sur les #define/*
/*
#include <stdio.h>
#include <stdlib.h>

#define frand(n) (((float)rand()/RAND_MAX)*(n))
#define MIN( a, b) (a) < (b) ? (a) : (b)
#define PAIR(n){\
	printf("%d ",(n));\
	if ((n) % 2)\
		printf("est impair\n"); \
	else\
		printf("est pair\n"); \
}

int main()
{
	float v1, v2;
	v1 = frand(10);
	v2 = frand(10);
	printf("%.2f, %.2f : min = %.2f\n", v1, v2, MIN(v1, v2));

	PAIR((int)v1) // ici le point virugule n'est pas utile
	PAIR((int)v2) // 
   
	return 0;
}
*/
//-----------------------------------
// utiliser un enum
/*
#include <stdio.h>
#include <stdlib.h>
enum test { start, run, accelerer, slow = 5, inverse, stop };
int main()
{
	enum test t1;
	int i;
	for (i = 0; i <= stop; i++){
		t1 = rand() % (stop);
		switch (t1){
			case start:		printf("start\n");			break;
			case run:		printf("run\n");			break;
			case accelerer: printf("accelerer\n");		break;
			case slow:		printf("slow\n");			break;
			case inverse:	printf("inverse\n");		break;
			case stop:		printf("stop\n");			break;
			default:		printf("autre valeurs\n");	break;
		}
	}
	return 0;
}
*/
// création de type enum
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{ NORD, EST, SUD, OUEST} direction;

int main()
{
	direction d;
	srand(time(NULL));
	d = rand() % (OUEST + 1);
	printf("%d\n", d);

	return 0;
}
*/
/**************************************
*                                     *
* Expérimentation tableaux statiques  *
*                                     *
***************************************/
/*
Qu'est ce qu'un tableau ?
- Un tableau est un ensemble d'objets de même type :
  un tableau de int, de float, de double etc.

Qu'est qu'un tableau statique ?
- le fait qu'il soit static signifie qu'il n'est pas dynamique
c'est à dire que sa taille est fixe et que son espace mémoire
est alloué par la machine à la déclaration.

Comment avoir un tableau statique dans un programme ?
Pour définir et déclarer un tableau il faut donner :
- le type des éléments
- un nom pour le tableau
- le nombre des éléments avec l'opérateur crochet (entre crochets)
  soit le formalisme : <type> <nom> < [ constante entière ] >

le nombre des éléments doit toujours être une valeur entière
constante (pas une variable)

La déclaration est la définition close par un point virgule
Par exemple :
int tab[50];   // déclaration d'un tableau de 50 int
float f[90];   // déclaration d'un tableau de 90 float

Comment accéder à chaque élément du tableau ?

Tous les éléments d'un tableau sont numérotés du premier 0 au
dernier taille tableau-1.  Ce numéro est l'indice de l'élément.
Il indique la place de l'élément dans le tableau (Attention le
premier élément du tableau est à l'indice 0).

Ensuite pour accéder à un élément du tableau il faut utiliser
l'opérateur crochet [ ], par exemple :
int toto[5]; // les indices sont 0, 1, 2, 3, 4. (la taille 5 n'est
             // pas un indice du tableau)

    toto[2] = 123;   // mise à 123 du 3eme int du tableau
    toto[0] = 10;    // mise à 10 du premier int du tableau
    toto[4] = 678;   // mise à 678 du cinquième int du tableau

****************************************************/
/*
#include <stdio.h>

int main()
{

int toto[5];
   toto[2] = 123;
   toto[0] = 10;
   toto[4] = 678;

   printf("toto[%d]=%d\n",2, toto[2]);
   printf("toto[%d]=%d\n",0, toto[0]);
   printf("toto[%d]=%d\n",4, toto[4]);
   
   return 0;
}
*/
//--------------------------------------------------
/*
#include <stdio.h>

int main()
{
   // possibilité d'initialiser un tableau à la déclaration.
   // Ce qui n'est pas spécifié vers la fin est mis à 0
int toto[10]={1,2,3};
   printf("toto[%d]=%d\n",0, toto[0]);
   printf("toto[%d]=%d\n",1, toto[1]);
   printf("toto[%d]=%d\n",2, toto[2]);
   printf("toto[%d]=%d\n",3, toto[3]);
   printf("toto[%d]=%d\n",4, toto[5]);

   return 0;
}
*/
//--------------------------------------------------
/*
#include <stdio.h>
#include <stdlib.h>
int main()
{
   // Comment initialiser un tableau de plusieurs millers
   // d'éléments ?

int tab[5000];

   // la boucle for permet facilement de faire défiler tous les
   // indices d'un tableau et ainsi d'accéder à chaque élément
   // quleque soit le nombre :
int i;
   for (i=0; i<5000; i++){
      tab[i]=rand()%256;
      printf("tab[%4d]=%4d\n",i,tab[i]);
   }

   return 0;
}
*/
//--------------------------------------------------
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NBMAX   50
int main()
{

   // Utiliser une macro constante pour la taille.
   // Pour la taille du tableau il est préférable d'utiliser une
   // macro constante globale de la forme :
   // #define NBMAX  50
	// au dessus du main() ou dans une librairie personnelle

int tab[NBMAX];
int i;

   // initialisation générateur aléatoire
   srand(time(NULL));

   for (i=0; i<NBMAX; i++){
      tab[i]=rand()%256;
      printf("tab[%4d]=%4d\n",i,tab[i]);
   }

   // Trier un tableau. Il existe de nombreux algorithmes qui
   // permettent de trier un tableau, par exemple pour ranger ses
   // valeurs en ordre croissant :
int j,tmp;
   for(i=0; i<NBMAX; i++)
      for (j=i+1; j<NBMAX; j++)
         if (tab[j]<tab[i]){
            tmp=tab[i];
            tab[i]=tab[j];
            tab[j]=tmp;
         }
   for(i=0; i<NBMAX;i++)
      printf("%4d\n",tab[i]);

   return 0;
}
*/
//--------------------------------------------------
/*
#include <stdio.h>

int main()
{

   // Tableaux à plusieurs dimensions.
   // il est posible d'avoir un tableau à plusieurs dimension il
   // suffit de spécifier pour chaque dimmension sa taille, par
   // exemple :

float f[3][4];  // tableau de float à 2 dimensions (une matrice)
                 // revient à avoir 3 tableaux de 4 float.

   // l'accès aux éléments se fait toujours avec l'opérateur
   // crochet [ ], un crochet par dimension :
   f[0][0]=0;
   f[0][1]=1;
   f[0][2]=2;
   f[0][3]=3;
   f[1][0]=4;
   //(...)
   f[2][3]=11;

   // l'utilisation de boucles requiert une variable et une boucle
   // par dimension :
int y, x,cmpt;

   // initialisation
   for (cmpt=0,y=0; y<3; y++)
      for (x=0; x<4; x++,cmpt++)
         f[y][x]=cmpt;

   // affichage
   for (cmpt=0,y=0; y<3; y++)
      for (x=0; x<4; x++,cmpt++)
         printf("f[%d][%d]=%0.1f\n",y,x,f[y][x]);

   return 0;
}
*/
//--------------------------------------------------
/*
#include <stdio.h>

int main()
{

   // possibilité également d'initialiser un tableau à plusieurs
   // dimensions à la déclaration, deux solutions :
int tab1[4][2]={ 1,2,3,4,5,6,7,8};
int i,j;
   printf("tab1 :\n");
   for (i=0; i<4; i++){
      for (j=0; j<2; j++)
         printf("%2d",tab1[i][j]);
      putchar('\n');
   }

int tab2[4][2]={ {1,2},
                 {3,4},
                 {5,6},
                 {7,8} };
   printf("tab2 :\n");
   for (i=0; i<4; i++){
      for (j=0; j<2; j++)
         printf("%2d",tab2[i][j]);
      putchar('\n');
   }
   //Remarque : tester en passant la taille dim 2 à 3
   //(ne pas oublier de modifier le test de la boucle 2)
   //et voir résultat

   return 0;
}
*/
/****************************************************
*                                                   *
*       2.   Exemples d'utilisations de tableaux    *
*                                                   *
*****************************************************/
// Chaines de caractères
// scanf, scanf_s
/*
#include <stdio.h>

int main()
{
	char nom[80];
	printf("Comment vous appelez-vous ? ");
	scanf_s("%s", nom, 80);
	printf("Bonjour %s\n", nom);
	return 0;
}

*/
//------------------------------------------------
// Chaines de caractères
// fgets
/*
#include <stdio.h>

int main()
{
	char nom[80];
	printf("Comment vous appelez-vous ? ");
	fgets(nom, 80, stdin);
	printf("Bonjour %s\n", nom);
	return 0;
}


*/
//------------------------------------------------
// Chaines de caractères
// strcpy
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main()
{
	char recup[100], copie[100];

	printf("entrer une phrase :\n");
	fgets(recup, 100, stdin);
	strcpy(copie, recup);
	printf("copie : %s\n", copie);
	return 0;
}
*/
//------------------------------------------------
// Chaines de caractères
// strcpy_s
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char recup[100], copie[100];

	printf("entrer une phrase :\n");
	fgets(recup, 100, stdin);
	strcpy_s(copie, 100, recup);
	printf("copie : %s\n", copie);
	return 0;
}


*/
//------------------------------------------------
/*

/************************************************************
*															*
* Expérimentation : utilisation de chaines de caractères    *
*															*
*************************************************************/
/*Qu'est ce qu'une chaine de caractères ?
une suite de caractères stockée dans un tableau de char et terminée
par le caractère '\0'
Le '\0' marque la fin de la chaine et est indispensable.Toutes les
fonctions de traitement des chaines de caractères s'appuient sur
cette marque de fin pour leurs traitements. S'il est ommis il risque
d'y avoir débordement de tableau et le programme va planter ou avoir
un comportement incertain. Sans le '\0' final, il ne s'agit pas d'une
chaine mais uniquement d'un tableau de caractères.

****************************************************/
/* 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int main()
{
/*
char s[100]="bonjour\n"; // 9 caractères dans la chaine : '\0' implicite
                         // le reste du tableau n'est pas utilisé
   printf(s);
   s[3]='s';
   s[5]='i';
   printf(s);
*/
//--------------------------------------------------
/*
   // si pas de \0 résultat incertain, plantage ou aléatoire
char s1[]={'a','b','c','d'};
   printf("test sans \\0 : %s\n",s1);
*/
//--------------------------------------------------
/*
   // la taille de la chaine définie par l'initalisation à la
    // déclaration
char s2[]="tata fait du velo"; // 17 caractères + \0

   // la fonction strlen renvoie le nombre de caractère d'une
   // chaine sans compter le \0 final :
   printf("s2 a %d caracteres\n",strlen(s2));
*/
//--------------------------------------------------
/*
   // pour entrer une chaine de caractères :
   // fonction fgets(le tab pour recup, la taille max, le fichier
	// source)
char recup[100];
   printf("entrer une phrase :\n");
   fgets(recup,100,stdin);
   printf("phrase entree : %s\n",recup);

//--------------------------------------------------

   // pour copier une chaine de caractères :
   // fonction strcpy(tab pour copie, chaine à copier)
char copie[100];
   strcpy_s(copie, 100, recup);
   printf("voici la copie : %s\n",copie);
*/

/*
   return 0;
}
*/

/****************************************************
*                                                   *
*       3.   Tableaux et structures                 *
*                                                   *
*****************************************************/
//Tableau comme champ dans une structure
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nom[80];
	float calc;
	int stock[10];
}test;

int main()
{
test t1;
int i;

	strcpy_s(t1.nom, 80, "Michael");
	printf("Nom : %s\n",t1.nom);
	t1.calc=(float)rand() / RAND_MAX;
	printf("Calcul : %f\n",t1.calc);

 	for (i=0; i<10; i++){
       t1.stock[i]=rand()%256;
	    printf("Valeurs %d stockees : %d\n", i, t1.stock[i]);
	}

	return 0;
}
*/
//--------------------------------------------------
// Tableau de structures 1
/*
#include <stdio.h>
#include <stdlib.h>
struct pix{
	int x, y, color;
};

int main()
{
struct pix  p, tab[3];
int i;
	// initialisation structure seule
	p.x=0;
	p.y=50;
	p.color=255;
	// affichage structure seule
	printf("x=%d,y=%d,color=%d\n",p.x,p.y,p.color);

	//initialisation du tableau de structures
	for (i=0; i<3; i++){
	    tab[i].x=0;
	    tab[i].y=50;
	    tab[i].color=255;
	    //affichage de chaque structure
	    printf("tab[%d].x=%d,y=%d,color=%d\n",
		     i,tab[i].x,tab[i].y,tab[i].color);

	}
	return 0;
}
*/
//--------------------------------------------------
// Tableau de structures 2
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NB_ENNEMI     100

typedef struct{
	char nom[80];     // nom et type de l'ennemi
	float nuisance;   // potentielle de nuisance
	float x,y,px,py;  // position et déplacement
	int force[10];    // 10 possibilités de force pour les combats
}t_ennemi;

t_ennemi init_ennemi(void)
{
char* lesNoms[4]={"Bretelgunch","Athanase","Belzebon",
                  "Trolympique"};
t_ennemi e;
int i;
	// un nom au hasard parmi les quatre
	strcpy(e.nom, lesNoms[rand()%4]);
	e.nuisance= rand()/(float)RAND_MAX;
	e.x = (rand()/(float)RAND_MAX) * 1024;    // x de 0 à 1024
	e.y = (rand()/(float)RAND_MAX) * 768;     // y de 0 à 768
	e.px = ((rand()/(float)RAND_MAX) * 10)-5; // de -5 à +5
	e.py = ((rand()/(float)RAND_MAX) * 10)-5; // de -5 à +5
	for (i=0; i<10; i++)
	    //les 10 indicateurs de force entre 0 et 100
	    e.force[i]=rand()%100;
	return e;
}

void affiche_ennemi (t_ennemi e, int number)
{
int i;
	printf("Ennemi %d :\n", number);
	printf("\t- nom                     : %s \n", e.nom);
	printf("\t- nuisance                : %.2f \n", e.nuisance);
	printf("\t- pos horizontale         : %.2f \n", e.x);
	printf("\t- pos verticale           : %.2f \n", e.y);
	printf("\t- deplacement horizontale : %.2f \n", e.px);
	printf("\t- deplacement verticale   : %.2f \n", e.py);
	for(i=0; i<10; i++)
       printf("\t- force[%d]=%d\n",i,e.force[i]);
}

int main()
{
t_ennemi E[NB_ENNEMI];
int i;
   srand(time(NULL));
	for (i=0; i<NB_ENNEMI; i++){
	    E[i]=init_ennemi();
	    affiche_ennemi(E[i],i);
   }
   return 0;
}
*/
/****************************************************
*                                                   *
* Expérimentations : voiture 3						*
*                                                   *
*****************************************************/
// Voiture 3 : une structure trait et un tableau de traits
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
// taille de la zone de jeu
#define TX 80
#define TY 24
#define MAXTRAIT 6 // nombre max de traits d'un circuit
// Les quatre directions
enum{ NORD, EST, SUD, OUEST };
/* Pour un circuit :
- 6 traits max
- un trait = une direction et un nombre de pas
- un nombre de traits
- un nombre de tours
*
// pour avoir un circuit :
typedef struct{
	int dir, pas;
}t_trait;
typedef struct{
	t_trait t[MAXTRAIT]; // 6 traits
	int nbtrait; // nombre de traits dans le circuit
	int nbtour; // nombre de tours à faire pour une course
}t_circuit;
/*Pour une voiture :
- une position x,y
- direction et pas : un trait
- un identificateur du trait courant
- un compteur de tours
- une vitesse
- le temps de départ (associé à vitesse)
En option, pour différencier toutes les voitures
avec couleur et apparence :
- une lettre pour l'apparence
- une couleur d'effacement
- une couleur d'affichage
*
typedef struct{
	int x, y, idtrait, tour, vit, tmps;
	t_trait t; // direction et pas
	int lettre; // lettre correspondante
	int color1, color2; // deux couleurs
}t_voiture;
// les déclarations des fonctions
t_trait		init_trait			(int dir, int pas);
t_circuit	create_circuit1		(void);
t_voiture	create_voiture		(int startx, int starty,int c1, int c2, int l);
t_voiture	bouge				(t_voiture v, t_circuit c);
int			run					(t_voiture v1, t_voiture v2,t_voiture v3, t_voiture v4,t_circuit c);
t_voiture	select_trait		(t_voiture v, t_circuit c);
t_voiture	avancer				(t_voiture v);
void		afficher			(t_voiture v, int color);
int			top					(t_voiture v);
void		gotoxy				(int x, int y);
void		textcolor			(int color);
void        pause				(int x, int y);
/********************************************************
ACTION
********************************************************
int main()
{
	t_circuit c;
	t_voiture v1, v2, v3, v4;
	srand(time(NULL));
	c = create_circuit1();
	v1 = create_voiture(2, 2, 0, 10, '1');
	v2 = create_voiture(3, 3, 1, 11, '2');
	v3 = create_voiture(4, 4, 2, 12, '3');
	v4 = create_voiture(5, 5, 3, 13, '4');
	while (run(v1, v2, v3, v4, c)){
		v1 = bouge(v1, c);
		v2 = bouge(v2, c);
		v3 = bouge(v3, c);
		v4 = bouge(v4, c);
	}
	pause(0, TY);
	return 0;
}
/********************************************************
CREATION, CIRCUIT, VOITURES
********************************************************
t_trait init_trait(int dir, int pas)
{
	t_trait t;
	t.dir = dir;
	t.pas = pas;
	return t;
}
t_circuit create_circuit1()
{
	t_circuit c;
	int i;
	// définition du circuit
	/*
	c.t[0]=init_trait(EST,10);
	c.t[1]=init_trait(SUD,10);
	c.t[2]=init_trait(OUEST,10);
	c.t[3]=init_trait(NORD,10);
	*
	// peut être remplacé par une boucle
	for (i = 0; i<4; i++)
		c.t[i] = init_trait((i + 1) % 4, 10);
	c.nbtrait = 4;
	c.nbtour = 2;
	return c;
}
/********************************************************
CREATION VOITURE
********************************************************
t_voiture create_voiture(int startx, int starty, int c1, int c2, int l)
{
	t_voiture v;
	v.x = startx;
	v.y = starty;
	v.t = init_trait(0, 0);
	v.idtrait = 0;
	v.tour = 0;
	v.tmps = 0;
	v.vit = 0;
	v.color1 = c1;
	v.color2 = c2;
	v.lettre = l;
	return v;
}
/********************************************************
BOUGER
********************************************************/
/*
contrôle de la fin de la course. La course continue tant
qu'aucune voiture n'a fini et s'arrête dés qu'une voiture
a fini
*
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
*
t_voiture bouge(t_voiture v, t_circuit c)
{
	if (top(v)){
		v.tmps = clock();
		if (v.t.pas == 0)
			v = select_trait(v, c);
		v = avancer(v);
	}
	return v;
}
/*
sélectionner un trait à parcourir
*
t_voiture select_trait(t_voiture v, t_circuit c)
{
	// contrôler si un tour a été effectué
	if (v.idtrait == c.nbtrait){
		v.tour++;
		v.idtrait = 0;
	}
	// changer la vitesse pour chaque trait
	v.vit = 150 + rand() % 150;
	// sélection du trait donné par le champ idtrait pris
	// comme indice dans le tableau des traits du circuit
	v.t = c.t[v.idtrait];
	// préparer pour le tour suivant
	v.idtrait++;
	return v;
}
/*
parcourir le trait courant
*
t_voiture avancer(t_voiture v)
{
	if (v.t.pas>0){
		v.t.pas--; // un pas de moins
		// effacer
		afficher(v, v.color1);
		// avancer selon direction
		switch (v.t.dir){
		case NORD: v.y--; break;
		case EST: v.x++; break;
		case SUD: v.y++; break;
		case OUEST: v.x--; break;
		}
		// réafficher
		afficher(v, v.color2);
	}
	return v;
}
/*
afficher une voiture de la couleur color
*
void afficher(t_voiture v, int color)
{
	gotoxy(v.x, v.y);
	textcolor(color);
	putchar(v.lettre);
}
/********************************************************
OUTILS
********************************************************
// déplacement curseur
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// gestion couleur
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/****************************************************
*                                                   *
* Expérimentations : voiture 4						*
*                                                   *
*****************************************************

//VOITURE 4 : TABLEAU DE STRUCTURES VOITURE

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

// Les quatre directions
enum{ NORD, EST, SUD, OUEST };

/* Pour un circuit :
- 6 traits max
- un trait = une direction et un nombre de pas
- un nombre de traits
- un nombre de tours
*
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
*
typedef struct{
	int x, y, idtrait, tour, vit, tmps;
	t_trait t;          // direction et pas
	int lettre;         // lettre correspondante
	int color1, color2;  // deux couleurs
}t_voiture;

// les déclarations des fonctions
t_trait        init_trait		(int dir, int pas);
t_circuit      create_circuit1	(void);
t_voiture      create_voiture	(int startx, int starty,
								int c1, int c2, int l);
t_voiture      bouge			(t_voiture v, t_circuit c);
int            run				(t_voiture v, t_circuit c);
t_voiture      select_trait		(t_voiture v, t_circuit c);
t_voiture      avancer			(t_voiture v);
void           afficher			(t_voiture v, int color);
int            top				(t_voiture v);
void           gotoxy			(int x, int y);
void           textcolor		(int color);
void		   pause			(int x, int y);
/********************************************************
ACTION
********************************************************
int main()
{
	t_circuit c;
	t_voiture v[MAXVOITURE];
	int i, fin = 0;

	srand(time(NULL));
	c = create_circuit1();

	// initialisation des voitures à partir de la valeur
	// croissante de i
	for (i = 0; i<MAXVOITURE; i++)
		v[i] = create_voiture(i + 2, i + 2, i, i + 10, i + '1');


	while (!fin){

		for (i = 0; i<MAXVOITURE; i++)
			v[i] = bouge(v[i], c);

		// contrôle fin boucle
		for (i = 0; i<MAXVOITURE; i++)
		if (!run(v[i], c))
			fin = 1;

	}

	pause(0, TY);
	return 0;
}
/********************************************************
CREATION, CIRCUIT, VOITURES
********************************************************
t_trait init_trait(int dir, int pas)
{
	t_trait t;
	t.dir = dir;
	t.pas = pas;
	return t;
}

t_circuit create_circuit1()
{
	t_circuit c;
	int i;
	// définition du circuit
	for (i = 0; i<4; i++)
		c.t[i] = init_trait((i + 1) % 4, 10);

	c.nbtrait = 4;
	c.nbtour = 2;

	return c;
}
/********************************************************
CREATION VOITURE
********************************************************
t_voiture create_voiture(int startx, int starty, int c1,
	int c2, int l)
{
	t_voiture v;

	v.x = startx;
	v.y = starty;
	v.t = init_trait(0, 0);
	v.idtrait = 0;
	v.tour = 0;
	v.tmps = 0;
	v.vit = 0;
	v.color1 = c1;
	v.color2 = c2;
	v.lettre = l;
	return v;
}
/********************************************************
BOUGER
********************************************************/
/*
la voiture a-t-elle terminé ?
*
int run(t_voiture v, t_circuit c)
{
	return v.tour<c.nbtour;
}
// topage voitures
int top(t_voiture v)
{
	return (clock() > v.tmps + v.vit);
}
/*

*
t_voiture bouge(t_voiture v, t_circuit c)
{
	if (top(v)){
		v.tmps = clock();
		if (v.t.pas == 0)
			v = select_trait(v, c);
		v = avancer(v);
	}
	return v;
}
/*
sélectionner un trait à parcourir
*
t_voiture select_trait(t_voiture v, t_circuit c)
{
	// contrôler si un tour a été effectué
	if (v.idtrait == c.nbtrait){
		v.tour++;
		v.idtrait = 0;
	}

	// changer la vitesse pour chaque trait
	v.vit = 150 + rand() % 150;

	// sélection du trait donné par le champ idtrait pris
	// comme indice dans le tableau des traits du circuit
	v.t = c.t[v.idtrait];

	// préparer pour le tour suivant
	v.idtrait++;

	return v;
}
/*
parcourir le trait courant
*
t_voiture avancer(t_voiture v)
{
	if (v.t.pas>0){
		v.t.pas--; // un pas de moins

		// effacer
		afficher(v, v.color1);

		// avancer selon direction
		switch (v.t.dir){
		case NORD:     v.y--;  break;
		case EST:      v.x++;  break;
		case SUD:      v.y++;  break;
		case OUEST:    v.x--;  break;
		}

		// ré-afficher
		afficher(v, v.color2);
	}
	return v;
}
/*
afficher une voiture de la couleur color
*
void afficher(t_voiture v, int color)
{
	gotoxy(v.x, v.y);
	textcolor(color);
	putchar(v.lettre);
}
/********************************************************
OUTILS
********************************************************
// déplacement curseur
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// gestion couleur
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/****************************************************
*                                                   *
* Expérimentations : voiture 5						*
*                                                   *
*****************************************************

// VOITURE 5 : CHAQUE VOITURE A SON CIRCUIT

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

enum{ NORD, EST, SUD, OUEST };

typedef struct{
	int dir, pas;
}t_trait;

typedef struct{
	t_trait t[MAXTRAIT];
	int nbtrait;
	int nbtour;
}t_circuit;

typedef struct{
	int x, y, idtrait, tour, vit, tmps;
	t_trait t;          // direction et pas
	int lettre;
	int color1, color2;
	t_circuit c;        // chaque voiture a son circuit
}t_voiture;

// les déclarations des fonctions
t_trait        init_trait(int dir, int pas);
t_circuit      create_circuit1(void);
t_voiture      create_voiture(int startx, int starty,
	int c1, int c2, int l);
t_voiture      bouge(t_voiture v);
int            run(t_voiture v);
t_voiture      select_trait(t_voiture v);
t_voiture      avancer(t_voiture v);
void           afficher(t_voiture v, int color);
int            top(t_voiture v);
void           gotoxy(int x, int y);
void           textcolor(int color);
void		   pause(int x, int y);
/********************************************************
ACTION
********************************************************
int main()
{
	t_voiture v[MAXVOITURE];
	int i, fin = 0;

	srand(time(NULL));

	// initialisation des voitures (circuit compris)
	for (i = 0; i<MAXVOITURE; i++)
		v[i] = create_voiture(i + 2, i + 2, i, i + 10, i + '1');


	while (!fin){

		for (i = 0; i<MAXVOITURE; i++)
			v[i] = bouge(v[i]);

		// contrôle fin boucle
		for (i = 0; i<MAXVOITURE; i++)
		if (!run(v[i]))
			fin = 1;

	}

	pause(0, TY);
	return 0;
}
/********************************************************
CREATION, CIRCUIT, VOITURES
********************************************************
t_trait init_trait(int dir, int pas)
{
	t_trait t;
	t.dir = dir;
	t.pas = pas;
	return t;
}

t_circuit create_circuit1()
{
	t_circuit c;
	int i;
	// définition du circuit
	for (i = 0; i<4; i++)
		c.t[i] = init_trait((i + 1) % 4, 10);

	c.nbtrait = 4;
	c.nbtour = 2;

	return c;
}
/********************************************************
CREATION VOITURE
********************************************************
t_voiture create_voiture(int startx, int starty, int c1,
	int c2, int l)
{
	t_voiture v;

	v.x = startx;
	v.y = starty;
	v.t = init_trait(0, 0);
	v.idtrait = 0;
	v.tour = 0;
	v.tmps = 0;
	v.vit = 0;
	v.color1 = c1;
	v.color2 = c2;
	v.lettre = l;

	// le circuit de la voiture, toutes auront le même
	v.c = create_circuit1();
	return v;
}
/********************************************************
BOUGER
********************************************************/
/*
la voiture a-t-elle terminé ?
*
int run(t_voiture v)
{
	return v.tour<v.c.nbtour;
}
// topage voitures
int top(t_voiture v)
{
	return (clock() > v.tmps + v.vit);
}
/*

*
t_voiture bouge(t_voiture v)
{
	if (top(v)){
		v.tmps = clock();
		if (v.t.pas == 0)
			v = select_trait(v);
		v = avancer(v);
	}
	return v;
}
/*
sélectionner un trait à parcourir
*
t_voiture select_trait(t_voiture v)
{
	// contrôler si un tour a été effectué
	if (v.idtrait == v.c.nbtrait){
		v.tour++;
		v.idtrait = 0;
	}

	// changer la vitesse pour chaque trait
	v.vit = 150 + rand() % 150;

	// sélection du trait donné par le champ idtrait pris
	// comme indice dans le tableau des traits du circuit
	v.t = v.c.t[v.idtrait];

	// préparer pour le tour suivant
	v.idtrait++;

	return v;
}
/*
parcourir le trait courant
*
t_voiture avancer(t_voiture v)
{
	if (v.t.pas>0){
		v.t.pas--; // un pas de moins

		// effacer
		afficher(v, v.color1);

		// avancer selon direction
		switch (v.t.dir){
		case NORD:     v.y--;  break;
		case EST:      v.x++;  break;
		case SUD:      v.y++;  break;
		case OUEST:    v.x--;  break;
		}

		// ré-afficher
		afficher(v, v.color2);
	}
	return v;
}
/*
afficher une voiture de la couleur color
*
void afficher(t_voiture v, int color)
{
	gotoxy(v.x, v.y);
	textcolor(color);
	putchar(v.lettre);
}
/********************************************************
OUTILS
********************************************************
// déplacement curseur
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// gestion couleur
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// arrêter la console
void pause(int x, int y)
{
	gotoxy(x, y);
	printf("Appuyez sur Enter pour continuer...");
	rewind(stdin);
	char c = getchar();
}
/****************************************************
*                                                   *
* Expérimentations : voiture 5b						*
*                                                   *
*****************************************************

// VOITURE 5B : CHAQUE VOITURE A SON CIRCUIT
// - création de circuits aléatoires

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

enum{ NORD, EST, SUD, OUEST };

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
	int x, y, idtrait, tour, vit, tmps;
	t_trait t;          // direction et pas
	int lettre;
	int color1, color2;
	t_circuit c;        // chaque voiture a son circuit
}t_voiture;

// les déclarations des fonctions
t_trait        init_trait(int dir, int pas);
t_circuit      create_circuit_alea(int startx, int starty);
t_voiture      create_voiture(int startx, int starty,
	int c1, int c2, int l);
t_voiture      bouge(t_voiture v);
int            run(t_voiture v);
t_voiture      select_trait(t_voiture v);
t_voiture      avancer(t_voiture v);
void           afficher(t_voiture v, int color);
int            top(t_voiture v);
void           gotoxy(int x, int y);
void           textcolor(int color);
void		   pause(int x, int y);
/********************************************************
ACTION
********************************************************
int main()
{
	t_voiture v[MAXVOITURE];
	int i, fin = 0;
	int cmpt;   // compter les voitures qui ont fini

	srand(time(NULL));

	// initialisation des voitures (circuit compris)
	for (i = 0; i<MAXVOITURE; i++)
		v[i] = create_voiture(rand() % TX, rand() % TY, i, i + 10, i + '1');


	while (!fin){

		for (i = 0; i<MAXVOITURE; i++)
			v[i] = bouge(v[i]);

		// fin de la boucle si toutes les voitures
		// ont terminé
		for (i = 0, cmpt = 0; i<MAXVOITURE; i++)
			cmpt += run(v[i]); // run retourne 0 si arrêtée

		if (cmpt == 0)
			fin = 1;

	}

	pause(0, TY);
	return 0;
}
/********************************************************
CREATION, CIRCUIT, VOITURES
********************************************************
t_trait init_trait(int dir, int pas)
{
	t_trait t;
	t.dir = dir;
	t.pas = pas;
	return t;
}

t_circuit create_circuit_alea(int startx, int starty)
{
	t_circuit c;
	int i, dir, pas, interdit;

	// point de départ du circuit passé en paramètre
	c.startx = startx;
	c.starty = starty;

	// un nombre aléatoire de traits
	c.nbtrait = 1 + rand() % MAXTRAIT;

	// nombre aléatoire de tour
	c.nbtour = 1 + rand() % 4;

	// création de traits aléatoires avec
	// - retour en arrière sur même trait interdit
	// - sortie fenêtre évitée

	interdit = -1;
	// pour chaque trait initialiser dir et pas
	for (i = 0; i<c.nbtrait; i++){

		// direction
		dir = rand() % 4;
		// contrôler retour en arrière
		if (dir == interdit){
			if (rand() % 2)
				dir = (dir + 1) % 4;
			else
				dir = (dir - 1 + 4) % 4;
		}
		// interdit = inverse (retour arrière) pour
		// le trait suivant
		interdit = (dir + 2) % 4;

		// un nombre de pas
		pas = 1 + rand() % MAXPAS;
		// contrôler si la voiture reste dans la
		// fenêtre console.
		switch (dir){
		case NORD:
			// si sortie le nombre de pas du trait est 0
			pas = (starty - pas >= 0) ? pas : 0;
			starty -= pas;
			break;

		case EST:
			pas = (startx + pas < TX) ? pas : 0;
			startx += pas;
			break;

		case SUD:
			pas = (starty + pas < TY) ? pas : 0;
			starty += pas;
			break;

		case OUEST:
			pas = (startx - pas >= 0) ? pas : 0;
			startx -= pas;
			break;
		}
		c.t[i] = init_trait(dir, pas);
	}
	return c;
}
/********************************************************
CREATION VOITURE
********************************************************
t_voiture create_voiture(int startx, int starty, int c1,
	int c2, int l)
{
	t_voiture v;

	v.x = startx;
	v.y = starty;
	v.t = init_trait(0, 0);
	v.idtrait = 0;
	v.tour = 0;
	v.tmps = 0;
	v.vit = 0;
	v.color1 = c1;
	v.color2 = c2;
	v.lettre = l;

	// le circuit de la voiture, toutes auront le même
	v.c = create_circuit_alea(startx, starty);
	return v;
}
/********************************************************
BOUGER
********************************************************/
/*
la voiture a-t-elle terminé ?
*
int run(t_voiture v)
{
	return v.tour<v.c.nbtour;
}
// topage voitures
int top(t_voiture v)
{
	return (clock() > v.tmps + v.vit);
}
/*

*
t_voiture bouge(t_voiture v)
{
	if (top(v)){
		v.tmps = clock();
		if (v.t.pas == 0)
			v = select_trait(v);
		v = avancer(v);
	}
	return v;
}
/*
sélectionner un trait à parcourir
*
t_voiture select_trait(t_voiture v)
{
	// contrôler si un tour a été effectué
	if (v.idtrait == v.c.nbtrait){
		v.tour++;
		v.idtrait = 0;
		v.x = v.c.startx;
		v.y = v.c.starty;
	}

	// changer la vitesse pour chaque trait
	v.vit = 150 + rand() % 150;

	// sélection du trait donné par le champ idtrait pris
	// comme indice dans le tableau des traits du circuit
	v.t = v.c.t[v.idtrait];

	// préparer pour le tour suivant
	v.idtrait++;

	return v;
}
/*
parcourir le trait courant
*
t_voiture avancer(t_voiture v)
{
	if (v.t.pas>0){
		v.t.pas--; // un pas de moins

		// effacer
		afficher(v, v.color1);

		// avancer selon direction
		switch (v.t.dir){
		case NORD:     v.y--;  break;
		case EST:      v.x++;  break;
		case SUD:      v.y++;  break;
		case OUEST:    v.x--;  break;
		}

		// ré-afficher
		afficher(v, v.color2);
	}
	return v;
}
/*
afficher une voiture de la couleur color
*
void afficher(t_voiture v, int color)
{
	gotoxy(v.x, v.y);
	textcolor(color);
	putchar(v.lettre);
}
/********************************************************
OUTILS
********************************************************
// déplacement curseur
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
// gestion couleur
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
// arrêter la console
void pause(int x, int y)
{
	gotoxy(x, y);
	printf("Appuyez sur Enter pour continuer...");
	rewind(stdin);
	char c = getchar();
}

/****************************************************
*                                                   *
*       4.   Tableaux et fonctions                  *
*                                                   *
*****************************************************/
/*
//Utiliser un tableau déclaré en global
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// valeur constante définie en globale
#define NBMAX  50

// tableau déclaré en global, accessible de partout dans le programme
int tabGlo[NBMAX];

// déclaration des fonctions définies en dessous du main()
void  init_tabGlobal    (void);
void  affich_tabGlobal  (void);


int main()
{
   init_tabGlobal();	// appel fonction d'initialisation sans paramètre
   affich_tabGlobal();// appel fonction d'affichage sans paramètre
   return 0;
}

//Les deux fonctions peuvent agir sur le tableau tabGlo sans
//le passer en paramètre parce qu'il est déclaré en  global.
//En revanche elles ne peuvent travailler que sur ce tableau.

void init_tabGlobal()
{
int i;
   for (i=0; i<NBMAX; i++)
      tabGlo[i]=rand()%256; // initialisation du tableau avec des

      // valeurs aléatoires comprises entre
      // 0 et 255
}

//
//
void affich_tabGlobal()
{
int i;
   for (i=0; i<NBMAX; i++){ 	// affichage du tableau
      printf("%4d",tabGlo[i]);
      if (i%10==9)		// par ligne de 10
         putchar('\n');
   }
}
*/
//--------------------------------------------------
//Tableau en paramètre de fonction
//En paramètre de fonction le tableau est converti en pointeur
/*
#include <stdio.h>
#include <stdlib.h>
void init (int*t)
{
int i;
	for (i=0; i<10; i++){
       t[i]=rand()%256;
	    printf("t[%d]=%d\n",i,t[i]);
	}
	putchar('\n');
}

int main()
{
int tab[10];

	init(tab);  // L'affectation implicite est la suivante :
			// init ( t = &tab[0]) ;
			// c'est équivalent à
			// init (t = tab) ;

	return 0;
}
*/
//------------
/*
#include <stdio.h>
#include <stdlib.h>
void init (int t[] )
{
int i;
	for (i=0; i<10; i++){
       t[i]=rand()%256;
	    printf("t[%d]=%d\n",i,t[i]);
	}
	putchar('\n');
}

int main()
{
int tab[10];

	init(tab);  // L'affectation implicite est la suivante :
			// init ( t = &tab[0]) ;
			// c'est équivalent à
			// init (t = tab) ;

	return 0;
}
*/
//--------------
/*
#include <stdio.h>
#include <stdlib.h>

void init (int t[10])
{
int i;
	for (i=0; i<10; i++){
       t[i]=rand()%256;
	    printf("t[%d]=%d\n",i,t[i]);
	}
	putchar('\n');
}

int main()
{
int tab[10];

	init(tab);  // L'affectation implicite est la suivante :
			// init ( t = &tab[0]) ;
			// c'est équivalent à
			// init (t = tab) ;

	return 0;
}
*/
//--------------------------------------------------
// Tableaux à plusieurs dimensions en paramètre
/*
#include <stdlib.h>
#include <stdio.h>
void init_matrice(int m[][10], int ty,int tx)
{
int x,y;
	for(y=0; y<ty; y++){
       for (x=0; x<tx; x++){
	        m[y][x]=rand()%256;
           printf("%4d",m[y][x]);
	    }
	    putchar('\n');
	}
}

int main()
{
int mat[25][10]; // 25 lignes de 10 colonnes chacune
	init_matrice(mat,25,10);

	return 0;
}
*/
// le paramètre peut aussi s'écrire int (*m)[10]
/*
#include <stdlib.h>
#include <stdio.h>
void init_matrice(int (*m)[10], int ty, int tx)
{
	int x, y;
	for (y = 0; y<ty; y++){
		for (x = 0; x<tx; x++){
			m[y][x] = rand() % 256;
			printf("%4d", m[y][x]);
		}
		putchar('\n');
	}
}

int main()
{
	int mat[25][10]; // 25 lignes de 10 colonnes chacune
	init_matrice(mat, 25, 10);

	return 0;
}
*/
//--------------------------------------------------
//Choix pour l'écriture des tableaux en paramètre
/*
#include <stdlib.h>
#include <stdio.h>
void init(int t[], int nb_element)
{
int i;
	for (i=0; i<nb_element; i++){
	    t[i]=rand()%256;
	    printf("t[%d]=%d\n",i,t[i]);
	}
	putchar('\n');
}

int main()
{
int t1[10];
int t2[20];

	init(t1, 10); 		// appel pour initialiser t1
	init(t2, 20);		// appel pour initialiser t2
	return 0;
}
*/
//--------------------------------------------------
//Modification des données via un passage par adresse
/*
#include <stdlib.h>
#include <stdio.h>
void init(int t[], int nb_element)
{
int i;
	for (i=0; i<nb_element; i++)
	    t[i]=1+rand()%9;
}

void affiche(int t[], int nb_element)
{
int i;
	for (i=0; i<nb_element; i++)
	    printf("t[%d]=%d\n",i,t[i]);

	putchar('\n');
}

int main()
{
int tab[4]={0};

	affiche(tab,4);
	init(tab, 4);
	affiche(tab,4);
	return 0;
}
*/
//--------------------------------------------------
/*
#include <stdlib.h>
#include <stdio.h>
void init(int t[], int nb_element)
{
int i;
	for (i=0; i<nb_element; i++)
	    t[i]=1+rand()%9;
}

void affiche(int t[], int nb_element)
{
int i;
	for (i=0; i<nb_element; i++)
	    printf("t[%d]=%d\n",i,t[i]);

	putchar('\n');
}
void test (int t1[], int nb1, int t2[], int nb2)
{
	init(t1,nb1);
	init(t2,nb2);
	affiche(t1,nb1);
	affiche(t2,nb2);
	init(t1,nb1);
	affiche(t2,nb2);
}

int main()
{
int tab[5];
	test(tab, 5, tab, 5);
	return 0;
}
*/
//--------------------------------------------------
// Pas de tableau statique en valeur de retour
/*
#include <stdio.h>
#include <stdlib.h>

#define NB	100
int* ErreurRetour()
{
	int tab[NB] = { 0 };
	//...
	return tab;
}

int main()
{
	int* t = ErreurRetour();
	for (int i = 0; i < NB; i++) {
		t[i] = rand() % 100;
		printf("t[%d]=%d\n", i, t[i]);
	}

	return 0;
}

*/
//----------------------------------------------------------
//Quelques fonctions de traitement de chaines de caractères
//Récupérer une chaine entrée par l'utilisateur
/*
#include <stdio.h> 

#define NB	100

int main()
{
	char buf[NB];
	printf("entrer une chaine :\n");
	fgets(buf, NB, stdin);
	printf("%s", buf);
	return 0;
}
*/
//--------------------------------------------------
//Obtenir la taille d'une chaine
/*
#include <stdio.h>
#include <string.h>

#define NB	100

int main()
{
	char buf[NB];
	int L;
	printf("entrer chaîne : ");
	fgets(buf, NB, stdin);
	L = strlen(buf);
	printf("longueur de la chaine %s : %d\n", buf, L);
	return 0;
}

*/
//--------------------------------------------------
// Copier une chaine
/*
#include <stdio.h>
#include <string.h>

#define NB	100

int main()
{
	char buf[NB] = { 0 };
	char cpi[NB] = { 0 };
	printf("entrer chaîne :\n");
	fgets(buf, NB, stdin);
	strcpy_s(cpi, NB, buf);
	printf("copie : %s", cpi);
	return 0;
}

*/
//--------------------------------------------------
// comparer deux chaines
/*
#include <stdio.h>
#include <string.h>

#define NB	100

int main()
{
	char buf[NB];
	char cpi[NB];
	int res;

	printf("entrer deux chaines :\n");
	fgets(buf, NB, stdin);
	buf[strlen(buf) - 1] = '\0';        // suppression  ’\n’ avant fin

	fgets(cpi, NB, stdin);
	cpi[strlen(cpi) - 1] = '\0';        // suppression  ’\n’ avant fin

	if ((res = strcmp(cpi, buf)) == 0)
		printf("les chaines sont identiques\n");
	else if (res < 0)
		printf("la chaine %s est avant la chaine %s\n", cpi, buf);
	else
		printf("la chaine %s est apres la chaine %s\n", cpi, buf);

	return 0;
}

*/
//--------------------------------------------------
// Concaténer deux chaines
/*
#include <stdio.h>
#include <string.h>

#define NB	100

int main()
{
	char buf[NB] = { 0 };
	char cpi[NB] = { 0 };
	int i;
	printf("entrer chaine :\n");
	fgets(buf, NB, stdin);
	// suppression de ‘\n’, avant dernier caractère
	buf[strlen(buf) - 1] = '\0';
	// la chaîne est mise trois fois à la suite dans cpi
	for (i = 0; i < 3; i++)
		strcat_s(cpi, NB, buf);
	printf("concat : %s\n", cpi);

	return 0;
}

*/

/****************************************************
*                                                   *
* Expérimentation : tableaux et fonctions			*
*                                                   *
*****************************************************/
/*TABLEAU ET FONCTION
- renvoie à la visibilité (accessibilité) des variables dans un
programme :

VARIABLES LOCALES :

- les variables sont locales à la fonction dans laquelle elles
sont déclarées. C'est-à-dire qu'elles sont visibles (accessibles)
uniquement dans le bloc de la fonction et dans tous ses sous-blocs
imbriqués.

- Les valeurs des variables peuvent circuler grâce aux paramètres
d'entrée et au mécanisme de retour (return).

VARIABLES GLOBALES :

- il est possible cependant de déclarer des variables au niveau
fichier en dehors de tout bloc, au-dessus du main(). La variable
est alors accessible de tous les blocs et toutes les fonctions
dans le fichier, sans avoir à utiliser les paramètres ou le
return.

- cette propriété est utilisée pour les définitions de type (typdef,
structures) et des valeurs constantes (#define, enum...).

- elle peut s'avérer utile pour simplifier l'écriture de petits
programmes de moins de 500 lignes de code. Elle ne s'applique
alors que sur quelques variables essentielles du programme.

- utilisée à mauvais escient cette propriété risque de nuire au
développement (en général le développement se trouve rapidement
paralysé au-delà de 1000 lignes de code).
*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// valeur constante définie en global
#define NBMAX 50

// tableau défini et déclaré en global, accessible de partout dans
// le prg
int tabGlo[NBMAX];

// déclaration des fonctions définies en dessous du main() (non
// encore définies au moment de l'appel)
void init_tabGlobal(void);
void affich_tabGlobal(void);
///********************************************************
///********************************************************
int main()
{
	init_tabGlobal();
	affich_tabGlobal();

	return 0;
}
///********************************************************
/// la fonction ne peut agir que sur tabGlo
///********************************************************
void init_tabGlobal()
{
	int i;
	for (i = 0; i<NBMAX; i++)
		tabGlo[i] = rand() % 256;
}
///********************************************************
/// la fonction ne peut agir que sur tabGlo
///********************************************************
void affich_tabGlobal()
{
	int i;
	for (i = 0; i<NBMAX; i++){
		printf("%4d", tabGlo[i]);
		if (i % 10 == 9)
			putchar('\n');
	}
}
/*****************************************************************
TABLEAU LOCAL EN PARAMETRE DE FONCTION
Quelle est la valeur numérique d'un tableau ?

- Soit par exemple la déclaration :

	int tab[10];		// Que vaut tab ?
						// Qu'est-ce que tab pour la machine ?

tab est l'adresse mémoire du bloc alloué pour le tableau, c'està-
dire l'adresse du premier élément du tableau et ils sont tous
consécutifs. Passer un tableau à un paramètre de fonction
suppose passer une adresse mémoire au paramètre.
Le type de variable qui prend pour valeur des adresses mémoire est
le type pointeur.
Donc, pour passer un tableau à une fonction il lui faudra un
pointeur en paramètre.

*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NBMAX_1 20
#define NBMAX_2 NBMAX_1*2

void	init		(int tab[], int taille);
void	affiche		(int tab[], int taille);

///********************************************************
///********************************************************
int main()
{
int tab[NBMAX_1]; // tableau local au main()
	printf("---------init et affiche tab :\n");
	init(tab, NBMAX_1);
	affiche(tab,NBMAX_1);

int tab2[NBMAX_2];
	printf("---------init et affiche tab2 :\n");
	init(tab2, NBMAX_2);
	affiche(tab2,NBMAX_2);

	return 0;
}
///********************************************************
///		la fonction peut agir sur n'importe quel tableau
///		d'entiers.
///
///		IMPORTANT :
///		Parce que l'on écrit à une adresse mémoire les
///		modifications effectuées dans la fonction sont
///		répercutées sur la variable du contexte d'appel qui
///		a donné son adresse (ce que l'on appelle un passage
///		par référence) :
///
///********************************************************
void init(int tab[], int taille) // ou int *tab
{
int i;
	for (i=0; i<taille; i++)
		tab[i]=rand()%256;
}
///********************************************************
///		la fonction peut agir sur n'importe quel tableau
///		d'entiers à une dimension
///********************************************************
void affiche(int tab[], int taille) // ou int *tab
{
int i;
	for (i=0; i<taille; i++){
		printf("%4d",tab[i]);
		if (i%10==9)
			putchar('\n');
	}
}
*/
///********************************************************
///
///		IMPORTANT :
///
///		Le retour d'un tableau statique local à une fonction
///		est impossible : comme pour toutes les variables, la
///		mémoire allouée par la machine est libérée à l'issue
///		de l'exécution du bloc de la fonction.
///		Si l'on retourne l'adresse d'un tableau local
///		celle-ci n'est plus allouée dans la suite des opérations
///		et écrire à une adresse non réservée provoque un plantage
///		ou un comportement incertain du programme.
///
///		Pour que cela marche il faut allouer dynamiquement son
///		tableau, à savoir allouer soi-même la mémoire via un
///		pointeur et une fonction d'allocation (malloc(),calloc()
///		realloc() )
///
///
///********************************************************
/*
int * init()
{
int tab[10];
int i;
	for (i=0; i<taille; i++)
		tab[i]=rand()%256;

	return tab;		// ERREUR!!!!!!!!!!!!!!!!!!
}
*/


/*****************************************************************
TABLEAU LOCAL STATIQUE DE 2 à n DIMENSIONS EN PARAMETRE DE
FONCTION :
- seule la première dimension est convertie en pointeur. Pour
toutes les autres il faut spécifier la taille
*****************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DIM1 10
#define DIM2 15

void	init	(int tab[][DIM2]);
void	affiche	(int tab[][DIM2]);
///********************************************************
///********************************************************
int main()
{
	int dd[DIM1][DIM2]; // tableau 2D local au main()
	printf("---------init et affiche tab 2D :\n");
	init(dd);
	affiche(dd);

	return 0;
}
///********************************************************
///********************************************************
void init(int t[][DIM2])
{
	int i, j;
	for (i = 0; i<DIM1; i++)
	for (j = 0; j<DIM2; j++)
		t[i][j] = rand() % 256;
}
///********************************************************
///********************************************************
void affiche(int t[][DIM2])
{
	int i, j;
	for (i = 0; i<DIM1; i++){
		for (j = 0; j<DIM2; j++)
			printf("%4d", t[i][j]);
		putchar('\n');
	}
}
*/
//-----------------------------------------------------
// EXercice 8 : Extrait code 
/*

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.c>

#define TX 30 // taille zone de jeu en x
#define TY 20 // " en y
#define DECX 5 // décalage par rapport au bord gauche
#define DECY 5 // décalage par rapport au bord haut

// la contrée des terres du milieu
#define BORD 1 // dans la matrice signifie 1 bord
#define MUR 2 // dans la matrice signifie 1 mur
int player[2]; // les coordonnées du player 0 pour x et 1 pour y
int level[TY][TX] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 1,
	1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 2, 2, 1,
	1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};
*/

/************************************************************
															*
FOURMI 2 : UNE COLONIE DE FOURMIS							*
															*
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// nombre max de fourmis
#define MAXFOURMI 50

// en global définition du type de ma structure fourmi
typedef struct {
	float x, y;      // la position de la fourmi
	float dx, dy;    // le déplacement
	int color;      // la couleur
	int lettre;     // l'apparence
}t_fourmi;

// Limites de la zone de jeu
const int TX = 80;
const int TY = 20;

// les actions
t_fourmi   init_fourmi		(void);
void       init_colonie		(t_fourmi f[]);
void       affiche_fourmi	(t_fourmi f, int color);
t_fourmi   avance_fourmi	(t_fourmi f);
void       run_colonie		(t_fourmi f[]);
int        top				(int*start, int dur);
void       gotoxy			(int x, int y);
void       textcolor		(int color);
/*************************************************************
ACTION
*************************************************************
int main()
{
	int start = 0;
	t_fourmi all[MAXFOURMI];

	srand(time(NULL));

	init_colonie(all);
	while (!_kbhit()){

		if (top(&start, 75))
			run_colonie(all);
	}
	return 0;
}
/*************************************************************
INITIALISATION
*************************************************************
t_fourmi init_fourmi()
{
	t_fourmi f;
	f.x = rand() % TX;
	f.y = rand() % TY;
	f.dx = ((float)rand() / RAND_MAX) * 4 - 2;
	f.dy = ((float)rand() / RAND_MAX) * 4 - 2;
	f.lettre = 'A' + rand() % 26;
	f.color = 1 + rand() % 255;
	return f;
}
void init_colonie(t_fourmi f[])
{
	int i;
	for (i = 0; i<MAXFOURMI; i++)
		f[i] = init_fourmi();
}
/*************************************************************
AFFICHAGE une fourmi
*************************************************************
void affiche_fourmi(t_fourmi f, int color)
{
	gotoxy(f.x, f.y);
	textcolor(color);
	putchar(f.lettre);
}
/*************************************************************
MOUVEMENT une fourmi
*************************************************************
t_fourmi avance_fourmi(t_fourmi f)
{
	f.x += f.dx;
	if (f.x < 0){
		f.x = 0;
		f.dx = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.x >= TX){
		f.x = TX - 1;
		f.dx = ((float)rand() / RAND_MAX)* -2;
	}

	f.y += f.dy;
	if (f.y < 0){
		f.y = 0;
		f.dy = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.y >= TY){
		f.y = TY - 1;
		f.dy = ((float)rand() / RAND_MAX)* -2;
	}
	return f;
}
/*************************************************************
RUN : animer toutes les fourmis
Le choix est ici d'animer chaque fourmi une par une plutôt
que toute la colonie d'un coup pour éviter l'effet de "page"
avec un léger interval au noir(effacement de toutes les fourmis,
avancer toutes les fourmis,ré-afficher toutes les fourmis)
*************************************************************
void run_colonie(t_fourmi f[])
{
	int i;

	for (i = 0; i<MAXFOURMI; i++){
		affiche_fourmi(f[i], 0);
		f[i] = avance_fourmi(f[i]);
		affiche_fourmi(f[i], f[i].color);
	}
}
/*************************************************************
OUTILS
*************************************************************
int top(int*start, int dur)
{
	int res = 0;
	if (clock()>*start + dur){
		*start = clock();
		res = 1;
	}
	return res;
}
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
*/

/************************************************************
															*
FOURMI 3 : PLUSIEURS COLONIES DE FOURMIS					*
															*
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// nombre max de fourmis
#define MAXFOURMI	50
// nombre de colonies
#define MAXCOLONIE	4

// en global définition du type de ma structure fourmi
typedef struct {
	float x, y;      // la position de la fourmi²
	float dx, dy;    // le déplacement
	int color;      // la couleur
	int lettre;     // l'apparence
}t_fourmi;

// Limites de la zone de jeu
const int TX = 80;
const int TY = 20;

// les actions
t_fourmi   init_fourmi		(int color, int lettre);
void       init_colonie		(t_fourmi f[], int color, int lettre);
void       init_all_colonie	(t_fourmi f[][MAXFOURMI]);
void       affiche_fourmi	(t_fourmi f, int color);
t_fourmi   avance_fourmi	(t_fourmi f);
void       run_colonie		(t_fourmi f[]);
void       run_all_colonie	(t_fourmi f[][MAXFOURMI]);
int        top				(int*start, int dur);
void       gotoxy			(int x, int y);
void       textcolor		(int color);
/*************************************************************
ACTION
*************************************************************
int main()
{
	int start = 0;
	t_fourmi all[MAXCOLONIE][MAXFOURMI];

	srand(time(NULL));

	init_all_colonie(all);
	while (!_kbhit()){

		if (top(&start, 75))
			run_all_colonie(all);
	}
	return 0;
}
/*************************************************************
INITIALISATION
*************************************************************
t_fourmi init_fourmi(int color, int lettre)
{
	t_fourmi f;
	f.x = rand() % TX;
	f.y = rand() % TY;
	f.dx = ((float)rand() / RAND_MAX) * 4 - 2;
	f.dy = ((float)rand() / RAND_MAX) * 4 - 2;
	f.lettre = lettre;
	f.color = color;
	return f;
}
void init_colonie(t_fourmi f[], int color, int lettre)
{
	int i;
	for (i = 0; i<MAXFOURMI; i++)
		f[i] = init_fourmi(color, lettre);
}
void init_all_colonie(t_fourmi f[][MAXFOURMI])
{
	int i;
	for (i = 0; i<MAXCOLONIE; i++)
		init_colonie(f[i], 1 + rand() % 255, 'A' + rand() % 26);
}
/*************************************************************
AFFICHAGE une fourmi
*************************************************************
void affiche_fourmi(t_fourmi f, int color)
{
	gotoxy(f.x, f.y);
	textcolor(color);
	putchar(f.lettre);
}
/*************************************************************
MOUVEMENT une fourmi
*************************************************************
t_fourmi avance_fourmi(t_fourmi f)
{
	f.x += f.dx;
	if (f.x < 0){
		f.x = 0;
		f.dx = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.x >= TX){
		f.x = TX - 1;
		f.dx = ((float)rand() / RAND_MAX)* -2;
	}

	f.y += f.dy;
	if (f.y < 0){
		f.y = 0;
		f.dy = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.y >= TY){
		f.y = TY - 1;
		f.dy = ((float)rand() / RAND_MAX)* -2;
	}
	return f;
}
/*************************************************************
RUN : animer toutes les fourmis
Le choix est ici d'animer chaque fourmi une par une plutôt
que toute la colonie d'un coup pour éviter l'effet de "page"
avec un léger interval au noir(effacement de toutes les fourmis,
avancer toutes les fourmis,ré-afficher toutes les fourmis)
*************************************************************
void run_colonie(t_fourmi f[])
{
	int i;

	for (i = 0; i<MAXFOURMI; i++){
		affiche_fourmi(f[i], 0);
		f[i] = avance_fourmi(f[i]);
		affiche_fourmi(f[i], f[i].color);
	}
}
void run_all_colonie(t_fourmi f[][MAXFOURMI])
{
	int i;
	for (i = 0; i<MAXCOLONIE; i++)
		run_colonie(f[i]);
}
/*************************************************************
OUTILS
*************************************************************
int top(int*start, int dur)
{
	int res = 0;
	if (clock()>*start + dur){
		*start = clock();
		res = 1;
	}
	return res;
}
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/*************************************************************
*************************************************************/



