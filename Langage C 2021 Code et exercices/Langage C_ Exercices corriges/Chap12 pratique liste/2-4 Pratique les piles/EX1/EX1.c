/*Exercice 1
Écrire un programme qui affiche une liste chaînée simple à l'envers en utilisant une pile.
*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

typedef struct Elem 
{	
	int val;
	struct Elem* suiv;
}Elem;

void Menu();
Elem* CreateElem(int val);
void AddElem(Elem** prem, Elem* e);
Elem* RemoveFirstElem(Elem** prem);
void DisplayElems(Elem* prem);
void DestroyElems(Elem** prem);

int main()
{
	int fin = 0, nb;
	Elem* Prem = NULL;

	srand((unsigned int)time(NULL));
	while (fin != 'q') {
		switch (_getch()) {
		case 'a': // créer une liste
			nb = 0;
			if (Prem != NULL)
				DestroyElems(&Prem);
			printf("Entrez le nombre d'elements : ");
			if (scanf_s("%d", &nb)) {
				for (int i = 0; i < nb; i++)
					AddElem(&Prem, CreateElem(rand() % 100));
				putchar('\n');
			}
			DisplayElems(Prem);
			rewind(stdin);
			break;

		case 'z':
		{
			Elem* pile = NULL;
			while (Prem != NULL) {
				Elem* e = RemoveFirstElem(&Prem); 
				AddElem(&pile, e); // empiler e
			}
			DisplayElems(pile);
			Prem = pile;  // équivalent à un reverse de Prem
		}
			break;
		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyElems(&Prem);
	return 0;
}
void Menu()
{
	printf("a : Creer une liste de nb elements\n");
	printf("z : \n");
	printf("q : Quitter\n");
}
Elem* CreateElem(int val)
{
	Elem* e = (Elem*)malloc(sizeof(Elem));
	if (e) {
		e->val = val;
		e->suiv = NULL;
	}
	return e;
}
void AddElem(Elem** prem, Elem *e)  // empiler
{
	if (*prem == NULL)
		* prem = e;
	else {
		e->suiv = *prem;
		*prem = e;
	}
}
Elem* RemoveFirstElem(Elem** prem) // dépiler
{
	Elem* e = NULL;
	if (*prem != NULL) {
		e = *prem;
		*prem = (*prem)->suiv;
		e->suiv = NULL;  // attention ! ne pas oublier
	}
	return e;
}
void DisplayElems(Elem* prem)
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
void DestroyElems(Elem** prem)
{
	while (*prem != NULL) {
		Elem* e = RemoveFirstElem(prem);
		free(e);
	}
	*prem = NULL;
}