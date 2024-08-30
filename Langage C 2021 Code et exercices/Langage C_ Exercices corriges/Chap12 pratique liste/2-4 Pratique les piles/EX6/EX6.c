/*
Exercice 6
Soient trois piles P1, P2 et P3 pouvant contenir un nombre illimit� d�objets.
Au d�but, des objets de tailles diff�rentes peuvent �tre empil�s de mani�re 
d�sordonn�e dans la premi�re pile P1. Cette pile n�est soumise � aucune contrainte : 
un objet plus grand peut donc �tre empil� sur un plus petit. Nous supposerons donc 
que l�appel � la proc�dure EmpilerEnVrac(P1) empile de mani�re d�sordonn�e plusieurs 
objets dans la pile P1.
On souhaite trier ces objets par taille dans la seconde pile P2, soumise quant � 
elle � la contrainte suivante : un objet plus petit ne peut �tre empil� que sur 
un objet plus grand. Pour cela, on d�pile les objets de la premi�re pile P1 un par 
un, et on les empile dans la seconde pile P2 en respectant cette contrainte d�ordre 
d�empilement.
Si la taille de l�objet en sommet de P1 est plus grande que celle en sommet de P2, 
la troisi�me pile P3 interm�diaire s�av�re indispensable. Tout comme P1, cette troisi�me 
pile P3 n�est soumise � aucune contrainte d�ordre d�empilement.

�crire un programme de simulation pour n objets entr�s par l'utilisateur.

*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

typedef struct Elem{
	int val;
	struct Elem* suiv;
}Elem;

void Menu();
int SaisieNombre(char* msg);
Elem* CreateElem(int val);
_Bool PileVide(Elem* pile);
void EmpilerElem(Elem** sommet, Elem* e);
Elem* DepilerElem(Elem** sommet);
void DisplayPile(Elem* sommet);
void DestroyPile(Elem** sommet);
void TrierPile(Elem** p1, Elem** p2);

int main()
{
	int fin = 0;
	Elem* P1 = NULL;
	Elem* P2 = NULL;
	srand((unsigned int)time(NULL));

	Menu();
	while (fin != 'q') {
		switch (_getch()) {
		case 'a': // Tas P1
		{
			int nb = SaisieNombre("Nombre d'elements ? ");
			while (nb--) 
				EmpilerElem(&P1, CreateElem(rand()%10));
			DisplayPile(P1);
		}
			break;

		case 'z':	// P1 tri� en P2 via P3 locale � la fonction de tri
			TrierPile(&P1, &P2);
			DisplayPile(P2);

			DestroyPile(&P1);
			DestroyPile(&P2);
			break;
		
		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyPile(&P1);
	DestroyPile(&P2);
	return 0;
}
void Menu()
{
	printf("a : Empiler su P1\n");
	printf("z : Trier sur P2\n");
	printf("q : Quitter\n\n");
}
int SaisieNombre(char* msg)
{
	int nb = 0, res = 0;
	do {
		printf(msg);
		res = scanf_s("%d", &nb);
		rewind(stdin);
	} while (res != 1);
	return nb;
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
_Bool PileVide(Elem* pile)
{
	return pile == NULL;
}
void EmpilerElem(Elem** sommet, Elem* e)  // empiler
{
	if(e!=NULL){
		e->suiv = *sommet;
		*sommet = e;
	}
}
Elem* DepilerElem(Elem** sommet) // d�piler
{
	Elem* e = NULL;
	if (*sommet != NULL) {
		e = *sommet;
		*sommet = (*sommet)->suiv;
		e->suiv = NULL;  // attention ! ne pas oublier
	}
	return e;
}
void DisplayPile(Elem* sommet)
{
	if (sommet == NULL)
		printf("liste vide\n");
	else {
		while (sommet != NULL) {
			printf("%d ", sommet->val);
			sommet = sommet->suiv;
		}
		putchar('\n');
	}
}
void DestroyPile(Elem** sommet)
{
	while (*sommet != NULL) {
		Elem* e = DepilerElem(sommet);
		free(e);
	}
	*sommet = NULL;
}
// p1 est la pile a trier, p2 la pile tri�e
void TrierPile(Elem** p1, Elem** p2)
{
	Elem* p3 = NULL; // pile utilis�e pendant le tri

	while (*p1 != NULL) {// vider p1
		Elem* e = DepilerElem(p1);
		if (*p2 == NULL) // si rien en p2
			EmpilerElem(p2, e);
		else {
			// si des �l�ments le d�piler jusqu'� trouver la bonne place
			// et les placer en attendant sur la pile p3. Attention au 
			// fait qu'il s'agit peut-�tre de vider la pile enti�re.
			while (*p2 != NULL && e->val > (*p2)->val) 
				EmpilerElem(&p3, DepilerElem(p2));
			// lorsque la bonne place est trouv�e mettre l'�l�ment e de p1
			EmpilerElem(p2, e);
			// et pour finir replacer tous les autres de p3
			while(p3!=NULL)
				EmpilerElem(p2, DepilerElem(&p3));
		}
	}
}

