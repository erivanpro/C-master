/*
Exercice 8
Écrire une fonction qui détermine si une liste chaînée d'entiers est triée ou
non en ordre croissant.
Écrire une fonction qui insère un élément à sa place dans une liste chaînée triée.
Tester dans un programme.
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // _getch
#include <time.h>

enum{FALSE,TRUE};

// J'ai utilisé une liste doublement chainée mais finalement
// ce n'est pas très utile.
typedef struct Elem 
{
	int val;
	struct Elem* prec, *suiv;
}Elem;

void Menu(void);
Elem* CreateElem(int val);
void InsertElem(Elem** prem, Elem* e);
void CreateListe(Elem** prem, int nb);
void DisruptListe(Elem* prem);
_Bool IncreasingList(Elem* prem);
void DisplayListe(Elem* prem);
void DestroyListe(Elem** prem);

int main()
{
	int fin = 0;
	Elem* Prem = NULL;  // ATTENTION, ne pas oublier !

	srand(time(NULL));
	Menu();
	while (fin != 'q') {

		switch (_getch()) {
			// crée une liste aléatoire ordonnée de nb éléments
			case 'a' : 
				if (Prem != NULL)
					DestroyListe(&Prem);
				CreateListe(&Prem, 1 + rand() % 20);
				DisplayListe(Prem);
				break;
			// insérer un élément
			case 'z':
			{
				int val = 0;
				printf("Entrez une valeur :\n");
				scanf_s("%d", &val);
				Elem* e = CreateElem(val);
				InsertElem(&Prem, e);
				DisplayListe(Prem);
			}
			break;
			// désorganiser une liste
			case 'e':
				DisruptListe(Prem);
				DisplayListe(Prem);
				break;
			
			// Diagnostiquer une liste
			case 'r':
				printf("%s",IncreasingList(Prem) ? "Croissante : " : "Non croissante : ");
				DisplayListe(Prem);
				break;

			case 'q':
				fin = 'q'; 
				break;
		}

	}
	DestroyListe(&Prem);
	return 0;
}
void Menu()
{
	printf("a : creer une listes de nb elements, nb aleatoire\n");
	printf("z : Inserer un element\n");
	printf("e : Deorganiser une liste\n");
	printf("r : Diagnostiquer une liste\n");
	printf("q : quitter\n");
}
Elem* CreateElem(int val)
{
	Elem* e = (Elem*)malloc(sizeof(Elem));
	if (e) {
		e->suiv = e->prec = NULL;
		e->val = val;
	}
	return e;
}

// insérer un élément (ordre croissant)
void InsertElem(Elem** prem, Elem*e) 
{
	if (*prem == NULL) {// si rien
		*prem = e;
	}	
	else if (e->val < (*prem)->val) {// si en premier
		e->suiv = *prem;
		(*prem)->prec = e;
		*prem = e;
	}
	else{
		Elem* p = *prem;
		while ( p->suiv != NULL && e->val >= p->suiv->val)
			p = p->suiv;
		
		e->suiv = p->suiv;
		p->suiv = e;
		e->prec = p;
		
	}
}
// créer une liste croissante de nb éléments
void CreateListe(Elem** prem, int nb)
{
	while (nb--)
		InsertElem(prem, CreateElem(rand() % 20));
}
// déorganise une liste (tout simplement en changeant les valeurs)
void DisruptListe(Elem* prem) 
{
	while (prem != NULL) {
		prem->val = rand() % 20;
		prem = prem->suiv;
	}
}
// liste croissante ?
_Bool IncreasingList(Elem*prem)
{
	_Bool res = TRUE;
	if (prem == NULL )
		printf("liste vide\n");
	else {
		while (prem != NULL && prem->suiv != NULL) {
			if (prem->val > prem->suiv->val) {
				res = FALSE;
				break;
			}
			prem = prem->suiv;
		}
	}
	return res;
}
// afficher
void DisplayListe(Elem* prem)
{
	if (prem == NULL)
		printf("liste vide\n");
	else {
		while (prem != NULL) {
			printf("%d->", prem->val);
			prem = prem->suiv;
		}
		putchar('\n');
	}
}
void DestroyListe(Elem** prem)
{
	while (*prem) {
		Elem* e = *prem;
		*prem = (*prem)->suiv;
		free(e);
	}
}