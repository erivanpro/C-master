/*
Exercice 5
Les internautes utilisent un logiciel pour naviguer sur Internet. Parmi ces fonctions 
il y a celle qui permet de revenir sur une page d�j� acc�d�e via son adresse URL 
(http://www...). Cette fonction est activ�e � l'aide de l'ic�ne repr�sentant la fl�che. 
Pour r�aliser cette fonctionnalit�, le navigateur conserve un historique des adresses URL 
de chaque page acc�d�e de fa�on � pouvoir y acc�der de nouveau au besoin. Les adresses des 
pages sont m�moris�es selon l'ordre d'acc�s du plus r�cent au moins r�cent. Apr�s un certain 
temps, cet historique peut contenir la m�me page plus d'une fois. On souhaite pouvoir �viter 
les doublons : ne garder en m�moire qu�une seule version URL de chaque page multiple, ceci 
tout en pr�servant l�ordre d�acc�s du plus r�cent au moins r�cent.
Programmer une simulation.
1) Quelle structure de donn�es envisager ?
2) Tester avec un programme qui initialise un historique d�adresses URL contenant des doublons.
3) Comment �viter les doublons dans l'historique ? Quelle solution pour r�f�rencer toutes les 
pages, y compris multiples, sans garder leur adresse URL en doublon ?
*/

/* SOLUTION 2 : 
Une pile constitu�e d'un tableau dynamique de char* qui contient toutes les urls chacune
en un seul exemplaire m�moire. Cet ensemble permet de restituer � la fois l'historique et les 
visites en respectant l'ordre chronologique du plus r�cent au moins r�cent.
Solution beaucoup plus simple que la pr�c�dente et moins sujette � erreur.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define FIN		-1
enum { FALSE, TRUE };

typedef struct PileUrls {
	int size;
	int sommet;
	char** p;
}PileUrls;

void Menu();
int SaisieNombre(char* msg);
PileUrls CreatePileUrls();
void AddUrl(PileUrls* pu);
char* SelectUrl();
char** ResizeTabUrls(PileUrls* t);
void DisplayHistorique(PileUrls* pu);
void DisplayVisites(PileUrls* pu);
void DestroyPile(PileUrls* pu);

int main()
{
	int fin = 0;
	// listes chain�es de Urls
	PileUrls PU = CreatePileUrls(); // ne pas oublier

	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
		{
			int nb = SaisieNombre("Combien d'urls ? ");
			for (int i = 0; i < nb; i++)
				AddUrl(&PU);
			DisplayHistorique(&PU);
		}
		break;

		case 'z':
			DisplayVisites(&PU);
			break;

		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyPile(&PU);
	return 0;
}
void Menu()
{
	printf("a : Entrer nouvelle URL\n");
	printf("z : Afficher sites visites\n");
}
int SaisieNombre(char* msg)
{
	int nb = 0, res = 0;
	do {
		printf(msg);
		res = scanf_s("%d", &nb);
		rewind(stdin);
	} while (res != 1);
	return nb;
}
PileUrls CreatePileUrls()
{
	PileUrls t = { 1,0,NULL };
	t.p = (char**)malloc(sizeof(char*) * t.size);
	for (int i = 0; i < t.size; i++)
		t.p[i] = NULL;
	return t;
}
void AddUrl(PileUrls* pu)
{
	char* url = SelectUrl();

	// v�rifier la taille de la pile
	if (pu->sommet >= pu->size) {
		if (!ResizeTabUrls(pu)) {
			printf("erreur redimensionnement de la pile\n");
			return;
		}
	}

	// rechercher si l'url est d�j� pr�sente
	for (int i = 0; i < pu->sommet; i++) {
		// si oui prendre l'existante et empiler
		if (strcmp(pu->p[i], url) == 0) {
			pu->p[pu->sommet++] = pu->p[i];
			free(url);
			url = NULL;
			break;
		}
	}
	// si non empiler la nouvelle
	if (url != NULL)
		pu->p[pu->sommet++] = url;
}
char* SelectUrl()
{
	// r�cup�ratin URL
	char buf[1024];
	char* url = NULL;

	printf("Entrez URL : ");
	fgets(buf, 1024, stdin);
	buf[strlen(buf) - 1] = '\0'; // supprimer '\n' de fin

	int max = strlen(buf) + 1;
	url = (char*)malloc(sizeof(char) * max);
	if(url)
		strcpy_s(url, sizeof(char) * max, buf);
	return url;
}
char** ResizeTabUrls(PileUrls* t)
{
	t->size *= 2;
	char**moreSize = (char**)realloc(t->p, sizeof(char*) * t->size);
	if (moreSize != NULL)
		t->p = moreSize;

	for (int i = t->sommet; i < t->size; i++)
		t->p[i] = NULL;

	return moreSize;
}
void DisplayHistorique(PileUrls* pu)
{
	printf("AFFICHAGE HISTORIQUE : \n");
	if (pu->sommet == 0)
		printf("historique vide\n");
	else {
		for (int i = pu->sommet - 1; i >= 0; i--) {
			printf("%s\n", pu->p[i]);
		}
	}
}
void DisplayVisites(PileUrls* pu)
{
	printf("AFFICHAGE VISITEES : \n");
	if (pu->sommet == 0)
		printf("pas de visite\n");
	else {
		// afficher la premi�re 
		printf("%s\n", pu->p[pu->sommet-1]);
		for (int i = pu->sommet - 2; i >= 0; i--) {
			// afficher uniquement si pas encore affich�e
			_Bool trouve = FALSE;
			for (int j = pu->sommet - 1; j > i; j--) {
				if (pu->p[j] == pu->p[i]) {
					trouve=TRUE;
					break;
				}
			}
			if (trouve == FALSE)
				printf("%s\n", pu->p[i]);
		}
	}
}
void DestroyPile(PileUrls* pu)
{
	if (pu->sommet != 0) {
		for (int i = 0; i < pu->sommet; i++) {
			// mettre � NULL les m�me adresse de l'historique
			if (pu->p[i] != NULL) {
				char* url = pu->p[i];
				for (int j = 0; j < pu->sommet; j++) {
					if (pu->p[j] == url)
						pu->p[j] = NULL;
				}
				free(url);
			}
		}
		free(pu->p);
		pu->p = NULL;
	}
}

