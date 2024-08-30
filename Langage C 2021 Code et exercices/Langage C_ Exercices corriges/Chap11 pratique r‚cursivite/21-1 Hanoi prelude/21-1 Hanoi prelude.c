/*********************************************************************************
Exercice 21 :

PART 1

r�cursivit� et pile, visualiser le d�placement
des anneaux des tours de Hano�
L'objectif est d'�crire un programme pour visualiser l'algorithme des tours de Hano�
et pour un nombre n d'anneaux avec n >= 3. La r�cursivit� devra �tre �limin�e via
l'utilisation de piles, une pile par poteau. Les anneaux sont repr�sent�s par des
entiers qui donnent la taille de l'anneau.
Avant de commencer :
�		Pourquoi un poteau peut-il se repr�senter par une pile ?
�		Dessiner l�arbre d�appels de la proc�dure Hanoi pour n=3.
�		Avec votre arbre d�appels, donner l�ordre de d�placement de chaque anneau tel
		que visualis� dans le printf de la proc�dure Hanoi.

PART 2

Reprendre la proc�dure Hanoi mais en repr�sentant chaque tour par une pile. Le d�placement
visuel du printf sera remplac� par un d�placement effectif d�un anneau entre deux piles
(tours).
1) �crire une fonction qui affiche le contenu d'une pile d�anneaux (1 anneau = 1 entier).
2) D�clarer trois piles qui repr�sentent les trois poteaux du jeu, et �crire une fonction
qui initialise le jeu en empilant les n anneaux correctement sur l'un des trois poteaux.
�crire �galement une fonction qui affiche � l'�cran l'�tat du jeu � un instant donn�.
3) �crire une fonction qui d�place les n anneaux sur l'un des deux poteaux libres en
respectant les r�gles du jeu. Faire en sorte que l'affichage � l'�cran montre bien le
d�placement de chaque anneau.
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
Soit trois variables D, I et A qui repr�sentent trois piquets D�part,
Interm�diaire et Arriv�e. Ces piquets restent fixes. les valeurs correspondent
aux plateaux et aux permutations des d�placements.

l'algorithme est le suivant :

au d�part le premier en D va en arriv�e A, c'est l'appel initial :
deplacement (N, D,I,A)    [avec N=3]

	1) les n-1 restants au d�part en D sont mis sur I en arriv�e
	(A devient interm�diaire) c'est l'appel r�cursif:
	-> deplacement (N-1, D, A, I)  [avec N = 2 puis N = 1 puis N = 0, � chaque fois I et A sont permut�s]

	2) Le dernier au d�part en D est mis sur arriv�e en A (I interm�diaire ne bouge pas)
	[Pour N = 0 les appels r�cursifs cessent et la pile des appels pr�c�dents est d�pil�es. 
	Pour N = 1 en remontant c'est l'instruction printf qui met le dernier au d�part en D sur arriv�e en A]
	-> printf deplacement D vers A

	[Ensuite les appels r�cursifs explorent la seconde branche de d�placement.]
	3) Les n-1 au d�part de interm�diaire sont mis sur A en arriv�e
	(D devient interm�diaire)
	-> deplacement (N-1, I, D, A)
	[Pour N=1 l'appel se fait avec N=0 et il ne se passe plus rien. La suite reprend avec le d�pilement
	� N=2. L� c'est l'instruction printf deplacement D vers A et la redescente avec N=1 en inversant D et I]


Voici l'arbre d'appels pour N = 3
												DIA
											N=3,123
											 4) 1�3
						DAI												IDA
					N=2 132											N=2 213
					 2) 1�2											6) 2�3
		DAI							IDA					DAI							IDA
	N=1 123						N=1 312				N=1 231						N=1 123
	N=0 fin						N=0 fin				N=0 fin						N=0 fin
  1)N=1 1�3					  3)N=1 3�2			  5)N=1 2�1					  7)N=1 1�3

  Vous pouvez regarder au d�bogueur la pile des appels et constater empilements et d�pilements 
  des appels r�cursifs de la fonction Hanoi (rebaptis�e "d�placement" ci-dessous)
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
Autre version peut-�tre plus parlante. Ne pas h�siter � regarder le fonctionnement
au d�bogueur
*******************************************************************************/
void Hanoi(int n, int d, int i, int a)
{
	if (n == 1)				// afficher le d�placement de chaque dernier
		printf("aller de %c en %c\n", d, a);
	else {
		Hanoi(n - 1, d, a, i); // d�placer les n-1 anneaux de d�part en interm�diaire
		Hanoi(1, d, i, a);	// deplacer le dernier de d�part sur arriv�e
		Hanoi(n - 1, i, d, a); // deplacer les n-1 anneaux de interm�diaire en arriv�e
	}
}
/*******************************************************************************
*******************************************************************************/


