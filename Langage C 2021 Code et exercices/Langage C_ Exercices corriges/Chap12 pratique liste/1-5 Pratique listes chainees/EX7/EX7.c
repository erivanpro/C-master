/*
Exercice 7
Écrire une fonction de concaténation de deux listes chaînées.
Il y a deux versions de la fonction : l’une détruit les deux listes
données au départ et l'autre préserve ces deux listes. Tester dans un programme.
*/
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include <time.h>

#define NBLIST	2

typedef struct Elem {
	int val;
	struct Elem* suiv;
}Elem;

void Menu(void);
void AddInHead(Elem** prem, Elem* e);
Elem* InitElem();
Elem* CreateListe();
Elem* CopyListe(Elem* l);
Elem* Merge(Elem* l1, Elem* l2); //enchaine l1 avec l2
Elem* ConcatOriginals(Elem** l1, Elem** l2);// détruit les originales
Elem* ConcatCopys(Elem* l1, Elem* l2);// conserve les originales
void DestroyListe(Elem** prem);
void DisplayListe(Elem* prem);

int main()
{
	Elem* L[NBLIST] = { 0 }; //têtes de la liste
	Elem* Concat = NULL;
	int fin = 0;

	srand(time(NULL));
	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
			for (int i = 0; i < NBLIST; i++) {
				if (L[i])
					DestroyListe(L + i);
				L[i] = CreateListe();
				DisplayListe(L[i]);
			}
			break;
			// test de copie des listes
		case 'z':
		{
			for (int i = 0; i < NBLIST; i++) {
				Elem* copie = CopyListe(L[i]);
				DisplayListe(copie);
				DestroyListe(&copie);
			}
		}
		break;

		// Concatene les listes et conserve les originales
		case'e':
			for (int i = 0; i < NBLIST - 1; i++)
				Concat = ConcatCopys(L[i], L[i + 1]);

			printf("Concatenation :\n");
			DisplayListe(Concat);
			printf("Listes originales :\n");
			for (int i = 0; i < NBLIST; i++) {
				DisplayListe(L[i]);
			}
			DestroyListe(&Concat);
			break;
			// Concatene les listes et détruit les originales
		case 'r':
			for (int i = 0; i < NBLIST - 1; i++)
				// attention dans cette version passer l'adresse des pointeurs
				// et non ce que quoi ils pointent
				Concat = ConcatOriginals(L + i, L + i + 1);

			printf("Concatenation :\n");
			DisplayListe(Concat);
			printf("Listes originales :\n");
			for (int i = 0; i < NBLIST; i++) {
				DisplayListe(L[i]);
			}
			DestroyListe(&Concat);
			break;

		case 'q': fin = 'q';
			break;
		}
	}
	for (int i = 0; i < NBLIST; i++)
		DestroyListe(L + i);
	return 0;
}
void Menu()
{
	printf("a : creer deux listes de nb elements, nb aleatoire\n");
	printf("z : Test de copie des listes\n");
	printf("e : Concatene les listes et conserve les originales\n");
	printf("r : Concatene les listes et détruit les originales\n");
	printf("q : quitter\n");
}

Elem* InitElem(int val)
{
	Elem* e = (Elem*)malloc(sizeof(Elem)); // null sur erreur
	if (e) {
		e->val = val;
		e->suiv = NULL;
	}
	return e;
}
void AddInHead(Elem * *prem, Elem * e)
{
	if (e != NULL) {
		e->suiv = *prem;
		*prem = e;
	}
}
Elem* CreateListe()
{
	int nb = 1 + rand() % 20;
	Elem* prem = NULL;
	while (nb--) {
		Elem* e = InitElem(rand() % 1000);
		AddInHead(&prem, e);
	}
	return prem;
}

Elem* CopyListe(Elem * l)
{
	Elem* copie = NULL;
	if (l != NULL) {
		copie = (Elem*)malloc(sizeof(Elem));
		if (copie) {
			copie->val = l->val;
			copie->suiv = NULL;
			Elem* e = copie;
			while (l->suiv != NULL) {
				e->suiv = (Elem*)malloc(sizeof(Elem));
				if (e->suiv) {
					e->suiv->val = l->suiv->val;
					e->suiv->suiv = NULL;

					e = e->suiv;
					l = l->suiv;
				}
				else {
					printf("bad alloc\n");
					break;
				}
			}
		}
		else
			printf("bad alloc\n");
	}
	return copie;
}
// Fusion de deux listes sans destruction d'adresse,
// les originales restent accessibles.
Elem* Merge(Elem * l1, Elem * l2)
{
	Elem* e = l1;
	if (l1) {
		while (l1->suiv != NULL)
			l1 = l1->suiv;
		l1->suiv = l2;
	}
	else
		e = l2;
	return e;
}
// concatene deux copies et détruit les originales 
Elem* ConcatOriginals(Elem * *l1, Elem * *l2)
{
	Elem* c1 = CopyListe(*l1);
	Elem* c2 = CopyListe(*l2);
	DestroyListe(l1);
	DestroyListe(l2);
	return Merge(c1, c2);
}
// concatene deux copies et conserve les originales 
Elem* ConcatCopys(Elem * l1, Elem * l2)
{
	Elem* c1 = CopyListe(l1);
	Elem* c2 = CopyListe(l2);
	return Merge(c1, c2);
}

void DestroyListe(Elem * *prem)
{
	while (*prem) {
		Elem* e = *prem;
		*prem = (*prem)->suiv;
		free(e);
	}
}
void DisplayListe(Elem * prem)
{
	if (prem == NULL)
		printf("liste vide");
	else
		while (prem != NULL) {
			printf("%d->", prem->val);
			prem = prem->suiv;
		}
	putchar('\n');
}