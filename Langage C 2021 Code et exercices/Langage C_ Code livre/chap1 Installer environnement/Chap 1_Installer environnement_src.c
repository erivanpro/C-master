/************************************************************
*                                                           *
*       CHAPITRE 1 : INSTALLER UN ENVIRONNEMENT             *
*                                                           *
*************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de pr�f�rence vide sous visual studio)
    - copier toute la page dans le fichier C du nouveau projet 
      (�craser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte imm�diatement ajouter
      getchar(); avant le return 0; de fin de main()
      (ou voir Chap 1 / Conserver la fen�tre console ouverte)
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

#include <stdio.h>	// pour avoir acc�s � la fonction printf()

int main()			// entr�e du programme,
{					// ouverture bloc d�instructions

	// appel de la fonction printf() qui affiche la cha�ne
    // de caract�res pass�e en  param�tre
	printf("bonjour");


	// valeur de retour de la fonction main qui indique un bon
	// d�roulement du programme.
	return 0;

}// fermeture bloc d�instructions
*/
//---------------------------------------------------
/*
// Bloquer le fen�tre console apr�s ex�cution d'un programme
// Ajouter une instruction :
// Utiliser l'instruction getchar() (solution portable)
#include <stdio.h>

void pause()
{
    printf("Appuyez sur Enter pour continuer...\n");
    rewind(stdin); // r�initialise le fichier des entr�es
    getchar(); // ici le programme s'arr�te et attend Enter
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
// Bloquer le fen�tre console apr�s ex�cution d'un programme
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



