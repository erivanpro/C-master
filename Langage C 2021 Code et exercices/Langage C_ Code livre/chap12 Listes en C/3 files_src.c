/********************************************************************
*                                                                   *
*       CHAPITRE 12 : 3. FILES                                       *
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
*       3.2 Implémentation d'une file en dynamique          *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Structure de données
#define NOMMAX  80
typedef struct elem {
    int val;
    char s[NOMMAX];
    struct elem* suiv;
}t_elem;

char* S[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

typedef struct file {
    t_elem* prem;  // sortie
    t_elem* dern;  // entrée
}t_file;

// File vide, file pleine
int file_vide(t_file* f)
{
    return f->dern == NULL;
}

// Initialisation
t_elem* init_elem(int val, char s[])
{
    t_elem* e;
    e = (t_elem*)malloc(sizeof(t_elem));
    e->val = val;
    strcpy_s(e->s, NOMMAX, s);
    e->suiv = NULL;
    return e;
}

t_file* init_file()
{
    t_file* f;
    f = (t_file*)malloc(sizeof(t_file));
    f->prem = f->dern = NULL;
    return f;
}

// Enfiler
void enfiler(t_file* f, t_elem* e)
{
    // ajouter en queue (en dern)
    if (file_vide(f))// si file vide
        f->dern = f->prem = e;
    else { // sinon ajouter à la fin
        f->dern->suiv = e;
        f->dern = e;
    }
}

// Lire tête, lire queue
t_elem* lire_tete(t_file* f)
{
    t_elem* e = NULL;
    if (!file_vide(f))
        e = f->prem;
    return e;
}

t_elem* lire_queue(t_file* f)
{
    t_elem* e = NULL;
    if (!file_vide(f))
        e = f->dern;
    return e;
}

//Défiler
t_elem* defiler(t_file* f)
{
    t_elem* e = NULL;
    if (!file_vide(f)) {       // si non vide retirer en tête (en prem)
        if (f->prem == f->dern) {// si un seul élément
            e = f->prem;
            f->prem = f->dern = NULL;
        }
        else {                 // si plusieurs
            e = f->prem;
            f->prem = f->prem->suiv;
        }
    }
    return e;
}

// Vider, détruire
void vider_file(t_file* f)
{
    t_elem* sup;
    while (!file_vide(f)) {
        sup = defiler(f);
        free(sup);
    }
}

void detruire_file(t_file** f)
{
    vider_file(*f);
    free(*f);
    *f = NULL;
}

// Affichage
void affiche_elem(t_elem* e)
{
    if (e != NULL)
        printf("%d%s", e->val, e->s);
    else
        printf("pas d'element");
    putchar('\n');
}

void affiche_file(t_file* f)
{
    t_elem* e;
    e = f->prem;
    if (file_vide(f))
        printf("file vide");
    while (e != NULL) {
        printf("%d%s--", e->val, e->s);
        e = e->suiv;
    }
    putchar('\n');
}

// Test dans le main()
int menu()
{
    int res = -1;
    printf("1  : enfiler\n"
        "2  : defiler\n"
        "3  : vider file\n"
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
    t_file* f;

    f = init_file();
    while (!fin) {

        switch (menu()) {

        case 1:
            e = init_elem(rand() % 26, S[(id++) % 26]);
            enfiler(f, e);
            break;

        case 2:
            e = defiler(f);
            affiche_elem(e);
            break;

        case 3:
            vider_file(f);
            break;

        default: fin = 1;
        }
        affiche_file(f);
    }
    detruire_file(&f);
    return 0;
}
*/
/************************************************************
*                                                           *
*       3.3 Implémentation d'une file en statique (tableau) *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Structure de données
#define NOMMAX  80
typedef struct elem {
    int val;
    char s[NOMMAX];
}t_elem;

char* S[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

#define NBMAX  8
typedef struct file {
    int prem, dern;
    void* tab[NBMAX];
}t_file;

// File vide, File pleine
_Bool file_vide(t_file* f)
{
    return f->dern == f->prem;
}

_Bool file_pleine(t_file* f)
{
    return ((f->dern + 1) % NBMAX == f->prem);
}

// Initialisation
t_file* init_file()
{
    t_file* f;
    f = (t_file*)malloc(sizeof(t_file));
    f->prem = f->dern = 0;
    return f;
}

t_elem* init_elem(int val, char s[])
{
    t_elem* e;
    e = (t_elem*)malloc(sizeof(t_elem));
    e->val = val;
    strcpy_s(e->s, NOMMAX, s);
    return e;
}

// Enfiler
void enfiler(t_file* f, void* e)
{
    // ajouter en queue (en dern)
    if (!file_pleine(f)) {
        f->tab[f->dern] = e;
        f->dern = (f->dern + 1) % NBMAX;
    }
}

// Lire tête, lire queue
void* lire_tete(t_file* f)
{
    void* e = NULL;
    if (!file_vide(f))
        e = f->tab[f->prem];
    return e;
}

void* lire_queue(t_file* f)
{
    void* e = NULL;
    int q;
    if (!file_vide(f)) {
        q = (f->dern - 1 + NBMAX) % NBMAX; //cntl si dern à 0
        e = f->tab[q];
    }
    return e;
}

// Défiler
void* defiler(t_file* f)
{
    void* e = NULL;
    if (!file_vide(f)) { // si non vide retirer en tête (en prem)
        e = f->tab[f->prem];
        f->prem = (f->prem + 1) % NBMAX;
    }
    return e;
}

// Vider, détruire
void vider_file(t_file* f)
{
    t_elem* sup;
    while (!file_vide(f)) {
        sup = defiler(f);
        free(sup);
    }
}

void detruire_file(t_file** f)
{
    vider_file(*f);
    free(*f);
    *f = NULL;
}

// Affichage
void affiche_elem(t_elem* e)
{
    if (e != NULL)
        printf("%d%s--", e->val, e->s);
    else
        printf("pas d'element");
}

void affiche_file(t_file* f)
{
    int e;
    if (file_vide(f))
        printf("file vide");
    for (e = f->prem; e != f->dern; e = (e + 1) % NBMAX)
        affiche_elem(f->tab[e]);
    putchar('\n');
}

// Test dans le main()
int menu()
{
    int res = -1;
    printf("1  : enfiler\n"
        "2  : defiler\n"
        "3  : vider file\n"
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
    t_file* f;

    f = init_file();
    while (!fin) {
        switch (menu()) {

        case 1:
            e = init_elem(rand() % 26, S[(id++) % 26]);
            enfiler(f, e);
            break;

        case 2:
            e = defiler(f);
            affiche_elem(e);
            putchar('\n');
            break;

        case 3:
            vider_file(f);
            break;

        default: fin = 1;
        }
        affiche_file(f);
    }
    detruire_file(&f);
    return 0;
}
*/
