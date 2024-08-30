/*Exercice 4
Repr�senter l'arbre g�n�alogique d'une famille de son choix ou de son invention. 
Les informations peuvent �tre fournies par un fichier texte du style :
Sonia : Paul, Catherine, Benoit ;
Paul : Isabelle, Armand ;
Catherine : Anatole, Elo�se, Brigitte ;
etc.*/

/*
En consid�rant que le fichier des donn�es est correctement constitu�, l'exercice pose au d�part 
trois questions qui n�cessitent des choix :
1) Quelle structure de donn�es adopter sachant qu'il y a plusieurs fa�on de coder un arbre n-aire ?
(tableau de listes chain�es, tableau de structures � deux dimensions, en dynamique avec des pointeurs)
2) Conserver la forme n-aire de l'arbre ou bien traduire en arbre binaire ?
3) Comment r�cup�rer les donn�es sur fichier et les traduire � travers la construction d'un arbre ?


	Notre solution choisit de traduire l'arbre n-aire en arbre binaire.
	La r�cup�ration des donn�es dans le fichier n�cessite un peu de bricolage.
	La traduction de l'arbre n-aire en arbre binaire rend son affichage moins
	facile � lire. La branche � gauche correspond � "fils de" et la branche � 
	droite  correspond � "frere de".

	Attention le fichier doit se terminner avec une ligne vide (retour chariot juste apr�s le dernier ;)

*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

typedef struct Noeud {
	char* nom;
	struct Noeud* fils;  //gauche
	struct Noeud* frere; // droite
}Noeud;

void CreateArbre(FILE* f, Noeud** racine);
char* NextLigne(FILE* f);
int CompteMots(char* ligne);
Noeud* CreateNoeud(char* nom);
void AddFrere(Noeud** n, Noeud* frere);
Noeud* RecupNoeudArbre(Noeud* r, char* nom);
void AffichageVertical(Noeud* r, int* x, int y);
void _AffichageVertical(Noeud* r, int* x, int y);
void DestroyArbre(Noeud** r);
void Gotoxy(int x, int y);

int main()
{
	// pour l'accentuation : ISO 8859-1 Latin 1; Western European (ISO)
	// https://docs.microsoft.com/en-us/windows/console/setconsoleoutputcp
	// https://docs.microsoft.com/fr-fr/windows/desktop/Intl/code-page-identifiers
	SetConsoleOutputCP(28591);

	FILE* f;
	fopen_s(&f, "arbre.dat", "r");
	if (f) {
		Noeud* racine = NULL;
		CreateArbre(f, &racine);
	
		int posx = 0;
		AffichageVertical(racine, &posx, 0);

		DestroyArbre(&racine);

		fclose(f);
	}
	else {
		printf("impossible ouvrir \"arbre.dat\" Enter pour quitter\n");
		char c = getchar();
	}
	
	getchar();
	return 0;
}
/*****************************************************
	R�cup�ration des donn�es sur fichier 
	et construction de l'arbre
******************************************************/
void CreateArbre(FILE* f, Noeud** racine)
{
	// en principe ici le fichier existe et est ouvert en lecture

	
	char* ligne = NextLigne(f);
	if (ligne) {
		// Apr�s r�cup�ration de la ligne courante il s'agit tout d'abord de 
		// dissocier les mots et de les stocker dans un tableau.
		// Ce tableau contient un pointeur NULL en derni�re position d'ou le + 1
		int num = CompteMots(ligne) + 1;
		char** noms = (char**)malloc(sizeof(char*) * num);
		if (noms) {
			// met � 0 (donc NULL) toutes les positions
			memset(noms, 0, sizeof(char*) * num);
			// num sert maintenant � se positionner dans le tableau en commen�ant au d�but
			num = 0;
			// r�cup�ration des noms de la ligne avec strok_s()
			// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strtok-s-strtok-s-l-wcstok-s-wcstok-s-l-mbstok-s-mbstok-s-l?view=vs-2019
			noms[num] = strtok_s(ligne, " :,;\n", &ligne);
			while (noms[num] != NULL)
				noms[++num] = strtok_s(NULL, " :,;\n", &ligne);

			// liste des noeuds freres (de 1 � num)
			Noeud* n = NULL;
			for (int i = 1; noms[i] != NULL; i++)
				AddFrere(&n, CreateNoeud(noms[i]));

			// ajout dans l'arbre
			if (*racine == NULL) {// si rien c'est le nom pour la racine de l'arbre
				*racine = CreateNoeud(noms[0]);
				(*racine)->fils = n; // et le premier frere est son fils
			}
			// si la racine existe
			else {
				// chercher le premier nom dans l'arbre
				Noeud* pos = RecupNoeudArbre(*racine, noms[0]);
				if (pos) { // s'il existe le premier frere de la ligne est fils du noeud trouv�
					pos->fils = n;
				}
			}
			// lib�rer le tableau de noms mais sans toucher aux noms
			free(noms);
		}
		// reprendre tout pour la ligne suivante
		CreateArbre(f, racine);
	}
}
// r�cup�rer une ligne
char* NextLigne(FILE* f)
{
	char rec[2048] = { 0 };
	char* res = NULL;

	fgets(rec, 2048, f);
	size_t nbchar = strlen(rec);
	if (nbchar > 0) {
		rec[nbchar - 1] = '\0'; // suppression '\n' final
		res = (char*)malloc(sizeof(char) * nbchar); 
		if (res)
			strcpy_s(res, nbchar, rec);
	}
	return res;
}
int CompteMots(char* ligne)
{
	int cmpt = 0;
	for (int i = 0; ligne[i] != '\0'; i++)
		if (ligne[i] == ':' || ligne[i] == ',' || ligne[i] == ';')
			cmpt++;
	return cmpt;
}

Noeud* CreateNoeud(char* nom)
{
	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	if (n) {
		n->nom = nom;
		n->fils = NULL;
		n->frere = NULL;
	}
	return n;
}

void AddFrere(Noeud** r, Noeud* frere)
{
	if (*r == NULL)
		*r = frere;
	else {
		Noeud* n = *r;
		while (n->frere != NULL)
			n = n->frere;
		n->frere = frere;
	}
}

Noeud* RecupNoeudArbre(Noeud* r, char* nom)
{
	Noeud* n = NULL;
	if (r != NULL) {
		if (strcmp(r->nom, nom)==0)
			n = r;
		else {
			n = RecupNoeudArbre(r->fils, nom);
			if (n == NULL)
				n = RecupNoeudArbre(r->frere, nom);
		}
	}
	return n;
}
/******************************************************
Affichage arbre
*******************************************************/
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
		_AffichageVertical(r->fils, x, y + 2);
		*x += 12;
		Gotoxy(*x, y);
		printf("%10s", r->nom);
		_AffichageVertical(r->frere, x, y + 2);
	}
}

/*****************************************************
	Destruction de l'arbre
******************************************************/
void DestroyArbre(Noeud** r)
{
	if (*r != NULL) { // parcours postfix�
		DestroyArbre(&(*r)->fils);
		DestroyArbre(&(*r)->frere);
		free(*r);
		*r = NULL;
	}
}
/*******************************************************
Tools utilisation console
*******************************************************/
void Gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };

	// controler que le curseur ne sorte pas du buffer associ�  
	// � la fen�tre pour �viter des comportements ind�finis de  
	// la console ensuite
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h, &info);

	if (c.X < info.dwSize.X && c.Y < info.dwSize.Y)
		SetConsoleCursorPosition(h, c);
}