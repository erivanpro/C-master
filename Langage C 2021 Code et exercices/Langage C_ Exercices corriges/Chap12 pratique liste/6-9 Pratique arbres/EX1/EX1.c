/*
Exercice 1
Générer un arbre binaire de recherche. Rechercher dedans un 
élément selon sa clé. Supprimer un élément. Afficher l'arbre. 
Faire la somme des éléments de l'arbre. Lister tous les éléments 
de l'arbre, etc.
*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define MAXNOEUD	16
typedef struct Noeud 
{
	int cle;
	// présence symbolique de datas uniquement pour illustrer qu'en dehors de la clé
	// un noeud peut posséder toutes sortes d'informations,
	char dat;   // ici ce sera juste une lettre. 
	struct Noeud* g, *d;
}Noeud;

// créer et détruire arbre
void Menu(void);
int CompareCle(int cle1, int cle2);
void Inserer(Noeud** r, Noeud* n);
Noeud* CreateNoeud(int cle, char dat);
void DestroyArbre(Noeud** r);
// afficher arbre
void AffichageVertical(Noeud* r);
void _AffichageVertical(Noeud* r, int* x, int y);
int HauteurArbre(Noeud* r);
int Max(int v1, int v2);
// trouver un noeud dans l'arbre selon sa clé
int DemandeCle(void);
Noeud* Rechercher(Noeud* r, int cle);
// supprimer un noeud selon sa clé
Noeud* RamenerMax(Noeud** r);
Noeud* Supprimer(Noeud** r, int cle);
// lister tous les noeuds
Noeud** Lister(Noeud* r, int* nbNoeud);
int NombreNoeud(Noeud* r);
void AfficherListe(Noeud* liste[], int nbNoeud);
void DestroyListe(Noeud*** liste);
// ordre croissant et addition clés
void ParcourInfixe(Noeud* r);
int AdditionCle(Noeud* r);
// outils console
void Gotoxy(int x, int y);
int Getposy(void);
void Pause(void);
_Bool ConsClearTo(int bcolor, int fcolor, char lettre);
_Bool Blit(CHAR_INFO* dat, SMALL_RECT* datsrc, SMALL_RECT* consdest);
_Bool ConsClear();

int main()
{
	// pour l'accentuation : ISO 8859-1 Latin 1; Western European (ISO)
	// https://docs.microsoft.com/en-us/windows/console/setconsoleoutputcp
	// https://docs.microsoft.com/fr-fr/windows/desktop/Intl/code-page-identifiers
	SetConsoleOutputCP(28591);
	srand((unsigned)time(NULL));

	char fin = 0, nb = 0, cle;
	Noeud* Racine = NULL;
	Noeud* n = NULL;

	Menu();
	while (fin != 'q') {
		switch (_getch()) {
		//créer un arbre ordonné, aléatoire
		case 'a':
			if (Racine != NULL) 
				DestroyArbre(&Racine);
			ConsClear();
			Menu();
			
			nb = rand() % (MAXNOEUD/2);
			for (int i = 0; i < nb; i++)
				Inserer(&Racine, CreateNoeud(rand() % 100, 'A' + i));
			AffichageVertical(Racine);
			break;
		//ajouter un noeud dans l'arbre (val aléatoire)	
		case 'z':
			if (Racine != NULL) {
				ConsClear();
				Menu();
			}
			Inserer(&Racine, CreateNoeud(rand() % 100, 'A' + rand() % 26));
			AffichageVertical(Racine);
			break;
		//chercher un élément dans l'arbre
		case 'e':
			cle = DemandeCle();
			n = Rechercher(Racine, cle);
			if (n)
				printf("Elément trouvé à l'adresse %p\n", n);
			else
				printf("pas d'élément avec la clé %d\n", cle);
			break;
		//supprimer un noeud
		case 'r':
			cle = DemandeCle();
			n = Supprimer(&Racine, cle);
			if (n) {
				printf("suppression effectuée\n");
				free(n);
			}
			else
				printf("clé non trouvée\n");
			AffichageVertical(Racine);
			break;
		//somme des clés 
		case 't':
			printf("addition des clés : %d\n", AdditionCle(Racine));
			break;
		// lister les éléments
		case 'y':
		{
			int nbNoeud = 0;
			Noeud** liste = Lister(Racine, &nbNoeud);
			AfficherListe(liste, nbNoeud);
			DestroyListe(&liste);
			break;
		}
		// afficher l'ordre croissant
		case 'u':
			ParcourInfixe(Racine);
			puts("");
			break;
		// quitter
		default: fin = 'q';
		}
	}
	DestroyArbre(&Racine);
	return 0;
}
void Menu()
{
	printf("a : créer un arbre ordonné, aléatoire\n");
	printf("z : ajouter un noeud dans l'arbre (val aléatoire)\n");
	printf("e : chercher un élément dans l'arbre\n");
	printf("r : supprimer un noeud\n");
	printf("t : somme des éléments\n");
	printf("y : lister les éléments\n");
	printf("u : Afficher en ordre croissant\n");
	printf("q : quitter\n");
}
/******************************************************
Créer et détruire arbre
*******************************************************/
// pour créer un arbre il suffit d'insérer des éléments dedans
// et pour ce faire il faut pouvoir comparer les clés entre elles
int CompareCle(int cle1, int cle2)
{
	return (cle1 == cle2) ? 0 : ((cle1 < cle2) ? -1 : 1);
}
void Inserer(Noeud**r, Noeud* n)
{
	if (*r == NULL)
		*r = n;
	else {
		int cmp = CompareCle(n->cle, (*r)->cle);
		if (cmp == 0)
			; // printf("pas d'insertion, la cle %d existe deja\n", n->cle);
		else if (cmp < 0)
			Inserer(&(*r)->g, n);
		else
			Inserer(&(*r)->d, n);
	}
}
// créer un noeud
Noeud* CreateNoeud(int cle, char dat)
{
	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	if (n) {
		n->cle = cle;
		n->dat = dat;
		n->d = n->g = NULL;
	}
	return n;
}
void DestroyArbre(Noeud** r)
{
	if (*r != NULL) {
		Noeud* n = *r;
		DestroyArbre(&(*r)->g);
		DestroyArbre(&(*r)->d);
		free(*r);
		*r = NULL;
	}
}
/******************************************************
Affichage arbre
*******************************************************/
void AffichageVertical(Noeud* r)
{
	int x = 0;
	int y = Getposy();
	if (r == NULL)
		printf("arbre vide\n");
	else
		_AffichageVertical(r, &x, Getposy());
	
	int h = HauteurArbre(r) * 2;
	Gotoxy(0, y + h );
}
void _AffichageVertical(Noeud* r, int* x, int y)
{
	if (r != NULL) {
		_AffichageVertical(r->g, x, y + 2);
		*x += 5;
		Gotoxy(*x, y);
		printf("%d%c", r->cle,r->dat);
		_AffichageVertical(r->d, x, y + 2);
	}
}
int HauteurArbre(Noeud* r)
{
	int h = 0;
	if (r != NULL)
		h = 1 + Max(HauteurArbre(r->g), HauteurArbre(r->d));
	return h;
}
int Max(int v1, int v2)
{
	return (v1 > v2) ? v1 : v2;
}
/******************************************************
Recherche dans l'arbre un noeud selon sa clé
*******************************************************/
int DemandeCle()
{
	int cle, res;
	do{
		printf("Entrez une clé : ");
		res = scanf_s("%d", &cle);
		if (res == 0) 
			printf("la clé doit être un nombre entier, recommencez :");
		rewind(stdin);
	} while (res != 1);
	return cle;
}
Noeud* Rechercher(Noeud* r, int cle)
{
	int cmp;
	Noeud* res = NULL;
	if (r != NULL) {
		cmp = CompareCle( cle, r->cle);
		if (cmp == 0)
			res = r;
		else if (cmp < 0)
			res = Rechercher(r->g, cle);
		else
			res = Rechercher(r->d, cle);
	}
	return res;
}
/*******************************************************
Supprimer un noeud selon sa clé
*******************************************************/
Noeud* RamenerMax(Noeud** r)
{
	Noeud* res = NULL;
	if (*r != NULL) {
		if ((*r)->d == NULL) { // plus grand trouvé
			res = *r;
			*r = (*r)->g;
		}
		else
			res = RamenerMax(&(*r)->d);
	}
	return res;
}
Noeud* Supprimer(Noeud** r, int cle)
{
	int cmp;
	Noeud* res = NULL;
	if (*r != NULL) {
		cmp = CompareCle(cle, (*r)->cle);
		if (cmp < 0)
			res = Supprimer(&(*r)->g, cle);
		else if (cmp > 0)
			res = Supprimer(&(*r)->d, cle);
		else { // noeud trouvé
			res = *r;
			if (res->d == NULL)
				*r = res->g;
			else if (res->g == NULL)
				*r = res->d;
			else {// si deux fils, suppression plus grand à gauche
				res = RamenerMax(&(*r)->g);
				(*r)->dat = res->dat;
			}
		}
	}
	return res;
}

/*******************************************************
Lister tous les éléments de l'arbre
*******************************************************/
Noeud** Lister(Noeud* r, int* nbNoeud)
{
	Noeud** tab = NULL;
	int nb = 0;
	nb = NombreNoeud(r);
	if (nb > 0) {
		tab = (Noeud **)malloc(sizeof(Noeud*) * nb);
		if (tab) {
			int pos = 0;
			int f = 1;
			tab[pos] = r;
			while (f < nb) {
				if (tab[pos]->g != NULL)
					tab[f++] = tab[pos]->g;
				if (tab[pos]->d != NULL)
					tab[f++] = tab[pos]->d;
				pos++;
			}
		}
	}
	*nbNoeud = nb;
	return tab;
}
int NombreNoeud(Noeud* r)
{
	int res = 0;
	if (r != NULL) 
		res = 1 + NombreNoeud(r->g) + NombreNoeud(r->d);
	return res;
}
void AfficherListe(Noeud* liste[], int nbNoeud)
{
	if (liste == NULL || nbNoeud == 0)
		printf("liste vide");
	else {
		for (int i = 0; i < nbNoeud; i++)
			printf("%d%c-", liste[i]->cle, liste[i]->dat);
	}
	puts("");
}
void DestroyListe(Noeud*** liste)
{
	if (*liste != NULL) {
		free(*liste);
		*liste = NULL;
	}
}
/******************************************************
Afficher en ordre croissant
*******************************************************/
void ParcourInfixe(Noeud* r)
{
	if (r != NULL) {
		ParcourInfixe(r->g);
		printf("%d%c-", r->cle, r->dat);
		ParcourInfixe(r->d);
	}
}
/******************************************************
Additionner toutes les clés
*******************************************************/
int AdditionCle(Noeud* r)
{
	int res = 0;
	if (r != NULL) {
		res = r->cle + AdditionCle(r->g) + AdditionCle(r->d);
	}
	return res;
}

/*******************************************************
Tools utilisation console
*******************************************************/
void Gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };

	// controler que le curseur ne sorte pas du buffer associé  
	// à la fenêtre pour éviter des comportements indéfinis de  
	// la console ensuite
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h, &info);

	if (c.X < info.dwSize.X && c.Y < info.dwSize.Y)
		SetConsoleCursorPosition(h, c);
}
// retourne la position vertivale du curseur en écriture
int Getposy()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h, &info);
	return info.dwCursorPosition.Y;
}
void Pause()
{
	printf("\nPresser Enter pour continuer...\n");
	char c = getchar();
}
/*Fonction pour remplir la fenetre console avec une couleur
et une lettre. La couleur couvre à la fois le fond (back :
4 bits de gauche) et la lettre (le for : les quatre bits
de droite)*/
_Bool ConsClearTo(int bcolor, int fcolor, char lettre)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	int nb = info.dwSize.X * info.dwSize.Y;
	CHAR_INFO* dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * nb);
	if (dat != NULL) {
		for (int i = 0; i < nb; i++) {
			dat[i].Attributes = (bcolor << 4) + fcolor;
			dat[i].Char.AsciiChar = lettre;
		}

		SMALL_RECT src = { 0 };
		src.Right = info.srWindow.Right + 1;
		src.Bottom = info.srWindow.Bottom + 1;

		SMALL_RECT dest = src;
		Blit(dat, &src, &dest);
		free(dat);
	}
	else
		return FALSE;

	// le curseur en écriture est placé en haut gauche
	Gotoxy(0, 0);

	return TRUE;
}
/*	Afficher directement dans la console un block dat de
	CHAR_INFO depuis le rectangle source pris dans dat et à
	destination du rectangle dest visible dans la console.
	Les champs right et bottom correspondent respectivement
	à la taille de la largeur et de la hauteur.

	Le paramètre constdest détermine le rectangle d'affichage dans la
	console. C'est un paramète en entrée et en sortie. En sortie il
	retourne le rectangle effectivement affiché dans la console.
	La fonction WriteConsoleOutPut() controle donc les possibles
	débordements du buffer de la console : écrire en dehors ne
	produit pas d'erreur.

	Documentation de la fonction WriteConsoleOutPut():
	https://docs.microsoft.com/en-us/windows/console/writeconsoleoutput
*/
_Bool Blit(CHAR_INFO* dat, SMALL_RECT* datsrc, SMALL_RECT* consdest)
{
	COORD taille = { datsrc->Right,datsrc->Bottom };
	COORD pos = { datsrc->Left, datsrc->Top };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	if (!WriteConsoleOutput(h, dat, taille, pos, consdest))
		return FALSE;
	return TRUE;
}
/*
Effacer la console avec des espaces noirs
*/
_Bool ConsClear()
{
	return ConsClearTo(0, 0, ' ');
}
/*****************************************
******************************************/