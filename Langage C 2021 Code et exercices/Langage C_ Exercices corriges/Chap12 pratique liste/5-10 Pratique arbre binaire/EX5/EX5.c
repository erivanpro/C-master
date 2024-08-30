/*Exercice 5
Une expression arithmétique comme (14 * 5) – (7 / 10) peut prendre la forme d'un arbre. 
Dans un programme :
1) Construire un arbre à partir d'une expression arithmétique.
2) Écrire une fonction d'évaluation de l'expression arithmétique à partir d'un arbre et 
donner son résultat.
3) Écrire une fonction qui affiche la traduction en expression postfixée.
Une expression postfixée (notation polonaise inversée) est du type :  
5  17  6 – 4 * 2 + * 
les parenthèses implicites sont : 
( 5 ( ( ( 17  6  – )  4 * )  2 + ) * ) 
ce qui équivaut, en notation classique infixée, à : 
( ( ( 17 – 6 ) * 4 ) + 2 ) * 5
4) Écrire une fonction pour construire un arbre à partir d'une expression postfixée donnée.
5) Écrire une fonction qui construit un arbre à partir d'une expression arithmétique infixée 
classique (avec parenthèses).
*/
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define MAX_SIZE_DAT	16

// les données pour l'arbre
typedef struct Noeud {
	char dat[MAX_SIZE_DAT];
	struct Noeud* g, *d;
}Noeud;

// les données pour la pile
typedef struct Elem {
	char dat[MAX_SIZE_DAT];
	struct Elem* suiv;
}Elem;

//enum{FALSE, TRUE};

Noeud* CreateArbre(char infixe[]);
Elem* InfixeToPilePrefixe(char infixe[]);
void ParcourArbrePrefixe(Noeud* r);
void ArbreToPilePrefixe(Noeud* r, Elem** pilePrefixe);
void CreateArbreFromPilePrefixe(Noeud** r, Elem** pilePrefixe);
Noeud* AlloueNoeud(void);
int HauteurArbre(Noeud* r);
int Max(int v1, int v2);
int EvaluationDepuisArbre(Noeud* r);
void _EvaluationDepuisArbre(Noeud* r, Elem** res);
void DestroyArbre(Noeud** racine);

void AffichageVertical(Noeud* r, int* x, int y);
void _AffichageVertical(Noeud* r, int* x, int y);

_Bool PileVide(Elem* pile);
void Empiler(Elem** sommet, char dat[]);
_Bool Depiler(Elem** sommet, char dat[]);
void AffichePile(Elem* sommet);
void DestroyPile(Elem** sommet);


void Gotoxy(int x, int y);
int Getposy(void);
void Pause(void);

int main()
{
	Elem* Pile = NULL;
	Noeud* Racine = NULL;
	//char Infixe[] = "((14 * 5) - (7 / 10))";
	
	// l'inconénient c'est qu'il faut systématiquement toutes les parenthèses
	// ce qui peut donner des expressions difficiles à lire :
	char Infixe[] = "( (((1+2)*(5/4)) + ((45*2)/(47-1))) *5)";  

	Racine = CreateArbre(Infixe);
	// affiche l'expression en prefixé
	printf("affichage en prefixe depuis un parcours de l'arbre :\n");
	ParcourArbrePrefixe(Racine);
	puts("\n");

	printf("affichage vertical de l'arbre :\n");
	int x = 0;
	int y = Getposy();
	AffichageVertical(Racine, &x, y);
	Gotoxy(0, y + HauteurArbre(Racine) + 5);
	
	printf("Reconstitution d'une pile en prefixe :\n");
	Elem* pilePrefixe = NULL;
	ArbreToPilePrefixe(Racine, &pilePrefixe);
	AffichePile(pilePrefixe);

	printf("Evaluation depuis arbre : %d \n", EvaluationDepuisArbre(Racine));
	DestroyArbre(&Racine);

	Pause();
	return 0;
}

/*****************************************
Gestion Arbre :
******************************************/
// 1) Construire un arbre à partir d'une expression arithmétique.
// 5) Écrire une fonction qui construit un arbre à partir d'une  
//	  expression arithmétique infixée classique(avec parenthèses).
Noeud* CreateArbre(char infixe[])
{
	Noeud* racine = NULL;
	Elem* pilePrefixe = NULL;

	pilePrefixe = InfixeToPilePrefixe(infixe);
	// afficher la pile permet d'obtenir l'expression prefixée
	printf("affichage en prefixe depuis la pile :\n");
	AffichePile(pilePrefixe);
	CreateArbreFromPilePrefixe(&racine, &pilePrefixe);
	return racine;
}
// 3) Écrire une fonction qui affiche la traduction en expression postfixée.
//	(Il suffit d'afficher la pile une fois la traduction infixe vers pile faite)
Elem* InfixeToPilePrefixe(char infixe[])
{
	Elem* resPile = NULL;
	Elem* tmp = NULL;
	
	for (int i = 0; infixe[i] != '\0'; i++) {
		char val[MAX_SIZE_DAT] = { 0 };

		if (infixe[i] == '(' || infixe[i] == ' ')
			continue;
		else if (infixe[i] == '+' || infixe[i] == '-' || infixe[i] == '*' || infixe[i] == '/') {
			val[0] = infixe[i];
			Empiler(&tmp, val);
		}
		else if (infixe[i] == ')') {
			// attention val est considéré ici en sortie de la fonction Depiler()
			Depiler(&tmp, val);
			Empiler(&resPile, val);
		}
		else if (isdigit(infixe[i])) { 
			// récupérer tous les chiffres du nombre
			for (int n = 0; infixe[i] >= '0' && infixe[i] <= '9'; i++)
				val[n++] = infixe[i];
			// à l'issue i pointe sur le caractère suivant et va encore incrémenté de 1
			// dans la boucle for principale, pour éviter de sauter un caractère il faut
			// ici le décrémenter de 1 :
			i--;  
			
			Empiler(&resPile, val);
		}
	}
	return resPile;
}
// on peut aussi parcourir l'arbre en prefixé :
void ParcourArbrePrefixe(Noeud* r)
{
	if (r) {
		printf("%s ", r->dat);
		ParcourArbrePrefixe(r->d);
		ParcourArbrePrefixe(r->g);
	}
}
/*Remarque : on peut également à partir d'un arbre reconstituer une pile
contenant l'expression préfixée. Il suffit ici d'empiler au lieu d'afficher
et pour ce faire de placer une pile vide en paramtre comme sortie de la fonction
Elem**. L'empilement se fait à l'issus du parcours (parcours postfixé)
et non à l'entrée (parcours préfixé). L'ordre du parcours est également inversé
on part d'abord à gauche et non à droite.*/
void ArbreToPilePrefixe(Noeud* r,Elem**pilePrefixe)
{
	if (r) {
		ArbreToPilePrefixe(r->g, pilePrefixe);
		ArbreToPilePrefixe(r->d, pilePrefixe);
		Empiler(pilePrefixe, r->dat);
	}
}

// 4) Écrire une fonction pour construire un arbre à partir d'une expression postfixée donnée.
void CreateArbreFromPilePrefixe(Noeud** r, Elem** pilePrefixe)
{
	char val[MAX_SIZE_DAT] = { 0 };
	if (!PileVide(*pilePrefixe)) {
		*r = AlloueNoeud();
		if(*r){
			Depiler(pilePrefixe, val);
			strcpy_s((*r)->dat, MAX_SIZE_DAT, val);
			if (val[0] == '+' || val[0] == '-' || val[0] == '*' || val[0] == '/') {
				CreateArbreFromPilePrefixe(&(*r)->d, pilePrefixe);
				CreateArbreFromPilePrefixe(&(*r)->g, pilePrefixe);
			}
		}
	}
}
Noeud* AlloueNoeud()
{
	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	if (n) {
		memset(n->dat, 0, sizeof(char) * MAX_SIZE_DAT);
		n->d = NULL;
		n->g = NULL;
	}
	return n;
}
int HauteurArbre(Noeud* r)
{
	int h = 0;
	if (r != NULL)
		h = 1 + Max(HauteurArbre(r->g), HauteurArbre(r->d));
	return h;
}
int Max(int v1, int v2)
{
	return (v1 > v2) ? v1 : v2;
}
int EvaluationDepuisArbre(Noeud* r)
{
	Elem* res = NULL;
	char v[MAX_SIZE_DAT] = { 0 };
	_EvaluationDepuisArbre(r, &res);
	Depiler(&res, v);
	return atoi(v);
}

void _EvaluationDepuisArbre(Noeud* r, Elem** res)
{
	char v1[MAX_SIZE_DAT] = { 0 };
	char v2[MAX_SIZE_DAT] = { 0 };
	char v3[MAX_SIZE_DAT] = { 0 };

	if (r != NULL) {
		_EvaluationDepuisArbre(r->d, res);
		_EvaluationDepuisArbre(r->g, res);
		if (strcmp(r->dat, "+") == 0) {
			Depiler(res, v1);
			Depiler(res, v2);
			sprintf_s(v3, MAX_SIZE_DAT, "%d", atoi(v1) + atoi(v2));
			Empiler(res, v3);
		}
		else if (strcmp(r->dat, "-") == 0) {
			Depiler(res, v1);
			Depiler(res, v2);
			sprintf_s(v3, MAX_SIZE_DAT, "%d", atoi(v1) - atoi(v2));
			Empiler(res, v3);
		}
		else if (strcmp(r->dat, "*") == 0) {
			Depiler(res, v1);
			Depiler(res, v2);
			sprintf_s(v3, MAX_SIZE_DAT, "%d", atoi(v1) * atoi(v2));
			Empiler(res, v3);
		}
		else if (strcmp(r->dat, "/") == 0) {
			Depiler(res, v1);
			Depiler(res, v2);
			sprintf_s(v3, MAX_SIZE_DAT, "%d", atoi(v1) / atoi(v2));
			Empiler(res, v3);
		}
		else
			Empiler(res, r->dat);
	}
}
/******************************************************
Affichage arbre
*******************************************************/
void AffichageVertical(Noeud* r, int*x, int y)
{
	if (r == NULL)
		printf("arbre vide\n");
	else
		_AffichageVertical(r, x, y);
}
void _AffichageVertical(Noeud* r, int* x, int y)
{
	if (r != NULL) {
		_AffichageVertical(r->g, x, y + 2);
		*x += 5;
		Gotoxy(*x, y);
		printf("%5s", r->dat);
		_AffichageVertical(r->d, x, y + 2);
	}
}
void DestroyArbre(Noeud** racine)
{
	Noeud* g, * d;
	if (*racine) {
		d = (*racine)->d;
		g = (*racine)->g;
		free(*racine);
		*racine = NULL;
		DestroyArbre(&d);
		DestroyArbre(&g);
	}
}
/*****************************************
Gestion pile
******************************************/
_Bool PileVide(Elem* pile)
{
	return pile == NULL;
}
void Empiler(Elem** sommet, char dat[])
{
	Elem* e = (Elem*)malloc(sizeof(Elem));
	if (e) {
		strcpy_s(e->dat, MAX_SIZE_DAT, dat);
		e->suiv = *sommet;
		*sommet = e;
	}
}
// le tableau dat donne une valeur en sortie  
_Bool Depiler(Elem** sommet, char dat[])
{
	_Bool res = FALSE;
	if (!PileVide(*sommet)) {
		Elem* e = *sommet;
		*sommet = (*sommet)->suiv;
		strcpy_s(dat, MAX_SIZE_DAT, e->dat);
		free(e);
		res = TRUE;
	}
	return res;
}
void AffichePile(Elem* sommet)
{
	if (PileVide(sommet))
		printf("pile vide\n");
	else {
		while (sommet != NULL) {
			printf("%s ", sommet->dat);
			sommet = sommet->suiv;
		}
		puts("\n");
	}
}
void DestroyPile(Elem** sommet)
{
	while (!PileVide(*sommet))
	{
		Elem* e = *sommet;
		*sommet = (*sommet)->suiv;
		free(e);
	}// à l'issue *sommet vaut NULL
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
void Pause()
{
	printf("\nPresser Enter pour continuer...\n");
	char c = getchar();
}
/*****************************************

******************************************/