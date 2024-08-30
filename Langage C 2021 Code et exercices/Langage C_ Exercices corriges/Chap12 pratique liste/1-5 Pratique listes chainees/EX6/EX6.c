/*
Exercice 6
Écrire une fonction qui prend en paramètre une liste chaînée et renvoie
une autre liste ayant les mêmes éléments mais dans l'ordre inverse. 
Tester dans un programme.
*/

#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include <time.h>

typedef struct Elem {
	int val;
	struct Elem* suiv;
}Elem;

void Menu(void);
void AddInHead(Elem** prem, Elem* e);
Elem* InitElem();
Elem* CreateListe();
Elem* ReverseCopy(Elem* prem);
void DestroyListe(Elem** prem);
void DisplayListe(Elem* prem);

int main()
{
	Elem* Prem = NULL; //têtes de la liste
	Elem* Copie = NULL;
	int fin = 0;

	srand(time(NULL));
	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
			if (Prem)
				DestroyListe(&Prem);
			Prem = CreateListe();
			DisplayListe(Prem);
			break;

		case'z':
			if (Copie)
				DestroyListe(&Copie);
			Copie = ReverseCopy(Prem);
			DisplayListe(Copie);
			break;
				
		case 'q': fin = 'q';
			break;

		}
	}
	DestroyListe(&Prem);
	return 0;
}
void Menu()
{
	printf("a : creer une liste de nb elements, nb aleatoire\n");
	printf("z : copie en ordre inverse\n");
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
void AddInHead(Elem** prem, Elem*e) 
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
Elem* ReverseCopy(Elem* prem)
{
	Elem* copie = NULL;
	while (prem != NULL) {
		Elem*e = (Elem*)malloc(sizeof(Elem));
		if (!e) {
			printf("bad alloc\n");
			break;
		}
		e->val = prem->val;
		e->suiv = NULL;
		AddInHead(&copie, e);
		prem = prem->suiv;
	}
	return copie;
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
