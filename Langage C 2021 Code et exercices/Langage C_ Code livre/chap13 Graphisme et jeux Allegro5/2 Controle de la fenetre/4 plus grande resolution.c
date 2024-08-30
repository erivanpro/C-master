#include <stdio.h>  
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
    ALLEGRO_DISPLAY_MODE mode;
    int nbmode = 0;
    if (!al_init())
        erreur("al_init()");

    // récupère les informations du dernier mode  
    nbmode = al_get_num_display_modes();
    al_get_display_mode(nbmode - 1, &mode);

    // affiche la résolution du mode courant dans la console  
    printf("mode %d resolution %4d x %4d\n", nbmode,
        mode.width, mode.height);

    // presser une touche pour continuer  
    system("PAUSE");

    return 0;
}
