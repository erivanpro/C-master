#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>

#define COLORALEA al_map_rgb(rand()%256,rand()%256,rand()%256)
const int SCRX = 800;
const int SCRY = 600;

void erreur(const char*txt)
{
	ALLEGRO_DISPLAY*d;
	d = al_is_system_installed() ? al_get_current_display() : NULL;
	al_show_native_message_box(d, "Erreur", txt, NULL, NULL, 0);
	exit(EXIT_FAILURE);
}
/*****************************************************************
fonction principale qui permet de savoir si un point est à gauche
d'un vecteur.Nous utilisons la règle du déterminant : soit trois
points O, I et P, P est à gauche de OI si le déterminant
oix*opy-oiy*opx des vecteurs OI(oix,oiyi) et OP(opx,opy) est
positif et à droite sinon.
*****************************************************************/
int gauche(int px, int py, int ox, int oy, int ix, int iy)
{
	int oix, oiy, opx, opy, determinant;

	// avoir les vecteurs oi et op
	oix = ix - ox;
	oiy = iy - oy;
	opx = px - ox;
	opy = py - oy;

	// calculer le déterminant
	determinant = oix*opy - oiy*opx;

	// inversion pour le point de vue de l'observateur, retourne 0
	// si positif et à droite et 1 si négatif et à gauche pour
	// l'observateur

	return (determinant>0) ? 0 : 1;
}
/*****************************************************************
à partir de la fonction gauche, en tournant dans le sens inverse
des aiguilles d'une montre, voyons si le point (x,y) est ou pas
dans triangle a-b-c-
*****************************************************************/
int in_triangle(int x, int y,
	int ax, int ay, int bx, int by, int cx, int cy)
{
	int res = 0;
	// le point (x,y) est-il à gauche de chaque segment ?
	res += gauche(x, y, ax, ay, bx, by);
	res += gauche(x, y, bx, by, cx, cy);
	res += gauche(x, y, cx, cy, ax, ay);
	return (res == 3) ? 1 : 0;
}
/*****************************************************************
initialisation d'un triangle
*****************************************************************/
void nouveau_triangle(int*x1,int*y1,int*x2,int*y2,int*x3,int*y3)
{
	// efface le triangle courant
	al_clear_to_color(al_map_rgb(0, 0, 0));
	// nouveaux sommets
	*x1 = rand() % SCRX / 2;
	*y1 = SCRY / 2 + rand() % SCRY / 2;
	*x2 = SCRX / 2 + rand() % SCRX / 2;
	*y2 = SCRY / 2 + rand() % SCRY / 2;;
	*x3 = rand() % SCRX;
	*y3 = rand() % SCRY / 2;
	// affichage
	al_draw_filled_triangle(*x1, *y1, *x2, *y2, *x3, *y3, COLORALEA);
}
/*****************************************************************
*****************************************************************/
int main()
{
	ALLEGRO_DISPLAY*display;
	ALLEGRO_KEYBOARD_STATE key;
	ALLEGRO_MOUSE_STATE mouse;
	
	int x1, y1, x2, y2, x3, y3;

	if (!al_init())
		erreur("al_init()");
	if (!al_install_keyboard())
		erreur("al_install_keyboard()");
	if (!al_install_mouse())
		erreur("al_install_mouse()");
	if (!al_init_primitives_addon())
		erreur("al_init_primitives_addon()");

	display = al_create_display(SCRX, SCRY);
	if (!display)
		erreur("al_create_display()");

	// un triangle au départ
	nouveau_triangle(&x1, &y1, &x2, &y2, &x3, &y3);
	do{
		al_get_keyboard_state(&key);
		al_get_mouse_state(&mouse);

		// nouveau triangle
		if (al_key_down(&key, ALLEGRO_KEY_ENTER))
			nouveau_triangle(&x1, &y1, &x2, &y2, &x3, &y3);

		// si dans triangle changer la couleur
		if (in_triangle(mouse.x, mouse.y, x1, y1, x2, y2, x3, y3))
			al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, COLORALEA);

		al_flip_display();


	} while (!al_key_down(&key, ALLEGRO_KEY_ESCAPE));

	al_destroy_display(display);
	return 0;
}
/*****************************************************************
*****************************************************************/