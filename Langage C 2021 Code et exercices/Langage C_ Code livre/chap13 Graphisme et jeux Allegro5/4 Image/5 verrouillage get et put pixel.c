#include <allegro5/allegro.h> 
#include <allegro5/allegro_native_dialog.h> 
#include <allegro5/allegro_image.h> 

void erreur(const char* txt)
{
    ALLEGRO_DISPLAY* d;
    d = al_is_system_installed() ? al_get_current_display() : NULL;
    al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
    exit(EXIT_FAILURE);
}
/***************************************************************
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
/***************************************************************
***************************************************************/

int main()
{
    ALLEGRO_DISPLAY* display;
    ALLEGRO_KEYBOARD_STATE key;
    ALLEGRO_BITMAP* image;
    int tx, ty;

    if (!al_init())
        erreur("al_init()");
    if (!al_install_keyboard())
        erreur("al_install_keyboard()");
    if (!al_init_image_addon())
        erreur("al_init_primitives_addon()");

    display = al_create_display(800, 600);
    if (!display)
        erreur("al_create_display()");

    image = al_load_bitmap("image.bmp");
    if (!image)
        erreur("al_load_bitmap()");
    tx = al_get_bitmap_width(image);
    ty = al_get_bitmap_height(image);

    do {
        al_get_keyboard_state(&key);

        if (is_key_pressed(&key, ALLEGRO_KEY_F1, 10)) {
            al_set_target_bitmap(image);
            if (al_lock_bitmap(image,
                al_get_bitmap_format(image),
                ALLEGRO_LOCK_READWRITE) != NULL) {
                int x, y;
                for (y = 0; y < ty; y++) {
                    for (x = 0; x < tx; x++) {
                        unsigned char r, g, b;
                        ALLEGRO_COLOR color;
                        color = al_get_pixel(image, x, y);
                        al_unmap_rgb(color, &r, &g, &b);

                        r = (r < 246) ? r + rand() % 10 : 0;
                        g = (g > 10) ? g - rand() % 10 : 255;
                        b = (b < 251) ? b + rand() % 5 : 0;

                        al_put_pixel(x, y, al_map_rgb(r, g, b));
                    }
                }
                al_unlock_bitmap(image);
                al_set_target_backbuffer(display);
            }
        }
        al_draw_bitmap(image, 0, 0, 0);
        al_flip_display();

    } while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

    al_destroy_display(display);
    return 0;
}
