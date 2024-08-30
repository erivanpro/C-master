/*Exercice 3
Pour simuler un croisement routier, � sens unique, on utilise 3 files f1, f2 et f3 repr�sentant respectivement 
les voitures arrivant sur les routes R1 et R2, et les voitures partant sur la route R3. La route R2 a un STOP, 
les voitures de la file f2 ne peuvent avancer que s�il n�y a au-cune voiture sur la route R1, donc dans la file f1.
 
L�algorithme de simulation utilisera une boucle sans fin.
� chaque it�ration, il sera fait un appel � la proc�dure arriv�e(f1, f2) qui simule l�arriv�e d�une ou 
plusieurs voitures des files f1 et f2, modifiant ainsi leur �tat en m�moire.
� Si l'on consid�re que les files sont infinies, quelle structure de donn�es choisir ?
� Admettons que les files ne sont pas infinies. La taille de nos files est limit�e � 
  une variable MAX saisie par l�utilisateur et symbolisant le maximum de voitures que peut 
  accueillir une route et la proc�dure arriv�e(f1, f2) prend en compte cette nouvelle hypoth�se.

  Programmer une simulation.
Nous ajoutons maintenant une nouvelle hypoth�se � notre probl�me : le STOP est respect� mais la 
voiture de la route R2 peut �tre prioritaire par rapport � la route R1. C'est-�-dire que si la 
distance entre la premi�re voiture de la route R1 et le croisement est jug�e suffisante par votre 
simulateur, on pr�f�rera d�filer f2 plut�t que f1. La vitesse des voitures est jug�e constante.

Modifier le programme pr�c�dent en ajoutant cette pr�cision.
*/

// VERSION 1 : SANS CONTROLE DE LA DISTANCE ET AVEC NOMBRE ILLIMITE DE VOITURES

// REMARQUE :
// La version 3 avec un nombre limit� de voiture et sans pile g�n�rique
// est plus simple � �crire, peut-�tre plus facile � comprendre pour
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


// File g�n�rique qui peut contenir n'importe quelle type de structure
typedef struct Elem {
	void* data;		// pointera sur des donn�es, Client ou autre 
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
		
		// Le d�filement est contr�l� au clavier (plus facile � voir)
		if (_kbhit()) {
			fin = _getch();

			// arriv�es en R1, R2
			if (fin == 'a') 
				ArriveeVoitures(&Q1, &Q2);
				
			// passages en R3
			else if (fin == 'z') {
				
				//passage de R1 � R3
				if (!EmptyQueue(Q1)) {
					EnqueueElem(&Q3, DequeueElem(Q1));
				}
				// passage de R2 � R3
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
		// affichage t�te jusqu'� queue
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
// les fonctions de d�sallocation implique la suppression des clients
// en plus de celles des �l�ments de la file et de la file, du coup
// elles ne sont que partiellement g�n�riques
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
Gestion File g�n�rique
**************************************************************/
Queue* CreateQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (q) {
		// premier entr�, premier sorti, first in, first out (FIFO)
		q->out = NULL;  // t�te, first
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
		//si la file n'existe pas la cr�er
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
Elem* DequeueElem(Queue * f) // d�filer
{
	Elem* e = NULL;
	if (!EmptyQueue(f)) {
		e = f->out;
		f->out = f->out->suiv;
		e->suiv = NULL; // attention

		// attention lors de la suppression du dernier out ET in doivent �tre � null
		if (f->out == NULL)
			f->in = NULL;
	}
	return e;
}