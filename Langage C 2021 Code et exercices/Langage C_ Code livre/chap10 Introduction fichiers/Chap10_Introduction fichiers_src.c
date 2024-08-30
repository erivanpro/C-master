/************************************************************
*															*
*       CHAPITRE 10 : Introduction Fichiers (type FILE*)	*
*															*
*************************************************************/
//Ouverture et fermeture d'un fichier
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE*f;

    if ((f=fopen("test.bin","rb"))!=NULL){
        printf("le fichier binaire test.bin existe\n");
        fclose(f);
    }
    else{
        printf("le fichier binaire test.bin n'existe pas\n");
        if ((f=fopen("test.bin","wb"))!=NULL)
        {
            printf("le fichier binaire test.bin a ete cree\n");
            fclose(f);
        }
        else
            printf("erreur création fichier binaire text.bin\n");
    }
    return 0;
}
*/
//--------------------------------------------------
//Fonction alternative à fopen : fopen_s  1
/*
#include <stdio.h> 

int main()
{
	FILE* f = NULL;
	fopen_s(&f, "test.bin", "rb");
	if (f) {
		printf("le fichier binaire test.bin existe\n");
		fclose(f);
	}
	else {
		printf("le fichier binaire test.bin n'existe pas\n");
		fopen_s(&f, "test.bin", "wb");
		if (f)
		{
			printf("le fichier binaire test.bin a ete cree\n");
			fclose(f);
		}
		else
			printf("erreur création fichier binaire text.bin\n");
	}

	return 0;
}
*/
//--------------------------------------------------
//Fonction alternative à fopen : fopen_s  2
/*
#include <stdio.h>

int main()
{
	FILE* f = NULL;

	if (fopen_s(&f, "test.bin", "rb")== 0)  {
		printf("le fichier binaire test.bin existe\n");
		fclose(f);
	}
	else {
		printf("le fichier binaire test.bin n'existe pas\n");

		if (fopen_s(&f, "test.bin", "wb")== 0)
		{
			printf("le fichier binaire test.bin a ete cree\n");
			fclose(f);
		}
		else
			printf("erreur création fichier binaire text.bin\n");
	}

	return 0;
}


*/

//--------------------------------------------------
//Spécifier un chemin d'accès
/*
* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
FILE*f;
	if ( (f=fopen("../../test.txt","w"))!=NULL)
       printf("le fichier est créé 2 repertoires au dessus du"
	           "repertoire ou se trouve le programme\n");
  	else
       printf("erreur création fichier\n");
  	return 0;
}
*/
//--------------------------------------------------
//Fichiers binaires
//Écriture et lecture en mode binaire
/*
#include <stdio.h>
#include <stdlib.h>

#define NB_POINT    10

typedef struct point {
  int x, y;
}t_point;

void    init(t_point t[]);
void    affiche(t_point t[]);

int main()
{
  FILE* f;
  t_point data[NB_POINT];
  t_point recup[NB_POINT];

  init(data);
  affiche(data);
  printf("-----------------------------\n");

  if (fopen_s(&f,"test.bin", "wb+")==0) { // version Visual Studio
	fwrite(data, sizeof(data), 1, f);
	// ramener le curseur écriture/lecture au début du fichier
	rewind(f);

	if (fread(recup, sizeof(t_point), NB_POINT, f) == NB_POINT)
	  affiche(recup);
	else
	  printf("erreur lecture fichier binaire\n");
	fclose(f);
  }
  else
	printf("erreur création fichier binaire\n");

  return 0;
}

void init(t_point t[])
{
  int i;
  for (i = 0; i < NB_POINT; i++) {
	t[i].x = rand() % 100;
	t[i].y = rand() % 100;
  }
}

void affiche(t_point t[])
{
  int i;
  for (i = 0; i < NB_POINT; i++)
	printf("t[%3d].x=%3d,.y=%3d\n", i, t[i].x, t[i].y);
}

*/
//--------------------------------------------------
//Écriture et lecture en mode texte
//Lecture / écriture de caractères
/*
#include <stdio.h>
#include <stdlib.h>
#define ERREUR(msg){\
		printf("erreur %s, Enter pour quitter\n", msg); \
		char c = getchar(); \
		exit(EXIT_FAILURE); \
}

int main(int argc, char* argv[])
{
  FILE* in, * out;
  int c;

  // ouverture fichier entrée en lecture seule pour rappel :
  // retourne 0 si ça marche autre chose si non
  if (fopen_s(&in, "entree.txt", "r"))
	ERREUR("ouverture du fichier entree.txt")

  // ouverture sortie en écriture seule
  if (fopen_s(&out,"sortie.txt", "w"))
	ERREUR("ouverture du fichier sortie.txt")

  // lecture/écriture caractère par caractère
  while ((c = fgetc(in)) != EOF) {
	fputc(c, out);
	fputc(c, stdout);   // contrôle dans la fenêtre console
  }
  fclose(in);
  fclose(out);

  return 0;
}

*/
//--------------------------------------------------
//Lecture / écriture de chaînes
/*
#include <stdio.h>

#define ERREUR(msg){\
printf("erreur %s, Enter pour quitter\n", msg); \
char c = getchar(); \
exit(EXIT_FAILURE); \
}

int main(int argc, char* argv[])
{
  FILE* in, * out;
  char buf[1000];

  // ouverture fichier entrée en lecture seule
  if (fopen_s(&in, "entree.txt", "r"))
	ERREUR("ouverture du fichier entree.txt")

  // ouverture sortie en écriture seule
  if (fopen_s(&out,"sortie.txt", "w"))
	ERREUR("ouverture du fichier sortie.txt")

  // lecture/écriture avec chaînes de caractères
  while (fgets(buf, 1000, in) != NULL) {
	fputs(buf, out);
	fputs(buf, stdout);
  }
  fclose(in);
  fclose(out);

  return 0;
}

*/
//--------------------------------------------------
//Lecture / écriture formatées
// anciennes versions des fonctions fopen et fscanf
/*
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define ERREUR(msg){\
printf("erreur %s, Enter pour quitter\n", msg); \
char c = getchar();\
exit(EXIT_FAILURE); \
}

int main(int argc, char* argv[])
{
	FILE* in, * out;
	int a, b, nb, i;
	char buf[1000];

	// ouverture fichier entrée en lecture seule
	// avec la version ancienne classique de fopen
	in = fopen("entree.txt", "r");
	if (in == NULL)
		// le point virgule est inutile ici
		ERREUR("ouverture du fichier entree.txt")

	// ouverture sortie en écriture seule
	if ((out = fopen("sortie.txt", "w")) == NULL)
		ERREUR("ouverture du fichier sortie.txt")

	// lecture des valeurs des nombres avec format %d
	// avec la version ancienne classique de fscanf
	fscanf(in, "%d %d %d,  ", &a, &b, &nb);

	// écriture des valeurs des nombres en chaînes de caractères
	// avec format %d
	fprintf(out, "%d, %d, %d, ", a, b, nb);

	// équivalent printf, contrôle dans la fenêtre console
	fprintf(stdout, "%d, %d, %d,\n", a, b, nb);

	// récupération des nb mots
	for (i = 0; i < nb; i++) {
		fscanf(in, "%s", buf);
		fprintf(out, "%s", buf);
		printf("%s ", buf);  // contrôle dans la fenêtre console
	}
	putchar('\n');
	return 0;
}

*/
//--------------------------------------------------
// idem avec versions plus récentes fopen_s et fscanf_s
/*
#include <stdio.h>

#define ERREUR(msg){\
printf("erreur %s, Enter pour quitter\n", msg); \
char c = getchar(); \
exit(EXIT_FAILURE); \
}

int main(int argc, char* argv[])
{
	FILE* in, * out;
	int a = 0, b = 0, nb = 0, i;
	char buf[1000];

	// ouverture fichier entrée en lecture seule
	if (fopen_s(&in, "entree.txt", "r"))
		ERREUR("ouverture du fichier entree.txt")

		// ouverture sortie en écriture seule
		if (fopen_s(&out, "sortie.txt", "w"))
			ERREUR("ouverture du fichier sortie.txt")

			// lecture des valeurs des nombres avec format %d
			fscanf_s(in, "%d%d%d", &a, &b, &nb);

	// écriture des valeurs des nombres en chaînes de caractères
	// avec format %d
	fprintf(out, "%d, %d, %d, ", a, b, nb);

	// équivalent printf, contrôle dans la fenêtre console
	fprintf(stdout, "%d, %d, %d,\n", a, b, nb);

	// récupération des nb mots un par un
	for (i = 0; i < nb; i++) {
		fscanf_s(in, "%s", buf, 1000);
		fprintf(out, "%s", buf);
		printf("%s ", buf);  // contrôle dans la fenêtre console
	}
	putchar('\n');
	return 0;
}
*/
//--------------------------------------------------
//Sauvegarde d'éléments dynamiques
// Sauvegarder et récupérer un tableau dynamique
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct point {
	int x, y;
}t_point;

void    init(t_point** t, int nb);
void    affiche(t_point t[], int nb);

int main()
{
	FILE* f;
	t_point* data;
	t_point* recup = NULL;
	int nb;

	srand(time(NULL));
	if (fopen_s(&f,"test.bin", "wb+")==0) {
		// allocation et initialisation d'un tableau dynamique
		// de taille aléatoire
		nb = 1 + rand() % 20;
		init(&data, nb);

		// affichage du tableau résultant
		affiche(data, nb);
		printf("-----------------------------\n");

		// enregistrement des nb structures du tableau
		// sur le fichier
		fwrite(data, sizeof(t_point), nb, f);

		// récupération dans un nouveau tableau dynamique
		// alloué séparément
		rewind(f);
		nb = 0;
		while (!feof(f)) {
			recup = (t_point*)realloc(recup, sizeof(t_point) * (nb + 1));
			nb += fread(&recup[nb], sizeof(t_point), 1, f);
		}

		// affichage du résultat
		printf("load de %d struct t_point\n", nb);
		affiche(recup, nb);

		// libération de la mémoire allouée à la fin
		free(data);
		free(recup);
		// fermeture du fichier
		fclose(f);
	}
	else
		printf("erreur creation fichier binaire\n");
	return 0;
}

void init(t_point** t, int nb)
{
	int i;
	*t = (t_point*)malloc(sizeof(t_point) * nb);
	for (i = 0; i < nb; i++) {
		(*t)[i].x = rand() % 100;
		(*t)[i].y = rand() % 100;
	}
}

void affiche(t_point t[], int nb)
{
	int i;
	for (i = 0; i < nb; i++)
		printf("t[%3d].x=%3d,.y=%3d\n", i, t[i].x, t[i].y);
}

*/
//--------------------------------------------------
//Récupérer des données via des pointeurs
/*
#include <stdio.h>
#include <stdlib.h>

typedef struct point {
	int x, y;
}t_point;

int main()
{
	FILE* f;
	t_point data = { 10,20 };
	t_point* recup;

	if (fopen_s(&f,"test.bin", "wb+")==0) {
		printf("x=%d, y=%d\n", data.x, data.y);

		fwrite(&data, sizeof(t_point), 1, f);
		rewind(f);

		recup = (t_point*)malloc(sizeof(t_point));
		fread(recup, sizeof(t_point), 1, f);

		printf("x=%d, y=%d\n", recup->x, recup->y);
		free(recup);
		fclose(f);
	}
	else
		printf("erreur création fichier binaire\n");
	return 0;
}
*/
/************************************************************
*															*
* Expérimentation : récapitulation sauvegardes binaires     *
*															*
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// macro constante pour la taille
// des tableaux statiques
#define NBMAX 5

// le type de data à sauvegarder et récupérer
typedef struct
{
	int x, y;
}t_acteur;

// pour tableau d'acteurs statique ou dynamique
void	Init(t_acteur t[], int nb);
void	Affiche(t_acteur t[], int nb);
void	SaveTabStatic(char* nameFile, t_acteur t[]);
void	LoadTabStatic(char* nameFile, t_acteur t[]);
void	SaveTabDyn(char* nameFile, t_acteur t[], int nb);
int		LoadTabDyn(char* nameFile, t_acteur** t);

// tableau statique de pointeurs
void	InitActeur(t_acteur* a);
void	InitTabPtr(t_acteur* t[]);
void	AfficheTabPtr(t_acteur* t[]);
void	SaveTabPtr(char* nameFile, t_acteur* t[]);
void	LoadTabPtr(char* nameFile, t_acteur* t[]);
/************************************************************
*************************************************************
int main()
{
	t_acteur tabStat[NBMAX];
	t_acteur* tabDyn;
	t_acteur* tabPtr[NBMAX];
	int nbmax;
	srand((unsigned)time(NULL));

	// TABLEAU STATIQUE
	printf("SEQUENCE TAB STATIQUE :\n");
	Init(tabStat, NBMAX);
	Affiche(tabStat, NBMAX);

	//Sauvegarde du tableau initialisé
	SaveTabStatic("tabStatic.bin", tabStat);

	// effacement du tableau : mise à 0 de tous les octets
	memset(tabStat, 0, sizeof(t_acteur) * NBMAX);
	Affiche(tabStat, NBMAX);

	// récupération des données précédentes sauvées sur fichier
	LoadTabStatic("tabStatic.bin", tabStat);
	Affiche(tabStat, NBMAX);

	// TABLEAU DYNAMIQUE
	printf("\nSEQUENCE TAB DYNAMIQUE :\n");

	// allocation du tableau sur taille aléatoire
	nbmax = 1 + rand() % NBMAX;
	tabDyn = (t_acteur*)malloc(sizeof(t_acteur) * nbmax);
	Init(tabDyn, nbmax);
	Affiche(tabDyn, nbmax);

	// sauvegarde du tableau initialisé
	SaveTabDyn("tabDyn.bin", tabDyn, nbmax);

	// effacement du tableau, désallocation
	free(tabDyn);

	//récupération des données sauvegardées
	nbmax = LoadTabDyn("tabDyn.bin", &tabDyn);
	Affiche(tabDyn, nbmax);

	// TABLEAU DE POINTEURS
	printf("\nSEQUENCE TAB STATIQUE DE POINTEURS :\n");
	InitTabPtr(tabPtr);
	AfficheTabPtr(tabPtr);

	// sauvegarde du tableau de pointeurs
	SaveTabPtr("tabPtr.bin", tabPtr);

	// effacement du tableau, libération mémoire
	int i;
	for (i = 0; i < NBMAX; i++)
		free(tabPtr[i]);

	// Récupération des données sauvegardées
	LoadTabPtr("tabPtr.bin", tabPtr);
	AfficheTabPtr(tabPtr);

	return 0;
}
/************************************************************
Tools
*************************************************************
void Init(t_acteur t[], int nb)
{
	int i;
	for (i = 0; i < nb; i++) {
		t[i].x = rand() % 100;
		t[i].y = 100 + rand() % 100;
	}
}
void Affiche(t_acteur t[], int nb)
{
	int i;
	for (i = 0; i < nb; i++)
		printf("(%2d,%2d)-", t[i].x, t[i].y);
	putchar('\n');
}
/************************************************************
TABLEAU STATIQUE save, load
*************************************************************
void SaveTabStatic(char* nameFile, t_acteur t[])
{
	FILE* f;
	int res;
	if (fopen_s(&f, nameFile, "wb") == 0) {
		res = fwrite(t, sizeof(t_acteur), NBMAX, f);
		printf("%d//%d acteurs sauves\n", res, NBMAX);
		fclose(f); // ne pas oublier
	}
	else
		printf("erreur save tab statique\n");
}
//
void LoadTabStatic(char* nameFile, t_acteur t[])
{
	FILE* f;
	int res;
	if (fopen_s(&f, nameFile, "rb") == 0) {
		res = fread(t, sizeof(t_acteur), NBMAX, f);
		printf("%d//%d acteurs recuperes\n", res, NBMAX);
		fclose(f);
	}
	else
		printf("erreur load tab statique\n");
}
/************************************************************
TABLEAU DYNAMIQUE save, load
*************************************************************
void SaveTabDyn(char* nameFile, t_acteur t[], int nb)
{
	FILE* f;
	int res;
	if (fopen_s(&f, nameFile, "wb") == 0) {
		// obligation de sauver le nombre d'éléments afin de
		// pouvoir réallouer un tableau à la récupération
		fwrite(&nb, sizeof(int), 1, f);
		// sauvegarde ensuite des acteurs
		res = fwrite(t, sizeof(t_acteur), nb, f);
		printf("%d//%d acteurs sauves\n", res, nb);
		fclose(f);
	}
	else
		printf("erreur save tab dynamique\n");
}
//
int LoadTabDyn(char* nameFile, t_acteur** t)
{
	FILE* f;
	int res, nb = -1;
	if (fopen_s(&f, nameFile, "rb") == 0) {
		if (1 == fread(&nb, sizeof(int), 1, f)) {
			// allocation d'un tableau de nb acteurs
			*t = (t_acteur*)malloc(sizeof(t_acteur) * nb);
			res = fread(*t, sizeof(t_acteur), nb, f);
			printf("%d//%d acteurs recuperes\n", res, nb);
			fclose(f);
		}
		else
			printf("erreur, recupération nombre d'"
				"éléments du tableau dynamique\n");
	}
	else
		printf("erreur load tab dynamique\n");
	return nb; // -1 si erreur
}
/************************************************************
TABLEAU DE POINTEURS save, load
*************************************************************
void InitActeur(t_acteur* a)
{
	a->x = rand() % 100;
	a->y = rand() % 100 + 100;
}
//
void InitTabPtr(t_acteur* t[])
{
	int i;
	for (i = 0; i < NBMAX; i++) {
		t[i] = (t_acteur*)malloc(sizeof(t_acteur));
		InitActeur(t[i]);
	}
}
//
void AfficheTabPtr(t_acteur* t[])
{
	int i;
	for (i = 0; i < NBMAX; i++)
		printf("(%2d,%2d)-", t[i]->x, t[i]->y);
	putchar('\n');
}
//
void SaveTabPtr(char* nameFile, t_acteur* t[])
{
	FILE* f;
	int i, res;
	if (fopen_s(&f, nameFile, "wb") == 0) {
		// il faut sauver chaque élément
		for (i = 0, res = 0; i < NBMAX; i++)
			res += fwrite(t[i], sizeof(t_acteur), 1, f);
		printf("%d//%d acteurs sauves\n", res, NBMAX);
		fclose(f);
	}
	else
		printf("erreur save tab pointeurs\n");
}
//
void LoadTabPtr(char* nameFile, t_acteur* t[])
{
	FILE* f;
	int i, res;
	if (fopen_s(&f, nameFile, "rb") == 0) {
		// obligation de les récupérer un par un
		for (i = 0, res = 0; i < NBMAX; i++) {
			t[i] = (t_acteur*)malloc(sizeof(t_acteur));
			res += fread(t[i], sizeof(t_acteur), 1, f);
		}
		printf("%d//%d acteurs recuperes\n", res, NBMAX);
		fclose(f);
	}
	else
		printf("erreur load tab pointeurs\n");
}
/************************************************************
************************************************************/


