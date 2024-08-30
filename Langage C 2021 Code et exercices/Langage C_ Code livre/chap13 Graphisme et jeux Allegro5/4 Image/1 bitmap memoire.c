#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <time.h>
#include <math.h>

#define SCREENX		1024
#define SCREENY		768
#define COLORALEA al_map_rgb(rand()%256,rand()%256,rand()%256)

void erreur(const char* txt)
{
	ALLEGRO_DISPLAY* d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/****************************************************************
****************************************************************/
ALLEGRO_BITMAP* CreateDessin(ALLEGRO_DISPLAY* display)
{
	ALLEGRO_BITMAP* bmp;
	// dimension pour la bitmap
	int tx = 10 + rand() % (SCREENX / 2);
	int ty = 10 + rand() % (SCREENY / 2);

	// création d'une bitmap mémoire
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	bmp = al_create_bitmap(tx, ty);
	if (!bmp)
		erreur("al_create_bitmap()");

	// dessiner dans la bitmap en mémoire
	al_set_target_bitmap(bmp);

	// dessin par bombardement de pixels et 
	// de rectangles de couleurs aléatoires
	al_clear_to_color(al_map_rgb(10, 0, 100));
	for (int i = 0; i < 10000; i++) {
		al_put_pixel(rand() % tx, rand() % ty, COLORALEA);
		if (rand() % 1000 > 997) {
			int x = rand() % tx;
			int y = rand() % ty;
			int trx = rand() % 20;
			int try = rand() % 20;
			al_draw_filled_rectangle(x, y, trx, try, COLORALEA);
		}
	}
	// revenir à l'affichage display
	al_set_target_backbuffer(display);

	return bmp;
}
int main()
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_BITMAP* bmp;

	srand(time(NULL));
	if (!al_init())
		erreur("al_init()");
	if (!al_install_keyboard())
		erreur("al_install_keyboard()");
	if (!al_init_primitives_addon())
		erreur("al_init_primitives_addon()");

	display = al_create_display(1024, 768);
	if (!display)
		erreur("al_create_display()");

	// position de départ
	int x = rand() % SCREENX;
	int y = rand() % SCREENY;

	// valeur de déplacement
	int dx = rand() % 20 - 10;
	int dy = rand() % 20 - 10;
	do {
		al_get_keyboard_state(&key);

		// création d'une nouvelle bitmap à chaque tour
		bmp = CreateDessin(display);

		// bouger et rebondir sur les bords
		x += dx;
		if (x < 0) {
			x = 0;
			dx = abs(dx);
		}

		int tx = al_get_bitmap_width(bmp);
		if (x + tx > SCREENX) {
			x = SCREENX - tx;
			dx = -abs(dx);
		}

		y += dy;
		if (y < 0) {
			y = 0;
			dy = abs(dy);
		}

		int ty = al_get_bitmap_height(bmp);
		if (y + ty > SCREENY) {
			y = SCREENY - ty;
			dy = -abs(dy);
		}

		// effacement Double Buffer
		al_clear_to_color(al_map_rgb(0, 0, 0));
		// affichage DB de l'imae aux coordonnées x,y
		al_draw_bitmap(bmp, x, y, 0);
		// DB copié à l'écran
		al_flip_display();

		// ralentir le processus
		al_rest(2.0 / 30.0);

		// detruire la bitmap courante avant création 
		// d'une nouvelle
		al_destroy_bitmap(bmp);

	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	al_destroy_display(display);

	return 0;
}
