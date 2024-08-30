/*
Exercice 14
Le problème de Joséphus Flavius : dans un bureau de recrutement, n personnes
numérotées de 1 à n sont disposées en cercle suivant l'ordre de leur numéro.
Le chef de bureau est au centre, puis se dirige vers la personne n°1.
Sa stratégie est d'éliminer chaque deuxième personne qu'il rencontre en
tournant sur le cercle.La dernière personne restante est embauchée.Par
exemple s'il y a 10 personnes, n = 10, les personnes 2, 4, 6, 8, 10, 3, 7, 1, 9
sont éliminées et la personne restante est le n°5.Écrire un programme de simulation :
1) Pour n entré par l'utilisateur donner le numéro de la personne restante.
2) Au lieu de prendre chaque deuxième personne, généraliser en prenant la k - ème
personne, k entré par l'utilisateur.
Il s'agit de faire une liste circulaire. Chaque élément est une personne (nom, numéro).
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>


typedef struct Person {
	char* nom;
	int num;
	struct Person* suiv;

}Person;

void Menu();
void CreateAllPersons(Person** person);
void DestroyAllPersons(Person** person);
void DisplayAllPersons(Person* person);
Person* CreatePerson(char* nom, int num);
char* CreateNom();
void AddPerson(Person** person, Person* p);
void SuppSuiv(Person** person);
void SuppAllPersons(Person** person, int nb);

int main()
{
	Person* Person = NULL;
	int fin = 0, nb = 0;;

	Menu();
	while (fin != 'q') {

		switch (_getch()) {

			// créer une liste de personnes
		case 'a':
			CreateAllPersons(&Person);
			DisplayAllPersons(Person);
			break;

			// sélectionner 
		case 'z':
			printf("Entrez nombre de suppression par saut : ");
			if (scanf_s("%d", &nb)) 
				SuppAllPersons(&Person, nb);
			DisplayAllPersons(Person);
			break;
		
		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyAllPersons(&Person);
	return 0;
}
void Menu()
{
	printf("a : Creer une liste de personnes\n");
	printf("z : selectionner une personne (Josephus Flavius)\n");
	printf("q : Quitter\n");
}
void CreateAllPersons(Person** person)
{
	int nb = 0;
	printf("Entrer un nombre de personnes : ");
	if (scanf_s("%d", &nb)) {
		if (nb > 0) {
			if (*person != NULL)
				DestroyAllPersons(person);
			while (nb > 0) {
				Person* p = CreatePerson(CreateNom(), nb--);
				AddPerson(person, p);
			}
			// se positionner sur le premier entré
			*person = (*person)->suiv;
		}
	}
}
void DestroyAllPersons(Person** person)
{
	if (*person != NULL) {
		Person* p = (*person)->suiv;
		while (p != *person) {
			Person* sup = p;
			p = p->suiv;
			free(sup);
		}
		free(*person);
		*person = NULL;
	}
}
void DisplayAllPersons(Person* person)
{
	printf("PARTICIPANTS :\n");
	if (person == NULL)
		printf("Aucune personne\n");
	else {
		Person* p = person;
		do {
			printf("%10s, num %d\n", p->nom, p->num);
			p = p->suiv;
		} while (p != person);
	}
}
Person* CreatePerson(char*nom, int num)
{
	Person* p = (Person*)malloc(sizeof(Person));
	if (p) {
		p->nom = nom;
		p->num = num;
		p->suiv = p; // pour liste circulaire
	}
	return p;
}
char* CreateNom() // ici juste pour mémoire 80 char max
{
	char v[7] = "aeiouy";
	char c[19] = "cdfghjklmnprstvwxz";
	
	int nbl = 3 + rand() % 8;
	char* nom = (char*)malloc(nbl + 1);
	if (nom) {
		memset(nom, 0, nbl + 1);
		while (nbl--) {
			if (nbl % 2)
				nom[nbl] = v[rand() % 6];
			else
				nom[nbl] = c[rand() % 18];
		}
	}
	return nom;
}
void AddPerson(Person** person, Person* p)
{
	if (*person == NULL)
		* person = p;
	else {
		p->suiv = (*person)->suiv;
		(*person)->suiv = p;
	}
}
void SuppSuiv(Person**person)
{
	if (*person != NULL && (*person)->suiv !=*person) {// 
		Person* p = (*person)->suiv;
		(*person)->suiv = p->suiv;
		free(p);
	}
}
void SuppAllPersons(Person** person, int nb) 
{
	if (*person != NULL) {
		while (*person != (*person)->suiv) {
			for (int i = 0; i < nb; i++) {
				SuppSuiv(person);
				if (*person == (*person)->suiv)// lorsque dernier trouvé
					return;
			}
			*person = (*person)->suiv; // passer au suivant
		}
	}
}