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


// ATTENTION 
// DEPUIS LA VERSION 1809 DE WINDOWS LA RECUPERATION DE SOURIS NE FONCTIONNE PLUS.
// ET CETTE VERSION NE MARCHE PLUS : VOIR LA VERSION ALLEGRO.



// Voici une base de jeu. Le score n'est pas comptabilis�. Le terrain est un peu
// vaste et il faudrait le sc�nariser, c'est � dire cr�er un d�cor. Pour ce faire
// utiliser une seconde matrice "decor" qui servirait � l'affichage et aussi �
// contraindre le terrain MAT.

//Pour obtenir des cases plus grosses, le mieux serait d'ajouter � la biblioth�que 
// GraphCons une structure pour simuler des bitmaps et des sprites � moins, bien sur, 
// de basculer sur un environnement graphique comme Allegro 4, Allegro 5 ou SFML.
#include "GraphCons.h"

// zone de jeu
#define TX		150
#define TY		40
#define VIDE	0
#define VU		-1
#define MINE	9
#define DRAPEAU	10
enum { BOUTONGAUCHE = 1, BOUTONDROITE, BOUTONCENTRE = 4 };

int DECALX = 0;		// pour d�caler l'affichage 
int DECALY = 0;		// dans la console

// le terrain
int MAT[TY][TX] = { VIDE };
void InitMines(int nbmines);
void IncrementVoisins(int x, int y);
void MemAfficheTerrain(int posx, int posy);
void AfficheMines(int posx, int posy);
int Cherche(int x, int y);
void Drapeau(int x, int y);

int main()
{
	srand(time(NULL));
	if (!G_PleinEcran())
		if (!G_ConsResizeMax())
			printf("plein ecran impossible\n");
	
	G_ConsClearTo(DARK_RED, INVISIBLE, ' ');
	G_ConsCursor(FALSE);

	DECALX = (G_ConsTX() - TX) / 2;
	DECALY = (G_ConsTY() - TY) / 2;

	G_Rect(DECALX - 1, DECALY - 1, TX + DECALX + 1, TY + DECALY + 1, ' ', WHITE, WHITE);
	G_FillRect(DECALX, DECALY, TX + DECALX, TY + DECALY, ' ', BLACK, BLACK);
	InitMines(500);

	// pour voir tout
	//MemAfficheTerrain(DECALX, DECALY);
	
	int trouve = 0;
	while (1) {
		G_PollEvent();

		// if exclusif car G_PollEvent g�re un �v�nement � la fois

		if (G_KeyDown(VK_ESCAPE))
			break;
		else if (G_KeyDown(VK_RETURN)) {
			G_ConsClearTo(BLACK, BLACK, ' ');
			InitMines(500);
			trouve = 0;
		}
		else if (G_MouseClic(BOUTONGAUCHE) && ! trouve) {
			int x = G_MouseX() - DECALX;
			int y = G_MouseY() - DECALY;
			trouve = Cherche(x, y);		
		}
		else if (G_MouseClic(BOUTONDROITE)) {
			int x = G_MouseX() - DECALX;
			int y = G_MouseY() - DECALY;
			Drapeau(x, y);
		}
	} 
	return 0;
}
// TODO :
/**************************************************
	Cr�er un terrain parsem� de mines
**************************************************/
void InitMines(int nbmines)
{
	int x, y;

	//initialise la matrice avec des valeurs de 0
	memset(MAT, VIDE, sizeof(int)*TX*TY);

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
void IncrementVoisins( int x, int y)
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
void MemAfficheTerrain(int posx, int posy)
{
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*TX*TY);
	for (int y = 0; y < TY; y++) {
		for (int x = 0; x < TX; x++) {

			WORD color = 0;
			// les couleurs s�lectionn�es sont pour le fond
			// les lettres �ventuelles sont en noir.
			dat[y*TX + x].Char.AsciiChar = ' ';
			if (MAT[y][x] == 0) { // noir
				color = DARK_BLUE;
			}
			else if (MAT[y][x] < MINE) {
				dat[y*TX + x].Char.AsciiChar = '0' + MAT[y][x];
				color = WHITE;  
			}
			else if (MAT[y][x] == MINE) 
				color = BRIGHT_RED;
			
			dat[y*TX + x].Attributes = color << 4;
		}
	}
	SHORT left = 0, top = 0, right = TX, bottom = TY;
	SMALL_RECT src = { left,top,right,bottom };

	left = posx, top = posy, right = TX + posx, bottom = TY + posy;
	SMALL_RECT dest = { left,top,right,bottom };
	G_Blit(dat, &src, &dest);
	free(dat);
}
/*******************************************************
	Chercher les mines 
	(recherche d�clench�e par un clic gauche sur le terrain)
********************************************************/
int Cherche(int x, int y)
{
	int res = 0;
	// si on est dans la zone matrice
	if (x >= 0 && x < TX && y >= 0 && y < TY) {
		
		switch (MAT[y][x]) {
		// si rien :
		// mettre � VU (pour indiquer passage), colorer la case puis
		// lancer recherches dans toutes les directions
		case VIDE:
			MAT[y][x] = VU;
			
			G_DrawChar(x + DECALX, y + DECALY, ' ', DARK_GREEN, BLACK);
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
			AfficheMines(x, y);
			break;

		// autre cas, si pas de drapeau afficher le nombre et condamner pour 
		// drapeaux
		default:
			if (MAT[y][x] < MINE) {
				G_DrawChar(x + DECALX, y + DECALY, '0' + MAT[y][x], BRIGHT_YELLOW, BLACK);
				MAT[y][x] = -1;
			}
			break;
		}
	}
	return res;
}
// Afficher toutes les mines
void AfficheMines(int posx, int posy)
{
	for(int y = 0; y < TY; y++)
		for(int x = 0; x < TX; x++)
			if(MAT[y][x]==MINE)
				G_DrawChar(x + DECALX, y + DECALY, ' ', BRIGHT_RED, BLACK);
}
/*******************************************************
	Poser un drapeau (d�clencher par un clic droit)
***************************
*****************************/
void Drapeau(int x, int y)
{
	if (x >= 0 && x <= TX && y >= 0 && y < TY) {
		// si la position n'est pas d�couverte (vu) 
		// ce peut �tre une mine
		if (MAT[y][x] >= 0 && MAT[y][x] <= MINE) {
			MAT[y][x] += DRAPEAU;
			G_DrawChar(DECALX + x, DECALY + y, ' ', BRIGHT_CYAN, BRIGHT_CYAN);
		}
		// si un drapeau a d�j� �t� pos�
		else if (MAT[y][x] > MINE) {
			MAT[y][x] -= DRAPEAU;
			G_DrawChar(DECALX + x, DECALY + y, ' ', BLACK, BLACK);
		}
	}
}

