/*
Exercice 13
Écrire un programme qui permet de distribuer les cartes d'un jeu de 52 cartes
entre nb joueurs entré par l'utilisateur. Le jeu de chaque joueur est constitué
par une liste chaînée.Tester dans un programme.
*/

/* L'exercice permet de commencer la création d'un jeu avec 52 cartes. 
plusieurs solutions d'implémentation s'offrent à nous :
	1) Tableau dynamique de joueurs (joueur*, probablement le plus simple).
	2) Un tableau dynamique de pointeurs de joueurs (Joueur**, une étoile pour 
	créer un tableau l'autre pour le type pointeur des éléments. ).
	3) Une liste chainée de joueurs (joueur*, pratique si des joueurs entrent 
	et sortent de la partie pendant le jeu)

	Pour bien choisir la structure de donnée du départ et également pour certains 
	aspects de l'implémentation (consultation des cartes, organisation des cartes 
	dans le jeu des joueurs, tri des cartes etc.) il est impératif de connaitre 
	le jeu à mettre en oeuvre.

	Nous allons traiter ici les solutions 1 (EX13_1a.c et EX13_1b.c) et 3 (EX13_2.c).
*/

// SOLUTION 1 : un tableau dynamique de joueurs déclaré dans le main
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

enum { FALSE, TRUE };

// le jeu de cartes peut être envisagé avec n'importe quel nombre de couleur
// (familles) et n'importe quel nombre de cartes par couleur. Il suffit de  
// changer les valeurs de NBCOLOR et NBRANG puis de recompiler

// jeu classique 52 cartes
#define NBCOLOR		4
#define NBRANG		13 // de 1 à 10 et valet dame roi
#define NBCARTES	(NBCOLOR*NBRANG)
	
typedef struct Carte
{
	int color;
	int rang;
	struct Carte* suiv;
	struct Carte* prec;
}Carte;
Carte JC[NBCARTES];

typedef struct Joueur {
	char name[80];
	int score;
	Carte* prem;
	Carte* dern;
}Joueur;

void Menu();
void CreateJC(void);
void DisplayJC(void);
void MelangeJC(void);
void Pause(void);

Joueur* CreateAllJoueurs(int nbJoueur);
void CreateNom(char nom[80]);
void DestroyAllJoueurs(Joueur** joueurs, int nbJoueurs);
void DistributeCarte(Joueur joueurs[], int nbJoueurs);
void AddCarte(Joueur* joueur, Carte* c);
void DisplayAllJoueurs(Joueur joueurs[], int nbJoueurs);

int main()
{
	int fin = 0;
	
	Joueur* Joueurs = NULL;
	int nbJoueurs = 0;

	srand((unsigned int)time(NULL));
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
			if (Joueurs)
				DestroyAllJoueurs(&Joueurs, nbJoueurs);
			
			printf("Combien de joueurs ? ");
			if (scanf_s("%d", &nbJoueurs)) {
				Joueurs = CreateAllJoueurs(nbJoueurs);
				DistributeCarte(Joueurs, nbJoueurs);
				DisplayAllJoueurs(Joueurs, nbJoueurs);
			}
			break;
		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyAllJoueurs(&Joueurs, nbJoueurs);
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
	printf("q : Quitter\n");
}
void CreateJC()
{
	int color = -1;
	for (int i = 0; i < NBCARTES; i++) {
		
		if (i % NBRANG == 0)
			color++;  // les couleurs commencent à 0

		JC[i].suiv = NULL;
		JC[i].prec = NULL;
		JC[i].color = color;
		// le rang détermine la place de la carte dans le jeu
		// et détermine sa valeur sa valeur (lselon le jeu l'as 
		// devra être augmenté)
		JC[i].rang = (i % NBRANG) + 1;
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
		printf("%c%-2d ", 'A' + JC[i].color, JC[i].rang);
		if ((++cmpt)% NBRANG ==0 )
			putchar('\n');
	}
	printf("------\n");
}
void MelangeJC()
{
	int i, j, k;
	for ( i = 0; i < 200; i++) {
		j = rand() % NBCARTES;
		k = rand() % NBCARTES;
		// permuter j et k
		Carte tmp = JC[j];
		JC[j] = JC[k];
		JC[k] = tmp;
	}
}
/*****************************************************************
	GESTION DES JOUEURS
******************************************************************/
Joueur* CreateAllJoueurs(int nbJoueur)
{
	Joueur*jeu = (Joueur *)malloc(sizeof(Joueur) * nbJoueur);
	if (jeu != NULL) {
		for (int i = 0; i < nbJoueur; i++) {
			CreateNom(jeu[i].name);
			jeu[i].score = 0;
			jeu[i].dern = NULL; // warning 6386 : aucun risque ici que jeu[i] ne soit pas alloué.
			jeu[i].prem = NULL;
		}
	}
	return jeu;
}

void CreateNom(char nom[80]) // ici juste pour mémoire 80 char max
{
	char v[7] = "aeiouy";
	char c[19] = "cdfghjklmnprstvwxz";
	memset(nom, 0, sizeof(char) * 80);

	int nbl = 3 + rand() % 8;
	while (nbl--) {
		if (nbl % 2)
			nom[nbl] = v[rand() % 6];
		else
			nom[nbl] = c[rand() % 18];
	}
	//nom[strlen(nom)] = '\n';
}
// il s'agit du tableau de joueurs
void DistributeCarte(Joueur joueurs[], int nbJoueurs)
{
	if (nbJoueurs > 0) {
		for (int i = 0; i < NBCARTES; i++)
			AddCarte(joueurs + (i % nbJoueurs), JC + i); // ou &j[i % nbJoueurs], &JC[i]
	}
}
// on ajoute les carte à la fin du paquet détenu par chaque joueur comme pour 
// la bataille. Il s'agit d'un joueur (passage par référence)
void AddCarte(Joueur* joueur, Carte* c)
{
	if (joueur != NULL ) {
		if (joueur->prem == NULL)
			joueur->dern = joueur->prem = c;
		else {
			joueur->dern->suiv = c;
			c->prec = joueur->dern;
			joueur->dern = c;
		}
	}
}

// afficher les cartes d'un joueur (passage d'un joueur par référence)
void DisplayJoueur(Joueur* joueur)
{
	if (joueur != NULL) {
		printf("%-10s: ", joueur->name);
		if (joueur->prem == NULL)
			printf("n'a plus de carte");
		else {
			Carte* j = joueur->prem;
			while (j != NULL) {
				printf(" %c%-2d ", 'A' + j->color, j->rang);
				j = j->suiv;
			}
			putchar('\n');
		}
	}
}
// afficher tous les joueurs
void DisplayAllJoueurs(Joueur joueurs[], int nbJoueurs)
{
	if (nbJoueurs <= 0)
		printf("pas de joueurs\n");
	else {
		for (int i = 0; i < nbJoueurs; i++)
			DisplayJoueur(joueurs + i);  // équivalent à &joueurs[i]
	}
	
}
// passage du tableau dynamique de pointeurs (deux étoiles) 
// tableau dynamique de joueurs par référence ( 2 étoiles)
void DestroyAllJoueurs(Joueur** joueurs, int nbJoueurs)
{
	// Attention : il n'ya que le tableau de joueur à libérer
	// parce que les cartes sont statiques et doivent rester 
	// en mémoire
	if (*joueurs != NULL) {
		// détruire le tableau de joueurs
		free(*joueurs);
		*joueurs = NULL;
	}
	// cependant il faut veiller aussi à réinitialiser les cartes
	for (int i = 0; i < NBCARTES; i++) {
		JC[i].suiv = NULL;
		JC[i].prec = NULL;
	}
}