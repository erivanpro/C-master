#include "jeu.h"   // ne pas oublier

/*****************************************************************
*****************************************************************/
int main()
{
	//------------------------Allegro et gestion evénements
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE*queue;
	ALLEGRO_TIMER*timer;
	bool fin = false;
	bool dessin = false;

	t_vaisseau vaisseau;
	t_missile missiles[NBMAXMISSILES];

	if (!al_init())
		erreur("init allegro");

	if (!al_init_primitives_addon())
		erreur("init primitives");

	// pour avoir le clavier
	if (!al_install_keyboard())
		erreur("install keyboard");

	// la fenêtre
	display = al_create_display(SCRX, SCRY);
	if (!display)
		erreur("display");

	// la file d'événements
	queue = al_create_event_queue();
	if (!queue)
		erreur("queue");

	// initialiser le timer
	timer = al_create_timer(1.0 / 50); // temps en seconde
	if (!timer)
		erreur("timer");

	// enregistrement des types d'événements à recueillir
	al_register_event_source(queue,
		al_get_display_event_source(display));
	al_register_event_source(queue,
		al_get_keyboard_event_source());
	al_register_event_source(queue,
		al_get_timer_event_source(timer));

	// démarrage timer
	al_start_timer(timer);

	// -----------------------------initialisations actions

	init_vaisseau(&vaisseau);
	al_set_target_backbuffer(display);

	init_all_missiles(missiles);

	while (!fin){

		ALLEGRO_EVENT ev;
		al_wait_for_event(queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			fin = true;
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_UP:
				key[UP] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[RIGHT] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[LEFT] = true;
				break;

				// tirs missiles
			case ALLEGRO_KEY_SPACE:
				lancement_missile(missiles, &vaisseau);
				break;

				// sortie
			case ALLEGRO_KEY_ESCAPE:
				fin = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode){
			case ALLEGRO_KEY_UP:
				key[UP] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[RIGHT] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[LEFT] = false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			// bouger, action
			if (key[UP])
				monte(&vaisseau);
			if (key[RIGHT])
				droite(&vaisseau);
			if (key[DOWN])
				descend(&vaisseau);
			if (key[LEFT])
				gauche(&vaisseau);

			// avancer les missiles
			avance_all_missiles(missiles);

			dessin = true;
		}

		// dessin si file vide (priorité au clavier)
		if (dessin == true && al_is_event_queue_empty(queue)){

			// les opérations d'affichage

			// 1 effacer le double buffer
			al_clear_to_color(al_map_rgb(0, 0, 0));

			// 2 afficher les entités à leurs positions
			affiche_vaisseau(&vaisseau);
			affiche_all_missiles(missiles);

			// 3 passer le double buffer à l'écran
			al_flip_display();

			dessin = false;
		}
	}
	// nettoyage sortie
	al_destroy_event_queue(queue);
	al_destroy_display(display);
	al_destroy_timer(timer);
	return 0;
}
/****************************************************************
VAISSEAU / Initialisation
*****************************************************************/
void init_vaisseau(t_vaisseau*p)
{
	p->x = 20;
	p->y = SCRY / 2;
	p->dv = 7;
	p->tx = 30;
	p->ty = 20;
	p->vie = 3;
	p->score = 0;

	// l'image du vaisseau : un triangle
	// création d'une bitmap ou possibiité de loader une image
	p->image = al_create_bitmap(p->tx, p->ty);

	// pour pouvoir dessiner dans la bitmap, avant chaque 
	// opération de dessin
	al_set_target_bitmap(p->image);

	// dessin dedans
	al_draw_filled_triangle(0, 0, 0, p->ty, p->x, p->ty / 2,
		al_map_rgb(0, 255, 0));
}
/****************************************************************
VAISSEAU / affichage
*****************************************************************/
void affiche_vaisseau(t_vaisseau*p)
{
	al_draw_bitmap(p->image, p->x, p->y, 0);
}
/**************************************************************
VAISSEAU / mouvement
***************************************************************/
void monte(t_vaisseau*p)
{
	p->y = (p->y - p->dv < 0) ? 0 : p->y - p->dv;
}
void droite(t_vaisseau*p)
{
	p->x = (p->x + p->dv >= SCRX / 3) ? SCRX / 3 : p->x + p->dv;
}
void descend(t_vaisseau*p)
{
	p->y = (p->y + p->ty + p->dv >= SCRY) ? SCRY - p->ty : p->y + p->dv;
}
void gauche(t_vaisseau*p)
{
	p->x = (p->x - p->dv <0) ? 0 : p->x - p->dv;
}
/**************************************************************
MISSILES / initialisation
***************************************************************/
void init_all_missiles(t_missile m[])
{
	int i;
	for (i = 0; i<NBMAXMISSILES; i++){
		m[i].dv = 10;
		m[i].actif = false;
	}
}
/**************************************************************
MISSILES / affichage
***************************************************************/
void affiche_all_missiles(t_missile m[])
{
	int i;
	for (i = 0; i<NBMAXMISSILES; i++){
		if (m[i].actif == true)
			al_draw_filled_ellipse(m[i].x, m[i].y, 3, 2,
			al_map_rgb(0, 255, 0));

	}
}
/**************************************************************
MISSILES / mouvement
***************************************************************/
void avance_all_missiles(t_missile m[])
{
	int i;
	for (i = 0; i<NBMAXMISSILES; i++){
		if (m[i].actif == true){
			m[i].x += m[i].dv;
			if (m[i].x >= SCRX)
				m[i].actif = false;
		}
	}
}
/**************************************************************
MISSILES / lancement
***************************************************************/
void lancement_missile(t_missile m[], t_vaisseau*p)
{
	int i;
	for (i = 0; i<NBMAXMISSILES; i++){
		if (m[i].actif == false){
			m[i].actif = true;
			m[i].x = p->x + p->tx;
			m[i].y = p->y + p->ty / 2;

			break; // provoque la sortie de la boucle
		}
	}
}
/**************************************************************
TOOLS
***************************************************************/
void erreur(const char*txt)
{
	ALLEGRO_DISPLAY *d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/