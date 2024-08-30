#include <allegro5/allegro.h>			
#include <allegro5/allegro_native_dialog.h>

// fonction simple pour le contrôle d'erreur
void erreur(const char* txt)
{
	al_show_native_message_box(NULL, "ERREUR", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/*************************************************************
*************************************************************/
int main()
{
	// obligatoire pour utiliser allegro
	if (!al_init())
		erreur("al_init()");

	// un petit message de bienvenue
	al_show_native_message_box(NULL, "Premier programme",
		"Hello allegro !", NULL, NULL, 0);

	return 0;
}
/*************************************************************
*************************************************************/

