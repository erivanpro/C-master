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

	// paramétrage fonctionnalités fenêtre avant sa création
	al_set_new_display_flags(ALLEGRO_WINDOWED |	ALLEGRO_RESIZABLE);
	display = al_create_display(800, 600);
	if (!display)
		erreur("create_display(800,600)");

	// pour utiliser le clavier
	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

	// boucle qui laisse le temps à l'utilisateur de manipuler
	// la fenêtre  
	while (!fin) {

		// récupération de l'état du clavier
		al_get_keyboard_state(&key);

		// si touche escape appuyée fin boucle et quitter
		if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
			fin = 1;

		al_flip_display();
	}
	al_destroy_display(display);
	return 0;
}