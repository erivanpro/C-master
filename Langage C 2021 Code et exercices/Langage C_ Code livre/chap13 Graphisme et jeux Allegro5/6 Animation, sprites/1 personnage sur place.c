
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#define NBIMAGES	10

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

	// stockage de l'animation
	ALLEGRO_BITMAP* anim[NBIMAGES];
	// position, compteur
	int posx, posy, cmptimage, flag;
	
	if (!al_init())
		erreur("al_init()");

	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

	if (!al_init_image_addon())
		erreur("al_init_image_addon()");

	int scrx = 800;
	int scry = 600;
	display = al_create_display(scrx, scry);
	if (!display)
		erreur("al_create_display()");

	queue = al_create_event_queue();
	if (!queue)
		erreur("al_create_event_queue()");

	timer = al_create_timer(1.0 / 30);
	if (!timer)
		erreur("al_create_timer()");

	// enregistrement événements
	al_register_event_source(queue,
		al_get_display_event_source(display));
	al_register_event_source(queue,
		al_get_keyboard_event_source());
	al_register_event_source(queue,
		al_get_timer_event_source(timer));


	// charger l'animation
	char nom[256];
	for (int i = 0; i < NBIMAGES; i++) {
		sprintf_s(nom, 256, "personnage/pers%d.bmp", i);
		anim[i] = al_load_bitmap(nom);
		if (!anim[i])
			erreur("al_load_bitmap()");
	}


	// initialisation du personnage au centre
	posx = (scrx - al_get_bitmap_width(anim[0])) / 2;
	posy = (scry - al_get_bitmap_height(anim[0])) / 2;
	// initialisation du compteur d'images à 0
	cmptimage = 0;
	flag = 0;

	al_start_timer(timer);
	while (!fin) {

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			fin = true;
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (event.keyboard.keycode) {

				// changer le sens de l'animation
			case ALLEGRO_KEY_ENTER:
				if (flag == 0)
					flag = ALLEGRO_FLIP_HORIZONTAL;
				else if (flag == ALLEGRO_FLIP_HORIZONTAL)
					flag = ALLEGRO_FLIP_VERTICAL;
				else if (flag == ALLEGRO_FLIP_VERTICAL)
					flag |= ALLEGRO_FLIP_HORIZONTAL;
				else
					flag = 0;
				break;

			case ALLEGRO_KEY_ESCAPE:
				fin = true;
				break;

			}
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {

			// mouvement
			al_draw_bitmap(anim[cmptimage], posx, posy, flag);
			cmptimage = (cmptimage + 1) % NBIMAGES;
			al_flip_display();
		}
	}
	for (int i = 0; i < NBIMAGES; i++) {
		al_destroy_bitmap(anim[i]);
	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}