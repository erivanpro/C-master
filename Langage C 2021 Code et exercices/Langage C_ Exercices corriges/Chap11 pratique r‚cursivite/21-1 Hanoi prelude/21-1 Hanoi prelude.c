/*********************************************************************************
Exercice 21 :

PART 1

récursivité et pile, visualiser le déplacement
des anneaux des tours de Hanoï
L'objectif est d'écrire un programme pour visualiser l'algorithme des tours de Hanoï
et pour un nombre n d'anneaux avec n >= 3. La récursivité devra être éliminée via
l'utilisation de piles, une pile par poteau. Les anneaux sont représentés par des
entiers qui donnent la taille de l'anneau.
Avant de commencer :
–		Pourquoi un poteau peut-il se représenter par une pile ?
–		Dessiner l’arbre d’appels de la procédure Hanoi pour n=3.
–		Avec votre arbre d’appels, donner l’ordre de déplacement de chaque anneau tel
		que visualisé dans le printf de la procédure Hanoi.

PART 2

Reprendre la procédure Hanoi mais en représentant chaque tour par une pile. Le déplacement
visuel du printf sera remplacé par un déplacement effectif d’un anneau entre deux piles
(tours).
1) Écrire une fonction qui affiche le contenu d'une pile d’anneaux (1 anneau = 1 entier).
2) Déclarer trois piles qui représentent les trois poteaux du jeu, et écrire une fonction
qui initialise le jeu en empilant les n anneaux correctement sur l'un des trois poteaux.
Écrire également une fonction qui affiche à l'écran l'état du jeu à un instant donné.
3) Écrire une fonction qui déplace les n anneaux sur l'un des deux poteaux libres en
respectant les règles du jeu. Faire en sorte que l'affichage à l'écran montre bien le
déplacement de chaque anneau.
**********************************************************************************/

// PART 1

#include <stdio.h>
#include <stdlib.h>

int	SaisieNombre(void);
void Deplacement(int n, int d, int i, int a);
void Hanoi(int n, int d, int i, int a);

/*******************************************************************************
*******************************************************************************/
int main()
{
	int n = 0;
	while (n>=0) {

		printf("(nombre negatif pour quitter)\n");
		n = SaisieNombre();
		Deplacement(n, '1', '2', '3');

	}
}
/*******************************************************************************
saisie nombre de disques par utilisateur
*******************************************************************************/
int SaisieNombre()
{
	int res = 0, n;
	printf ("nombre de disques : ");
	do{
		if((res = scanf_s("%d", &n)) == 0)
			printf("entree incorrecte\n");
		rewind(stdin);
	}while (!res);
	
	putchar('\n');
	return n;
}
/***************************************************************************
Soit trois variables D, I et A qui représentent trois piquets Départ,
Intermédiaire et Arrivée. Ces piquets restent fixes. les valeurs correspondent
aux plateaux et aux permutations des déplacements.

l'algorithme est le suivant :

au départ le premier en D va en arrivée A, c'est l'appel initial :
deplacement (N, D,I,A)    [avec N=3]

	1) les n-1 restants au départ en D sont mis sur I en arrivée
	(A devient intermédiaire) c'est l'appel récursif:
	-> deplacement (N-1, D, A, I)  [avec N = 2 puis N = 1 puis N = 0, à chaque fois I et A sont permutés]

	2) Le dernier au départ en D est mis sur arrivée en A (I intermédiaire ne bouge pas)
	[Pour N = 0 les appels récursifs cessent et la pile des appels précédents est dépilées. 
	Pour N = 1 en remontant c'est l'instruction printf qui met le dernier au départ en D sur arrivée en A]
	-> printf deplacement D vers A

	[Ensuite les appels récursifs explorent la seconde branche de déplacement.]
	3) Les n-1 au départ de intermédiaire sont mis sur A en arrivée
	(D devient intermédiaire)
	-> deplacement (N-1, I, D, A)
	[Pour N=1 l'appel se fait avec N=0 et il ne se passe plus rien. La suite reprend avec le dépilement
	à N=2. Là c'est l'instruction printf deplacement D vers A et la redescente avec N=1 en inversant D et I]


Voici l'arbre d'appels pour N = 3
												DIA
											N=3,123
											 4) 1à3
						DAI												IDA
					N=2 132											N=2 213
					 2) 1à2											6) 2à3
		DAI							IDA					DAI							IDA
	N=1 123						N=1 312				N=1 231						N=1 123
	N=0 fin						N=0 fin				N=0 fin						N=0 fin
  1)N=1 1à3					  3)N=1 3à2			  5)N=1 2à1					  7)N=1 1à3

  Vous pouvez regarder au débogueur la pile des appels et constater empilements et dépilements 
  des appels récursifs de la fonction Hanoi (rebaptisée "déplacement" ci-dessous)
*****************************************************************************************/
void Deplacement(int n, int d, int i, int a)
{
	if (n > 0) {
		Deplacement(n - 1, d, a, i);
		printf("n%d = d%c, i%c, a%c : dep %c - %c\n", n, d, i, a, d, a);
		Deplacement(n - 1, i, d, a);
	}
}
/*******************************************************************************
Autre version peut-être plus parlante. Ne pas hésiter à regarder le fonctionnement
au débogueur
*******************************************************************************/
void Hanoi(int n, int d, int i, int a)
{
	if (n == 1)				// afficher le déplacement de chaque dernier
		printf("aller de %c en %c\n", d, a);
	else {
		Hanoi(n - 1, d, a, i); // déplacer les n-1 anneaux de départ en intermédiaire
		Hanoi(1, d, i, a);	// deplacer le dernier de départ sur arrivée
		Hanoi(n - 1, i, d, a); // deplacer les n-1 anneaux de intermédiaire en arrivée
	}
}
/*******************************************************************************
*******************************************************************************/


