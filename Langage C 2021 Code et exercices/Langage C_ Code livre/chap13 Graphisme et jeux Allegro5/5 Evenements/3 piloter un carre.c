#include <allegro5/allegro.h> 
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
    const int screenx = 800; // dimension fenêtre 
    const int screeny = 600;
    int fin = 0;
    int x = screenx / 2;       // position du rectangle 
    int y = screeny / 2;

    if (!al_init())
        erreur("al_init()");

    // initialisation opérations de dessin 
    if (!al_init_primitives_addon())
        erreur("al_init_primitives_addon()");

    if (!al_install_keyboard())
        erreur("install_keyboard()");

    display = al_create_display(screenx, screeny);
    if (!display)
        erreur("al_create_display()");

    queue = al_create_event_queue();
    if (!queue)
        erreur("al_create_event_queue()");

    al_register_event_source(queue,
        al_get_display_event_source(display));
    al_register_event_source(queue,
        al_get_keyboard_event_source());

    while (!fin) {

        // affichage au début pour être visible dès le départ 

        //1 effacer le double buffer 
        al_clear_to_color(NOIR);

        //2 le rectangle à sa position x,y dans le double buffer 
        // (invisible, car en mémoire) 
        al_draw_filled_rectangle(x, y, x + 20, y + 20, BLEU);

        // 3 passer le double buffer à l'écran 
        al_flip_display();


        // Récupération des événements 
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        // de quel type d'événement s'agit-il ? 
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            // si clavier selon touche appuyée, 
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_UP:       y -= 10;    break;
            case ALLEGRO_KEY_RIGHT:    x += 10;    break;
            case ALLEGRO_KEY_DOWN:     y += 10;    break;
            case ALLEGRO_KEY_LEFT:     x -= 10;    break;
            case ALLEGRO_KEY_ESCAPE:   fin = 1;    break;
            }

        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            fin = 1;
    }
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;
}
