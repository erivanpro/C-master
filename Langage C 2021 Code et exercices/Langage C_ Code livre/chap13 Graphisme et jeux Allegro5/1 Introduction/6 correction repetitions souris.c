#include <allegro5/allegro.h>  
#include <allegro5/allegro_native_dialog.h>  
#include <stdio.h>
static int* PRESS = NULL;

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d=al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}
/***************************************************************
****************************************************************/
int is_mouse_pressed(ALLEGRO_MOUSE_STATE* mouse, int btn, int repeat)
{
    int res = 0;
    int nbbtn = al_get_mouse_num_buttons();

    // initialisation du tableau de contrôle  
    if (PRESS == NULL) {
        PRESS = (int*)calloc(nbbtn + 1, sizeof(int));
        memset(PRESS, 0, sizeof(int) * (nbbtn + 1));
    }

    if (btn > nbbtn)
        btn = nbbtn;

    if (al_mouse_button_down(mouse, btn) && PRESS[btn] < repeat) {
        PRESS[btn]++;
        res = 1;
    }
    else if (!al_mouse_button_down(mouse, btn))
        PRESS[btn] = 0;

    return res;
}
/***************************************************************
****************************************************************/
int main()
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_MOUSE_STATE mouse;
    ALLEGRO_KEYBOARD_STATE key;
    int i, nbbtn;

    if (!al_init())
        erreur("allegro init");
    if (!al_install_mouse())
        erreur("install mouse");
    if (!al_install_keyboard())
        erreur("install clavier");

    display = al_create_display(800, 600);
    if (!display)
        erreur("display");

    nbbtn = al_get_mouse_num_buttons();
    do {
        // action souris  
        al_get_mouse_state(&mouse);

        // état des boutons  
        for (i = 1; i <= nbbtn; i++) {
            if (is_mouse_pressed(&mouse, i, 2))
                printf("boutons %d presse\n", i);
        }
        // récupération état du clavier  
        al_get_keyboard_state(&key);
    } while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

    al_destroy_display(display);
    free(PRESS);
    return 0;
}