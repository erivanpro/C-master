/************************************************************
*                                                           *
*       CHAPITRE 3 : LES OPERATIONS							*
*                                                           *
*************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de pr�f�rence vide sous visual studio)
    - copier toute la page dans le fichier C du nouveau projet (�craser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte imm�diatement ajouter
      getchar(); avant le return 0; de fin de main()
      (ou voir Chap 1 / Conserver la fen�tre console ouverte)
    - remettre les commentaires pour tester un autre programme
**************************************************************/
// La notion d'expression
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a, b=20;
	printf("%d--",a=10);	// affectation
	printf("%d--",a=a*b);   	// multiplication
	printf("%d\n",a%b);		// modulo ( reste de la division)
   return 0;
}
*/
//-----------------------------------------------
// Op�rations arithm�tiques
/*
//Les op�rateurs +, -, *, /, %

#include <stdio.h>
#include <stdlib.h>

int main()
{
int a=10,b=20,c=0;				// 1
	c=a+b;						// 2
	a=b/c;						// 3
	b=a*c;						// 4
	printf("a=%d, b=%d, c=%d\n",a,b,c);	// 5
	printf("res=%d\n",c%4);			// 6
	printf("c=%d\n",c);				// 7
	return 0;
}
*/
//-----------------------------------------------
// Les affectations combin�es
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a=7,b=232,c=4;					// 1

		c+=a;						// 2
		b-=c;						// 3
		a%=10;						// 4
		printf("a=%d, b=%d, c=%d\n",a,b,c);	// 5
		c+=(b-a);					// 6
		printf("c=%d\n",c);				// 7
		return 0;
}
*/
//-----------------------------------------------
// Op�rations entre type diff�rents, op�rateur de "cast"
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int entier = 10;
float flottant = 34.9;
int eRes;
float fRes;
	eRes=entier+flottant;
	fRes=entier+flottant;
	printf("eRes : %d, fRes : %f\n", eRes, fRes);		// 1

	eRes=entier / (entier+5);
	fRes=entier / (entier+5);
	printf("eRes : %d, fRes : %f\n", eRes, fRes);  	// 2

	eRes=flottant / entier;
	fRes=flottant / entier;
	printf("eRes : %d, fRes : %f\n", eRes, fRes);  	// 3
 	return 0;
}
*/
//-----------------------------------------------
// Priorit�s entre op�rateurs
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int x,y,z;

	x= -3+4*5-6;
	printf("%d\n",x);

	x= 3+4%5-6;
	printf("%d\n",x);

	x=-3*4%-6/5;
	printf("%d\n",x);

	x= (7+6)%5/2;
	printf("%d\n",x);

	x=2;
	x*=3+2;
	printf("%d\n",x);

	x*=y=z=4;
	printf("%d\n",x);

	return 0;
}
*/
//-----------------------------------------------
// La fonction rand()
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int test;

	test=rand();
	printf("etape 1 : %d\n",test);
	test=rand();
	printf("etape 2 : %d\n",test);
	test=rand();
	printf("etape 3 : %d\n",test);
	test=rand();
	printf("etape 5 : %d\n",test);
	test=rand();
	printf("etape 1 : %d\n",test);
	return 0;
}
*/
//-----------------------------------------------
// La fonction srand() 1
/*
#include <stdio.h>
#include <stdlib.h>
int main()
{
int val;

	srand(689);			// initialisation du d�part

	val = rand();
  	printf("val=%d\n",val);	// tirage du premier nombre
	return 0;
}
*/
//-----------------------------------------------
// La fonction srand() 2
/*
#include <stdio.h>	// pour utiliser la fonction printf()
#include <stdlib.h>	// pour utiliser les fonctions rand() et 				
					// srand()
#include <time.h>	// pour utiliser la fonction time()

int main()
{
int depart=time(NULL);	// initialisation d�s la d�claration de la variable
	srand(depart);

	printf("premi�re valeur : %d\n",rand());
	printf("deuxieme valeur : %d\n",rand());
	printf("troisieme valeur : %d\n",rand());
	return 0;
}
*/
//-----------------------------------------------
// Valeurs al�atoires dans des fourchettes
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
int test;
	srand(time(NULL));

	test=rand();
   test%=10;  // �quivalent � test = test%10;;
	printf("test=%d\n",test);

	// il est possible d'�crire directement
	test=rand()%10;
	printf("test=%d\n",test);
	return 0;
}
*/
//-----------------------------------------------
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
float test;
	srand(time(NULL));

	test=(float) rand() / RAND_MAX;   // entre 0 et 1
	printf("test1=%f\n",test);

	test=((float) rand() / RAND_MAX)*50; // entre 0 et 50
	printf("test2=%f\n",test);

	test=20+ ((float) rand() / RAND_MAX)*30; // entre 20 et 50
	printf("test3=%f\n",test);

	return 0;
}
*/
//-----------------------------------------------
//  Op�rations bits � bits
//  OU exclusif - op�rateur ^
/*
#include <stdio.h>
#include <stdlib.h>

int main()
{
int a=345, b=678;

	printf("a: %d, b: %d\n",a,b);
	a^=b;
	b^=a;
	a^=b;
	printf("a: %d, b: %d\n",a,b);
	return 0;
}
*/
//-----------------------------------------------
// Exp�rimentation : Op�rations arithm�tiques, valeurs al�atoires
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
int a=90, b=10;

   // les op�rateurs arithm�tiques sont +, -, *, /, %

   //----------------
   // a+b est une expression
   // la valeur num�rique d'une expression est le r�sultat
   // de l'op�ration (arithm�tique ou non)
   printf("%d\n",a+b);

   //----------------
   // priorit� des op�rateurs arithm�tiques :
   printf("%d\n",a/2+b*8%3); // (a/2)+((b*8)%3)

   //----------------
   // type d'une expression arithm�tique :
   // si les op�randes sont de types diff�rents, l'expression
   // est du type de l'op�rande le plus fort
char c=12, res2;
float f=4.5, res1;
   printf("%f\n",c+f);

   //----------------
   // r�cup�rer un r�sultat : l'affectation est faite dans le type
   // de la variable qui re�oit,  troncature �ventuelle
   res1=c+f;
   printf("%f\n",res1);

   res2=c+f;
   printf("%d\n",res2);

   //----------------
   // L'op�ration est faite dans le type le plus fort :
int i1=10, i2=5;

   i1=i2/i1;
   printf("res i1 : %d\n",i1);

float res;
   i1=10;  // (attention div par 0)
   res=i2/i1;
   printf("res float : %f\n",res);

   //----------------
   // forcer une op�ration � se faire dans un autre type que celui 	// des op�randes : op�rateur de cast
   res= (float)i2/i1;
   printf("res float : %f\n",res);

   //----------------
   //possibilit� de combiner affectation et op�ration arithm�tique
   // +=, -=, *=, /=, %=

   res+=10; // �quivalent � res= res+10
   printf("res float : %f\n",res);

   //----------------
   // op�rateurs d'incr�mentation/d�cr�mentation
int i=0;
   printf("%d\n",i++); // post incr�mentation
   printf("%d\n",++i); // pr� incr�mentation

   //----------------
   // obtenir une valeur al�atoire enti�re : fonction rand()
   i=rand();
   printf("%d\n",i);

   // contraindre dans une fourchette
   i=rand()%10;  // entre 0 et 9 compris
   printf("%d\n",i);

   i=5+rand()%10;// entre 5 et 14

   //----------------
   // initialiser la suite des nombre al�atoires :
   srand(time(NULL));

   //----------------
   // obtenir une valeur al�atoire entre 0 et 1
   res= (float)rand()/RAND_MAX;
   printf("%f\n",res);

   // obtenir une valeur al�atoire en r�elle dans une fourchette
   res= ((float)rand()/RAND_MAX)*10; // entre 0 et 10 compris
   printf("%f\n",res);

   // fin prog
   return 0;

}
*/


