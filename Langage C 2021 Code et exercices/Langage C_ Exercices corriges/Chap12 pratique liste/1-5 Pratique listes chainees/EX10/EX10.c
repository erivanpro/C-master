/*
Exercice 10
Écrire une fonction qui prend en entrée une liste chaînée d'entiers et qui ressort
deux listes chaînées, une pour les nombres pairs et une autre pour les nombres impairs.
La liste initiale est détruite.Tester dans un programme.
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
void AddInHead(Elem** prem, Elem** dern, Elem* e);
void AddInBack(Elem** prem, Elem** dern, Elem* e);
Elem* InitElem();
void CreateList(Elem** prem, Elem** dern);
void SplitList(Elem** prem, Elem** pair, Elem** impair);
void _DestroyList(Elem** prem);
void DestroyList(Elem** prem, Elem** dern);
void DisplayList(Elem* prem);

int main()
{
	int fin = 0;
	//les listes sont déterminées par un premier, la tête, mais aussi
	//un dernier qui facilite l'accroche de nouveaux éléments à la fin.
	// (et puis ça change un peu par rapport aux exercices précédents)
	Elem* Prem = NULL, * Dern = NULL;
	Elem* Pair = NULL, * Impair = NULL;

	srand((unsigned int)time(NULL));
	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
			CreateList(&Prem, &Dern);
			DisplayList(Prem);
			break;
			
		case 'z':
			SplitList(&Prem, &Pair, &Impair);

			printf("liste orginale : ");
			DisplayList(Prem);
			printf("liste pair : ");
			DisplayList(Pair);
			printf("liste impair : ");
			DisplayList(Impair);

			_DestroyList(&Pair);
			_DestroyList(&Impair);
			break;

		case 'q': fin = 'q';
			break;
		}
	}
	DestroyList(&Prem,&Dern);
	return 0;
}
void Menu()
{
	printf("a : creer une liste de nb elements, nb aleatoire\n");
	printf("z : scinder en deux listes de nombres, les paires et impaires\n");
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
void AddInHead(Elem**prem, Elem**dern, Elem * e)
{
	if (e != NULL) {
		e->suiv = *prem;
		*prem = e;
		if ((*prem)->suiv == NULL)// si un seul
			*dern = *prem;
	}
}
void AddInBack(Elem**prem, Elem**dern, Elem*e)
{
	if (e != NULL) {
		if (*dern == NULL ) 
			*prem = *dern = e;
		else {
			(*dern)->suiv = e;
			*dern = e;
		}
	}
}
void CreateList(Elem**prem, Elem**dern)
{
	int nb = rand() % 10;
	while (nb--) {
		Elem* e = InitElem(rand() % 100);
		AddInHead(prem,dern, e);
	}
}
void SplitList(Elem** prem, Elem** pair, Elem** impair)
{
	Elem* dernImpair = NULL;
	Elem* dernPair = NULL;
	while (*prem != NULL) {

		// récupérer chaque élément depuis le premier
		Elem* e = *prem;
		*prem = (*prem)->suiv;
		e->suiv = NULL;

		if (e->val % 2) // si impair
			AddInBack(impair, &dernImpair, e);
		else
			AddInBack(pair, &dernPair, e);
	}
}
void _DestroyList(Elem** prem)
{
	while (*prem) {
		Elem* e = *prem;
		*prem = (*prem)->suiv;
		free(e);
	}
}
void DestroyList(Elem **prem, Elem**dern)
{
	_DestroyList(prem);
	*dern = NULL;
}
void DisplayList(Elem *prem)
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