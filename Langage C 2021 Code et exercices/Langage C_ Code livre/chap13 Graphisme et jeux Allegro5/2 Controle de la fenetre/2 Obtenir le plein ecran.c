#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

void erreur(const char* txt)
{
	ALLEGRO_DISPLAY* d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}

void message(const char* format, ...)
{
	ALLEGRO_DISPLAY* display;
	char txt[1024];
	va_list args;

	va_start(args, format);
	vsnprintf_s(txt, sizeof(txt), strlen(txt), format, args);
	va_end(args);

	display=al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(display, "Message", txt, txt, NULL, 0);
}
/*************************************************************
*************************************************************/
int main()
{
	ALLEGRO_DISPLAY* display;
	int w, h;

	srand(time(NULL));
	if (!al_init())
		erreur("al_init()");

	// spécifie une fenêtre à la taille de l'écran 
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	// la taille passée pour le display n'est pas prise en compte
	// mais il prend automatiquement la résolution courante de l'écran
	display = al_create_display(0, 0); 
	if (!display)
		erreur("create_display");
			
	// changer sa couleur
	al_clear_to_color(al_map_rgb(rand() % 256, rand() % 256,
		rand() % 256));
	al_flip_display();

	// pour récupérer la largeur et la hauteur
	w = al_get_display_width(display);
	h = al_get_display_height(display);

	// attente
	al_rest(3.0);

	// fermeture
	al_destroy_display(display);

	// afficher la résolution obtenue après fermeture
	message("resolution : %d par %d\n", w, h);
	return 0;
}