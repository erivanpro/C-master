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

/*
VERSION 3 NOMBRE LIMITE DE VOITURES, CONTROLE DE LA DISTANCE
version plus simple à écrire, moins de risque d'erreur, mais les 
voitures ne sont plus prises en compte lorsque la file est pleine.
*/


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#define DISTANCEMIN	50
#define CARMAX	10
enum { FALSE, TRUE };

typedef struct Car {
	int lettre;
	int distance;
	// etc.
}Car;

typedef struct Queue {
	Car* cars[CARMAX];
	int out;		// tete, premier
	int in;		// queue, dernier
}Queue;

void Menu(void);
// gestion voitures
void ArrivalCar(Queue** q1, Queue** q2);
void MoveCar(Car* v);
_Bool TooNearCar(Car* c);
Car* CreateCar(int lettre, int distance);
void DisplayCar(Car* c);
void DisplayQueueCars(Queue* q, int num);
int Top(int* start, int duree);

// gestion file
Queue* CreateQueue(void);
_Bool EmptyQueue(Queue* q);
_Bool FullQueue(Queue* q);
void Enqueue(Queue** q, Car* v);
Car* Dequeue(Queue* q);
void DestroyQueue(Queue** q);


int main()
{
	int fin = 0;
	Queue* Q1 = NULL;
	Queue* Q2 = NULL;
	Queue* Q3 = NULL;

	srand((unsigned int)time(NULL));

	/*// au la fonction Enqueue() initialise au besoin la file
	// passée en paramètre il est donc inutile de le faire ici
	Q1 = CreateQueue();
	Q2 = CreateQueue();
	Q3 = CreateQueue();*/

	int start = 0;
	Menu();
	while (fin != 'q') {


		// Le défilement contrôlé au clavier (plus facile à voir)
		if (_kbhit()) {
			fin = _getch();

			//avancer voiture file 1
			if (!EmptyQueue(Q1))
				MoveCar(Q1->cars[Q1->out]);

			// arrivées en R1, R2
			if (fin == 'a')
				ArrivalCar(&Q1, &Q2);

			// passages en R3
			else if (fin == 'z') {

				//passage de R1 à R3
				if (!EmptyQueue(Q1) && TooNearCar(Q1->cars[Q1->out])) {
					Enqueue(&Q3, Dequeue(Q1));
				}
				// passage de R2 à R3
				else if (!EmptyQueue(Q2)) {
					Enqueue(&Q3, Dequeue(Q2));
				}
			}
			// Disparition en R3
			else if (fin == 'e') {
				if (!EmptyQueue(Q3))
					free(Dequeue(Q3));
			}
			DisplayQueueCars(Q1, 1);
			DisplayQueueCars(Q2, 2);
			DisplayQueueCars(Q3, 3);
		}
	}
	DestroyQueue(&Q1);
	DestroyQueue(&Q2);
	DestroyQueue(&Q3);
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
void ArrivalCar(Queue** q1, Queue** q2)
{
	static int lettre = 0;
	if (rand() % 2) {
		Enqueue(q1, CreateCar('A'+ lettre++, rand() % (DISTANCEMIN * 2)));
	}

	if (rand() % 2)
		Enqueue(q2, CreateCar('A' + lettre++, 0));

	lettre %= 26;
}
void MoveCar(Car* c)
{
	if (c != NULL)
		c->distance = (c->distance <= 10) ? 0 : c->distance - 10;
}
_Bool TooNearCar(Car* c)
{
	_Bool res = TRUE;
	if (c != NULL)
		res = (c->distance < DISTANCEMIN) ? TRUE : FALSE;
	return res;
}
Car* CreateCar(int lettre, int distance)
{
	Car* c = (Car*)malloc(sizeof(Car));
	if (c) {
		c->lettre = lettre;
		c->distance = distance;
	}
	return c;
}
void DisplayCar(Car * c)
{
	printf("%c%d ", c->lettre, c->distance);
}
void DisplayQueueCars(Queue * q, int num)
{
	printf("R%d : ", num);
	if (!EmptyQueue(q)) {
		// affichage tête jusqu'à queue
		for (int i = q->out; i != q->in; i = (i + 1) % CARMAX)
			DisplayCar(q->cars[i]);
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
/*************************************************************
Gestion File générique
**************************************************************/
Queue* CreateQueue()
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	if (q) {
		// premier entré, premier sorti, first in, first out (FIFO)
		memset(q->cars, 0, sizeof(Car) * CARMAX);
		q->out = 0;  // tête, first
		q->in = 0;	// queue, last
	}
	return q;
}
_Bool EmptyQueue(Queue * q)
{
	return (q == NULL || q->in == q->out);
}
_Bool FullQueue(Queue* q)
{
	return (q != NULL && (q->in + 1)%CARMAX == q->out);
}
void Enqueue(Queue **q, Car * c)  // enfiler
{
	if (*q == NULL)
		*q = CreateQueue();
	if (!FullQueue(*q)) {
		(*q)->cars[(*q)->in] = c;
		(*q)->in = ((*q)->in + 1) % CARMAX;
	}
}
Car* Dequeue(Queue * q) // défiler
{
	Car* c = NULL;
	if (!EmptyQueue(q)) {
		c = q->cars[q->out];
		q->cars[q->out] = NULL; // pas très utile ici, juste par principe
		q->out = (q->out + 1) % CARMAX;
	}
	return c;
}
void DestroyQueue(Queue** q)
{
	if (*q != NULL) {
		while (!EmptyQueue(*q)) {
			Car* c = Dequeue(*q);
			free(c);
		}
		free(*q);
		*q = NULL;
	}
}