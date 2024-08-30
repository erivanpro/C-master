/*Exercice 5
Écrire un programme qui transforme une expression infixée(avec parenthèses) 
en notation postfixée(polonaise inversée).L'expression suivante :
3 * (((12 - 3) / 3) - 1)
devra être traduite en :
3 12 3 – 3 / 1 - *
Les opérateurs valides sont : +, -, *, / .L'algorithme lit une suite de 
caractères et range le résultat de la conversion dans une file qui est 
affichée à la fin.
*/


/*	L'alogorithme qui permet de traduire une expression infixée en une expression postfixée
	n'est en réalité pas aisée à trouver. Il nécessite une file mais aussi une pile.
	la file reçoit systématiquement les nombres, les opérateurs sont empilés à part.
	en cas de parenthèse fermante l'opérateur au sommet de la pile est dépilé et
	enfilé dans la file avec les nombres. A la fin ce qui reste dans la pile est
	enfilé dans la file.
	Dans le cas où il n'y a pas de parenthèse la priorité des opérateurs doit être prise en compte.
	Au moment d'empiler un opérateur si la priorité de cet opérateur est inférieure ou égale à
	celle de ceux qui sont au sommet de la pile, d'abord  les retirer et les passer dans la file,
	ensuite seulement mettre le nouvel opérateur dans la pile.
	Dans le cas d'un parenthèsage incomplet et non systématique on est oblgé de considérer aussi les
	parenthèses ouvrantes. L'algorithme général est le suivant :

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
					file[in++] = inf[i++]; // attention incrémentation après utilisation de i
				}
				file[in++] = ' ';
			}
				
			// si opérateur l'empiler dans la pile
			if (!isdigit(inf[i]) && inf[i] != ' '&& inf[i] != '(' && inf[i] != ')') {
				pile[sommet++] = inf[i];
			}
			// si parenthèse fermante : passer opérateur au sommet de la pile dans la file
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



