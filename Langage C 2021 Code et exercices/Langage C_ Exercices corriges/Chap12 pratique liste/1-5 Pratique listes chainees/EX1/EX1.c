/*AVERTISSEMENT

Les exercices de ce chapitre proposent avec les listes chain�es de s'entrainer
�galement aux manipulations de pointeurs, d'en exp�rimenter certaines difficult�s
et d'�laborer grace � eux des algorithmes.
Du point de vue des listes chain�es les situations cr��es peuvent apparaitre parfois
un peu artificielles et ne pas n�cessairement constituer de bonnes r�ponses pratiques
� des situations r�elles. Il s'agit donc au passage de r�fl�chir � quelle impl�mentation
d'une liste chain�e choisir selon les besoins sp�cifiques de tel ou tel programme.
Par exemple il apparaitra clairement je pense que l'insertion ou la supression d'�l�ments
dans une liste ordonn�e sera baucoup plus simple avec une liste sym�trique non circulaire.

*/


/*
Exercice 1
Dans un programme, mettre en place une liste cha�n�e simple � partir
de la structure de donn�es du cours, tester les fonctions d'initialisation,
d'ajout, de suppression, de destruction de la liste et de sauvegarde de la liste.
Ajouter ensuite :
� une fonction copie de liste
� une fonction d'insertion en ordre croissant
� une fonction de suppression selon un crit�re donn�
  (par exemple tous les �l�ments dont le champ val est
  �gal � une valeur ou inf�rieur � une valeur)

*/

#include"GraphCons.h"

#define SAVESTR	"save liste entite.entite"

typedef struct Entite {
	float x, y, dx, dy;
	int intelligence;
	int bcolor, fcolor;
	int lettre;
	struct Entite* suiv;
}Entite;

void Menu(void);
Entite* CreateEntite(void);
void AjouteEntite(Entite** prem, Entite* e);
void AjoutCroissantEntite(Entite** prem, Entite* e);
void SuppEntite(Entite** prem);
void SuppEntiteColor(Entite** prem, int color);
void DestroyListeEntite(Entite** prem);
Entite* CopieListeEntite(Entite* liste);
_Bool SaveListeEntite(Entite* liste);
Entite* LoadListeEntite(char* path);

void MoveEntite(Entite* e);
void AfficheLigneEntite(Entite* prem);
void AfficheEntite(Entite* e);
void EffaceEntite(Entite* e);
void RunEntite(Entite* e);
void RunAllEntite(Entite* prem);


int main()
{
	Entite* Prem = NULL; // t�te de liste
	srand((unsigned int)time(NULL));

	//G_PleinEcran();
	G_ConsResize(120, 30);
	G_ConsCursor(FALSE);

	// avec AJOUTCROISSANT d�fini l'ajout est ordonn� et l'affichage permet de le 
	// constater. Sinon, sans AJOUTCROISSANT d�fini, l'ajout se fait en t�te de 
	//liste et les entit�s sont anim�es.

//#define AJOUTCROISSANT  // si non defini : entite non class�es et anim�es

	while (1) {

		G_PollEvent();
		if (G_KeyDown(VK_ESCAPE))
			break;

		else if (G_KeyDown(VK_A))
#ifndef AJOUTCROISSANT
			AjouteEntite(&Prem, CreateEntite()); // ajout sans ordre
#else
			AjoutCroissantEntite(&Prem, CreateEntite());
#endif
		else if (G_KeyDown(VK_Z))
			SuppEntite(&Prem);

		else if (G_KeyDown(VK_E)) {
			SuppEntiteColor(&Prem, BRIGHT_RED);
			SuppEntiteColor(&Prem, DARK_RED);
		}
		else if (G_KeyDown(VK_R)) {
			SuppEntiteColor(&Prem, BRIGHT_BLUE);
			SuppEntiteColor(&Prem, DARK_BLUE);
			SuppEntiteColor(&Prem, BRIGHT_CYAN);
			SuppEntiteColor(&Prem, DARK_CYAN);
		}
		else if (G_KeyDown(VK_T)) {
			SuppEntiteColor(&Prem, BRIGHT_YELLOW);
			SuppEntiteColor(&Prem, DARK_YELLOW);
		}
		else if (G_KeyDown(VK_C)) {
			Entite* copie = CopieListeEntite(Prem);
			DestroyListeEntite(&Prem);
			Prem = copie;
		}
		else if (G_KeyDown(VK_S)) {
			SaveListeEntite(Prem);
			DestroyListeEntite(&Prem);
			printf("sauvegarde");
		}
		else if (G_KeyDown(VK_L)) {
			Entite* e = LoadListeEntite(SAVESTR);
			if (e != NULL) {
				DestroyListeEntite(&Prem);
				Prem = e;
			}
		}
		else if (G_KeyDown(VK_DELETE))
			DestroyListeEntite(&Prem);

		// animation
		if (G_Top(100)) {
#ifdef AJOUTCROISSANT
			AfficheLigneEntite(Prem);
#else
			RunAllEntite(Prem);
#endif
			Menu();
		}
	}

	DestroyListeEntite(&Prem);
	return 0;

}
void Menu()
{
	G_Gotoxy(0, G_ConsTY() / 4);
	printf("A : ajouter \n"
		"Z : supprimer\n"
		"E : retirer rouges\n"
		"R : retirer bleu\n"
		"T : retirer jaune\n"
		"C : copier la liste\n"
		"S : sauvegarder la liste\n"
		"L : Loader la liste\n"
		"Supp : detruire liste\n"
		"Escape : quitter\n");
}
Entite* CreateEntite()
{
	Entite* e = NULL;
	e = (Entite*)malloc(sizeof(Entite));
	if (e) {
		e->x = (float)(rand() % G_ConsTX());
		e->y = (float)(rand() % G_ConsTY());
		e->dx = ((float)rand() / RAND_MAX) * 4 - 2;
		e->dy = ((float)rand() / RAND_MAX) * 4 - 2;

		e->bcolor = rand() % COLORMAX;

		/* // force le bleu ou le rouge pour tester plus facilement la suppression
		if (rand() % 2)
			e->bcolor = BRIGHT_BLUE;
		else
			e->bcolor = BRIGHT_RED;*/

			// permet de mieux voir la supression avec le fond seul
		e->fcolor = BLACK; //  rand() % COLORMAX;
		e->lettre = 'A' + rand() % 26;
		e->intelligence = rand() % 100;
		e->suiv = NULL;
	}
	return e;
}
// passage par r�f�rence du premier pointeur de la liste
// l'ajout se fait en t�te de liste
void AjouteEntite(Entite * *prem, Entite * e)
{
	if (e != NULL) {
		e->suiv = *prem;
		*prem = e;
	}
}
void AjoutCroissantEntite(Entite * *prem, Entite * e)
{
	// chaine vide
	if (*prem == NULL)
		* prem = e;
	// avant premier
	else if (e->lettre < (*prem)->lettre)
		AjouteEntite(prem, e);
	else {
		// trouver la bonne place
		Entite* prec = *prem, * sv = (*prem)->suiv;
		while (sv != NULL && e->lettre > sv->lettre) {
			prec = sv;
			sv = sv->suiv;
		}
		// ins�rer
		e->suiv = prec->suiv;
		prec->suiv = e;
	}
}
void SuppEntite(Entite * *prem)
{
	if (*prem != NULL) {
		Entite* e = *prem;
		*prem = (*prem)->suiv;
		EffaceEntite(e);
		free(e);
	}
}
// Si une entite comprend la couleur color pour la lettre ou le fond, 
// elle est supprim�e
void SuppEntiteColor(Entite * *prem, int color)
{
	Entite* e = *prem;

	while (e != NULL) {
		// suppression premi�re (�ventuellement aussi derni�re)
		if (e->bcolor == color || e->fcolor == color) {
			EffaceEntite(e);  // efface de l'�cran
			SuppEntite(prem);
			e = *prem;
		}
		// une trouv�e dans la chaine
		else if ( e->suiv != NULL &&  (e->suiv->bcolor == color || e->suiv->fcolor == color)) {
			Entite* ee = e->suiv;
			EffaceEntite(ee);
			e->suiv = e->suiv->suiv;
			free(ee);
		}
		// rien passer � la suivante
		else
			e = e->suiv;
	}
}
void DestroyListeEntite(Entite * *prem)
{
	while (*prem != NULL)
		SuppEntite(prem);
}
// la fonction est r�cursive afin de conserver l'ordre de la liste
// (on ajoute les maillons en t�te en commencant par le dernier)
Entite* CopieListeEntite(Entite * p)
{
	Entite* copie = NULL;

	if (p != NULL) {
		// copier p
		Entite* e = (Entite*)malloc(sizeof(Entite));
		if (e) {
			*e = *p;
			// parcourir toute la liste jusque avant dernier 
			if (p->suiv != NULL) {
				p = p->suiv;
				copie = CopieListeEntite(p);
				// au d�pilement ajouter chaque maillon
				e->suiv = copie;
				copie = e;
			}
			// stop appel prise du dernier
			else
				copie = e;
		}
	}
	return copie;
}
_Bool SaveListeEntite(Entite* prem)
{
	FILE* f = NULL;
	errno_t err;
	_Bool res = FALSE;

	err = fopen_s(&f, SAVESTR, "wb");
	if (!err && f != NULL) {

		while (prem != NULL) {
			fwrite(prem, sizeof(Entite), 1, f);
			prem = prem->suiv;
		}
		fclose(f);
		res = TRUE;
	}
	else
		printf("Save impossible\n");

	return res;
}
Entite* LoadListeEntite(char* path)
{
	Entite* prem = NULL;
	FILE* f = NULL;
	errno_t err;
	
	err = fopen_s(&f, path, "rb");
	if (! err && f != NULL) {
		size_t res;
		do {
			Entite* e = NULL;
			e=(Entite*)malloc(sizeof(Entite));
			if (e) {
				res = fread(e, sizeof(Entite), 1, f);
				if (res)
					AjouteEntite(&prem, e);
			}
			else {
				printf("bab alloc line %d\n", __LINE__);
				break;
			}
		} while (res);
		fclose(f);
	}
	return prem;
}
//
void MoveEntite(Entite * e)
{
	e->x += e->dx;
	e->y += e->dy;

	// �cran circulaire
	if (e->x >= G_ConsTX())
		e->x = 0;
	if (e->x < 0)
		e->x = G_ConsTX() - 1;

	if (e->y >= G_ConsTY())
		e->y = 0;
	if (e->y < 0)
		e->y = G_ConsTY() - 1;
}
void AfficheLigneEntite(Entite * prem)
{
	int y = 0;
	int x = 0;
	// En cas de suppression d'entit�s les derni�res de la liste reste � l'�cran
	// parce que la liste diminue de taille. Pour r�gler ce probl�me Le plus simple 
	// semble d'effacer la console, l'affichage du menu se fait apr�s.
	G_ConsClear();
	while (prem != NULL) {
		G_DrawChar(x, y, prem->lettre, prem->bcolor, prem->fcolor);
		prem = prem->suiv;
		++x;
		if (x >= G_ConsTX()) {
			x = 0;
			y++;
		}
	}
}
void AfficheEntite(Entite * e)
{
	G_DrawChar((int)e->x, (int)e->y, e->lettre, e->bcolor, e->fcolor);
}
void EffaceEntite(Entite * e)
{
	G_DrawChar((int)e->x, (int)e->y, e->lettre, BLACK, BLACK);
}
void RunEntite(Entite * e)
{
	EffaceEntite(e);
	MoveEntite(e);
	AfficheEntite(e);
}
void RunAllEntite(Entite * prem)
{
	while (prem != NULL) {
		RunEntite(prem);
		prem = prem->suiv;
	}
}

