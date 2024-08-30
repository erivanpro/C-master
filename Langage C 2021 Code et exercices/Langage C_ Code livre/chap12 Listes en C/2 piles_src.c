/********************************************************************
*                                                                   *
*       CHAPITRE 12 : 2. PILES                                       *
*                                                                   *
*********************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de préférence vide sous visual studio)
    - copier toute la page dans le fichier C du nouveau projet (écraser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte immédiatement ajouter
      getchar(); avant le return 0; de fin de main()
    - remettre les commentaires pour tester un autre programme
*/
/************************************************************
*                                                           *
*       2.2 Implémentation d'une pile en dynamique          *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Structure de données
#define NOMMAX  80
typedef struct elem {
    int val;
    char s[NOMMAX];

    struct elem* suiv;
}t_elem;

char* S[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

// Pile vide, pile pleine
_Bool pile_vide(t_elem* tete)
{
    return (tete == NULL);
}

// Initialisation un élément
t_elem* init_elem(int val, char s[])
{
    t_elem* e;
    e = (t_elem*)malloc(sizeof(t_elem));
    e->val = val;
    strcpy_s(e->s, NOMMAX, s);
    e->suiv = NULL;
    return e;
}

// Empiler
void empiler(t_elem** p, t_elem* e)
{
    e->suiv = *p;
    *p = e;
}

//Dépiler
t_elem* depiler(t_elem** p)
{
    t_elem* e = NULL;

    if (!pile_vide(*p)) {
        e = *p;
        *p = (*p)->suiv;
    }
    return e;
}

//Vider, détruire
void detruire_pile(t_elem** p)
{
    t_elem* e;
    while (!pile_vide(*p)) {
        e = depiler(p);
        free(e);
    }
    *p = NULL;
}

//Affichage
void affiche_elem(t_elem* e)
{
    if (e != NULL)
        printf("%d%s", e->val, e->s);
    else
        printf("pas d'element a aficher");
    putchar('\n');
}

void affiche_pile(t_elem* p)
{
    if (p == NULL)
        printf("pile vide");
    while (p != NULL) {
        printf("%d%s--", p->val, p->s);
        p = p->suiv;
    }
    putchar('\n');
}

//Test dans le main()
int menu()
{
    int res = -1;
    printf("1  : empiler \n"
        "2  : depiler \n"
        "3  : detruire pile\n"
    );
    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}

int main()
{
    int fin = 0, id = 0;
    t_elem* e, * p = NULL;

    srand((unsigned)time(NULL));
    while (!fin) {
        switch (menu()) {
        case 1:
            e = init_elem(rand() % 26, S[(id++) % 26]);
            empiler(&p, e);
            break;

        case 2:
            e = depiler(&p);
            affiche_elem(e);
            break;

        case 3:
            detruire_pile(&p);
            break;

        default:
            fin = 1;
            detruire_pile(&p);
        }
        affiche_pile(p);
    }
    return 0;
}
*/
/****************************************************************
*                                                               *
*       2.3 Implémentation d'une pile en statique (tableau)     *
*                                                               *
*****************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Structure de données
#define NBMAX  16    // la taille du bloc
typedef struct pile {
    int n;            // le sommet
    void* t[NBMAX];  // le bloc pour la pile
}t_pile;

#define NOMMAX  80
typedef struct elem {
    int val;
    char s[NOMMAX];
}t_elem;

char* S[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

//Initialisation
t_pile* init_pile()
{
    t_pile* p;
    p = (t_pile*)malloc(sizeof(t_pile));
    p->n = 0;
    return p;
}

t_elem* init_elem(int val, char s[])
{
    t_elem* e;
    e = (t_elem*)malloc(sizeof(t_elem));
    e->val = val;
    strcpy_s(e->s, NOMMAX, s);
    return e;
}

//Pile vide, pile pleine
_Bool pile_vide(t_pile* p)
{
    return (p->n == 0);
}

_Bool pile_pleine(t_pile* p)
{
    return (p->n == NBMAX);
}

//Empiler
void empiler(t_pile* p, void* e)
{
    if (!pile_pleine(p)) {
        p->t[p->n] = e;
        p->n++;
    }
    else
        printf("pile pleine\n");
}

//Lire le sommet
void* sommet(t_pile* p)
{
    void* e = NULL;
    if (!pile_vide(p))
        e = p->t[p->n - 1];
    return e;
}

//Dépiler
void* depiler(t_pile* p)
{
    void* e = NULL;
    if (!pile_vide(p)) {
        p->n--;
        e = p->t[p->n];
    }
    return e;
}

//Vider, détruire
void vider_pile(t_pile* p)
{
    int i;
    for (i = 0; i < p->n; i++)
        free(p->t[i]);
    p->n = 0;
}

void detruire_pile(t_pile** p)
{
    vider_pile(*p);
    free(*p);
    *p = NULL;
}

//Affichage
void affiche_elem(t_elem* e) // permet de caster le void* en t_elem*
{
    if (e != NULL)
        printf("%d%s--", e->val, e->s);
    else
        printf("pas d'element");
}

void affiche_pile(t_pile* p)
{
    int i;
    if (p == NULL)
        printf("pas de pile");
    else if (p->n <= 0)
        printf("pile vide");
    else {
        for (i = p->n - 1; i >= 0; i--)
            affiche_elem(p->t[i]); // void* casté en t_elem*
    }
    putchar('\n');
}

//Test dans le main()
int menu()
{
    int res = -1;
    printf("1  : empiler\n"
        "2  : depiler\n"
        "3  : vider pile\n"
    );
    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}

int main()
{
    srand((unsigned)time(NULL));

    int fin = 0, id = 0;
    t_elem* e;
    t_pile* p = NULL;

    p = init_pile();

    while (!fin) {
        switch (menu()) {
        case 1:
            e = init_elem(rand() % 26, S[(id++) % 26]);
            empiler(p, e);
            break;

        case 2:
            e = depiler(p);
            affiche_elem(e);
            putchar('\n');
            break;

        case 3:
            vider_pile(p);
            break;

        default: fin = 1;
        }
        affiche_pile(p);
    }
    detruire_pile(&p);
    return 0;
}
*/
