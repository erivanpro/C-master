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
            printf("erreur cr�ation fichier binaire text.bin\n");
    }
    return 0;
}
*/
//--------------------------------------------------
//Fonction alternative � fopen : fopen_s  1
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
			printf("erreur cr�ation fichier binaire text.bin\n");
	}

	return 0;
}
*/
//--------------------------------------------------
//Fonction alternative � fopen : fopen_s  2
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
			printf("erreur cr�ation fichier binaire text.bin\n");
	}

	return 0;
}


*/

//--------------------------------------------------
//Sp�cifier un chemin d'acc�s
/*
* #define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
FILE*f;
	if ( (f=fopen("../../test.txt","w"))!=NULL)
       printf("le fichier est cr�� 2 repertoires au dessus du"
	           "repertoire ou se trouve le programme\n");
  	else
       printf("erreur cr�ation fichier\n");
  	return 0;
}
*/
//--------------------------------------------------
//Fichiers binaires
//�criture et lecture en mode binaire
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
	// ramener le curseur �criture/lecture au d�but du fichier
	rewind(f);

	if (fread(recup, sizeof(t_point), NB_POINT, f) == NB_POINT)
	  affiche(recup);
	else
	  printf("erreur lecture fichier binaire\n");
	fclose(f);
  }
  else
	printf("erreur cr�ation fichier binaire\n");

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
//�criture et lecture en mode texte
//Lecture / �criture de caract�res
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

  // ouverture fichier entr�e en lecture seule pour rappel :
  // retourne 0 si �a marche autre chose si non
  if (fopen_s(&in, "entree.txt", "r"))
	ERREUR("ouverture du fichier entree.txt")

  // ouverture sortie en �criture seule
  if (fopen_s(&out,"sortie.txt", "w"))
	ERREUR("ouverture du fichier sortie.txt")

  // lecture/�criture caract�re par caract�re
  while ((c = fgetc(in)) != EOF) {
	fputc(c, out);
	fputc(c, stdout);   // contr�le dans la fen�tre console
  }
  fclose(in);
  fclose(out);

  return 0;
}

*/
//--------------------------------------------------
//Lecture / �criture de cha�nes
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

  // ouverture fichier entr�e en lecture seule
  if (fopen_s(&in, "entree.txt", "r"))
	ERREUR("ouverture du fichier entree.txt")

  // ouverture sortie en �criture seule
  if (fopen_s(&out,"sortie.txt", "w"))
	ERREUR("ouverture du fichier sortie.txt")

  // lecture/�criture avec cha�nes de caract�res
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
//Lecture / �criture format�es
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

	// ouverture fichier entr�e en lecture seule
	// avec la version ancienne classique de fopen
	in = fopen("entree.txt", "r");
	if (in == NULL)
		// le point virgule est inutile ici
		ERREUR("ouverture du fichier entree.txt")

	// ouverture sortie en �criture seule
	if ((out = fopen("sortie.txt", "w")) == NULL)
		ERREUR("ouverture du fichier sortie.txt")

	// lecture des valeurs des nombres avec format %d
	// avec la version ancienne classique de fscanf
	fscanf(in, "%d %d %d,  ", &a, &b, &nb);

	// �criture des valeurs des nombres en cha�nes de caract�res
	// avec format %d
	fprintf(out, "%d, %d, %d, ", a, b, nb);

	// �quivalent printf, contr�le dans la fen�tre console
	fprintf(stdout, "%d, %d, %d,\n", a, b, nb);

	// r�cup�ration des nb mots
	for (i = 0; i < nb; i++) {
		fscanf(in, "%s", buf);
		fprintf(out, "%s", buf);
		printf("%s ", buf);  // contr�le dans la fen�tre console
	}
	putchar('\n');
	return 0;
}

*/
//--------------------------------------------------
// idem avec versions plus r�centes fopen_s et fscanf_s
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

	// ouverture fichier entr�e en lecture seule
	if (fopen_s(&in, "entree.txt", "r"))
		ERREUR("ouverture du fichier entree.txt")

		// ouverture sortie en �criture seule
		if (fopen_s(&out, "sortie.txt", "w"))
			ERREUR("ouverture du fichier sortie.txt")

			// lecture des valeurs des nombres avec format %d
			fscanf_s(in, "%d%d%d", &a, &b, &nb);

	// �criture des valeurs des nombres en cha�nes de caract�res
	// avec format %d
	fprintf(out, "%d, %d, %d, ", a, b, nb);

	// �quivalent printf, contr�le dans la fen�tre console
	fprintf(stdout, "%d, %d, %d,\n", a, b, nb);

	// r�cup�ration des nb mots un par un
	for (i = 0; i < nb; i++) {
		fscanf_s(in, "%s", buf, 1000);
		fprintf(out, "%s", buf);
		printf("%s ", buf);  // contr�le dans la fen�tre console
	}
	putchar('\n');
	return 0;
}
*/
//--------------------------------------------------
//Sauvegarde d'�l�ments dynamiques
// Sauvegarder et r�cup�rer un tableau dynamique
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
		// de taille al�atoire
		nb = 1 + rand() % 20;
		init(&data, nb);

		// affichage du tableau r�sultant
		affiche(data, nb);
		printf("-----------------------------\n");

		// enregistrement des nb structures du tableau
		// sur le fichier
		fwrite(data, sizeof(t_point), nb, f);

		// r�cup�ration dans un nouveau tableau dynamique
		// allou� s�par�ment
		rewind(f);
		nb = 0;
		while (!feof(f)) {
			recup = (t_point*)realloc(recup, sizeof(t_point) * (nb + 1));
			nb += fread(&recup[nb], sizeof(t_point), 1, f);
		}

		// affichage du r�sultat
		printf("load de %d struct t_point\n", nb);
		affiche(recup, nb);

		// lib�ration de la m�moire allou�e � la fin
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
//R�cup�rer des donn�es via des pointeurs
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
		printf("erreur cr�ation fichier binaire\n");
	return 0;
}
*/
/************************************************************
*															*
* Exp�rimentation : r�capitulation sauvegardes binaires     *
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

// le type de data � sauvegarder et r�cup�rer
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

	//Sauvegarde du tableau initialis�
	SaveTabStatic("tabStatic.bin", tabStat);

	// effacement du tableau : mise � 0 de tous les octets
	memset(tabStat, 0, sizeof(t_acteur) * NBMAX);
	Affiche(tabStat, NBMAX);

	// r�cup�ration des donn�es pr�c�dentes sauv�es sur fichier
	LoadTabStatic("tabStatic.bin", tabStat);
	Affiche(tabStat, NBMAX);

	// TABLEAU DYNAMIQUE
	printf("\nSEQUENCE TAB DYNAMIQUE :\n");

	// allocation du tableau sur taille al�atoire
	nbmax = 1 + rand() % NBMAX;
	tabDyn = (t_acteur*)malloc(sizeof(t_acteur) * nbmax);
	Init(tabDyn, nbmax);
	Affiche(tabDyn, nbmax);

	// sauvegarde du tableau initialis�
	SaveTabDyn("tabDyn.bin", tabDyn, nbmax);

	// effacement du tableau, d�sallocation
	free(tabDyn);

	//r�cup�ration des donn�es sauvegard�es
	nbmax = LoadTabDyn("tabDyn.bin", &tabDyn);
	Affiche(tabDyn, nbmax);

	// TABLEAU DE POINTEURS
	printf("\nSEQUENCE TAB STATIQUE DE POINTEURS :\n");
	InitTabPtr(tabPtr);
	AfficheTabPtr(tabPtr);

	// sauvegarde du tableau de pointeurs
	SaveTabPtr("tabPtr.bin", tabPtr);

	// effacement du tableau, lib�ration m�moire
	int i;
	for (i = 0; i < NBMAX; i++)
		free(tabPtr[i]);

	// R�cup�ration des donn�es sauvegard�es
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
		// obligation de sauver le nombre d'�l�ments afin de
		// pouvoir r�allouer un tableau � la r�cup�ration
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
			printf("erreur, recup�ration nombre d'"
				"�l�ments du tableau dynamique\n");
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
		// il faut sauver chaque �l�ment
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
		// obligation de les r�cup�rer un par un
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


