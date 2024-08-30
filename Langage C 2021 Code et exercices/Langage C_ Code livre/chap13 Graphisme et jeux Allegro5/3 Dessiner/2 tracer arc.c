#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_primitives.h> 
#include <stdio.h> 

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "ERREUR", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}
/**************************************************************
***************************************************************/
int is_key_pressed(ALLEGRO_KEYBOARD_STATE* key, int touche, int repeat)
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
    ALLEGRO_KEYBOARD_STATE key;

    if (!al_init())
        erreur("al_init()");
    if (!al_install_keyboard())
        erreur("al_install_keyboard()");
    if (!al_init_primitives_addon())
        erreur("al_init_primitives_addon()");

    display = al_create_display(800, 600);
    if (!display)
        erreur("al_create_display()");

    int screenx = al_get_display_width(display);
    int screeny = al_get_display_height(display);

    do {
        al_get_keyboard_state(&key);
        int rien = false;

        int r = 100;            //rand()%(screeny/2) +1 ; 
        int rx = rand() % (screeny / 2) + 1;
        int ry = rand() % (screeny / 2) + 1;
        int cx = screenx / 2;     //rand()%screenx; 
        int cy = screeny / 2;     //rand()%screeny; 
        float start_theta = 1 + rand() % 6; //rand()%1000; 
        float delta_theta = 1 + rand() % 6;  //rand()%1000; 
        ALLEGRO_COLOR color = al_map_rgba(rand() % 256, rand() % 256,
            rand() % 256, rand() % 256);
        float thickness = 2;    //((float)rand()/RAND_MAX) * 30; 

        if (is_key_pressed(&key, ALLEGRO_KEY_F1, 1)) {
            al_draw_arc(cx, cy, r, start_theta, delta_theta, color,
                thickness);
            printf("cx=%d, cy=%d, r=%d, start_theta=%.2f, "
                "delta_theta=%.2f, thickness=%.2f\n",
                cx, cy, r, start_theta, delta_theta, thickness);
        }

        else if (is_key_pressed(&key, ALLEGRO_KEY_F2, 1)) {
            al_draw_elliptical_arc(cx, cy, rx, ry, start_theta,
                delta_theta, color, thickness);
            printf("cx=%d, cy=%d, rx=%d, ry=%dstart_theta=%.2f, "
                "delta_theta=%.2f, thickness=%.2f\n",
                cx, cy, rx, ry, start_theta, delta_theta, thickness);
        }

        else if (is_key_pressed(&key, ALLEGRO_KEY_ENTER, 1))
            al_clear_to_color(al_map_rgb(0, 0, 0));

        else
            rien = true;

        // si quelque chose dessiné, le basculer à l'écran 
        if (!rien)
            al_flip_display();

        // pour effacer le double buffer 
        al_clear_to_color(al_map_rgb(0, 0, 0));

    } while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

    return 0;
}
