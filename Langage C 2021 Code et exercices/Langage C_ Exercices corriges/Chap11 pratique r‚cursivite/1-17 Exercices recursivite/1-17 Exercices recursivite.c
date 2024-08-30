/**********************************************************************************

REMARQUE:
les exercices 3, 4, 5, 6 sont extraits du livre :
Leendert Ammeraal Programs and data structures in C, Jhon Wiley & Sons, 1988.
traduit en français aux éditions interEditions / Masson en 1996.
Le livre est toujours paru sans corrigé et dans une traduction parfois aproximative.
De ce fait il apparait parfois difficile voire impossible de répondre à certaines
des questions posées. Nous amménagerons nos réponses aux exercices en conséquence.

D'une façon générale, dans notre approche d'apprentissage, ce n'est pas la solution
qui compte, c'est la capacité de trouver et d'élaborer une solution. Chaque exercice
a pour but de solliciter une mise en pratique qui seule va permettre de comprendre
et d'acquérir une certaine maitrise du concept abordé.

/***********************************************************************************
Exercice 1
Afficher avec une fonction récursive tous les nombres entre n et n'
entrés par l'utilisateur.
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
présentées p.456 pour l'analyse descendante, p. 457 pour l'analyse ascendente.
puis de vérifier ensuite si les résultats obtenus sur papier sont correctes.
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
Remplacer les fonctions f(), g(), h() ci-après par des variantes itératives
équivalentes (plus ou moins). Comparer dans chaque cas la quantité de
mémoire utilisée et le temps de calcul nécessaire pour l'une et l'autre
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

/* Place en mémoire ?
L'opérateur sizeof ne permet pas de prendre la place occupée
en mémoire par une fonction.
Mais à priori une version itérative prend moins de place en mémoire
dans la mesure où elle suppose une pile d'appel plus réduite.
En effet chaque nouvel appel de fonction s'ajoute à la pile des appels
et de ce fait une fonction récursive qui est appelée plusieurs fois
augmente la place prise en mémoire.
Tout dépend si la récursivité permet ou pas de réduire le nombre
des ressources nécessaires à l'algorithme.

Temps ?
Il y a des saisies à faire et le temps en dépend aussi. Il sera donc
difficile de comparer de ce point de vue récursif et itératif
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
// solution incomplète :
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
//on est obligé d'implémenter une pile et de stocker
// dedans chaque saisie au fur et à mesure puis d'fficher en
// partant de la dernière.
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
// la suite de fibonacci avec une légère modification au départ

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
Écrire une fonction prenant un argument entier et renvoyant la somme des
chiffres décimaux constituant l'argument. Comparer deux variantes de la
solution à ce problème, l'une récursive et l'autre itérative.
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
Écrire un programme destiné à lire une succession de nombres réels en virgule
flottante et afficher la somme des 1er, 3e, 6e, 10e, 15e (etc.) éléments de
cette suite. Tout caractère non numérique sera interprété comme le signal
d'arrêt de cette suite de nombres.
*********************************************************************************
// exercice identique à l'exercice 7 :
// il s'agit de "nombres triangulaires", une suite due à Pythagore :
// le n-ième nombre triangulaire est la somme des entiers de 1 à n.
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
Exercice 6  : il y a une erreur, l'énoncé est incomplet.
Écrire un programme destiné à lire un chiffre décimal d. Afficher systématiquement
chacun des entiers positifs x inférieurs à 100 qui comportent d pour x et pour x2.

Enoncé complet :
Écrire un programme destiné à lire un chiffre décimal d. Afficher systématiquement
chacun des entiers positifs x inférieurs à 100 présentant la caractéristique de
compter le chiffre d aussi bien dans sa représentation décimale (x) que dans celle
de son carré (x2)
*********************************************************************************
// énoncé ramené à :
// soit d entré par l'utilisateur, trouver et afficher x ou x2 égale à d pour
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
Écrire une fonction récursive qui à partir de n entré par l'utilisateur calcule
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
Écrire une fonction récursive qui à partir de n entré par l'utilisateur calcule
la somme :
un = 1 + 24 + 34 + 44 + .... + n4. (4 est une puissance : voir mise en page énoncé
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
Sur le modèle de la suite de Fibonacci, écrire une fonction récursive pour
calculer la suite à partir de n entré par l'utilisateur : f(n) = n-4 + n-3 + n-2 + n-1.
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
Sur le modèle du calcul factoriel, écrire une fonction récursive qui calcule
la suite pour n entré par l'utilisateur : f(n) = 2*n*n-1 ... pour n>0.
*********************************************************************************
#include <stdio.h>
#include <stdlib.h>

int f(int n)
{
	return (n == 1) ? 2 : n * f(n - 1);

	// équivalent
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
strlen en récursif
Écrire une version récursive de la fonction strlen() qui retourne la longueur
d'une chaîne de caractères donnée en paramètre.
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
	printf("%d\n", strlen("Bonjour")); // pour comparer résultats

	pause();
	return 0;
}

/*********************************************************************************
Exercice 12 :
détecteur de palindrome
Un palindrome est un mot ou une phrase qui se lit aussi bien à l'envers
qu'à l'endroit (sans tenir compte des espaces). Par exemple "radar", "kayak",
"abccba" ou une phrase "esope reste et se repose". La phrase ou le mot sont
entrés par l'utilisateur et une fonction récursive re-tourne si oui ou non
la chaîne de caractères donnée en paramètre est un palindrome.
*********************************************************************************
#include <stdio.h>
#include <string.h>

int palindrome(char*s)
{
	int res = 1;
	int l = strlen(s)-1; // l pointe sur le dernier caractère de la chaine
	if (l > 0) {// si plus d'un caractère dans la chaine

		while (*s == ' ') { // sauter les espaces du début
			s++;
			l--; // ce qui diminue la taille de la chaine
		}
		while (*(s + l) == ' ')// sauter espace fin
			l--;

		if (*s != *(s + l))// comparer premier et dernier caractères
			res = 0; // si différent ce n'est pas un palindrome

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
	//la fonction n'accepte pas de prendre en paramètre une constante
	//chaine de caractères par exemple passer directement "esope reste et se repose"
	//ne fonctionnera pas. En effet la chaine de caractères doit pouvoir être modifiable.

	pause();
	return 0;
}

/*********************************************************************************
Exercice 13 :
parcours systématique d'une matrice
Soit une matrice MAT d'entiers de TX par TX faire le programme qui affiche tous
les chemins directs possibles qui partent de MAT[0][0] pour arriver en MAT[TY-1][TX-1]
sans jamais retourner en arrière ou faire des circuits. C'est-à-dire sur le schéma,
tous les trajets qui peuvent aller directement en avançant ou en descendant de la
case grise en haut à gauche à celle en bas à droite :

L'affichage est soit graphique avec allegro ou conio, soit en texte, le trajet
étant une suite de positions : (0,0)-(0,1)-(0,2)-(...,...)-(TX-1, TY-1).
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
// déjà vues
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
parcours aléatoire d'une matrice
Soit une matrice de TX par TY, écrire une fonction récursive de remplissage aléatoire.
Chaque position ne peut être visitée qu'une fois et sert de départ pour visiter
d'autres positions.
Réaliser un affichage graphique en utilisant les fonctions gotoxy() et textcolor()
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

// remplit la matrice de façon systématique
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
// ça dépend des tirages aléatoires de directions
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

// en combinant les deux on obtient un remplissage systématique
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
dégradé de couleurs dans un carré
On dispose d'une palette de couleurs style arc-en-ciel avec un dégradé de couleurs.
On donne une couleur au hasard à chaque coin A, B, C, D d'un carré tracé à l'écran.
Puis on donne la moyenne de ces quatre couleurs au centre du carré O.

On calcule également les couleurs des points I, J, K, L par moyenne des deux
couleurs voisines. Puis on recommence avec les quatre carrés obtenus, et ainsi de
suite jusqu'à ce que les carrés aient des côtés de l'ordre du pixel.
Réaliser un programme de test de préférence en mode graphique sous allegro.
*********************************************************************************
// Pour simplifier et éviter d'entrer dans un environnement graphique nous allons
// prendre pour image carré une matrice de nombres. La palette de couleur correspondra
// à des valeurs de couleurs entre 0 et 255 bornes comprises. Cette palette suppose
// un dégradé du plus sombre 0 au plus clair 255. L'important est de
// mettre en place un algorithme de répartition de ces nombres et de pouvoir ensuite
// l'observer.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// attention TX-1 et TY-1 doivent être des puissances de 2
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
	// déséquilibrent la répartition en rendant des lignes et des colones inaccessibles
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
tracé de carrés
Au départ on a une position (x,y), par exemple le centre de l'écran et une taille
de segments. Écrire deux fonctions qui tracent récursivement 8 carrés répartis
de façon fractale les uns autour des autres. La première fonction trace ses carrés
à partir d'une taille maximum donnée en entrée et vers l'intérieur. La seconde
fonction trace des carrés de façon extensive, vers l'extérieur jusqu'à atteindre
une taille maximum.
*********************************************************************************
// Dans cet exercice la répartition des carrés peut s'interpréter de différentes
// façons. La plus simple est sans doute de produire des carrés encastrés les uns
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
	// pour bénéficier d'une console plusa grande
	ConsolePosEtSize(0, 0, 150, 40);

	// deux traces de "cibles" carrées
	carre_interieur(8, 10, 15, 15);
	carre_exterieur(10, 1, 40, 15, 1);

	// modification pour tracé aux coins
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
	// controler que le curseur ne sort pas de la fenêtre
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
	// positionne la fenêtre à la position X, Y et prend une nouvelle taille nWidth,
	// nHeight en pixel. Le bool bRepaint donne la possibilité de redessiner le contenu de
	// la fenêtre.

	// Pour éviter des soucis avec le buffer de la console, il plus
	// prudent de redonner une "vraie" taille à la console derrière
	// avec la fonction ConsoleResize()
	MoveWindow(hwnd, x, y, 0, 0, FALSE);
	if (!ConsoleResize(150, 40))
		return FALSE;

	return TRUE;
}
_Bool ConsoleResize(int width, int height)
{
	// récupérer un handle sur la fenêtre concernée
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE)
		return FALSE;

	// récupération des tailles maximum et minimum
	// supportées par la console
	COORD max = GetLargestConsoleWindowSize(h);
	width = (width > max.X) ? max.X : ((width < 1) ? 1 : width);
	height = (height > max.Y) ? max.Y : ((height < 1) ? 1 : height);

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	// si la hauteur  demandée est inférieure à la hauteur
	// actuelle
	if (height < info.dwSize.Y) {

		// diminuer d'abord le rect fenêtre (abs coord)
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		// ensuite le buffer correspondant
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	// si la taille demandée est supérieure à la taille actuelle
	else if (height > info.dwSize.Y) {

		// d'abord augmenter la taille du buffer
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		// ensuite le rectangle correspondant de la fenêtre
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
Écrire une fonction récursive qui permet de tracer une spirale rectangulaire.
Au départ il y a une longueur L pour le premier segment et la taille maximum
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
	// controler que le curseur ne sort pas de la fenêtre
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
	// positionne la fenêtre à la position X, Y et prend une nouvelle taille nWidth,
	// nHeight en pixel. Le bool bRepaint donne la possibilité de redessiner le contenu de
	// la fenêtre.

	// Pour éviter des soucis avec le buffer de la console, il plus
	// prudent de redonner une "vraie" taille à la console derrière
	// avec la fonction ConsoleResize()
	MoveWindow(hwnd, x, y, 0, 0, FALSE);
	if (!ConsoleResize(150, 40))
		return FALSE;

	return TRUE;
}
_Bool ConsoleResize(int width, int height)
{
	// récupérer un handle sur la fenêtre concernée
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	if (h == INVALID_HANDLE_VALUE)
		return FALSE;

	// récupération des tailles maximum et minimum
	// supportées par la console
	COORD max = GetLargestConsoleWindowSize(h);
	width = (width > max.X) ? max.X : ((width < 1) ? 1 : width);
	height = (height > max.Y) ? max.Y : ((height < 1) ? 1 : height);

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	// si la hauteur  demandée est inférieure à la hauteur
	// actuelle
	if (height < info.dwSize.Y) {

		// diminuer d'abord le rect fenêtre (abs coord)
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		// ensuite le buffer correspondant
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	// si la taille demandée est supérieure à la taille actuelle
	else if (height > info.dwSize.Y) {

		// d'abord augmenter la taille du buffer
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		// ensuite le rectangle correspondant de la fenêtre
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