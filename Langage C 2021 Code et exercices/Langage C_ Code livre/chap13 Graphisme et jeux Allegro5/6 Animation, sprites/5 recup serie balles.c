#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdlib.h>
#include <time.h>

#define NBIMAGE		32

const int SCRX = 800;
const int SCRY = 600;
const int IMTX = 64;
const int IMTY = 64;

typedef struct{
	// déplacement
	float x, y;      // position
	float dx, dy;    // déplacement

	// image
	int tx, ty;      // taille

	// animation
	int imcourante; // image courante
	int nbimage;    // nombre d'images
	int tour;       // compte tours
	int nbtour;     // nombre de tours
	int dir;        // direction de l'animation
}t_sprite;

ALLEGRO_BITMAP*     recup_sprite(ALLEGRO_BITMAP*scr,
								int tx, int ty,
								int startx, int starty,
								int colonne, int i);
t_sprite*           init_sprite(void);
void                cntl_anim(t_sprite*s);
void                avance(t_sprite*s);

void                erreur(const char*txt);
/**************************************************************
***************************************************************/
int main()
{
	ALLEGRO_DISPLAY*display;
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_BITMAP*all;
	ALLEGRO_BITMAP*anim[NBIMAGE];
	
	t_sprite*balle;

	srand(time(NULL));
	if (!al_init())
		erreur("al_init()");

	if (!al_init_image_addon())
		erreur("al_init_image_addon()");

	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

	display = al_create_display(SCRX, SCRY);
	if (!display)
		erreur("al_create_display()");

	//Récupération de l'image générale
	all = al_load_bitmap("all_sprites.bmp");
	if (!all)
		erreur("al_load_bitmap()");

	// découpe de l'animation (taille images : 64x64)
	for (int i = 0; i < NBIMAGE; i++){
		anim[i] = recup_sprite(all, IMTX, IMTY, 0, 0, 8, i);
		if (!anim[i])
			erreur("recup_sprite()");
		al_convert_mask_to_alpha(anim[i],
			al_get_pixel(anim[i], 0, 0));
	}
	// revenir à l'affichage écran
	al_set_target_backbuffer(display);

	// allocation et initialisation d'un t_sprite
	balle = init_sprite();

	do{
		al_get_keyboard_state(&key);

		// contrôle animation
		cntl_anim(balle);

		// avancer
		avance(balle);

		// affichage
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_bitmap(anim[balle->imcourante],
			balle->x, balle->y, 0);
		al_flip_display();

		al_rest(1.0 / 60);

	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	for (int i = 0; i<NBIMAGE; i++)
		al_destroy_bitmap(anim[i]);

	al_destroy_display(display);
	return 0;
}
/**************************************************************
Initialisation d'un sprite
***************************************************************/
t_sprite* init_sprite()
{
	t_sprite*s = (t_sprite*)malloc(sizeof(t_sprite));

	s->x = rand() % (SCRX - IMTX);
	s->y = rand() % (SCRY - IMTY);
	s->dx = ((float)rand() / RAND_MAX) * 6 - 3;
	s->dy = ((float)rand() / RAND_MAX) * 6 - 3;
	s->tx = IMTX;  // ou al_get_bitmap_width(anim[0]);
	s->ty = IMTY;
	s->imcourante = 0;
	s->nbimage = NBIMAGE;
	s->tour = 0;
	s->nbtour = 1 + rand() % 3;
	s->dir = rand() % 2 * 2 - 1; // -1 ou 1

	return s;
}
/**************************************************************
Récupérer sur un fichier la séquence d'animation
***************************************************************/
ALLEGRO_BITMAP*recup_sprite(
	ALLEGRO_BITMAP*scr,     // bitmap d'origine
	int tx, int ty,          // taille élément
	int startx, int starty,  // à partir de
	int colonne,            // nombre de colonnes
	int i)                  // ieme élément
{
	ALLEGRO_BITMAP*sprite = NULL;
	int x, y;
	sprite = al_create_bitmap(tx, ty);
	if (sprite != NULL){
		// attention colonne doit être > 0
		x = startx + (i%colonne)*tx;
		y = starty + (i / colonne)*ty;

		al_set_target_bitmap(sprite);
		al_draw_bitmap_region(scr, x, y, tx, ty, 0, 0, 0);
	}
	return sprite;
}
/**************************************************************
Contrôler l'animation des images 
(qui peut fonctionner à l'envers)
***************************************************************/
void cntl_anim(t_sprite*s)
{
	// attention nbtour doit être > 0
	s->tour = (s->tour + 1) % s->nbtour;
	if (s->tour == 0){
		s->imcourante += s->dir;
		// rester entre 0 et (nbimage-1) compris
		s->imcourante = (s->imcourante + s->nbimage) % s->nbimage;
	}
}
/**************************************************************
Contrôle du déplacement dans l'écran. Si un bord est touché
la balle part dans l'autre sens avec un pas et une animation
différents.
***************************************************************/
void avance(t_sprite*s)
{
	bool res = false;

	// avancer
	s->x += s->dx;
	s->y += s->dy;

	if (s->x<0){// cntl bords horizontaux
		s->x = 0;
		s->dx = ((float)rand() / RAND_MAX) * 3;
		res = true;
	}
	else if (s->x + s->tx>SCRX){
		s->x = SCRX - s->tx;
		s->dx = ((float)rand() / RAND_MAX)*-3;
		res = true;
	}
	if (s->y<0){// cntl bords verticaux
		s->y = 0;
		s->dy = ((float)rand() / RAND_MAX) * 3;
		res = true;
	}
	else if (s->y + s->ty>SCRY){
		s->y = SCRY - s->ty;
		s->dy = ((float)rand() / RAND_MAX)*-3;
		res = true;
	}
	if (res == true){// si un bord touché
		s->nbtour = 1 + rand() % 3;
		s->dir = (rand() % 2) * 2 - 1;
	}
}
/**************************************************************
Gestion des erreurs
***************************************************************/
void erreur(const char*txt)
{
	ALLEGRO_DISPLAY*d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/