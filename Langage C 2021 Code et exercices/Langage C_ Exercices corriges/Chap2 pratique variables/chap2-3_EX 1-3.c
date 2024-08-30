/*
*   Pour tester la solution d'un exercice il faut :
*   - faire un projet c en mode console
*   - copier le code correspondant dans le fichier c
*   - compiler et ex�cuter
*
*   ou
*   - copier tout dans le fichier c du projet
*   - enlever les commentaires du code de l'exercice � tester
*   - mettre en commentaire tous les autres
*   - compiler et ex�cuter
*/

/********************************************************************
*   Chapitre 1 : Variables simples                                  *
*   2. Variables simples                                            *
*   2.3 Mise en pratique : avoir des variables dans un programme    *
*********************************************************************


/***********************************
Exercice 1
Combien y a t-il de type en C et quels sont-ils ?

6 types de variables simples :
char, short, int, long, float, double

(auxquels s'ajoutent �galement les variables ensembles
structures, tableaux, et les pointeurs)


Qu'est ce qui les diff�rencie ?
Les types de variables simples se diff�rencient par la taille en m�moire
et la virgule qui est pr�sente ou pas.


Par d�faut sont-ils sign�s ou non sign�s ?
Ils sont sign�s


Quelles sont les fourchettes de valeurs ?

Se reporter au tableau page ...

*/

/***********************************
Exercice 2
Quels sont les  types � choisir pour coder les nombres
45.876,  56.0,     77,    650987,    32769,  - 32765,   450009996   ?

45.876 et 56.0 :
float ou double (virgule)

77 :
un char suffit

650987 :
il faut 20 bits pour le codage en binaire, soit au moin 3 octets,
alors un int (en 4 octets) ou un long

32769 :
il faut 16 bits pour le codage binaire alors soit un unsigned short, soit un int (4 octets), soit un long.

- 32765
15 bits plus le bit de signe, 2 octets, alors un short ou un int

450009996 :
29 bits, 4 octets soit un int soit un long


�crivez un programme dans lequel vous avez des variables susceptibles de recevoir ces valeurs.

*
#include <stdio.h>
#include <stdlib.h>
int main()
{
float f = 45.876;
double d = 56.0;
char c = 77;
int i = 650987;
unsigned short is = 32769;
short s = - 32765;
long l = 450009996;

    printf("%f\n",f);
    printf("%lf\n",d);
    printf("%d\n",c);
    printf("%d\n",i);
    printf("%d\n",is);
    printf("%d\n",s);
    printf("%ld\n",l);
    return 0;
}

/***********************************
Exercice 3
Soit dans un programme les d�clarations suivantes :
	int 0t, ti, p0;
	freste float;
	double div-total;
	float tata, t2345, char c, cc :
	short Err_, _E_,
Indiquez, expliquez et corrigez les erreurs (vous pouvez utiliser le compilateur).


*
#include <stdio.h>
#include <stdlib.h>
int main()
{
int 0t, ti, p0; // err 0t identificateur qui commence par un chiffre
freste float;   // err le type est avant l'identificateur dans une d�claration de variable
double div-total; // err le signe - ne peut pas �tre util;is� dans un nom de variable
float tata, t2345, char c, cc : // err ; obligatoire pour clore les d�claration de float avant char c
short Err_, _E_, // err ; apr�s la variable _E_ pour clore sa d�claration

    return 0;
}
/*********************************
*/











