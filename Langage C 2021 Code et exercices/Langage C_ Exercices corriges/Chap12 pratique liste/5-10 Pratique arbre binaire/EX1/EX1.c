/*Exercice 1
Réaliser un générateur d'arbres binaires DYNAMIQUES contenant des données aléatoires. 
- Générer un arbre. 
- Parcourir l'arbre en profondeur (trois parcours à tester). 
- Parcourir l'arbre en largeur. À chaque fois, afficher l'arbre. 
- Obtenir toutes les propriétés de l'arbre :
	-taille, 
	-hauteur, 
	-nombre de feuilles, 
	-lister les feuilles, 
	-somme des nœuds de l'arbre. 
- Ramener tel ou tel nœud selon une valeur donnée. 
- Sauver l'arbre. 
- Détruire l'arbre. 
- Charger l'arbre.
*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

#define PATH "Save Arbre.bin"

// noeud de l'arbre dynamique
typedef struct Noeud {
	int val;
	struct Noeud* g;
	struct Noeud*d;
}Noeud;

void Menu();
Noeud* CreateNoeud(int val);
void CreateArbreRandom(Noeud** r, int level);
void CreateArbreOrdonne(Noeud** r);
void AjouteFeuille(Noeud** r, Noeud* n);
void DestroyArbre(Noeud** r);

void ParcoursPrefixe(Noeud* r);
void ParcoursInfixe(Noeud* r);
void ParcoursPostfixe(Noeud* r);
void ParcoursEnlargeur(Noeud* r);

void AffichageHorizontal(Noeud* r, int niveau);
void _AffichageHorizontal(Noeud* r, int niveau);
void AffichageVertical(Noeud* r, int* x, int y);
void _AffichageVertical(Noeud* r, int* x, int y);

int TailleArbre(Noeud* r);
int HauteurArbre(Noeud* r);
int Max(int v1, int v2);
int NombreFeuilleArbre(Noeud* r);
_Bool IsFeuilleArbre(Noeud* n);
void ListerFeuilleArbre(Noeud* r);
int SommeNoeudArbre(Noeud* r);
Noeud* RecupNoeudArbre(Noeud* r, int val);

// noeud de l'arbre statique pour sauvegarde
typedef struct S_Noeud {
	int val;
	int g;
	int d;
}S_Noeud;

_Bool SaveArbre(Noeud* r, char*path);
S_Noeud* DynToStat(Noeud* rd);
int _DynToStat(Noeud* rd, S_Noeud* rs, int* pos);
Noeud* LoadArbre(char* path);
Noeud* FileToDyn(FILE* f, int r);
void LireNoeud(FILE* f, int nieme, S_Noeud* enr);

// quelques outils annexes
void Gotoxy(int x, int y);
int Getposy();
int Getposx();
_Bool ConsClearTo(int bcolor, int fcolor, char lettre);
_Bool Blit(CHAR_INFO* dat, SMALL_RECT* datsrc, SMALL_RECT* consdest);
_Bool ConsClear();
_Bool ConsBufferResize(int width, int height);

int main()
{
	int fin = 0;
	srand((unsigned)time(NULL));

	// pour l'accentuation : ISO 8859-1 Latin 1; Western European (ISO)
	// https://docs.microsoft.com/en-us/windows/console/setconsoleoutputcp
	// https://docs.microsoft.com/fr-fr/windows/desktop/Intl/code-page-identifiers
	SetConsoleOutputCP(28591);
	
	// l'arbre
	Noeud* Racine = NULL; // important
	int hauteur;

	Menu();
	while (!fin) {
		switch (_getch()) {
			// création arbre ordonné avec affichage horizontal
			case 'a':
				ConsClear();
				Menu();
				if (Racine != NULL)
					DestroyArbre(&Racine);

				Racine = CreateNoeud(rand() % 100);
				hauteur = 2 + rand() % 6;
				if (Racine)
					CreateArbreRandom(&Racine, hauteur);
				AffichageHorizontal(Racine, 0); // niveau 0 au départ
				putchar('\n');
				break;

			// création arbre aléatoire avec affichage vertical
			case 'z':
			{
				ConsClear();
				Menu();
				if (Racine != NULL)
					DestroyArbre(&Racine);

				Racine = CreateNoeud(rand() % 100);
				// au delà d'une hauteur de 4 l'arbre ne tient plus dans la console
				// ce qui nécessite d'augmenter la taille horizontales du buffer. 
				hauteur = 2 + rand() % 6;
				if (hauteur > 4) {
					int more = (6 << hauteur) + 10; // 6 * (2 puissance hauteur) + 10
					ConsBufferResize(more, 1000);
				}
				if (Racine)
					CreateArbreRandom(&Racine, hauteur);
			
				int posy = Getposy();
				int posx = 0;
				AffichageVertical(Racine, &posx, Getposy());
				Gotoxy(0, posy + 4 * 2 + 1);
				/*REMARQUE : 
				Redimensionner la fenêtre console pendant le fonctionnement du programme 
				entraine un redimenssionnement du buffer qui brouille l'affichage de l'arbre. 
				Malheureusement pour l'heure je ne dispose pas d'un moyen simple d'empêcher 
				le redimensionnement de la console*/
			}
			break;

			// Création arbre ordonné   + affichage vertical
			case 'e':
			{
				ConsClear();
				Menu();
				if (Racine != NULL)
					DestroyArbre(&Racine);

				CreateArbreOrdonne(&Racine);
				// problème d'affichage si arbre trop grand : élargir le buffer de la console
				int hauteur = HauteurArbre(Racine);
				if ( hauteur > 4) {
					int more = (6 << hauteur) + 10; // 6 * (2 puissance hauteur) + 10
					ConsBufferResize(more, 1000);
				}
			
				int posy = Getposy();
				int posx = 0;
				AffichageVertical(Racine, &posx, posy);
				Gotoxy(0, posy + hauteur * 2 + 1);
			}
				break;

			// les parcours
			case 'r':
				if (Racine) {
					printf("Prefixé  : ");
					ParcoursPrefixe(Racine);
					putchar('\n');
					printf("Infixé   : ");
					ParcoursInfixe(Racine);
					putchar('\n');
					printf("Postfixé : ");
					ParcoursPostfixe(Racine);
					putchar('\n');
					printf("Parcours en largeur, par niveau : ");
					ParcoursEnlargeur(Racine);
					putchar('\n');
				}
				else
					printf("pas d'arbre\n");
				Gotoxy(0, Getposy() + 1);
				break;

			//Taille, hauteur, nombre de feuilles, liste des feuilles
			case 't':
				printf("Taille : %d\n", TailleArbre(Racine));
				printf("Hauteur : %d\n", HauteurArbre(Racine));
				printf("Nombre de feuilles : %d\n", NombreFeuilleArbre(Racine));
				printf("Liste des feuilles de l'arbre : ");
				ListerFeuilleArbre(Racine);
				putchar('\n');
				Gotoxy(0, Getposy() + 1);
				break;
			
			// Somme des noeuds
			case 'y':
				printf("Somme des noeuds de l'arbre : %d\n", SommeNoeudArbre(Racine));
				Gotoxy(0, Getposy() + 1);
				break;

			// Récuperer un noeud
			case 'u':
			{
				printf("Entrer la valeur à récupérer dans l'arbre : ");
				int val = -1;
				scanf_s("%d", &val);
				Noeud* n = RecupNoeudArbre(Racine, val);
				if (n)
					printf("noeud trouvé : adresse %p valeur %d\n", n, n->val);
				else
					printf("pas de noeud correspondant à %d\n", val);
				Gotoxy(0, Getposy() + 1);
			}
				break;
			
			// Sauver l'arbre
			case 'i':
				ConsClear();
				Menu();
				if (SaveArbre(Racine, PATH))
					printf("Sauvegarde effectuée\n");
				else
					printf("erreur sauvegarde\n");
				Gotoxy(0, Getposy() + 1);
				break;
			
			// Charger l'arbre
			case 'o':
				if (Racine) {
					ConsClear();
					Menu();
					DestroyArbre(&Racine);
				}
				printf("Load : \n");
				Racine = LoadArbre(PATH);
				if (!Racine) {
					printf("erreur chargement arbre\n");
					Gotoxy(0, Getposy() + 1);
				}
				else {
					int posy = Getposy();
					int posx = 0;
					AffichageVertical(Racine, &posx, Getposy());
					Gotoxy(0, posy + HauteurArbre(Racine) * 2 + 1);
				}
				break;

			case 'q':
				fin = 1;
				break;
		}
	}
	DestroyArbre(&Racine);
	return 0;
}

void Menu()
{
	//Gotoxy(0, 0);
	printf("a : Création arbre aléatoire + affichage horizontal\n");
	printf("z : Création arbre aléatoire + affichage vertical\n");
	printf("e : Création arbre ordonné   + affichage vertical\n");
	printf("r : Parcours en profondeur(préfixé, infixé, postfix) et en largeur (par niveau)\n");
	printf("t : Taille, hauteur, nombre de feuilles, liste des feuilles\n");
	printf("y : Somme des noeuds\n");
	printf("u : Récuperer un noeud\n");
	printf("i : Sauver l'arbre\n");
	printf("o : Charger l'arbre\n");
	printf("q : Quitter\n");
}
/******************************************************
Création/destruction arbre
*******************************************************/
Noeud* CreateNoeud(int val)
{
	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	if (n) {
		n->val = val;
		n->g = NULL;
		n->d = NULL;
	}
	return n;
}
// une autre possibilité de création d'arbre aléatoire que celle utilisée dans le livre.
void CreateArbreRandom(Noeud**r, int level)
{
	if (*r != NULL && level-- > 0) {
		if (rand() % 1000 > 200) {  
			(*r)->g = CreateNoeud(rand() % 100);
			CreateArbreRandom(&(*r)->g, level);//fils gauche passé par référence	
		}
		if (rand() % 1000 > 200) {
			(*r)->d = CreateNoeud(rand() % 100);
			CreateArbreRandom(&(*r)->d, level);//fils droit passé par référence
		}
	}
}
void CreateArbreOrdonne(Noeud** r)
{
	int nbnoeud = rand() % 50;
	while (nbnoeud-- > 0) {
		AjouteFeuille(r, CreateNoeud(rand() % 100));
	}
}
void AjouteFeuille(Noeud** r, Noeud* n)
{
	Noeud* x, * prec;
	if (*r == NULL)
		* r = n;
	else {
		x = *r;
		prec = NULL;
		while (x != NULL) {
			prec = x; // conserver la dernière position
			x = (n->val < x->val) ? x->g : x->d; // descente jusque feuille selon valeur
		}
		// en principe arrivée à la bonne position pour la nouvelle valeur,
		// accrocher la nouvelle feuille
		if (n->val < prec->val)
			prec->g = n;
		else
			prec->d = n;
	}
}
void DestroyArbre(Noeud** r)
{
	if (*r != NULL) { // parcours postfixé
		DestroyArbre(&(*r)->g);
		DestroyArbre(&(*r)->d);
		free(*r);
		*r = NULL;
	}
}
/******************************************************
Parcours arbre
*******************************************************/
void ParcoursPrefixe(Noeud* r)
{
	if (r != NULL) {
		printf("%3d", r->val);
		ParcoursPrefixe(r->g);
		ParcoursPrefixe(r->d);
	}
}
void ParcoursInfixe(Noeud* r)
{
	if (r != NULL) {
		ParcoursInfixe(r->g);
		printf("%3d", r->val);
		ParcoursInfixe(r->d);
	}
}
void ParcoursPostfixe(Noeud* r)
{
	if (r != NULL) {
		ParcoursPostfixe(r->g);
		ParcoursPostfixe(r->d);
		printf("%3d", r->val);
	}
}
void ParcoursEnlargeur(Noeud* r)
{
	Noeud** file;
	int q = 0, t = 0; // queue et tête
	if (r == NULL)
		printf("Arbre vide\n");
	else {
		file = (Noeud **)malloc(sizeof(Noeud*) * TailleArbre(r));
		if (file) {
			// la racine au départ de la file
			file[q++] = r;
			while (t != q) {
				r = file[t++]; // sortie en tête
				printf("%d ", r->val);
				if(r->g)
					file[q++] = r->g; // entrées en queue
				if(r->d)
					file[q++] = r->d;
			}
			free(file);
		}
	}
}
/******************************************************
Affichage arbre
*******************************************************/
void AffichageHorizontal(Noeud* r, int niveau)
{
	if (r == NULL)
		printf("Arbre vide\n");
	else
		_AffichageHorizontal(r, niveau);

}
void _AffichageHorizontal(Noeud* r, int niveau)
{
	if (r != NULL) {
		for (int i = 0; i < niveau; i++)
			printf("%5s", " ");
		printf("%2d\n", r->val);
		_AffichageHorizontal(r->g, niveau + 1);
		_AffichageHorizontal(r->d, niveau + 1);
	}
}
void AffichageVertical(Noeud* r, int* x, int y)
{
	if (r == NULL)
		printf("arbre vide\n");
	else
		_AffichageVertical(r, x, y);
}
void _AffichageVertical(Noeud* r, int* x, int y)
{
	if (r != NULL) {
		_AffichageVertical(r->g, x, y + 2);
		*x += 3;
		Gotoxy(*x, y);
		printf("%2d", r->val);
		// en affichant *x à la place de val on peut
		// suivre l'ordre dans lequel se fait le tracé
		//printf("%2d", *x); 
		_AffichageVertical(r->d, x, y + 2);
	}
}
/******************************************************
Propriétés de l'arbre
*******************************************************/
int TailleArbre(Noeud* r)
{
	int res = 0;
	if (r != NULL)
		res = 1 + TailleArbre(r->g) + TailleArbre(r->d);
	return res;
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
int NombreFeuilleArbre(Noeud* r)
{
	int nb = 0;
	if (r != NULL) {
		if (IsFeuilleArbre(r))
			nb = 1;
		else
			nb = NombreFeuilleArbre(r->g) + NombreFeuilleArbre(r->d);
	}
	return nb;
}
_Bool IsFeuilleArbre(Noeud* n)
{
	return n->g == NULL && n->d == NULL;
}

void ListerFeuilleArbre(Noeud* r)
{
	if (r != NULL) {
		if (IsFeuilleArbre(r))
			printf("%3d", r->val);
		ListerFeuilleArbre(r->g);
		ListerFeuilleArbre(r->d);
	}
}
int SommeNoeudArbre(Noeud* r)
{
	int res = 0;
	if (r) {
		res = r->val;
		res += SommeNoeudArbre(r->g) + SommeNoeudArbre(r->d);
	}
	return res;
}

Noeud* RecupNoeudArbre(Noeud* r, int val)
{
	Noeud* n = NULL;
	if (r != NULL) {
		if (r->val == val)
			n = r;
		else {
			n = RecupNoeudArbre(r->g, val);
			if (n == NULL)
				n = RecupNoeudArbre(r->d, val);
		}
	}
	return n;
}
/******************************************************
Sauvegarde arbre
*******************************************************/
_Bool SaveArbre(Noeud* rd, char*path)
{
	_Bool res = TRUE;
	if (rd != NULL) {
		FILE* f = NULL;
		fopen_s(&f, path, "wb");
		if (f != NULL) {
			S_Noeud* rs = DynToStat(rd);
			if (rs != NULL)
				fwrite(rs, sizeof(S_Noeud), TailleArbre(rd), f);
			else {
				printf("Erreur conversion dynamique en statique\n");
				res = FALSE;
			}
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
S_Noeud* DynToStat(Noeud* rd)
{
	S_Noeud* rs = (S_Noeud*)malloc(sizeof(S_Noeud) * TailleArbre(rd));
	if (rs) {
		int pos = 0;
		_DynToStat(rd, rs, &pos);
	}
	return rs;
}
int _DynToStat(Noeud*rd,S_Noeud*rs, int* pos )
{
	int res = -1;
	if (rd != NULL) {
		res = *pos;
		(*pos)++;
		rs[res].val = rd->val;
		rs[res].g = _DynToStat(rd->g, rs, pos);
		rs[res].d = _DynToStat(rd->d, rs, pos);
	}
	return res;
}

Noeud* LoadArbre(char* path)
{
	FILE* f;
	Noeud* rd = NULL;
	fopen_s(&f, path, "rb");
	if (f != NULL) {
		rd = FileToDyn(f, 0);
		fclose(f);
	}
	else
		printf("erreur ouverture fichier\n");
	return rd;
}
Noeud* FileToDyn(FILE* f, int r)
{
	Noeud* n = NULL;
	S_Noeud enr;
	if (r != -1) {
		LireNoeud(f, r, &enr);
		n = (Noeud*)malloc(sizeof(Noeud));
		if (n) {
			n->val = enr.val;
			n->g = FileToDyn(f, enr.g);
			n->d = FileToDyn(f, enr.d);
		}
	}
	return n;
}
void LireNoeud(FILE* f, int nieme, S_Noeud* enr)
{
	fseek(f, sizeof(S_Noeud) * nieme, SEEK_SET);
	fread(enr, sizeof(S_Noeud), 1, f);
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
		
	if (c.X < info.dwSize.X && c.Y < info.dwSize.Y )
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
/*
	Augmenter la taille buffer de la fenêtre console. Seule la
	partie mémoire est augmentée, la partie visible de la fenêtre 
	reste la même (des ascenseurs apparaissent pour la verticale 
	et l'horizontale).
*/
_Bool ConsBufferResize(int width, int height)
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
	if (width > info.dwSize.X) {
		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}

	return TRUE;
}
