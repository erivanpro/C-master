#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_primitives.h> 
#include <time.h> 

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
    ALLEGRO_DISPLAY_MODE mode;
    ALLEGRO_KEYBOARD_STATE key;
    // les tracés avec une animation 
    float ptxy[8]; // les points de la courbe 
    float dxdy[8]; // les déplacements de chaque point 
    ALLEGRO_COLOR color;
    int screenx, screeny;
    int i;

    srand(time(NULL));

    if (!al_init())
        erreur("al_init()");
    if (!al_install_keyboard())
        erreur("al_install_keyboard()");
    if (!al_init_primitives_addon())
        erreur("al_init_primitives_addon()");

    // création plein écran sans fenêtre de la taille maximum 
    al_get_display_mode(al_get_num_display_modes() - 1, &mode);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    display = al_create_display(mode.width, mode.height);
    if (!display)
        erreur("al_create_display()");

    // taille écran 
    screenx = al_get_display_width(display);
    screeny = al_get_display_height(display);

    // initialiser les positions de chaque point,   
    // les valeurs de déplacement et la couleur 
    for (i = 0; i < 8; i += 2) {
        ptxy[i] = rand() % screenx;
        ptxy[i + 1] = rand() % screeny;
        dxdy[i] = (1 + rand() % 10) * (rand() % 2 * 2 - 1);
        dxdy[i + 1] = (1 + rand() % 10) * (rand() % 2 * 2 - 1);
    }
    color = al_map_rgba(rand() % 255, 64, rand() % 255, 128);

    do {
        al_get_keyboard_state(&key);

        // bouger 
        for (i = 0; i < 8; i += 2) {
            ptxy[i] += dxdy[i];
            if (ptxy[i]<0 || ptxy[i]>screenx)
                dxdy[i] *= -1;

            ptxy[i + 1] += dxdy[i + 1];
            if (ptxy[i + 1]<0 || ptxy[i + 1]>screeny)
                dxdy[i + 1] *= -1;
        }
        // afficher 
        al_draw_spline(ptxy, color, 20);
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));

        al_rest(1 / 30.0);

    } while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));


    return 0;
}
