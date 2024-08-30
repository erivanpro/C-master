/*
Exercice 5
L'objectif est d'écrire les deux fonctions suivantes :
la première permet de transformer en liste chaînée un tableau dynamique
de nb éléments. La seconde transforme à l'inverse une liste chaînée de nb 
éléments en un tableau dynamique.Écrire un programme de test.
*/

// Ces questions peuvent être abordées de différentes façons qui dépendent
// des conditions que l'on se donne au départ. 
// Le programme suivant va au plus simple. Des améliorations sont possibles :
// - pour le tableau utiliser une struct qui regroupe int*tab pour l'allocation 
//   dynamique et int nb pour le nombre d'éléments
// - eventuellement avoir une liste de Elem  et un tableau de Elem afin de 
//   disposer du même ensemble comme tableau ou comme liste (chaque élément 
//   du tableau étant relié à un autre présent aussi dans le tableau)

#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include <time.h>

typedef struct Elem {
	int val;
	struct Elem* suiv;
}Elem;

void Menu(void);
void CreateTableau(int**t, int*nb);
void DestroyTableau(int**t, int* nb);
void AfficheTableau(int t[], int nb);
Elem* ConvertTableauEnListe(int t[], int nb);
Elem* InitElem();
Elem* CreateListe();
void DestroyListe(Elem** prem);
void AfficheListe(Elem* prem);
void ConvertListeEnTableau(Elem* prem, int** t, int* nb);


int main()
{
	Elem* Prem = NULL; //tête de la liste
	int* Tab = NULL; // tableau dynamique 
	int nb = 0;  // nombre éléments du tableau
	int fin = 0;

	srand(time(NULL));
	Menu();
	while (fin != 'q'){

		switch (_getch()) {
		case 'a' :
			if (Tab)
				DestroyTableau(&Tab, &nb);
			CreateTableau(&Tab,&nb);
			AfficheTableau(Tab, nb);
			break;
		case'z':
			if (Prem)
				DestroyListe(&Prem);
			Prem = CreateListe();
			AfficheListe(Prem);
			break;
		case 'e':
		{
			Elem* p = ConvertTableauEnListe(Tab, nb);
			AfficheListe(p);
			DestroyListe(&p);
		}
			break;
		case 'r':
		{
			int *tab=NULL, nb = 0; // nb local à ce bloc, masque celui du main
			ConvertListeEnTableau(Prem, &tab, &nb);
			AfficheTableau(tab, nb);
			DestroyTableau(&tab, &nb);
		}
			break;
		case 'q': fin = 'q'; 
			break;

		}
	}
	DestroyTableau(&Tab, &nb);
	DestroyListe(&Prem);
	return 0;
}
void Menu()
{
	printf("a : creer un tableau de nb elements, nb aleatoire\n");
	printf("z : creer une liste de nb elements, nb aleatoire\n");
	printf("e : convertir tableau en liste\n");
	printf("r : convertir liste en tableau\n");
	printf("q : quitter\n");
}

void CreateTableau(int**t, int*nb)
{
	*nb = 1 + rand() % 20;
	*t = (int*)malloc(sizeof(int) * (*nb));
	if (*t) {
		for (int i = 0; i < *nb; i++)
			(*t)[i] = rand() % 1000; // attention parenthèses pour priorité
	}
}
void DestroyTableau(int**t, int*nb)
{
	*nb = 0;
	if (*t != NULL) {
		free(*t);
		*t = NULL;
	}
}
void AfficheTableau(int t[], int nb)
{
	if (nb) {
		for (int i = 0; i < nb; i++)
			printf("[%d]", t[i]);
	}
	else
		printf("[tableau vide]");
	putchar('\n');
}
Elem* ConvertTableauEnListe(int t[], int nb)
{
	Elem* prem = NULL;
	while (--nb >= 0) {
		Elem* e = InitElem(t[nb]);
		e->suiv = prem;
		prem = e;
	}
	return prem;
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
Elem* CreateListe() 
{
	int nb = 1 + rand() % 20;
	Elem* prem = NULL;
	while (nb--) { 
		Elem*e = InitElem(rand()%1000);
		if (e) {
			e->suiv = prem;
			prem = e;
		}
		else {
			printf("erreur creation liste\n");
			break;
		}
	}
	return prem;
}
void DestroyListe(Elem** prem)
{
	while (*prem) {
		Elem* e = *prem;
		*prem = (*prem)->suiv;
		free(e);
	}
}
void AfficheListe(Elem* prem)
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
void ConvertListeEnTableau(Elem* prem, int** t, int* nb) 
{
	if (prem != NULL) {
		// pour allouer le tableau il faut compter le nombre d'éléments de la iste
		Elem* p = prem;
		while (p != NULL) {
			(*nb)++;
			p = p->suiv;
		}
		*t = (int*)malloc(sizeof(int) * (*nb));
		if (*t) {
			for (int i = 0; i < *nb; i++) {
				(*t)[i] = prem->val;
				prem = prem->suiv;
			}
		}
	}
	else {
		// dans le cas d'une liste vide
		*t = NULL;
		*nb = 0;
	}
}

