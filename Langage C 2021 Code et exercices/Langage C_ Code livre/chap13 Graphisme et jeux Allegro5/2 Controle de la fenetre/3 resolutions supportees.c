#include <stdio.h>  
#include <time.h>  
#include <allegro5/allegro.h>  
#include <allegro5/allegro_native_dialog.h>  

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
    ALLEGRO_DISPLAY_MODE mode;
    int i, nbmode;
    srand(time(NULL));

    if (!al_init())
        erreur("al_init()");

    // r�cup�re le nombre de r�solutions possibles  
    nbmode = al_get_num_display_modes();
    printf("il y a %d resolution possibles :\n", nbmode);

    for (i = 0; i < nbmode; i++) {
        // r�cup�re les informations pour chaque mode  
        al_get_display_mode(i, &mode);

        // affiche la r�solution du mode courant   
        // dans la console  
        printf("mode %2d resolution %4d x %4d "
            "%2d bits et %2d \n",
            i, mode.width, mode.height,
            al_get_pixel_format_bits(mode.format),
            mode.refresh_rate);
    }

    // tester les r�solutions  
    do {
        printf("entrer le numero du mode souhaite :\n");
        scanf_s("%d", &i);
        rewind(stdin);

        if (i >= 0 && i < nbmode) {
            // cr�e un display plein �cran  
            // dans le mode courant  
            al_get_display_mode(i, &mode);

            al_set_new_display_refresh_rate(mode.refresh_rate);
            al_set_new_display_flags(ALLEGRO_FULLSCREEN);
            display = al_create_display(mode.width,
                mode.height);

            // change la couleur de la fen�tre  
            al_clear_to_color(al_map_rgb(rand() % 256,
                rand() % 256,
                rand() % 256));
            // affiche et reste trois seconde  
            al_flip_display();
            al_rest(3.0);

            // d�truit le display courant, passe au suivant  
            al_destroy_display(display);
        }
    } while (i >= 0 && i < nbmode);

    return 0;
}
