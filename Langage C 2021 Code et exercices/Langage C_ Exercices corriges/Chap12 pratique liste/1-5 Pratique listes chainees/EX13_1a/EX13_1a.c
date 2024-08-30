/*
Exercice 13
�crire un programme qui permet de distribuer les cartes d'un jeu de 52 cartes
entre nb joueurs entr� par l'utilisateur. Le jeu de chaque joueur est constitu�
par une liste cha�n�e.Tester dans un programme.
*/

/* L'exercice permet de commencer la cr�ation d'un jeu avec 52 cartes. 
plusieurs solutions d'impl�mentation s'offrent � nous :
	1) Tableau dynamique de joueurs (joueur*, probablement le plus simple).
	2) Un tableau dynamique de pointeurs de joueurs (Joueur**, une �toile pour 
	cr�er un tableau l'autre pour le type pointeur des �l�ments. ).
	3) Une liste chain�e de joueurs (joueur*, pratique si des joueurs entrent 
	et sortent de la partie pendant le jeu)

	Pour bien choisir la structure de donn�e du d�part et �galement pour certains 
	aspects de l'impl�mentation (consultation des cartes, organisation des cartes 
	dans le jeu des joueurs, tri des cartes etc.) il est imp�ratif de connaitre 
	le jeu � mettre en oeuvre.

	Nous allons traiter ici les solutions 1 (EX13_1a.c et EX13_1b.c) et 3 (EX13_2.c).
*/

// SOLUTION 1 : un tableau dynamique de joueurs d�clar� dans le main
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

enum { FALSE, TRUE };

// le jeu de cartes peut �tre envisag� avec n'importe quel nombre de couleur
// (familles) et n'importe quel nombre de cartes par couleur. Il suffit de  
// changer les valeurs de NBCOLOR et NBRANG puis de recompiler

// jeu classique 52 cartes
#define NBCOLOR		4
#define NBRANG		13 // de 1 � 10 et valet dame roi
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
		// m�langer et voir le jeu de carte
		case 'z':
			MelangeJC();
			DisplayJC();
			break;
		// entrer le nombre de joueurs, cr�er les joueurs, 
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
			color++;  // les couleurs commencent � 0

		JC[i].suiv = NULL;
		JC[i].prec = NULL;
		JC[i].color = color;
		// le rang d�termine la place de la carte dans le jeu
		// et d�termine sa valeur sa valeur (lselon le jeu l'as 
		// devra �tre augment�)
		JC[i].rang = (i % NBRANG) + 1;
	}
}
// fonction qui permet de controler la bonne cr�ation du jeu 
// et aussi le m�lange du jeu.
void DisplayJC()
{
	int cmpt = 0;
	for (int i = 0; i < NBCARTES; i++) {
		// chaque famille est identifi�e par une lettre (A, B, C et D)
		// %-2d pour que l'aligement des chiffres soit coll� � la lettre
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
			jeu[i].dern = NULL; // warning 6386 : aucun risque ici que jeu[i] ne soit pas allou�.
			jeu[i].prem = NULL;
		}
	}
	return jeu;
}

void CreateNom(char nom[80]) // ici juste pour m�moire 80 char max
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
// on ajoute les carte � la fin du paquet d�tenu par chaque joueur comme pour 
// la bataille. Il s'agit d'un joueur (passage par r�f�rence)
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

// afficher les cartes d'un joueur (passage d'un joueur par r�f�rence)
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
			DisplayJoueur(joueurs + i);  // �quivalent � &joueurs[i]
	}
	
}
// passage du tableau dynamique de pointeurs (deux �toiles) 
// tableau dynamique de joueurs par r�f�rence ( 2 �toiles)
void DestroyAllJoueurs(Joueur** joueurs, int nbJoueurs)
{
	// Attention : il n'ya que le tableau de joueur � lib�rer
	// parce que les cartes sont statiques et doivent rester 
	// en m�moire
	if (*joueurs != NULL) {
		// d�truire le tableau de joueurs
		free(*joueurs);
		*joueurs = NULL;
	}
	// cependant il faut veiller aussi � r�initialiser les cartes
	for (int i = 0; i < NBCARTES; i++) {
		JC[i].suiv = NULL;
		JC[i].prec = NULL;
	}
}