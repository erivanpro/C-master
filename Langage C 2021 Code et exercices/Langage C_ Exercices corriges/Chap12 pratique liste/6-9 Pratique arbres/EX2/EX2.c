/*
Exercice 2
Faire un compteur d'occurrence de mots à partir d'un texte 
fourni par exemple sur fichier texte.
*/
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define MAXNOEUD	16
#define MAXSIZEMOT	256
#define FILETXTNAME			"texte.txt"
#define FILECOPIETXTNAME	"copie sans ponctuation.txt"
typedef struct Noeud
{
	int cmp;	// compteur occurrence du mot
	char mot[MAXSIZEMOT];
	struct Noeud *g, *d;
}Noeud;

void Inserer(Noeud** r, Noeud* n);
Noeud* CreateNoeud(char* mot);
void DestroyArbre(Noeud** r);
_Bool CopieTexteSansPonctuation(void);
void ParcourInfixe(Noeud* r);
void Pause();

int main()
{
	// pour l'accentuation : ISO 8859-1 Latin 1; Western European (ISO)
	// https://docs.microsoft.com/en-us/windows/console/setconsoleoutputcp
	// https://docs.microsoft.com/fr-fr/windows/desktop/Intl/code-page-identifiers
	SetConsoleOutputCP(28591);

	if (CopieTexteSansPonctuation()) {
		FILE* copietxt;
		fopen_s(&copietxt, FILECOPIETXTNAME, "r");
		if (copietxt != NULL) {
			Noeud* Racine = NULL;
			while (!feof(copietxt)) {
				char mot[MAXSIZEMOT] = { 0 };
				// les espaces servent de séparateurs et scanf ne retourne pas de chaine vide 
				fscanf_s(copietxt, "%s", mot, MAXSIZEMOT);
				Inserer(&Racine, CreateNoeud(mot));
			}
			ParcourInfixe(Racine);
			fclose(copietxt);
			DestroyArbre(&Racine);
		}
		else
			printf("erreur ouverture copie du texte sans ponctuation\n");
	}
	else
		printf("erreur création copie du texte sans ponctuation\n");

	Pause();
	return 0;
}

/******************************************************
Créer et détruire arbre
*******************************************************/
// insérer un mot dans l'arbre par ordre alphabétique
void Inserer(Noeud** r, Noeud* n)
{
	if (*r == NULL)
		* r = n;
	else {
		int cmp = strcmp(n->mot, (*r)->mot);
		if (cmp == 0) { // si le mot est déjà dans l'arbre incrémenter le compteur
			(*r)->cmp++;
			free(n);
		}
		else if (cmp < 0)
			Inserer(&(*r)->g, n);
		else
			Inserer(&(*r)->d, n);
	}
}
// créer un noeud
Noeud* CreateNoeud(char*mot)
{
	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	if (n) {
		strcpy_s(n->mot, MAXSIZEMOT, mot);
		n->cmp = 1;
		n->d = n->g = NULL;
	}
	return n;
}
void DestroyArbre(Noeud** r)
{
	if (*r != NULL) {
		Noeud* n = *r;
		DestroyArbre(&(*r)->g);
		DestroyArbre(&(*r)->d);
		free(*r);
		*r = NULL;
	}
}
/******************************************************
supprimer la ponctuation
*******************************************************/
_Bool CopieTexteSansPonctuation()
{
	FILE* f,*copie;
	fopen_s(&f, FILETXTNAME, "r+");
	fopen_s(&copie, FILECOPIETXTNAME, "w");
	if (f != NULL && copie != NULL) {
		char c;
		while ((c = getc(f)) != EOF) {
			if (c == ',' || c == ';' || c == ':' || c == '.' || c == '?' || c == '!' || c == '_') {
				fputc(' ', copie);
			}
			else
				fputc(c, copie);

		}
		fclose(f);
		fclose(copie);
		return TRUE;
	}
	else
		printf("copie texte abandonnée\n");
	
	return FALSE;
}
/******************************************************
Afficher en ordre alphabétique
*******************************************************/
void ParcourInfixe(Noeud* r)
{
	if (r != NULL) {
		ParcourInfixe(r->g);
		printf("%-20s : %d\n", r->mot, r->cmp);
		ParcourInfixe(r->d);
	}
}
/******************************************************
Tools console
*******************************************************/
void Pause()
{
	printf("\nPresser Enter pour continuer...\n");
	char c = getchar();
}
/******************************************************
*******************************************************/