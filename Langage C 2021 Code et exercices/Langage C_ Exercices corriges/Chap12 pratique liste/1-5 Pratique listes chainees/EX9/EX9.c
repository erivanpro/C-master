/*
Exercice 9
Écrire une fonction qui permet de fusionner deux listes chaînées.La fusion se
fait en alternant un élément d'une liste avec un de l'autre liste.Tous les éléments
des deux listes doivent trouver leur place dans la liste résultante même en cas
de différence de taille.Faire deux versions, une qui conserve les deux listes de
départ et une autre qui les détruit.Tester dans un programme.
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
Elem* CreateList();
Elem* CopyList(Elem* l);
Elem* ToolsMerge(Elem* l1, Elem* l2);
Elem* RetainMerge(Elem* l1, Elem* l2);// détruit les originales
Elem* DestroyMerge(Elem** l1, Elem** l2);// conserve les originales
void DestroyList(Elem** prem);
void DisplayList(Elem* prem);

int main()
{
	Elem* L[NBLIST] = { 0 }; //têtes de la liste
	Elem* Merging = NULL;
	int fin = 0;

	srand((unsigned int)time(NULL));
	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
			for (int i = 0; i < NBLIST; i++) {
				if (L[i])
					DestroyList(L + i);
				L[i] = CreateList();
				DisplayList(L[i]);
			}
			break;
			// test de copie des listes
		case 'z':
		{
			for (int i = 0; i < NBLIST; i++) {
				Elem* copie = CopyList(L[i]);
				DisplayList(copie);
				DestroyList(&copie);
			}
		}
		break;

		// Fusionne les listes et conserve les originales
		case 'e':
			if (Merging)
				DestroyList(&Merging);
			
			for (int i = 0; i < NBLIST - 1; i++)
				Merging = RetainMerge(L[i], L[i + 1]);

			printf("Fusion :\n");
			DisplayList(Merging);
			printf("Listes originales :\n");
			for (int i = 0; i < NBLIST; i++) {
				DisplayList(L[i]);
			}
			DestroyList(&Merging);
			break;

		// Concatene les listes et détruit les originales
		case 'r':
			for (int i = 0; i < NBLIST - 1; i++)
				// attention dans cette version passer l'adresse des pointeurs
				// et non ce sur quoi ils pointent
				Merging = DestroyMerge(L + i, L + i + 1);

			printf("Fusion :\n");
			DisplayList(Merging);
			printf("Listes originales :\n");
			for (int i = 0; i < NBLIST; i++) {
				DisplayList(L[i]);
			}
			DestroyList(&Merging);
			break;
			
		case 'q': fin = 'q';
			break;
		}
	}
	for (int i = 0; i < NBLIST; i++)
		DestroyList(L + i);
	return 0;
}
void Menu()
{
	printf("a : creer deux listes de nb elements, nb aleatoire\n");
	printf("z : Test de copie des listes\n");
	printf("e : Fusionne les listes et conserve les originales\n");
	printf("r : Fusionne les listes et détruit les originales\n");
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
Elem* CreateList()
{
	int nb = rand() % 10;
	Elem* prem = NULL;
	while (nb--) {
		Elem* e = InitElem(rand() % 100);
		AddInHead(&prem, e);
	}
	return prem;
}

Elem* CopyList(Elem * l)
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
// Fusionner deux listes. Attention les deux adresses passées 
// ne devront pas être libérées ensuite. A priori cette fonction
// est uniquement interne au fonctionnement des deux suivantes.
// Il est préférable de ne pas l'appeler en dehors.  

Elem* ToolsMerge(Elem* l1, Elem* l2)
{
	Elem* m = NULL;

	if (l1 == NULL)
		m = l2;
	if (l2 == NULL)
		m = l1;

	if (l1 != NULL && l2 != NULL) {
		m = l1;
		Elem* s1, * s2;
		while (l1 != NULL && l2 != NULL) {
			s1 = l1->suiv;
			s2 = l2->suiv;
			if (l2 != NULL)
				l1->suiv = l2;
			if (s1 != NULL)
				l2->suiv = s1;
			l1 = s1;
			l2 = s2;
		}
	}
	return m;
}

// Fusionne deux copies et conserve les originales 
Elem* DestroyMerge(Elem **l1, Elem **l2)
{
	Elem* c1 = CopyList(*l1);
	Elem* c2 = CopyList(*l2);
	DestroyList(l1);
	DestroyList(l2);
	return ToolsMerge(c1, c2);
}
// concatene deux copies et conserve les originales 
Elem* RetainMerge(Elem * l1, Elem * l2)
{
	Elem* c1 = CopyList(l1);
	Elem* c2 = CopyList(l2);
	return ToolsMerge(c1, c2);
}

void DestroyList(Elem * *prem)
{
	while (*prem) {
		Elem* e = *prem;
		*prem = (*prem)->suiv;
		free(e);
	}
}
void DisplayList(Elem * prem)
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