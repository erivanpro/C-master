/*Exercice 9
Objectifs : parcourir et ajouter dans un arbre binaire
La représentation d'un domaine dont les concepts sont hiérarchisés 
sous forme d'arbre binaire peut s'appliquer aussi bien à des tâches 
de classification/identification (d'animaux, de végétaux, de minéraux...) 
qu'à des tâches de diagnostic (diagnostic médical, détection de panne...).

Par exemple :
L'ordinateur pose des questions pour essayer de découvrir 
un animal auquel vous pensez. Vous ne pouvez répondre que par OUI ou NON. 
S'il échoue, il vous demande de lui fournir une question qui caractérise 
l'animal qu'il n'a pas trouvé, ce qui permet de réaliser une certaine forme 
d'apprentissage. Trouver un animal consiste à parcourir un arbre binaire dont 
les nœuds internes sont des questions et les feuilles des animaux. La phase 
d’apprentissage consiste, si l’utilisateur le souhaite, à ajouter l’animal 
non trouvé dans l’arbre (voir trace d’exécution en page suivante).
Afin de garder une trace de cet arbre binaire, celui-ci est sauvegardé dans un fichier.

Deux approches sont possibles : sur fichier en accès direct ou en dynamique en mémoire 
centrale. 

Pour commencer, faites plutôt un arbre dynamique (mais vous pouvez opter pour un arbre 
sur fichier si vous préférez). La sauvegarde sur fichier d'un arbre dynamique pourra 
être réalisée grâce à un parcours en largeur de l'arbre.

À faire :
Définir en C la structure de données pour un nœud de l’arbre.
– À quelle(s) condition(s) sait-on différencier un noeud interne d’une feuille ?
– Quel est l’ordre de parcours (infixé, préfixé ou postfixé) de l’arbre affiché 
dans la trace d’exécution de la page suivante ? Justifier. Donner les 2 autres 
ordres de parcours.
– Écrire, commenter et tester les fonctions suivantes en respectant la trace 
d’exécution de la page suivante :
– Affichage d'un arbre de jeu.
– Parcours d'un arbre de jeu en posant les questions à l'utilisateur.
– Apprentissage d'un nouvel animal par ajout d'une question et d'une réponse.
– Toute autre fonction jugée nécessaire.
– Envisager la sauvegarde et le chargement de l'arbre dans le programme.
Pour la trace d'exécution, on a utilisé les caractères normaux pour ce qui 
est affiché à l'écran par le programme, les commentaires sont en italique 
et les réponses tapées par l'utilisateur en caractères souligné.
*/

/*VERSION DYNAMIQUE
Constituer un arbre dynamique facilite son évolution dans le jeu 
et l'on peut le convertir ensuite en arbre statique pour exécuter 
la sauvegarde. Pour le chargement nous pouvons soit récupérer l'arbre 
en statique et le convertir en dynamique, soit le récupérer directement 
en dynamique à l'aide d'un tableau de pointeurs.
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// arbre dynamique
typedef struct noeudd {
	char dat[256];
	struct noeudd*oui, *non;
}t_noeudd;
// arbre statique pour sauvegarde
typedef struct noeuds {
	char dat[256];
	int oui, non;
}t_noeuds;

// au départ si pas de fichier bin
t_noeudd* arbreInitial(void);

// les contrôles de l'arbre
void afficheArbreInfixe(t_noeudd* r, int niveau);
int	feuille(t_noeudd* n);
int	reponse(void);
void insererQuestionReponse(t_noeudd* prec);

// la sauvegarde
int	tailleArbre(t_noeudd* r);
t_noeuds* initArbreStatique(t_noeudd* r, int* nb);
int	convertDynStat(t_noeudd* r, t_noeuds* tab, int* pos);
void saveArbre(t_noeudd* r);

// le load
void lireNoeud(FILE* f, int nieme, t_noeuds* enr);
t_noeudd* convert(FILE* f, int r);
t_noeudd* loadArbreBin(void);

/*******************************************************************************
*******************************************************************************/
int main()
{
	int play = 'n', res;
	t_noeudd* r = NULL, *pos = NULL, *prec = NULL;

	r = loadArbreBin();					// s'il y a un fichier binaire chargement
	if (r == NULL)
		r = arbreInitial();				// sinon construction arbre initial

	do {									// boucle event
		printf("Nouvelle partie :\n\n");
		afficheArbreInfixe(r, 0);
		putchar('\n');
		pos = r;
		while (!feuille(pos)) {
			prec = pos;					// save position pécédente
			printf("%s", pos->dat);	// affiche question
			res = reponse();				// saisie réponse
			if (res == 'o' || res == 'n') // progression en fonction réponse
				pos = (res == 'o') ? pos->oui : pos->non;
		}
		// ici on a la feuille réponse et l'adresse du noeud père (prec)
		printf("%s\nEtes vous d'accord ?", pos->dat);
		res = reponse();
		if (res == 'n')
			insererQuestionReponse(prec); // insérer une nouvelle question-réponse
		printf("\nplay again ?(o/n)\n"); // contrôle boucle events
		play = reponse();
	} while (play == 'o');
	saveArbre(r);						// sauvegarder dans un fichier binaire
											// détruire arbre à faire
	return 0;
}
/*******************************************************************************
arbre initial : fabriquer l'arbre de départ avec les 7 noeuds proposés
(3 questions et 4 réponses)
*******************************************************************************/
t_noeudd* arbreInitial()
{
#define NBNOEUDD	7
	t_noeudd * *tab = NULL;
	t_noeudd* r = NULL;
	int i;
	tab = (t_noeudd * *)malloc(sizeof(t_noeudd*) * NBNOEUDD);// init tableau de pointeurs
	if (tab) {
		for (i = 0; i < NBNOEUDD; i++)     // une adresse pour chaque noeud
			tab[i] = (t_noeudd*)malloc(sizeof(t_noeudd));

		for (i = 0; i < NBNOEUDD; i++) { // les datas et les liens
			if (tab[i]) {
				switch (i) {
					case 0: strcpy_s(tab[i]->dat, _countof(tab[i]->dat), "Est-ce un mammifere ?");
						tab[i]->oui = tab[1];
						tab[i]->non = tab[2];
						break;
					case 1: strcpy_s(tab[i]->dat, _countof(tab[i]->dat), "Aboie t-il ?");
						tab[i]->oui = tab[3];
						tab[i]->non = tab[4];
						break;
					case 2: strcpy_s(tab[i]->dat, _countof(tab[i]->dat), "Vole t-il ?");
						tab[i]->oui = tab[5];
						tab[i]->non = tab[6];
						break;
					case 3: strcpy_s(tab[i]->dat, _countof(tab[i]->dat), "Chien");
						tab[i]->oui = NULL;
						tab[i]->non = NULL;
						break;
					case 4: strcpy_s(tab[i]->dat, _countof(tab[i]->dat), "Cheval");
						tab[i]->oui = NULL;
						tab[i]->non = NULL;
						break;
					case 5: strcpy_s(tab[i]->dat, _countof(tab[i]->dat), "Canari");
						tab[i]->oui = NULL;
						tab[i]->non = NULL;
						break;
					case 6: strcpy_s(tab[i]->dat, _countof(tab[i]->dat), "Vipere");
						tab[i]->oui = NULL;
						tab[i]->non = NULL;
						break;
				}
			}
		}
		r = tab[0];
		free(tab);
	}
	return r;
}
/*******************************************************************************
afficher arbre de jeu
*******************************************************************************/
void afficheArbreInfixe(t_noeudd* r, int niveau)
{
	int i;
	if (r != NULL) {
		afficheArbreInfixe(r->non, niveau + 1);
		for (i = 0; i < niveau; i++)
			printf("%5s", " ");
		printf("%s\n", r->dat);
		afficheArbreInfixe(r->oui, niveau + 1);
	}
}
/*******************************************************************************
*******************************************************************************/
int feuille(t_noeudd* n)
{
	return (n->oui == NULL && n->non == NULL);
}
/*******************************************************************************
*******************************************************************************/
int reponse()
{
	char res = 0;
	scanf_s("%c", &res, 1);
	rewind(stdin);
	return res;
}
/*******************************************************************************
*******************************************************************************/
void insererQuestionReponse(t_noeudd* prec)
{
	t_noeudd* q, * rep;
	q = (t_noeudd*)malloc(sizeof(t_noeudd));   // un noeud pour la questio
	rep = (t_noeudd*)malloc(sizeof(t_noeudd)); // un noeud pour la réponse
	printf("a quel animal pensiez-vous ?");  // recup réponse
	fgets(rep->dat, 256, stdin);
	rep->dat[strlen(rep->dat) - 1] = '\0';
	// recup question
	printf("Entrer une question permettant de caractériser cet animal\n"
		"et dont la réponse est oui :");
	fgets(q->dat, 256, stdin);
	q->dat[strlen(q->dat) - 1] = '\0';
	// mise en place des liens
	rep->oui = rep->non = NULL;	// la réponse est une feuille
	q->oui = rep;			   // la réponse oui est fils gauche de la question
	q->non = prec->non;		   // la réponse non est la réponse non précédente
	prec->non = q;			   // la reponse non à la quest prec donne la new quest
	printf("Maintenant je connais cet animal\n\n");
}
/*******************************************************************************
* Sauvegarder :
* 1) convertir l'arbre dynamique en arbre statique
*	- allocation tableau (+avoir taille tableau)
*	- conversion des noeuds dyn en statique
*	- regroupement + save
* 2) sauvegarde de l'arbre statique
*
************** avoir la taille de l' arbre ************************************/
int tailleArbre(t_noeudd* r)
{
	int res = 0;  // important
	if (r != NULL)
		res = 1 + tailleArbre(r->oui) + tailleArbre(r->non);
	return res; // si r==NULL, res==0
}
/************* allocation tableau de noeuds statiques *************************/
t_noeuds* initArbreStatique(t_noeudd* r, int* nb)
{
	t_noeuds* tab;
	*nb = tailleArbre(r);
	tab = (t_noeuds*)malloc(sizeof(t_noeuds) * (*nb));
	return tab;
}
/************* conversion des noeuds dynamiques en noeuds statiques ***********/
int convertDynStat(t_noeudd* r, t_noeuds* tab, int* pos)
{
	int res = -1;   // important
	if (r != NULL) {
		res = *pos;
		(*pos)++;
		strcpy_s(tab[res].dat, _countof(tab[res].dat), r->dat);   // copier les datas
		tab[res].oui = convertDynStat(r->oui, tab, pos); // créer liens
		tab[res].non = convertDynStat(r->non, tab, pos);
	}
	return res; // si r==Null, res==-1
}
/************* sauvegarde arbre statique **************************************/
void saveArbre(t_noeudd* r)
{
	t_noeuds* tab;
	int nb, pos = 0;
	FILE* f;
	tab = initArbreStatique(r, &nb);// arbre statique vide
	convertDynStat(r, tab, &pos);  // conversion-copie arbre dynamique
	fopen_s(&f,"animaux.bin", "wb");
	if (f != NULL) {
		fwrite(tab, sizeof(t_noeuds), nb, f);
		fclose(f);
	}
	else
		printf("probleme sauvegarde animaux.bin\n");
}
/*******************************************************************************
* load arbre binaire :
*	- fonction de récupération d'un noeud dans le fichier
*	- fonction de conversion des noeuds fichier vers arbre dynamique
*	- fonction ouverture fichier et regroupement
*
/**** récupération d'un noeud dans le fichier (supposé ouvert préallablement) */
void lireNoeud(FILE* f, int nieme, t_noeuds* enr)
{
	fseek(f, sizeof(t_noeuds) * nieme, SEEK_SET);
	fread(enr, sizeof(t_noeuds), 1, f);
}
/**** conversion des noeuds fichier vers arbre dynamique **********************/
t_noeudd* convert(FILE* f, int r)
{
	t_noeudd* res = NULL;  // important
	t_noeuds enr;
	if (r != -1) {
		lireNoeud(f, r, &enr);
		res = (t_noeudd*)malloc(sizeof(t_noeudd));
		if (res) {
			strcpy_s(res->dat, _countof(res->dat), enr.dat);
			res->oui = convert(f, enr.oui);
			res->non = convert(f, enr.non);
		}
	}
	return res; // si r==-1 res==NULL
}
/**** ouverture fichier et regroupement ***************************************/
t_noeudd* loadArbreBin()
{
	t_noeudd* res = NULL;
	FILE* f;
	fopen_s(&f, "animaux.bin", "rb");
	if (f != NULL) {
		res = convert(f, 0);
		fclose(f);
	}
	else
		printf("Pas de sauvegarde animaux.bin\n");
	return res;
}
/*******************************************************************************
*******************************************************************************/
