/************************************************************
*                                                           *
*       CHAPITRE 9 : Variables pointeur                     *
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
*       1. Principe du pointeur                     *
*                                                   *
*****************************************************/

//Fonctionnement des quatre opérateurs
//Opérateur adresse : &
/*
#include <stdio.h>

int main()
{
char c;
int i,j;
struct {
	 int x,y;
	 float dx,dy;
}s1;
	printf("l’adresse de c est : %p\n", &c);
	printf("l’adresse de i est : %p\n", &i);
	printf("l’adresse de j est : %p\n", &j);
	printf("l’adresse de s1 est : %p\n", &s1);
	return 0;
}
*/
//--------------------------------------------------
//Opérateur étoile : *
/*
#include <stdio.h>
int main()
{
int i = 23;					// 1
int  *ptr;

	ptr = &i;				// 2
	printf("%d, ",*ptr);

	*ptr = 55;				// 2
	printf("%d, ",i);

	i = 777;				// 3
	printf("%d.",*ptr);
	return 0;
}
*/
//--------------------------------------------------
//Opérateur flèche : ->
/*
#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int vie;
	float x, y, dx, dy;
	int color;
}ennemi;
int main()
{
	ennemi S1;
	ennemi* p;
	p = &S1;

	// test avec opérateur point, jamais utilisé
	(*p).vie = 1;
	(*p).x = rand() % 80;
	(*p).y = rand() % 25;
	printf("vie : %d, x : %.2f, y : %.2f\n", (*p).vie, (*p).x, (*p).y);

	// remplacement par ->
	p->vie = 1;
	p->x = rand() % 80;
	p->y = rand() % 25;
	printf("vie : %d, x : %.2f, y : %.2f\n", p->vie, p->x, p->y);

	return 0;
}
*/
//--------------------------------------------------
// Opérateur crochet : [ ]
/*#include <stdlib.h>
#include <stdio.h>

int main()
{
	int tab[50];

	int* p;
	p = tab;

	int i;
	for (i = 0; i < 50; i++) {
		p[i] = rand() % 256;
		printf("p[%d] = %d\n", i, p[i]);
	}
	printf("--------------------\n");
	for (i = 0; i < 50; i++) {
		*(p + i) = rand() % 256;
		printf("p[%d] = %d\n", i, *(p + i));
	}

	return 0;
}
*/
//--------------------------------------------------
//Allouer dynamiquement de la mémoire
/*
//La fonction malloc()
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NBCHOSE 10
typedef struct {
	int x, y, color;
}Chose;

int main()
{
	Chose* ptr;
	Chose* choses[NBCHOSE];        // tableau de pointeurs Chose*
	int i;

	srand((unsigned)time(NULL));
	ptr = malloc(sizeof(Chose));
	ptr->x = rand() % 800;
	ptr->y = rand() % 600;
	ptr->color = rand() % 256;
	printf("ptr, une Chose prend l'adresse %p et vaut:%d,%d,%d\n",
		ptr, ptr->x, ptr->y, ptr->color);


	for (i = 0; i < NBCHOSE; i++) {
		choses[i] = malloc(sizeof(Chose));
		choses[i]->x = rand() % 800;
		choses[i]->y = rand() % 600;
		choses[i]->color = rand() % 256;
		printf("choses[%d] prend l'adresse %p et vaut:%d,%d,%d\n",
			i, choses[i], choses[i]->x, choses[i]->y, choses[i]->color);
	}

	return 0;
}
*/
//--------------------------------------------------
//Libérer la mémoire allouée : la fonction free()
/*
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
double*p[500000];
int i;
int fin=0;
	do{
        printf("\n\n");

        for (i=0; i<500000; i++)
 		   p[i]=malloc(sizeof(double)) ;  	// 1

        for (i=0; i<500000; i++)			// 2
 		   free(p[i]) ;

        printf("Play again ? (o/n)\n");
        fin=getch();

	}while(fin!='n');
	return 0;
}
*/
//--------------------------------------------------
//Attention à la validité d'une adresse mémoire 1
/*
//Validité d'une adresse mémoire
#include <stdio.h>

int main()
{
char*ptr;
char tab[80];
	printf("entrer une phrase :\n");
	fgets(tab,80,stdin);
	printf("tab : %s\n",tab);

	printf("entrer une autre phrase :\n");
	fgets(ptr,80,stdin);	// ERREUR !! le programme quitte ou comportement incertain
	printf("ptr : %s\n",ptr);
    return 0;
}
*/
//--------------------------------------------------
//Attention à la validité d'une adresse mémoire 2
/*
#include <stdio.h>

int main()
{
char*ptr;
char tab[80];
	printf("entrer une phrase :\n");
	fgets(tab,80,stdin);
	printf("tab : %s\n",tab);

	ptr=tab;
	printf("entrer une autre phrase :\n");
	fgets(ptr,80,stdin);			// ok
	printf("ptr : %s",ptr);			//
	printf("tab : %s\n",tab);		// ptr et tab sont identiques
    return 0;
}
*/
//--------------------------------------------------
//Attention à la validité d'une adresse mémoire 3
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char* ptr;
	char tab[80];
	printf("entrer une phrase :\n");
	fgets(tab, 80, stdin);

	// un nouveau bloc alloué
	int taille = strlen(tab) + 1;
	ptr = (char*)malloc(sizeof(char) * taille);

	// copie de tab
	strcpy_s(ptr, taille, tab);

	// modification de la copie
	for (unsigned i = 0; i < strlen(ptr); i++)
		ptr[i]++;

	// ptr et tab sont différents
	printf("ptr : %s\n", ptr);
	printf("tab : %s\n", tab);

	return 0;
}
*/
//--------------------------------------------------
// Pointeurs et constantes
// l'objet pointé supposé constant, le pointeur peut varier :
/*

#include <stdio.h>
#include <stdlib.h>

int main()
{
	const int val = 100; // objet constant
	int v2 = 0;			 // objet non constant
	const int *p = &val; // pointeur de const int, non constant

	// *p += 10; // erreur, objet pointé supposé constant
	 
	p = &v2;	 // p non constant, peut varier

	// *p += 10; // erreur, ojet pointé supposé constant

	printf("val : %d et *p : %d\n", val, *p);

	return 0;
}
*/
//--------------------------------------------------
// l'objet pointé est constant mais le pointeur n'est pas 
// un pointeur de constante
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{

	const int val = 100; // objet constant
	int *p = &val; // pointeur de int ordinaire

	// pas d'erreur, possibilité de modifier la variable constante
	*p += 10; 
	printf("val : %d et *p : %d\n", val, *p);

	return 0;
}
*/
//--------------------------------------------------
// le pointeur est constant, l'objet pointé est modifiable
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int val = 100; 
int v2 = 0;
int*const p = &val; // pointeur constant de int

	p = &v2;	// erreur p constant

	printf("val : %d et *p : %d\n", val, *p);

	return 0;
}
*/
//--------------------------------------------------
// pointeur constant mais objet pointé constant
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	const int val = 100;
	int*const p = &val; // pointeur constant de int

	*p += 10;	// ok objet pointé devient modifiable

	printf("val : %d et *p : %d\n", val, *p);

	return 0;
}
*/
//--------------------------------------------------
// pointeur constant et objet pointé constant :
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int val = 100;
	int v2 = 0;
	const int * const p = &val; // pointeur constant de int

	// p = &v2;	// erreur p constant
	*p += 10;	// erreur pointeur de const int

	printf("val : %d et *p : %d\n", val, *p);

	return 0;
}
*/
//--------------------------------------------------
//Cas des tableaux de pointeurs
//Une structure de données très utile
/*
#include <stdio.h>
#include <stdlib.h>

#define NBMAX   10

typedef struct troll{
    int x,y;
    int color;

}t_troll;

void initialisation(t_troll* t[])
{
int i;
    for (i=0; i<NBMAX; i++){

        t[i]=(t_troll*)malloc(sizeof(t_troll));
        t[i]->x=rand()%800;
        t[i]->y=rand()%600;
        t[i]->color=rand()%256;
    }
}
void affiche(t_troll*t[])
{
int i;
    for (i =0; i<NBMAX; i++){
       printf("troll%d : %4d %4d %4d\n",i,t[i]->x,t[i]->y,t[i]->color);
    }
}
int main()
{
t_troll* ALL[NBMAX];

    initialisation(ALL);
    affiche(ALL);
	return 0;
}
*/
//--------------------------------------------------
//Utiliser les arguments de lignes de commandes
/*
// compiler puis lancer à partir de la ligne de commande
// en passant une ou plusieurs chaines de caractères
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[])
{
int i;
    printf("nom du programme : %s\n",argv[0]);
    if (argc>1)
        for (i=1;i<argc; i++ )
            printf("param %d : %s\n",i,argv[i]);

    // suite du programme qui prend ou non en compte
    // les arguments reçus.

	return 0;
}
*/
//--------------------------------------------------
// Une fonction est une adresse
/*
#include <stdio.h>
#include <stdlib.h>
void maFonction(int val)
{
	printf("maFonction, val = %d\n", val);
}
int main()
{
	printf("adresse de maFonction :%p\n", maFonction);

	return 0;
}
*/
//--------------------------------------------------
//Appeler une fonction via un pointeur 1
/*
#include <stdio.h>
#include <stdlib.h>

void maFonction(int val)
{
	printf("maFonction, val = %d\n", val);
}
int main()
{
	void*p = maFonction;
	// l'appel de :
	((void(*)(int))p)(10);
	// équivalent à un appel de :
	// maFonction(10);

	return 0;
}
*/
//--------------------------------------------------
//Appeler une fonction via un pointeur 2
/*
#include <stdio.h>
#include <stdlib.h>

void maFonction(int val)
{
	printf("maFonction, val = %d\n", val);
}
int main()
{
void (*p)(int) ;      // déclaration du pointeur de fonction

	p = maFonction;   // affectation de la fonction de même type

	p(10);            // appel de la fonction via le pointeur
					  // avec 10 passé au paramètre

	return 0;
}

*/
//--------------------------------------------------
//Pourquoi des pointeurs de fonction ?
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void f1(int val1, int val2)
{
	printf("f1 avec val1 %3d et val2 %3d", val1, val2);
}
void f2(int val1, int val2)
{
	printf("f2 avec val1 %3d et val2 %3d", val1, val2);
}
void f3(int val1, int val2)
{
	printf("f3 avec val1 %3d et val2 %3d", val1, val2);
}
void f4(int val1, int val2)
{
	printf("f4 avec val1 %3d et val2 %3d", val1, val2);
}
void cntl(int v1, void(*p)(int, int))
{
	int v2 = rand() % 1000;
	printf("instructions de : ");
	p(v1, v2);
	printf(" dans cntl\n");
}
int main()
{
	int play = 'o';
	srand(time(NULL));
	while (play == 'o'){
		int val = rand() % 100;
		switch (rand() % 4){
			case 0: cntl(val, f1); break;
			case 1: cntl(val, f2); break;
			case 2: cntl(val, f3); break;
			case 3: cntl(val, f4); break;
		}
		printf("nouvel appel ?(o/n)\n");
		scanf_s("%c", &play, 1);
		rewind(stdin);
	}
	return 0;
}
*/
//--------------------------------------------------


/****************************************************
*													*
*	Expérimentation : base pointeur					*
*													*
/****************************************************/
// Principe
/*Qu'est ce qu'un pointeur ?
une variable qui prend uniquement des adresses mémoire
pour valeur.

A quoi servent les pointeurs ?
Trois utilisations :
1) en paramètre de fonction : permet de passer l'adresse
mémoire d'une variable et de transformer l'entrée en sortie
(possibilité d'écrire à une adresse mémoire)

2) allocation dynamique d'objets ou de tableaux d'objets

3) créer des structures de données dynamique non natives
en C : listes chainées, arbres, graphes

Comment les utilise t-on ?
Il y a quatre opérateurs associés et trois fonctions
d'allocation de mémoire (pour l'allocation dynamique)

Les quatre opérateurs sont :
1) "adresse de" : & permet de récupérer l'adresse mémoire
d'une variable

2) "étoile" : * permet de déclarer un pointeur etd'accéder
à une adresse mémoire.

EXEMPLE :
int a;
int *ptr; // déclaration d'un pointeur d'entier
    ptr = &a; // ptr prend pour valeur l'adresse de a
*/
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a;
int*ptr=&a;

   a= 100;
   *ptr=200;
   printf("a : %d / *ptr : %d\n",a,*ptr);

   return 0;
}
*/
/****************************************************

3) "flèche" : -> permet daccéder à un champ de structure
via un pointeur

EXEMPLE :
struct test{
   int x,y;
} t;

struct test *ptr;
   ptr=&t;
   ptr->x=450;
   ptr->y=90;

équivaut à : (*ptr).x=450 et (*ptr).y=90
la flèche est juste une contraction, une facilité
d'écriture
*/
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
struct test{
   int x,y;
} t;
struct test *ptr;

   ptr=&t;
   ptr->x=450;
   ptr->y=90;
   printf("t.x=%d, t.y=%d\n", t.x, t.y);

   return 0;
}
*/
/****************************************************
4) "crochet" : [] c'est l'opérateur tableau, à partie
d'une adresse de départ il permet d'accéder aux adresses
des différents éléments du tableau

EXEMPLE :

int tab[50];
int*ptr;
    ptr=tab;   // ptr prend l'adresse du tableau cad
               // l'adresse du premier élément du tableau

    for (i=0; i<50; i++)
       ptr[i] = rand()%256;

    // équivalent à :
    for (i=0; i<50; i++)
       *(ptr+i) = rand()%256;

*/
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int tab[10];
int*ptr;
int i;

   ptr=tab;
   for (i=0; i<10; i++){
      ptr[i] = rand()%256;
      printf("ptr[%d] = %d\n",i,ptr[i]);
   }

   // équivalent à :
   for (i=0; i<10; i++){
      *(ptr+i) = ptr[i]+1;
      printf("*(ptr+%d) = %d\n",i,*(ptr+i));
   }
   return 0;
}
*/
/****************************************************
*                                                   *
*       2. Allocation dynamique de tableaux         *
*                                                   *
*****************************************************/

// Allouer un tableau en même temps qu'une structure
/*
#include <stdio.h>
#include <stdlib.h>

#define NBMAX   10
typedef struct {
	int temps;
	float stock[];
}Mesure;

void pause(void);

int main()
{
	Mesure *mesure= malloc(sizeof(Mesure)+ sizeof(float[NBMAX]));

	mesure->temps = 1;
	for (int i = 0; i < NBMAX; i++)
		mesure->stock[i] = (float)rand() / RAND_MAX * 10;
	for (int i = 0; i < NBMAX; i++)
		printf("stock[%d]=%.2f\n", i, mesure->stock[i]);

	pause();
	return 0;
}
void pause()
{
	printf("Appuyez sur enter pour continuer\n");
	rewind(stdin);
	getchar();
}

*/
//---------------------------------------------------
// Allouer un tableau avec un pointeur (tableau d'entiers)
/*
#include <stdio.h>
#include <stdlib.h>

  // fonction qui alloue un tableau de nb entiers
int*AllouerTableau(int taille)
{
	int*ptr = (int*)malloc(sizeof(int)*taille);
	if (ptr == NULL)
		   exit(EXIT_FAILURE);
	return ptr;
}

int main()
{
	int* p;
	// alloue un tableau de 10 int
	p= AllouerTableau(10);
	// detruit le tableau, libère la mémoire
	free(p);

	  // alloue un tableau de 15 int
	p = AllouerTableau(15);
	// detruit le tableau, libère la mémoire
	free(p);

	return 0;
}


*/
//---------------------------------------------------
// Allouer un tableau avec un pointeur (tableau de structures)
/*
#include <stdio.h>
#include <stdlib.h>

  typedef struct {
	char nom[256];
	int age;
}Pers;

// alloue et initialise un tableau de nb Pers
Pers* CreateTableau(int nb)
{
char*noms[4] = { "Alex", "Fred", "Jean", "Cathy"};

	// allocation d'un tableau de nb Pers
	Pers*p = (Pers*)malloc(sizeof(Pers)*nb);

	// initialisation avec des valeurs aléatoires
	int i;
	for (i = 0; i < nb; i++) {
		   strcpy_s(p[i].nom, 256, noms[rand() % 4]);
		   p[i].age = 10 + rand() % 30;
	}
	return p;
}

void AfficheTableau(Pers*p, int nb)
{
	int i;
	for (i = 0; i < nb; i++)
		   printf("%s : %d ans\n", p[i].nom, p[i].age);
}

int main()
{
	Pers*p;
  // allocation avec initialisation d'un tableau de 10 Pers
	p = CreateTableau(10);

	AfficheTableau(p, 10);
	free(p);

	return 0;
}
*/
//---------------------------------------------------
// Allouer une matrice avec un pointeur de pointeur 1
/*
// Allouer une matrice avec un pointeur de pointeur
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main(int argc, char *argv[])
{
int**mat;							// 1
int tx,ty,i,j,fin=0;

	srand(time(NULL));
	do{

        tx=1+rand()%30;					// 2
	    ty=1+rand()%10;
	    mat=(int**)malloc(sizeof(int*)*ty);
        for (i=0; i<ty; i++){
            mat[i]=(int*)malloc(sizeof(int)*tx);

            for (j=0; j<tx; j++){
                mat[i][j]=rand()%2;
                printf("%2d",mat[i][j]);
            }
            putchar('\n');
       }

       for (i=0; i<ty; i++)				// 3
			free(mat[i]);
       free(mat);

       printf("\nAutre matrice ? (o/n)\n\n");
       fin=_getch();
	}while(fin=='o');

  	return 0;
}
*/
//---------------------------------------------------
// Allouer une matrice avec un pointeur de pointeur 2 (fonctions d'allocation)
/*
#include <stdio.h>
#include <stdlib.h>

int** AllouerMatrice(int d1, int d2)
{
	  int y;
	  int**mat = (int**)malloc(sizeof(int*)*d1);
	  for (y = 0; y < d1; y++)
		   mat[y] = (int*)malloc(sizeof(int)*d2);
	  return mat;
}
void InitMatrice(int**m, int d1, int d2)
{
	  int y, x;
	  for (y = 0; y < d1; y++)
		   for (x = 0; x < d2; x++)
				m[y][x] = rand() % 100;
}
void AfficheMatrice(int**m, int d1, int d2)
{
	  int y, x;
	  for (y = 0; y < d1; y++) {
		   for (x = 0; x < d2; x++)
				printf("%3d", m[y][x]);
		   putchar('\n');
	  }
}
void DestroyMatrice(int**mat, int d1)
{
	  int y;
	  for (y = 0; y < d1; y++) {
		   free(mat[y]);
	  }
	  free(mat);
}

int main()
{
	  int**mat;
	  int nbligne, nbcolonne;
	  srand(time(NULL));

	  // alloue une matrice de taille aléatoire
	  nbligne = 1 + rand() % 20;
	  nbcolonne = 1 + rand() % 40;
	  mat = AllouerMatrice(nbligne,nbcolonne);

	  // initialise avec des valeurs puis affiche
	  InitMatrice(mat, nbligne, nbcolonne);
	  AfficheMatrice(mat, nbligne, nbcolonne);

	  // détruit la matrice
	  DestroyMatrice(mat, nbligne);
	  return 0;
}
*/
//--------------------------------------------------
// Tableau dynamique de pointeurs de structures
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int x, y;
}Coord;

Coord** AllouerTabPtr(int nb)
{
	Coord** c;
	int i;
	// allocation du tableau de pointeurs
	c = (Coord**)malloc(sizeof(Coord*)*nb);

	// allocation de chaque pointeur dans le tableau
	for (i = 0; i < nb; i++)
		   c[i] = (Coord*)malloc(sizeof(Coord));

	return c;
}
void InitTab(Coord*c[], int nb)
{
	int i;
	for (i = 0; i < nb; i++) {
		   c[i]->x = rand() % 100;
		   c[i]->y = rand() % 100;
	}
}
void AfficheTab(Coord*c[], int nb)
{
	int i;
	printf("%d elements : \n", nb);
	for (i = 0; i < nb; i++)
		   printf("(%d,%d)\n",c[i]->x, c[i]->y);
}
void DestroyTab(Coord*c[],int nb)
{
	int i;
	for (i = 0; i < nb; i++)
		   free(c[i]);
	free(c);
}

int main()
{
	Coord**C;
	int nb;
	srand((unsigned)time(NULL));
	nb = 1 + rand() % 30;

	C = AllouerTabPtr(nb);
	InitTab(C, nb);
	AfficheTab(C, nb);
	DestroyTab(C, nb);

	return 0;
}
*/
//--------------------------------------------------
// Allocation dynamique d'un tableau de pointeurs sur des unions
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// pour identifier les types de structures
enum { MISSILE, VAISSEAU };

// ce define sert uniquement à compacter l'écriture
// (il évite d'avoir à réécrire à la main ces cinq données
// communes dans les trois structures)
#define COMMUN     int type;\
int x; \
int y; \
int dx; \
int dy;

// la structure commune aux données
// des missiles et des vaisseaux
typedef struct
{
	COMMUN
}Commun;

// les spécificités d'un missile
typedef struct
{
	COMMUN
		int charge;
}Missile;

// le constructeur d'un missile
Missile ConstructMissile()
{
	Missile m;
	m.type = MISSILE;
	m.x = rand() % 100;
	m.y = rand() % 100;
	m.dx = rand() % 11 - 5;
	m.dy = rand() % 11 - 5;
	m.charge = rand() % 1000;
	return m;
}

// les spécificités d'un vaisseau
typedef struct
{
	COMMUN
		int color;
	char lettre;
}Vaisseau;

// le constructeur d'un vaisseau
Vaisseau ConstructVaisseau()
{
	Vaisseau v;
	v.type = VAISSEAU;
	v.x = rand() % 100;
	v.y = rand() % 100;
	v.dx = rand() % 11 - 5;
	v.dy = rand() % 11 - 5;
	v.lettre = 'A' + rand() % 26;
	v.color = rand() % 256;
	return v;
}

// l'union Entite qui permet de gérer
// un vaisseau ou un missile
typedef union
{
	int type;
	Commun commun;
	Missile missile;
	Vaisseau vaisseau;
}Entite;

// crée un tableau dynamique de nb pointeurs sur
// des unions Entite. Chaque Entite est aléatoirement
// soit un missile soit un vaisseau.
Entite** CreateTabPointeurs(int nb)
{
	Entite** e;
	int i;
	e = (Entite**)malloc(sizeof(Entite*) * nb);
	for (i = 0; i < nb; i++)
	{
		// Chaque élément est un pointeur
		// qu'il ne faut pas oublier d'allouer !
		e[i] = (Entite*)malloc(sizeof(Entite));

		// Les sous-ensembles type et commun sont
		// initialisés lorsque l'on initialise un
		// vaisseau ou un missile. Ils constituent
		// ensuite des facilités de lecture et
		// d'écriture pour certaines opérations
		// communes aux missiles et vaisseaux.
		if (rand() % 2)
			e[i]->vaisseau = ConstructVaisseau();
		else
			e[i]->missile = ConstructMissile();
	}
	return e;
}
void AfficheTab(Entite** e, int nb)
{
	int i;
	for (i = 0; i < nb; i++) {

		// données spécifiques missiles ou vaisseaux
		if (e[i]->type == MISSILE) {
			printf("Missile  : ");
			printf("charge %d, ", e[i]->missile.charge);
		}
		else {
			printf("Vaisseau : ");
			printf("lettre %c, color %d ", e[i]->vaisseau.lettre,
				e[i]->vaisseau.color);
		}
		// types de données commununes pour un missil et pour un
		// vaisseau
		printf("x %d, y %d, dx %d, dy %d\n",
			e[i]->commun.x, e[i]->commun.y,
			e[i]->commun.dx, e[i]->commun.dy);

	}
}
void DestroyTab(Entite** e, int nb)
{
	int i;
	// libérer chaque pointeur
	for (i = 0; i < nb; i++)
		free(e[i]);
	// libérer le pointeur de pointeurs
	free(e);
}
int main()
{
	Entite** E;
	int nb;

	srand(time(NULL));

	// nombre d'entites aléatoire
	nb = 1 + rand() % 20;

	// allocation du tableau et de ses éléments
	E = CreateTabPointeurs(nb);

	AfficheTab(E, nb);
	DestroyTab(E, nb);

	return 0;
}
*/
//--------------------------------------------------
// Différences entre tableaux statiques et dynamiques
/*

#include <stdio.h>
#include <stdlib.h>
int main()
{
	int tabStat[1000000];	// quitte avec l'erreur 0XC00000FD pour
							// dépassement de capacité
	int * tabDyn;
	tabDyn = (int*)malloc(sizeof(int)* 1000000); // pas d’erreur
	free(tabDyn);
	return 0;
}
*/
//--------------------------------------------------
//Autres fonctions d'allocation dynamique
//Fonction calloc()
/*

#include <stdio.h>
#include <stdlib.h>

int main()
{
int nb,i;
int*tab;
	printf("entrer la taille du tableau:\n");	// 1
	scanf_s("%d",&nb);
	tab=(int*)calloc(nb,sizeof(int));		// 2
	for (i=0; i<nb; i++){				// 3
	    tab[i]=rand()%256;
	    printf("tab[%d]=%d\n",i,tab[i]);
	}
	return 0;
}
*/
//--------------------------------------------------
//Fonction realloc()
/*

#include <stdio.h>
#include <stdlib.h>

int main()
{
int nb,i,k;
int *tab=NULL;						// 1

	for (i=0; i<10; i++){				// 2
	    printf("entrer une nouvelle taille de tableau:\n");
	    scanf_s("%d",&nb);
	    tab=(int*)realloc(tab,sizeof(int)*nb);
	    for (k=0; k<nb; k++){				// 3
	        if(tab[k]!=k)
		      tab[k]=k;
		  printf("%d ",tab[k]);
	    }
	}
	return 0;
}
*/
/****************************************************
*                                                   *
*       3. Pointeurs en paramètre de fonction       *
*                                                   *
*****************************************************/
//Passage par référence
//Cas général d'une variable quelconque 1
/*
#include <stdio.h>

void modif(int e1)
{
	e1=50;
}

int main()
{
int v=10;
	modif(v);
	printf("v=%d \n", v);
	return 0;
}
*/
//--------------------------------------------------
//Cas général d'une variable quelconque 2
/*
#include <stdio.h>

void modif( int *x)
{
	*x=50;
}

int main()
{
int v=10;

	printf( "v=%d\n",v);	// v vaut 10
	modif( &v );		// passage de l'adresse de v au paramètre x
	printf( "v=%d\n",v);	// v vaut maintenent 50
	return 0;
}
*/
//--------------------------------------------------
//Exemple : une fonction qui retourne l'heure
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hms(int *h, int *m, int*s)
{
time_t tu; 				// pour récup temps universel (interne)
struct tm *p;			// pour récup format lisible

	time(&tu);			// passage par référence variable tu
	p = localtime(&tu); // passage adresse de tu juste pour lecture
						// mais retour d'une adresse de structure 			      
						// obtenue dynamiquement dans la fonction

	*h = p->tm_hour;	// écriture à l'adresse h de l'heure
	*m = p->tm_min;		// écriture à l'adresse m des minutes
	*s = p->tm_sec;		// écriture à l'adresse s des secondes
}

int main()
{
 int h, m, s;

		hms(&h, &m, &s);
		printf("%d : %d : %d\n",h,m,s);
		return 0;
}
*/
//--------------------------------------------------
//Passage par référence d'une structure
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct troll{
	int x, y;
	int color;
}t_troll;

void init(t_troll*p)
{
	p->x = rand() % 800;
	p->y = rand() % 600;
	p->color = rand() % 256;
}

int main()
{
t_troll t;
t_troll* ALL[10];   // attention les pointeurs ne sont pas alloués
int i;

	srand(time(NULL));

	init(&t); // ok

	for (i = 0; i < 10; i++){
		ALL[i] = (t_troll*)malloc(sizeof(t_troll)); // alocation de chaque t_troll
		init(ALL[i]);  // chaque élément est un pointeur
	}
	
	// libérer la mémoire allouée
	for (i = 0; i < 10; i++)
		free(ALL[i]);

	return 0;
}
*/
//--------------------------------------------------
//Passage par référence d'une variable pointeur 1
/*
#include <stdio.h>
#include <stdlib.h>

void alloue(float**f,int taille)
{
	*f=(float*)malloc(sizeof(float)*taille);
}

int main()
{
 float*tab;
 int i;
	alloue(&tab, 10);
	for (i=0; i<10; i++){
	    tab[i]= (rand()%10000)/100.0;
	    printf("%f ",tab[i]);
	}
	putchar('\n');

	return 0;
}
*/
//--------------------------------------------------
//Passage par référence d'une variable pointeur 2
/*
#include <stdio.h>
#include <stdlib.h>

void alloue(int***m,int t1, int t2)
{
int i;
   *m=(int**)malloc(sizeof(int*)*t1);
   for (i=0; i<t1; i++)
      (*m)[i]=(int*)malloc(sizeof(int)*t2);
}

void init(int**mat, int t1, int t2)
{
int i, j;
   for (i=0; i<t1; i++)
      for (j=0; j<t2; j++)
         mat[i][j]=rand()%100;
}

void affiche(int**mat, int t1, int t2)
{
int i, j;
   for (i=0; i<t1; i++){
      for (j=0; j<t2; j++)
         printf("%3d",mat[i][j]);
      putchar('\n');
   }
}

int main()
{
int**mat;

   alloue(&mat,5,10); // à l'adresse de mat passée par référence
   init(mat,5,10);   // à la valeur de mat (adresse de la matrice)
   affiche(mat,5,10);
   return 0;
}
*/
//--------------------------------------------------
//Passage par référence d'une variable pointeur 3
/*
#include <stdio.h>
#include <stdlib.h>

#define NBMAX   100
typedef struct troll {
	int x, y;
	int color;

}t_troll;

void init(t_troll** p)
{
	*p = (t_troll*)malloc(sizeof(t_troll));
	(*p)->x = rand() % 800;
	(*p)->y = rand() % 600;
	(*p)->color = rand() % 256;
}
void initialisation(t_troll* t[])
{
	int i;
	for (i = 0; i < NBMAX; i++)
		init(t + i);// équivalent de &t[i]
}

void affiche(t_troll* t[])
{
	int i;
	for (i = 0; i < NBMAX; i++) {
		printf("%4d %4d %4d\n", t[i]->x, t[i]->y, t[i]->color);
	}
}
void pause()
{
	printf("Appyuez sur enter pour continuer\n");
	getchar();
}
int main()
{
	t_troll* ALL[NBMAX];

	initialisation(ALL);
	affiche(ALL);

	pause();
	return 0;
}

*/
//--------------------------------------------------
// Subtilités à propos des tableaux en paramètre 
// de fonction
/*
#include <stdio.h>
#include <stdlib.h>

#define TY         3	// nombre de lignes
#define TX         8	// nombre de colonnes

void test1 	( char**tab )
{
int x,y;
	putchar('\n');
  	for (y=0;y<TY;y++){
  	    putchar('\t');
  	    for (x=0; x<TX; x++)
  	        putchar(tab[y][x]);
  	    putchar('\n');
  	}
	putchar('\n');
}
void test2	( char* tab[ ] )
{
int x,y;
	putchar('\n');
  	for (y=0;y<TY;y++){
  	    putchar('\t');
  	    for (x=0; x<TX; x++)
  	        putchar(tab[y][x]);
  	    putchar('\n');
  	}
	putchar('\n');
}
void test3	( char tab[ ][TX] )
{
int x,y;
	putchar('\n');
  	for (y=0;y<TY;y++){
  	    putchar('\t');
  	    for (x=0; x<TX; x++)
  	        putchar(tab[y][x]);
  	    putchar('\n');
  	}
	putchar('\n');
}


int main()
{
// les déclarations des tableaux
char mat1[TY][TX];
char*mat2[TY];
char**mat3;
int y,x;

	// les tableaux sont alloués si nécessaire et initialisés
	// avec les mêmes valeurs
    for (y=0; y<TY; y++)
   	   for (x=0; x<TX; x++)
         mat1[y][x]='0'+x;

    for (y=0; y<TY; y++){
   	   mat2[y]=(char*)malloc(sizeof(char)*TX);
   	   for (x=0; x<TX; x++)
   	      mat2[y][x]='0'+x;
    }

    mat3=(char**)malloc(sizeof(char*)*TY);
    for (y=0;y<TY;y++){
        mat3[y]=(char*)malloc(sizeof(char)*TX);
        for (x=0; x<TX; x++)
            mat3[y][x]='0'+x;
   }

	// première série de test avec mat1 en paramètre pour chacune
	//des fonctions
	printf( "TEST 1  Passage de :  char mat1[TY][TX] \n\n");
    printf( "appel de la fonction f(char**tab)    :  "
            "Warming et plante\n");
	//test1(mat1);
    putchar('\n');
    printf( "appel de la fonction f(char* tab[])  :  "
            "Warming et plante\n");
	//  test2(mat1);
    putchar('\n');
    printf( "appel de la fonction f(char tab[][TX]): ok\n");
    test3(mat1);

	// série 2 avec mat2
 	printf( "TEST 2  Passage de :  char *mat2[TY] \n\n");
  	printf( "appel de la fonction f(char**tab)          : ok\n");
  	test1(mat2);
  	printf( "appel de la fonction f(char* tab[])     : ok\n");
 	test2(mat2);
 	printf( "appel de la fonction f(char tab[][TX])  : "
            "Warming et resultats incertains ou erreur\n");
 	//test3(mat2);

	// série 3 avec mat3
 	printf( "TEST 3  Passage de :  char**mat3 \n\n");
  	printf( "appel de la fonction f(char**tab)       :   ok\n");
  	test1(mat3);
  	printf( "   appel de la fonction f(char* tab[])  :   ok\n");
  	test2(mat3);
  	printf( "   appel de la fonction f(char tab[][TX]):  "
            "Warming et resultats incertains ou erreur \n");
  	test3(mat3);
  	return 0;
}
*/
//--------------------------------------------------------------
// Association de structures de types différents
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR	256
typedef struct pilote
{
	struct avion* avion;
	char nom[MAXCHAR];

}pilote;

typedef struct avion
{
	struct pilote* pilote;
	char type[MAXCHAR];
	int num;
}avion;

pilote* ConstructPilote(char* nom, avion* a)
{
	pilote* p;
	p = (pilote*)malloc(sizeof(pilote));
	strcpy_s(p->nom, MAXCHAR, nom);
	p->avion = a;
	if (a != NULL)
		a->pilote = p;
	return p;
}

avion* ConstructAvion(char* type, int num, pilote* p)
{
	avion* a;
	a = (avion*)malloc(sizeof(avion));
	strcpy_s(a->type, MAXCHAR, type);
	a->num = num;
	a->pilote = p;
	if (p != NULL)
		p->avion = a;
	return a;
}

void AffichePilote(pilote* p)
{
	printf("%s pilote ", p->nom);
	if (p->avion == NULL)
		printf("rien\n");
	else
		printf("le %s numero %d\n", p->avion->type, p->avion->num);
}

void AfficheAvion(avion* a)
{
	printf("L'avion de type %s numero %d ", a->type, a->num);
	if (a->pilote == NULL)
		printf("n'a pas de pilote\n");
	else
		printf("est pilote par %s\n", a->pilote->nom);
}
int main()
{
	//allocation dynamique
	avion* airbus = ConstructAvion("Airbus A340", 18, NULL);
	AfficheAvion(airbus);

	pilote* tintin = ConstructPilote("Tintin", airbus);
	AffichePilote(tintin);

	// libération mémoire
	free(airbus);
	free(tintin);

	return 0;
}

*/
//--------------------------------------------------------------
// Association de deux structures de même type
// deux personnes se connaissent
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR	256
typedef struct pers
{
	struct pers* connait;
	char nom[MAXCHAR];
	int age;

}pers;

pers* ConstructPers(char* nom, int age, pers* connaissance)
{
	pers* p;
	p = (pers*)malloc(sizeof(pers));
	strcpy_s(p->nom, MAXCHAR, nom);
	p->age = age;
	p->connait = connaissance;
	return p;
}
void AffichePers(pers* p)
{
	printf("nom : %s\n", p->nom);
	printf("age : %d\n", p->age);
	printf("connaissance : %s\n", p->connait == NULL ? "personne" : p->connait->nom);
	printf("----------------------\n");
}

int main()
{
	// Alain 25 ans ne connait personne
	pers*Alain = ConstructPers("Alain", 25, NULL);
	AffichePers(Alain);

	// Isabelle, 30 ans connait Alain
	pers*Isabelle = ConstructPers("Isabelle", 30, Alain);
	AffichePers(Isabelle);

	// Alain fait connaissance d'Isabelle
	Alain->connait = Isabelle;
	AffichePers(Alain);

	return 0;
}

*/
//--------------------------------------------------------------
// Association de deux structures de même type
// plusieurs personnes se connaissent et forment une liste
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR	256
typedef struct pers
{
	struct pers* connait;
	char nom[MAXCHAR];
	int age;

}pers;

pers* ConstructPers(char* nom, int age, pers* connaissance)
{
	pers* p;
	p = (pers*)malloc(sizeof(pers));
	strcpy_s(p->nom, MAXCHAR, nom);
	p->age = age;
	p->connait = connaissance;
	return p;
}
void AffichePers(pers* p)
{
	printf("nom : %s\n", p->nom);
	printf("age : %d\n", p->age);
	printf("connaissance : %s\n", p->connait == NULL ? "personne" : p->connait->nom);
	printf("----------------------\n");
}


int main()
{
	pers* Alain = ConstructPers("Alain", 25, NULL);
	pers* Isabelle = ConstructPers("Isabelle", 30, Alain);
	pers* Solange = ConstructPers("Solange", 12, Isabelle);
	pers* Arthur = ConstructPers("Arthur", 80, Solange);
	pers* Melanie = ConstructPers("Melanie", 43, Arthur);
	pers* cour;

	cour = Melanie;
	while (cour != NULL) {
		AffichePers(cour);
		cour = cour->connait;
	}

	// libération mémoire
	cour = Melanie;
	while (cour != NULL) {
		pers* p = cour;
		cour = cour->connait;
		free(p);
	}
	return 0;
}
*/



