/*********************************************************************************
Exercice 19 :
faire un labyrinthe avec croisements de chemin.
Modifier la fonction de cr�ation de labyrinthe afin de produire des labyrinthes
avec croisements de chemin. Comment �crire une fonction de recherche pour un
tel labyrinthe ?

*********************************************************************************/
// ETUDE AVEC DES CROISEMENTS DANS LE LABYRINTHE:
// -Le programme ajoute des fonctions pour cr�er des croisements dans le labyrinthe
// -La fonction de recherche de chemin est modifi�e. Le principe retenu est celui 
//  du petit Poucet : semer des cailloux pour retrouver son chemin (ici pour ne pas 
//  reprendre le m�me)
#include "GraphCons.h"

#define TX          150
#define TY          50
#define ESCAPE		27

#define MUR			0	// noir
#define CHEMIN		1	// couleur bleu
#define PASSAGE		5	// passage pour cr�er des croisements entre voies s�par�es
#define BUT         10	// vert clair
#define START		14	// entr�e pour la recherche (jaune clair)
#define CHERCHE		9	// recherche chemin (couleur bleu clair)
#define ACCES       4	// acc�s but d�couvert (couleur rouge fonc�)


// le terrain
int MAT[TY][TX];

//Les fonctions en rapport avec le labyrinthe

void CreateLabyAlea(void);
void CreuseLaby(int x, int y);
void InitDir(int d[4]);
void MemAfficheLaby(int posx, int posy);
void Trouve(int olddir, int posx, int posy);
void SelectEntree(int olddir, int*x, int*y);
int Chemin(int x, int y, int olddir, int posx, int posy);
void CreatePassages(void);
int ComptePosChemin(int x, int y);
void MemAffichePos(int x, int y, int color);

int main()
{
	srand(time(NULL));

	if (!G_PleinEcran())
		if (!G_ConsResizeMax())
			printf("plein ecran impossible\n");
	
	G_ConsCursor(FALSE);
	do {
		G_ConsClearTo(12, INVISIBLE, ' ');
		
		CreateLabyAlea();
		MemAfficheLaby(24, 2);
		Trouve(rand() % 4, 24, 2);

	} while (_getch() != ESCAPE);

	G_Gotoxy(0, TY + 2);
	return 0;
}

void CreateLabyAlea()
{
	memset(MAT, 0, sizeof(int)*TX*TY);
	int x = rand() % TX;
	int y = rand() % TY;
	MAT[y][x] = BUT;
	CreuseLaby(x, y);
	CreatePassages();
}

void CreuseLaby(int x, int y)
{
	int d[4];//= { 0,1,2,3 };
	int i;
	if (MAT[y][x] != BUT)
		MAT[y][x] = CHEMIN;

	InitDir(d);
	for (i = 0; i < 4; i++)
		switch (d[i]) {
		case 0: // remonte nord
			if (y > 1 && MAT[y - 2][x] == MUR) {
				MAT[y - 1][x] = CHEMIN;
				CreuseLaby(x, y - 2);
			}
			break;
		case 1: // avance est
			if (x < TX - 2 && MAT[y][x + 2] == MUR) {
				MAT[y][x + 1] = CHEMIN;
				CreuseLaby(x + 2, y);
			}
			break;
		case 2: // descend sud
			if (y < TY - 2 && MAT[y + 2][x] == MUR) {
				MAT[y + 1][x] = CHEMIN;
				CreuseLaby(x, y + 2);
			}
			break;
		case 3: // avance ouest
			if (x > 1 && MAT[y][x - 2] == MUR) {
				MAT[y][x - 1] = CHEMIN;
				CreuseLaby(x - 2, y);
			}
			break;
		}
}
void InitDir(int d[4])
{
	int i, i1, i2, tmp;
	for (i = 0; i < 4; i++)
		d[i] = i;

	for (i = 0; i < 50; i++) {
		i1 = rand() % 4;
		i2 = rand() % 4;
		if (i1 != i2) {
			tmp = d[i1];
			d[i1] = d[i2];
			d[i2] = tmp;
		}
	}
}	
// Cr�er des passages afin de doter le labyrinthe de ciruits.
// Il s'agit simpelent de creuser du mur qui s�pare deux chemins.
// Le nombre de passages cr��s est al�atoire de fa�on un peu statistique.
void CreatePassages()
{
	for(int y = 1; y< TY-1; y++)
		for (int x = 1; x < TX; x++) {
			if (MAT[y][x] == MUR && ComptePosChemin(x, y) > 0 && rand() % 1000 > 980)
				MAT[y][x] = PASSAGE;
		}
}
// Deux chemins peuvent �tre reli�s � certaines conditions :
// -la position concern�e pour faire passage doit �tre du mur
// - Le passage doit relier nord et sud ou est et ouest
//   (des passages en coin sont exclus)
int ComptePosChemin(int x, int y)
{
	for (int i = y - 1; i < y + 1; i++)
		for (int j = x - 1; j < x + 1; j++)
			if (MAT[i][j] == PASSAGE)
				return 0;

	int cmpt = 0;
	if (MAT[y - 1][x] == CHEMIN && MAT[y + 1][x] == CHEMIN &&
		MAT[y][x + 1] == MUR && MAT[y][x - 1] == MUR)
		cmpt++;
	if (MAT[y][x + 1] == CHEMIN && MAT[y][x - 1] == CHEMIN &&
		MAT[y - 1][x] == MUR && MAT[y + 1][x] == MUR)
		cmpt++;
	
	return cmpt;
}
// version rapide de la fonction d'affichage
void MemAfficheLaby(int posx, int posy)
{
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*TX*TY);
	for (int y = 0; y < TY; y++) {
		for (int x = 0; x < TX; x++) {
			WORD color = (WORD)MAT[y][x];
			// attention : multiplier par 16 pour 
			// passer � couleur de fond (ou << 4 �quivalent)
			dat[y*TX + x].Attributes = color << 4;
			dat[y*TX + x].Char.AsciiChar = ' ';
		}
	}
	// casts pour small rect ensuite
	SHORT left = 0, top = 0, right = TX, bottom = TY;
	SMALL_RECT src = { left,top,right,bottom };

	left = posx, top = posy, right = TX + posx, bottom = TY + posy;
	SMALL_RECT dest = { left,top,right,bottom };
	G_Blit(dat, &src, &dest);
	free(dat);
}
void Trouve(int olddir, int posx, int posy)
{
	int x, y;
	SelectEntree(olddir, &x, &y);
	MAT[y][x] = START;
	while (!Chemin(x, y, olddir, posx, posy))
		olddir = (olddir + 1) % 4;
}

// l'entr�e se fait par un bord au nord, est, sud ou ouest.
// A partir de n'importe quel bord si le bord courant ne fournit 
// pas de solution la fonction cherche alors sur le bord suivant.
// La position finale obtenue est donn�e en sortie via les pointeurs
// x et y
void SelectEntree(int olddir, int*x, int*y)
{
	olddir;
	do {
		switch (olddir) {
			// entr�e nord
		case 0:
			*y = 0;
			*x = 0;
			while (*x < TX && MAT[*y][*x] != CHEMIN)
				(*x)++;
			if (*x < TX)
				return;

			// entr�e est
		case 1:
			*y = 0;
			*x = TX - 1;
			while (*y < TY && MAT[*y][*x] != CHEMIN)
				(*y)++;
			if (*y < TY)
				return;

			// entr�e sud
		case 2:
			*y = TY - 1;
			*x = 0;
			while (*x < TX && MAT[*y][*x] != CHEMIN)
				(*x)++;
			if (*x < TX)
				return;

			// entr�e ouest
		case 3:
			*y = 0;
			*x = 0;
			while (*y < TY && MAT[*y][*x] != CHEMIN)
				(*y)++;
			if (*y < TY)
				return;
		}
		olddir = (olddir + 1) % 4;

	} while (1);
}
// L'affichage de la recherche de chemin se fait progressivement
// au fur et � mesure. Les param�tres posx et posy servent � d�caler
// l'affichage des bords haut et gauche de la console. Il doivent
// prendre les m�mes valeurs que le d�calage demand� pour l'affichage 
// du labyrinthe. Le param olddir correspond � la direction pr�c�dente.

// Avec des croisements, pour faire simple la seule modification requise 
// est de proc�der comme le petit Poucet : en semant des cailloux qui 
// signalent le chemin d�j� parcouru. Chaque position vue prend ainsi la 
// valeur CHERCHE diff�rente de la valeur CHEMIN. Si la recherche tombe sur
// une position � CHERCHE elle stope les appls r�cursifs
int Chemin(int x, int y, int olddir, int posx, int posy)
{
	int i, nx, ny;

	// 1 
	// si sortie matrice ou retombe sur chemin d�j� vu
	if (x < 0 || x >= TX || y < 0 || y >= TY || MAT[y][x] == CHERCHE)
		return 0;

	if (MAT[y][x] == BUT)
		return 1;

	// 2 si CHEMIN ou START
	if (MAT[y][x] != MUR) {
		// 3 
		if (MAT[y][x] != START) {
			MAT[y][x] = CHERCHE; // marquer le chemin
			MemAffichePos(x + posx, y + posy, CHERCHE);
		}

		G_Attendre(5);
		// 4
		for (i = 0; i < 4; i++) {
			if (i != (olddir + 2) % 4) { // si non retour en arri�re
				// 5 
				// nord(0): 0, est(1): 1, sud(2): 0, ouest(3):-1
				nx = x + (i % 2)*(2 - i);
				// nord(0): -1, est(1): 0, sud(2): 1, ouest(3): 0
				ny = y + ((i + 1) % 2)*(i - 1);
				// 6 
				if (Chemin(nx, ny, i, posx, posy)) {
					// 7 L'affichage du point de d�part se fait en tout dernier
					if (MAT[y][x] == START)
						MemAffichePos(x + posx, y + posy, START);
					else
						MemAffichePos(x + posx, y + posy, ACCES);
					G_Attendre(10);
					return 1;
				}
			}
		}
	}
	return 0;
}
void MemAffichePos(int x, int y, int color)
{
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO));
	// attention : multiplier par 16 pour 
	// passer � couleur de fond (ou << 4 �quivalent)
	dat->Attributes = ((WORD)color) << 4;
	dat->Char.AsciiChar = ' ';

	// casts pour small rect ensuite
	SHORT left = 0, top = 0, right = 1, bottom = 1;
	SMALL_RECT src = { left,top,right,bottom };

	left = x, top = y, right = x + 1, bottom = y + 1;
	SMALL_RECT dest = { left,top,right,bottom };
	G_Blit(dat, &src, &dest);
	free(dat);
}
