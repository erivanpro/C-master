/*Exercice 5
�crire un programme qui transforme une expression infix�e(avec parenth�ses) 
en notation postfix�e(polonaise invers�e).L'expression suivante :
3 * (((12 - 3) / 3) - 1)
devra �tre traduite en :
3 12 3 � 3 / 1 - *
Les op�rateurs valides sont : +, -, *, / .L'algorithme lit une suite de 
caract�res et range le r�sultat de la conversion dans une file qui est 
affich�e � la fin.
*/


/*	L'alogorithme qui permet de traduire une expression infix�e en une expression postfix�e
	n'est en r�alit� pas ais�e � trouver. Il n�cessite une file mais aussi une pile.
	la file re�oit syst�matiquement les nombres, les op�rateurs sont empil�s � part.
	en cas de parenth�se fermante l'op�rateur au sommet de la pile est d�pil� et
	enfil� dans la file avec les nombres. A la fin ce qui reste dans la pile est
	enfil� dans la file.
	Dans le cas o� il n'y a pas de parenth�se la priorit� des op�rateurs doit �tre prise en compte.
	Au moment d'empiler un op�rateur si la priorit� de cet op�rateur est inf�rieure ou �gale �
	celle de ceux qui sont au sommet de la pile, d'abord  les retirer et les passer dans la file,
	ensuite seulement mettre le nouvel op�rateur dans la pile.
	Dans le cas d'un parenth�sage incomplet et non syst�matique on est oblg� de consid�rer aussi les
	parenth�ses ouvrantes. L'algorithme g�n�ral est le suivant :

1.	While there are tokens to be read:
2.        Read a token
3.        If it's a number add it to queue
4.        If it's an operator
5.               While there's an operator on the top of the stack with greater precedence:
6.                       Pop operators from the stack onto the output queue
7.               Push the current operator onto the stack
8.        If it's a left bracket push it onto the stack
9.        If it's a right bracket
10.            While there's not a left bracket at the top of the stack:
11.                     Pop operators from the stack onto the output queue.
12.             Pop the left bracket from the stack and discard it
13. While there are operators on the stack, pop them to the queue

Pour en savoir plus voici les documentations dont cet algorithme est extrait:
https://brilliant.org/wiki/shunting-yard-algorithm/
https://fr.wikipedia.org/wiki/Algorithme_Shunting-yard
https://en.wikipedia.org/wiki/Shunting-yard_algorithm
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>

void Menu();
char* InfixeToPostfixe(char inf[]);

int main()
{
	char infixe[] = "3 * (((12 - 3) / 3) - 1)";
	char* postfixe;
	int fin = 0;

	Menu();
	while (!fin) {

		switch (_getch()) {
		case 'a':
			printf("%s infixe donne : ", infixe);
			postfixe = InfixeToPostfixe(infixe);
			printf("%s\n", postfixe);
			free(postfixe);
			break;
		case 'q':
			fin = 1;
			break;
		}
	}
	return 0;
}
void Menu()
{
	printf("a : traduire infixe en postfixe\n");
	printf("q : quitter\n");
}

char* InfixeToPostfixe(char inf[])
{
	int max = strlen(inf) + 1;
	char* file = (char*)malloc(sizeof(char) * max);
	int in = 0, out = 0; // ici out ne changera jamais
	char* pile = (char*)malloc(sizeof(char) * max);
	int sommet = 0;
	if (pile && file) {
		for (int i = 0; inf[i] != '\0'; i++) {
			// si nombre le passer dans la file
			if (isdigit(inf[i])) {
				while (isdigit(inf[i])) {
					file[in++] = inf[i++]; // attention incr�mentation apr�s utilisation de i
				}
				file[in++] = ' ';
			}
				
			// si op�rateur l'empiler dans la pile
			if (!isdigit(inf[i]) && inf[i] != ' '&& inf[i] != '(' && inf[i] != ')') {
				pile[sommet++] = inf[i];
			}
			// si parenth�se fermante : passer op�rateur au sommet de la pile dans la file
			if (inf[i] == ')') {
				file[in++] = pile[--sommet];
				file[in++] = ' ';
			}
		}
		while (sommet >= 1) {
			file[in++] = pile[--sommet];
		}
		file[in++] = '\0';
		free(pile);
	}
	return file;
}



