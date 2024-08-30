/*********************************************************************************
Exercice 20 :
base du d�mineur
Le jeu consiste � retirer des mines cach�es et dispos�es sur un terrain. Le terrain
est une grille. Le joueur clique sur une case, s'il y a une mine il a perdu. S'il y
a une mine ou plusieurs mines adjacentes, le nombre de ces mines est indiqu� dans
la case cliqu�e. S'il n'y a pas de mine, le programme d�couvre automatiquement toute
la zone ceintur�e de cases adjacentes � des mines. Chacune de ces cases indique le
nombre des cases min�es voisines. En se servant de ces indications, le joueur doit
d�duire o� sont les mines. Il a la possibilit� de d�poser des drapeaux pour neutraliser
une case...
�		L'objectif est de mettre en place une base pour le jeu.
�		Le terrain est une matrice de nombres. Les cases non min�es sont � 0 ou indiquent
		combien il y a de mines � proximit�, les autres � une valeur MINE.
�		�crire une fonction qui initialise le terrain avec des mines ainsi que toutes les
		positions adjacentes.
�		�crire une fonction de recherche appel�e lorsque le joueur clique sur le terrain
		(dans une case de la matrice sous-jacente).
*********************************************************************************/
/* // Version graphique sous allegro 5

Pour l'installation d'allegro (une connexion internet est n�cessaire):
- dans la solution selectionnez le projet
- cliquez droit dessus 
- dans le menu s�lectionnez "Gr�rer les packages NuGet..." 
- dans la page NuGet cliquez en haut � gauche sur "Parcourir" et entrez
  allegro 5 dans la barre de recherche juste en dessous
- dans la liste s�lectionner Allegro (logo crocodile) par allegro developers Allegro 5
- dans la partie � droite de la page cliquez sur installer
En principe allegro s'installe pour le projet avec ses d�pendances sans probl�me.

ATTENTION
Ce n'est pas fini il faut maintenant indiquer quels modules d'allegro le programme utilise.
Pour ce faire :
- dans la solution selectionnez le projet
- cliquez droit dessus
- dans le menu s�lectionnez "propri�t�s" tout en bas. 
- ouvrez "Allegro 5" puis en dessous s�lectionnez "Add-ons"
- Dans le coin hautgauche de la fen�tre qui s'ouvre � droite s�lectionnez "toute configurations"
- Ensuite sur la droite en dessous mettez "primitive addon", "Dialog addon", TrueType Font addon 
  et Font Addon sur "oui" (il suffit de cliquer en face et une boite de choix apparait).
- pour finir cliquez sur "appliquer"

N'oubliez pas cette op�ration. Plus tard si vous voulez ajouter des images il faudra faire de 
m�me avec image add-on. Dans le doute on peut tout mettre sur "oui"

Remarque :
En l'�tat le projet est configur� pour �tre utilis� avec les dll corresondantes. Ces dll doivent 
�tre plac�es avec l'ex�cutable, au m�me niveau dans le m�me folder. C'est r�alis� automatiquement 
par visual studio.

Pour une version release il peut �tre pr�f�rable de ne plus avoir ces dll. Dans ce cas revenez � 
la fen�tre propri�t�s :
- en haut � gauche dans "Configuration" s�lectionnez "debug" ou "active debug" si le mode courant.
- en dessous ouvrez l'onlet "allegro 5" sur la gauche et en dessous de "Add-ons"
  s�lectionnez "Libary Type". Dans la page � droite s�lectionnez "Dynamic debug-dynamic runtime"
- en haut � gauche dans "Configuration" s�lectionnez maintenant "release".
  Dans l'onlet "allegro 5" sur la gauche s�lectionnez "Libary Type" et sur la droite 
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
#define SCREENX		1366	// r�solution du display
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
	Cr�er un terrain parsem� de mines
**************************************************/
void InitMines(int nbmines)
{
	int x, y;

	//initialise la matrice avec des valeurs de 0
	memset(MAT, VIDE, sizeof(int)*TX*TY);

	// Le nombre total de mines ne peut pas d�passer la taille du tableau.
	// La densit� maximum est de une sur deux
	if (nbmines >= TX * TY)
		nbmines /= 2;

	// pose nb mines de fa�on al�atoire dans la matrice
	while (nbmines > 0) {
		x = rand() % TX;
		y = rand() % TY;
		if (MAT[y][x] != MINE) {
			MAT[y][x] = MINE;
			nbmines--;
		}
	}
	// faire appara�tre le relief des mines
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
	Voir le terrain complet (permet de contr�ler si
	les mines sont bien pos�es et si les positions
	adjacentes sont correctement initialis�es)
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
								"%d", MAT[yi][xi]);		// texte format� (style printf) � afficher
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
	(recherche d�clench�e par un clic gauche sur le terrain)
********************************************************/
int Cherche(int x, int y)
{
	int res = 0;
	//Position x, y � l'�cran
	int xe = DECALX + x * TCARREAU;
	int ye = DECALY + y * TCARREAU;
	// si on est dans la zone matrice
	if (x >= 0 && x < TX && y >= 0 && y < TY) {

		switch (MAT[y][x]) {
			// si rien :
			// mettre � VU (pour indiquer passage), colorer la case puis
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

			// d�j� pass� (ou nombre d�couvert), ou drapeau, ou drapeau sur mine = 
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
	Poser un drapeau (d�clencher par un clic droit)
********************************************************/
void Drapeau(int x, int y)
{
	if (x >= 0 && x <= TX && y >= 0 && y < TY) {
		int xe = DECALX + x * TCARREAU;
		int ye = DECALY + y * TCARREAU;

		// si la position n'est pas d�couverte (vu) 
		// ce peut �tre une mine
		if (MAT[y][x] >= 0 && MAT[y][x] <= MINE) {
			MAT[y][x] += DRAPEAU;
			al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BRIGHT_CYAN);
		}
		// si un drapeau a d�j� �t� pos�
		else if (MAT[y][x] > MINE) {
			MAT[y][x] -= DRAPEAU;
			al_draw_filled_rectangle(xe + 1, ye + 1, xe + TCARREAU - 1, ye + TCARREAU - 1, BLACK);

		}
	}
}
/**************************************************
	Initialisation allegro, r�glage �cran
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
	// Si vous voulez r�cup�rer la plus grande r�solution possible de l'ordinateur
	ALLEGRO_DISPLAY_MODE mode;
	int nb = al_get_num_display_modes();
	al_get_display_mode(nb - 1, &mode);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);  // si plein �cran
	DISPLAY = al_create_display(mode.width, mode.height);
	*/

	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);  // si plein �cran
	DISPLAY = al_create_display(SCREENX, SCREENY);
	if (!DISPLAY)
		Erreur("display");

	// colore la zone fen�tre/�cran en rouge
	al_clear_to_color(DARK_RED);

	// pour avoir du texte
	al_init_font_addon();
	if (!al_init_ttf_addon())
		Erreur("al_init_ttf_addon");

	ARIAL12 = al_load_font("arial.ttf", 18, 0);
	if (!ARIAL12)
		Erreur("al_load_font");

	// initialiser le g�n�rateur de nombres al�atoires
	srand(time(NULL));
}
/**************************************************
	Controler les clics souris
Les fonctions allegro que nous utilisons sont tellement rapides
que le temps d'appuyer sur bouton de souris correspond � plusieurs 
tours de la boucle principale ce qui a des cons�quences n�fastes 
pour l'affichage des drapeaux (clignotements).
L'id�e de la fonction ci-dessous est de controler le nombre de 
r�p�tions des clics.
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