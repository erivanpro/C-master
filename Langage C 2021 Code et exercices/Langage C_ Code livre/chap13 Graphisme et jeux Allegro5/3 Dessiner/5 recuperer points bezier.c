#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_primitives.h> 

// le type point pour la courbe : la position doit obligatoirement 
// être les deux premiers champs de la structure; 
typedef struct {
    float x, y; // position 
    int autres_donnees;
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

    // les quatre points nécessaires au tracé d'une courbe de Bézier 
    float beziers_4_pos[8] =
    {
        400, 100,
        500, 200,
        300, 400,
        400, 500
    };
    // le nombre maximum de points pour la récupération (pair) 
    int nbpoint = 5 * 2;

    // tableau dynamique pour la récupération 
    t_point* recpoint = (t_point*)calloc(nbpoint, sizeof(t_point));

    // l'épaisseur qui détermine s'il y a un ou deux points 
    // par position : 
    // si épaisseur <=0 : 1 seul point 
    // si épaisseur >0 : 2 points par position qui sont espacés 
    // de épaisseur (thickness) 
    int thickness = 30;

    // le nombre de positions 
    int nbpos = (thickness <= 0) ? nbpoint : nbpoint / 2;

    al_calculate_spline((float*)recpoint,
        sizeof(t_point),
        beziers_4_pos,
        thickness,

        nbpos);


    for (i = 0; i < nbpoint; i++) {
        al_draw_filled_circle(recpoint[i].x, recpoint[i].y, 5,
            al_map_rgb_f(0.5, 1, 0));
        al_rest(0.5);
        al_flip_display();
    }

    al_destroy_display(display);
    free(recpoint);
    return 0;
}
