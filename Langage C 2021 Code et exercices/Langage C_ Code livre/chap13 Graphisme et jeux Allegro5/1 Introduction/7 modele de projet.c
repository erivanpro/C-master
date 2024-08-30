#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

void erreur(const char* txt)
{
	ALLEGRO_DISPLAY* d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/*****************************************************************
*****************************************************************/
int main()
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_KEYBOARD_STATE key;

	if (!al_init())
		erreur("al_init()");

	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

	display = al_create_display(800, 600);
	if (!display)
		erreur("al_create_display()");

	do {
		al_get_keyboard_state(&key);



	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	al_destroy_display(display);
	return 0;
}
/*****************************************************************
*****************************************************************/