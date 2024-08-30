/*********************************************************************************
Exercice 21 :

PART 1

récursivité et pile, visualiser le déplacement
des anneaux des tours de Hanoï.
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

//PART 2

// L'idée de l'exercice est de permettre de visualiser le processus
// mis en oeuvre par l'algorithme récursif de Hanoi. Il ne consiste 
// pas à créer une verion itérative de l'algorithme.

#include"GraphCons.h"

typedef struct Poteau {
	int*discs;  // chaque int de la pile contient la taille d'un disque
	int top;	// sommet pile
	int nb;		// nombre maximum de discs dans la pile
	int ty;		// épaisseur d'un disque 
	int posx, posy; // position d'un poteau
}Poteau;

int Quitter(void);
int SaisieNombre(void);
void CreateJeu(Poteau* p[3], int nb);
_Bool PileVide(Poteau*p);
_Bool PilePleine(Poteau*p);
void Empiler(Poteau*p, int e);
int Depiler(Poteau*p);
void Afficher(Poteau*p);
void AfficherAll(Poteau*p[3]);
void DetruireAll(Poteau*p[3]);

void Hanoi(int n, Poteau*d, Poteau*i, Poteau*a);
void AfficheMove(Poteau* d, Poteau*a);



int main()
{
	// les trois poteaux 0, 1, 2
	Poteau* poteaux[3];
	
	if(!G_PleinEcran()) 
		if(!G_ConsResizeMax())
			printf("Plein écran impossible. Resolution : %d x %d\n", G_ConsTX(), G_ConsTY());

	int fin = 0;
	do {
		int nb = SaisieNombre();
		
		CreateJeu(poteaux, nb);
		AfficherAll(poteaux);
		
		Hanoi(nb, poteaux[0], poteaux[1], poteaux[2]);

		DetruireAll(poteaux);

	} while (!Quitter());
	return 0;
}
/****************************************
saisie nombre de disques par utilisateur
*****************************************/
int SaisieNombre()
{
	int res = 0, n;
	printf("nombre de disques : ");
	do {
		if ((res = scanf_s("%d", &n)) == 0)
			printf("entree incorrecte\n");
		rewind(stdin);
	} while (!res);

	G_ConsCursor(FALSE);
	return n;
}
/****************************************
Contrôle fin
*****************************************/
int Quitter()
{
	int fin = 0;

	printf("appuyez sur une touche pour continuer (escap pour quitter)\n");
	G_FlushEvent();
	while (1) {
		G_PollEvent();
		if (G_KeyPressed()) {
	
			if (G_KeyDown(VK_ESCAPE))
				fin = 1;
			
			G_ConsClear();
			break;
		}
	}
	return fin;
}
/****************************************
Gestion pile (les poteaux)
*****************************************/
void CreateJeu(Poteau* p[3],int nb)
{
	// création des poteaux
	/*
	Pour dim = 4 on aura une représentation du type :
	       -|-
	      --|--
	     ---|---
		----|---- ----|---- ----|---- 
	  1+dim+1+dim+1 etc.  
	  t pour multiplication de dim et e pour ajout des écartements
	Au départ calée à gauche à un espace de la marge et décalé du haut de 
	10 espaces
	*/
	for (int i = 0, t=1, e=1; i < 3; i++, t+=2, e+=6) {
		p[i] = (Poteau*)malloc(sizeof(Poteau));
		p[i]->discs = (int*)malloc(sizeof(int)*nb); // création pile de nb discs
		p[i]->nb = nb;  // conserver la taille max de la pile
		p[i]->top = 0;  // au depart pile vide
		
		// épaisseur des disques
		p[i]->ty = 3;	
		
		// positions poteaux
		p[i]->posx = nb * t + e;
		p[i]->posy = nb * p[i]->ty + 10;  
	}
	/*
	// test pour visualiser tous les poteaux remplis de disques
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < nb; i++)
			p[j]->discs[i] = nb - i;
		p[j]->top = nb;
	}
	*/
	// Mise en place des disques sur le premier poteau
	//for (int j = 0; j < 3; j++) {
		for (int i = 0; i < nb; i++)
			p[0]->discs[i] = nb - i;
		p[0]->top = nb;
	//}
}
_Bool PileVide(Poteau*p)
{
	return p->top == 0;
}
_Bool PilePleine(Poteau*p)
{
	return p->top == p->nb;
}
void Empiler(Poteau*p, int e)
{
	if (!PilePleine(p))
		// (attention l'incrémentation a lieu après l'affectation)
		p->discs[p->top++] = e;	
}
int Depiler(Poteau*p)
{
	int res = -1;
	if (!PileVide(p))
		// (la décrémentation a lieu avant l'affectation)
		res = p->discs[--p->top];
	return res;
}
void Afficher(Poteau*p)
{
	// effacer le poteau
	int x1 = p->posx - p->nb;
	int y1 = p->posy - p->ty*p->nb;
	int x2 = p->posx + p->nb + 1;
	int y2 = p->posy;
	G_FillRect(x1, y1, x2, y2, ' ', BLACK, INVISIBLE); // la couleur de lettre ne sert pas
	
	// afficher les disques
	for (int i = 0; i < p->top; i++) {
		int x1 = p->posx - p->discs[i]; // chaque disque contient sa taille
		int y1 = p->posy - p->ty - (p->ty * i);
		int x2 = p->posx + 1 + p->discs[i] ;
		int y2 = y1 + p->ty ;
		G_FillRect(x1, y1, x2, y2, ' ', p->discs[i], INVISIBLE); 
	}
	// afficher le piquet
	for (int i = p->top; i < p->nb; i++) {
		int x1 = p->posx ; 
		int y1 = p->posy - p->ty - (p->ty * i);
		int x2 = p->posx + 1 ;
		int y2 = y1 + p->ty;
		G_FillRect(x1, y1, x2, y2, ' ', DARK_WHITE, INVISIBLE); // ici la seconde color ne sert à rien
	}
}
void AfficherAll(Poteau*p[3])
{
	for (int i = 0; i < 3; i++)
		Afficher(p[i]);
	
}
void DetruireAll(Poteau*p[3])
{
	for (int i = 0; i < 3; i++) 
		if (p[i]->discs != NULL) 
			free(p[i]->discs);	
}
/*******************************************************************************
Hanoi
*******************************************************************************/
void Hanoi(int n, Poteau*d, Poteau*i, Poteau*a)
{
	if(n>0){
	
		Hanoi(n - 1, d, a, i);
		G_Attendre(1000);
		AfficheMove(d, a);
		Afficher(d);
		Afficher(a);
		Afficher(i);
		Hanoi(n - 1, i, d, a);
	}
}

void AfficheMove(Poteau* d, Poteau*a)
{	
	Empiler(a, Depiler(d));
}
/*******************************************************************************
*******************************************************************************/