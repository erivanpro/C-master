/********************************************************
VOITURE 2
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// taille de la zone de jeu
#define TX 80
#define TY 24

// Les quatre directions
enum{ NORD, EST, SUD, OUEST };
/* Pour un circuit :
- 6 traits max
- un trait = une direction et un nombre de pas
- un nombre de traits
- un nombre de tours
*/
// pour avoir un circuit :
typedef struct {
	int d1, p1, d2, p2, d3, p3, d4, p4, d5, p5, d6, p6; //6 traits
	int nbtrait; // nombre de traits dans le circuit
	int nbtour; // nombre de tours à faire pour une course
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
*/
typedef struct {
	int x, y, dir, pas, idtrait, tour, vit, tmps;
	int lettre; // lettre correspondante
	int color1, color2; // deux couleurs
}voiture;

// les déclarations des fonctions
circuit create_circuit1		(void);
voiture create_voiture		(int startx, int starty, int c1, int c2,int l);
voiture bouge				(voiture v, circuit c);
int		run					(voiture v1, voiture v2, voiture v3,voiture v4, circuit c);
voiture select_trait		(voiture v, circuit c);
voiture avancer				(voiture v);
void	afficher			(voiture v, int color);
int		top					(voiture v);
void	gotoxy				(int x, int y);
void	textcolor			(int color);
void	pause				(int x, int y);
/********************************************************
ACTION
********************************************************/
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
	while (run(v1, v2, v3, v4, c)){
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
		}*/
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
********************************************************/
/*
Un seul circuit. C'est un carré de 10 sur 10, deux tours
prévus. Initialisation des variables circuit en conséquence.
Initialisation de la voiture
*/
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
********************************************************/
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
********************************************************/
/*
contrôle de la fin de la course. La course continue tant
qu'aucune voiture n'a fini et s'arrête dés qu'une voiture
a fini
*/
int run(voiture v1, voiture v2, voiture v3, voiture v4,
	circuit c)
{
	return (v1.tour<c.nbtour && v2.tour<c.nbtour &&
		v3.tour<c.nbtour && v4.tour<c.nbtour);
}
// topage voitures
int top(voiture v)
{
	return (clock() > v.tmps + v.vit);
}
/*
*/
voiture bouge(voiture v, circuit c)
{
	if (top(v)){
		v.tmps = clock();
		if (v.pas == 0)
			v = select_trait(v, c);
		v = avancer(v);
	}
	return v;
}
/*
sélectionner un trait à parcourir
*/
voiture select_trait(voiture v, circuit c)
{
	// contrôler si un tour a été effectué
	if (v.idtrait == c.nbtrait){
		v.tour++;
		v.idtrait = 0;
	}
	// changer la vitesse pour chaque trait
	v.vit = 150 + rand() % 150;
	// sélection du trait
	switch (v.idtrait){
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
/*
parcourir le trait courant
*/
voiture avancer(voiture v)
{
	if (v.pas>0){
		v.pas--; // un pas de moins
		// effacer
		afficher(v, v.color1);
		// avancer selon direction
		switch (v.dir){
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
*/
void afficher(voiture v, int color)
{
	gotoxy(v.x, v.y);
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