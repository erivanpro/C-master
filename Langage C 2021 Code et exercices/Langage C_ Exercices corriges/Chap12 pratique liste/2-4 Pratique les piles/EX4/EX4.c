/*
Exercice 4
Écrire un programme qui, à l’aide d’une pile, évalue l’expression arithmétique postfixée :
5 11 9 + 2 12 * - 8 / * .
Puis à l’aide d’une autre pile, transformer l’expression postfixée en son expression infixée 
(opérateur entre 2 opérandes le tout entre parenthèses).
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>


void Menu();
float Evaluer(char* expPostfixee);
char* Traduire(char* expPostfixee);

int main()
{
	int fin = 0;
	char Post[] = "5 11 9 + 2 12 * - 8 / *";

	Menu();
	while (fin != 'q') {

		switch (_getch()) {
		case 'a':
			printf("Evaluation de : %s\n", Post);
			printf("res : %.2f\n", Evaluer(Post));
			break;
		case 'z':
		{
			printf("Traduction de : %s\n", Post);
			char* res = Traduire(Post);
			printf("res : %s\n", res);
			free(res);
		}
			break;
		case 'q':
			fin = 'q';
			break;
		}

	}
	return 0;
}
void Menu()
{
	printf("a : Evaluation expression post fixee\n");
	printf("z : Traduction post fixe en infixe\n");
}

/*Attention :
les fonctions Evaluer et Traduire ne sont pas sécurisées. 
Elles supposent chacune une expression correcte  en entrée. Pour 
sécuriser les fonctions il faut essentiellement vérifier le bon  
fonctionnement de chaque pile (sommet doit toujours être compris 
entre 0 et max-1). Le mieux dans cette perspective est de traiter 
le fonctionnement de la pile à part, hors des fonctions. 

Il s'agit ici de montrer le caractère très simple finalement d'une pile
et la possibilité rapide d'en implémenter une.
*/
float Evaluer(char* post)
{
	// la pile (un tableau)
	int max = strlen(post); // cette taille ne pourra jamais être dépassée.
	float *p = (float*)malloc(sizeof(float)* max);
	int sommet = 0;

	// pour calculer
	float v1 = 0;
	float v2 = 0;
	float res = 0;;

	// action
	// pour commencer il faut récupérer les nombres afin de recomposer ensuite les opérations.
	// Les nombres de l'expressions sont considérés comme des nombres entiers uniquement mais 
	// le résultat de l'expression peut être une valeur décimales.

	// Nous ne pouvons pas utiliser sscanf(.., "%d",&val) parce que un opérateur est aussi un 
	// nombre par exemple '+' vaut 43 dans la table acsii. L'utilisation %d pour '+' met 43  
	// dans val et nous ne pouvons pas ensuite différencier 43 le nombre de 43 l'opérateur en 
	// ascii.
	for (int i = 0; post[i] != '\0'; i++) {
		if (isdigit(post[i])) { // récupérer les nombres
			int n;
			for (n = 0; post[i] != ' '; i++) 
				n = n * 10 + (post[i] - '0');
			p[sommet++] = n;   // incrémentation après affectation de n
		}
		// si opérateur faire l'opération et empiler le résultat
		else if(post[i] != ' '){
			// décrémentation avant affectation. attention en cas 
			// d'erreur dans l'expression il est possible de passer 
			// en dessous de 0 et de provoquer une erreur à l'exécution.
			v2 = p[--sommet]; 
			v1 = p[--sommet]; 
			switch (post[i]) {
				case '+': p[sommet++] = v1 + v2; break;
				case '-': p[sommet++] = v1 - v2; break;
				case '*': p[sommet++] = v1 * v2; break;
				case '/': p[sommet++] = v1 / v2; break;
			}
		}
	}
	// Si l'expression est correcte au départ à la fin 
	// ne reste que le résulat dans la pile
	res = p[--sommet];
	free(p);
	return res;
}

char* Traduire(char* expPostFixee)
{
	// faire une copie de l'expression passée avant sa découpe
	int max = strlen(expPostFixee) + 1;
	char* post = (char*)malloc(sizeof(char) * max );
	strcpy_s(post, max, expPostFixee);

	// tableau de char*, taille maximum sur nombre de caractères de l'expression
	char** p = (char**)malloc(sizeof(char*) * strlen(post));
	int sommet = 0;
	char *res = NULL;

	/* La fonction strtok :
	Recherche les mots de la chaine param1 (p1) en prenant comme ensemble 
	de séparateurs les caractères de la chaine param2 (p2). Lors du premier 
	appel la fonction modifie la chaine p1 en déplacant le caractère '\0'
	à la fin du premier mot, et retourne l'adresse de ce mot. Les appels 
	suivants doivent être effectués avec NULL comme premier paramètre, la
	fonction concervant la position courante dans la chaine entre deux appels. 
	Cette position courante est stockée à chaque appel dans le param3 (p3). 
	Lorsqu'il n'y a plus de mot la fonction retourne NULL et p3 vaut NULL.*/

	char* next = NULL;
	char* e = NULL;

	// empiler le premier élément de la chaine post.
	e = strtok_s(post, " ",&next);
	p[sommet++] = e;
 
	do {
		e = strtok_s(NULL, " ", &next);
		if (e != NULL) {

			// si nombre empiler
			if (isdigit(e[0]))
				p[sommet++] = e;

			// si opérateur constituer la chaine en infixé
			else { 
				char* v1, * v2;
				char exp[100] = { 0 };

				v2 = p[--sommet];
				v1 = p[--sommet];

				strcat_s(exp, 100, "(");
				strcat_s(exp, 100, v1);
				strcat_s(exp, 100, e);
				strcat_s(exp, 100, v2);			
				strcat_s(exp, 100, ")");

				res = malloc(sizeof(char) * (strlen(exp) + 1));
				strcpy_s(res, strlen(exp) + 1, exp);
				p[sommet++] = res;
				printf("%s\n", res);
			}
		}
	} while (e != NULL);
	// en principe à la fin le résultat se trouve dans res, au sommet de la pile
	free(p);
	free(post);
	return res;
}