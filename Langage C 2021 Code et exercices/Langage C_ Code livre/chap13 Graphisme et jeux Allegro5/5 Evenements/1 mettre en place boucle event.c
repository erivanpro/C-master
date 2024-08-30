#include<allegro5/allegro.h> 
#include<allegro5/allegro_native_dialog.h> 

// remplacer un appel de fonction par un mot 
#define COLORALEA al_map_rgb(rand()%256,rand()%256,rand()%256) 

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
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue; //file d'attente des �v�nements 

    if (!al_init())
        erreur("al_init()");

    display = al_create_display(800, 600);
    if (!display)
        erreur("al_create_display()");

    // 1) cr�ation de la file 
    queue = al_create_event_queue();
    if (!queue)
        erreur("al_create_event_queue()");

    // 2) s�lection des types d'�v�nements � prendre en charge 
    // ici les �v�nements choisis concernent la barre des t�ches 
    // de la fen�tre (carr� rouge avec croix pour fermer...) 
    al_register_event_source(
        queue,  // la file 
        al_get_display_event_source(display));// l'�v�nement  
 
    // mise en noir de la fen�tre 
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    // boucle d'�v�nements 
    while (1) {

        ALLEGRO_EVENT event = { 0 };// mise � 0  

        // r�cup�ration NON bloquante et top�e des �v�nements 
        al_wait_for_event_timed(
            queue,   // la file 
            &event,  // l'event par r�f�rence 
            1.0 / 10); // topage en seconde 

        // analyse de l'�v�nement et action en cons�quence 
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        // si non changer la couleur de la fen�tre 
        al_clear_to_color(COLORALEA);
        al_flip_display();
    }

    //lib�rer les ressources utilis�es 
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    return 0;

}
