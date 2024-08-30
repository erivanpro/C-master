/*
JEU DES ANIMAUX VERSION 2 
Arbre sur fichier en accès direct
*/
#include <stdlib.h>
#include <stdio.h>

typedef struct noeuds {
	char dat[256];
	int g, d;
}t_noeuds;

int	reponse(void);
void lireNoeud(FILE* f, int nieme, t_noeuds* enr);
void ecrireNoeud(FILE* f, int nieme, t_noeuds* enr);
void fichierArbreInfixe(FILE* f, int r, int niveau);
int	feuille(FILE* f, int pos, t_noeuds* enr);
int	tailleArbreFichier(FILE* f, int r);
void ajoutQuestionReponse(FILE* f, int prec);
/*******************************************************************************
*******************************************************************************/
int main()
{
	FILE* f;
	t_noeuds enr;
	int play = 0, pos, prec, res;

	printf("ouverture du fichier animaux.bin\n");// ouverture fichier 
	if ((f = fopen("animaux.bin", "r+b")) == NULL) {		// en cas d'erreur
		printf("erreur ouverture animaux.bin\n");
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	do {											// boucle d'évémenents
		printf("\nNouvelle partie :\n");
		fichierArbreInfixe(f, 0, 0);				// affichage arbre infixé
		putchar('\n');
		pos = 0;
		while (!feuille(f, pos, &enr)) {
			prec = pos;
			printf("%s", enr.dat);
			res = reponse();
			pos = (res == 'o') ? enr.g : enr.d;
		}											  // arrivée sur une feuille
		printf("%s\nEtes vous d'accord ?", enr.dat);
		res = reponse();
		if (res == 'n')		// si pas d'accord inserer question-réponse
			ajoutQuestionReponse(f, prec);

		printf("\nplay again ? (o/n)");  // cntl nouvelle partie
		play = reponse();
	} while (play == 'o');
	printf("fermeture du fichier animaux.bin\n");
	fclose(f);
	return 0;
}
/*******************************************************************************
*******************************************************************************/
int reponse()
{
	int res = 0;
	scanf_s("%c", &res, 1);
	rewind(stdin);
	return res;
}
/*******************************************************************************
lecture des informations fichier, noeud par noeud
*******************************************************************************/
void lireNoeud(FILE* f, int nieme, t_noeuds* enr)
{
	fseek(f, sizeof(t_noeuds) * nieme, SEEK_SET);
	fread(enr, sizeof(t_noeuds), 1, f);
}
/*******************************************************************************
écriture des informations dans le fichier, noeud par noeud
*******************************************************************************/
void ecrireNoeud(FILE* f, int nieme, t_noeuds* enr)
{
	fseek(f, sizeof(t_noeuds) * nieme, SEEK_SET);
	fwrite(enr, sizeof(t_noeuds), 1, f);
}
/*******************************************************************************
affichage infixé de l'arbre de jeu
*******************************************************************************/
void fichierArbreInfixe(FILE* f, int r, int niveau)
{
	t_noeuds enr;
	int i;
	if (r != -1) {
		lireNoeud(f, r, &enr);
		fichierArbreInfixe(f, enr.d, niveau + 1);
		for (i = 0; i < niveau; i++)
			printf("%5s", " ");
		printf("%s\n", enr.dat);
		fichierArbreInfixe(f, enr.g, niveau + 1);
	}
}
/*******************************************************************************
feuille ou non ?
*******************************************************************************/
int feuille(FILE* f, int pos, t_noeuds* enr)
{
	lireNoeud(f, pos, enr);
	return (enr->g == -1 && enr->d == -1);
}
/*******************************************************************************
avoir la taille de l'arbre (nombre de noeuds)
*******************************************************************************/
int tailleArbreFichier(FILE* f, int r)
{
	t_noeuds enr;
	int res = 0;
	if (r != -1) {
		lireNoeud(f, r, &enr);
		res = 1 + tailleArbreFichier(f, enr.g) + tailleArbreFichier(f, enr.d);
	}
	return res;
}
/*******************************************************************************
ajouter une question et une réponse
*******************************************************************************/
void ajoutQuestionReponse(FILE* f, int prec)
{
	t_noeuds eprec;
	t_noeuds rep, q;
	int posq, posrep;
	int taille;

	printf("a quel animal pensez-vous ?"); // recup réponse
	fgets(rep.dat, 256, stdin);
	rep.dat[strlen(rep.dat) - 1] = '\0';
	// recup question
	printf("entrez une question permettant de caracteriser cet animal\n"
		"et pour laquelle la reponse est oui :");
	fgets(q.dat, 256, stdin);
	q.dat[strlen(q.dat) - 1] = '\0';
	// créer liens
	taille = tailleArbreFichier(f, 0);// avoir position fin des deux nouveaux noeuds
	posrep = taille;
	posq = taille + 1;

	rep.d = rep.g = -1;		// la réponse est toujours une feuille
	lireNoeud(f, prec, &eprec); // récup noeud pére 
	q.g = posrep;          // suite nouvelle question : nouvelle reponse à gauche,
	q.d = eprec.d;			// ancienne reponse à droite
	eprec.d = posq;			// accrochage nouvelle question au noeud pére à droite
						//écrire les modifications noeuds eprec,rep,q dans le fichier						
	ecrireNoeud(f, prec, &eprec);
	ecrireNoeud(f, posrep, &rep);
	ecrireNoeud(f, posq, &q);
	printf("maintenant je connais cet animal\n");
}
/*******************************************************************************
*******************************************************************************/

