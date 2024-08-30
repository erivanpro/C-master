// ceci sous Visual Studio uniquement afin de 
// lever l'interdiction d'utiliser des fonctions  
// jugées unsafe par Microsoft. 
#define _CRT_SECURE_NO_WARNINGS 


#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h>  
#include <allegro5/allegro_image.h> 
#include <stdio.h> 

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}
/***************************************************************
****************************************************************/
int is_key_pressed(ALLEGRO_KEYBOARD_STATE* key, int touche,
    int repeat)
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
/***************************************************************
***************************************************************/
int main()
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_KEYBOARD_STATE key;
    ALLEGRO_BITMAP* image;
    int tx, ty, screenx, screeny;

    if (!al_init())
        erreur("al_init()");
    if (!al_install_keyboard())
        erreur("al_install_keyboard()");
    if (!al_init_image_addon())
        erreur("al_init_image_addon()");

    display = al_create_display(800, 600);
    if (!display)
        erreur("al_create_display()");

    screenx = al_get_display_width(display);
    screeny = al_get_display_height(display);

    image = al_load_bitmap("image.bmp");
    if (!image)
        erreur("al_load_bitmap()");

    tx = al_get_bitmap_width(image);
    ty = al_get_bitmap_height(image);

    do {
        al_get_keyboard_state(&key);

        // pour les régions 
        int sx = rand() % tx;
        int sy = rand() % ty;
        int sw = rand() % (tx - sx);
        int sh = rand() % (ty - sy);

        // pivot destination (pivot source centré) 
        int dx = rand() % (screenx - sw);
        int dy = rand() % (screeny - sh);

        // filtre 
        float r = ((float)rand() / RAND_MAX) * 2;
        float g = ((float)rand() / RAND_MAX) * 2;
        float b = ((float)rand() / RAND_MAX) * 2;
        float a = ((float)rand() / RAND_MAX) * 2;
        ALLEGRO_COLOR filtre = al_map_rgba_f(r, g, b, a);

        // proportion pour déformation 
        float xscale = ((float)rand() / RAND_MAX) * 2;
        float yscale = ((float)rand() / RAND_MAX) * 2;
        float angle = ((float)rand() / RAND_MAX) * (2 * 3.14);

        if (is_key_pressed(&key, ALLEGRO_KEY_F1, 100))
            al_draw_tinted_scaled_rotated_bitmap_region(
                image,
                sx, sy,// source haut gauche 
                sw, sh,// source taille 
                filtre,
                tx / 2, ty / 2,// pivot source 
                dx, dy,// pivot destination 
                xscale, yscale, // rapport taille 
                angle,
                0);// pas de permutation  
        // faire une photo d'écran 
        if (is_key_pressed(&key, ALLEGRO_KEY_S, 1)) {
            static int cmpt = 1;
            char nom[80];
            ALLEGRO_BITMAP* save;

            // nom du fichier (save+numéro+extension) 
            sprintf(nom, "save%d.png", cmpt);
            cmpt++;

            // l'image bitmap, deux solutions pour obtenir écran : 
            save = al_get_backbuffer(display);  // écran 
            //save=al_get_target_bitmap();//image cible actuelle 

            // sauvegarde 
            al_save_bitmap(nom, save);

        }

        if (al_key_down(&key, ALLEGRO_KEY_ENTER))
            al_clear_to_color(al_map_rgb(0, 0, 0));

        al_flip_display();

    } while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

    al_destroy_display(display);
    al_destroy_bitmap(image);
    return 0;
}
