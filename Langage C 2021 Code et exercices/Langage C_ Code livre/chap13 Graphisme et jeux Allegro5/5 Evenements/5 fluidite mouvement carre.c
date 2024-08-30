#include<allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_primitives.h> 

#define NOIR    al_map_rgb(0,0,0) 
#define BLEU    al_map_rgb(128,0,255) 

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
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_TIMER* timer;

    int screenx = 800;// dimension fenêtre 
    int screeny = 600;
    int x = screenx / 2;// position rectangle 
    int y = screeny / 2;

    int fin = false;
    bool dessine = true;// pour contrôler les opérations d'affichage 

    /*Pour mieux contrôler le clavier nous allons conserver en
    permanence l'état des touches qui nous intéressent dans un
    tableau de booléens à part. L'indice de chaque touche est
    identifié dans le tableau par une constante et toutes les
    constantes sont réunies dans un enum
    */
    enum { KEY_UP, KEY_RIGHT, KEY_DOWN, KEY_LEFT, KEY_MAX };
    bool key[KEY_MAX] = { 0 };

    // les initialisations 
    if (!al_init())
        erreur("al_init()");

    if (!al_init_primitives_addon())
        erreur("al_init_primitives_addon()");

    if (!al_install_keyboard())
        erreur("al_install_keyboard()");

    display = al_create_display(screenx, screeny);
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

    // démarrer le timer 
    al_start_timer(timer);

    while (!fin) {

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            fin = true;
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:    key[KEY_UP] = true;   break;
            case ALLEGRO_KEY_RIGHT: key[KEY_RIGHT] = true; break;
            case ALLEGRO_KEY_DOWN:  key[KEY_DOWN] = true; break;
            case ALLEGRO_KEY_LEFT:  key[KEY_LEFT] = true; break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_KEY_UP) {
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:    key[KEY_UP] = false;  break;
            case ALLEGRO_KEY_RIGHT: key[KEY_RIGHT] = false; break;
            case ALLEGRO_KEY_DOWN:  key[KEY_DOWN] = false; break;
            case ALLEGRO_KEY_LEFT:  key[KEY_LEFT] = false; break;
            case ALLEGRO_KEY_ESCAPE: fin = true;          break;
            }
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) {
            y -= key[KEY_UP] * 10;    //(true vaut 1 et false 0) 
            x += key[KEY_RIGHT] * 10;
            y += key[KEY_DOWN] * 10;
            x -= key[KEY_LEFT] * 10;

            dessine = true;
        }

        // sur événement timer ET dernière touche appuyée prise 
        // en compte 
        if (dessine == true && al_is_event_queue_empty(queue)) {

            // effacer le double buffer 
            al_clear_to_color(NOIR);

            // afficher le rectangle à sa position courantes 
            // dans le double buffer 
            al_draw_filled_rectangle(x, y, x + 20, y + 20, BLEU);

            // passer le double buffer à l'écran 
            al_flip_display();

            dessine = false;
        }
    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}
