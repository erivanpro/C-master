/*
Exercice 5
Les internautes utilisent un logiciel pour naviguer sur Internet. Parmi ces fonctions 
il y a celle qui permet de revenir sur une page déjà accédée via son adresse URL 
(http://www...). Cette fonction est activée à l'aide de l'icône représentant la flèche. 
Pour réaliser cette fonctionnalité, le navigateur conserve un historique des adresses URL 
de chaque page accédée de façon à pouvoir y accéder de nouveau au besoin. Les adresses des 
pages sont mémorisées selon l'ordre d'accès du plus récent au moins récent. Après un certain 
temps, cet historique peut contenir la même page plus d'une fois. On souhaite pouvoir éviter 
les doublons : ne garder en mémoire qu’une seule version URL de chaque page multiple, ceci 
tout en préservant l’ordre d’accès du plus récent au moins récent.
Programmer une simulation.
1) Quelle structure de données envisager ?
2) Tester avec un programme qui initialise un historique d’adresses URL contenant des doublons.
3) Comment éviter les doublons dans l'historique ? Quelle solution pour référencer toutes les 
pages, y compris multiples, sans garder leur adresse URL en doublon ?
*/


/* SOLUTION 1  / Bilan : 
-Une liste chainée simple en guise de pile représentant l'historique complet 
des adresses uml.
-Un controle des urls de façon à ce que chaque url n'existe qu'une fois
en mémoire. 
-Une sous-liste des sites visités.

Inconvénients :
- Certes chaque url n'existe qu'une fois mais c'est pas vraiment utile ni pratique dans ce contexte
(rajoute des possibilités d'erreurs difficiles à détecter).
- Au final nous avons deux listes une pour l'historique et une autre pour les visites (sans doublon)
- Chaque changement dans l'historique nécessite de supprimer l'ancienne liste de visites et d'en 
construire une nouvelle.

Il serait plus pratique de stocker toutes les urls dans un unique tableau dynamique de char* (en 
veillant à conserver l'ordre des visites) avec une seule adresse mémoire par urls. Ensuite il suffit 
de lire tout le tableau pour avoir l'historique complet, ou de lire dans l'ordre chronologique 
de l'empilement une seule fois chaque url pour visualiser uniquement les urls visitées. (solution 2)

*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define FIN		-1
enum { FALSE, TRUE };

typedef struct Url {
	char* url;
	struct Url* suiv;
}Url;

void Menu();
int SaisieNombre(char* msg);
char* SelectUrl(Url* sommet);
Url* CreateUrl(char* url);
void EmpilerUrl(Url** sommet, Url* u);
void DisplayUrls(Url* sommet, char*msg);
Url* VisitUrls(Url* historique);
_Bool AbsentUrl(Url* visit, Url* u);
Url* DepilerUrl(Url** sommet);
void DestroyAll(Url** histo, Url** visit);
void DestroyUrls(Url** urls);

int main()
{
	int fin = 0;
	// listes chainées de Urls
	Url* Historique = NULL;
	Url* Visites = NULL;
	

	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
		{
			int nb = SaisieNombre("Combien d'urls ? ");
			for (int i = 0; i < nb; i++)
				EmpilerUrl(&Historique, CreateUrl(SelectUrl(Historique)));
			DisplayUrls(Historique, "AFFICHAGE HISTORIQUE :");
		}
			break;

		case 'z':
			if (Visites != NULL)
				DestroyUrls(&Visites);
			Visites = VisitUrls(Historique);
			DisplayUrls(Visites, "AFFICHAGE SITES VISITES :");
			break;
		
		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyAll(&Historique, &Visites);
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
char* SelectUrl(Url*sommet)
{
	// récupératin URL
	char buf[1024];
	char* url = NULL;
	
	printf("Entrez URL : ");
	fgets(buf, 1024, stdin);
	buf[strlen(buf) - 1] = '\0'; // supprimer '\n' de fin

	// si déjà présente récupérer l'existante
	while (sommet != NULL) {
		if (strcmp(buf, sommet->url) == 0) {
			url = sommet->url;
			break;
		}
		sommet = sommet->suiv;
	}
	// si non créer son adresse et recopier l'entrée dans buf
	if (url == NULL) {
		int max = strlen(buf) + 1;
		url = (char*)malloc(sizeof(char) * max);
		if (url)
			strcpy_s(url, sizeof(char) * max, buf);
	}
	
	return url;
}
Url* CreateUrl(char*url)
{
	Url* u = (Url*)malloc(sizeof(Url));
	if (u) {
		u->url = url;
		u->suiv = NULL;
	}
	return u;
}
void EmpilerUrl(Url** sommet, Url* u)
{
	if (u != NULL) {
		u->suiv = *sommet;
		*sommet = u;
	}
}
void DisplayUrls(Url* sommet, char*msg)
{
	printf("%s\n", msg);
	while (sommet != NULL) {
		printf("%s\n", sommet->url);
		sommet = sommet->suiv;
	}
	putchar('\n');
}

Url* VisitUrls( Url* historique)
{
	Url* vst = NULL;
	// TODO : voir si ça marche
	while (historique != NULL) {
		if (AbsentUrl(vst, historique))
			// inconvénient 1 : on est obligé de créer uns sous liste des sites visités
			// parce qu'on ne peut pas modifier l'historique sans le perdre.
			EmpilerUrl(&vst, CreateUrl(historique->url));
		historique = historique->suiv;
	}
	// inconvénient 2 ici il faut remettre 
	// ensuite la liste des visites à l'endroit
	Url* visit = NULL;
	while (vst != NULL) {
		EmpilerUrl(&visit, DepilerUrl(&vst));
	}
	return visit;
}
_Bool AbsentUrl(Url* visit, Url* u)
{
	_Bool res = TRUE;
	while (visit != NULL) {
		if (visit->url == u->url) {
			res = FALSE;
			break;
		}
		visit = visit->suiv;
	}
	return res;
}
Url* DepilerUrl(Url** sommet)
{
	Url* res = NULL;
	if (*sommet != NULL) {
		res = *sommet;
		*sommet = (*sommet)->suiv;
		res->suiv = NULL; // attention ne pas oublier
	}
	return res;
}
void DestroyAll(Url** histo, Url** visit)
{
	// destruction des chaines allouées dynamiquement
	while (*visit != NULL) {
		free((*visit)->url);
		(*visit)->url = NULL;
		*visit = (*visit)->suiv;
	}
	// destruction uniquement des maillons Url*
	DestroyUrls(visit);
	DestroyUrls(histo);

}
void DestroyUrls(Url**urls)
{
	// il s'agit de désallouer uniquement les Url* mais de conserver
	// les chaines de caractères allouées dynamiquement (les champs url)
	while (*urls != NULL) {
		Url* u = DepilerUrl(urls);
		//*urls = (*urls)->suiv;
		free(u);
	}
}
