/*
Exercice 4
�crire un programme qui, � l�aide d�une pile, �value l�expression arithm�tique postfix�e :
5 11 9 + 2 12 * - 8 / * .
Puis � l�aide d�une autre pile, transformer l�expression postfix�e en son expression infix�e 
(op�rateur entre 2 op�randes le tout entre parenth�ses).
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
les fonctions Evaluer et Traduire ne sont pas s�curis�es. 
Elles supposent chacune une expression correcte  en entr�e. Pour 
s�curiser les fonctions il faut essentiellement v�rifier le bon  
fonctionnement de chaque pile (sommet doit toujours �tre compris 
entre 0 et max-1). Le mieux dans cette perspective est de traiter 
le fonctionnement de la pile � part, hors des fonctions. 

Il s'agit ici de montrer le caract�re tr�s simple finalement d'une pile
et la possibilit� rapide d'en impl�menter une.
*/
float Evaluer(char* post)
{
	// la pile (un tableau)
	int max = strlen(post); // cette taille ne pourra jamais �tre d�pass�e.
	float *p = (float*)malloc(sizeof(float)* max);
	int sommet = 0;

	// pour calculer
	float v1 = 0;
	float v2 = 0;
	float res = 0;;

	// action
	// pour commencer il faut r�cup�rer les nombres afin de recomposer ensuite les op�rations.
	// Les nombres de l'expressions sont consid�r�s comme des nombres entiers uniquement mais 
	// le r�sultat de l'expression peut �tre une valeur d�cimales.

	// Nous ne pouvons pas utiliser sscanf(.., "%d",&val) parce que un op�rateur est aussi un 
	// nombre par exemple '+' vaut 43 dans la table acsii. L'utilisation %d pour '+' met 43  
	// dans val et nous ne pouvons pas ensuite diff�rencier 43 le nombre de 43 l'op�rateur en 
	// ascii.
	for (int i = 0; post[i] != '\0'; i++) {
		if (isdigit(post[i])) { // r�cup�rer les nombres
			int n;
			for (n = 0; post[i] != ' '; i++) 
				n = n * 10 + (post[i] - '0');
			p[sommet++] = n;   // incr�mentation apr�s affectation de n
		}
		// si op�rateur faire l'op�ration et empiler le r�sultat
		else if(post[i] != ' '){
			// d�cr�mentation avant affectation. attention en cas 
			// d'erreur dans l'expression il est possible de passer 
			// en dessous de 0 et de provoquer une erreur � l'ex�cution.
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
	// Si l'expression est correcte au d�part � la fin 
	// ne reste que le r�sulat dans la pile
	res = p[--sommet];
	free(p);
	return res;
}

char* Traduire(char* expPostFixee)
{
	// faire une copie de l'expression pass�e avant sa d�coupe
	int max = strlen(expPostFixee) + 1;
	char* post = (char*)malloc(sizeof(char) * max );
	strcpy_s(post, max, expPostFixee);

	// tableau de char*, taille maximum sur nombre de caract�res de l'expression
	char** p = (char**)malloc(sizeof(char*) * strlen(post));
	int sommet = 0;
	char *res = NULL;

	/* La fonction strtok :
	Recherche les mots de la chaine param1 (p1) en prenant comme ensemble 
	de s�parateurs les caract�res de la chaine param2 (p2). Lors du premier 
	appel la fonction modifie la chaine p1 en d�placant le caract�re '\0'
	� la fin du premier mot, et retourne l'adresse de ce mot. Les appels 
	suivants doivent �tre effectu�s avec NULL comme premier param�tre, la
	fonction concervant la position courante dans la chaine entre deux appels. 
	Cette position courante est stock�e � chaque appel dans le param3 (p3). 
	Lorsqu'il n'y a plus de mot la fonction retourne NULL et p3 vaut NULL.*/

	char* next = NULL;
	char* e = NULL;

	// empiler le premier �l�ment de la chaine post.
	e = strtok_s(post, " ",&next);
	p[sommet++] = e;
 
	do {
		e = strtok_s(NULL, " ", &next);
		if (e != NULL) {

			// si nombre empiler
			if (isdigit(e[0]))
				p[sommet++] = e;

			// si op�rateur constituer la chaine en infix�
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
	// en principe � la fin le r�sultat se trouve dans res, au sommet de la pile
	free(p);
	free(post);
	return res;
}