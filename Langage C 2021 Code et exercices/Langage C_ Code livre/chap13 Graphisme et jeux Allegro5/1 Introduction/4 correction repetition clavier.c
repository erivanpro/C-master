#include <allegro5/allegro.h>  
#include <allegro5/allegro_native_dialog.h>  
#include <stdio.h>

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/
int is_key_pressed(ALLEGRO_KEYBOARD_STATE* key, int touche,
    int repeat)
{
    //le tableau conserve ses valeurs d'un appel à l'autre (static)  
    static int press[ALLEGRO_KEY_MAX] = { 0 };
    int res = 0;

    if (al_key_down(key, touche) && press[touche] < repeat) {
        press[touche]++;
        res = 1;
    }
    else if (!al_key_down(key, touche))
        press[touche] = 0;
    return res;

}
/**************************************************************
***************************************************************/
int main()
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_KEYBOARD_STATE k, * key = &k;

    if (!al_init())
        erreur("al_init()");

    if (!al_install_keyboard())
        erreur("install keyboard");

    display = al_create_display(800, 600);
    if (!display)
        erreur("display");

    do {
        al_get_keyboard_state(key);

        if (is_key_pressed(key, ALLEGRO_KEY_UP, 1))
            printf("touche UP pressee\n");

        if (is_key_pressed(key, ALLEGRO_KEY_RIGHT, 2))
            printf("touche RIGHT pressee\n");

        if (is_key_pressed(key, ALLEGRO_KEY_DOWN, 3))
            printf("touche DOWN pressee\n");

        if (is_key_pressed(key, ALLEGRO_KEY_LEFT, 10))
            printf("touche LEFT pressee\n");

    } while (!is_key_pressed(key, ALLEGRO_KEY_ESCAPE, 1));

    al_destroy_display(display);
    return 0;
}
