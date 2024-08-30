/*
Exercice 11
Écrire les instructions qui saisissent puis affichent une liste de chevaux de course.
Chaque cheval est entré séparément par l'utilisateur. Un cheval est défini par un nom,
un dossard, un temps réalisé dans la course, un classement et la liste est une liste
chaînée.Le programme permet d'ordonner la liste selon le classement des chevaux et
de supprimer des chevaux de la liste.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

typedef struct Cheval
{
	char nom[80];
	int dossard;  
	int temps; 
	int classement;

	// une liste symétrique facilite l'insertion dans la chaine  
	// et donc le tri pour le classement
	struct Cheval* suiv, *prec; 
}Cheval;

void Menu(void);
Cheval* SaisieCheval(int num);
void CreateNom(char nom[80]);
void AddCheval(Cheval** prem, Cheval* c);
void CreateCourse(Cheval** prem);
void DisplayCourse(Cheval* prem);
void DisplayClassement(Cheval* prem);
void Run(Cheval* prem);
void ClassementCourse(Cheval** prem);
Cheval* MoinsBonTemps(Cheval* pos);
Cheval* RemoveCheval(Cheval** prem, Cheval* c);
void SuppCheval(Cheval** prem, Cheval* c);
void DestroyCourse(Cheval** prem);

int main()
{
	int fin = 0;
	Cheval* Course = NULL;

	srand((unsigned int)time(NULL));
	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
			if (Course != NULL)
				DestroyCourse(&Course);
			printf("-----------------Participants : \n");
			CreateCourse(&Course);
			DisplayCourse(Course);
			break;

		case 'z':
			printf("-----------------Course : \n");
			Run(Course);
			DisplayCourse(Course);
			break;

		case 'e':
		{
			printf("-----------------Classement : \n");
			ClassementCourse(&Course);
			DisplayClassement(Course);
		}
			break;

		case 'r':
			Menu();
			break;

		case 'q': fin = 'q';
			break;
		}
	}
	DestroyCourse(&Course);

	return 0;
}

void Menu()
{
	printf("a : Creer une course\n");
	printf("z : Courrir\n");
	printf("q : quitter\n");
}
Cheval* SaisieCheval(int num) 
{
	Cheval* c = (Cheval*)malloc(sizeof(Cheval));
	if (c) {
		// long à entrer si beaucoup de chevaux. 
		//printf("Entrez nom : ");
		//fgets(c->nom, 80, stdin);
		// supprimer le \n ajouté par fegts à la fin
		//c->nom[strlen(c->nom)-1]='\0';

		//Je préfère faire un générateur de noms
		CreateNom(c->nom);
		
		c->dossard = num;
		c->temps = 0;
		c->classement = 0;
		c->suiv = c->prec = NULL;
	}
	return c;
}
void CreateNom(char nom[80]) // ici juste pour mémoire 80 char max
{
	char v[7] = "aeiouy";
	char c[19] = "cdfghjklmnprstvwxz";
	memset(nom, 0, sizeof(char) * 80);

	int nbl = 4;// 3 + rand() % 8;
	while (nbl--) {
		if (nbl % 2)
			nom[nbl] = v[rand() % 6];
		else
			nom[nbl] = c[rand() % 18];
	}
	//nom[strlen(nom)] = '\n';
}
void AddCheval(Cheval** prem, Cheval* c)
{
	if (c != NULL) {
		c->suiv = *prem;
		if (*prem)
			(*prem)->prec = c;
		*prem = c;
	}
}
void CreateCourse(Cheval**prem)
{
	int nbChevaux, res = 0;
	while (res == 0) {
		printf("nombre de chevaux ? : ");
		res = scanf_s("%d", &nbChevaux); // retourne 1 si ok, 0 si non
		rewind(stdin);
	}
	while (nbChevaux--) {
		AddCheval(prem, SaisieCheval(nbChevaux));
	}
}
void DisplayCourse(Cheval* prem)
{
	if (prem == NULL)
		printf("Pas de chevaux\n");
	else {
		while (prem != NULL) {
			printf("Nom        : %s\n", prem->nom);
			printf("Dossard    : %d\n", prem->dossard);
			printf("Temps      : %d\n", prem->temps);
			printf("Classement : %d\n\n", prem->classement);// saut de ligne pour suivant
			prem = prem->suiv;
		}
	}
}
void DisplayClassement(Cheval* prem)
{
	if (prem == NULL)
		printf("Pas de chevaux\n");
	else {
		while (prem != NULL) {
			printf("%d : %s (%d)\n", prem->classement, prem->nom, prem->temps);
			prem = prem->suiv;
		}
	}
}
void Run(Cheval* prem)
{
	while (prem != NULL) {
		prem->temps = 1 + rand() % 20;
		prem = prem->suiv;
	}
}

void ClassementCourse(Cheval**prem)
{
	if (*prem != NULL) {

		// ordonner la liste en fonction des temps (du meilleur au moins bon)
		Cheval* p = *prem;
		Cheval* dern = NULL;
		while (p != NULL) {
			Cheval* c = MoinsBonTemps(p);
			RemoveCheval(prem, c);
			AddCheval(prem, c);
			if (dern == NULL)
				dern = c;
			p = dern->suiv;
		}

		// établir le classement
		p = *prem;
		int pos = 0;
		int temps = 0;
		while (p != NULL) {
			if (p->temps != temps) { // à cause des ex-aequo
				pos++;
				temps = p->temps;
			}
			p->classement = pos;
			p = p->suiv;
		}
	}
}
// retourne le temps le plus long dans la liste à partir de pos
Cheval* MoinsBonTemps(Cheval* pos)
{
	Cheval* c = pos;
	while (pos->suiv != NULL) {
		if (c->temps < pos->suiv->temps)
			c = pos->suiv;
		pos = pos->suiv;
	}
	return c;
}
Cheval* RemoveCheval(Cheval** prem, Cheval* c)
{
	if (c != NULL) {
		if (c->suiv != NULL)
			c->suiv->prec = c->prec;
		if (c->prec != NULL)
			c->prec->suiv = c->suiv;
		if (*prem == c)
			* prem = c->suiv;

		c->suiv = c->prec = NULL;
	}
	return c;
}
void SuppCheval(Cheval** prem, Cheval*c)
{
	free(RemoveCheval(prem, c));
}
void DestroyCourse(Cheval** prem)
{
	while (*prem != NULL) {
		Cheval* c = *prem;
		*prem = (*prem)->suiv;
		free(c);
	}
	
}


