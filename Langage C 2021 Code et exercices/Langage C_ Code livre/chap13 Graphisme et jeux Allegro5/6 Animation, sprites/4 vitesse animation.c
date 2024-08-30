#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <time.h>

#define NBIMAGE		6

void erreur(const char*txt)
{
	ALLEGRO_DISPLAY*d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/*****************************************************************
*****************************************************************/
int main()
{
	ALLEGRO_DISPLAY*display;
	ALLEGRO_EVENT_QUEUE*queue;
	ALLEGRO_TIMER*timer;

	bool fin = 0;

	ALLEGRO_BITMAP*anim[NBIMAGE];
	int compte, nbTours, image;
	int posx, posy;  // position de l'animation

	srand(time(NULL));
	if (!al_init())
		erreur("al_init()");

	if (!al_init_image_addon())
		erreur("al_init_image_addon()");

	if (!al_install_keyboard())
		erreur("al_install_keyboard()");

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

	// récupération des images
	char nom[256];
	for (int i = 0; i<NBIMAGE; i++){
		sprintf_s(nom, 256, "cat/cat%d.bmp", i);
		anim[i] = al_load_bitmap(nom);
		if (!anim[i])
			erreur("al_load_bitmap()");
		al_convert_mask_to_alpha(anim[i], al_get_pixel(anim[i], 0, 0));
	}
	// initialisations
	image = compte = 0;
	nbTours = 0;
	posx = 0;
	posy = (scry - al_get_bitmap_height(anim[0])) / 2;

	// démarrer le timer
	al_start_timer(timer);

	while (!fin){

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			fin = true;
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN){
			switch (event.keyboard.keycode){

				// change le défilement de l'animation
				case ALLEGRO_KEY_UP:
					nbTours = (nbTours<40) ? nbTours + 1 : 40;
					break;
				case ALLEGRO_KEY_DOWN:
					nbTours = (nbTours>0) ? nbTours - 1 : 0;
					break;

				case ALLEGRO_KEY_ESCAPE:
					fin = true;
					break;

			}
			printf("nbTours : %d\n", nbTours);
		}
		else if (event.type == ALLEGRO_EVENT_TIMER){

			// mouvement
			posx += 5;
			if (posx>scrx)
				posx = -al_get_bitmap_height(anim[0]);

			// animation
			if (compte++ > nbTours){
				compte = 0;
				image = (image + 1) % NBIMAGE;
			}

			//affichage
			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(anim[image], posx, posy, 0);
			al_flip_display();

		}
	}
	for (int i = 0; i<NBIMAGE; i++)
		al_destroy_bitmap(anim[i]);

	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	return 0;
}