#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

// fonction contrôle d'erreur
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
	// pour obtenir une fenêtre
	ALLEGRO_DISPLAY* display;

	// 1) initialisation allegro obligatoire
	if (!al_init())
		erreur("al_init()");

	// 2) créer sa fenêtre
	display = al_create_display(800, 600);
	if (!display)
		erreur("creation display");

	//donner un nom à sa fenêtre
	al_set_window_title(display, "Premier programme !");

	// petit test : colorer la fenêtre en rouge
	al_clear_to_color(al_map_rgb(255, 0, 0));

	// pour rendre visible toutes les opérations de dessin ou
	// d'affichage il faut basculer le double buffer à l'écran.
	// En effet tous les affichages sont faits d'abord dans un
	// double buffer, c'est à dire une image en mémoire
	// invisible à l'écran
	al_flip_display();

	// temps d'attente en seconde
	al_rest(5.0);

	// libérer la mémoire allouée pour la fenêtre
	al_destroy_display(display);

	return 0;
}
/*************************************************************
*************************************************************/
