/*
Exercice 3
Un fichier texte peut contenir des parenthèses( ), des crochets [ ] et des accolades { }. 
Ces éléments peuvent être imbriqués les uns dans les autres, par exemple : { a(bc[d])[{ef}(g)]}. 
Écrire une fonction qui parcourt le fichier texte et détermine si le fichier est correctement structuré. 
À savoir, parenthèses, crochets et accolades doivent être correctement refermés et imbriqués. 
Par exemple ({]}) et ({)} ne sont pas corrects mais {[()]} et {(([]))} sont corrects.

*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

typedef struct Elem
{
	int val;
	struct Elem* suiv;
}Elem;

void Menu();
void VerifierFichier(Elem** pile, char* name);
Elem* CreateElem(int val);
_Bool PileVide(Elem* pile);
void EmpilerElem(Elem** sommet, Elem* e);
Elem* DepilerElem(Elem** sommet);
void DisplayPile(Elem* sommet);
void DestroyPile(Elem** sommet);

int main()
{
	int fin = 0;
	Elem* Pile = NULL;
	srand((unsigned int)time(NULL));

	Menu();
	while (fin != 'q') {
		switch (_getch()) {
		case 'a': // créer la pile 1
			if (!PileVide(Pile))
				DestroyPile(&Pile);
			VerifierFichier(&Pile, "Test1.txt");
			break;

		case 'z':		// créer la pile 2
			if (!PileVide(Pile))
				DestroyPile(&Pile);
			VerifierFichier(&Pile, "Test2.txt");
			break;
		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyPile(&Pile);
	return 0;
}
void Menu()
{
	printf("a : test fichier 1\n");
	printf("z : test fichier 2\n");
	printf("q : Quitter\n\n");
}
void VerifierFichier(Elem **pile, char* name)
{
	FILE* f = NULL;
	
	fopen_s(&f, name, "r");
	if (f != NULL) {
		while (!feof(f)) {
			char courant = fgetc(f);
			if (courant == '{' || courant == '(' || courant == '[') {
				EmpilerElem(pile, CreateElem(courant));
			}
			else if ( courant == '}' || courant == ')' || courant == ']') {
				if (*pile != NULL ) {
					char sommet = (*pile)->val; // récupère la valeur au sommet de la pile
					if ((sommet == '{' && courant == '}') ||
						(sommet == '(' && courant == ')') ||
						(sommet == '[' && courant == ']')) {
						printf("%cok%c\n", sommet,courant);
						free(DepilerElem(pile));
					}
					else
						printf("erreur : %c+%c\n", sommet, courant);
				}
				else
					printf("erreur : vide+%c\n", courant);
			}
		}
		/*Remarque :
		En cas d'erreur il n'y a pas dépilement et le nombre total des éléments restants 
		dans la pile peut être supérieur au nombre total d'erreurs. La correspondance 
		entre {}, (), [] se trouve décalée et c'est seulement à la fin lorsque la pile 
		s'avère non vide (s'il manque une fermeture) ou au contraire si la pile est vide 
		(s'il manque une ouverture) que le décalage est constaté et l'erreur déduite.
		D'ailleurs en général pour un fichier de code source c l'oubli ou l'effacement  
		d'une { ou } peut s'avérer difficile à localiser dans le code.

		L'algorithme ici vérifie bien la symétrie entre ouverture pour {,[,(, et fermetures },],). 
		
		*/
		if (!PileVide(*pile)) {
			printf("Erreur : ");
			DisplayPile(*pile);
		}
		printf("end\n");
		fclose(f);
	}
	else
		printf("probleme ouverture fichier\n");
}
Elem* CreateElem(int val)
{
	Elem* e = (Elem*)malloc(sizeof(Elem));
	if (e) {
		e->val = val;
		e->suiv = NULL;
	}
	return e;
}
_Bool PileVide(Elem* pile)
{
	return pile == NULL;
}
void EmpilerElem(Elem **sommet, Elem * e)  // empiler
{
	if (*sommet == NULL)
		*sommet = e;
	else {
		e->suiv = *sommet;
		*sommet = e;
	}
}
Elem* DepilerElem(Elem **sommet) // dépiler
{
	Elem* e = NULL;
	if (*sommet != NULL) {
		e = *sommet;
		*sommet = (*sommet)->suiv;
		e->suiv = NULL;  // attention ! ne pas oublier
	}
	return e;
}
void DisplayPile(Elem * sommet)
{
	if (sommet == NULL)
		printf("liste vide\n");
	else {
		while (sommet != NULL) {
			printf("%c ", sommet->val);
			sommet = sommet->suiv;
		}
		putchar('\n');
	}
}
void DestroyPile(Elem **sommet)
{
	while (*sommet != NULL) {
		Elem* e = DepilerElem(sommet);
		free(e);
	}
	*sommet = NULL;
}