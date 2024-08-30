#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_primitives.h> 

// les points d'un ruban 
typedef struct
{
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
/***************************************************************
****************************************************************/
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

    // les points constitutifs du ruban 
    const int nbpos = 5;
    t_point tabpos[] =
    {
        {100, 100, 0},
        {100, 150, 0},
        {200, 200, 0},
        {200, 300, 0},
        {100, 500, 0}
    };

    int thickness = 10;
    // 
    int nbpoint = (thickness <= 0) ? nbpos : nbpos * 2;
    t_point* recpoint = (t_point*)calloc(nbpoint, sizeof(t_point));

    al_calculate_ribbon((float*)recpoint, // sortie  
        sizeof(t_point),// taille point en sortie 
        (float*)tabpos,//les positions du ruban 
        sizeof(t_point),//taille point en entrée 
        thickness,//  
/*si >0 alors 2 points par position et séparés de thickness. Si 
<=0 un seul point par position */

        nbpos); // le nombre de positions  


    for (i = 0; i < nbpoint; i++) {
        al_draw_filled_circle(recpoint[i].x, recpoint[i].y, 5,
            al_map_rgb_f(1, 0.5, 0));
        al_flip_display();
        al_rest(0.5);
    }
    al_rest(5.0);
    al_destroy_display(display);
    free(recpoint);
    return 0;
}
