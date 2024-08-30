#ifndef _GENERAL
#define _GENERAL

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_primitives.h>

// taille ecran
const int SCRX = 800;
const int SCRY = 600;

// vaisseau
typedef struct{

	int x, y;			// position
	int dv;			// déplacement et vitesse
	int tx, ty;			// taille
	int vie;			// vivant ou pas, actif ou pas
	int score;			// les points obtenus
	ALLEGRO_BITMAP*image; 	// une image pour le vaisseau

}t_vaisseau;

// pour le contrôle du clavier
enum KEYS{ UP, RIGHT, DOWN, LEFT, SPACE, KEY_MAX };
bool key[KEY_MAX] = { false };
/*****************************************************************
VAISSEAU /
*****************************************************************/
void		init_vaisseau(t_vaisseau*p);
void		affiche_vaisseau(t_vaisseau*p);
void		monte(t_vaisseau*p);
void		droite(t_vaisseau*p);
void		descend(t_vaisseau*p);
void		gauche(t_vaisseau*p);
void		erreur(const char*txt);
/*****************************************************************
*****************************************************************/
#endif