#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

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
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;

	bool fin = 0;
	bool dessine = true;

	// clavier fluide
	enum { UP, RIGHT, DOWN, LEFT, KEYMAX };
	bool key[KEYMAX] = { false };

	// images et sélection des images. Les images sont rangées
	// dans l'ordre : UP,RIGTH,DOWN,LEFT avec deux images par
	// direction.
	ALLEGRO_BITMAP* anim[8];
	int dir, cmptimage, image;
	int posx, posy;

	if (!al_init())
		erreur("al_init()");

	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

	int scrx = 800;
	int scry = 600;
	display = al_create_display(scrx, scry);
	if (!display)
		erreur("al_create_display()");

	// fond en rouge 
	// al_clear_to_color(al_map_rgb(255,0,0)) ;

	if (!al_init_image_addon())
		erreur("al_init_image_addon()");

	queue = al_create_event_queue();
	if (!queue)
		erreur("al_create_event_queue()");

	timer = al_create_timer(1.0 / 25);
	if (!timer)
		erreur("al_create_timer()");

	// enregistrement événements
	al_register_event_source(queue,
		al_get_display_event_source(display));
	al_register_event_source(queue,
		al_get_keyboard_event_source());
	al_register_event_source(queue,
		al_get_timer_event_source(timer));

	// initialisation personnage. Attention les images doivent
	// correspondre aux directions dans l'ordre
	char nom[256];
	for (int i = 0; i < 8; i++) {
		sprintf_s(nom, 256, "zelda/z%d.bmp", i);
		anim[i] = al_load_bitmap(nom);
		if (!anim[i])
			erreur("al_load_bitmap()");
	}
	// centré au départ
	posx = (scrx - al_get_bitmap_width(anim[0])) / 2;
	posy = (scry - al_get_bitmap_height(anim[0])) / 2;
	dir = cmptimage = image = 0;

	al_start_timer(timer);
	while (!fin) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			fin = true;
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[UP] = true;
				dir = 0;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[RIGHT] = true;
				dir = 1;
				break;
			case ALLEGRO_KEY_DOWN:
				key[DOWN] = true;
				dir = 2;
				break;
			case ALLEGRO_KEY_LEFT:
				key[LEFT] = true;
				dir = 3;
				break;
			case ALLEGRO_KEY_ESCAPE:
				fin = true;
				break;
			}
			// sélection de l'image selon direction et sur
			// événement key_up. 2 images par direction
			// rangées aux indices 01-23-45-67
			cmptimage = 1 - cmptimage; // 0 ou 1
			image = (dir * 2) + cmptimage;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_UP:    key[UP] = false;     break;
			case ALLEGRO_KEY_RIGHT: key[RIGHT] = false;  break;
			case ALLEGRO_KEY_DOWN:  key[DOWN] = false;   break;
			case ALLEGRO_KEY_LEFT:  key[LEFT] = false;   break;
			case ALLEGRO_KEY_ESCAPE: fin = true;         break;
			}
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {

			// avancer
			posy -= 10 * key[UP];
			posx += 10 * key[RIGHT];
			posy += 10 * key[DOWN];
			posx -= 10 * key[LEFT];

			// redessiner
			dessine = true;
		}

		if (dessine == true && al_is_event_queue_empty(queue)) {

			al_clear_to_color(al_map_rgb(0, 0, 0));
			// al_clear_to_color(al_map_rgb(255,0,0));

			al_draw_bitmap(anim[image], posx, posy, 0);
			al_flip_display();

			dessine = false;
		}
	}
	for (int i = 0; i < 8; i++)
		al_destroy_bitmap(anim[i]);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}