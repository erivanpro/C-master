#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <stdio.h>

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}

/*************************************************************
*************************************************************/
int main()
{

    if (!al_init())
        erreur("al_init()");

    // Fenêtre 
    ALLEGRO_DISPLAY* display;
    display = al_create_display(800, 600);
    if (!display)
        erreur("al_create_display()");

    // Avoir le clavier 
    if (!al_install_keyboard())
        erreur("al_install_keyboard()");

    // Avoir la souris 
    if (!al_install_mouse())
        erreur("al_install_mouse()");

    // File d'événements 
    ALLEGRO_EVENT_QUEUE* queue;
    queue = al_create_event_queue();
    if (!queue)
        erreur("al_create_event_queue()");

    // Sélection des événements à prendre dans la file 
    al_register_event_source(queue,
        al_get_display_event_source(display));
    al_register_event_source(queue,
        al_get_keyboard_event_source());
    al_register_event_source(queue, 
        al_get_mouse_event_source());

    // Boucle événements 
    int fin = 0;
    while (!fin) {

        // Récupération des événements 
        ALLEGRO_EVENT event = { 0 };
        al_wait_for_event(queue, &event);

        // Selon événement trouvé 
        switch (event.type) {

            // Événements souris 
        case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
            printf("bouton %d presse\n", event.mouse.button);
            break;
        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            printf("bouton %d relache\n", event.mouse.button);
            break;
            // Si mouvement 
        case ALLEGRO_EVENT_MOUSE_AXES:
            printf("x:%4d  y:%4d  z:%3d\n",
                event.mouse.x, event.mouse.y,
                event.mouse.z);
            break;

            // Événements clavier 
        case ALLEGRO_EVENT_KEY_DOWN:
        {
            const char* nomkey = al_keycode_to_name(
                event.keyboard.keycode);
            printf("%8s : %s\n", "DOWN", nomkey);
        }
        break;
        case ALLEGRO_EVENT_KEY_UP:
        {
            const char* nomkey = al_keycode_to_name(
                event.keyboard.keycode);
            printf("%8s : %s\n","UP", nomkey);
        }
        break;
        // Caractères et répétitions 
        case ALLEGRO_EVENT_KEY_CHAR:
        {
            char* label = event.keyboard.repeat ?
                "repeat" : "KEY_CHAR";
            const char* nomkey = al_keycode_to_name(
                event.keyboard.keycode);
            printf("%8s : %s\n", label, nomkey);
        }
        break;

        // Événements fenêtre 
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            fin = true;
            break;
        }
    }
    //Libérer les ressources utilisées 
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    return 0;
}
