/*Exercice 1
Donner le contenu de la file pour chaque opération de la suite : Q*UES***TI*ON*FAC***IL***E**.
Chaque lettre provoque un enfilement et chaque astérisque un défilement.
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>

enum { FALSE, TRUE };

typedef struct Elem{
	int val;
	struct Elem* suiv;
}Elem;

typedef struct Queue {
	Elem* out;	  // tete, premier
	Elem* in;    // queue, dernier
}Queue;

void Menu();
int SaisieNombre(char* msg);
Queue* CreateQueueNbElem();
Queue* CreateQueue();
Elem* CreateElem(int val);
_Bool EmptyQueue(Queue* f);
void EnqueueElem(Queue** f, Elem* e);
Elem* DequeueElem(Queue* f);
void DisplayQueueVal(Queue* f);
void DisplayQueueChar(Queue* f);
void DestroyQueue(Queue** f);
void ClearQueue(Queue* f);
void CheckQueue(Queue** f, char* instructions);


int main()
{
	int fin = 0;
	Queue*Q = NULL;
	char* instructions1 = "Q*UES***TI*ON*FAC***IL***E**";
	char* instructions2 = "EAS*Y*QUE***ST***IO*N***";
	int cmpt = 0;

	srand((unsigned int)time(NULL));
	Menu();
	while (fin != 'q') {
		switch (_getch()) {

			// Tester fonctionnement de la file la file
		case 'a': 	
			EnqueueElem(&Q, CreateElem(cmpt++));
			DisplayQueueVal(Q);
			break;
		case 'z':
		{
			Elem* e = DequeueElem(Q);
			DisplayQueueVal(Q);
			break;
		}
		// résultat suite commande 1
		case 'e': 
			printf("Result pour Q*UES***TI*ON*FAC***IL***E** :\n");
			if (!EmptyQueue(Q))
				DestroyQueue(&Q);
			CheckQueue(&Q, instructions1);
			break;

		// résultat suite commande 2
		case 'r':
			printf("Result pour EAS*Y*QUE***ST***IO*N*** :\n");
			if (!EmptyQueue(Q))
				DestroyQueue(&Q);
			CheckQueue(&Q, instructions2);
			break;

		case 'q':
			fin = 'q';
			break;
		}
	}
	DestroyQueue(&Q);
	return 0;
}
void Menu()
{
	printf("a : ajouter element (enfiler)\n");
	printf("z : retirer element (defiler)\n");
	printf("e : resultat premiere chaine de commandes\n");
	printf("r : resultat seconde chaine de commandes\n");
	printf("q : Quitter\n");
}

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

Elem* CreateElem(int val)
{
	Elem* e = (Elem*)malloc(sizeof(Elem));
	if (e) {
		e->val = val;
		e->suiv = NULL;
	}
	return e;
}
_Bool EmptyQueue(Queue* f)
{
	return (f != NULL && (f->out != NULL)) ? FALSE : TRUE;
}
void EnqueueElem( Queue**f, Elem * e)  // enfiler
{
	if (e != NULL) {
		if (*f==NULL) 
			*f = CreateQueue();
		if ((*f)->out == NULL)
			(*f)->out = (*f)->in = e;
		else { // ajout en fin de file
			(*f)->in->suiv = e;
			(*f)->in = e;
		}
	}
}
Elem* DequeueElem( Queue*f) // défiler
{
	Elem* e = NULL;
	if (!EmptyQueue(f)) {
		e = f->out;
		f->out = f->out->suiv;
	}
	return e;
}
void DisplayQueueVal(Queue* f)
{
	if (!EmptyQueue(f)) {
		// affichage tête jusqu'à queue
		Elem* e = f->out;
		if (e != NULL) {
			printf("<-OUT");
			while (e != NULL) {
				printf("<-%d", e->val);
				e = e->suiv;
			}
			printf("<-IN");
		}
		else
			printf("file vide");
	}
	else
		printf("pas de file");
	putchar('\n');
}
void DisplayQueueChar(Queue*f )
{
	if (!EmptyQueue(f)) {
		// affichage tête jusqu'à queue
		Elem* e = f->out;
		if (e != NULL) {
			printf("<-OUT");
			while (e != NULL) {
				printf("<-%c", (char)e->val);
				e = e->suiv;
			}
			printf("<-IN");
		}
		else
			printf("file vide");
	}
	else
		printf("pas de file");
	putchar('\n');
}
// pour désallouer entièrement la file si elle est de type dynamique (File*)
void DestroyQueue( Queue**f)
{
	if (!EmptyQueue(*f)) {
		ClearQueue(*f);
		free(*f);
		*f = NULL;
	}
}
// sinon pour juste pour supprimer les éléments de la file (Elem*out et *in)
void ClearQueue(Queue* f)
{
	if (f != NULL) {
		while (f->out != NULL) {
			Elem* e = f->out;
			f->out = f->out->suiv;
			free(e);
		}
		f->out = NULL;
		f->in = NULL;
	}
}
void CheckQueue(Queue**f, char* instructions)
{
	for (int i = 0; instructions[i] != '\0'; i++) {
		if (instructions[i] != '*')
			EnqueueElem(f, CreateElem(instructions[i]));
		else
			free(DequeueElem(*f));
		// pour voir les étapes intermédiaires en caractères
		DisplayQueueChar(*f);
	}
}