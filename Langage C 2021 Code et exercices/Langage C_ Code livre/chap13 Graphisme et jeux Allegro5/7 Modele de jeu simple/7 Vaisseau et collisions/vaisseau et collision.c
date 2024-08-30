#include "jeu.h"

/*****************************************************************
*****************************************************************/
int main()
{
	//--------------------------------Allegro et gestion events
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE*queue;
	ALLEGRO_TIMER*timer;
	bool fin = false;
	bool dessin = false;

	t_vaisseau vaisseau;
	t_missile missiles[NBMAXMISSILES];
	t_ennemi ennemis[NBMAXENNEMIS];

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
	init_all_ennemis(ennemis);

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

			// missiles
			avance_all_missiles(missiles);

			// gestion ennemis
			apparition_ennemi(ennemis);
			avance_all_ennemis(ennemis);

			// collisions
			collision_missiles(missiles, ennemis,
				&vaisseau);
			collision_vaisseau(&vaisseau, ennemis);

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
			affiche_all_ennemis(ennemis);

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

	// pour pouvoir dessiner dans la bitmap, avant chaque 	// opération de dessin
	al_set_target_bitmap(p->image);

	// dessin dedans
	al_draw_filled_triangle(0, 0, 0, p->ty, p->x, p->ty / 2, al_map_rgb(0, 255, 0));

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
	p->y = (p->y + p->ty + p->dv >= SCRY) ?
		SCRY - p->ty : p->y + p->dv;
}
void gauche(t_vaisseau*p)
{
	p->x = (p->x - p->dv <0) ? 0 : p->x - p->dv;
}
/**************************************************************
VAISSEAU / collisions ennemis
***************************************************************/
void collision_vaisseau(t_vaisseau*p, t_ennemi e[])
{
	int i;
	for (i = 0; i<NBMAXENNEMIS; i++){
		if (e[i].actif == true){
			// la zone x1,y1 - x2,y2 de collision
			// (simplifie écriture)
			int x1 = e[i].x - e[i].tx;
			int y1 = e[i].y - e[i].ty;
			int x2 = e[i].x;
			int y2 = e[i].y + e[i].ty;

			// test
			if (p->x + p->tx > x1 && p->x < x2 &&
				p->y + p->ty > y1 && p->y < y2){

				// conséquences collision
				p->vie--;
				e[i].actif = false;

			}
		}
	}
}
/**************************************************************
MISSILES / initialisation
initialisse ce qui est fixe (vitesse) et état (non actif)
La position sera initialisée au momebt du tir en fonction de la
position du vaisseau
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
MISSILES / bouger
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
MISSILES / mise à feu
***************************************************************/
void lancement_missile(t_missile m[], t_vaisseau*p)
{
	int i;
	for (i = 0; i<NBMAXMISSILES; i++){
		if (m[i].actif == false){
			m[i].actif = true;
			m[i].x = p->x + p->tx;
			m[i].y = p->y + p->ty / 2;
			break; // sortir de la boucle
		}
	}
}
/**************************************************************
MISSILES / collisions
***************************************************************/
void collision_missiles(t_missile m[], t_ennemi e[], t_vaisseau*p)
{
	int i, j;
	for (j = 0; j<NBMAXENNEMIS; j++){
		if (e[j].actif == true){
			for (i = 0; i<NBMAXMISSILES; i++){

				if (m[i].actif == true &&
					m[i].x > e[j].x - e[j].tx &&
					m[i].y > e[j].y - e[j].ty &&
					m[i].y < e[j].y + e[j].ty){

					m[i].actif = false;
					e[j].actif = false;
					p->score++;
				}
			}
		}
	}
}
/**************************************************************
ENNEMIS / initialisation
***************************************************************/
void init_all_ennemis(t_ennemi e[])
{
	int i;
	for (i = 0; i<NBMAXENNEMIS; i++){
		e[i].actif = false;
		e[i].dv = 5 + rand() % 5;
		e[i].tx = 5 + rand() % 20;
		e[i].ty = 5 + rand() % 20;
	}
}
/**************************************************************
ENNEMIS / affichage
***************************************************************/
void affiche_all_ennemis(t_ennemi e[])
{
	int i;
	for (i = 0; i<NBMAXENNEMIS; i++){
		if (e[i].actif == true)
			al_draw_filled_ellipse(e[i].x, e[i].y,
			e[i].tx, e[i].ty,
			al_map_rgb(255, rand() % 256, rand() % 256));

	}
}
/**************************************************************
ENNEMIS / mouvement
***************************************************************/
void avance_all_ennemis(t_ennemi e[])
{
	int i;
	for (i = 0; i<NBMAXENNEMIS; i++){
		if (e[i].actif == true){
			e[i].x -= e[i].dv; // attention soustraction
			if (e[i].x - e[i].tx < 0)
				e[i].actif = false;
		}
	}
}
/**************************************************************
ENNEMIS / lancement
***************************************************************/
void apparition_ennemi(t_ennemi e[])
{
	int i;
	for (i = 0; i<NBMAXENNEMIS; i++){
		if (e[i].actif == false && rand() % 1000<10){
			e[i].x = SCRX - e[i].tx;
			e[i].y = rand() % (SCRY - (e[i].ty * 2));
			e[i].actif = true;
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