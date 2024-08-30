/*Exercice 3
Pour simuler un croisement routier, à sens unique, on utilise 3 files f1, f2 et f3 représentant respectivement 
les voitures arrivant sur les routes R1 et R2, et les voitures partant sur la route R3. La route R2 a un STOP, 
les voitures de la file f2 ne peuvent avancer que s’il n’y a au-cune voiture sur la route R1, donc dans la file f1.
 
L’algorithme de simulation utilisera une boucle sans fin.
À chaque itération, il sera fait un appel à la procédure arrivée(f1, f2) qui simule l’arrivée d’une ou 
plusieurs voitures des files f1 et f2, modifiant ainsi leur état en mémoire.
– Si l'on considère que les files sont infinies, quelle structure de données choisir ?
– Admettons que les files ne sont pas infinies. La taille de nos files est limitée à 
  une variable MAX saisie par l’utilisateur et symbolisant le maximum de voitures que peut 
  accueillir une route et la procédure arrivée(f1, f2) prend en compte cette nouvelle hypothèse.

  Programmer une simulation.
Nous ajoutons maintenant une nouvelle hypothèse à notre problème : le STOP est respecté mais la 
voiture de la route R2 peut être prioritaire par rapport à la route R1. C'est-à-dire que si la 
distance entre la première voiture de la route R1 et le croisement est jugée suffisante par votre 
simulateur, on préférera défiler f2 plutôt que f1. La vitesse des voitures est jugée constante.

Modifier le programme précédent en ajoutant cette précision.
*/

// VERSION 1 : SANS CONTROLE DE LA DISTANCE ET AVEC NOMBRE ILLIMITE DE VOITURES

// REMARQUE :
// La version 3 avec un nombre limité de voiture et sans pile générique
// est plus simple à écrire, peut-être plus facile à comprendre pour
// commencer.

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>


enum { FALSE, TRUE };

typedef struct Voiture {
	int lettre;
	
	// etc.
}Voiture;


// File générique qui peut contenir n'importe quelle type de structure
typedef struct Elem {
	void* data;		// pointera sur des données, Client ou autre 
	struct Elem* suiv;
}Elem;

typedef struct Queue {
	Elem* out;		// tete, premier
	Elem* in;		// queue, dernier
}Queue;

void Menu(void);
// gestion voitures
void ArriveeVoitures(Queue** Q1, Queue** Q2);
Voiture* CreateVoiture(int lettre);
void DisplayVoiture(Voiture* c);
void DisplayQueueVoiture(Queue* q, int num);
int Top(int* start, int duree);
void ClearVoiture(Voiture* c);
void ClearAllVoitures(Queue* q);
void DestroyAllQueueVoiture(Queue** q);

// gestion file
Queue* CreateQueue(void);
Elem* CreateElem(void* data);
_Bool EmptyQueue(Queue* f);
void EnqueueElem(Queue** f, Elem* e);
Elem* DequeueElem(Queue* f);


int main()
{
	int fin = 0;
	Queue* Q1 = NULL;
	Queue* Q2 = NULL;
	Queue* Q3 = NULL;

	srand((unsigned int)time(NULL));

	int start = 0;
	Menu();
	while (fin != 'q') {
		
		// Le défilement est contrôlé au clavier (plus facile à voir)
		if (_kbhit()) {
			fin = _getch();

			// arrivées en R1, R2
			if (fin == 'a') 
				ArriveeVoitures(&Q1, &Q2);
				
			// passages en R3
			else if (fin == 'z') {
				
				//passage de R1 à R3
				if (!EmptyQueue(Q1)) {
					EnqueueElem(&Q3, DequeueElem(Q1));
				}
				// passage de R2 à R3
				else if (!EmptyQueue(Q2)) {
					EnqueueElem(&Q3, DequeueElem(Q2));
				}
			}
			// Disparition en R3
			else if(fin =='e'){
				if (!EmptyQueue(Q3))
					free(DequeueElem(Q3));
			}
			DisplayQueueVoiture(Q1, 1);
			DisplayQueueVoiture(Q2, 2);
			DisplayQueueVoiture(Q3, 3);
		}
	}
	DestroyAllQueueVoiture(&Q1);
	DestroyAllQueueVoiture(&Q2);
	DestroyAllQueueVoiture(&Q3);
	return 0;
}
void Menu()
{
	printf("SI CONTROLE MANUEL :\n");
	printf("a : Arrivee voitures\n");
	printf("z : Passages R1 ou R2 vers R3\n");
	printf("e : Retirer une voiture de la file R3 \n");
	printf("q : Quitter\n");
}
/*************************************************************
Gestion voitures
**************************************************************/
void ArriveeVoitures(Queue** q1, Queue** q2)
{
	static int lettre = 'A';
	if (rand() % 2)
		EnqueueElem(q1, CreateElem(CreateVoiture(lettre++)));
		
	if (rand() % 2)
		EnqueueElem(q2, CreateElem(CreateVoiture(lettre++)));

	lettre %= ('A' + 26);
}

Voiture* CreateVoiture(int lettre)
{
	Voiture* v = (Voiture*)malloc(sizeof(Voiture));
	if (v) {
		v->lettre = lettre;
	}
		
	return v;
}
void DisplayVoiture(Voiture * v)
{
	printf("%c", v->lettre);
}
void DisplayQueueVoiture(Queue * q, int num)
{
	printf("R%d : ", num);
	if (!EmptyQueue(q)) {
		// affichage tête jusqu'à queue
		Elem* e = q->out;
		if (e != NULL) {
			
			while (e != NULL) {
				DisplayVoiture((Voiture*)e->data);
				e = e->suiv;
			}
		}
		else
			printf("-");
	}
	else
		printf("-");
	putchar('\n');
}
int Top(int* start, int duree)
{
	int res = FALSE;
	if (clock() > * start + duree) {
		*start = clock();
		res = TRUE;
	}
	return res;
}
// les fonctions de désallocation implique la suppression des clients
// en plus de celles des éléments de la file et de la file, du coup
// elles ne sont que partiellement génériques
void ClearVoiture(Voiture * v)
{
	if (v != NULL) {
		free(v);
	}
}
void ClearAllVoitures(Queue * q)
{
	if (q != NULL) {
		while (q->out != NULL) {
			Elem* e = q->out;
			q->out = q->out->suiv;
			ClearVoiture((Voiture*)e->data);
			free(e);
		}
		q->out = NULL;
		q->in = NULL;
	}
}
void DestroyAllQueueVoiture(Queue **q)
{
	if (!EmptyQueue(*q)) {
		ClearAllVoitures(*q);
		free(*q);
		*q = NULL;
	}
}

/*************************************************************
Gestion File générique
**************************************************************/
Queue* CreateQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (q) {
		// premier entré, premier sorti, first in, first out (FIFO)
		q->out = NULL;  // tête, first
		q->in = NULL;	// queue, last
	}
	return q;
}
Elem* CreateElem(void* data)
{
	Elem* e = (Elem*)malloc(sizeof(Elem));
	if (e) {
		e->data = data;
		e->suiv = NULL;
	}
	return e;
}
_Bool EmptyQueue(Queue * q)
{
	return (q != NULL && (q->out != NULL)) ? FALSE : TRUE;
}
void EnqueueElem(Queue **q, Elem * e)  // enfiler
{
	if (e != NULL) {
		//si la file n'existe pas la créer
		if (*q == NULL)
			*q = CreateQueue();
		// si elle est vide 
		if ((*q)->out == NULL)
			(*q)->out = (*q)->in = e;
		// si elle n'est pas vide ajout en fin de file
		else { 
			(*q)->in->suiv = e;
			(*q)->in = e;
		}
	}
}
Elem* DequeueElem(Queue * f) // défiler
{
	Elem* e = NULL;
	if (!EmptyQueue(f)) {
		e = f->out;
		f->out = f->out->suiv;
		e->suiv = NULL; // attention

		// attention lors de la suppression du dernier out ET in doivent être à null
		if (f->out == NULL)
			f->in = NULL;
	}
	return e;
}