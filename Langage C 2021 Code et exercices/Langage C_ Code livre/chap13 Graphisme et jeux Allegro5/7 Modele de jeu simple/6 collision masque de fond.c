#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

const int SCRX = 800;
const int SCRY = 600;

void erreur(const char*txt)
{
	ALLEGRO_DISPLAY*d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/*****************************************************************
La fonction test l'égalité de deux couleurs et retourne le  
résultat. Les couleurs sont des structures et il est nécessaire de 
comparer chaque champ. Le champ  a du canal alpha pour la 
transparence n'est pas prise en compte.
*****************************************************************/
bool meme_couleur(ALLEGRO_COLOR c1, ALLEGRO_COLOR c2)
{
	return(c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}
/*****************************************************************
*****************************************************************/
void creation_decor(ALLEGRO_BITMAP*fond, ALLEGRO_DISPLAY*display)
{
	al_clear_to_color(al_map_rgb(0,0,0));
	al_set_target_bitmap(fond);
	int x = rand() % SCRX;
	int y = rand() % SCRY;
	int tx = (rand() % (SCRX - x)) / 2;
	int ty = (rand() % (SCRY - y)) / 2;
	ALLEGRO_COLOR c = al_map_rgb(rand() % 256,
		rand() % 256,
		rand() % 256);
	al_draw_filled_rectangle(x, y, x + tx, y + ty, c);
	al_set_target_backbuffer(display);
}
/*****************************************************************
*****************************************************************/
int main()
{
	ALLEGRO_DISPLAY*display;
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_MOUSE_STATE mouse;
	ALLEGRO_COLOR vert, rouge, noir, color;
	ALLEGRO_BITMAP*fond;

	if (!al_init())
		erreur("al_init()");
	if (!al_install_keyboard())
		erreur("al_install_keyboard()");
	if (!al_install_mouse())
		erreur("al_install_mouse()");
	if (!al_init_primitives_addon())
		erreur("al_init_primitives_addon()");

	//création écran
	display = al_create_display(SCRX, SCRY);
	if (!display)
		erreur("al_create_display()");

	// création fond (déjà noir par défaut)
	fond = al_create_bitmap(SCRX, SCRY);
	if (!fond)
		erreur("al_create_bitmap()");

	noir = al_map_rgb(0, 0, 0); // couleur de fond
	vert = al_map_rgb(0, 255, 0);// couleur si quelque chose
	rouge = al_map_rgb(255, 0, 0);// couleur si rien

	// premier décor invisible
	creation_decor(fond, display);

	do{
		al_get_keyboard_state(&key);
		al_get_mouse_state(&mouse);

		// rempalcement du décor courant
		if (al_key_down(&key, ALLEGRO_KEY_ENTER))
			creation_decor(fond, display);

		// pour voir le décor à l'écran
		if (al_key_down(&key, ALLEGRO_KEY_F1))
			al_draw_bitmap(fond, 0, 0, 0);

		// récupérer info sur fond
		if (meme_couleur(al_get_pixel(fond, mouse.x, mouse.y), noir))
			color = rouge; // rien
		else
			color = vert;// quelque chose

		// dessiner un cercle à la position de la souris
		al_draw_filled_circle(mouse.x, mouse.y, 5, color);
		al_flip_display();

	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	al_destroy_display(display);
	return 0;
}
/*****************************************************************
*****************************************************************/