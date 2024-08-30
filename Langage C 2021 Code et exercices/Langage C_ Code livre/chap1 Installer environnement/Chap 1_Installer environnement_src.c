/************************************************************
*                                                           *
*       CHAPITRE 1 : INSTALLER UN ENVIRONNEMENT             *
*                                                           *
*************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de préférence vide sous visual studio)
    - copier toute la page dans le fichier C du nouveau projet 
      (écraser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte immédiatement ajouter
      getchar(); avant le return 0; de fin de main()
      (ou voir Chap 1 / Conserver la fenêtre console ouverte)
      (Sous Windows uniquement)
    - remettre les commentaires pour tester un autre programme
*/
/****************************************************************
*																*
*       CHapitre 1 :  Installer un environnement				*
*																*
*****************************************************************/
/*
//Afficher du texte avec la fonction printf()

#include <stdio.h>	// pour avoir accès à la fonction printf()

int main()			// entrée du programme,
{					// ouverture bloc d’instructions

	// appel de la fonction printf() qui affiche la chaîne
    // de caractères passée en  paramètre
	printf("bonjour");


	// valeur de retour de la fonction main qui indique un bon
	// déroulement du programme.
	return 0;

}// fermeture bloc d’instructions
*/
//---------------------------------------------------
/*
// Bloquer le fenêtre console après exécution d'un programme
// Ajouter une instruction :
// Utiliser l'instruction getchar() (solution portable)
#include <stdio.h>

void pause()
{
    printf("Appuyez sur Enter pour continuer...\n");
    rewind(stdin); // réinitialise le fichier des entrées
    getchar(); // ici le programme s'arrête et attend Enter
}

int main()
{
    printf("Au commencement le C !\n");

    pause();
    return 0;
}

*/
//---------------------------------------------------
/*
// Bloquer le fenêtre console après exécution d'un programme
// Ajouter une instruction :
// Utiliser une ressource system (non portable)
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Au commencement le C !\n");

    system("PAUSE");
    return 0;
}
*/



