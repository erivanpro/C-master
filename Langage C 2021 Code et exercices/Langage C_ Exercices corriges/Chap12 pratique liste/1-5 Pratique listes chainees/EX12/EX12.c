/*
Exercice 12 (suppose fichier)
Écrire un programme permettant de lire un texte à partir d'un fichier. Chaque mot
du texte est récupéré dans une liste chaînée qui regroupe tous les mots du texte.
Les mots sont dans l'ordre du texte sur le fichier et il n'y a pas de répétition
de mots.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>

enum{FALSE,TRUE};

typedef struct Mot
{
	char *mot;
	struct Mot *suiv;
}Mot;

void AddMotBack(Mot** prem, Mot** dern, Mot* m);
void SuppPonctuation(char m[80]);
void RecupText(Mot** prem, Mot** dern, char* txt);
Mot* CreateMot(char mot[80]);
_Bool IsAbsent(Mot* prem, char* mot);
void DisplayText(Mot* prem);
void DestroyText(Mot** prem, Mot**dern);
void Pause();

int main()
{
	Mot* Prem = NULL;
	Mot* Dern = NULL;
	
	//RecupText(&Prem, &Dern, "_texte pour tests.txt");
	RecupText(&Prem, &Dern, "hartley_potts_cultural_science.txt");
	DisplayText(Prem);
	DestroyText(&Prem, &Dern);

	Pause();
	return 0;
}
void AddMotBack(Mot** prem, Mot** dern, Mot* m)
{
	if (*prem == NULL)
		* prem = *dern = m;
	else {
		(*dern)->suiv = m;
		*dern = m;
	}
}
void RecupText(Mot**prem, Mot**dern, char* txt)
{
	FILE* f;
	// ouverture en lecture et écriture afin de pouvoir supprimer la ponctuation
	fopen_s(&f, txt, "r+"); 
	if(f){
		char mot[80] = { 0 };
		while (fscanf_s(f, "%s", mot, 80) != EOF) {
			SuppPonctuation(mot);
			if (IsAbsent(*prem, mot)) {
				Mot* m = CreateMot(mot);
				AddMotBack(prem, dern, m);
			}
		}
		fclose(f);
	}
	else
		printf("impossible ouvrir le fichier %s", txt);
}
void SuppPonctuation(char m[80])// 80 max pour mémoire
{
	for(int i = 0; m[i] != '\0'; i++){
		if (m[i] == ',' || m[i] == ';' || m[i] == '.' || m[i] == ':' || m[i] == '!' || m[i] == '?' || m[i]== ' ')
			m[i] = '\0';
	}
}
Mot* CreateMot(char mot[80])// 80 pour mémoire
{
	Mot* m = (Mot*)malloc(sizeof(Mot));
	if (m) {
		m->suiv = NULL;
		m->mot = (char*)malloc(sizeof(char) * (strlen(mot) + 1) );// +1 pour '\0'
		if (m->mot) {
			// le 2e param indique la taille exacte allouée pour m->mot
			strcpy_s(m->mot, sizeof(char) * (strlen(mot) + 1), mot);
		}
	}
	return m;
}
_Bool IsAbsent(Mot* prem, char*mot)
{
	_Bool res = TRUE;
	// pour éviter un mot vide (par exemple une virgule isolée ou un espace en trop)
	if (strlen(mot) < 2) 
		res = FALSE;
	else {
		while (prem != NULL) {
			if (strcmp(prem->mot, mot) == 0) {
				res = FALSE;
				break;
			}
			prem = prem->suiv; // attention, ne pas oublier
		}
	}
	return res;
}
void DisplayText(Mot* prem)
{
	int i = 1;
	while (prem != NULL) {
		printf("%s ", prem->mot);
		prem = prem->suiv;
		if ((i++) % 10 == 0) {
			putchar('\n');
		}
	}
}
void DestroyText(Mot** prem, Mot**dern)
{
	while (*prem != NULL) {
		Mot* m = *prem;
		*prem = (*prem)->suiv;
		free(m->mot);
		free(m);
	}
	*prem = NULL;
	*dern = NULL;
}
void Pause()
{
	printf("\nAppuyez sur Enter pour continuer");
	getchar();
}
