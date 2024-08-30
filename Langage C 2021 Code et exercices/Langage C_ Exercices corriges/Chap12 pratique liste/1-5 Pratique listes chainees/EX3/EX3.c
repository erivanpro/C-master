/*
Exercice 3
Dans un programme, mettre en place une liste symétrique, utiliser les fonctions du cours. 
Ajouter la sauvegarde et le chargement d'une liste, la suppression d'éléments sur critère.
*/

/*
Dans ce corrigé nous sortons légérement de ce qui et proposé dans le cours en ajoutant 
l'animation d'une liste d'entités qui se meuvent à l'écran mais les principes sont les 
mêmes.

Ce programme tire profit de la symétrie surtout pour la suppression d'entités.
*/
#include "GraphCons.h"

#define SAVESTR	"save liste entite.entite"

// il y a 15 degrés d'intelligence chacun représenté par 
// une couleur de DARK_BLUE 1 à WHITE 15 et une lettre de A à O
typedef struct Entite {
	float x, y, dx, dy;
	int intelligence, lettre; 
	struct Entite*suiv,*prec; // liste symétrique 
}Entite;

void Menu(void);
Entite* CreateEntite(void);
void AjouteTete(Entite**prem, Entite*e);
void AjoutCroissantEntite(Entite**prem, Entite*e);
void SuppTete(Entite**prem);
void SuppEntite(Entite**prem, Entite*e);
void SuppQIout(Entite**prem, int seuilbas, int seuilhaut);
void SuppQIin(Entite**prem, int seuilbas, int seuilhaut);
void DestroyListeEntite(Entite**prem);
Entite* CopieListeEntite(Entite*liste);
_Bool SaveListeEntite(Entite*liste);
Entite* LoadListeEntite(char*path);
void TrierListeEntite(Entite**cour);
Entite* RetirerTete(Entite**cour);

void MoveEntite(Entite*e);
void AfficheLigneEntite(Entite*prem);
void AfficheEntite(Entite*e);
void EffaceEntite(Entite*e);
void RunEntite(Entite*e);
void RunAllEntite(Entite*prem);


int main()
{
	Entite*Prem = NULL; // tête de liste

	G_ConsResize(120, 30);
	//G_PleinEcran();
	G_ConsCursor(FALSE);

	// AJOUTCROISSANT TRUE l'ajout est ordonné et l'affichage en ligne permet de 
	// le constater. AJOUTCROISSANT FALSE, l'ajout se fait sans ordre en tête de  
	// liste et les entités sont animées.
	_Bool AJOUTCROISSANT = FALSE;  // entite non classées et animées

	int outbas = 1, outhaut = 15;
	int inbas = 8, inhaut = 8;
	while (1) {

		G_PollEvent();
		if (G_KeyDown(VK_ESCAPE))
			break;

		else if (G_KeyDown(VK_A)) {
			if (AJOUTCROISSANT)
				AjoutCroissantEntite(&Prem, CreateEntite());
			else
				AjouteTete(&Prem, CreateEntite());
		}
		else if (G_KeyDown(VK_Z))
			SuppTete(&Prem);

		// juste pour tester des suppression de QI au dela des bords outbas et outhaut
		// à chaque fois les bords avancent vers le centre
		else if (G_KeyDown(VK_E)) {
			if (Prem != NULL) {
				outbas++;
				outhaut--;
				SuppQIout(&Prem, outbas, outhaut);
			}
			else {
				outbas = 1;
				outhaut = 15;
			}
		}
		// suppression dans un segment, au depart le QI 8 au centre, à chaque fois  
		// élargissement vers l'extérieur (inbas recule, inhaut avance) 
		else if (G_KeyDown(VK_R)) {
			if (Prem != NULL) {
				SuppQIin(&Prem, inbas, inhaut);
				inbas--;
				inhaut++;
			}
			else {
				inbas = 8;
				inhaut = 8;
			}
		}
		else if (G_KeyDown(VK_C)) {
			Entite*copie = CopieListeEntite(Prem);
			DestroyListeEntite(&Prem);
			Prem = copie;
			printf("copie");
		}
		else if (G_KeyDown(VK_S)) {
			SaveListeEntite(Prem);
			DestroyListeEntite(&Prem);
			printf("sauvegarde");
		}
		else if (G_KeyDown(VK_L)) {
			DestroyListeEntite(&Prem);
			Prem = LoadListeEntite(SAVESTR);
		}
		else if (G_KeyDown(VK_SPACE)) {
			G_ConsClear();
			// l'ordre croissant ne peut pas fonctionner correctement
			// sur la base d'une liste non classée dés le départ.
			if (AJOUTCROISSANT == FALSE)
				TrierListeEntite(&Prem);
			AJOUTCROISSANT = !AJOUTCROISSANT;
		}
		else if (G_KeyDown(VK_DELETE))
			DestroyListeEntite(&Prem);

		// animation
		if (G_Top(100)) {
			// remarque : 
			// l'animation est plus fluide si les enttés sont effacées une par une.  
			// C'est pourquoi je n'utilise pas G_ConsClear() pour le mode animation.
			if (AJOUTCROISSANT) {
				G_ConsClear();
				AfficheLigneEntite(Prem);
			}
			else
				RunAllEntite(Prem);

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
		"Z : supprimer en tete\n"
		"E : retirer bords supp]-[supp\n"
		"R : retirer section [supp]\n"
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

		e->intelligence = 1 + rand() % (COLORMAX - 1);
		e->lettre = 'A' + e->intelligence - 1;
		e->prec = e->suiv = NULL;
	}
	return e;
}
// passage par référence du premier pointeur de la liste,
// ajout en tête de liste
void AjouteTete(Entite**prem, Entite*e)
{
	if (*prem == NULL)
		*prem = e;
	else{
		e->suiv = *prem;
		(*prem)->prec = e;
		*prem = e;
	}
}

void AjoutCroissantEntite(Entite**prem, Entite*e)
{
	// chaine vide
	if (*prem == NULL)
		*prem = e;
	// avant premier : modifie prem
	else if (e->intelligence <= (*prem)->intelligence)
		AjouteTete(prem, e);
	// dans la chaine
	else {
		// trouver la bonne place
		Entite*p = *prem;
		while (p->suiv != NULL && e->intelligence > p->suiv->intelligence) 
			p = p->suiv;
		// relier derrière p
		if (p->suiv != NULL) 
				p->suiv->prec = e;
		e->suiv = p->suiv;
		p->suiv = e;
		e->prec = p;
	}
}
// Dans ce programme c'est surtout pour la suppression
// d'entités que l'on tire bénéfice de la symétrie.
void SuppTete(Entite**prem)
{
	SuppEntite(prem, *prem);
}
//
void SuppEntite(Entite**prem, Entite*e)
{
	if (*prem != NULL) {
		if (e->prec != NULL)
			e->prec->suiv = e->suiv;
		if (e->suiv != NULL)
			e->suiv->prec = e->prec;
		if (*prem == e)
			(*prem) = e->suiv;

		EffaceEntite(e);
		free(e);
	}
}
//supression hors seuils bas et haut (sup]-[sup)
void SuppQIout(Entite**prem, int seuilbas, int seuilhaut)
{
	Entite*e = *prem, *p;
	while (e != NULL) {
		p = e;
		e = e->suiv;
		if (p->intelligence < seuilbas || p->intelligence > seuilhaut)
			SuppEntite(prem, p);	
	}
}
// suppression entre seuils bas et haut inclus ([sup])
void SuppQIin(Entite**prem, int seuilbas, int seuilhaut)
{
	Entite*e = *prem,*p;
	while (e != NULL) {
		p = e;
		e = e->suiv;
		if (p->intelligence >= seuilbas && p->intelligence <= seuilhaut)
			SuppEntite(prem, p);	
	}
}
//
void DestroyListeEntite(Entite**prem)
{
	while (*prem != NULL)
		SuppTete(prem);
}
// 
Entite* CopieListeEntite(Entite*p)
{
	Entite*copie = NULL;
	if (p != NULL) {
		// se positionner sur le dernier maillon de la liste
		while (p->suiv != NULL)
			p = p->suiv;
		do {
			Entite* e = NULL;
			e = (Entite*)malloc(sizeof(Entite));
			if (e) {
				*e = *p;
				e->suiv = e->prec = NULL;
				AjouteTete(&copie, e);
				p = p->prec;
			}
			else
				break;
		} while (p != NULL);
	}
	return copie;
}
//
_Bool SaveListeEntite(Entite*p)
{
	FILE*f = NULL;
	errno_t err;
	_Bool res = FALSE;

	err = fopen_s(&f, SAVESTR, "wb");
	if (!err && f != NULL) {
		if (p != NULL) {
			// commencer par la fin pour conserver l'ordre facilement avec 
			// la fonction load
			while (p->suiv != NULL)
				p = p->suiv;

			while (p != NULL) {
				fwrite(p, sizeof(Entite), 1, f);
				p = p->prec;
			}
		}
		fclose(f);
		res = TRUE;
	}
	return res;
}
//
Entite* LoadListeEntite(char*path)
{
	Entite*prem = NULL;
	FILE* f = NULL;
	fopen_s(&f, path, "rb");
	if (f != NULL) {
		size_t res;
		Entite* e = NULL;
		do {
			e = (Entite*)malloc(sizeof(Entite));
			if (e) {
				res = fread(e, sizeof(Entite), 1, f);
				e->suiv = e->prec = NULL;
				res == 1 ? AjouteTete(&prem, e) : free(e);
			}
			else
				break;
		} while (res);
		fclose(f);
	}
	else
		printf("load impossible\n");
	
	return prem;
}
//
void TrierListeEntite(Entite**prem)
{
	Entite*e, *triee = NULL;
	while (*prem != NULL) {
		e = RetirerTete(prem);
		AjoutCroissantEntite(&triee, e);
	}
	*prem = triee;
}
//
Entite* RetirerTete(Entite**prem)
{
	Entite*e = NULL;
	if (*prem != NULL) {
		e = *prem;  // recup tete
		*prem = (*prem)->suiv; // tete passe au suivant
		if(*prem != NULL)  // si !fin
			(*prem)->prec = NULL; // rien avant
		e->suiv = e->prec = NULL; // initialiser les pointeurs e
	}
	return e;
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
//
void AfficheLigneEntite(Entite*prem)
{
	int x = 0, y = 0;
	while (prem != NULL) {
		G_DrawChar(x, y, prem->lettre, prem->intelligence, BLACK);
		++x;
		if (x >= G_ConsTX()) {
			x = 0;
			y++;
		}
		prem = prem->suiv;
	}
}
//
void AfficheEntite(Entite*e)
{
	G_DrawChar((int)e->x, (int)e->y, e->lettre, e->intelligence, BLACK);
}
//
void EffaceEntite(Entite*e)
{
	G_DrawChar((int)e->x, (int)e->y, ' ', BLACK, BLACK);
}
//
void RunEntite(Entite*e)
{
	EffaceEntite(e);
	MoveEntite(e);
	AfficheEntite(e);
}
//
void RunAllEntite(Entite*prem)
{
	while (prem != NULL) {
		RunEntite(prem);
		prem = prem->suiv;
	}
}









