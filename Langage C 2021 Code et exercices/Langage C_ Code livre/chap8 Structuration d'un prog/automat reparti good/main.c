#include "automat.h"

int MAT[TY][TX] = { 0 };
int SAV[TY][TX] = { 0 };

/****************************************************************
*****************************************************************/
int main()
{
int fin = 0;

	printf("Action  : appuyer sur n'importe quelle touche\n"
		"Quitter : q");
	init_matrice();    
	while (fin != 'q'){    
		if (_kbhit()){     
			fin = _getch(); 
			affiche();    
			calcul();
			copie();
		}
	}
	return 0;
}
/****************************************************************
*****************************************************************/