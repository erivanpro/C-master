/*********************************************************************************
Exercice 18 :
placer des fruits dans dist'arbre
Modifier la fonction récursive dessine_arbre() de façon à dessiner le segment
terminal en vert et à insérer de façon aléatoire des fruits de couleur dans dist'arbre.
*********************************************************************************/
#include "GraphCons.h"

void Branche(int x, int y, int angle, int longueur, double*ax, double *ay, int lettre, int bcolor, int fcolor);
void DessineArbre(int x, int y, int angle, int hauteur, int lettre, int bcolor, int fcolor);
/*****************************************************************************
*****************************************************************************/
int main(int argc, char *argv[])
{
	srand((time_t)time(NULL));
	
	if (!G_PleinEcran())
		if (!G_ConsResizeMax())
			printf("plein ecran impossible\n");

	G_ConsCursor(FALSE);
	
	// Base de l'arbre
	int x = G_ConsTX() / 2;
	int y = G_ConsTY() - 1;
	int angle = 90;
	int hauteur = 20;

	printf("Enter pour dessiner l'arbre (Escape pour quitter)\n");
	while (1) {
		G_PollEvent();
		
		// réappuyer sur ENTER permet de changer la couleur de l'arbre.
		if (G_KeyDown(VK_RETURN)) 
			DessineArbre(x, y, angle, hauteur, 'A' + rand() % 26, 1 + rand() % COLORMAX, 1 + rand() % COLORMAX);
		else if (G_KeyDown(VK_ESCAPE))
			break;
	}
	return 0;
}
/*****************************************************************************
La fonction G_DrawLigneAngle trace un segment depuis la position cx, cy
selon dist'angle angle et la distance dist. La position d'arrivée et sortie en ax et ay.
Le tracé utilise la lettre ainsi que les couleurs données en paramètre. 
*****************************************************************************/
void Branche( int x, int y, int angle, int hauteur, double*ax, double *ay, 
			 int lettre, int bcolor, int fcolor)
{
	const double pi = 3.1416;
	const double degre = pi * 2 / 360.0;

	*ax = x + hauteur * cos(angle*degre);
	*ay = y - hauteur * sin(angle*degre);
	
	// petits problèmes d'arrondis
	// (attention l'étoile * ici correspond à l'opérateur pointeur d'accès)
	*ax = (*ax >= (int)(*ax) + 0.5) ? (int)(*ax) + 1 : (int)(*ax);
	*ay = (*ay >= (int)(*ay) + 0.5) ? (int)(*ay) + 1 : (int)(*ay);
	   
	// à la différence de la fonction G_DrawLigneAngle() plusieurs traits 
	// permettent ici de représenter l'épaisseur décroissantes des branches 
	// depuis le tronc de l'arbre. L'épaisseur est relative à la hauteur 
	// de branches. Plus la branche est longue plus elle est épaisse.

	for (int i = 0; i < hauteur / 2; i++) {
		// FRUITS :
		// à 2 la branche ne fait que deux cases et la dernière correspond 
		// visuellement à une feuille
		if(hauteur <=2 && rand() % 2)
			// (fruits) toute la ligne change de couleur 
			G_DrawLigne(x + i, y, *ax + i, *ay, ' ', BRIGHT_RED, fcolor);
		else
			G_DrawLigne(x + i, y, *ax + i, *ay, lettre, bcolor, fcolor);
	}
	
	// (fruits) mais la première position de la ligne repasse dans la couleur  
	// de l'arbre et correspond visuellement à la fin de la branche précédente.
	if (hauteur <= 2)
		G_DrawChar(x, y, lettre, bcolor, fcolor);
}
/*****************************************************************************
*****************************************************************************/
void DessineArbre( int x, int y, int angle, int hauteur, int lettre, int bcolor, int fcolor)
{
	double ax, ay;
	
	// Solution 2 : colorer les dernières branches qui font office de feuilles.
	// Cette modification doit alors être portée dans la fonction Branche()
	Branche(x, y, angle, hauteur, &ax, &ay, lettre, bcolor, fcolor);
	

	hauteur = hauteur * 2 / 3.0;
	if (hauteur > 1) {
		int nbbranche = 2;
		int ecartement = 180 / nbbranche;
		for (int i = 1; i <= nbbranche; i++) {
			DessineArbre(ax, ay, angle - 90 - (ecartement / 2) + (i * ecartement),
					hauteur, lettre, bcolor, fcolor);
		}
	}
	/* // solution 1 : positionner des fruits sous forme de petits rects
	// en bout de branche. Il convient d'affiner en fonction des angles.
	// Si vers haut diminuer cy, vers droite augmenter cx, vers bas augmenter cy
	// vers gauche diminuer cx. La solution ci-dessous est bonne pour gauche-haut.
	// Les autres sont à affiner selon angle
	
	else if (rand() % 2) {
		bcolor = BRIGHT_RED;
		lettre = ' ';
		G_FillRect(cx -2, cy - 1, cx, cy, ' ', BRIGHT_RED, BLACK);
	}*/
		
}
/*****************************************************************************
TOOLS
*****************************************************************************/


