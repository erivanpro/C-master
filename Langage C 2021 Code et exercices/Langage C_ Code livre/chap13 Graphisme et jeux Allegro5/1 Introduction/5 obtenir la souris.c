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
	ALLEGRO_MOUSE_STATE mouse;	// souris simple
	int fin = 0, oldx = 0, oldy = 0;

	srand(time(NULL));

	if (!al_init())
		erreur("al_init()");

	display = al_create_display(800, 600);
	if (!display)
		erreur("create_display(800,600)");

	// pour utiliser la souris
	if (!al_install_mouse())
		erreur("al_install_mouse()");

	while (!fin) {

		// récupération de l'état de la souris
		al_get_mouse_state(&mouse);

		// si mouvement afficher position dans console
		if (oldx != mouse.x || oldy != mouse.y) {
			oldx = mouse.x;
			oldy = mouse.y;
			printf("%d-%d\n", mouse.x, mouse.y);
		}

		// si clic gauche chager couleur fenêtre
		if (al_mouse_button_down(&mouse, 1))
			al_clear_to_color(al_map_rgb(rand() % 256,
				rand() % 256,
				rand() % 256));

		// si clic droit quitter
		if (al_mouse_button_down(&mouse, 2))
			fin = 1;
		

		al_flip_display();
	}

	al_destroy_display(display);
	return 0;
}