/********************************************************************
*																	*
*       CHAPITRE 1 : LES VARIABLES									*
*																	*
*********************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de pr�f�rence vide sous visual 
	  studio)
    - copier toute la page dans le fichier C du nouveau projet 
	  (�craser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous 
	  voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte imm�diatement ajouter
      getchar(); avant le return 0; de fin de main()
      (ou voir Chap 1 / Conserver la fen�tre console ouverte)
    - remettre les commentaires pour tester un autre programme
**********************************************************************/
// obtenir des caract�res accentu�s dans la console (sous windows)
/*

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main()
{
	int encode;

	// r�cup�ration encodage courant (celui par d�faut)
	encode = GetConsoleOutputCP();
	
	// passage � l'encodage Window 1252
	SetConsoleOutputCP(1252);
    printf("� � ���� �\n"); // affiche � � ���� �

	// restitution encodage par d�faut 
	SetConsoleOutputCP(encode);
	printf("� � ���� �\n"); // affiche (testez pour voir)

	system("PAUSE");
    return 0;
}
*/
//----------------------------------------------
// Obtenir et afficher la taille en m�moire d'une variable
/*


#include <stdio.h>
int main()
{
int i ;
float f;
double d;
char c;

	printf("taille en memoire de i : %d\n",sizeof(i) );
    printf("taille en memoire de f : %d\n",sizeof(f) );
	printf("taille en memoire de d : %d\n",sizeof(d) );
	printf("taille en memoire de c : %d\n",sizeof(c) );
	return 0;
}
*/
//-----------------------------------------------
// La fonction scanf() 
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int rec;

	scanf("%d",&rec);
	return 0;
}
*/
//-----------------------------------------------
// Plusieurs entr�es dans un seul appel de scanf 1
/*
#include <stdio.h> 
#include <stdlib.h> 

int main()
{
	int rec1, rec2;
	float rec3;
	scanf("%d%d%f", &rec1, &rec2, &rec3);
	return 0;
}
*/
//-----------------------------------------------
// Plusieurs entr�es dans un seul appel de scanf 2
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char c1,c2,c3,c4;

	printf("Entrez quatre lettres : ");
	scanf("%c%c%c%c", &c1, &c2, &c3, &c4);
	printf("vous avez entre : %c, %c, %c, %c\n", c1, c2, c3, c4);

	system("PAUSE");
	return 0;
}

*/
//-----------------------------------------------
// Plusieurs entr�es dans un seul appel de scanf 3
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int rec1, rec2;
   printf("entrer deux valeurs enti�res :\n");
   scanf("%d%d",&rec1,&rec2);
   printf("les valeurs entr�es sont : %d et %d\n",rec1,rec2);
   return 0;
}

*/
//-----------------------------------------------
// scanf ou scanf_s ?
// La fonction scanf_s()  1
/*

#include <stdio.h> 
#include <stdlib.h> 
int main()
{
	int rec;
	scanf_s("%d", &rec);
	return 0;
}
*/
//-----------------------------------------------
// La fonction scanf_s()  2
/*
#include <stdio.h> 
#include <stdlib.h> 

int main()
{
	char a, b, c;
	printf("entrez trois lettres : ");
	scanf_s("%c%c%c", &a, 1, &b, 1, &c, 1);
	printf("vous avez entre : %c, %c, %c\n", a, b, c);

	system("PAUSE");
	return 0;
}
*/
//-----------------------------------------------
// La fonction scanf_s()  3
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char mot[80];
	printf("entrez un mot : ");
	scanf_s("%s", mot,80);
	printf("vous avez entre le mot : %s\n", mot);

	system("PAUSE");
	return 0;
}

*/
//-----------------------------------------------
// scanf() et scanf_s() sous Visual Studio
/*
#define _CRT_SECURE_NO_WARNINGS    // sous visual studio
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int rec;
	scanf("%d", &rec);
	return 0;
}
*/
//-----------------------------------------------
// Contr�ler la saisie avec la valeur de retour de scanf, scanf_s
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int rec1, rec2;
	printf("entrer deux valeurs enti�res :\n");
	int ok = scanf_s("%d%d", &rec1, &rec2);

	printf("Il y a %d valeurs entrees : %d et %d\n",
			ok,rec1,rec2);

	system("PAUSE");
	return 0;
}

*/
//-----------------------------------------------
// Les pi�ges de scanf, scanf_s
// Utiliser rewind(stdin) si plusieurs appels successifs 1
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char c1;
	char c2;
	char c3;

	scanf_s("%c", &c1, 1);
	scanf_s("%c", &c2, 1);
	scanf_s("%c", &c3, 1);

	printf("vous avez entre : %c, %c, %c\n", c1, c2, c3);
	system("PAUSE");
	return 0;
}

*/
//-----------------------------------------------
// Les pi�ges de scanf, scanf_s
// Utiliser rewind(stdin) si plusieurs appels successifs 2
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char c1;
	char c2;
	char c3;

	scanf_s("%c", &c1, 1);
	rewind(stdin);
	scanf_s("%c", &c2, 1);
	rewind(stdin);
	scanf_s("%c", &c3, 1);
	rewind(stdin);

	printf("vous avez entre : %c, %c, %c\n", c1, c2, c3);
	system("PAUSE");
	return 0;
}
*/
//-----------------------------------------------
// R�cup�ration d'une lettre avec scanf_s()
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int c = 0;   // attention � l'initialisation
	// attention nombre total d'octets � sp�cifier en dernier param�tre :
	scanf_s("%c", &c, 1);     // entrer ici la lettre 'A'
	printf("erreur : %d ne vaut pas %d ", c, 'A');

	return 0;
}
*/
//-----------------------------------------------
// Exp�rimentation : Variables simples, d�claration, affectation, affichage, saisie
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
   //---------------
//avoir des variables : <type> <identificateur> < ; >
//le type d�finit une taille et des propri�t�s (virgule ou pas)

// les instructions
int toto; // r�serve un emplacement m�moire (une adresse) pour un int
   toto = 10; // affecte la valeur 10 � la variable toto,

   // remarque :
   // expression (int toto, toto=10) et instruction (int toto; toto=10;)

   //---------------
// les autres types en variables simples du C
char c = 'A';     // 1octet, codage ascii des caract�res
short s = 10;     // 2 octets
int i = 20;       // 2 ou 4 octets
long l = 456;     // 4 octets
float f = 3.89;   // 4 octets
double d = 45678890.876543;// 8 octets

   //---------------
   // pour afficher une valeur :
   //    chaque type a son format :
   //    char %c, short, int, long %d, float %f, double %lf,
   //    adresse m�moire (variable complexe de type pointeur) %p
   printf("i vaut : %d\n", i);

   //---------------
   // codage ascii des caract�res : � une valeur num�rique
   // correspond un caract�re
   printf("%c : %d\n", 112,112);

   //---------------
   // taille en m�moire d'une variable : op�rateur sizeof
   printf("double : %d, int :%d\n",sizeof(double), sizeof(i));

   //---------------
   // r�cup�rer l'adresse m�moire d'une variable : op�rateur &
   printf("%p, %p, %p, %p\n", &i, &l,&f,&d);

   //---------------
   // entr�e utilisateur : scanf
   printf ("entrer une valeur entiere\n");
   scanf_s("%d",&i);
   printf("i vaut : %d\n",i);

   //---------------
   // remarque : les instructions sont ex�cut�es dans l'ordre les
   // unes � la suite des autres de fa�on lin�aire

   //---------------
   // valeur de retour pour communication avec le syst�me
   return 0;

}
*/



