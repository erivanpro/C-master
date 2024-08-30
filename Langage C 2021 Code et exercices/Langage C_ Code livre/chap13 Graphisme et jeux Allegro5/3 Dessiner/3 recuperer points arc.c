#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_primitives.h> 

// le type des points d'un arc 
typedef struct {
    float x, y; // obligatoirement au début de la structure 
    int data;
}t_point;


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
    int i;

    if (!al_init())
        erreur("allegro init");

    display = al_create_display(800, 600);
    if (!display)
        erreur("allegro display");

    if (!al_init_primitives_addon())
        erreur("allegro init primitives addon");

    // les points constitutifs de l'arc 
    int screenx = al_get_display_width(display);
    int screeny = al_get_display_height(display);
    float cx = screenx / 2;
    float cy = screeny / 2;
    float rx = 100;
    float ry = 100;
    float start_theta = 0;
    float delta_theta = 3.5; // radian 

    float thickness = 10;
    int num_segment = 10;
    int nbpoint = (thickness <= 0) ? num_segment : num_segment * 2;
    t_point* dest = (t_point*)calloc(nbpoint, sizeof(t_point));

    al_calculate_arc((float*)dest,
        sizeof(t_point),
        cx, cy,
        rx, ry,
        start_theta,
        delta_theta,
        thickness,
        num_segment);

    for (i = 0; i < nbpoint; i++) {
        al_draw_filled_circle(dest[i].x, dest[i].y, 5,
            al_map_rgb_f(1, 0.5, 0));
        al_flip_display();
        al_rest(0.5);
    }
    al_rest(5.0);
    al_destroy_display(display);
    free(dest);
    return 0;
}
