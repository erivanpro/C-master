/*
Exercice 4
L'objectif est de faire une suite de nombres entiers sous la forme d'une liste chaînée.
Le programme à faire :
– initialise chaque entier avec une valeur aléatoire comprise entre 0 et 1000
– affiche une liste de nb entiers, nb entré par l'utilisateur
– peut détruire la liste afin d'en faire une nouvelle
– calcule la somme des entiers de la liste
– met à - 1 le maillon nb / 2 de la liste
– passe en négatif tous les maillons inférieurs à un seuil déterminé par l'utilisateur. 
  Afficher le résultat
– efface tous les maillons dont la valeur est comprise entre un seuil haut et un seuil 
  bas entrés par l'utilisateur. Afficher le résultat
– duplique les maillons qui ont la même valeur qu'une valeur entrée par l'utilisateur.
  Afficher le résultat
– sauve la liste sur fichier(reportez-vous au chapitre Les pointeurs sur les fichiers)
– charge une liste sauvegardée
*/

#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>

#define SAVEPATH "save.liste"

typedef struct Elem{
	int val;
	struct Elem*suiv;
}Elem;

void Menu(void);
Elem* InitElem(void);
void Affiche(Elem*prem);
void AjouteTete(Elem**prem, Elem*e);
int SaisieNombre(const char*msg);
Elem* ConstructListe(void);
void SuppElem(Elem**prem);
void DestroyListe(Elem**prem);
int CalculSomme(Elem*prem);
void MilieuAMoinsUn(Elem*prem);
void Negatise(Elem*prem, int seuil);
void EffaceEntre(Elem** prem, int sbas, int shaut);
void Dupplique(Elem*prem, int val);
void SaveListe(Elem* prem);
Elem* LoadListe(void);

int main()
{
	Elem*Prem = NULL; //tête de la liste

	int fin = 0;

	srand(time(NULL));
	Menu();
	while (fin != 'q')
	{
		switch (_getch()) {
		case 'a':
			if (Prem != NULL)
				DestroyListe(&Prem);
			Prem = ConstructListe();
			Affiche(Prem);
			break;
		case 'z':
			DestroyListe(&Prem);
			Affiche(Prem);
			break;
		case 'e':
			printf("Somme : %d\n", CalculSomme(Prem));
			break;
		case 'r':
			MilieuAMoinsUn(Prem);
			Affiche(Prem);
			break;
		case 't':
		{
			int seuil = SaisieNombre("Seuil : ");
			Negatise(Prem, seuil);
			Affiche(Prem);
			break;
		}
		case 'y':
		{
			int sbas = SaisieNombre("Seuil bas : "); 
			int shaut = SaisieNombre("Seuil haut : ");
			EffaceEntre(&Prem, sbas, shaut);
			Affiche(Prem);
		}
			break;
		case 'u':
		{
			int val = SaisieNombre("Val a duppliquer / ");
			Dupplique(Prem, val);
			Affiche(Prem);
			break;
		}
		case 'i':
			SaveListe(Prem);
			break;
		case 'o':
			if (Prem != NULL)
				DestroyListe(&Prem);
			Prem = LoadListe();
			Affiche(Prem);
			break;
		case 'p':
			break;
		case 'm':	
			Menu();
			break;
		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyListe(&Prem);
	return 0;
}

void pause()
{
	printf("Appuyez sur enter pour continuer\n");
	getchar();
}
void Menu() 
{
	printf("a : affiche une liste de nb entiers, nb entre par l'utilisateur\n");
	printf("z : peut detruire la liste afin d'en faire une nouvelle\n");
	printf("e : calcule la somme des entiers de la liste\n");
	printf("r : met a - 1 le maillon nb / 2 de la liste\n");
	printf("t : passe en negatif tous les maillons inferieurs a un seuil determine par l'utilisateur.\n");
	printf("y : efface tous les maillons dont la valeur est comprise entre un seuil haut et un seuil"
		   "    bas entres par l'utilisateur. Afficher le resultat\n");
	printf("u : duplique les maillons qui ont la meme valeur qu'une valeur entree par l'utilisateur\n");
	printf("i : sauve la liste sur fichier(reportez-vous au chapitre Les pointeurs sur les fichiers)\n");
	printf("o : charge une liste sauvegardee\n");
	//printf("p : menu\n");
	printf("q : quitter\n");
}
//initialise chaque entier avec une valeur aléatoire comprise entre 0 et 1000
Elem* InitElem()
{
	Elem* e = (Elem*)malloc(sizeof(Elem)); // null sur erreur
	if (e) {
		e->val = rand() % 1000;
		e->suiv = NULL;
	}
	return e;
}
// affiche une liste 
void Affiche(Elem*prem) 
{
	if (prem == NULL)
		printf("liste vide");
	else {
		while (prem != NULL) {
			printf("%d->", prem->val);
			prem = prem->suiv;
		}
	}
	putchar('\n');
}
// 
void AjouteTete(Elem**prem, Elem*e) 
{
	e->suiv = *prem;
	*prem = e;
}
//
int SaisieNombre(const char*msg)
{
	int nb = 0;
	int res = 0;
	while(res==0) {
		printf(msg);
		res = scanf_s("%d", &nb);
		rewind(stdin);
	}
	return nb;
}
// construit une liste de nb entiers, nb entré par l'utilisateur
Elem* ConstructListe() 
{
	Elem*e = NULL;
	int nb = SaisieNombre("nombre de maillons : ");
	while (nb--)
		AjouteTete(&e, InitElem());
	return e;
}
// peut détruire la liste afin d'en faire une nouvelle
void SuppElem(Elem**prem)
{
	if (*prem != NULL) {
		Elem*e = *prem;
		*prem = (*prem)->suiv;
		free(e);
	}
}
void DestroyListe(Elem**prem) 
{
	while (*prem != NULL)
		SuppElem(prem);
}
// calcule la somme des entiers de la liste
int CalculSomme(Elem*prem)
{
	int res = 0;
	while (prem != NULL) {
		res += prem->val;
		prem = prem->suiv;
	}
	return res;
}
// met à - 1 le maillon nb / 2 de la liste
int Compte(Elem*prem)
{
	int nb = 0;
	while (prem != NULL) {
		nb++;
		prem = prem->suiv;
	}
	return nb;
}
void MilieuAMoinsUn(Elem*prem) 
{
	if (prem != NULL) {
		int nb = Compte(prem) / 2;
		while (nb--)
			prem = prem->suiv;
		prem->val = -1;
	}
}
// passe en négatif tous les maillons inférieurs à un seuil déterminé par l'utilisateur.
//  Afficher le résultat
void Negatise(Elem*prem,int seuil) 
{
	while (prem != NULL) {
		if (prem->val < seuil && prem->val >= 0)
			prem->val *= -1; 
		prem = prem->suiv;
	}
}
// efface tous les maillons dont la valeur est comprise entre un seuil haut et un seuil
// bas entrés par l'utilisateur. Afficher le résultat
void EffaceEntre(Elem**prem, int sbas, int shaut)
{
	// au début
	while (*prem != NULL && (*prem)->val > sbas && (*prem)->val < shaut)
			SuppElem(prem);
	// ensuite
	if (*prem != NULL) {
		Elem* prec = *prem;
		Elem* e = (*prem)->suiv;
		while (e != NULL) {
			if (e->val > sbas && e->val < shaut) {
				prec->suiv = e->suiv;
				free(e);
				e = prec->suiv;
			}
			else {
				prec = e;
				e = e->suiv;
			}
		}
	}
}

// duplique les maillons qui ont la même valeur qu'une valeur entrée par l'utilisateur.
// Afficher le résultat
void Dupplique(Elem*prem, int val)
{
	while (prem != NULL) {
		if (prem->val == val) {
			Elem* e = (Elem*)malloc(sizeof(Elem));
			if (e) {
				e->val = val;
				e->suiv = prem->suiv;
				prem->suiv = e;
				//l'ajout se faisant après, pour éviter la dupplication de la dupplication
				//il faut passer au suivant ici
				prem = prem->suiv;
			}
			else
				break;
		}
		prem = prem->suiv;
	}
}

// sauve la liste sur fichier(reportez-vous au chapitre Les pointeurs sur les fichiers)
void SaveListe(Elem* prem)
{
	FILE* f = NULL;
	fopen_s(&f, SAVEPATH, "wb");
	if (f) {
		while (prem != NULL) {
			fwrite(prem, sizeof(Elem), 1, f);
			prem = prem->suiv;
		}
		fclose(f);
		printf("Sauvegarde effectuee\n");
	}
	else
		printf("erreur save\n");
}
// charge une liste sauvegardée (la liste se trouve inversée parce que 
// l'ajout se fait en tête, le premier devient dernier))
Elem* LoadListe()
{
	FILE* f = NULL;
	Elem* prem = NULL;

	fopen_s(&f, SAVEPATH, "rb");
	if (f) {

		int trouve = 1;
		while (trouve) {
			Elem* e = (Elem*)malloc(sizeof(Elem));
			if (e) {
				trouve = fread(e, sizeof(Elem), 1, f);
				if (trouve) {
					e->suiv = NULL; // ne pas oublier
					AjouteTete(&prem, e);
				}
				else
					free(e);
			}
		}
		fclose(f);
	}
	else
		printf("erreur load \n");
	return prem;
}