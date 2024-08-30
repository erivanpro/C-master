/*
Exercice 15
Division cellulaire de l'algue Anabaena Catenula. Au d�part nous avons une
cellule de taille 4 symbolis�e par un sens, par exemple une fl�che <-.Elle
grandit de 1 � chaque �tape de son �volution. � l'�tape 5 elle a la taille 9
qui est le maximum qu'une cellule peut atteindre. Alors elle se divise en deux
cellules, une de 4, sens <-, et une de 5 symbolis�e par le sens-> et l'�volution
reprend. D�s qu'une cellule arrive � la taille 9 elle se divise en deux cellules
de 4 et 5. Programmer une simulation.L� encore il s'agit de faire une liste
circulaire. D�finir pour commencer une structure cellule avec une repr�sentation
du sens.Trouver un mode d'affichage et pouvoir afficher une �tape quelconque de la
progression.
*/

/*
La circularit� de la liste se discute ici. Il sera en effet un peu plus simple 
de controler  chaque cycle avec une liste non circulaire. Une liste circulaire 
est int�ressante dans le cas par exemple d'un jeu video en imaginant un �tre 
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

			// cr�er une cellule de d�part
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
	printf("a : Creer une premi�re cellule\n");
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


