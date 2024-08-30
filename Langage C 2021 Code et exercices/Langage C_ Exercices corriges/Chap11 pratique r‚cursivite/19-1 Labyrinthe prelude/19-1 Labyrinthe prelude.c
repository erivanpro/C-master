/*********************************************************************************
Exercice 19 :
faire un labyrinthe avec croisements de chemin.
Modifier la fonction de création de labyrinthe afin de produire des labyrinthes
avec croisements de chemin. Comment écrire une fonction de recherche pour un
tel labyrinthe ?

*********************************************************************************/
// ETUDE PRELINIMAIRE
// Création de labyrinthes avec but à atteindre, recherche de chemin, tracé du chemin 
// pour arriver au but. L'affichage du chemin bénéficie de fonctions directes mmémoire 
// très rapides. C'est l'occasion de commencer une librairie pour une utilisation plus  
// ludique de la console.

#include "GraphCons.h"

#define TX           150
#define TY           50
#define ESCAPE		27

#define MUR			0	// noir
#define CHEMIN		1	// couleur bleu
#define PASSAGE		2
#define BUT         10	// vert clair
#define START		14	// entrée pour la recherche (jaune clair)
#define CHERCHE		9	// recheche chemin (couleur bleu clair)
#define ACCES       4	// accès but découvert (couleur rouge foncé)


// le terrain
int MAT[TY][TX];

//Les fonctions en rapport avec le labyrinthe

void CreateLabyAlea(void);
void CreuseLaby(int x, int y);
void InitDir(int d[4]);
//void AfficheLaby(int posx, int posy);
void MemAfficheLaby(int posx, int posy);
void Trouve(int olddir, int posx, int posy);
void SelectEntree(int olddir, int*x, int*y);
int Chemin(int x, int y, int olddir, int posx, int posy);
//void AffichePos(int x, int y, int color);
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
//void AfficheLaby(int posx, int posy)
//{
//	int x, y;
//	for (y = 0; y < TY; y++)
//		for (x = 0; x < TX; x++)
//			AffichePos(posx + x, posy + y, MAT[y][x]);
//}
// version rapide de la fonction d'affichage
void MemAfficheLaby(int posx, int posy)
{
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*TX*TY);
	for (int y = 0; y < TY; y++) {
		for (int x = 0; x < TX; x++) {
			WORD color = (WORD)MAT[y][x];
			// attention : multiplier par 16 pour 
			// passer à couleur de fond (ou << 4 équivalent)
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

// l'entrée se fait par un bord au nord, est, sud ou ouest.
// A partir de n'importe quel bord si le bord courant ne fournit 
// pas de solution la fonction cherche alors sur le bord suivant.
// La position finale obtenue est donnée en sortie via les pointeurs
// x et y
void SelectEntree(int olddir, int*x, int*y)
{
	olddir;
	do {
		switch (olddir) {
			// entrée nord
		case 0:
			*y = 0;
			*x = 0;
			while (*x < TX && MAT[*y][*x] != CHEMIN)
				(*x)++;
			if (*x < TX)
				return;

			// entrée est
		case 1:
			*y = 0;
			*x = TX - 1;
			while (*y < TY && MAT[*y][*x] != CHEMIN)
				(*y)++;
			if (*y < TY)
				return;

			// entrée sud
		case 2:
			*y = TY - 1;
			*x = 0;
			while (*x < TX && MAT[*y][*x] != CHEMIN)
				(*x)++;
			if (*x < TX)
				return;

			// entrée ouest
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
// au fur et à mesure. Les paramètres posx et posy servent à décaler
// l'affichage des bords haut et gauche de la console. Il doivent
// prendre les mêmes valeurs que le décalage demandé pour l'affichage 
// du labyrinthe. Le param olddir correspond à la direction précédente.
int Chemin(int x, int y, int olddir, int posx, int posy)
{
	int i, nx, ny;

	// 1 
	// si sortie matrice 
	if (x < 0 || x >= TX || y < 0 || y >= TY)
		return 0;

	if (MAT[y][x] == BUT)
		return 1;
	
	// 2 si CHEMIN ou START
	if (MAT[y][x] != MUR) {
		// 3 
		if (MAT[y][x] != START)
			MemAffichePos(x + posx, y + posy, CHERCHE);
		G_Attendre(5);
		// 4
		for (i = 0; i < 4; i++) {
			if (i != (olddir + 2) % 4) { // si non retour en arrière
				// 5 
				// nord(0): 0, est(1): 1, sud(2): 0, ouest(3):-1
				nx = x + (i % 2)*(2 - i);
				// nord(0): -1, est(1): 0, sud(2): 1, ouest(3): 0
				ny = y + ((i + 1) % 2)*(i - 1);
				// 6 
				if (Chemin(nx, ny, i, posx, posy)) {
					// 7 L'affichage du point de départ se fait en tout dernier
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
//void AffichePos(int x, int y, int color)
//{
//	Gotoxy(x, y);
//	TextColor(color << 4);
//	putchar(' ');
//}
void MemAffichePos(int x, int y, int color)
{
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO));
	// attention : multiplier par 16 pour 
	// passer à couleur de fond (ou << 4 équivalent)
	dat->Attributes = ((WORD)color) << 4;
	dat->Char.AsciiChar = ' ';

	// casts pour small rect ensuite
	SHORT left = 0, top = 0, right = 1, bottom = 1;
	SMALL_RECT src = { left,top,right,bottom };

	left = x, top = y, right = x + 1, bottom = y + 1;
	SMALL_RECT dest = { left,top,right,bottom };
	G_Blit(dat, &src, &dest);
}

