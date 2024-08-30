/*Exercice 3
Réaliser un générateur d'arbres binaires SUR FICHIER contenant des données aléatoires. 
-Générer un arbre. 
-Parcourir l'arbre en profondeur (trois parcours à tester). 
-Parcourir l'arbre en largeur. À chaque fois, afficher l'arbre. 
-Obtenir toutes les propriétés de l'arbre 
	-taille, 
	-hauteur, 
	-nombre de feuilles, 
	-lister les feuilles, 
	-somme des nœuds de l'arbre). 
-Ramener tel ou tel nœud selon une valeur donnée. 
-Sauver l'arbre. 
-Charger l'arbre.
-Détruire l'arbre.
*/


/*BUG REMARQUE :

Un petit problème se pose lorsque le curseur en écriture de la console sort de la fenêtre
tout en restant dans le buffer. Il arrive alors que la dernière phrase écrite se duplique en bas
de la fenêtre. Il faudrait éventuellement adapter le scroll en utilisant la fonction
ScrollConsoleScreenBuffer https://docs.microsoft.com/en-us/windows/console/scrollconsolescreenbuffer

*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

#define NOFILS	-1

// noeud de l'arbre statique
typedef struct Noeud {
	int val;
	int g;
	int d;
}Noeud;

void Menu();
void EcrireNoeud(FILE* f, int pos, Noeud* n);
void LireNoeud(FILE* f, int pos, Noeud* n);
int FileLength(FILE* f);
void CreateNewFile(FILE** f);


void CreateArbrePlein(FILE* f, int nbNoeud);
int CreateArbreRandom(FILE*f, int* pos, int level);
void CreateArbreOrdonne(FILE* f, int nbNoeud);
void AjouterFeuille(FILE* f, int pos, Noeud n);
Noeud CreateNoeud(int val);
void DestroyArbre(FILE** arbre);


void ParcoursPrefixe(FILE*f, int r);
void ParcoursInfixe(FILE*f, int r);
void ParcoursPostfixe(FILE*f, int r);
void ParcoursEnlargeur(FILE*f, int r);

void AffichageHorizontal(FILE*f, int r, int niveau);
void _AffichageHorizontal(FILE* f, int r, int niveau);
void AffichageVertical(FILE* f, int r);
void _AffichageVertical(FILE* f, int r, int* x, int y);

int TailleArbre(FILE*f, int r);
int HauteurArbre(FILE*f, int r);
int Max(int v1, int v2);
int NombreFeuilleArbre(FILE*f, int r);
_Bool IsFeuilleArbre(Noeud n);
void ListerFeuilleArbre(FILE*f, int r);
int SommeNoeudArbre(FILE*f, int r);
int RecupNoeudArbre(FILE* f, int r, int val);


FILE* CopieFichierArbre(FILE* f, int r, char* path);
FILE* LoadArbre(char* path);

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

	// réduire la taille par défaut du buffer
	//ConsBufferLessHeight(150);

	// l'arbre est contenu dans un fichier de Noeuds
	FILE* fArbre = NULL;
	CreateNewFile(&fArbre);

	// la racine toujours le premier noeud dans le fichier
	// comme dans un tableau
	const int racine = 0;

	Menu();
	while (!fin) {
		switch (_getch()) {
			// création arbre plein avec affichage horizontal 
			// (racine à gauche feuilles vers droite)
		case 'a':
			ConsClear();
			Menu();
			if (FileLength(fArbre) != 0)
				CreateNewFile(&fArbre);
			CreateArbrePlein(fArbre, 1 + rand() % 64);
			AffichageHorizontal(fArbre, racine, 0); // niveau 0 au départ (collé à la marge)
			break;

			// création arbre plein avec affichage vertical
			// (racine en haut feuilles vers bas)
		case 'z':
			ConsClear();
			Menu();
			if (FileLength(fArbre) != 0)
				CreateNewFile(&fArbre);
			CreateArbrePlein(fArbre, 1 + rand() % 64);
			AffichageVertical(fArbre, racine);
			break;

			// Création arbre aléatoire avec affichage vertical
		case 'e':
		{
			ConsClear();
			Menu();
			if (FileLength(fArbre) != 0)
				CreateNewFile(&fArbre);
			int pos = racine;
			CreateArbreRandom(fArbre, &pos, 1 + rand() % 6);
			AffichageVertical(fArbre, racine);
			break;
		}
		// Création arbre ordonné avec affichage vertical
		case 'r':
			ConsClear();
			Menu();
			if (FileLength(fArbre) != 0)
				CreateNewFile(&fArbre);
			CreateArbreOrdonne(fArbre, 1 + rand() % 20);
			AffichageVertical(fArbre, racine);
			break;
		// les parcours
		case 't':
			if (FileLength(fArbre) != 0) {
				printf("Prefixé  : ");
				ParcoursPrefixe(fArbre, racine);
				putchar('\n');
				printf("Infixé   : ");
				ParcoursInfixe(fArbre, racine);
				putchar('\n');
				printf("Postfixé : ");
				ParcoursPostfixe(fArbre, racine);
				putchar('\n');
				printf("Parcours en largeur, par niveau : ");
				ParcoursEnlargeur(fArbre, racine);
				putchar('\n');
			}
			break;

			//Taille, hauteur, nombre de feuilles, liste des feuilles
		case 'y':
			if (FileLength(fArbre) != 0) {
				printf("Taille : %d\n", TailleArbre(fArbre, racine));
				printf("Hauteur : %d\n", HauteurArbre(fArbre, racine));
				printf("Nombre de feuilles : %d\n", NombreFeuilleArbre(fArbre, racine));
				printf("Liste des feuilles de l'arbre : ");
				ListerFeuilleArbre(fArbre, racine);
				putchar('\n');
				Gotoxy(0, Getposy() + 1);
			}
			break;

			// Somme des noeuds
		case 'u':
			if (FileLength(fArbre) != 0) {
				printf("Somme des noeuds de l'arbre : %d\n", SommeNoeudArbre(fArbre, racine));
				Gotoxy(0, Getposy() + 1);
			}
			break;

			// Récuperer un noeud
		case 'i':
			if (FileLength(fArbre) != 0) {
				printf("Entrer la valeur à récupérer dans l'arbre : ");
				int val = -1;
				scanf_s("%d", &val);
				int pos = RecupNoeudArbre(fArbre, racine, val);
				if (pos >= 0) {
					Noeud n;
					LireNoeud(fArbre, pos, &n);
					printf("noeud trouvé : position %d valeur %d\n", pos, n.val);
				}
				else
					printf("pas de noeud correspondant à %d\n", val);
				Gotoxy(0, Getposy() + 1);
			}
			break;

			// Sauver et charger l'arbre le mieux est de copier le fichier
		case 'o':
			if (fArbre) {
				if (CopieFichierArbre(fArbre, racine, "save_arbre.arbre"))
					printf("arbre sauvegardé\n");
				else
					printf("erreur sauvegarde\n");
			}
			else
				printf("pas d'arbre à sauvegarder\n");
			break;

			// Charger un arbre sauvegardé
		case 'p':
		{
			//ConsClear();
			//Menu();
			FILE* copie;
			copie = LoadArbre("save_arbre.arbre");
			AffichageVertical(copie, racine);
			fclose(copie);
			break;
		}
		case 'q':
			fin = 1;
			break;
		}
	}
	//fermeture du fichier
	DestroyArbre(&fArbre);
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
/************************************************
Gestion du fichier
************************************************/
void EcrireNoeud(FILE* f, int pos, Noeud* n)
{
	fseek(f, sizeof(Noeud) * pos, SEEK_SET);
	fwrite(n, sizeof(Noeud), 1, f);
}
void LireNoeud(FILE* f, int pos, Noeud*n)
{
	fseek(f, sizeof(Noeud) * pos, SEEK_SET);
	fread(n, sizeof(Noeud), 1, f);
}
int FileLength(FILE* f)
{
	fseek(f, 0, SEEK_END);
	return ftell(f);
}
/* 
 Ouverture en mode création lecture-écriture du fichier binaire arbre (w+b).
 Le fichier est ainsi réinitialisé à chaque ouverture et  
 son contenu est effacé et la fonction peut servir aussi
 à détruire un arbre existant.
 */
void CreateNewFile(FILE** arbre)
{
	if (*arbre != NULL)
		fclose(*arbre);
	//
	fopen_s(arbre, "arbre.arbre", "w+b");
	if (!*arbre) {
		printf( "création du fichier arbre impossible\n"
				"taper enter pour quitter\n");
		char c = getchar();
		exit(EXIT_FAILURE);
	}
}
/************************************************
Création/destruction arbre
************************************************/
void CreateArbrePlein(FILE*f, int nbNoeud)
{
	if (f) {
		// la racine est en 0
		for (int i = 0, k = 0; i < nbNoeud; i++) {
			Noeud n = { 0 };
			n.val = rand() % 100;
			n.g = ++k < nbNoeud ? k : NOFILS;
			n.d = ++k < nbNoeud ? k : NOFILS;
			EcrireNoeud(f, i, &n);
		}
	}
}
// création arbre aléatoir
int CreateArbreRandom(FILE*f, int* pos, int level)
{
	int res = NOFILS;
	if (level > 0) {
		Noeud n = CreateNoeud(rand() % 100);
		res = *pos;
		//EcrireNoeud(f, res, &n);
		
		(*pos)++;
		if (rand() % 1000 > 250) {
			n.g = CreateArbreRandom(f, pos, level - 1);
		}
		if (rand() % 1000 > 250) {
			n.d = CreateArbreRandom(f, pos, level - 1);
		}
		EcrireNoeud(f, res, &n);
	}
	return res;
}
Noeud CreateNoeud(int val)
{
	return (Noeud) { val, -1, -1 };
}
//TODO
// Arbre ordonné
void CreateArbreOrdonne(FILE*f, int nbNoeud)
{
	Noeud n = CreateNoeud(rand() % 100);
	EcrireNoeud(f, 0, &n);
	for (int i = 1; i < nbNoeud; i++) {
		AjouterFeuille(f, i, CreateNoeud(rand() % 100));
	}
}

void AjouterFeuille(FILE*f, int pos, Noeud nouveau)
{
	int posx, prec;
	Noeud x;

	posx = 0;
	prec = NOFILS;
	while (posx != NOFILS) {
		prec = posx; // conserver la dernière position
		LireNoeud(f, posx, &x);
		posx = (nouveau.val < x.val) ? x.g : x.d; // descente jusque feuille selon valeur
	}
	// en principe arrivée à la bonne position pour la nouvelle valeur,
	// accrocher la nouvelle feuille
	LireNoeud(f, prec, &x);
	if (nouveau.val < x.val) {
		x.g = pos;
		EcrireNoeud(f, prec, &x);
		EcrireNoeud(f, pos, &nouveau);
	}
	else {
		x.d = pos;
		EcrireNoeud(f, prec, &x);
		EcrireNoeud(f, pos, &nouveau);
	}
}

void DestroyArbre(FILE** arbre)
{
	if (*arbre != NULL) {
		fclose(*arbre);
		*arbre = NULL;
	}
}
/************************************************
Parcours arbre
*************************************************/
void ParcoursPrefixe(FILE*f, int r)
{
	if (r != NOFILS) {
		Noeud n;
		LireNoeud(f, r, &n);
		printf("%3d", n.val);
		ParcoursPrefixe(f, n.g);
		ParcoursPrefixe(f, n.d);
	}
}
void ParcoursInfixe(FILE*f, int r)
{
	if (r != NOFILS) {
		Noeud n;
		LireNoeud(f, r, &n);
		ParcoursInfixe(f, n.g);
		printf("%3d", n.val);
		ParcoursInfixe(f, n.d);
	}
}
void ParcoursPostfixe(FILE*f, int r)
{
	if (r != NOFILS) {
		Noeud n;
		LireNoeud(f, r, &n);
		ParcoursPostfixe(f, n.g);
		ParcoursPostfixe(f, n.d);
		printf("%3d", n.val);
	}
}

void ParcoursEnlargeur(FILE*f, int r)
{
	Noeud* file;
	int queue = 0, tete = 0; // queue et tête
	if (r == NOFILS || ! FileLength(f))
		printf("Arbre vide\n");
	else {
		file = (Noeud*)malloc(sizeof(Noeud) * TailleArbre(f, r));
		if (file) {
			// la racine au départ de la file
			Noeud n;
			LireNoeud(f, r, &n);
			file[queue++] = n;
			while (tete != queue) {
				n = file[tete++]; // sortie en tête
				printf("%d ", n.val);
				if (n.g != NOFILS) {
					Noeud g;
					LireNoeud(f, n.g, &g);
					file[queue++] = g; // entrées en queue
				}
				if (n.d != NOFILS) {
					Noeud d;
					LireNoeud(f, n.d, &d);
					file[queue++] = d;
				}
			}
			free(file);
		}
	}
}
/************************************************
Affichage arbre
************************************************/
void AffichageHorizontal(FILE*f, int r, int niveau)
{
	//_filelength() donne la taille d'un fichier en octets et 0 si rien
	if (r == NOFILS || !FileLength(f))
		printf("Arbre vide\n");
	else
		_AffichageHorizontal(f, r, niveau);

}
void _AffichageHorizontal(FILE*f, int r, int niveau)
{
	if (r != NOFILS) {
		for (int i = 0; i < niveau; i++)
			printf("%5s", " ");
		
		Noeud n;
		LireNoeud(f, r, &n);
		printf("%2d\n", n.val);
		_AffichageHorizontal(f, n.g, niveau + 1);
		_AffichageHorizontal(f, n.d, niveau + 1);
	}
}

void AffichageVertical(FILE*f, int r)
{
	if (r == NOFILS || !FileLength(f))
		printf("arbre vide\n");
	else {
		// problème affichage si trop grand : élargir le buffer de la fenêtre
		int hauteur = HauteurArbre(f, r);
		if (hauteur > 4) {
			int more = (6 << hauteur) + 10; // 6 * (2 puissance hauteur) + 10
			ConsBufferMoreWidth(more);
		}
		// dessin de l'arbre
		// trouver la bonne position en y
		int y = Getposy();
		// partir de la marge
		int x = 0;
		_AffichageVertical(f, r, &x, y);
		// position curseur en dessous de l'arbre
		Gotoxy(0, y + hauteur * 2 + 1);
	}
}
void _AffichageVertical(FILE*f, int r, int* x, int y)
{
	if (FileLength(f)!=0 && r != NOFILS) {
		Noeud n = { 0 };
		LireNoeud(f, r, &n);
		_AffichageVertical(f, n.g, x, y + 2);
		*x += 3;
		Gotoxy(*x, y);
		printf("%2d", n.val);
		// en affichant *x à la place de val on peut
		// suivre l'ordre dans lequel se fait le tracé
		//printf("%2d", *x); 
		_AffichageVertical(f, n.d, x, y + 2);
	}
}
/************************************************
Propriétés de l'arbre
*************************************************/
int TailleArbre(FILE*f, int r)
{
	int res = 0;
	Noeud n = { 0 };
	if (FileLength(f) != 0 && r != NOFILS) {
		LireNoeud(f, r, &n);
		res = 1 + TailleArbre(f, n.g) + TailleArbre(f, n.d);
	}
	return res;
}
int HauteurArbre(FILE*f, int r)
{
	int h = 0;
	Noeud n = { 0 };
	if (FileLength(f) != 0 && r != NOFILS) {
		LireNoeud(f, r, &n);
		h = 1 + Max(HauteurArbre(f, n.g), HauteurArbre(f, n.d));
	}
	return h;
}
int Max(int v1, int v2)
{
	return (v1 > v2) ? v1 : v2;
}
int NombreFeuilleArbre(FILE*f, int r)
{
	int nb = 0;
	Noeud n = { 0 };
	if (FileLength(f) != 0 && r != NOFILS) {
		LireNoeud(f, r, &n);
		if (IsFeuilleArbre(n))
			nb = 1;
		else
			nb = NombreFeuilleArbre(f, n.g) + NombreFeuilleArbre(f, n.d);
	}
	return nb;
}
_Bool IsFeuilleArbre(Noeud n)
{
	return n.g == NOFILS && n.d == NOFILS;
}

void ListerFeuilleArbre(FILE*f, int r)
{
	if (FileLength(f) != 0 && r != NOFILS) {
		Noeud n = { 0 };
		LireNoeud(f, r, &n);
		if (IsFeuilleArbre(n))
			printf("%3d", n.val);
		ListerFeuilleArbre(f, n.g);
		ListerFeuilleArbre(f, n.d);
	}
}
int SommeNoeudArbre(FILE*f, int r)
{
	int res = 0;
	if (FileLength(f) != 0 && r != NOFILS) {
		Noeud n = { 0 };
		LireNoeud(f, r, &n);
		res = n.val;
		res += SommeNoeudArbre(f, n.g) + SommeNoeudArbre(f, n.d);
	}
	return res;
}
// la fonction retourne la position du noeud dans le fichier
int RecupNoeudArbre(FILE*f, int r, int val)
{
	// -1 ne peut pas être une position dans le fichier
	// signifie qu'un noeud avec la valeur val n'est pas trouvé
	int res = -1;
	if (FileLength(f) != 0 && r != NOFILS) {
		Noeud n = { 0 };
		LireNoeud(f, r, &n);
		if (n.val == val)
			res = r;
		else {
			res = RecupNoeudArbre(f, n.g, val);
			if (res == -1)
				res = RecupNoeudArbre(f, n.d, val);
		}
	}
	return res;
}
/************************************************
Sauvegarde arbre
************************************************/
// attention le fichier source en entrée est considéré 
// comme ouvert
FILE* CopieFichierArbre(FILE*f, int r, char* path)
{
	// création fichier copie
	FILE* copie = NULL;
	fopen_s(&copie, path, "wb");
	if (!copie) {
		printf("erreur creation copie\n");
		return NULL;
	}
	// récupérer le nombre des noeuds à copier
	int nb = TailleArbre(f, r);
	// se placer au début du fichier source, celui de l'arbre à copier
	fseek(f, 0L, SEEK_SET);
	// copier chaque noeud
	while (nb--) {
		Noeud n;
		if (fread(&n, sizeof(Noeud), 1, f) != 1)
			return NULL;
		if (fwrite(&n, sizeof(Noeud), 1, copie) != 1)
			return NULL;
	}
	fclose(copie);
	return copie;
}
FILE* LoadArbre(char* path)
{
	FILE* f;
	// ouverture en lecture et écriture mais le fichier est sensé 
	// exister. S'il n'existe pas il y a erreur.
	fopen_s(&f, path, "r+b");
	if (!f)
		printf("erreur ouverture fichier save, existe-t-il ?\n");
	return f;
}
/*******************************************************
Tools utilisation de la console
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

