#include <allegro5/allegro.h>  
#include <allegro5/allegro_native_dialog.h>  

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
    ALLEGRO_KEYBOARD_STATE key;
    ALLEGRO_MOUSE_STATE mouse;

    ALLEGRO_TEXTLOG* console;  // une console  

    if (!al_init())
        erreur("al_init()");

    if (!al_install_keyboard())
        erreur("al_install_keyboard()");

    if (!al_install_mouse())
        erreur("al_install_mouse()");

    display = al_create_display(800, 600);
    if (!display)
        erreur("al_create_display()");

    // création et ouverture  
    console = al_open_native_text_log("Ma console", 0);
    if (!console)
        erreur("al_open_native_text_log(\"Ma console\", 0)");

    int mx = 0;
    int my = 0;
    do {
        al_get_keyboard_state(&key);
        al_get_mouse_state(&mouse);

        // écrire dans la console  
        if (console != NULL && (mx != mouse.x || my != mouse.y)) {
            mx = mouse.x;
            my = mouse.y;
            al_append_native_text_log(console,
                "position souris : %d, %d\n", mx, my);
        }

        //fermer la console  
        if (al_key_down(&key, ALLEGRO_KEY_ENTER)) {
            al_close_native_text_log(console);
            console = NULL;
        }

    } while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

    al_destroy_display(display);
    return 0;
}
