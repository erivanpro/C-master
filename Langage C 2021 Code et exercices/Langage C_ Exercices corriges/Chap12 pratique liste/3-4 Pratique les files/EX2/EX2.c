/*Exercice 2
Dans une gare un guichet est ouvert. Les clients arrivent à des dates aléatoires et font la queue. 
L'intervalle entre l'arrivée de deux clients successifs est un nombre aléatoire entre 0 et INTERVAL_MAX 
en secondes ou en minutes. Lorsque le guichetier a fini avec un client, il appelle le client suivant et 
le traitement a une durée entre 0 et DUREE_TRAITEMENT_MAX.
Écrire un programme de simulation.
*/

/*Pour changer ici nous allons implémenter une file générique. 
L'intérêt est de dissocier le mécanisme de la file du contenu des données d'un client.
Un client devient un élement distinct de la file, il ne contient pas la file en lui-même.
L'approche générique permet de la sorte d'associer un client à d'autres traitements  
une pile, une liste chainée symétrique, un arbre etc., sans pour autant ajouter des 
données à la structure interne d'un client. Ces mécanismes dissociés du client lui 
deviennent externes.

*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

#define INTERVAL_MAX			1000
#define DUREE_TRAITEMENT_MAX	1100
enum { FALSE, TRUE };

typedef struct Client{
	char*name;
	int age;
	int num;
}Client;


// File générique qui peut contenir n'importe quelle type de structure
typedef struct Elem {
	void* data;		// pointera sur des données, Client ou autre 
	struct Elem* suiv;
}Elem;

typedef struct Queue {
	Elem* out;		// tete, premier
	Elem* in;		// queue, dernier
}Queue;

// gestion client
Client* CreateClient(char* name, int age);
char* CreateName();
void DisplayClient(Client* c);
void DisplayQueueClient(Queue* f);
int Top(int* start, int duree);
void ClearClient(Client* c);
void ClearAllClients(Queue* q);
void DestroyAllQueueClient(Queue** q);

// gestion file
Queue* CreateQueue();
Elem* CreateElem(void* data);
_Bool EmptyQueue(Queue* f);
void EnqueueElem(Queue** f, Elem* e);
Elem* DequeueElem(Queue* f);


int main()
{
	int fin = 0;
	Queue* Q = NULL;

	srand((unsigned int)time(NULL));
	
	Q = CreateQueue();
	int in = 0, out = 0, num=0;
	int tmpIn = 0, tmpOut = 0;
	while (fin != 'q') {
		
		if (_kbhit())
			fin = 'q';

		if (Top(&tmpIn, in)) {
			EnqueueElem(&Q, CreateElem(CreateClient(CreateName(), 10 + rand() % 100)));
			DisplayQueueClient(Q);
			in = rand() % INTERVAL_MAX;
		}
		if (Top(&tmpOut, out)) {
			Elem* e = DequeueElem(Q);
			if (e != NULL) {
				DisplayClient((Client*)e->data);
				printf("sort\n");
				ClearClient((Client*)e->data);
				free(e);
			}
			out = rand() % DUREE_TRAITEMENT_MAX;
		}
	}
	DestroyAllQueueClient(&Q);
	return 0;
}

/*************************************************************
Gestion client
**************************************************************/
Client* CreateClient(char*name, int age)
{
	Client* c = (Client*)malloc(sizeof(Client));
	if (c) {
		c->age = age;
		c->name = name;
	}
	return c;
}

char* CreateName() 
{
	char buf[80];
	char v[7] = "aeiouy";
	char c[19] = "cdfghjklmnprstvwxz";
	memset(buf, 0, sizeof(char) * 80);

	int nbl = 3 + rand() % 9;
	while (nbl--) {
		if (nbl % 2)
			buf[nbl] = v[rand() % 6];
		else
			buf[nbl] = c[rand() % 18];
	}
	char* name = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
	if (name)
		strcpy_s(name, strlen(buf) + 1, buf);
	return name;
}
void DisplayClient(Client* c)
{
	printf("%s %d ans|",c->name,c->age);
}
void DisplayQueueClient(Queue* f)
{
	if (!EmptyQueue(f)) {
		// affichage tête jusqu'à queue
		Elem* e = f->out;
		if (e != NULL) {
			while (e != NULL) {
				DisplayClient((Client*)e->data);
				e = e->suiv;
			}
		}
		else
			printf("file vide");
	}
	else
		printf("pas de file");
	putchar('\n');
}
int Top(int *start, int duree)
{
	int res = FALSE;
	if (clock() > *start + duree) {
		*start = clock();
		res = TRUE;
	}
	return res;
}
// les fonctions de désallocation implique la suppression des clients
// en plus de celles des éléments de la file et de la file, du coup
// elles ne sont que partiellement génériques
void ClearClient(Client* c)
{
	if (c != NULL) {
		free(c->name);
		free(c);
	}
}
void ClearAllClients(Queue* q)
{
	if (q != NULL) {
		while (q->out != NULL) {
			Elem* e = q->out;
			q->out = q->out->suiv;
			ClearClient((Client*)e->data);
			free(e);
		}
		q->out = NULL;
		q->in = NULL;
	}
}
void DestroyAllQueueClient(Queue** q)
{
	if (!EmptyQueue(*q)) {
		ClearAllClients(*q);
		free(*q);
		*q = NULL;
	}
}

/*************************************************************
Gestion File générique
**************************************************************/
Queue* CreateQueue()
{
	Queue* f = (Queue*)malloc(sizeof(Queue));
	if (f) {
		// premier entré, premier sorti, first in, first out (FIFO)
		f->out = NULL;  // tête, first
		f->in = NULL;	// queue, last
	}
	return f;
}
Elem* CreateElem(void*data)
{
	Elem* e = (Elem*)malloc(sizeof(Elem));
	if (e) {
		e->data = data;
		e->suiv = NULL;
	}
	return e;
}
_Bool EmptyQueue(Queue* f)
{
	return (f != NULL && (f->out != NULL)) ? FALSE : TRUE;
}
void EnqueueElem(Queue * *f, Elem * e)  // enfiler
{
	if (e != NULL) {
		if (*f == NULL)
			* f = CreateQueue();
		if ((*f)->out == NULL)
			(*f)->out = (*f)->in = e;
		else { // ajout en fin de file
			(*f)->in->suiv = e;
			(*f)->in = e;
		}
	}
}
Elem* DequeueElem(Queue * f) // défiler
{
	Elem* e = NULL;
	if (!EmptyQueue(f)) {
		e = f->out;
		f->out = f->out->suiv;
	}
	return e;
}


