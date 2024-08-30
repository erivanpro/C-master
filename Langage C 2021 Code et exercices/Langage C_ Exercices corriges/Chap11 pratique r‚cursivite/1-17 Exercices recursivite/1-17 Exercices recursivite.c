/**********************************************************************************

REMARQUE:
les exercices 3, 4, 5, 6 sont extraits du livre :
Leendert Ammeraal Programs and data structures in C, Jhon Wiley & Sons, 1988.
traduit en fran�ais aux �ditions interEditions / Masson en 1996.
Le livre est toujours paru sans corrig� et dans une traduction parfois aproximative.
De ce fait il apparait parfois difficile voire impossible de r�pondre � certaines
des questions pos�es. Nous amm�nagerons nos r�ponses aux exercices en cons�quence.

D'une fa�on g�n�rale, dans notre approche d'apprentissage, ce n'est pas la solution
qui compte, c'est la capacit� de trouver et d'�laborer une solution. Chaque exercice
a pour but de solliciter une mise en pratique qui seule va permettre de comprendre
et d'acqu�rir une certaine maitrise du concept abord�.

/***********************************************************************************
Exercice 1
Afficher avec une fonction r�cursive tous les nombres entre n et n'
entr�s par l'utilisateur.
************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

void affiche(int n1, int n2)
{
	printf("%d", n1);
	if (n1 < n2)
		affiche(++n1, n2);
}

int main()
{
	int n1, n2;
	printf("entrer deux nombres : ");
	scanf_s("%d%d", &n1, &n2);

	// permuter si n1 plus grand
	if (n1 > n2) {
		n1 ^= n2;
		n2 ^= n1;
		n1 ^= n2;
	}

	affiche(n1, n2);

	system("PAUSE");
	return 0;
}
/********************************************************************
Exercice 2
Qu'impriment les programmes suivants ?

Le mieux est ici de mettre en pratique les deux analyses possibles
pr�sent�es p.456 pour l'analyse descendante, p. 457 pour l'analyse ascendente.
puis de v�rifier ensuite si les r�sultats obtenus sur papier sont correctes.
**********************************************************************
//programme 1
#include <stdio.h>
void f(int n)
{
	if (n>0){
		f (n-3);
		printf("%3d\n",n);
		f (n-2);
	}
}

#include <stdio.h>
int main()
{
	f(6);

	system("PAUSE");
	return 0;
}

// programme 2
#include <stdio.h>
void f(int n)
{
	if (n>0){
		f (n/10-100);
		printf("%3d\n",n);
		f (n/5-200);
	}
}
int main()
{
	f (10000);

	system("PAUSE");
	return 0;
}
*/

/********************************************************************
Exercice 3
Remplacer les fonctions f(), g(), h() ci-apr�s par des variantes it�ratives
�quivalentes (plus ou moins). Comparer dans chaque cas la quantit� de
m�moire utilis�e et le temps de calcul n�cessaire pour l'une et l'autre
des variantes.

void f(void)
{
	if (getchar() == ' ') {
		f();
	}
}
void g(int n)
{
	int i;
	if (n>0){
		scanf_s("%d",&i);
		g(n-1);
		printf("%d\n",i);
	}
}
int h(int n)
{
	return n<0 ? 0 : (n==0 ? 1 : h(n-1) + h(n-2));
}
******************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Place en m�moire ?
L'op�rateur sizeof ne permet pas de prendre la place occup�e
en m�moire par une fonction.
Mais � priori une version it�rative prend moins de place en m�moire
dans la mesure o� elle suppose une pile d'appel plus r�duite.
En effet chaque nouvel appel de fonction s'ajoute � la pile des appels
et de ce fait une fonction r�cursive qui est appel�e plusieurs fois
augmente la place prise en m�moire.
Tout d�pend si la r�cursivit� permet ou pas de r�duire le nombre
des ressources n�cessaires � l'algorithme.

Temps ?
Il y a des saisies � faire et le temps en d�pend aussi. Il sera donc
difficile de comparer de ce point de vue r�cursif et it�ratif
**************************************************************************

void f(void)
{
	static int cmpt = 0;   // ajout pour visualiser
	if (getchar() == ' ') {
		printf("%d", ++cmpt); // ce qui se passe
		f();
	}
}

void fi(void)
{
	int cmpt = 0;		// ajout pour visualiser
	while (getchar() == ' ')
		printf("%d", ++cmpt); // ce qui se passe
}
 // si on entre 1 2 3 4 5 on obtient l'affichage : 5 4 3 2 1
void g(int n)
{
	int i;
	if (n>0){
		scanf_s("%d",&i);
		g(n-1);
		printf("%d\n",i);
	}
}
// solution incompl�te :
//si on entre 1 2 3 4 5 on obtient l'affichage : 1 2 3 4 5
void gi1(int n)
{
	int i;
	while (n-- > 0) {
		scanf_s("%d", &i);
		printf("%d\n", i);
	}
}
//si on entre 1 2 3 4 5 pour obtenir l'affichage : 5 4 3 2 1
//on est oblig� d'impl�menter une pile et de stocker
// dedans chaque saisie au fur et � mesure puis d'fficher en
// partant de la derni�re.
void gi2(int n)
{
	int i;
	int*pile = (int*) malloc(sizeof(int)*n);
	int nb;

	for(nb=0; nb<n; nb++){
		scanf_s("%d", &i);
		pile[nb] = i;
	}
	// ici nb == n, il faut lui soustraire 1
	while(--nb >= 0)
		printf("%d\n", pile[nb]);

	free(pile);
}
// la suite de fibonacci avec une l�g�re modification au d�part

int h(int n)
{
	return n<0 ? 0 : (n==0 ? 1 : h(n-1) + h(n-2));
	// suite de fibonacci :
	//return n <= 1 ? n : h(n - 2) + h(n - 1);
}
int hi(int n)
{
	int res, f1, f2;
	if (n < 0)
		res = 0;
	else if (n == 0)
		res = 1;
	else {
		f2 = 0;
		f1 = 1;
		for (int i = 1; i <= n; i++) {
			res = f2 + f1;
			f2 = f1;
			f1 = res;
		}
	}
	return res;
}

int main()
{

	printf("1) F recursif : taper des espaces puis enter \n");
	int debut = clock();
	f();
	int fin = clock();
	printf("temps : %d\n", fin - debut);

	printf("1) F iteratif : taper des espaces puis enter \n");
	debut = clock();
	fi();
	fin = clock();
	printf("temps : %d\n", fin - debut);
	printf("--------------------------\n");

	printf("2) G recursif : entrez cinq nombres\n");
	g(5);
	printf("2) G iteratif 1 : entrez cinq nombres\n");
	gi1(5);
	printf("2) G iteratif 2 : entrez cinq nombres\n");
	gi2(5);
	printf("--------------------------\n");

	printf("3) H :\n");
	printf("%d\n",h(8));
	printf("%d\n", hi(8));


	system("PAUSE");
	return 0;
}
/********************************************************************************
Exercice 4
�crire une fonction prenant un argument entier et renvoyant la somme des
chiffres d�cimaux constituant l'argument. Comparer deux variantes de la
solution � ce probl�me, l'une r�cursive et l'autre it�rative.
*********************************************************************************
#include <stdio.h>
#include <stdlib.h>

int recursive(int n)
{
	int cmpt = 0;
	if (n > 0) {
		cmpt = n % 10;
		cmpt += recursive(n / 10);
	}
	return cmpt;
}
int iterative(int n)
{
	int cmpt = 0;
	while (n > 0) {
		cmpt += n % 10;
		n /= 10;
	}
	return cmpt;
}
int main()
{
	printf("%d\n",iterative(123456));
	printf("%d\n",recursive(123456));

	system("PAUSE");
	return 0;
}
/*********************************************************************************
Exercice 5
�crire un programme destin� � lire une succession de nombres r�els en virgule
flottante et afficher la somme des 1er, 3e, 6e, 10e, 15e (etc.) �l�ments de
cette suite. Tout caract�re non num�rique sera interpr�t� comme le signal
d'arr�t de cette suite de nombres.
*********************************************************************************
// exercice identique � l'exercice 7 :
// il s'agit de "nombres triangulaires", une suite due � Pythagore :
// le n-i�me nombre triangulaire est la somme des entiers de 1 � n.
#include <stdio.h>

int somme(int n)
{
	return (n > 0) ? n += somme(n - 1) : n;
}

void pause()
{
	puts("Appuyez sur [enter] pour quitter...\n");
	getchar();
}

int main()
{
	printf("%d\n", somme(7));

	pause();
	return 0;
}
/*********************************************************************************
Exercice 6  : il y a une erreur, l'�nonc� est incomplet.
�crire un programme destin� � lire un chiffre d�cimal d. Afficher syst�matiquement
chacun des entiers positifs x inf�rieurs � 100 qui comportent d pour x et pour x2.

Enonc� complet :
�crire un programme destin� � lire un chiffre d�cimal d. Afficher syst�matiquement
chacun des entiers positifs x inf�rieurs � 100 pr�sentant la caract�ristique de
compter le chiffre d aussi bien dans sa repr�sentation d�cimale (x) que dans celle
de son carr� (x2)
*********************************************************************************
// �nonc� ramen� � :
// soit d entr� par l'utilisateur, trouver et afficher x ou x2 �gale � d pour
// x entre 0 et 100
#include <stdio.h>

int trouve(int x, int nb)
{
	int res = -1;
	if (x > 0) {
		if (x == nb || x * x == nb)
			res = x;
		else
			res = trouve(x - 1, nb);
	}
	return res;
}

int main()
{
	printf("entrez un nombre :\n");
	int nb;
	scanf_s("%d", &nb);

	int res = trouve(100, nb);
	if (res < 0)
		printf("pas de solution trouvee\n");
	else
		printf("x : %d", res);


	system("pause");
	return 0;
}
/*********************************************************************************
Exercice 7
�crire une fonction r�cursive qui � partir de n entr� par l'utilisateur calcule
la somme n+n-1+n-2... jusque n=0.
*********************************************************************************
#include <stdio.h>

int somme(int n)
{
	return (n > 0) ? n += somme(n - 1) : n;
}

void pause()
{
	puts("Appuyez sur [enter] pour quitter...\n");
	getchar();
}

int main()
{
	printf("%d\n", somme(7));

	pause();
	return 0;
}


/*********************************************************************************
Exercice 8
�crire une fonction r�cursive qui � partir de n entr� par l'utilisateur calcule
la somme :
un = 1 + 24 + 34 + 44 + .... + n4. (4 est une puissance : voir mise en page �nonc�
dans le livre)
*********************************************************************************
#include <stdio.h>

int calcul(int n, int p)
{
	int res = 0;
	if (n == 1)
		res = 1;
	else{
		for (int i = 0; i < p; i++)
			res += n * n;
		res += calcul(n - 1, p);
	}
	return res;
}

void pause()
{
	puts("Appuyez sur [enter] pour quitter...\n");
	getchar();
}

int main()
{
	printf("%d\n", calcul(3,4));

	pause();
	return 0;
}
/*********************************************************************************
Exercice 9
Sur le mod�le de la suite de Fibonacci, �crire une fonction r�cursive pour
calculer la suite � partir de n entr� par l'utilisateur : f(n) = n-4 + n-3 + n-2 + n-1.
*********************************************************************************
#include <stdio.h>

// suite de Fibonacci :
int fibo(int n)
{
	return n <= 1 ? n : fibo(n - 2) + fibo(n - 1);
}
// variation :
int fbo(int n)
{
	return n <= 3 ? n : fbo(n - 4) + fbo(n - 3) + fbo(n - 2) + fbo(n - 1);
}

int main()
{
	printf("Entrez un nombre entier :\n");
	int val;
	scanf_s("%d", &val);

	printf("%d\n", fbo(val));

	system("pause");
	return 0;
}
/*********************************************************************************
Exercice 10
Sur le mod�le du calcul factoriel, �crire une fonction r�cursive qui calcule
la suite pour n entr� par l'utilisateur : f(n) = 2*n*n-1 ... pour n>0.
*********************************************************************************
#include <stdio.h>
#include <stdlib.h>

int f(int n)
{
	return (n == 1) ? 2 : n * f(n - 1);

	// �quivalent
	//if (n == 1)
	//	return n = 2;
	//else
	//	return n * f(n - 1);
}

int main()
{

	printf("%d\n",f(3));

	system("pause");
	return 0;
}


/*********************************************************************************
Exercice 11 :
strlen en r�cursif
�crire une version r�cursive de la fonction strlen() qui retourne la longueur
d'une cha�ne de caract�res donn�e en param�tre.
*********************************************************************************
#include <stdio.h>
#include <string.h>

int strlen_(char*s)
{
	int cmp = 1;
	if (*s != '\0')
		cmp += strlen_(++s);
	else
		cmp = 0;
	return cmp;
}
void pause()
{
	printf("Presser Enter pour quitter\n");
	getchar();
}
int main()
{

	printf("%d\n", strlen_("Bonjour"));
	printf("%d\n", strlen("Bonjour")); // pour comparer r�sultats

	pause();
	return 0;
}

/*********************************************************************************
Exercice 12 :
d�tecteur de palindrome
Un palindrome est un mot ou une phrase qui se lit aussi bien � l'envers
qu'� l'endroit (sans tenir compte des espaces). Par exemple "radar", "kayak",
"abccba" ou une phrase "esope reste et se repose". La phrase ou le mot sont
entr�s par l'utilisateur et une fonction r�cursive re-tourne si oui ou non
la cha�ne de caract�res donn�e en param�tre est un palindrome.
*********************************************************************************
#include <stdio.h>
#include <string.h>

int palindrome(char*s)
{
	int res = 1;
	int l = strlen(s)-1; // l pointe sur le dernier caract�re de la chaine
	if (l > 0) {// si plus d'un caract�re dans la chaine

		while (*s == ' ') { // sauter les espaces du d�but
			s++;
			l--; // ce qui diminue la taille de la chaine
		}
		while (*(s + l) == ' ')// sauter espace fin
			l--;

		if (*s != *(s + l))// comparer premier et dernier caract�res
			res = 0; // si diff�rent ce n'est pas un palindrome

		else {
			s[l] = '\0'; // supprimer dernier
			res = palindrome(s+1); // passer au premier suivant
		}
	}
	return res;

}

void pause()
{
	printf("Presser Enter pour quitter\n");
	getchar();
}
int main()
{
	char s[100] = "esope reste et se repose";
	printf("%d\n", palindrome(s));

	//remarque :
	//la fonction n'accepte pas de prendre en param�tre une constante
	//chaine de caract�res par exemple passer directement "esope reste et se repose"
	//ne fonctionnera pas. En effet la chaine de caract�res doit pouvoir �tre modifiable.

	pause();
	return 0;
}

/*********************************************************************************
Exercice 13 :
parcours syst�matique d'une matrice
Soit une matrice MAT d'entiers de TX par TX faire le programme qui affiche tous
les chemins directs possibles qui partent de MAT[0][0] pour arriver en MAT[TY-1][TX-1]
sans jamais retourner en arri�re ou faire des circuits. C'est-�-dire sur le sch�ma,
tous les trajets qui peuvent aller directement en avan�ant ou en descendant de la
case grise en haut � gauche � celle en bas � droite :

L'affichage est soit graphique avec allegro ou conio, soit en texte, le trajet
�tant une suite de positions : (0,0)-(0,1)-(0,2)-(...,...)-(TX-1, TY-1).
*********************************************************************************
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define TX	30
#define TY	20

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void attendre(int duree)
{
	int start = clock();
	while (clock()<start+duree){}
}

// tous les parcours possibles dans une matrice
void parcours1(int mat[][TX], int tx, int ty, int x, int y)
{
	if (x < TX && y < TY) {

		mat[y][x] = 1;
		gotoxy(x * 3, y);
		printf("%3d", mat[y][x]);

		//attendre(100);
		parcours1(mat, tx, ty, x + 1, y);
		parcours1(mat, tx, ty, x, y + 1);
	}
	else
		textcolor(rand() % 15 + 1);
}
// tous les parcours possibles dans une matrice sans repasser sur les positions
// d�j� vues
void parcours2(int mat[][TX], int tx, int ty, int x, int y)
{
	if (x < TX && y < TY && mat[y][x] != 1) { // juste controle valeur dans mat

		mat[y][x] = 1;
		gotoxy(x * 3, y);
		printf("%3d", mat[y][x]);

		attendre(50);
		parcours2(mat, tx, ty, x + 1, y);
		parcours2(mat, tx, ty, x, y + 1);
		textcolor(rand() % 15 + 1);
	}


}

void pause()
{
	printf("Presser Enter pour quitter\n");
	getchar();
}
int main()
{
	int mat[TY][TX];
	//parcours1(mat, TX, TY, 0, 0);
	parcours2(mat, TX, TY, 0, 0);

	gotoxy(0, TY + 2);
	pause();
	return 0;
}

/*********************************************************************************
Exercice 14 :
parcours al�atoire d'une matrice
Soit une matrice de TX par TY, �crire une fonction r�cursive de remplissage al�atoire.
Chaque position ne peut �tre visit�e qu'une fois et sert de d�part pour visiter
d'autres positions.
R�aliser un affichage graphique en utilisant les fonctions gotoxy() et textcolor()
ou avec une librairie graphique, allegro par exemple.
*********************************************************************************
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define TX	40
#define TY	20

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void attendre(int duree)
{
	int start = clock();
	while (clock()<start+duree){}
}

// remplit la matrice de fa�on syst�matique
void remplir(int mat[][TX], int tx, int ty, int x, int y)
{
	if (x > 0 && x < TX && y >= 0 && y < TY && mat[y][x]!=1) {

		mat[y][x] = 1;
		gotoxy(x , y);
		putchar(' ');

		attendre(50);

		remplir(mat, tx, ty, x, y - 1);		//nord
		remplir(mat, tx, ty, x + 1, y - 1); // nord-est
		remplir(mat, tx, ty, x + 1, y);		// est
		remplir(mat, tx, ty, x + 1, y + 1); // sud-est
		remplir(mat, tx, ty, x, y + 1);		// sud
		remplir(mat, tx, ty, x - 1, y + 1); // sud-ouest
		remplir(mat, tx, ty, x - 1, y);		// ouest
		remplir(mat, tx, ty, x - 1, y - 1); // nord-ouest
	}
	//else
		//textcolor((rand() % 15 + 1)<<4);
}


// version plus marrante mais le remplissage total n'est pas garanti
// �a d�pend des tirages al�atoires de directions
void remplir2(int mat[][TX], int tx, int ty, int x, int y)
{
	if (x > 0 && x < TX && y >= 0 && y < TY && mat[y][x] != 1) {

		mat[y][x] = 1;
		gotoxy(x, y);
		putchar(' ');

		attendre(25);

		switch (rand() % 8) {
			case 0: remplir2(mat, tx, ty, x, y - 1);		//nord
			case 1: remplir2(mat, tx, ty, x + 1, y - 1); // nord-est
			case 2: remplir2(mat, tx, ty, x + 1, y);		// est
			case 3: remplir2(mat, tx, ty, x + 1, y + 1); // sud-est
			case 4: remplir2(mat, tx, ty, x, y + 1);		// sud
			case 5: remplir2(mat, tx, ty, x - 1, y + 1); // sud-ouest
			case 6: remplir2(mat, tx, ty, x - 1, y);		// ouest
			case 7: remplir2(mat, tx, ty, x - 1, y - 1); // nord-ouest
		}

	}
	//else
		//textcolor((rand() % 15 + 1)<<4);
}

// en combinant les deux on obtient un remplissage syst�matique
void remplir3(int mat[][TX], int tx, int ty, int x, int y)
{
	if (x > 0 && x < TX && y >= 0 && y < TY && mat[y][x] == 0) {

		mat[y][x] = 1;
		gotoxy(x, y);
		putchar(' ');

		attendre(50);

		switch (rand() % 8) {
			case 0: remplir3(mat, tx, ty, x, y - 1);		//nord
			case 1: remplir3(mat, tx, ty, x + 1, y - 1); // nord-est
			case 2: remplir3(mat, tx, ty, x + 1, y);		// est
			case 3: remplir3(mat, tx, ty, x + 1, y + 1); // sud-est
			case 4: remplir3(mat, tx, ty, x, y + 1);		// sud
			case 5: remplir3(mat, tx, ty, x - 1, y + 1); // sud-ouest
			case 6: remplir3(mat, tx, ty, x - 1, y);		// ouest
			case 7: remplir3(mat, tx, ty, x - 1, y - 1); // nord-ouest
		}
		textcolor(14 << 4);

		remplir3(mat, tx, ty, x, y - 1);		//nord
		remplir3(mat, tx, ty, x + 1, y - 1); // nord-est
		remplir3(mat, tx, ty, x + 1, y);		// est
		remplir3(mat, tx, ty, x + 1, y + 1); // sud-est
		remplir3(mat, tx, ty, x, y + 1);		// sud
		remplir3(mat, tx, ty, x - 1, y + 1); // sud-ouest
		remplir3(mat, tx, ty, x - 1, y);		// ouest
		remplir3(mat, tx, ty, x - 1, y - 1); // nord-ouest

		textcolor((rand() % 15 + 1) << 4);

	}
}

void pause()
{
	printf("Presser Enter pour quitter\n");
	getchar();
}
int main()
{
	int mat[TY][TX] = { 0 };

	srand(time(NULL));
	textcolor((rand() % 15 + 1) << 4);

	//remplir(mat, TX, TY, rand()%TX, rand()%TY);
	//remplir3(mat, TX, TY, rand() % TX, rand() % TY);
	remplir3(mat, TX, TY, rand() % TX, rand() % TY);

	gotoxy(0, TY + 2);
	pause();
	return 0;
}
/*********************************************************************************
Exercice 15 :
d�grad� de couleurs dans un carr�
On dispose d'une palette de couleurs style arc-en-ciel avec un d�grad� de couleurs.
On donne une couleur au hasard � chaque coin A, B, C, D d'un carr� trac� � l'�cran.
Puis on donne la moyenne de ces quatre couleurs au centre du carr� O.

On calcule �galement les couleurs des points I, J, K, L par moyenne des deux
couleurs voisines. Puis on recommence avec les quatre carr�s obtenus, et ainsi de
suite jusqu'� ce que les carr�s aient des c�t�s de l'ordre du pixel.
R�aliser un programme de test de pr�f�rence en mode graphique sous allegro.
*********************************************************************************
// Pour simplifier et �viter d'entrer dans un environnement graphique nous allons
// prendre pour image carr� une matrice de nombres. La palette de couleur correspondra
// � des valeurs de couleurs entre 0 et 255 bornes comprises. Cette palette suppose
// un d�grad� du plus sombre 0 au plus clair 255. L'important est de
// mettre en place un algorithme de r�partition de ces nombres et de pouvoir ensuite
// l'observer.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// attention TX-1 et TY-1 doivent �tre des puissances de 2
#define TX	17
#define TY	17

void init(int im[TY][TX]);
void affiche(int im[TY][TX]);
void repartir(int im[][TX], int x, int y, int tx, int ty);
void pause();

int main()
{
	// simulation d'une image bitmap
	int image[TY][TX] = { 0 };

	srand(time(NULL));
	init(image);

	// attention il faut que TX-1 et TY-1 soient des puissances de 2, toujours pairs
	// lors d'une succession de divisions par 2, par exemple 16 -> 8 -> 4 -> 2
	// sinon la fonction remplir_degrade se retrouve avec des tx et ty impairs qui
	// d�s�quilibrent la r�partition en rendant des lignes et des colones inaccessibles
	// par exemple 20 -> 10 -> 5 -> 2 engendre des pertes entre 5 et 2
	//

	repartir(image, 0, 0, TX - 1, TY - 1);
	affiche(image);

	pause();
	return 0;
}
void init(int im[TY][TX])
{
	im[0][0] = rand() % 256;
	im[0][TX - 1] = rand() % 256;
	im[TY - 1][0] = rand() % 256;
	im[TY - 1][TX - 1] = rand() % 256;
}
void affiche(int im[TY][TX])
{
	for (int y = 0; y < TY; y++) {
		for (int x = 0; x < TX; x++)
			printf("%4d", im[y][x]);
		putchar('\n');
	}
}
void repartir(int im[][TX], int x, int y, int tx, int ty)
{
	int I, J, K, L, C;
	I= (im[y + ty][x] + im[y + ty][x + tx]) / 2;
	J= (im[y][x + tx] + im[y + ty][x + tx]) / 2;
	K = (im[y][x] + im[y][x + tx]) / 2;
	L = (im[y][x] + im[y + ty][x]) / 2;
	C = (im[y][x] + im[y][x + tx] + im[y + ty][x] + im[y + ty][x + tx]) / 4;

	im[y][x + tx / 2] = K;
	im[y + ty / 2][x + tx] = J;
	im[y + ty][x + tx / 2] = I;
	im[y + ty / 2][x] = L;
	im[y + ty / 2][x + tx / 2] = C;

	if (tx > 0 || ty > 0) {
		repartir(im, x, y, tx / 2, ty / 2);
		repartir(im, x + tx / 2, y, tx / 2, ty / 2);
		repartir(im, x, y + ty / 2, tx / 2, ty / 2);
		repartir(im, x + tx / 2, y + ty / 2, tx / 2, ty / 2);
	}
}
void pause()
{
	printf("Presser Enter pour quitter\n");
	getchar();
}

/*********************************************************************************
Exercice 16 :
trac� de carr�s
Au d�part on a une position (x,y), par exemple le centre de l'�cran et une taille
de segments. �crire deux fonctions qui tracent r�cursivement 8 carr�s r�partis
de fa�on fractale les uns autour des autres. La premi�re fonction trace ses carr�s
� partir d'une taille maximum donn�e en entr�e et vers l'int�rieur. La seconde
fonction trace des carr�s de fa�on extensive, vers l'ext�rieur jusqu'� atteindre
une taille maximum.
*********************************************************************************
// Dans cet exercice la r�partition des carr�s peut s'interpr�ter de diff�rentes
// fa�ons. La plus simple est sans doute de produire des carr�s encastr�s les uns
// dans les autres comme une cible, soit en partant du plus grand, soit en partant
// du plus petit.
// Voici une version console
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h>  // pour utiliser le type bool en C

#define TX	40
#define TY	20

void carre_interieur(int tmax, int x, int y, int color);
void carre_exterieur(int max, int t, int x, int y, int color);
void carre_coin(int t, int x, int y, int color);
void trace(int t, int x, int y, int color);

void gotoxy(int x, int y);
void textcolor(int color);
_Bool ConsolePosEtSize(int x, int y, int tx, int ty);
_Bool ConsoleResize(int width, int height);
void pause(int x, int y, int color);

int main()
{
	// pour b�n�ficier d'une console plusa grande
	ConsolePosEtSize(0, 0, 150, 40);

	// deux traces de "cibles" carr�es
	carre_interieur(8, 10, 15, 15);
	carre_exterieur(10, 1, 40, 15, 1);

	// modification pour trac� aux coins
	carre_coin(8, 80, 20, 15);

	pause(0,32,15);

	return 0;
}
void carre_interieur(int tmax, int x, int y, int color)
{
	if (tmax > 0) {
		trace(tmax, x, y, color);
		carre_interieur(tmax - 1, x, y, color - 1);
	}

}
void carre_exterieur(int max, int t, int x, int y, int color)
{
	if (t < max) {
		trace(t, x, y, color);
		carre_exterieur(max, t + 1, x, y, color + 1);
	}
}
void carre_coin(int t, int x, int y, int color)
{
	if (t > 0) {
		trace(t, x, y, color);
		carre_coin(t / 2, x - t, y - t, color - 1);
		carre_coin(t / 2, x + t, y - t, color - 1);
		carre_coin(t / 2, x + t, y + t, color - 1);
		carre_coin(t / 2, x - t, y + t, color - 1);
	}
}

void trace(int t, int x, int y, int color)
{
	textcolor(color<<4);
	for (int py = y - t; py <= y + t; py++) {
		gotoxy(x-t, py);
		putchar(' ');
		gotoxy(x+t, py);
		putchar(' ');
	}
	for (int px = x - t; px <= x + t; px++) {
		gotoxy(px, y-t);
		putchar(' ');
		gotoxy(px, y + t);
		putchar(' ');
	}

}
void gotoxy(int x, int y)
{
	COORD c = { x,y };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;

	if (!GetConsoleScreenBufferInfo(h, &info))
		return;
	// controler que le curseur ne sort pas de la fen�tre
	if (c.X >= 0 && c.X <= info.dwSize.X && c.Y >= 0 && c.Y <= info.dwSize.Y)
		SetConsoleCursorPosition(h, c);
}
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
_Bool ConsolePosEtSize(int x, int y, int tx, int ty)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE)
		return FALSE;

	HWND hwnd = GetForegroundWindow();

	// BOOL MoveWindow(HWND hWnd, int  X, int  Y, int  nWidth, int  nHeight, BOOL bRepaint);
	// positionne la fen�tre � la position X, Y et prend une nouvelle taille nWidth,
	// nHeight en pixel. Le bool bRepaint donne la possibilit� de redessiner le contenu de
	// la fen�tre.

	// Pour �viter des soucis avec le buffer de la console, il plus
	// prudent de redonner une "vraie" taille � la console derri�re
	// avec la fonction ConsoleResize()
	MoveWindow(hwnd, x, y, 0, 0, FALSE);
	if (!ConsoleResize(150, 40))
		return FALSE;

	return TRUE;
}
_Bool ConsoleResize(int width, int height)
{
	// r�cup�rer un handle sur la fen�tre concern�e
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE)
		return FALSE;

	// r�cup�ration des tailles maximum et minimum
	// support�es par la console
	COORD max = GetLargestConsoleWindowSize(h);
	width = (width > max.X) ? max.X : ((width < 1) ? 1 : width);
	height = (height > max.Y) ? max.Y : ((height < 1) ? 1 : height);

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	// si la hauteur  demand�e est inf�rieure � la hauteur
	// actuelle
	if (height < info.dwSize.Y) {

		// diminuer d'abord le rect fen�tre (abs coord)
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		// ensuite le buffer correspondant
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	// si la taille demand�e est sup�rieure � la taille actuelle
	else if (height > info.dwSize.Y) {

		// d'abord augmenter la taille du buffer
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		// ensuite le rectangle correspondant de la fen�tre
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;
	}
	// idem pour la largeur
	if (width < info.dwSize.X) {

		info.srWindow.Right = width - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

	}
	else if (width > info.dwSize.X) {

		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		info.srWindow.Right = width - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;
	}
	return TRUE;
}

void pause(int x, int y, int color)
{
	gotoxy(x, y);
	textcolor(color);
	printf("Presser Enter pour quitter");
	getchar();
}
/*********************************************************************************
Exercice 17 :
tracer une spirale
�crire une fonction r�cursive qui permet de tracer une spirale rectangulaire.
Au d�part il y a une longueur L pour le premier segment et la taille maximum
qu'un segment peut atteindre.
*********************************************************************************
#include <stdio.h>
#include <windows.h>
#include <time.h>

void spirale(int x, int y, int tx, int ty, int color);
void AvanceDroite(int x, int y, int tx, int color);
void Descend(int x, int y, int ty, int color);
void AvanceGauche(int x, int y, int tx, int color);
void Monte(int x, int y, int ty, int color);

void gotoxy(int x, int y);
void textcolor(int color);
_Bool ConsolePosEtSize(int x, int y, int tx, int ty);
_Bool ConsoleResize(int width, int height);
void pause(int x, int y, int color);

int main()
{
	ConsolePosEtSize(0, 0, 130, 40);

	spirale(10, 2, 60, 20, 9);

	pause(10,35, 9);
	return 0;
}

void spirale(int x, int y, int tx, int ty, int color)
{
	if (tx > 0 && ty > 0) {
		Descend(x, y, ty, color);
		AvanceDroite(x, y+ty, tx, color);
		Monte(x+tx, y + ty, ty - 2, color);
		AvanceGauche(x + tx, y + 2, tx - 2, color);
		spirale(x + 2, y + 2, tx - 4, ty - 4, color+1);
	}
}
void AvanceDroite(int x, int y, int tx, int color)
{
	textcolor(color<<4);
	for (int i = x; i < x + tx; i++) {
		gotoxy(i, y);
		putchar(' ');
	}
}
void Descend(int x, int y, int ty, int color)
{
	textcolor(color << 4);
	for (int i = y; i < y + ty; i++) {
		gotoxy(x, i);
		putchar(' ');
	}
}
void AvanceGauche(int x, int y, int tx, int color)
{
	textcolor(color << 4);
	for (int i = x; i > x - tx; i--) {
		gotoxy(i, y);
		putchar(' ');
	}
}
void Monte(int x, int y, int ty, int color)
{
	textcolor(color << 4);
	for (int i = y; i > y - ty; i--) {
		gotoxy(x, i);
		putchar(' ');
	}
}

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;

	if (!GetConsoleScreenBufferInfo(h, &info))
		return;
	// controler que le curseur ne sort pas de la fen�tre
	if (c.X >= info.srWindow.Left && c.X <= info.srWindow.Right &&
		c.Y >= info.srWindow.Top && c.Y <= info.srWindow.Bottom)
		SetConsoleCursorPosition(h, c);
}
void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
_Bool ConsolePosEtSize(int x, int y, int tx, int ty)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE)
		return FALSE;

	HWND hwnd = GetForegroundWindow();

	// BOOL MoveWindow(HWND hWnd, int  X, int  Y, int  nWidth, int  nHeight, BOOL bRepaint);
	// positionne la fen�tre � la position X, Y et prend une nouvelle taille nWidth,
	// nHeight en pixel. Le bool bRepaint donne la possibilit� de redessiner le contenu de
	// la fen�tre.

	// Pour �viter des soucis avec le buffer de la console, il plus
	// prudent de redonner une "vraie" taille � la console derri�re
	// avec la fonction ConsoleResize()
	MoveWindow(hwnd, x, y, 0, 0, FALSE);
	if (!ConsoleResize(150, 40))
		return FALSE;

	return TRUE;
}
_Bool ConsoleResize(int width, int height)
{
	// r�cup�rer un handle sur la fen�tre concern�e
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE)
		return FALSE;

	// r�cup�ration des tailles maximum et minimum
	// support�es par la console
	COORD max = GetLargestConsoleWindowSize(h);
	width = (width > max.X) ? max.X : ((width < 1) ? 1 : width);
	height = (height > max.Y) ? max.Y : ((height < 1) ? 1 : height);

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	// si la hauteur  demand�e est inf�rieure � la hauteur
	// actuelle
	if (height < info.dwSize.Y) {

		// diminuer d'abord le rect fen�tre (abs coord)
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		// ensuite le buffer correspondant
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	// si la taille demand�e est sup�rieure � la taille actuelle
	else if (height > info.dwSize.Y) {

		// d'abord augmenter la taille du buffer
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		// ensuite le rectangle correspondant de la fen�tre
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;
	}
	// idem pour la largeur
	if (width < info.dwSize.X) {

		info.srWindow.Right = width - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

	}
	else if (width > info.dwSize.X) {

		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		info.srWindow.Right = width - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;
	}
	return TRUE;
}
void pause(int x, int y, int color)
{
	gotoxy(x, y);
	textcolor(color);
	printf("Presser Enter pour quitter");
	getchar();
}
*/