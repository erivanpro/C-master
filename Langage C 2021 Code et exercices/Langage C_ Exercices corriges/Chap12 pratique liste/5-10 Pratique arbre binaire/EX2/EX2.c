/*Exercice 2
-Réaliser un générateur d'arbres binaires STATIQUES contenant des données aléatoires. 
-Générer un arbre. 
-Parcourir l'arbre en profondeur (trois parcours à tester). 
-Parcourir l'arbre en largeur. À chaque fois, afficher l'arbre. 
-Obtenir toutes les propriétés de l'arbre 
	-taille, 
	-hauteur, 
	-nombre de feuilles, 
	-lister les feuilles, 
	-somme des nœuds de l'arbre. 
-Ramener tel ou tel nœud selon une valeur donnée. 
-Sauver l'arbre. 
-Détruire l'arbre. 
-Charger l'arbre.*/

/*BUG REMARQUE :

Un petit problème se pose lorsque le curseur en écriture de la console sort de la fenêtre
tout en restant dans le buffer. Il arrive alors que la dernière écrite se duplique en bas
de la fenêtre. Il faudrait éventuellement adapter le scroll en utilisant la fonction 
ScrollConsoleScreenBuffer https://docs.microsoft.com/en-us/windows/console/scrollconsolescreenbuffer

*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

#define PATH "Save Arbre.bin"
#define NOFILS	-1

// noeud de l'arbre statique
typedef struct Noeud {
	int val;
	int g;
	int d;
}Noeud;

void Menu();
Noeud* CreateArbrePlein(int nbNoeud);
Noeud* CreateArbreRandom(int level);
int _CreateArbreRandom(Noeud arbre[], int* pos, int level);
Noeud* CreateArbreOrdonne(int nbNoeud);
void AjouterFeuille(Noeud* arbre, int pos, Noeud n);
Noeud CreateNoeud(int val);
void DestroyArbre(Noeud** t);

void ParcoursPrefixe(Noeud t[], int r);
void ParcoursInfixe(Noeud t[], int r);
void ParcoursPostfixe(Noeud t[], int r);
void ParcoursEnlargeur(Noeud t[], int r);

void AffichageHorizontal(Noeud t[], int r, int niveau);
void _AffichageHorizontal(Noeud t[], int r, int niveau);
void AffichageVertical(Noeud t[], int r);
void _AffichageVertical(Noeud t[], int r, int* x, int y);

int TailleArbre(Noeud t[], int r);
int HauteurArbre(Noeud t[], int r);
int Max(int v1, int v2);
int NombreFeuilleArbre(Noeud t[], int r);
_Bool IsFeuilleArbre(Noeud n);
void ListerFeuilleArbre(Noeud t[], int r);
int SommeNoeudArbre(Noeud t[], int r);
Noeud* RecupNoeudArbre(Noeud t[], int r, int val);

_Bool SaveArbre(Noeud arbre[], char* path);
Noeud* LoadArbre(char* path);

// quelques outils annexes
void Gotoxy(int x, int y);
int Getposy(void);
int Getposx(void);
_Bool ConsClearTo(int bcolor, int fcolor, char lettre);
_Bool Blit(CHAR_INFO* dat, SMALL_RECT* datsrc, SMALL_RECT* consdest);
_Bool ConsClear(void);

_Bool ConsBufferMoreWidth(int width);
_Bool ConsBufferMoreHeight(int height);
_Bool ConsBufferLessWidth(int width);
_Bool ConsBufferLessHeight(int height);
int ConsGetBufferWidth(void);
int ConsGetBufferHeight(void);

int main()
{
	int fin = 0;
	srand((unsigned)time(NULL));

	// pour l'accentuation : ISO 8859-1 Latin 1; Western European (ISO)
	// https://docs.microsoft.com/en-us/windows/console/setconsoleoutputcp
	// https://docs.microsoft.com/fr-fr/windows/desktop/Intl/code-page-identifiers
	SetConsoleOutputCP(28591);

	// réduire la taille par défaut du buffer pour que l'effacement 
	// de la console ne soit pas trop long
	ConsBufferLessHeight(300);
	
	// l'arbre est contenu dans un tableau de Noeud
	Noeud* Arbre = NULL; 
	// la racine toujours à l'indice 0
	const int racine = 0;
	

	Menu();
	while (!fin) {
		switch (_getch()) {
			// création arbre plein avec affichage horizontal
			// (racine à gauche feuilles vers droite)
		case 'a':
			ConsClear();
			Menu();
			if (Arbre != NULL)
				DestroyArbre(&Arbre);
			Arbre = CreateArbrePlein(1 + rand() % 64);
			AffichageHorizontal(Arbre, racine, 0); // niveau 0 au départ (collé à la marge)
			break;

			// création arbre plein avec affichage vertical
			// (racine en haut feuilles vers bas)
		case 'z':
			ConsClear();
			Menu();
			if (Arbre != NULL)
				DestroyArbre(&Arbre);
			Arbre = CreateArbrePlein(1 + rand() % 64);
			AffichageVertical(Arbre, racine);
			break;

		// Création arbre aléatoire avec affichage vertical
		case 'e':
			ConsClear();
			Menu();
			if (Arbre)
				DestroyArbre(&Arbre);
			Arbre = CreateArbreRandom(1 + rand()% 6);
			AffichageVertical(Arbre, racine);

		break;
		// Création arbre ordonné avec affichage vertical
		case 'r':
			ConsClear();
			Menu();
			if (Arbre)
				DestroyArbre(&Arbre);
			Arbre = CreateArbreOrdonne(1+rand()%20);
			AffichageVertical(Arbre, racine);
			break;
		// les parcours
		case 't':
			if (Arbre) {
				printf("Prefixé  : ");
				ParcoursPrefixe(Arbre,racine);
				putchar('\n');
				printf("Infixé   : ");
				ParcoursInfixe(Arbre, racine);
				putchar('\n');
				printf("Postfixé : ");
				ParcoursPostfixe(Arbre, racine);
				putchar('\n');
				printf("Parcours en largeur, par niveau : ");
				ParcoursEnlargeur(Arbre, racine);
				putchar('\n');
			}
			
			break;

			//Taille, hauteur, nombre de feuilles, liste des feuilles
		case 'y':
			if (Arbre) {
				printf("Taille : %d\n", TailleArbre(Arbre, racine));
				printf("Hauteur : %d\n", HauteurArbre(Arbre, racine));
				printf("Nombre de feuilles : %d\n", NombreFeuilleArbre(Arbre, racine));
				printf("Liste des feuilles de l'arbre : ");
				ListerFeuilleArbre(Arbre, racine);
				putchar('\n');
				Gotoxy(0, Getposy() + 1);
			}
			break;

			// Somme des noeuds
		case 'u':
			if (Arbre) {
				printf("Somme des noeuds de l'arbre : %d\n", SommeNoeudArbre(Arbre, racine));
				Gotoxy(0, Getposy() + 1);
			}
			break;

			// Récuperer un noeud
		case 'i':
			if(Arbre){
				printf("Entrer la valeur à récupérer dans l'arbre : ");
				int val = -1;
				scanf_s("%d", &val);
				Noeud* n = RecupNoeudArbre(Arbre, racine, val);
				if (n)
					printf("noeud trouvé : adresse %p valeur %d\n", n, n->val);
				else
					printf("pas de noeud correspondant à %d\n", val);
				Gotoxy(0, Getposy() + 1);
			}
			break;
		
		// Sauver l'arbre
		case 'o':
			if (Arbre) {
				if(SaveArbre(Arbre, PATH))
					printf("arbre sauvegardé\n");
				else
					printf("erreur sauvegarde\n");
			}
			else
				printf("pas d'arbre à sauvegarder\n");
			break;

			// Charger l'arbre
		case 'p':
			//ConsClear();
			//Menu();
			if (Arbre != NULL)
				DestroyArbre(&Arbre);
			Arbre = LoadArbre(PATH);
			AffichageVertical(Arbre, racine);
			break;

		case 'q':
			fin = 1;
			break;
		}
	}
	DestroyArbre(&Arbre);
	return 0;
}

void Menu()
{
	Gotoxy(0, 0);
	printf("a : Création arbre aléatoire plein, affichage horizontal\n");
	printf("z : Création arbre aléatoire plein, affichage vertical\n");
	printf("e : Création arbre aléatoire non plein, affichage vertical\n");
	printf("r : Création arbre ordonné, affichage vertical\n");
	printf("t : Parcours en profondeur(préfixé, infixé, postfix) et en largeur (par niveau)\n");
	printf("y : Taille, hauteur, nombre de feuilles, liste des feuilles\n");
	printf("u : Somme des noeuds\n");
	printf("i : Récuperer un noeud\n");
	printf("o : Sauver l'arbre\n");
	printf("p : Charger l'arbre\n");
	printf("q : Quitter\n");
}
/***************************************************
Création/destruction arbre
***************************************************/
Noeud* CreateArbrePlein(int nbNoeud)
{
	// création d'un espace mémoire, un tableau, regroupant tous les noeuds
	Noeud* t = (Noeud*)malloc(sizeof(Noeud) * nbNoeud);
	if (t) {
		// la racine est en 0
		for (int i = 0, k = 0; i < nbNoeud; i++) {
			t[i].val = rand() % 100;
			t[i].g = ++k < nbNoeud ? k : NOFILS;
			t[i].d = ++k < nbNoeud ? k : NOFILS;
		}
	}
	return t;
}
// une autre possibilité de création d'arbre aléatoire,
// compatible avec la sauvegarde prévue.
Noeud* CreateArbreRandom(int level)
{
	Noeud *arbre = NULL;
	if (level > 0) {
		// au départ créer un tableau capable de contenir l'arbre potentiel le plus grand
		// selon le nombre de niveaux (2 puissance niveau - 1)
		int maxNoeud = (1 << level) - 1; // équivalent (2 puissance level) - 1
		arbre = (Noeud*)malloc(sizeof(Noeud) * maxNoeud);
		if (arbre != NULL) {
			int pos = 0; 
			_CreateArbreRandom(arbre, &pos, level);
		}
	}
	return arbre;
}
// création arbre
int _CreateArbreRandom(Noeud arbre[], int *pos, int level)
{
	int res = NOFILS;
	if (level > 0) {
		res = *pos;
		arbre[res] = CreateNoeud(rand() % 100);
		(*pos)++;
		if (rand() % 1000 > 250) {
			arbre[res].g = _CreateArbreRandom(arbre, pos, level - 1);
		}
		if (rand() % 1000 > 250) {
			arbre[res].d = _CreateArbreRandom(arbre, pos, level - 1);
		}
	}
	return res;
}
Noeud CreateNoeud(int val)
{
	return (Noeud) { val, -1, -1 };
}
Noeud* CreateArbreOrdonne(int nbNoeud)
{
	Noeud* arbre = (Noeud*)malloc(sizeof(Noeud) * nbNoeud);
	if (arbre) {
		arbre[0] = CreateNoeud(rand() % 100);
		for (int i = 1; i < nbNoeud; i++) {
			AjouterFeuille(arbre, i, CreateNoeud(rand() % 100));
		}
	}
	return arbre;
}

void AjouterFeuille(Noeud*arbre, int pos, Noeud n)
{
	int x, prec;

	x = 0;
	prec = NOFILS;
	while (x != NOFILS) {
		prec = x; // conserver la dernière position
		x = (n.val < arbre[x].val) ? arbre[x].g : arbre[x].d; // descente jusque feuille selon valeur
	}
	// en principe arrivée à la bonne position pour la nouvelle valeur,
	// accrocher la nouvelle feuille
	
	if (n.val < arbre[prec].val) {
		arbre[prec].g = pos;
		//arbre[pos] = n;  // ou bien 
		arbre[arbre[prec].g] = n; // pour mieux voir la filiation
	}
	else {
		arbre[prec].d = pos;
		// arbre[pos] = n;  
		arbre[arbre[prec].d] = n;
	}
}

void DestroyArbre(Noeud**t)
{
	if (*t != NULL) {
		free(*t);
		*t = NULL;
	}
}
/***************************************************
Parcours arbre arbre
***************************************************/
void ParcoursPrefixe(Noeud t[], int r)
{
	if (r != NOFILS) {
		printf("%3d", t[r].val);
		ParcoursPrefixe(t, t[r].g);
		ParcoursPrefixe(t,t[r].d);
	}
}
void ParcoursInfixe(Noeud t[], int r)
{
	if (r != NOFILS) {
		ParcoursInfixe(t, t[r].g);
		printf("%3d", t[r].val);
		ParcoursInfixe(t, t[r].d);
	}
}
void ParcoursPostfixe(Noeud t[], int r)
{
	if (r != NOFILS) {
		ParcoursPostfixe(t, t[r].g);
		ParcoursPostfixe(t, t[r].d);
		printf("%3d", t[r].val);
	}
}

void ParcoursEnlargeur(Noeud t[], int r)
{
	Noeud* file;
	int queue = 0, tete = 0; // queue et tête
	if (r == NOFILS || t == NULL)
		printf("Arbre vide\n");
	else {
		file = (Noeud*)malloc(sizeof(Noeud) * TailleArbre(t,r));
		if (file) {
			// la racine au départ de la file
			file[queue++] = t[r];
			while (tete != queue) {
				Noeud n = file[tete++]; // sortie en tête
				printf("%d ", n.val);
				if (n.g != NOFILS)
					file[queue++] = t[n.g]; // entrées en queue
				if (n.d != NOFILS)
					file[queue++] = t[n.d];
			}
			free(file);
		}
	}
}
/***************************************************
Affichage arbre
***************************************************/
void AffichageHorizontal(Noeud t[], int r, int niveau)
{
	if (r == NOFILS || t == NULL)
		printf("Arbre vide\n");
	else
		_AffichageHorizontal(t, r, niveau);

}
void _AffichageHorizontal(Noeud t[], int r, int niveau)
{
	if (r != NOFILS) {
		for (int i = 0; i < niveau; i++)
			printf("%5s", " ");
		printf("%2d\n", t[r].val);
		_AffichageHorizontal(t, t[r].g, niveau + 1);
		_AffichageHorizontal(t, t[r].d, niveau + 1);
	}
}

void AffichageVertical(Noeud t[], int r)
{
	if (r == NOFILS || t == NULL)
		printf("arbre vide\n");
	else {
		// problème affichage si trop grand : élargir le buffer de la fenêtre
		int hauteur = HauteurArbre(t, r);
		if (hauteur > 4) {
			int more = (6 << hauteur) + 10; // 6 * (2 puissance hauteur) + 10
			ConsBufferMoreWidth(more);
		}
		// dessin de l'arbre
		// trouver la bonne position en y
		int y = Getposy();
		// partir de la marge
		int x = 0; 
		_AffichageVertical(t, r, &x, y);
		// position curseur en dessous de l'arbre
		Gotoxy(0, y + hauteur * 2 + 1);
	}
}
void _AffichageVertical(Noeud t[],int r, int* x, int y)
{
	if ( t!= NULL && r != NOFILS) {
		_AffichageVertical(t,t[r].g, x, y + 2);
		*x += 3;
		Gotoxy(*x, y);
		printf("%2d", t[r].val);
		// en affichant *x à la place de val on peut
		// suivre l'ordre dans lequel se fait le tracé
		//printf("%2d", *x); 
		_AffichageVertical(t, t[r].d, x, y + 2);
	}
}
/***************************************************
Propriétés arbre arbre
***************************************************/
int TailleArbre(Noeud t[], int r)
{
	int res = 0;
	if (t != NULL && r != NOFILS)
		res = 1 + TailleArbre(t,t[r].g) + TailleArbre(t, t[r].d);
	return res;
}
int HauteurArbre(Noeud t[], int r)
{
	int h = 0;
	if (t != NULL && r != NOFILS)
		h = 1 + Max(HauteurArbre(t, t[r].g), HauteurArbre(t, t[r].d));
	return h;
}
int Max(int v1, int v2)
{
	return (v1 > v2) ? v1 : v2;
}
int NombreFeuilleArbre(Noeud t[], int r)
{
	int nb = 0;
	if (t != NULL && r != NOFILS) {
		if (IsFeuilleArbre(t[r]))
			nb = 1;
		else
			nb = NombreFeuilleArbre(t, t[r].g) + NombreFeuilleArbre(t, t[r].d);
	}
	return nb;
}
_Bool IsFeuilleArbre(Noeud n)
{
	return n.g == NOFILS && n.d == NOFILS;
}

void ListerFeuilleArbre(Noeud t[], int r)
{
	if (t != NULL && r != NOFILS) {
		if (IsFeuilleArbre(t[r]))
			printf("%3d", t[r].val);
		ListerFeuilleArbre(t, t[r].g);
		ListerFeuilleArbre(t, t[r].d);
	}
}
int SommeNoeudArbre(Noeud t[], int r)
{
	int res = 0;
	if (t != NULL && r != NOFILS) {
		res = t[r].val;
		res += SommeNoeudArbre(t, t[r].g) + SommeNoeudArbre(t, t[r].d);
	}
	return res;
}

Noeud* RecupNoeudArbre(Noeud t[], int r, int val)
{
	Noeud* n = NULL;
	if (t != NULL && r != NOFILS) {
		if (t[r].val == val)
			n = &t[r];
		else {
			n = RecupNoeudArbre(t, t[r].g, val);
			if (n == NULL)
				n = RecupNoeudArbre(t, t[r].d, val);
		}
	}
	return n;
}
/***************************************************
Sauvegarde arbre
La sauvegarde est plus simple qu'avec un arbre dynamique, il suffit de
sauver un tableau de Noeud, l'important est de connaitre la taille du
tableau. Ici c'est le nombre de noeuds dans le tableau.
***************************************************/
_Bool SaveArbre(Noeud arbre[], char*path)
{
	_Bool res = TRUE;
	if (arbre != NULL ) {
		FILE* f = NULL;
		fopen_s(&f, path, "wb");
		if (f != NULL) {
			int nbnoeud = TailleArbre(arbre, 0);
			// stocker au début taille de l'arbre (et du tableau)
			fwrite(&nbnoeud, sizeof(int), 1, f);
		
			// ensuite stocker l'arbre
			fwrite(arbre, sizeof(Noeud), nbnoeud, f);
			fclose(f);
		}
		else {
			printf("erreur création fichier\n");
			res = FALSE;
		}
	}
	else {
		printf("Arbre vide\n");
		res = FALSE;
	}
	return res;
}
Noeud* LoadArbre(char* path)
{
	FILE* f;
	Noeud* arbre = NULL;
	fopen_s(&f, path, "rb");
	if (f != NULL) {
		int nbnoeud = 0;
		if (!fread(&nbnoeud, sizeof(int), 1, f))
			return NULL;
		arbre = (Noeud*)malloc(sizeof(Noeud) * nbnoeud);
		if (!arbre)
			return NULL;
		if (fread(arbre, sizeof(Noeud), nbnoeud, f) != nbnoeud) {
			free(arbre);
			arbre = NULL;
		}
		fclose(f);
	}
	else
		printf("erreur ouverture fichier\n");
	return arbre;
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

	// le curseur reste dans le buffer mais peut sortir de la fenêtre
	// (ne marche pas super lorsqu'il sort de la fenetre mais ne plante pas
	// la console, à vérifier éventuellement)
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
// retourne la position horizontale du curseur en écriture
int Getposx()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h, &info);
	return info.dwCursorPosition.X;
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
		/*// n'efface que la fenêtre :
		src.Right = info.srWindow.Right + 1;
		src.Bottom = info.srWindow.Bottom + 1;
		*/
		// efface tout le buffer de la console
		src.Right = info.dwSize.X;
		src.Bottom = info.dwSize.Y;

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
/*
	Augmenter ou diminuer  la taille buffer de la fenêtre console. 
	Seule la partie mémoire est adaptée, la partie visible de la fenêtre
	reste la même (des ascenseurs apparaissent pour la verticale
	et l'horizontale).

	Pour changer la taille de la fenêtre utiliser la fonction 
	SetConsoleWindowInfo() mais attention le buffer ne peut jamais être plus 
	petit que la fenêtre.

	Dans l'exercice 1 une seule fonction permet d'élargir le buffer
	en largeur et en hauteur.
	Ici une fonction pour chaque cas : élargir ou rétrécir largeur ou hauteur.
	C'est un peu plus long mais finalement plus pratique.
*/
_Bool ConsBufferMoreWidth(int width)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h)
		return FALSE;

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	if (width > info.dwSize.X) {
		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	return TRUE;
}
_Bool ConsBufferMoreHeight(int height)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h)
		return FALSE;

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	if (height > info.dwSize.Y) {
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	return TRUE;
}
// attention le buffer ne peut pas être plus petit que la fenêtre
// sinon plantage de la console
_Bool ConsBufferLessWidth(int width)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h)
		return FALSE;

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;
	// width inférieur à la taille actuelle et supérieur à la taille de fenêtre
	if (width < info.dwSize.X && width > info.srWindow.Right) {
		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	return TRUE;
}
_Bool ConsBufferLessHeight(int height)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h)
		return FALSE;

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	if (height < info.dwSize.Y && height > info.srWindow.Bottom) {
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	return TRUE;
}
int ConsGetBufferWidth()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return -1;
	return info.dwSize.X;
}
int ConsGetBufferHeight()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!h)
		return -1;

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return -1;

	return info.dwSize.Y;
}

