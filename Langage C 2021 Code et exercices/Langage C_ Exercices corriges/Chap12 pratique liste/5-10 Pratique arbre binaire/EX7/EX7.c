/*Exercice 7
Simuler la gestion d'un tournoi de tennis sous la forme d'un arbre binaire. 
Les informations de chaque match sont conservées. À l'issue du tournoi, 
le match de finale se trouve à la racine de l'arbre.
*/

/*
	Nous sauegardons ici tous les joueurs et tous les match
	dans un tableau. 
	Pour simplifer le nombre de joueurs est une puissance de deux
	ce qui donne un arbre binaire plein.
	et le nom des joueurs est juste une lettre majuscule
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

#define NBJOUEUR	8  
// l'ensemble des infos correspond à la taille de l'arbre binaire + 1.
// La taille de l'arbre est seulement de (2 puissance 4)-1 mais l'indice 0
// du tableau sera ignoré
#define ALLINFO		NBJOUEUR * 2  
#define NOMATCH		0

typedef struct Joueur {
	char nom;	// les joueurs sont nommés A,B,C D...
	int gagne;	// le gagnant du match précédent
	int perd;	// le perdant du match précédent
}Joueur;

Joueur CreateJoueur(char nom, int gagne, int perd);
void InitTournois(Joueur t[]);
void PlayTournois(Joueur t[]);
Joueur Match(Joueur t[], int j1, int j2);
void AffichageVertical(Joueur t[], int r, int* x, int y);
void Gotoxy(int x, int y);
int Getposy(void);

int main()
{
	/*	Ce tableau rassemble joueurs et matchs. Chaque match est un couple de joueurs.
		Les premiers matchs sont rangés à la fin du tableau par (premier joueur indice 
		pair, second joueur indice impair) : 14 et 15 premier match ensuite 12 et 13, 
		10 et 11, 8 et 9. 
		A l'issue de chaque match le vainqueur est rangé plus avant dans l'arbre à la 
		position d'indice (indice du premier joueur) /2
	*/
	Joueur Tournois[ALLINFO];
	const racine = 1; // la racine toujours à l'indice 1
	srand(time(NULL));

	char c = 0;
	do {
		InitTournois(Tournois);
		PlayTournois(Tournois);
		int posx = 0;
		AffichageVertical(Tournois, racine, &posx, Getposy());
		printf("\nNouveau match ? (o/n)\n");
	} while ((c = getchar()) == 'o');

	return 0;
}
Joueur CreateJoueur(char nom, int gagne, int perd)
{
	return(Joueur) { nom, gagne, perd };
}
void InitTournois(Joueur t[])
{
	for (int i = ALLINFO-1; i >= NBJOUEUR; i--) {
		t[i] = CreateJoueur('A' + i - NBJOUEUR, NOMATCH, NOMATCH);
	}
}
void PlayTournois(Joueur t[])
{
	for (int i = ALLINFO - 2; i > 0; i -= 2) {
		t[i / 2] = Match(t, i, i + 1);
	}
}
Joueur Match(Joueur t[], int j1, int j2)
{
	Joueur gagnant;
	printf("%c contre % c : ", t[j1].nom, t[j2].nom);
	if (rand()%2)
		gagnant = CreateJoueur(t[j1].nom, j1, j2);// j1 gagne
	else 
		gagnant = CreateJoueur(t[j2].nom, j2, j1);// j2 gagne
	printf("%c gagne\n", gagnant.nom);

	return gagnant;
}

void AffichageVertical(Joueur t[], int r, int* x, int y)
{
	if (r != NOMATCH) {
		AffichageVertical(t, t[r].gagne, x, y + 2);
		*x += 3;
		Gotoxy(*x, y);
		printf("%c", t[r].nom);
		AffichageVertical(t, t[r].perd, x, y + 2);
	}
}
/*******************************************************
Tools utilisation console
*******************************************************/
void Gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x,y };

	// controler que le curseur ne sorte pas du buffer associé  
	// à la fenêtre pour éviter des comportements indéfinis de  
	// la console ensuite
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h, &info);

	// le curseur reste dans le buffer mais peut sortir de la fenêtre
	// (ne marche pas super lorsqu'il sort de la fenetre mais ne plante pas
	// la console, à vérifier éventuellement)
	if (c.X < info.dwSize.X && c.Y < info.dwSize.Y)
		SetConsoleCursorPosition(h, c);
}
// retourne la position vertivale du curseur en écriture
int Getposy()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	GetConsoleScreenBufferInfo(h, &info);
	return info.dwCursorPosition.Y;
}