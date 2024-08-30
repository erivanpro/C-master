#include <stdlib.h>
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

/*************************************************************
*************************************************************/
int main()
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_KEYBOARD_STATE key;	// clavier simple
	int fin = 0;

	srand(time(NULL));

	if (!al_init())
		erreur("al_init()");

	display = al_create_display(1024, 768);
	if (!display)
		erreur("create_display(screenx,screeny)");

	// pour utiliser le clavier
	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

	while (!fin) {

		// récupération de l'état du clavier
		al_get_keyboard_state(&key);

		// si touche escape appuyée fin boucle et quitter
		if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
			fin = 1;

		// si Enter changer de couleur
		if (al_key_down(&key, ALLEGRO_KEY_ENTER)) {
			al_clear_to_color(al_map_rgb(rand() % 256,
				rand() % 256, rand() % 256));
		}

		al_flip_display();
	}

	al_destroy_display(display);
	return 0;
}