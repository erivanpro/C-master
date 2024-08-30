/*********************************************************************************
Exercice 20 :
base du démineur
Le jeu consiste à retirer des mines cachées et disposées sur un terrain. Le terrain
est une grille. Le joueur clique sur une case, s'il y a une mine il a perdu. S'il y
a une mine ou plusieurs mines adjacentes, le nombre de ces mines est indiqué dans
la case cliquée. S'il n'y a pas de mine, le programme découvre automatiquement toute
la zone ceinturée de cases adjacentes à des mines. Chacune de ces cases indique le
nombre des cases minées voisines. En se servant de ces indications, le joueur doit
déduire où sont les mines. Il a la possibilité de déposer des drapeaux pour neutraliser
une case...
–		L'objectif est de mettre en place une base pour le jeu.
–		Le terrain est une matrice de nombres. Les cases non minées sont à 0 ou indiquent
		combien il y a de mines à proximité, les autres à une valeur MINE.
–		Écrire une fonction qui initialise le terrain avec des mines ainsi que toutes les
		positions adjacentes.
–		Écrire une fonction de recherche appelée lorsque le joueur clique sur le terrain
		(dans une case de la matrice sous-jacente).
*********************************************************************************/
/* // Version graphique sous allegro 5

Pour l'installation d'allegro (une connexion internet est nécessaire):
- dans la solution selectionnez le projet
- cliquez droit dessus 
- dans le menu sélectionnez "Grérer les packages NuGet..." 
- dans la page NuGet cliquez en haut à gauche sur "Parcourir" et entrez
  allegro 5 dans la barre de recherche juste en dessous
- dans la liste sélectionner Allegro (logo crocodile) par allegro developers Allegro 5
- dans la partie à droite de la page cliquez sur installer
En principe allegro s'installe pour le projet avec ses dépendances sans problème.

ATTENTION
Ce n'est pas fini il faut maintenant indiquer quels modules d'allegro le programme utilise.
Pour ce faire :
- dans la solution selectionnez le projet
- cliquez droit dessus
- dans le menu sélectionnez "propriétés" tout en bas. 
- ouvrez "Allegro 5" puis en dessous sélectionnez "Add-ons"
- Dans le coin hautgauche de la fenêtre qui s'ouvre à droite sélectionnez "toute configurations"
- Ensuite sur la droite en dessous mettez "primitive addon", "Dialog addon", TrueType Font addon 
  et Font Addon sur "oui" (il suffit de cliquer en face et une boite de choix apparait).
- pour finir cliquez sur "appliquer"

N'oubliez pas cette opération. Plus tard si vous voulez ajouter des images il faudra faire de 
même avec image add-on. Dans le doute on peut tout mettre sur "oui"

Remarque :
En l'état le projet est configuré pour être utilisé avec les dll corresondantes. Ces dll doivent 
être placées avec l'exécutable, au même niveau dans le même folder. C'est réalisé automatiquement 
par visual studio.

Pour une version release il peut être préférable de ne plus avoir ces dll. Dans ce cas revenez à 
la fenêtre propriétés :
- en haut à gauche dans "Configuration" sélectionnez "debug" ou "active debug" si le mode courant.
- en dessous ouvrez l'onlet "allegro 5" sur la gauche et en dessous de "Add-ons"
  sélectionnez "Libary Type". Dans la page à droite sélectionnez "Dynamic debug-dynamic runtime"
- en haut à gauche dans "Configuration" sélectionnez maintenant "release".
  Dans l'onlet "allegro 5" sur la gauche sélectionnez "Libary Type" et sur la droite 
  "Static Monolith Release".

- poour finir cliquez sur "appliquer"
*/
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// le jeu 
#define SCREENX		1366	// résolution du display
#define SCREENY		768
#define TX			25		// matrice du jeu
#define TY			13
#define TCARREAU	50
#define DECALX		((SCREENX-TX*TCARREAU)/2)
#define DECALY		((SCREENY-TY*TCARREAU)/2)

#define VIDE	0
#define VU		-1
#define MINE	9
#define DRAPEAU	10
enum { BOUTONGAUCHE = 1, BOUTONDROITE, BOUTONCENTRE = 4 };

// les couleurs de la console (nous ne les utiliserons pas toutes)
#define BLACK 			al_map_rgb(0, 0, 0) 	
#define DARK_BLUE 		al_map_rgb(0, 55, 218)	   // 0, 0, 128
#define DARK_GREEN 		al_map_rgb(19, 161, 14)		//0, 128, 0 	
#define DARK_CYAN 		al_map_rgb(58, 150, 221)	//0, 128, 128
#define DARK_RED 		al_map_rgb(197, 15, 31)		// 128, 0, 0 
#define DARK_MAGENTA 	al_map_rgb(136, 23, 152)	//128, 0, 128
#define DARK_YELLOW 	al_map_rgb(193, 156, 0)		//128, 128, 0 	
#define DARK_WHITE 		al_map_rgb(204, 204, 204)	//192, 192, 192 	
#define BRIGHT_BLACK 	al_map_rgb(118, 118, 118)	//128, 128, 128 	
#define BRIGHT_BLUE 	al_map_rgb(59, 120, 255)	//0, 0, 255 	
#define BRIGHT_GREEN 	al_map_rgb(22, 198, 12)		//0, 255, 0 	
#define BRIGHT_CYAN 	al_map_rgb(97, 214, 214)	//0, 255, 255 	
#define BRIGHT_RED 		al_map_rgb(231, 72, 86)		//255, 0, 0 	
#define BRIGHT_MAGENTA 	al_map_rgb(180, 0, 158)		//255, 0, 255 	
#define BRIGHT_YELLOW 	al_map_rgb(249, 241, 165)	//255, 255, 0 	
#define WHITE 			al_map_rgb(255, 255, 255)


// le terrain du jeu
ALLEGRO_DISPLAY*DISPLAY;
ALLEGRO_FONT*ARIAL12;
int MAT[TY][TX] = { VIDE };

void InitMines(int nbmines);
void IncrementVoisins(int x, int y);
void AfficheTerrain(void);
void AfficheGrille(void);
void AfficheMines();
int Cherche(int x, int y);
void Drapeau(int x, int y);

void InitAllegroEcran(void);
_Bool BoutonPress(ALLEGRO_MOUSE_STATE*mouse, int btn, int repeat);
void Erreur(const char*txt);

int main()
{
	InitAllegroEcran();
	InitMines(TX*TY/10); 
	AfficheGrille();
	
	int fin = 0, trouve = 0;
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_MOUSE_STATE mouse;

	while (!fin) {
		al_get_keyboard_state(&key);
		al_get_mouse_state(&mouse);

		if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
			fin = 1;
		else if (al_key_down(&key, ALLEGRO_KEY_ENTER)) {
			al_clear_to_color(BLACK);
			InitMines(TX*TY / 10);
			AfficheGrille();
			trouve = 0;
		}
		else if ( BoutonPress( &mouse,BOUTONGAUCHE, 1) && !trouve ){
			//position x,y dans la matrice
			int x = (mouse.x - DECALX) / TCARREAU;
			int y = (mouse.y - DECALY) / TCARREAU;
			trouve = Cherche(x, y);
		}
		else if (BoutonPress(&mouse, BOUTONDROITE, 1)) {
			int x = (mouse.x - DECALX) / TCARREAU;
			int y = (mouse.y - DECALY) / TCARREAU;
			Drapeau(x, y);
		}
		al_flip_display();
	}
	
	al_destroy_display(DISPLAY);
	al_destroy_font(ARIAL12);

	return 0;
}
/**************************************************
	Créer un terrain parsemé de mines
**************************************************/
void InitMines(int nbmines)
{
	int x, y;

	//initialise la matrice avec des valeurs de 0
	memset(MAT, VIDE, sizeof(int)*TX*TY);

	// Le nombre total de mines ne peut pas dépasser la taille du tableau.
	// La densité maximum est de une sur deux
	if (nbmines >= TX * TY)
		nbmines /= 2;

	// pose nb mines de façon aléatoire dans la matrice
	while (nbmines > 0) {
		x = rand() % TX;
		y = rand() % TY;
		if (MAT[y][x] != MINE) {
			MAT[y][x] = MINE;
			nbmines--;
		}
	}
	// faire apparaître le relief des mines
	for (y = 0; y < TY; y++)
		for (x = 0; x < TX; x++)
			if (MAT[y][x] == MINE)
				IncrementVoisins(x, y);
}
/*******************************************************
	Comptabiliser les mines dans les positions voisines
********************************************************/
void IncrementVoisins(int x, int y)
{
	if (x - 1 >= 0) {
		if (MAT[y][x - 1] != MINE)
			MAT[y][x - 1]++;
		if (y - 1 >= 0)
			if (MAT[y - 1][x - 1] != MINE)
				MAT[y - 1][x - 1]++;
		if (y + 1 < TY)
			if (MAT[y + 1][x - 1] != MINE)
				MAT[y + 1][x - 1]++;
	}
	if (x + 1 < TX) {
		if (MAT[y][x + 1] != MINE)
			MAT[y][x + 1]++;
		if (y - 1 >= 0)
			if (MAT[y - 1][x + 1] != MINE)
				MAT[y - 1][x + 1]++;
		if (y + 1 < TY)
			if (MAT[y + 1][x + 1] != MINE)
				MAT[y + 1][x + 1]++;
	}
	if (y - 1 >= 0)
		if (MAT[y - 1][x] != MINE)
			MAT[y - 1][x]++;
	if (y + 1 < TY)
		if (MAT[y + 1][x] != MINE)
			MAT[y + 1][x]++;
}
/*******************************************************
	Voir le terrain complet (permet de contrôler si
	les mines sont bien posées et si les positions
	adjacentes sont correctement initialisées)
********************************************************/
void AfficheTerrain()
{
	AfficheGrille();
	for (int yi = 0; yi < TY; yi++) {
		for (int xi = 0; xi < TX; xi++) {

			int x = DECALX + xi * TCARREAU;
			int y = DECALY + yi * TCARREAU;
			ALLEGRO_COLOR color = { 0 };

			if (MAT[yi][xi] == MINE)
				al_draw_filled_rectangle(x + 1, y + 1, x + TCARREAU - 1, y + TCARREAU - 1, BRIGHT_RED);
			else if (MAT[yi][xi] > 0 && MAT[yi][xi] < MINE) {
				al_draw_filled_rectangle(x + 1, y + 1, x + TCARREAU - 1, y + TCARREAU - 1, BRIGHT_YELLOW);
				al_draw_textf(	ARIAL12, 
								BLACK,					// police,couleur
								x + TCARREAU / 2, y + TCARREAU / 4, //position
								ALLEGRO_ALIGN_CENTER,	// type alignement
								"%d", MAT[yi][xi]);		// texte formaté (style printf) à afficher
			}
		}
	}
}
void AfficheGrille()
{
	al_draw_filled_rectangle(DECALX, DECALY, DECALX + TCARREAU * TX, DECALY + TCARREAU * TY, BLACK);
	for (int yi = 0; yi < TY; yi++)
		for (int xi = 0; xi < TX; xi++) {
			int x = DECALX + xi * TCARREAU;
			int y = DECALY + yi * TCARREAU;
			al_draw_rectangle(x, y, x + TCARREAU, y + TCARREAU, BRIGHT_BLACK, 2);
		}
}
/*******************************************************
	Afficher uniquement les mines si le joueur perd
********************************************************/
void AfficheMines()
{
	for (int y = 0; y < TY; y++) {
		for (int x = 0; x < TX; x++) {
			int xe = DECALX + x * TCARREAU;
			int ye = DECALY + y * TCARREAU;
			if (MAT[y][x] == MINE) 
				al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BRIGHT_RED);
			else if (MAT[y][x] == MINE+DRAPEAU)
				al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BRIGHT_MAGENTA);
		}
	}
}
/*******************************************************
	Chercher les mines
	(recherche déclenchée par un clic gauche sur le terrain)
********************************************************/
int Cherche(int x, int y)
{
	int res = 0;
	//Position x, y à l'écran
	int xe = DECALX + x * TCARREAU;
	int ye = DECALY + y * TCARREAU;
	// si on est dans la zone matrice
	if (x >= 0 && x < TX && y >= 0 && y < TY) {

		switch (MAT[y][x]) {
			// si rien :
			// mettre à VU (pour indiquer passage), colorer la case puis
			// lancer recherches dans toutes les directions
		case VIDE:
			MAT[y][x] = VU;

			al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BRIGHT_GREEN);
			Cherche(x + 1, y);
			Cherche(x + 1, y - 1);
			Cherche(x, y - 1);
			Cherche(x - 1, y - 1);
			Cherche(x - 1, y);
			Cherche(x - 1, y + 1);
			Cherche(x, y + 1);
			Cherche(x + 1, y + 1);
			break;

			// déjà passé (ou nombre découvert), ou drapeau, ou drapeau sur mine = 
			// ne rien faire
		case VU:
			// case DRAPEAU :
			// case DRAPEAU+MINE :   
			break;

			// au cas ou clic sur une mine afficher toutes les mines
		case MINE:
			res = 1;
			AfficheMines();
			break;

			// autre cas, si pas de drapeau afficher le nombre et condamner pour 
			// drapeaux
		default:
			if (MAT[y][x] < MINE) {
				al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BRIGHT_YELLOW);
				al_draw_textf(ARIAL12, BLACK, xe + TCARREAU / 2, ye + TCARREAU / 4, ALLEGRO_ALIGN_CENTER, "%d", MAT[y][x]);
				MAT[y][x] = -1;
			}
			break;
		}
	}
	return res;
}
/*******************************************************
	Poser un drapeau (déclencher par un clic droit)
********************************************************/
void Drapeau(int x, int y)
{
	if (x >= 0 && x <= TX && y >= 0 && y < TY) {
		int xe = DECALX + x * TCARREAU;
		int ye = DECALY + y * TCARREAU;

		// si la position n'est pas découverte (vu) 
		// ce peut être une mine
		if (MAT[y][x] >= 0 && MAT[y][x] <= MINE) {
			MAT[y][x] += DRAPEAU;
			al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BRIGHT_CYAN);
		}
		// si un drapeau a déjà été posé
		else if (MAT[y][x] > MINE) {
			MAT[y][x] -= DRAPEAU;
			al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BLACK);

		}
	}
}
/**************************************************
	Initialisation allegro, réglage écran
**************************************************/
void InitAllegroEcran()
{
	if (!al_init())
		Erreur("al_init()");
	if (!al_install_keyboard())
		Erreur("al_install_keyboard()");
	if (!al_install_mouse())
		Erreur("al_install_mouse()");
	if (!al_init_primitives_addon())
		Erreur("al_init_primitives_addon()");

	/*
	// Si vous voulez récupérer la plus grande résolution possible de l'ordinateur
	ALLEGRO_DISPLAY_MODE mode;
	int nb = al_get_num_display_modes();
	al_get_display_mode(nb - 1, &mode);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);  // si plein écran
	DISPLAY = al_create_display(mode.width, mode.height);
	*/

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);  // si plein écran
	DISPLAY = al_create_display(SCREENX, SCREENY);
	if (!DISPLAY)
		Erreur("display");

	// colore la zone fenêtre/écran en rouge
	al_clear_to_color(DARK_RED);

	// pour avoir du texte
	al_init_font_addon();
	if (!al_init_ttf_addon())
		Erreur("al_init_ttf_addon");

	ARIAL12 = al_load_font("arial.ttf", 18, 0);
	if (!ARIAL12)
		Erreur("al_load_font");

	// initialiser le générateur de nombres aléatoires
	srand(time(NULL));
}
/**************************************************
	Controler les clics souris
Les fonctions allegro que nous utilisons sont tellement rapides
que le temps d'appuyer sur bouton de souris correspond à plusieurs 
tours de la boucle principale ce qui a des conséquences néfastes 
pour l'affichage des drapeaux (clignotements).
L'idée de la fonction ci-dessous est de controler le nombre de 
répétions des clics.
**************************************************/
_Bool BoutonPress(ALLEGRO_MOUSE_STATE*mouse, int btn, int repeat)
{
	_Bool res = false;

	static int*press = NULL;
	static int nbbtn;
	if (press == NULL) {
		nbbtn = al_get_mouse_num_buttons();
		press = (int*)calloc(nbbtn + 1, sizeof(int));
		memset(press, 0, sizeof(int)*nbbtn);
	}
	if (btn > nbbtn) {
		btn = nbbtn;
	}
	if (al_mouse_button_down(mouse, btn) && press[btn] < repeat) {
		press[btn]++;
		res = true;
	}
	else if (!al_mouse_button_down(mouse, btn))
		press[btn] = 0;
	return res;
}

/**************************************************
	si erreur
**************************************************/
void Erreur(const char*txt)
{
	FILE*f;
	fopen_s(&f, "erreur.txt", "w");
	fprintf_s(f, " erreur : %s\nligne : %d\nfile : %s\n", txt, __LINE__, __FILE__);
	fclose(f);
	exit(EXIT_FAILURE);
}
/*******************************************************
********************************************************/