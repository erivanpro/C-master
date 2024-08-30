/****************************************************************
*                                                               *
*       CHAPITRE 4 : LES CONTROLES DES BLOCS D'INSTRUCTIONS     *
*                                                               *
*****************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de préférence vide sous visual studio)
    - copier toute la page dans le fichier C du nouveau projet (écraser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte immédiatement ajouter
      getchar(); avant le return 0; de fin de main()
      (ou voir Chap 1 / Conserver la fenêtre console ouverte)
    - remettre les commentaires pour tester un autre programme
*/

/****************************************************
*                                                   *
*       1.   Blocs d'instructions et conditions     *
*                                                   *
*****************************************************/
// Exemple
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{  //------------------------- ouv bloc main B1
int x,pasx;    // déclarations de variables locales au bloc main
               // elles sont visibles (accessibles) dans ce bloc
               //et tous les sous blocs

   {  //----------ouv B2
      int c;
      x=0;
      c=rand()%256;
      pasx=rand()%5;
   }  // ---------ferm B2
   x=640;

   {  // ---------ouv B3
      //c=10; // provoque erreur, c non visible dans ce bloc
      x/=2;
      pasx=15;

   }  // ---------ferm B3
   x+=pasx;
   printf("x vaut : %d\n",x);  // affichage ?

   return 0;

}  //-------------------------ferm bloc main
*/
//--------------------------------------------------
// Les opérateurs de comparaison 1
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a=10, b=5;
	printf("%d ",a < b);
	printf("%d ",a+b > 12);

	a = 5;
	printf("%d ",a >= b);
	printf("%d ",a == b);

	b = 4;
	printf("%d ",a <= b);
	printf("%d ",a == b);
	printf("%d ",a+3 != b*2);
	return 0;
}
*/
//--------------------------------------------------
// Les opérateurs de comparaison 2
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a,b;
    printf("%d ",56 < rand() );  //  1 si vrai, 0 si faux
    // attention, parenthèses nécessaires autour de b=rand()
    printf("%d ",a=rand() + (b = rand()) >= 1000 );
								// 1 si vrai, 0 si faux
    printf("%d ",a*b == 45);	// 1 si oui, 0 si non
	return 0;
}
*/
//--------------------------------------------------
// L'opérateur unaire NON !
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a=10, b=20;
	printf("%d ", !(a < b)); // imprime 0
	printf("%d ", !(a > b)); // imprime 1
	return 0;
}
*/
//--------------------------------------------------
// Priorités des opérateurs NON et comparaison
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a=10, b=0, c=2;
	printf("a+b < c*10 vaut %d\n", a+b < c*10);
	printf("c*10 >= 66 vaut %d\n", c*10 >= 66);
	printf("a+b < c*10 >= 66 == 80 vaut %d\n",a+b < c*10 >= 66 == 80);
	return 0;
}
*/

/****************************************************
*                                                   *
*       2. Sauts Conditionnels                      *
*                                                   *
*****************************************************/

// Le couple d'instructions if-else
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int Paul, Jean;

	srand(time(NULL));
	Paul = 1 + rand() % 6;
	Jean = 1 + rand() % 6;

	if (Paul > Jean) {
	  printf("%s %d gagne sur %s %d\n","Paul",Paul,"Jean",Jean);
	  printf("%s fait la vaisselle\n", "Jean");
	}else{
	   printf("%s %d gagne sur %s %d\n","Jean",Jean,"Paul",Paul);
	   printf("%s fait la vaisselle\n", "Paul");
	}

	system("PAUSE");
	return 0;
}
*/
//--------------------------------------------------
// Expérimentation : les sauts conditionnels (les trois if) 


/****************************************************
 SAUTS CONDITIONNELS DE BLOCS / 3 possibilités

  Forme 1 :

      Si (condition vraie) Alors
         faire bloc d'instructions
      FinSi

   COMMENT DEFINIR UNE CONDITION ?
   -> les opérateurs de comparaison : >, >=, <, <=, ==, !=
   -> les expressions sont évaluées VRAIE (valeur 1) ou FAUX 	(valeur 0)

   REMARQUE :
   En C
   - toute expression qui vaut 0 peut être considérée comme fausse
   - et toute expression qui vaut autre chose que 0 peut être
     considérée comme vraie

****************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
int d1,d2;
   srand(time(NULL));
   // tirage aux dés
   d1=1+rand()%6;
   d2=1+rand()%6;
   if (d1>d2)
      printf("le de 1 gagne : d1=%d, d2=%d\n",d1,d2);
   if (d2>d1)
      printf("le de 2 gagne : d1=%d, d2=%d\n",d1,d2);

   // pour voir, affichage de la valeur du test
   printf("d1>d2 vaut %d,d1<d2 vaut %d\n",d1>d2, d1<d2);

   //REMARQUE :
   //si une seule instruction, les { } ne sont pas nécessaires

   return 0;
}
*/
/****************************************************
SAUTS CONDITIONNELS DE BLOCS

   Forme 2 :

      Si (condition vraie) Alors
         faire bloc d'instructions 1
      Sinon
         faire bloc d'instructions 2
      FinSi

****************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
int d1,d2;
   srand(time(NULL));
   // tirage aux dés
   d1=1+rand()%6;
   d2=1+rand()%6;
   if (d1>d2)
      printf("le de 1 gagne : d1=%d, d2=%d\n",d1,d2);
   else
      printf("le de 2 gagne : d1=%d, d2=%d\n",d1,d2);

   return 0;
}
*/
/****************************************************
SAUTS CONDITIONNELS DE BLOCS

   Forme 3 :

      Si (condition 1 vraie) Alors
         faire bloc d'instructions 1
      sinon Si (condition 2 vraie) Alors
         faire bloc d'instructions 2
      sinon Si (condition n vraie) Alors
         faire bloc d'instructions n
      Sinon
         faire bloc d'instructions par défaut
      FinSi

****************************************************/
/*
// TEST 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
int d1,d2;
   srand(time(NULL));
   // tirage aux dés
   d1=1+rand()%6;
   d2=1+rand()%6;
   if (d1==d2)
      printf("de 1 et de 2 execo : d1=%d, d2=%d\n",d1,d2);
   else if (d1>d2)
      printf("le de 1 gagne : d1=%d, d2=%d\n",d1,d2);
   else
      printf("le de 2 gagne : d1=%d, d2=%d\n",d1,d2);

   return 0;
}
*/
//--------------------------------------------------
/*
// TEST 2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
int d;
   srand(time(NULL));
   // tirage aux dés
   d=1+rand()%6;

   if (d==1)
      printf("d vaut 1 : %d\n",d);
   else if (d==2)
      printf("d vaut 2 : %d\n",d);
   else if (d==3)
      printf("d vaut 3 : %d\n",d);
   else if (d==4)
      printf("d vaut 4 : %d\n",d);
   else
      printf("d vaut 5 ou 6 : %d\n",d);


   return 0;
}
*/
/****************************************************
*                                                   *
*       3.   Branchements                           *
*                                                   *
*****************************************************/
//Branchement sélectif : switch, case et break
/*
//Branchement sélectif : switch, case et break
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int choix = 0;

	// menu utilisateur
	printf("a : Afficher la liste des clients\n"
		"b : Afficher les donnees d'un client\n"
		"c : Saisir les donnees d'un client\n"
		"q : quitter\n");
	// récupération du choix de l'utilisateur
	scanf_s("%c", &choix, 1);
	// aiguillage sur les instructions correspondant au choix
	switch (choix) {
		case 'a':
			printf("affichage de la liste des clients\n");
			//mettre ici le code pour l'affichage de tous les clients
			break;

		case 'b':
			printf("Afficher les donnees d'un client\n");
			printf("Nom du client ? :\n");
			//mettre ici le code pour l'affichage des infos du client
			break;

		case 'c':
			printf("Entrer les donnees du client : \n");
			//mettre ici le code pour la saisie des infos du client
			break;

		case 'q':   // instruction de sortie
					 // (il faut une boucle)
			break;
		default:   printf("saisie de commande incorrecte\n");
	}

	system("PAUSE");
	return 0;
}
*/
/****************************************************
*													*
* Expérimentation : Branchement sélectif switch		*
*													*
/****************************************************/
/*AIGUILLAGE

   La Forme if – else if - else peut être remplacée par :

   Selon (valeur)
      cas 1 : faire bloc d'instructions 1
      cas 2 : faire bloc d'instructions 2
      cas n : faire bloc d'instructions n
      defaut : faire bloc d'instructions par défaut
   FinSelon

****************************************************/
/*
// par exemple ce programme :
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
int d;
   srand(time(NULL));
   // tirage aux dés
   d=1+rand()%6;

   if (d==1)
      printf("d vaut 1 : %d\n",d);
   else if (d==2)
      printf("d vaut 2 : %d\n",d);
   else if (d==3)
      printf("d vaut 3 : %d\n",d);
   else if (d==4)
      printf("d vaut 4 : %d\n",d);
   else
      printf("d vaut 5 ou 6 : %d\n",d);
   return 0;
}
*/
// peut s'écrire :
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
int d;
   srand(time(NULL));
   // tirage aux dés
   d=1+rand()%6;

   switch(d){
      case 1  : printf("d vaut 1 : %d\n",d);    // break;
      case 2  : printf("d vaut 2 : %d\n",d);    // break;
      case 3  : printf("d vaut 3 : %d\n",d);    // break;
      case 4  : printf("d vaut 4 : %d\n",d);    // break;
      default :printf("d vaut 5 ou 6 : %d\n",d);
   }
// REMARQUE : l'instruction break; provoque la sortie immédiate du
// bloc switch, sans break les cas suivants sont aussi exécutés

   return 0;
}
*/

/****************************************************
*                                                   *
*       4.   Les tests multi-conditions (ET/OU)     *
*                                                   *
*****************************************************/
//ET avec deux expressions membres
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char papier = 0, declarer = 0;

	printf("Vous avez vos papiers ? (o/n)\n");
	scanf_s("%c", &papier, 1);
	// lorsqu'il y a plusieurs appels successifs de scanf_s() il s'avère
	// nécessaire de réinitialiser le buffer d'entrée (stdin) avec
	// la fonction rewind()
	rewind(stdin);

	printf("Quelque chose a declarer ? (o/n)\n");
	scanf_s("%c", &declarer, 1);

	if (papier == 'o' && declarer == 'n')
		printf("C'est bon, vous pouvez passer\n");
	else
		printf("Attendez la s'il vous plait\n");

	system("PAUSE");
	return 0;
}

*/
//--------------------------------------------------
//ET avec plus de deux expressions membres
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char farine = 0, sel = 0, oeufs = 0, lait = 0, gruyere = 0;

	printf("Dans le frigo y a-t-il des oeufs (o/n), du lait (o/n),"
		" du gruyere (o/n)\n ?");
	scanf_s("%c%c%c", &oeufs,1, &lait,1, &gruyere,1);
	rewind(stdin);

	printf("Dans le placard y a-t-il de la farine (o/n)"
		"et du sel (o/n) ?\n");
	scanf_s("%c%c", &farine,1, &sel,1);

	if (oeufs == 'o' && lait == 'o' && gruyere == 'o' &&
		farine == 'o' && sel == 'o')
		printf("Top, je fais des crepes !\n");
	else
		printf("No crepe\n");

	system("PAUSE");
	return 0;
}

*/
//--------------------------------------------------
//Disjonction OU, opérateur
//OU avec deux expressions membres
/*
#include <stdio.h>
#include <stdlib.h>

int main()   // A LA DOUANE version OU
{
	char papier, declarer;

	printf("vous avez vos papiers ? (o/n)\n");
	scanf_s("%c", &papier, 1);
	rewind(stdin);

	printf("quelque chose a declarer ?(o/n)\n");
	scanf_s("%c", &declarer, 1);
	rewind(stdin);

	if (papier == 'n' || declarer == 'o')
		printf("attendez la SVP\n");
	else
		printf("c'est bon vous pouvez passer\n");

	system("PAUSE");
	return 0;
}

*/
//--------------------------------------------------
//OU avec plus de deux expressions membres
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char pain = 0, beurre = 0, jambon = 0, cornichon = 0, salade = 0;

	printf("Dans le frigo y a-t-il :\n"
		"du beurre (o/n), des cornichons (o/n), "
		"de la salade (o/n)\n"
		"ai-je du pain frais (o/n)\n ?");
	scanf_s("%c%c%c%c%c", &pain,1, &beurre,1, &jambon,1,
		&cornichon,1, &salade,1);

	if (pain == 'n' || beurre == 'n' || jambon == 'n' ||
		cornichon == 'n' || salade == 'n')
		printf("Pas de sandwich au jambon !\n");
	else
		printf("Miam, un bon sandwich\n");

	system("PAUSE");
	return 0;
}

*/
/****************************************************
*                                                   *
*       5.   Boucles                                *
*                                                   *
*****************************************************/
//Boucle TANT QUE :  le while
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int a;
	printf("entrer une valeur entre 50 et 100\n");
	scanf_s("%d",&a);
	while( a < 50 ||  a>100 ){
	   printf("le nombre doit etre compris entre 50 et 100\n");
	   scanf_s("%d",&a);
	   rewind(stdin);
	}
	printf("valeur entree : %d\n",a);

	system("PAUSE");
	return 0;
}

*/
//--------------------------------------------------
//Boucle FAIRE {…}TANT QUE : le do-while
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a;
    printf("entrer une valeur entre 50 et 100\n");
	do{
	   scanf_s("%d",&a);
	   rewind(stdin);
	   if (a<50 || a>100 )
	      printf("le  nombre doit être compris entre 50 et 100\n");
	}while( a<50 || a>100);
	printf("valeur entree : %d\n",a);

	system("PAUSE");
	return 0;
}
*/
/****************************************************
*                                                   *
*       6. Utilisations typiques de boucles         *
*                                                   *
*****************************************************/
//Créer un menu utilisateur
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int choix, res;
	do{												// 1
	    printf ( "1 : Affiche bonjour\n"			// 2
                 "2 : Affiche il fait beau\n"
                 "3 : Entrer un nombre entier\n"
                 "0 : Quitter\n");

	    scanf_s("%d",&choix);					// 3
	    rewind(stdin);

        switch(choix){						// 4
            case 0 :
                break;
            case 1 :
                printf("bonjour\n");
                break;

            case 2 :
                printf("il fait beau\n");
                break;

            case 3 :
                printf("c'est quoi le nombre ? \n");
                scanf("%d",&res);
                rewind(stdin);
                printf("le nombre est :  %d\n",res);
                break;

            default :
                printf("Pas de commande %d\n",choix);
                break;
	   }

	}while(choix !=0);						// 5

	return 0;
}
*/
//--------------------------------------------------
//Boucle d'événements dans un jeu vidéo
//Boucle événements simple
/*
#include <stdio.h>
#include <conio.h> // ne pas oublier d'inclure la cette librairie conio

int main()
{
	int res=0;
	while (res!=’q’){
	   if (_kbhit()){
		  res=_getch();
		  printf("touche %c pressee, val ascii : %d\n",res,res);
	   }
	   putchar('0');
	}
	return 0;
}

*/
//--------------------------------------------------
//Contrôler le temps d'exécution
/*
#include <stdio.h>
#include <conio.h>
#include <time.h>
int main()
{
int res, top=0;

	while (res!='q'){
	   if (_kbhit()){
		res=_getch();
		printf("touche %c pressee, val ascii : %d\n",res,res);
	   }
	   if(clock()>top+30){  // contrôler le temps
	      top=clock();
         putchar('0');
	   }
	}
	return 0;
}
*/
//--------------------------------------------------
//Commencer la création d'un jeu en mode console
/*
#include <stdio.h>    // pour utilisation fonctions affichage
#include <stdlib.h>   // pour fonction srand() et rand()
#include <time.h>     // pour initialisation srand() avec time()
#include <conio.h>    // pour fonctions kbhit()et getch()
#include <windows.h>  // pour écriture fonctions gotoxy ci-dessous

void gotoxy(int x, int y)
{
  COORD c;

  c.X = x;
  c.Y = y;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
int fin=0, res, x, y;					//1
const int TX=20, TY=15;

	srand(time(NULL));
	x=rand()%TX;
	y=rand()%TY;
	gotoxy(x,y);
	putchar('X');

	while (! fin){ // équivalent à fin==0		//2

		if( _kbhit()){							//3

			gotoxy(x,y);						//4
			putchar(' ');

			res=_getch();						//5
			switch(res){
				case 72 :	y--;	break;	// haut
				case 77 :	x++;	break;	// droite
				case 80 :	y++;	break;	// bas
				case 75 :	x--;	break;	// gauche
				case 224 : 	break;	// évacuer la touche combinée
				default : fin=1; break; // autre touche :
										//met fin au prg
			}
			if (x<0)							//6
			   x=TX;
			if (x>TX)
				x=0;
			if (y<0)
				y=TY;
			if (y>TY)
				y=0;

			gotoxy(x,y);					//7
			putchar('X');
	    }
	}
	return 0;
}
*/
/****************************************************
*                                                   *
*       7. Fonctions                                *
*                                                   *
*****************************************************/
// Exemple de fonction sans retour et sans paramètre
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Bonjour()
{
	switch (rand() % 6) {
	case 0: printf("Noirs dans la neige et dans la brume,\n");
		break;
	case 1: printf("Au grand soupirail qui s'allume,\n");
		break;
	case 2: printf("Leurs culs en rond,\n");
		break;
	case 3: printf("A genoux, cinq petits, -misères!-\n");
		break;
	case 4: printf("Regardent le boulanger faire\n");
		break;
	case 5: printf("Le lourd pain rond...\n");
		break;
	}
}


int main()
{
	srand((unsigned)time(NULL));

	// appel de la fonction
	Bonjour();

	system("PAUSE");
	return 0;
}
*/
//--------------------------------------------------
//	Déclaration et visibilité d'une fonction
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// déclaration de la fonction au dessus du main
void Bonjour(void);

int main()
{
	srand(time(NULL));

	// appel de la fonction là où on en a besoin
	Bonjour();

	system("PAUSE");
	return 0;
}

// Définition de la fonction après le main
void Bonjour()
{
	switch (rand() % 6) {
	case 0: printf("Noirs dans la neige et dans la brume,\n");
		break;
	case 1: printf("Au grand soupirail qui s'allume,\n");
		break;
	case 2: printf("Leurs culs en rond,\n");
		break;
	case 3: printf("A genoux, cinq petits, -misères!-\n");
		break;
	case 4: printf("Regardent le boulanger faire\n");
		break;
	case 5: printf("Le lourd pain rond...\n");
		break;
	}
}
*/
//--------------------------------------------------
//Exemples de fonction avec paramètres
// Déplacer le curseur en écriture de la fenêtre console
/*
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void gotoxy(int x, int y)
{
	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}

int main()
{
	// déplace le curseur en écriture à 20, 10
	gotoxy(20, 10);

	system("PAUSE");
	return 0;
}
*/
//--------------------------------------------------
//Exemples de fonction avec paramètres
//Changer le couleur des caractères
/*
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

void textcolor(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}

int main()
{
	// couleur vert clair
	textcolor(10);

	system("PAUSE");
	return 0;
}
*/
//--------------------------------------------------
//Exemples de fonction avec paramètres
//Afficher une lettre à une position et d'une couleur donnée dans la console
//Tracer une ligne horizontale
/*
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

// avec paramètre et sans retour
// déclarations
void gotoxy(int x, int y);
void textcolor(int color);
void poselettre(int x, int y, int lettre, int color);
void ligne_h(int x1, int y, int x2, int lettre, int color);

int main()
{
	srand(time(NULL));

	// appel fonction
	ligne_h(rand() % 40, rand() % 20, rand() % 40, ' ', 12*16);

	gotoxy(0, 20);
	textcolor(15);

	system("PAUSE");
	return 0;
}
// Définition
void gotoxy(int x, int y)
{
	COORD c;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}
void textcolor(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}
void poselettre(int x, int y, int lettre, int color)
{
	gotoxy(x, y);
	textcolor(color);
	putchar(lettre);
}
void ligne_h(int x1, int y, int x2, int lettre, int color)
{
	// inverser si x1 après x2
	if (x1 > x2) {
		x1 ^= x2;
		x2 ^= x1;
		x1 ^= x2;
	}
	// tracer la ligne
	for (x1; x1 <= x2; x1++)
		poselettre(x1, y, lettre, color);
}
*/
//--------------------------------------------------
//Exemples de fonction avec retour
// Retourner un nombre aléatoire entre 0 et 1
// Retourner le résultat d'un jeté de deux dés à six faces
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float frand();
int LanceDes();

int main()
{
	int val = 0, i;

	srand((unsigned)time(NULL));

	printf( "valeur retournee : %f\n", frand());
	printf( "lance de : %d\n", LanceDes() );

	for (i = 0; i < 2; i++)
		val += LanceDes();
	printf( "Resultat deux lances : %d\n", val );

	system("PAUSE");
	return 0;
}

float frand()
{
	return rand() / (float)RAND_MAX;
}
int LanceDes()
{
	int d1 = 0, d2 = 0, res = 0;
	while (d1 == d2) {
		d1 = 1 + rand() % 6;
		d2 = 1 + rand() % 6;
		res += (d1 + d2);
	}
	return res;
}
*/
//--------------------------------------------------
//Exemple de fonction avec retour et avec paramètres
//Conversion chiffres romains 
/*
#include <stdio.h>
#include <stdlib.h>

void TraductionRomain(int num);
int conversion(int num, int lettre, int val);

int main()
{
	int num;
	printf( "entrez un nombre :\n");
	scanf_s("%d", &num);

	TraductionRomain(num);

	system("PAUSE");
	return 0;
}
//I: 1, V : 5, X : 10, L : 50, C : 100, D : 500, M : 1000
void TraductionRomain(int num)
{
	num = conversion(num, 'M', 1000);
	num = conversion(num, 'D', 500);
	num = conversion(num, 'C', 100);
	num = conversion(num, 'L', 50);
	num = conversion(num, 'X', 10);
	num = conversion(num, 'V', 5);
	num = conversion(num, 'I', 1);
	putchar('\n');
}

int conversion(int num, int lettre, int val)
{
	while (num >= val) {
		putchar(lettre);
		num -= val;

		if (num == 9) {
			putchar('I');
			putchar('X');
			num = 0;
		}
		if (num == 4) {
			putchar('I');
			putchar('V');
			num = 0;
		}
	}
}
*/
//--------------------------------------------------
//Transformer les entrées en sorties
//Précision sur le passage par valeur
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a=0, b=0;

   modif(a,b);
   printf("a=%d, b=%d\n",a,b);

   return 0;
}
*/
//--------------------------------------------------
//Transformer les entrées en sorties
//Passage par référence
/*
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

void Empoisonner(int* personnage, int* poison)
{
	*personnage -= *poison;
	if (*poison > 0)
		(*poison)--;
	else
		*poison = rand() % 20;
}


int main()
{
	srand((unsigned)time(NULL));

	int BlancheNeige = 100;
	int poison = rand() % 20;

	while (1) {

		if (_getch() == 32) { // si appuie sur espace
			printf("poison %d, ", poison);
			Empoisonner(&BlancheNeige, &poison);
			printf("Blanche Neige %d\n", BlancheNeige);
		}
		else
			break;
	}
	return 0;
}

*/
//--------------------------------------------------
//Fonctions avec liste variable de paramètres
//Liste variable de paramètres de même type
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int somme(int nb,...)// 1 entête de la fonction avec liste
{
va_list lparam;             // 2 déclarer une liste
int res=0,n;
    va_start(lparam,nb);    // 3 initialiser la liste

    for(n=0; n<nb; n++)     // 4
        res+= va_arg(lparam,int);// 5 récupération de la valeur
                                 // de chaque paramètre

    va_end(lparam);     // 6 libérer la mémoire de la liste 					 // constituée
    return res;

}

int main(int argc, char*argv[])
{
    printf("%d\n",somme(1,1));           // affiche 1
    printf("%d\n",somme(3,1,2,3));       // affiche 6
    printf("%d\n",somme(5,1,2,3,4,5));  // affiche 15
	return 0;
}
*/
//--------------------------------------------------
//Liste variable de paramètres de types différents
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

enum{t_int,t_double, t_string,t_end};  // 1 une énumération

void test(int type,...)		   // 2
{
va_list lparam;				   // 3
int fin=0;
int i;
double f;
char*s;

    va_start(lparam,type);		   // 4

    while(!fin){
       switch(type){			   // 5
        case t_int :
           i=va_arg(lparam,int);
           printf("int %d\n",i);
           break;

        case t_double :
           f=va_arg(lparam,double);
           printf("float %f\n",f);
           break;

        case t_string :
           s=va_arg(lparam,char*);
           printf("int %s\n",s);
           break;

        case t_end :
           fin=1;
           break;
       }
       type=va_arg(lparam,int);	   // 6
    }
    va_end(lparam); 			   //7
}

int main()
{
    test(	t_int, 10,		      	   // 8
		t_int,20,
		t_string, "bonjour",
		t_double, 3.5,
		t_end);

    return 0;
}
*/
//--------------------------------------------------
//Transformer printf()
/*
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>    // pour écriture des fonctions gotoxy()
// et textcolor()

// déclaration des fonctions
void G_printf(int x, int y, int color, const char* format, ...);
void gotoxy(int x, int y);
void textcolor(int color);

int main()
{
	G_printf(5, 5, 12, "num : %d", 2341);    // 0
	return 0;
}
void G_printf(int x, int y, int color, const char* format, ...)    //1
{
	va_list lparam;
	char stock[10000];              // 2

	va_start(lparam, format);
	//vsprintf(stock,format,lparam);   // 3 (version obsolète)
	vsprintf_s(stock, 10000, format, lparam); // (version C11)
	va_end(lparam);

	// afficher à la position et de la bonne couleur      // 4
	gotoxy(x, y);
	textcolor(color);
	printf("%s", stock);
}
void gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}
void textcolor(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}
*/
//-------------------------------------------------
// Fonctions récursives
/*
#include <stdio.h>
#include <stdlib.h>
void affiche(int nb)
{
	if (nb>0)
		affiche(nb - 1);
	printf("%d-", nb);
}
int main()
{
	affiche(10);

	system("PAUSE");
	return 0;
}
*/
//-------------------------------------------------
// Exercice 16, code du programme
/*
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
/*****************************************************
*****************************************************
void gotoxy(int x, int y);
void textcolor(int color);
/*****************************************************
*****************************************************
int main()
{
	const int TX = 40;
	const int TY = 20;
	int x, y, res, i;
	int fin = 0;
	srand(time(NULL));
	// commentaire 1
	for (i = 0; i <= TX; i++){
		gotoxy(i, 0);
		textcolor(12 * 16);
		putchar(' ');
	}
	// com 2
	for (i = 0; i <= TX; i++) {
		gotoxy(i, TY);
		textcolor(12 * 16);
		putchar(' ');
	}
	// com 3
	for (i = 0; i <= TY; i++){
		gotoxy(0, i);
		textcolor(12 * 16);
		putchar(' ');
	}
	// com 4
	for (i = 0; i <= TY; i++){
		gotoxy(TX, i);
		textcolor(12 * 16);
		putchar(' ');
	}
	// com 5
	x = rand() % TX;
	y = rand() % TY;
	// com 6
	gotoxy(x, y);
	textcolor(10);
	putchar('P');
	// com 7
	while (!fin){
		// com 8
		if (_kbhit()){
			// com 9
			gotoxy(x, y);
			textcolor(0);
			putchar('P');
			// com 10
			res = _getch();
			switch (res){
			case 72: y--; break; // 11
			case 77: x++; break; // 12
			case 80: y++; break; // 13
			case 75: x--; break; // 14
			case 224: break;
			default: fin = 1; // 15
			}
			// com 16
			if (x < 1)
				x = TX - 1;
			if (x >= TX)
				x = 1;
			if (y < 1)
				y = TY - 1;
			if (y >= TY)
				y = 1;
			// com 17
			gotoxy(x, y);
			textcolor(10);
			putchar('P');
		}
	}
	gotoxy(0, TY + 2);
	return 0;
}
/*****************************************************
*****************************************************
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/*****************************************************
*****************************************************
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
*/


/****************************************************
*                                                   *
*       8. Gestion des variables                    *
*                                                   *
*****************************************************/
// Profondeur de la déclaration
/*
#include<stdlib.h> // niveau 0 en global, hors bloc
int x = 0;
void test(int a);
int main()
{ // bloc niveau 1
	int i = 0;
	{ // bloc niveau 2
		int y = 9;
		{ // bloc niveau 3
			int w = rand();
			test(w);
		}
	}
	test(i);
}
void test(int a)
{ // autre bloc niveau 1
	int b;
	// instructions de la fonction
}
*/
//--------------------------------------------
// Visibilité des variables
//Masquage d'une variable
/*
#include <stdio.h>
int x=1000;
int test(int x);

int main()
{
int x;
	x=1;
	printf ("%d, ",x);
	{
	int x;
	    x=2;
	    printf ("%d, ",x);
	    {
	    int x;
	        x=3;
           printf ("%d, ",x);
	    }
	    {
	    int x;
	        x=33;
           printf ("%d, ",x);
	    }
	    printf ("%d, ",x);
	}
	x++;
 	printf ("%d, ",x);
	x=test(x);
	printf("%d.",x);
	return 0;
}

int test(int x)
{
	x+=50;
	return x;
}
*/
//--------------------------------------------------
//Durée de vie des variables
//Variables static
/*
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void  test( )
{
static int v=0;
	printf("toto=%d\n",v);
	v++;
}

int main()
{
int fin=0;
	while (fin!='q'){
       if (kbhit()){
	        fin=getch();
	        test();
	    }
	}
	return 0;
}
*/

/****************************************************
*                                                   *
* Expérimentations :  circuit de voiture			*
*                                                   *
*****************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
// taille de la zone de jeu
#define TX 80
#define TY 24
// position de départ de la zone de jeu
#define STARTX 2
#define STARTY 2
// Les quatre directions
enum{ NORD, EST, SUD, OUEST };
// l'ensemble des variables pour la composition
// du circuit
int D1, P1, D2, P2, D3, P3, D4, P4, D5, P5, D6, P6, NBTRAIT, NBTOUR;
// ensemble des variables pour avoir une voiture
// (position, vitesse, direction, nombre de pas,
// trait courant, compte-tours)
int X, Y, VIT, DIR, PAS, IDTRAIT, TOUR;
// les déclarations des fonctions
void	create_circuit1(void);
void	select_trait(void);
void	avancer(int l, int color1, int color2);
void	afficher(int x, int y, int l, int color);
void	gotoxy(int x, int y);
void	textcolor(int color);
/********************************************************
ACTION
********************************************************
int main()
{
	int start = 0; // pour contrôle du temps
	srand(time(NULL));
	// création circuit et initialisation voiture
	create_circuit1();
	while (TOUR<NBTOUR){
		// contrôle vitesse voiture
		if (clock()>start + VIT){
			start = clock();
			//nouveau trait ?
			if (PAS == 0)
				select_trait();
			// avancer, lettre v pour voiture,
			// effacement en noir, couleur voiture rouge
			avancer('v', 0, 10);
		}
	}
	gotoxy(0, TY);
	system("PAUSE");
	return 0;
}
/********************************************************
CREATION DU CIRCUIT
Un seul circuit. C'est un carré de 10 sur 10, deux tours
prévus. Initialisation des variables circuit en conséquence.
Initialisation de la voiture
********************************************************
void create_circuit1()
{
	// définition du circuit
	D1 = EST; // trait 1
	P1 = 10;
	D2 = SUD;
	P2 = 10;
	D3 = OUEST;
	P3 = 10;
	D4 = NORD;
	P4 = 10;
	NBTRAIT = 4;
	NBTOUR = 2;
	// la voiture
	X = STARTX;
	Y = STARTY;
	PAS = 0; // au départ rien
	IDTRAIT = 0;
	TOUR = 0;
	VIT = 0;
}
/********************************************************
AVANCER
********************************************************
//Sélection du trait à parcourir
void select_trait()
{
	// contrôler si un tour a été effectué et affichage
	// du nombre de tours réalisés
	if (IDTRAIT == NBTRAIT){
		TOUR++;
		IDTRAIT = 0;
		gotoxy(TX / 2, TY / 2);
		textcolor(12); // couleur vert
		printf("TOUR : %d", TOUR);
	}
	// changement de la vitesse de la voiture (chaque trait
	// est parcouru à une vitesse différente
	VIT = 150 + rand() % 150;
	// sélection du trait
	switch (IDTRAIT){
	case 0: // trait 1
		DIR = D1;
		PAS = P1;
		break;
	case 1: // trait 2
		DIR = D2;
		PAS = P2;
		break;
	case 2: // etc.
		DIR = D3;
		PAS = P3;
		break;
	case 3:
		DIR = D4;
		PAS = P4;
		break;
	case 4:
		DIR = D5;
		PAS = P5;
		break;
	case 5:
		DIR = D6;
		PAS = P6;
		break;
	}
	// préparer pour le trait suivant
	IDTRAIT++;
}

// Parcourir le trait courant
void avancer(int l, int color1, int color2)
{
	if (PAS>0){
		// supprimer un pas
		PAS--;
		// effacer
		afficher(X, Y, l, color1);
		// déplacer selon direction
		switch (DIR){
		case NORD: Y--; break;
		case EST: X++; break;
		case SUD: Y++; break;
		case OUEST: X--; break;
		}
		// afficher à la nouvelle position
		afficher(X, Y, l, color2);
	}
}

//afficher une position
void afficher(int x, int y, int l, int color)
{
	gotoxy(x, y);
	textcolor(color);
	putchar(l);
}
/********************************************************
OUTILS
********************************************************
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/********************************************************
********************************************************/


