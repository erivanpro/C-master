#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

// écran
const int SCRX = 640;
const int SCRY = 480;

// animation
typedef struct{
	char*nom;       // fichier conteneur
	int startx, starty; // départ dans le fichier conteneur
	int nbcolonne;  // nombre de colonne
	int nbimage;    // nombre d'images
	int tx, ty;      // taille d'une image
	bool masque;     // 0 si pas de masque, 1 si oui
	ALLEGRO_BITMAP**image; // les images de l'anim
}t_animation;

enum{ DECOR, DRAGON, POISSON, CRABE, ABEILLE, MOUSTIQUE, SERPENT, NBSPRITE };
t_animation ANIMDECOR = { "anim/decor.png", 0, 0, 1, 1, 640, 480, 0 };
t_animation ANIMDRAGON = { "anim/dragon.png", 0, 0, 3, 6, 128, 64, 1 };
t_animation ANIMPOISSON = { "anim/poisson.png", 0, 0, 3, 3, 64, 32, 1 };
t_animation ANIMCRABE = { "anim/crabe.png", 0, 0, 4, 4, 64, 32, 1 };
t_animation ANIMABEILLE = { "anim/abeille.png", 0, 0, 6, 6, 50, 40, 1 };
t_animation ANIMMOUSTIQUE = { "anim/moustique.png", 0, 0, 6, 6, 50, 40, 1 };
t_animation ANIMSERPENT = { "anim/serpent.png", 0, 0, 4, 7, 100, 50, 1 };

typedef struct{
	// déplacement
	float x, y;      // position
	float dx, dy;    // déplacement

	// gestion animation
	int imcourante; // image courante
	int tour;       // compte tours
	int nbtour;     // nombre de tours
	int dir;        // direction de l'animation
	t_animation*anim; // les images de l'animations

}t_sprite;

void            recup_animation(t_animation*a);
ALLEGRO_BITMAP* recup_image(ALLEGRO_BITMAP*scr, int tx, int ty,
							int startx, int starty, int colonne,
							int i);
t_sprite*       init_sprite(int posx, int posy, int dx, int dy, 
							int nbtour, int dir, t_animation*a);
void            avance_sprite(t_sprite*s);
void            anime_sprite(t_sprite*s);
void            affiche_sprite(t_sprite*s);
void            destroy_sprite(t_sprite*s[]);
void            erreur(const char* txt);
/**************************************************************
***************************************************************/
int main()
{
	ALLEGRO_DISPLAY*display;
	ALLEGRO_KEYBOARD_STATE key;
	t_sprite*all[NBSPRITE];

	if (!al_init())
		erreur("al_init()");
	if (!al_install_keyboard())
		erreur("al_install_keyboard()");
	if (!al_init_image_addon())
		erreur("al_init_image_addon()");

	display = al_create_display(SCRX, SCRY);
	if (!display)
		erreur("al_create_display()");

	// récupération des animations
	recup_animation(&ANIMDECOR);
	recup_animation(&ANIMDRAGON);
	recup_animation(&ANIMPOISSON);
	recup_animation(&ANIMCRABE);
	recup_animation(&ANIMABEILLE);
	recup_animation(&ANIMMOUSTIQUE);
	recup_animation(&ANIMSERPENT);

	// initialisation des sprites
	all[DECOR] = init_sprite(0, 0, 0, 0, 0, 0, &ANIMDECOR);
	all[DRAGON] = init_sprite(500, 0, -5, 0, 5, 1, &ANIMDRAGON);
	all[POISSON] = init_sprite(300, 400, 3, 0, 8, 1, &ANIMPOISSON);
	all[CRABE] = init_sprite(300, 212, 2, 0, 20, 1, &ANIMCRABE);
	all[ABEILLE] = init_sprite(100, 122, -3, 0, 8, 1, &ANIMABEILLE);
	all[MOUSTIQUE] = init_sprite(500, 70, 4, 0, 2, 1, &ANIMMOUSTIQUE);
	all[SERPENT] = init_sprite(350, 200, -2, 0, 4, 1, &ANIMSERPENT);

	// ne pas oublier!
	al_set_target_backbuffer(display);

	do{
		al_get_keyboard_state(&key);

		for (int i = DECOR; i<NBSPRITE; i++){
			avance_sprite(all[i]);
			anime_sprite(all[i]);
			affiche_sprite(all[i]);
		}

		al_flip_display();
		al_rest(1.0 / 30);

	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	//destroy_sprite(all);// BUG
	al_destroy_display(display);
	return 0;
}
/**************************************************************
***************************************************************/
void recup_animation(t_animation*a)
{
	ALLEGRO_BITMAP*conteneur;

	// récupération du fichier conteneur
	conteneur = al_load_bitmap(a->nom);
	if (!conteneur)
		erreur("recup_animation(), conteneur");

	// allocation du tableau dynamique d'images
	a->image = (ALLEGRO_BITMAP**)malloc(
		sizeof(ALLEGRO_BITMAP*)*a->nbimage);
	for (int i = 0; i < a->nbimage; i++){
		a->image[i] = recup_image(
			conteneur,// bitmap d'origine
			a->tx, a->ty,// taille élément
			0, 0,		// à partir du point h-g
			a->nbcolonne,// nombre colonnes
			i);// ieme élément de 0 à nbimage-1
		if (!a->image[i])
			erreur("recup_animation()");
		if (a->masque == true)
			al_convert_mask_to_alpha(a->image[i],
			                  al_get_pixel(a->image[i], 0, 0));
	}
}
/**************************************************************
***************************************************************/
ALLEGRO_BITMAP*recup_image(ALLEGRO_BITMAP*scr, int tx, int ty,
	int startx, int starty, int colonne, int i)
{
	ALLEGRO_BITMAP*image = NULL;
	int x, y;
	image = al_create_bitmap(tx, ty);
	if (image != NULL){
		// attention colonne doit être > 0
		x = startx + (i%colonne)*tx;
		y = starty + (i / colonne)*ty;

		al_set_target_bitmap(image);
		al_draw_bitmap_region(scr, x, y, tx, ty, 0, 0, 0);
	}
	return image;
}

/**************************************************************
***************************************************************/
t_sprite*init_sprite(int posx, int posy,
	int dx, int dy,
	int nbtour, int dir,
	t_animation*a)
{
	t_sprite*s = (t_sprite*)malloc(sizeof(t_sprite));
	s->x = posx;
	s->y = posy;
	s->dx = dx;
	s->dy = dy;
	s->imcourante = 0;
	s->tour = 0;
	s->nbtour = nbtour;
	s->dir = dir;
	s->anim = a;

	return s;
}
/**************************************************************
***************************************************************/
void avance_sprite(t_sprite*s)
{
	s->x += s->dx;
	s->y += s->dy;

	//sortie à gauche entrée à droite
	if (s->x + s->anim->tx < 0)
		s->x = SCRX;
	// sortie à droite entrée à gauche
	else if (s->x >SCRX)
		s->x = -s->anim->tx;

	//sortie en haut entrée en bas
	if (s->y + s->anim->ty < 0)
		s->y = SCRY;
	// sortie à droite entrée à gauche
	else if (s->y >SCRY)
		s->y = -s->anim->ty;
}
/**************************************************************
***************************************************************/
void anime_sprite(t_sprite*s)
{
	if (++s->tour > s->nbtour) {
		s->imcourante =
			(s->imcourante + s->dir + s->anim->nbimage) % s->anim->nbimage;
		s->tour = 0;
	}
}
/**************************************************************
***************************************************************/
void affiche_sprite(t_sprite*s)
{
	al_draw_bitmap(s->anim->image[s->imcourante], s->x, s->y, 0);
}
/**************************************************************
***************************************************************/
void destroy_sprite(t_sprite*s[])
{
	int i;
	for (i = 0; i<NBSPRITE; i++){
		// l'animation peut servir à plusieurs sprite mais
		// il faut la détruire une seule fois
		if (s[i]->anim != NULL){
			if (s[i]->anim->image != NULL){
				for (i = 0; i < s[i]->anim->nbimage; i++)
					al_destroy_bitmap(s[i]->anim->image[i]);
				free(s[i]->anim->image);
				s[i]->anim->image = NULL;
			}
		}
		free(s[i]);
	}
}
/**************************************************************
***************************************************************/
void erreur(const char*txt)
{
	ALLEGRO_DISPLAY*d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/