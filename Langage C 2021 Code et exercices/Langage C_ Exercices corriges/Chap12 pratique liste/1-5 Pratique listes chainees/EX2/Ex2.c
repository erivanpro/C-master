/*AVERTISSEMENT

Les exercices de ce chapitre proposent avec les listes chainées de s'entrainer
également aux manipulations de pointeurs, d'en expérimenter certaines difficultés
et d'élaborer grace à eux des algorithmes.
Du point de vue des listes chainées les situations créées peuvent apparaitre parfois
un peu artificielles et ne pas nécessairement constituer de bonnes réponses pratiques
à des situations réelles. Il s'agit donc au passage de réfléchir à quelle implémentation
d'une liste chainée choisir selon les besoins spécifiques de tel ou tel programme.
Par exemple il apparaitra clairement je pense que l'insertion ou la supression d'éléments
dans une liste ordonnée sera baucoup plus simple avec une liste symétrique non circulaire.

*/

/*
Dans un programme, mettre en place une liste chaînée circulaire simple à partir de 
la structure de données du cours, tester les fonctions d'initialisation, d'ajout, 
de suppression, de destruction de la liste.
Ajouter ensuite :
– une fonction copie de liste
– une fonction d'insertion en ordre croissant
– une fonction de suppression selon un critère donné (par exemple tous les éléments 
dont le champ val est égal à une valeur ou inférieur à une valeur)

*/
// Même exercice que le 1 mais implémenté avec une liste circulaire.

#include"GraphCons.h"

#define SAVESTR	"save liste entite.entite"

typedef struct Entite {
	float x, y, dx, dy;
	int bcolor,fcolor;
	int lettre;
	struct Entite*suiv;
}Entite;

void Menu(void);
Entite* CreateEntite(void);
void AjouteEntite(Entite**cour, Entite*e);
void AjoutCroissantEntite(Entite**cour, Entite*e);
void SuppEntite(Entite**cour );
void SuppEntiteColor(Entite**cour, int color);
void DestroyListeEntite(Entite**cour);
Entite* CopieListeEntite(Entite*cour);
void TrierListeEntite(Entite**cour);
Entite* RetirerEntite(Entite**cour);
_Bool SaveListeEntite(Entite*cour);
Entite* LoadListeEntite(char*path);

void MoveEntite(Entite*e);
void AfficheLigneEntite(Entite*prem);
void EffaceLigneEntite(Entite*cour);
void AfficheEntite(Entite*e);
void EffaceEntite(Entite*e);
void RunEntite(Entite*e);
void RunAllEntite(Entite*prem);

int main()
{
	Entite*Courant = NULL; // tête de liste
	srand((unsigned int)time(NULL));

	//G_PleinEcran();
	G_ConsResize(120, 30);
	G_ConsCursor(FALSE);
	
	// permet de basuler entre ordre croissant ou pas
	_Bool AJOUTCROISSANT = FALSE;

	while (1) {

		G_PollEvent();

		if (G_KeyDown(VK_ESCAPE))
			break;

		else if (G_KeyDown(VK_A)) {
			if (AJOUTCROISSANT)
				AjoutCroissantEntite(&Courant, CreateEntite());
			else
				AjouteEntite(&Courant, CreateEntite());
		}
		else if (G_KeyDown(VK_Z))
			SuppEntite(&Courant);
		else if (G_KeyDown(VK_E)) {
			SuppEntiteColor(&Courant, BRIGHT_RED);
			SuppEntiteColor(&Courant, DARK_RED);
		}
		else if (G_KeyDown(VK_R)) {
			SuppEntiteColor(&Courant, BRIGHT_BLUE);
			SuppEntiteColor(&Courant, DARK_BLUE);
			SuppEntiteColor(&Courant, BRIGHT_CYAN);
			SuppEntiteColor(&Courant, DARK_CYAN);
		}
		else if (G_KeyDown(VK_T)) {
			SuppEntiteColor(&Courant, BRIGHT_YELLOW);
			SuppEntiteColor(&Courant, DARK_YELLOW);
		}
		else if (G_KeyDown(VK_C)) {
			Entite*copie = CopieListeEntite(Courant);
			DestroyListeEntite(&Courant);
			Courant = copie;
		}
		else if (G_KeyDown(VK_S)) {
			SaveListeEntite(Courant);
			DestroyListeEntite(&Courant);
			printf("sauvegarde");
		}
		else if (G_KeyDown(VK_L)) {
			Entite*e = LoadListeEntite(SAVESTR);
			if (e != NULL) {
				DestroyListeEntite(&Courant);
				Courant = e;
			}
		}
		else if (G_KeyDown(VK_DELETE))
			DestroyListeEntite(&Courant);

		else if (G_KeyDown(VK_SPACE)) {
			G_ConsClear();
			// l'ordre croissant ne peut pas fonctionner correctement
			// sur la base d'une liste non classée dés le départ.
			if (AJOUTCROISSANT == FALSE)
				TrierListeEntite(&Courant);
			AJOUTCROISSANT = !AJOUTCROISSANT;
		}

		// affichage
		if (G_Top(100)) {
			if (AJOUTCROISSANT){
				G_ConsClear();
				AfficheLigneEntite(Courant);
			}
			else
				RunAllEntite(Courant); // animation
			Menu();
		}	
	}
	DestroyListeEntite(&Courant);
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
		   "Espace : Bascule ordre croissant ou pas"
		   "Supp   : detruire liste\n"
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

		// éviter d'avoir du noir comme couleur de fond
		e->bcolor = 1 + rand() % (COLORMAX - 1);
		// les lettre sont en noir pour mieux voir les suppressions
		e->fcolor = BLACK;// rand() % COLORMAX;
		e->lettre = 'A' + rand() % 26;
		// différence avec liste non circulaire
		e->suiv = e;  // pointe sur lui-même
		// la fin constitue aussi le début
	}
	return e;
}
// passage par référence du premier pointeur de la liste
// l'ajout se fait à partir du pointeur courant dans la liste
void AjouteEntite(Entite**cour, Entite*e)
{
	if (e == NULL)
		return;

	if (*cour == NULL) 
		*cour = e;
	else {
		e->suiv = (*cour)->suiv;
		(*cour)->suiv = e;
		*cour = e; // se place sur le nouveau entrant (pas obligé)
	}
}
// une liste ciculaire à sens unique n'est pas vraiment faite pour 
// être ordonnée. Pour avoir un ordre croissant dans une telle liste 
// le plus simple semble de partir du plus petit de la liste pour 
// chercher la place du nouvel entrant. 
void AjoutCroissantEntite(Entite**cour, Entite*e)
{	 
	// si vide
	if (*cour == NULL)
		*cour = e;

	// si un seul en principe peu importe l'ordre puisque 
	// la liste est circulaire
	else if (*cour == (*cour)->suiv) {
		e->suiv = *cour;
		(*cour)->suiv = e;
	}
	// si plusieurs
	else {
		// se positionner sur le plus grand en dernier dans la liste
		while ((*cour)->suiv->lettre >= (*cour)->lettre)
			*cour = (*cour)->suiv;
		
		//ensuite chercher la bonne place pour le nouvel élément
		Entite*prec = *cour, *suiv = (*cour)->suiv;
		while (e->lettre >= suiv->lettre) {
			prec = suiv;
			suiv = suiv->suiv;
			if (prec == *cour)
				break;
		}
		// insérer
		e->suiv = prec->suiv;
		prec->suiv = e;
	}
}
void SuppEntite(Entite**cour)
{
	if (*cour == NULL)
		return;
	else if ((*cour)->suiv == *cour) { // si un seul
		EffaceEntite(*cour);
		free(*cour);
		*cour = NULL;
	}
	else { // si plusieurs
		Entite*e, *p;
		e = p = *cour;
		// chercher le dernier, qui précède *cour
		while (p->suiv != e)
			p = p->suiv;
		p->suiv = e->suiv; // supprimer le courant
		*cour = e->suiv;// courant devient le suivant
		EffaceEntite(e);
		free(e);
	}
}

void SuppEntiteColor(Entite**cour, int color)
{
	Entite*e = *cour; 

	// si non vide
	if (*cour != NULL) {

		// si un seul 
		if (*cour == (*cour)->suiv) {
			// supprimer ?
			if ((*cour)->bcolor == color || (*cour)->fcolor == color) {
				EffaceEntite(*cour);
				free(*cour);
				*cour = NULL;
			}
		}
		// si plusieurs
		else {

			// trouver un différent qui servira de stop
			Entite* stop = (*cour)->suiv;
			while (stop != *cour) {
				if (stop->bcolor != color && stop->fcolor != color)
					break;
				stop = stop->suiv;
			}

			// si stop égale *cour ils sont tous à supprimer.
			if (stop == *cour)
				DestroyListeEntite(cour);

			// sinon suprimer jusqu'à retrouver stop
			else {
				*cour = stop;
				while ((*cour)->suiv != stop) {

					if ((*cour)->suiv->bcolor == color || (*cour)->suiv->fcolor == color) {
						// ici il n'est pas interessant d'appeler SupEntite(cour)
						Entite* e = (*cour)->suiv;
						(*cour)->suiv = (*cour)->suiv->suiv;
						EffaceEntite(e);
						free(e);
					}
					else
						*cour = (*cour)->suiv;
				}
			}
		}
	}
}
void DestroyListeEntite(Entite**cour)
{
	G_ConsClear();
	while (*cour != NULL) 
		SuppEntite(cour);
	*cour = NULL;
}
//TODO
Entite* CopieListeEntite(Entite*liste)
{
	Entite*e = NULL;
	if (liste != NULL) {
		// tete
		e = (Entite*)malloc(sizeof(Entite));
		if (e) {
			*e = *liste;
			e->suiv = e;

			// les autres s'il y en a
			Entite* p = e;
			Entite* l = liste;
			while (l->suiv != liste) {
				p->suiv = (Entite*)malloc(sizeof(Entite));
				p = p->suiv;
				l = l->suiv;
				*p = *l;
			}
			p->suiv = e;
		}
	}
	return e;
}
//
void TrierListeEntite(Entite**cour)
{
	Entite*e, *triee = NULL;
	while (*cour != NULL) {
		e = RetirerEntite(cour);
		AjoutCroissantEntite(&triee, e);
	}
	*cour = triee;
}
//
Entite* RetirerEntite(Entite**cour)
{
	Entite*e = *cour;
	if (*cour != NULL && (*cour)->suiv == *cour)
		*cour = NULL;
	else {
		Entite*p = *cour;
		while (p->suiv != *cour)
			p = p->suiv;
		p->suiv = (*cour)->suiv;
		*cour = (*cour)->suiv;
		e->suiv = e;
	}
	return e;
}
//
_Bool SaveListeEntite(Entite*cour)
{
	FILE*f = NULL;
	errno_t err;
	err = fopen_s(&f, SAVESTR, "wb");
	if (err) {
		G_Gotoxy(0, 0);
		printf("save impossible\n");
		return FALSE;
	}
	else if (cour != NULL) {
		Entite*e = cour;
		do{
			fwrite(e, sizeof(Entite), 1, f);
			e = e->suiv;
		} while (e != cour);
		fclose(f);
		return TRUE;
	}
}
Entite* LoadListeEntite(char*path)
{
	Entite*cour = NULL;
	FILE*f;
	errno_t err;
	err = fopen_s(&f, path, "rb");
	if (err) {
		G_Gotoxy(0, 0);
		printf("load impossible\n");
		return cour;
	}
	else {
		size_t res;
		do {
			Entite*e = (Entite*)malloc(sizeof(Entite));
			res = fread(e, sizeof(Entite), 1, f);
			e->suiv = e;
			res == 1 ? AjouteEntite(&cour, e) : free(e);		
		} while (res);
		fclose(f);
	}
	return cour;
}
//
void MoveEntite(Entite*e)
{
	e->x += e->dx;
	e->y += e->dy;

	// écran circulaire
	if (e->x >= G_ConsTX())
		e->x = 0;
	if (e->x < 0)
		e->x = (float)G_ConsTX() - 1;

	if (e->y >= G_ConsTY())
		e->y = 0;
	if (e->y < 0)
		e->y = (float)G_ConsTY() - 1;
}
void AfficheLigneEntite(Entite*cour)
{
	// si liste vide sortir
	if (cour == NULL)
		return;

	int y = 0;
	int x = 0;

	//si un seul
	if(cour == cour->suiv)
		G_DrawChar(x, y, cour->lettre, cour->bcolor, cour->fcolor);
	
	// si plusieurs
	else {
		// chercher l'adresse du plus petit comme départ
		Entite*petit = cour;
		Entite*e = cour->suiv;
		while (e != cour) {
			if (e->lettre < petit->lettre)
				petit = e;
			e = e->suiv;
		}
		// afficher la liste en commencant au plus petit
		e = petit;
		do {
			G_DrawChar(x, y, e->lettre, e->bcolor, e->fcolor);
			++x;
			if (x >= G_ConsTX()) {
				x = 0;
				y++;
			}
			e = e->suiv;
		} while (e != petit);
	}
}
void EffaceLigneEntite(Entite*cour)
{
	if (cour != NULL) {
		Entite *e = cour;
		int x = 0, y = 0;
		do {
			G_DrawChar(x, y, ' ', BLACK, BLACK);
			++x;
			if (x >= G_ConsTX()) {
				x = 0;
				y++;
			}
			e = e->suiv;
		} while (e != cour);
	}
}
void AfficheEntite(Entite*e)
{
	G_DrawChar((int)e->x, (int)e->y, e->lettre, e->bcolor, e->fcolor);
}
void EffaceEntite(Entite*e)
{
	G_DrawChar((int)e->x, (int)e->y, e->lettre, BLACK, BLACK);
}
void RunEntite(Entite*e)
{
	EffaceEntite(e);
	MoveEntite(e);
	AfficheEntite(e);
}
void RunAllEntite(Entite*cour)
{
	if (cour != NULL) {
		Entite*e = cour;
		do {
			RunEntite(e);
			e = e->suiv;
		} while (e != cour);
	}
}

