#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_primitives.h> 

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
/****************************************************************
****************************************************************/
int main()
{
    ALLEGRO_DISPLAY* display;

    if (!al_init())
        erreur("allegro init");

    display = al_create_display(800, 600);
    if (!display)
        erreur("allegro display");

    if (!al_init_primitives_addon())
        erreur("allegro init primitives addon");

    // tracer des rubans 
    const int nbmax = 5;
    t_point tabpoint[] =
    {
        {100, 100, 0},
        {100, 150, 0},
        {200, 200, 0},
        {200, 300, 0},
        {100, 500, 0}
    };

    al_draw_ribbon((float*)tabpoint,       // le tableau de points 
        sizeof(t_point),  // la taille d'une structure 
        al_map_rgb_f(1, 0, 0.5),// couleur 
        10,                     // épaisseur du trait 
        nbmax);                // nombre max de points 


    al_flip_display();
    al_rest(4.0);
    al_destroy_display(display);
    return 0;
}
