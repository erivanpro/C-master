/*Exercice 6
Soit la description suivante :
Homme : tête, cou, tronc, bras, jambe ;
tête : crâne, yeux, oreilles, cheveux, bouche ;
tronc : abdomen, thorax ;
thorax : coeur, foie, poumons ;
jambe : cuisse, mollet, pied ;
pied : coup-de-pied, orteils, talon ;
bras : épaule, avant-bras, main ;
main : doigts ;
Dans un programme, faire l'arbre n-aire, puis l'arbre binaire correspondant.
Sur le modèle de cette description, faire l'arbre des composants d'une voiture. 
Toujours sur ce modèle analyser un sujet ou un objet de son choix et représenter 
l'arbre correspondant dans un programme.
*/

/*
	Notre solution propose un arbre n-aire dans lequel chaque noeud contient
	un tableau de noeud fils.

	La solution en binaire est très proche, se reporter à l'exercice 4. 
	Pour une voiture ou un autre sujet cette solution fonctionne. Libre à vous 
	d'en essayer une autre.

	Attention : 
	En ce qui concerne le fichier :
	- il doit se terminner avec une ligne vide (retour chariot 
	juste après le dernier ;)
	- supprimer les caractères spéciaux ( oe de coeur)
	- relier les expression constituées de plusieurs mots
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>

typedef struct Noeud {
	char*nom;
	struct Noeud** fils; // tableau dynamique de Noeud*
}Noeud;

void CreateArbre(FILE* f, Noeud** racine);
char* NextLigne(FILE* f);
int CompteMots(char* ligne);
Noeud* CreateNoeud(char* nom);
Noeud* RecupNoeudArbre(Noeud* r, char* nom);
void Affichage(Noeud* r);
void DestroyArbre(Noeud** r);
void Pause(void);

int main()
{
	// pour l'accentuation : ISO 8859-1 Latin 1; Western European (ISO)
	// https://docs.microsoft.com/en-us/windows/console/setconsoleoutputcp
	// https://docs.microsoft.com/fr-fr/windows/desktop/Intl/code-page-identifiers
	SetConsoleOutputCP(28591);

	FILE* f;
	fopen_s(&f, "datas arbre.txt", "r");
	if (f) {
		Noeud* racine = NULL;
		CreateArbre(f, &racine);
		Affichage(racine);
		DestroyArbre(&racine);
		fclose(f);
	}
	else {
		printf("impossible ouvrir \"arbre.dat\" Enter pour quitter\n");
		char c = getchar();
	}
	Pause();
	return 0;
}
/*****************************************************
	Récupération des données sur fichier
	et construction de l'arbre
******************************************************/
void CreateArbre(FILE* f, Noeud** racine)
{
	// en principe ici le fichier existe et est ouvert en lecture
	char* ligne = NextLigne(f);
	if (ligne) {
		// Après récupération de la ligne courante il s'agit tout d'abord de 
		// dissocier les mots et de les stocker dans un tableau.
		// num Ce tableau contient un pointeur NULL en dernière position d'ou le + 1
		int num = CompteMots(ligne) + 1;
		char** noms = (char**)malloc(sizeof(char*) * num);
		if (noms) {
			// met à 0 (donc NULL) toutes les positions
			memset(noms, 0, sizeof(char*) * num);
			// num sert maintenant à se positionner dans le tableau en commençant au début
			num = 0;
			// récupération des noms de la ligne avec strok_s()
			// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/strtok-s-strtok-s-l-wcstok-s-wcstok-s-l-mbstok-s-mbstok-s-l?view=vs-2019
			noms[num] = strtok_s(ligne, " :,;\n", &ligne);
			while (noms[num] != NULL)
				noms[++num] = strtok_s(NULL, " :,;\n", &ligne);
			//ici num vaut num-1
			
			// liste des noeuds fils de 1 à num (num-1 éléments)
			Noeud**tabFils = NULL;
			tabFils = (Noeud**)malloc(sizeof(Noeud*) * num);
			if (tabFils) {
				memset(tabFils, 0, sizeof(Noeud*) * num);
				for (int i = 0; noms[i+1] != NULL; i++) {
					tabFils[i] = CreateNoeud(noms[i+1]);
				}
			}

			// ajout dans l'arbre
			if (*racine == NULL) {// si rien c'est le nom pour la racine de l'arbre
				*racine = CreateNoeud(noms[0]);
				(*racine)->fils = tabFils; // et le tableau des fils fils
			}
			// si la racine existe
			else {
				// chercher le premier nom dans l'arbre
				Noeud* pos = RecupNoeudArbre(*racine, noms[0]);
				if (pos) { // s'il existe le premier frere de la ligne est fils du noeud trouvé
					pos->fils = tabFils;
				}
			}
			// libérer le tableau de noms mais sans toucher aux noms
			free(noms);
		}
		// reprendre tout pour la ligne suivante
		CreateArbre(f, racine);
	}
}
// récupérer une ligne
char* NextLigne(FILE* f)
{
	char rec[2048] = { 0 };
	char* res = NULL;

	fgets(rec, 2048, f);
	size_t nbchar = strlen(rec);
	if (nbchar > 0) {
		rec[nbchar - 1] = '\0'; // suppression '\n' final
		res = (char*)malloc(sizeof(char) * nbchar);
		if (res)
			strcpy_s(res, nbchar, rec);
	}
	return res;
}
int CompteMots(char* ligne)
{
	int cmpt = 0;
	for (int i = 0; ligne[i] != '\0'; i++)
		if (ligne[i] == ':' || ligne[i] == ',' || ligne[i] == ';')
			cmpt++;
	return cmpt;
}

Noeud* CreateNoeud(char* nom)
{
	Noeud* n = (Noeud*)malloc(sizeof(Noeud));
	if (n) {
		n->nom = nom;
		n->fils = NULL;
	}
	return n;
}

Noeud* RecupNoeudArbre(Noeud* r, char* nom)
{
	Noeud* n = NULL;
	if (r != NULL) {
		if (strcmp(r->nom, nom) == 0)
			n = r;
		else if (r->fils != NULL) {
			for (int i = 0; r->fils[i] != NULL; i++) {
				n = RecupNoeudArbre(r->fils[i], nom);
				if (n != NULL)
					break;
			}
		}
	}
	return n;
}
/******************************************************
Affichage arbre
L'affichage finalement le plus simple et lisible est 
celui que nous avons dans le fichier. Cette fonction
retrace l'arbre comme il est dans le fichier en 
modifiant un peu l'ordre des lignes.
En admettant que le programme permette d'ajouter des 
éléments dans l'arbre il serait du coup facile de le 
sauvegarder (juste afficher l'afficher l'arbre dans
un fichier)
*******************************************************/
void Affichage(Noeud* r)
{
	if (r != NULL) {
		printf("%s : ", r->nom);
		if (r->fils != NULL) {
			for (int i = 0; r->fils[i] != NULL; i++) {
				printf("%s", r->fils[i]->nom);
				if (r->fils[i + 1] == NULL)
					printf(";\n");
				else
					printf(", ");
			}
			
			for (int i = 0; r->fils[i] != NULL; i++)
				if(r->fils[i]->fils != NULL)
					Affichage(r->fils[i]);
		}
	}
}

/*****************************************************
	Destruction de l'arbre
******************************************************/
void DestroyArbre(Noeud** r)
{
	if (*r != NULL) { 
		if ((*r)->fils != NULL) {
			for (int i = 0; (*r)->fils[i] != NULL; i++)
				DestroyArbre(&(*r)->fils[i]);
		}
		free(*r);
		*r = NULL;
	}
}
/*******************************************************
Tools
********************************************************/
void Pause()
{
	printf("Appuyez sur enter pour continuer...\n");
	char c = getchar();
}
