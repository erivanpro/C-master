/*Exercice 4
Le but de cet exercice est d'écrire un programme qui simule le déroulement
d'une partie du jeu de la bataille.
Rappel des règles :
– On dispose d'un jeu de 32 cartes (4 couleurs et 8 puissances de carte).
– Chaque carte possède une couleur (COEUR, CARREAU, TREFLE ou PIQUE) et
une puissance (SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI ou AS). On utilisera les
codes ASCII 3, 4, 5 et 6 pour représenter les symboles(treffle...). Par exemple,
la dame de cœur sera affichée D .
Le jeu est d'abord mélangé aléatoirement pour ensuite être coupé en deux tas
de 16 cartes. On en donne un à chaque joueur. La partie peut enfin commencer.
Chaque joueur montre la carte au sommet de son tas. Le joueur qui a la carte
plus forte valeur ramasse sa carte et celle de son adversaire et les met sous
son tas. En cas d'égalité, les deux cartes sont placées sur un tas d'attente
avec, pour chaque joueur, une autre carte prise au sommet de son tas. Ensuite,
la partie reprend. Le joueur qui remportera la manche suivante remportera non
seulement les deux cartes en jeu mais également toutes celles qui se trouvent
dans le tas d'attente.

Le perdant sera le joueur qui n’a plus de carte dans son tas et le vainqueur
celui qui réalise le meilleur score à la fin de la partie.
Définir des structures de données adaptées pour une carte, un tas de cartes
et un jeu de cartes.

Définir les joueurs. Commencer avec deux joueurs.
Quelles sont les actions à effectuer et dans quel ordre ?
Soigner l'affichage du déroulement de la partie.

Ensuite généraliser pour une partie de bataille entre nb joueurs avec un jeu de
cartes imaginaire de nb cartes avec nb couleurs.
*/


//VERSION GENERALISATION 
//L'implémentation est la plus simple possible : 
//  - chaque jour est une liste de cartes et l'ensemble des joueurs est 
//    un tableau dynamique de listes de cartes. 
//	- De même le tapis est un tableau dynamique de listes de cartes 
//	  (en cas de bataille les joueurs qui concourent doivent rejouer 
//	   autant de fois que nécessaire)

// pour les batailles plusieurs régles sont envisageables :
// 1) faire bataille uniquement pour les vainqueurs potentiels  
//	 (bataille entre des cartes susceptibles de gagner le tour)
// 2) faire également les sous-batailles avec potentiellement 
//   la possibilité pour un joueur de remonter de niveau et de gagner 
//   la partie ou de faire d'autres batailles.

// nous avons traité uniquement le premier point. Il n'y a bataille 
// qu'entre les cartes les plus fortes et le résultat obtenu sert uniquement
// à départager les joueurs potentiellement vainqueurs.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

enum { FALSE, TRUE };

/*
L'implémentation proposée permet de créer tous les jeux de cartes que l'on veut
 avec n'importe quel nombre de couleur et de valeur de rang. Il suffit de  
changer les valeurs de NBCOLOR et NBRANG puis de recompiler.
*/

// Les couleurs Treffle, carreaux, pique, coeur
// sont remplacées par A, B, C, D.
// la force de la carte correspond à une valeur entre 1 et NBRANG compris
// selon le jeu des amménagements sont nécessaires, par exemple pour la
// bataille l'as, 1, est plus puissant que les autres cartes.

// réglage jeu 32 cartes
#define NBCOLOR		4
#define NBRANG		8  // 13 // pour 52 cartes (1 à 10 et valet dame roi ou 2 à 11 + V D R As)
#define NBCARTES	(NBCOLOR*NBRANG)

typedef struct Carte {
	int color;   // la famille de carte coeur pique etc.
	int rang;    // la force/valeur de la carte
	struct Carte* suiv;
}Carte;
Carte JC[NBCARTES];

void Menu();
void CreateJC(void);
void DisplayJC(void);
void MelangeJC(void);
void Pause(void);

Carte** CreateGame(int nbPlayers);
void DestroyGame(Carte*** game);
void StackCarte(Carte** prem, Carte* c);
void DistributeCarte(Carte* players[], int nbPlayers);
void DisplayPlayer(Carte* p, int num, char*msg);
void DisplayGame(Carte* p[], int nbPlayers, char* msg1, char* msg2);
void PlayingTurn(Carte* players[], int nbPlayers);
int CheckTapis(Carte* tapis[], Carte* players[], int nbPlayers);
Carte* DequeueCarte(Carte** prem);
void EnqueueCarte(Carte** prem, Carte* c);

int main()
{
	int fin = 0;

	// tableaux dynamiques de pointeurs 
	Carte** Players = NULL; // Une liste de carte par joueur
	
	int nbPlayers = 0;

	//srand((unsigned int)time(NULL));
	srand(10);
	CreateJC();
	Menu();
	while (fin != 'q') {

		switch (_getch()) {

			// voir le jeu de carte
			case 'a':
				DisplayJC();
				break;
			// mélanger et voir le jeu de carte
			case 'z':
				MelangeJC();
				DisplayJC();
				break;

			// entrer le nombre de joueurs, créer les joueurs, 
			// distribuer les cartes, afficher chaque jeu
			case 'e':
				if (Players)
					DestroyGame(&Players);
					
				printf("Combien de joueurs ? ");
				if (scanf_s("%d", &nbPlayers)) {
					Players = CreateGame(nbPlayers);
					MelangeJC();
					DistributeCarte(Players, nbPlayers);
					DisplayGame(Players, nbPlayers, "JOUEURS :\n","joueur");
				}
				break;
			case 'r':
				// jouer et voir le tapis
				PlayingTurn(Players, nbPlayers);
				DisplayGame(Players, nbPlayers, "JOUEURS :\n","joueur");
				break;

			case 'q':
				fin = 'q';
				break;
		}
	}
	DestroyGame(&Players);
	return 0;
}
/*****************************************************************
	PAQUET DE CARTE ET MENU
******************************************************************/
void Menu()
{
	printf("a : Voir jeu complet ordonne\n");
	printf("z : melanger jeu\n");
	printf("e : Creer partie, afficher joueurs\n");
	printf("r : Jouer un tour, afficher tapis\n");
	printf("q : Quitter\n");
}
void CreateJC()
{
	int color = -1;
	for (int i = 0; i < NBCARTES; i++) {

		if (i % NBRANG == 0)
			color++;  // les couleurs commencent à 0

		JC[i].suiv = NULL;
		//JC[i].prec = NULL;// symétrie
		JC[i].color = color;
		// le rang détermine la place de la carte dans le jeu
		// et détermine sa valeur (selon le jeu l'as 
		// devra être augmenté)
		JC[i].rang = (i % NBRANG) + 1;
		if (JC[i].rang == 1)
			JC[i].rang += NBRANG;  // las devient la plus puissante carte
	}
}
// fonction qui permet de controler la bonne création du jeu 
// et aussi le mélange du jeu.
void DisplayJC()
{
	int cmpt = 0;
	for (int i = 0; i < NBCARTES; i++) {
		// chaque famille est identifiée par une lettre (A, B, C et D)
		// %-2d pour que l'aligement des chiffres soit collé à la lettre
		// (voir documentation format de printf)
		// au delà de 26 couleurs ce sont des signes de la table ascii
		printf("%c%-2d ", 'A' + JC[i].color, JC[i].rang);
		if ((++cmpt) % NBRANG == 0)
			putchar('\n');
	}
	printf("------\n");
}
void MelangeJC()
{
	int i, j, k;
	for (i = 0; i < 200; i++) {
		j = rand() % NBCARTES;
		k = rand() % NBCARTES;
		// permuter j et k
		Carte tmp = JC[j];
		JC[j] = JC[k];
		JC[k] = tmp;
	}
}
/*****************************************************************
	GESTION DES JOUEURS ET AFFICHAGES
******************************************************************/
Carte** CreateGame(int nbJoueur)
{
	// un tableau dynamique de nbjoueur pointeurs Carte*
	Carte** c = (Carte **)malloc(sizeof(Carte*) * nbJoueur);
	if (c) {
		// chaque pointeur doit être initialisé à NULL
		for (int i = 0; i < nbJoueur; i++)
			c[i] = NULL;
	}
	return c;
}
// Carte*** = Carte** passé par référence
void DestroyGame(Carte*** tab)
{
	// les cartes ne font pas l'objet d'une allocation, seuls
	// les tableaux dynamiques doivent être libérés
	if (*tab != NULL) {
		free(*tab);
		*tab = NULL;
	}
}
void StackCarte(Carte** prem, Carte* c)
{
	if (c != NULL) {
		c->suiv = (*prem);
		*prem = c;
	}
}
// passage du tableau dynamique de carte*
void DistributeCarte(Carte* p[], int nbPlayers)
{
	if (nbPlayers > 0) {
		for (int i = 0; i < NBCARTES; i++)
			// la liste de cartes de chaque joueur se constitue en les empilant
			// les joueurs reçoivent les cartes une par une à tour de rôle en 
			// tournat toujours dans le même sens
			StackCarte(p + (i % nbPlayers), JC + i); // ou &j[i % nbJoueurs], &JC[i]
	}
}
void DisplayPlayer(Carte* p, int num, char* msg)
{
	printf("%s %d : ", msg, num);
	if (p != NULL) {
		while (p != NULL) {
			printf(" %c%-2d ", 'A' + p->color, p->rang);
			p = p->suiv;
		}
	}
	else
		printf("n'a pas de carte");
	putchar('\n');
}
void DisplayGame(Carte* p[], int nbPlayers, char*msg1, char*msg2)
{
	printf("%s", msg1);
	if (p != NULL) {
		for (int i = 0; i < nbPlayers; i++)
			DisplayPlayer(p[i], i, msg2);  // ou *(p + i)
	}
	else
		printf("pas de joueurs\n");
	putchar('\n');
}
/***********************************************************
	JOUER
************************************************************/
void PlayingTurn(Carte* players[], int nbPlayers)
{
	Carte** tapis = CreateGame(nbPlayers);
	if (tapis && players) {
		// au départ tous les joueurs qui ont encore des cartes jouent
		// chacun empile sur le tapis la première de son paquet (défiler)
		for (int i = 0; i < nbPlayers; i++) {
			if (players[i] != NULL)
				StackCarte(&tapis[i], DequeueCarte(players + i)); // ou &(*players)[i]
		}
		DisplayGame(tapis, nbPlayers, "TAPIS :\n", "tapis");

		// s'il reste plusieurs joueurs c'est qu'il y bataille
		// les joueurs restants rejoueunt tant qu'il y a bataille
		while (CheckTapis(tapis, players, nbPlayers) > 1) {

			for (int i = 0; i < nbPlayers; i++) {
				if (tapis[i] != NULL && players[i] != NULL)
					StackCarte(&tapis[i], DequeueCarte(players + i)); // ou &(*players)[i]
			}
			DisplayGame(tapis, nbPlayers, "NEW TAPIS :\n", "tapis");
		}
		// à l'issue il ne doit rester une seule liste à enfiler à celle du vainqueur
		for (int i = 0; i < nbPlayers; i++) {
			if (tapis[i] != NULL) {
				EnqueueCarte(players + i, tapis[i]);
			}
		}
		DestroyGame(&tapis);
	}
	else
		printf("pas de joueur ni de tapis\n");
}
int CheckTapis(Carte* tapis[], Carte* players[], int nbPlayers)
{
	int nb = 0;
	if (tapis != NULL) {
		// pour chaque carte joueur abattue sur tapis
		for (int i = 0; i < nbPlayers; i++) {
			// regarder les suivantes
			for (int j = i + 1; j < nbPlayers; j++) {
				// si cartes trouvées
				if (tapis[i] != NULL && tapis[j] != NULL) {
					// si carte i supérieure
					if (tapis[i]->rang > tapis[j]->rang) {
						// ajouter carte j à liste carte i et mettre liste carte j à null
						EnqueueCarte(&tapis[i], tapis[j]);
						tapis[j] = NULL;
					}
					// si carte i inférieur
					else if (tapis[i]->rang < tapis[j]->rang) {
						// ajouter i à j et mettre i à null
						EnqueueCarte(&tapis[j], tapis[i]);
						tapis[i] = NULL;
						// il faut en plus regarder si entre i et j il y a des cartes 
						// ex-aequo à i qu'il faut aussi ajouter à j
						for (i = i + 1; i < j; i++) {
							if (tapis[i] != NULL && tapis[i]->rang < tapis[j]->rang) {
								EnqueueCarte(&tapis[j], tapis[i]);
								tapis[i] = NULL;
							}
						}
					}
					// si i et j égaux : bataille. 
					else {
						// les joueurs devront rejouer : vérifier ici qu'ils ont encore des cartes
						// sinon ceux qui n'ont plus de carte pour rejouer perdent
						if (players[i] == NULL) {
							EnqueueCarte(&tapis[j], tapis[i]);
							tapis[i] = NULL;
						}
						if (players[j] == NULL) {
							EnqueueCarte(&tapis[i], tapis[j]);
							tapis[j] = NULL;
						}
					}
				}
			}
		}
		// compter le nombre de joueurs toujours en lice sur le tapis 
		for (int i = 0; i < nbPlayers; i++) 
			if (tapis[i] != NULL)
				nb++;
	}
	return nb;
}
Carte* DequeueCarte(Carte** prem) // équivalent dépiler ici
{
	Carte* c = NULL;
	if (*prem != NULL) {
		c = *prem;
		*prem = (*prem)->suiv;
		// attention, ne pas oublier, la carte doit être détachée du jeu du joueur qui la pose
		c->suiv = NULL;  
	}
	return c;
}
// passage par référence d'une liste de carte*
void EnqueueCarte(Carte** prem, Carte* c)
{
	if (c != NULL) {
		if (*prem == NULL)
			* prem = c;
		else {
			// trouver dernière carte pour ajouter à la fin :
			// c'est plus simple que de gérer un pointeur de queue,
			// c'est très rapide et ça n'est exécuté qu'une fois par tour
			// pour un seul joueur, celui qui gagne.
			Carte* e = *prem;
			while (e->suiv != NULL)
				e = e->suiv;
			e->suiv = c;
		}
	}
}