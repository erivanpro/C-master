#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

void erreur(const char* txt)
{
	ALLEGRO_DISPLAY* d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/*****************************************************************
*****************************************************************/
int main()
{
	ALLEGRO_DISPLAY* display;
	ALLEGRO_DISPLAY_MODE mode;
	ALLEGRO_KEYBOARD_STATE key;

	if (!al_init())
		erreur("al_init()");

	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

	// plein écran dans la résolution optimale
	al_get_display_mode(al_get_num_display_modes() - 1, &mode);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	display = al_create_display(mode.width, mode.height);
	if (!display)
		erreur("al_create_display()");

	int screenx = al_get_display_width(display);
	int screeny = al_get_display_height(display);

	if (!al_init_primitives_addon())
		erreur("al_init_primitives_addon()");

	do {
		al_get_keyboard_state(&key);

		int x1 = rand() % screenx;
		int y1 = rand() % screeny;
		int x2 = rand() % screenx;
		int y2 = rand() % screeny;
		int x3 = rand() % screenx;
		int y3 = rand() % screeny;
		int cx = rand() % screenx;
		int cy = rand() % screeny;
		int rx = rand() % (screenx / 2);
		int ry = rand() % (screeny / 2);
		int r = rand() % (screeny / 2);

		ALLEGRO_COLOR color = al_map_rgba(rand() % 256, rand() % 256,
			rand() % 256, rand() % 256);
		int thickness = rand() % 30 - 5;

		// LIGNE
		if (al_key_down(&key, ALLEGRO_KEY_F1)) {
			al_draw_line(x1, y1, x2, y2, color, thickness);
		}

		// TRIANGLES
		else if (al_key_down(&key, ALLEGRO_KEY_F2)) {
			if (rand() % 2) // pile ou face
				al_draw_triangle(x1, y1, x2, y2, x3, y3, color, thickness);
			else
				al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, color);
		}

		// RECTANGLES
		else if (al_key_down(&key, ALLEGRO_KEY_F3)) {
			switch (rand() % 4) {
			case 0:
				al_draw_rectangle(x1, y1, x2, y2, color, thickness);
				break;
			case 1:
				al_draw_filled_rectangle(x1, y1, x2, y2, color);
				break;
			case 2:
				al_draw_rounded_rectangle(x1, y1, x2, y2, rx, ry,
					color, thickness);
				break;
			case 3:
				al_draw_filled_rounded_rectangle(x1, y1, x2, y2,
					rx, ry, color);
				break;
			}
		}

		// ELLIPSES
		else if (al_key_down(&key, ALLEGRO_KEY_F4)) {
			if (rand() % 2)
				al_draw_ellipse(cx, cy, rx, ry, color, thickness);
			else
				al_draw_filled_ellipse(cx, cy, rx, ry, color);

		}
		// CERCLES
		else if (al_key_down(&key, ALLEGRO_KEY_F5)) {
			if (rand() % 2)
				al_draw_circle(cx, cy, r, color, thickness);
			else
				al_draw_filled_circle(cx, cy, r, color);
		}

		// EFFACER
		else if (al_key_down(&key, ALLEGRO_KEY_ENTER))
			al_clear_to_color(al_map_rgb(0, 0, 0));


		al_flip_display();

	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	al_destroy_display(display);
	return 0;
}
/*****************************************************************
*****************************************************************/