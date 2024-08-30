/*
Exercice 15
Division cellulaire de l'algue Anabaena Catenula. Au départ nous avons une
cellule de taille 4 symbolisée par un sens, par exemple une flèche <-.Elle
grandit de 1 à chaque étape de son évolution. À l'étape 5 elle a la taille 9
qui est le maximum qu'une cellule peut atteindre. Alors elle se divise en deux
cellules, une de 4, sens <-, et une de 5 symbolisée par le sens-> et l'évolution
reprend. Dès qu'une cellule arrive à la taille 9 elle se divise en deux cellules
de 4 et 5. Programmer une simulation.Là encore il s'agit de faire une liste
circulaire. Définir pour commencer une structure cellule avec une représentation
du sens.Trouver un mode d'affichage et pouvoir afficher une étape quelconque de la
progression.
*/

/*
La circularité de la liste se discute ici. Il sera en effet un peu plus simple 
de controler  chaque cycle avec une liste non circulaire. Une liste circulaire 
est intéressante dans le cas par exemple d'un jeu video en imaginant un être 
comme celui-ci croissant continuellement et envahissant tout progressivement.

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>


typedef struct Cell {
	int taille;
	struct Cell* suiv;

}Cell;

void Menu();
Cell* CreateCell(int val);
void RunCells(Cell** cells);
void RunNbTours(Cell** cells, int nb);
void AddCell(Cell** cells, Cell* c);
void DestroyCells(Cell** cells);
void DisplayCells(Cell* cells);

int main()
{
	Cell* Cells = NULL;
	int fin = 0, cycle = 0;;

	Menu();
	while (fin != 'q') {

		switch (_getch()) {

			// créer une cellule de départ
		case 'a':
			if (Cells != NULL)
				DestroyCells(&Cells);
			printf("premiere cellule :\n");
			Cells = CreateCell(4);
			DisplayCells(Cells);
			break;

			//  
		case 'z':
		{
			// avec 39 cycles l'aspect exponentiel de la croissance est bien visible
			printf("entrez le nombre de cycles : ");
			int cycle = 0;
			if (scanf_s("%d", &cycle))
				RunNbTours(&Cells, cycle);
		}
			break;

		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyCells(&Cells);
	return 0;
}
void Menu()
{
	printf("a : Creer une première cellule\n");
	printf("z : Faire touner nb cycles\n");
	printf("q : Quitter\n");
}
Cell* CreateCell(int val)
{
	Cell* c = (Cell*)malloc(sizeof(Cell));
	if (c) {
		c->taille = val;
		c->suiv = c; // pour liste circulaire
	}
	return c;
}
void AddCell(Cell** cells, Cell* c)
{
	if (*cells == NULL)
		*cells = c;
	else {
		c->suiv = (*cells)->suiv;
		(*cells)->suiv = c;
	}
}
void RunCells(Cell** cells)
{
	if (*cells != NULL) {  // erreur probable par ici
		Cell* c = *cells;
		do {
			(*cells)->taille++;
			if ((*cells)->taille > 9) {
				(*cells)->taille = 4;
				AddCell(cells, CreateCell(4));
			}
			*cells = (*cells)->suiv;
		} while (*cells != c);
	}
}
void RunNbTours(Cell **cells, int nb)
{
	if (*cells != NULL) {
		for (int i = 0; i < nb; i++) {
			printf("cycle %d : ", i);
			RunCells(cells);
			DisplayCells(*cells);
		}
	}
}
void DestroyCells(Cell** cells)
{
	if (*cells != NULL) {
		Cell* p = (*cells)->suiv;
		while (p != *cells) {
			Cell* sup = p;
			p = p->suiv;
			free(sup);
		}
		free(*cells);
		*cells = NULL;
	}
}
void DisplayCells(Cell* cells)
{
	if (cells == NULL)
		printf("Aucune cellule\n");
	else {
		Cell* p = cells;
		do {
			printf("%d", p->taille);
			p = p->suiv;
		} while (p != cells);
		putchar('\n');
	}
}


