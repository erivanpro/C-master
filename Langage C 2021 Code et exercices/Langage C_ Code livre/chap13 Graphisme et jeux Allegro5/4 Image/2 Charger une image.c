#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>

void erreur(const char* txt)
{
	ALLEGRO_DISPLAY* d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/
int main()
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* image;		// l'image

	if (!al_init())
		erreur("al_init()");

	display = al_create_display(1024, 768);
	if (!display)
		erreur("al_create_display()");

	//nécessaire pour laod et save bitmap
	if (!al_init_image_addon())
		erreur("al_init_image_addon()");

	// charger une image dans le programme
	image = al_load_bitmap("./images/image.bmp");
	if (!image)
		erreur("al_load_bitmap()");

	// l'afficher
	al_draw_bitmap(image, 0, 0, 0);
	al_flip_display();

	al_rest(3.0);
	al_destroy_display(display);
	al_destroy_bitmap(image);
	return 0;
}
