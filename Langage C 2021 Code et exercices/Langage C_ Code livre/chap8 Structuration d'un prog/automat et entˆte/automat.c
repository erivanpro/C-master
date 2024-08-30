/****************************************************
*													*
*     fichiers .c automate cellulaire + entête		*
*													*
*****************************************************/
#include "automat.h"


/****************************************************************
*****************************************************************/
int main(int argc, char *argv[])
{
	int fin = 0;

	printf("Action  : appuyer sur n'importe quelle touche\n"
		"Quitter : q");

	init_matrice();     // initialisation une fois au début

	while (fin != 'q'){    // pendant la boucle principale

		if (_kbhit()){     // si une touche est appuyée
			fin = _getch();  // récup de la touche appuyée pour
			// contrôler la fin
			affiche();    // le moteur d'organisation
			calcul();
			copie();
		}
	}
	return 0;
}
/****************************************************************
*****************************************************************/
void init_matrice(void)
{
	int i, j;

	// toutes les positions sont mises à 0
	for (j = 0; j<TY; j++){
		for (i = 0; i<TX; i++){
			MAT[j][i] = 0;
			SAV[j][i] = 0;
		}
	}
	// sauf quatre positions au centre qui sont mises à 1
	MAT[TY / 2][TX / 2] = 1;
	MAT[TY / 2 + 1][TX / 2] = 1;
	MAT[TY / 2][TX / 2 + 1] = 1;
	MAT[TY / 2 + 1][TX / 2 + 1] = 1;
}
/****************************************************************
*****************************************************************/
void calcul(void)
{
	int x, y, nb_voisins;

	// pour chaque position dans la matrice (sans compter le
	// pourtour à cause de la recherche des voisins : de 1 à TY-1
	// et non de 0 à TY, idem pour x)
	for (y = 1; y<TY - 1; y++){
		for (x = 1; x<TX - 1; x++){

			// récupération du nombre de voisin à 1
			nb_voisins = compte_voisins(y, x);

			// application de la loi de transition basique et
			// stockage du résultat dans la matrice SAV
			if (nb_voisins <2 || nb_voisins>3)
				SAV[y][x] = 0;
			else
				SAV[y][x] = 1;
		}
	}
}
/****************************************************************
*****************************************************************/
// en paramètre une position donnée
int compte_voisins(int y, int x)
{
	int nb = 0;                 // par défaut 0 voisin à 1

	if (MAT[y][x + 1] == 1)    // examen de chaque position adjacente
		nb++;                // si 1, incrémenter le compte
	if (MAT[y - 1][x + 1] == 1)  // les valeurs y-1, y+1, x-1, x+1
		nb++;                // doivent toujours rester dans la
	if (MAT[y - 1][x] == 1)    // matrice, attention aux débordements !
		nb++;
	if (MAT[y - 1][x - 1] == 1)
		nb++;
	if (MAT[y][x - 1] == 1)
		nb++;
	if (MAT[y + 1][x - 1] == 1)
		nb++;
	if (MAT[y + 1][x] == 1)
		nb++;
	if (MAT[y + 1][x + 1] == 1)
		nb++;

	return nb;             // à la fin retourner le nombre trouvé
}
/****************************************************************
*****************************************************************/
void copie(void)
{
	/*int i, j;

	for (j=0; j<TY; j++){    // méthode basique
	for (i=0 ;i<TX ;i++){
	MAT[j][i]= SAV[j][i];
	}
	}*/
	// Avec la fonction memcpy dans string.h
	memcpy(MAT, SAV, sizeof(int)*TX*TY);
}
/****************************************************************
*****************************************************************/
void affiche(void)
{
	int x, y;

	for (y = 0; y<TY; y++){    // pour chaque position
		for (x = 0; x<TX; x++){
			gotoxy(x, y);       // déplacer le curseur à la position
			if (MAT[y][x] == 1)   // si valeur 1
				textcolor(192);  // couleur rouge en fond
			else
				textcolor(16);   // sinon couleur bleu en fond
			putchar(' ');      // affiche un espace
		}
	}
}
/****************************************************************
****************************************************************/
void gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}
/****************************************************************
*****************************************************************/
void textcolor(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}
/****************************************************************
*****************************************************************/