/************************************************************
*                                                           *
*       CHAPITRE 5 : Les structures							*
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
*       1.    Structures					        *
*                                                   *
*****************************************************/

 // Disposer d'une structure dans un programme 1
/*
// utiliser un typedef
#include <stdio.h>
#include <stdlib.h>

typedef int toto; // création du type toto

int main()
{
	toto test = 80;
	printf("la variable test vaut : %d\n", test);

	system("PAUSE");
	return 0;
}
*/
//--------------------------------------------------
// Disposer d'une structure dans un programme 2
/*
#include <stdlib.h>
#include <time.h>
typedef struct {
	char type;     	    // type de l'ennemi (une lettre)
	float nuisance;   	// potentielle de nuisance
	float x, y, px, py;  	// position et déplacement
	int force;    	    // indicateur de force pour les combats
}Ennemi;

Ennemi init_ennemi(void)
{
	Ennemi e;
	// mettre code correspondant (voir bouger une entité)

	return e;
}

void affiche_ennemi(Ennemi e)
{
	// mettre code correspondant (voir bouger une entité)
}

int main()
{
	Ennemi E;
	srand(time(NULL));
	E = init_ennemi();
	affiche_ennemi(E);
	return 0;
}
*/

//--------------------------------------------------
//Initialiser une structure à la déclaration
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	float x, y;
}Coord;
typedef struct {
	const int tx;
	const int ty;
	Coord coord;
	int px, py;
	char lettre;
}Personnage;

// Valeurs par défaut
#define DEFAUT  { 50,100,1.5f,2.5f,rand()%100,rand()%100,'A' }

int main()
{
	srand(time(NULL));

	// initialisation de tous les champs (y compris structures
	// imbriquées)dans l'ordre
	Personnage p1={50,100,{1.5f,2.5f},rand()%100,rand()% 100,'A' };
	printf("%d-%d-%f-%f-%d-%d-%c\n",
	p1.tx, p1.ty, p1.coord.x, p1.coord.y, p1.px, p1.py, p1.lettre);

	// initialisation dans l'ordre, les éléments manquants sont
	// automatiquement mis à 0
	Personnage p2 = { 50,100 };
	printf("%d-%d-%f-%f-%d-%d-%c\n",
	p2.tx, p2.ty, p2.coord.x, p2.coord.y, p2.px, p2.py, p2.lettre);

	// pratique pour tout mettre à 0
	Personnage p3 = { 0 };
	printf("%d-%d-%f-%f-%d-%d-%c\n",
	p3.tx, p3.ty, p3.coord.x, p3.coord.y, p3.px, p3.py, p3.lettre);

	// initialisation avec sélection de champs (pas d'ordre à
	// respecter, les champs manquants sont mis à 0)
	Personnage p4 = {.tx = 50, .lettre = 'b', .coord.x = 50.0f };
	printf("%d-%d-%f-%f-%d-%d-%c\n",
	p4.tx,p4.ty,p4.coord.x, p4.coord.y, p4.px, p4.py, p4.lettre);

	// création d'une initialisation par défaut
	Personnage p5 = DEFAUT;
	printf("%d-%d-%f-%f-%d-%d-%c\n",
	p5.tx, p5.ty, p5.coord.x, p5.coord.y, p5.px, p5.py, p5.lettre);

	system("PAUSE");
	return 0;
}

*/

/****************************************************
*                                                   *
*       2.    Structures et fonctions               *
*                                                   *
*****************************************************/
//Retourner une structure
/*
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int x, y;
}Coord;

Coord ConstructPoint1()
{
	Coord t0;
	t0.x = rand() % 1024;
	t0.y = rand() % 768;
	return t0;
}

Coord ConstructPoint2(int x, int y)
{
	Coord t0;
	t0.x = x;
	t0.y = y;
	return t0;
}

int main()
{
	Coord pt1, pt2;

	pt1 = ConstructPoint1();
	pt2 = ConstructPoint2(40, 40);
	printf("pt1.x=%d, pt1.y=%d\n"
		"pt2.x=%d, pt2.y=%d\n", pt1.x, pt1.y, pt2.x, pt2.y);

	system("PAUSE");
	return 0;
}
*/
//--------------------------------------------------
//Structures en paramètre de fonction
/*
#include <stdio.h>

typedef struct {
	int x, y;
}Coord;

void modif(Coord pt)
{
	pt.x++;
	if (pt.x > 1000)
		pt.x = 0;

}

int main()
{
	Coord p = { 10,20 };
	printf("p.x=%d, p.y=%d\n", p.x, p.y);
	modif(p);
	printf("p.x=%d, p.y=%d\n", p.x, p.y);
	return 0;
}
*/


/****************************************************
*                                                   *
*       Expérimentations			                *
*                                                   *
*****************************************************/

/*
/*************************************************************
fourmi 1 : une fourmi mobile à l'écran.
J'ai conservé un style classique en C (sans majuscule pour
les noms de fonction ni-même pour le type fourmi)
*************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
// en global définition du type de la structure fourmi
typedef struct {
	float x, y; // la position de la fourmi
	float dx, dy; // le déplacement
	int color; // la couleur
	int lettre; // l'apparence
}fourmi;

// Limites de la zone de jeu
const int TX = 40;
const int TY = 20;

// les actions
fourmi	init		(void);
void	affiche		(fourmi f, int color);
fourmi	avance		(fourmi f);
int		top			(int*start, int dur);
void	gotoxy		(int x, int y);
void	textcolor	(int color);
/*************************************************************
ACTION
*************************************************************
int main()
{
	int start = 0;
	fourmi f;
	srand(time(NULL));
	f = init();
	while (!_kbhit()){
		if (top(&start, 75)){
			affiche(f, 0); // effacer
			f = avance(f); // changer la position
			affiche(f, f.color); // réafficher
		}
	}
	return 0;
}
/*************************************************************
INITIALISATION
*************************************************************
fourmi init()
{
	fourmi f;
	f.x = rand() % TX;
	f.y = rand() % TY;
	f.dx = ((float)rand() / RAND_MAX) * 4 - 2;
	f.dy = ((float)rand() / RAND_MAX) * 4 - 2;
	f.lettre = 'A' + rand() % 26;
	f.color = 1 + rand() % 255;
	return f;
}
/*************************************************************
AFFICHAGE
*************************************************************
void affiche(fourmi f, int color)
{
	gotoxy(f.x, f.y);
	textcolor(color);
	putchar(f.lettre);
}
/*************************************************************
MOUVEMENT
*************************************************************
fourmi avance(fourmi f)
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

/********************************************************
						VOITURE 2
********************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// taille de la zone de jeu
#define TX  80
#define TY  24

// Les quatre directions
enum { NORD, EST, SUD, OUEST };

// Pour un circuit :
//  - 6 traits max
//  - un trait = une direction et un nombre de pas
//  - un nombre de traits
//  - un nombre de tours

// pour avoir un circuit : 
typedef struct {
    int d1, p1, d2, p2, d3, p3, d4, p4, d5, p5, d6, p6; //6 traits 
    int nbtrait;  // nombre de traits dans le circuit 
    int nbtour;   // nombre de tours à faire pour une course 
}circuit;

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
typedef struct {
    int x, y, dir, pas, idtrait, tour, vit, tmps;
    int lettre;  // lettre correspondante 
    int color1, color2; // deux couleurs 
}voiture;

// les déclarations des fonctions 
circuit  create_circuit1(void);
voiture  create_voiture(int startx, int starty, int c1, int c2,
    int l);
voiture  bouge(voiture v, circuit c);
int      run(voiture v1, voiture v2, voiture v3,
    voiture v4, circuit c);
voiture  select_trait(voiture v, circuit c);
voiture  avancer(voiture v);
void     afficher(voiture v, int color);
int      top(voiture v);
void     gotoxy(int x, int y);
void     textcolor(int color);
void     pause(int x, int y);
/********************************************************
ACTION
********************************************************
int main()
{
    circuit c;
    voiture v1, v2, v3, v4;

    srand(time(NULL));
    c = create_circuit1();
    v1 = create_voiture(2, 2, 0, 10, '1');
    v2 = create_voiture(3, 3, 1, 11, '2');
    v3 = create_voiture(4, 4, 2, 12, '3');
    v4 = create_voiture(5, 5, 3, 13, '4');

    while (run(v1, v2, v3, v4, c)) {

        /* est généralisé et remplacé avec la fonction bouge()
        if(top(v1)){
        v1.tmps=clock();
        if(v1.pas==0)
        v1=select_trait(v1,c);
        v1=avancer(v1);
        }
        if(top(v2)){
        v2.tmps=clock();
        if(v2.pas==0)
        v2=select_trait(v2,c);
        }
        v3.tmps=clock();
        if(v3.pas==0)
        v3=select_trait(v3,c);
        v3=avancer(v3);
        }
        if(top(v4)){
        v4.tmps=clock();
        if(v4.pas==0)
        v4=select_trait(v4,c);
        v4=avancer(v4);
        }*
        // un appel de la fonction bouge() par voiture 
        v1 = bouge(v1, c);
        v2 = bouge(v2, c);
        v3 = bouge(v3, c);
        v4 = bouge(v4, c);
    }
    pause(0, TY);
    return 0;
}
/********************************************************
CRÉATION DU CIRCUIT
********************************************************
//Un seul circuit. C'est un carré de 10 sur 10, deux tours
//prévus. Initialisation des variables circuit en conséquence.
//Initialisation de la voiture
circuit create_circuit1()
{
    circuit c;
    // définition du circuit 
    c.d1 = EST; // trait 1 
    c.p1 = 10;
    c.d2 = SUD;
    c.p2 = 10;
    c.d3 = OUEST;
    c.p3 = 10;
    c.d4 = NORD;
    c.p4 = 10;
    c.nbtrait = 4;
    c.nbtour = 2;

    return c;
}
/********************************************************
CRÉATION VOITURE
********************************************************
voiture create_voiture(int startx, int starty, int c1,
    int c2, int l)
{
    voiture v;

    v.x = startx;
    v.y = starty;
    v.pas = 0;
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
********************************************************
//contrôle de la fin de la course. La course continue tant
//qu'aucune voiture n'a fini et s'arrête dés qu'une voiture
//a fini
int run(voiture v1, voiture v2, voiture v3, voiture v4,
    circuit c)
{
    return (v1.tour < c.nbtour&& v2.tour < c.nbtour&&
        v3.tour < c.nbtour&& v4.tour < c.nbtour);
}
// topage voitures 
int top(voiture v)
{
    return (clock() > v.tmps + v.vit);
}

voiture bouge(voiture v, circuit c)
{
    if (top(v)) {
        v.tmps = clock();
        if (v.pas == 0)
            v = select_trait(v, c);
        v = avancer(v);
    }
    return v;
}
//sélectionner un trait à parcourir
voiture select_trait(voiture v, circuit c)
{
    // contrôler si un tour a été effectué 
    if (v.idtrait == c.nbtrait) {
        v.tour++;
        v.idtrait = 0;
    }

    // changer la vitesse pour chaque trait 
    v.vit = 150 + rand() % 150;

    // sélection du trait 
    switch (v.idtrait) {
    case 0:
        v.dir = c.d1;
        v.pas = c.p1;
        break;
    case 1:
        v.dir = c.d2;
        v.pas = c.p2;
        break;
    case 2:
        v.dir = c.d3;
        v.pas = c.p3;
        break;
    case 3:
        v.dir = c.d4;
        v.pas = c.p4;
        break;
    case 4:
        v.dir = c.d5;
        v.pas = c.p5;
        break;
    case 5:
        v.dir = c.d6;
        v.pas = c.p6;
        break;
    }

    // préparer pour le tour suivant 
    v.idtrait++;

    return v;
}
//parcourir le trait courant
voiture avancer(voiture v)
{
    if (v.pas > 0) {
        v.pas--; // un pas de moins 

        // effacer 
        afficher(v, v.color1);

        // avancer selon direction 
        switch (v.dir) {
        case NORD:     v.y--;  break;
        case EST:      v.x++;  break;
        case SUD:      v.y++;  break;
        case OUEST:    v.x--;  break;
        }

        // réafficher 
        afficher(v, v.color2);
    }
    return v;
}
//afficher une voiture de la couleur color
void afficher(voiture v, int color)
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
/********************************************************
********************************************************/

