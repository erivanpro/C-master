#include <allegro5/allegro5.h> 
#include <allegro5/allegro_native_dialog.h> 

#define COLORALEA   al_map_rgb(rand()%256,rand()%256,rand()%256) 

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/
int main()
{
    if (!al_init())
        erreur("al_init()");

    ALLEGRO_DISPLAY* display;
    display = al_create_display(800, 600);
    if (!display)
        erreur("al_create_display()");

    // création du timer 
    ALLEGRO_TIMER* timer;
    timer = al_create_timer(1.5); // en secondes 

    // gestion de la file d'événements 
    ALLEGRO_EVENT_QUEUE* queue;
    queue = al_create_event_queue();
    al_register_event_source(queue,
        al_get_display_event_source(display));
    // enregistrement du timer comme source d'événements 
    al_register_event_source(queue,
        al_get_timer_event_source(timer));

    // ATTENTION, ne pas oublier : démarre le timer 
    al_start_timer(timer);

    int fin = 0;
    while (!fin) {

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        // si événement timer changer la couleur 
        if (event.type == ALLEGRO_EVENT_TIMER) {
            al_clear_to_color(COLORALEA);
            al_flip_display();
        }
        // fermeture fenêtre 
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            fin = 1;
    }
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}
