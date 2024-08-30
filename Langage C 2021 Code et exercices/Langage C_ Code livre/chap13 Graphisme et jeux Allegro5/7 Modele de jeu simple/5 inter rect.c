#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

typedef struct{
	int x, y, tx, ty;
}t_rect;
/**************************************************************
***************************************************************/
void erreur(const char*txt)
{
	ALLEGRO_DISPLAY*d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/
bool collision_rect(t_rect r1, t_rect r2)
{
	return  (r1.x > r2.x + r2.tx || r1.x + r1.tx < r2.x ||
		r1.y > r2.y + r2.ty || r1.y + r1.ty < r2.y);
}
/*
// autre version
bool collision_rect(t_rect r1, t_rect r2)
{
return  (r1.x < r2.x+r2.tx && r1.x+r1.tx > r2.x &&
r1.y < r2.y+r2.ty && r1.y+r1.ty > r2.y );
}
*/
/**************************************************************
***************************************************************/
int main()
{
	ALLEGRO_DISPLAY*display;
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_MOUSE_STATE mouse;
	int scrx, scry;
	t_rect r1, r2;
	ALLEGRO_COLOR color;

	if (!al_init())
		erreur("al_init()");
	if (!al_install_keyboard())
		erreur("al_install_keyboard()");
	if (!al_install_mouse())
		erreur("al_install_mouse()");
	if (!al_init_primitives_addon())
		erreur("al_init_primitives_addon()");

	scrx = 800;
	scry = 600;
	display = al_create_display(scrx, scry);
	if (!display)
		erreur("al_create_display()");

	// le rectangle r1 est piloté par la souris
	r1.y = r1.x = -1;
	r1.ty = r1.tx = 40;

	// le rectangle r2 est fixe de taille et de
	// position aléatoires
	r2.tx = rand() % 200 + 100;
	r2.ty = rand() % 200 + 100;
	r2.x = rand() % (scrx - r2.tx);
	r2.y = rand() % (scry - r2.ty);

	do{
		al_get_keyboard_state(&key);
		al_get_mouse_state(&mouse);

		if (r1.x != mouse.x || r1.y != mouse.y){
			r1.x = mouse.x;
			r1.y = mouse.y;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (collision_rect(r1, r2))
				color = al_map_rgb(0, 255, 0);
			else
				color = al_map_rgb(255, 0, 0);

			al_draw_filled_rectangle(r2.x, r2.y,
				r2.x + r2.tx, r2.y + r2.ty,
				al_map_rgb(0, 0, 255));
			al_draw_filled_rectangle(r1.x, r1.y,
				r1.x + r1.tx, r1.y + r1.ty,
				color);
			al_flip_display();
		}

	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	al_destroy_display(display);
	return 0;
}
/**************************************************************
***************************************************************/