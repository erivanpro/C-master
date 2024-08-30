/********************************************************************
*                                                                   *
*       CHAPITRE 12 : 5. Contrôler un arbre binaire 
*       
*                                                                   *
*********************************************************************/
/*
    Pour tester les programmes :
    - faire un projet C console (de préférence vide sous visual studio)
    - copier toute la page dans le fichier C du nouveau projet (écraser tout ce qu'il contient)
    - retirer les commentaires qui encadre le programme que vous voulez tester
    - compiler et lancer le programme
      Remarque : si le programme se lance et quitte immédiatement 
      ajouter getchar(); avant le return 0; de fin de main()
    - remettre les commentaires pour tester un autre programme
*/
/****************************************************************
*     
*   Version dynamique :                                       *
*     5.1 Créer un arbre binaire								*
*     5.2 Parcourir l'arbre                                     *
*	  5.3 Afficher l'arbre										*
*	     														*
*****************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATMAX  80
typedef struct noeud {
    char dat[DATMAX];
    struct noeud* g, * d;
}t_noeud;

char* S[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

int menu(void);
// créer arbre
t_noeud* CN(char s[], t_noeud* g, t_noeud* d);
t_noeud* creerArbre1(void);
t_noeud* creerArbre2(void);
t_noeud* creerArbre3(void);

void inserer(t_noeud** racine, t_noeud* n);

// parcourir arbre
void prefixe(t_noeud* r);
void prefixe_iter(t_noeud* r);
void infixe(t_noeud* r);
void postfixe(t_noeud* r);
void largeur_iter(t_noeud* r);

// avoir la taille de l'arbre
int taille_dyn(t_noeud* r);

// afficher, dessiner (sans les arrêtes) arbre
void aff_indent(t_noeud* r, int niveau);

// détruire arbre
void detruire_arbre(t_noeud** r);

//-------------------------------------------------
int main()
{
    int fin = 0;
    t_noeud* r = NULL;

    srand((unsigned)time(NULL));
    while (!fin) {
        switch (menu()) {
        case 1:
            detruire_arbre(&r);
            r = creerArbre1();
            break;
        case 2:
            detruire_arbre(&r);
            r = creerArbre2();
            break;
        case 3:
            detruire_arbre(&r);
            r = creerArbre3();
            break;
        case 4:
            inserer(&r, CN(S[rand() % 26], NULL, NULL));
            break;
        case 5:
            if (r != NULL) {
                prefixe(r);
                putchar('\n');
                prefixe_iter(r);
                putchar('\n');
                infixe(r);
                putchar('\n');
                postfixe(r);
                putchar('\n');
                largeur_iter(r);
                putchar('\n');
            }
            break;
        case 6:
            detruire_arbre(&r);
            break;

        default:
            fin = 1;
            detruire_arbre(&r);
        }
        aff_indent(r, 0);
    }
    return 0;
}

//-------------------------------------------------
int menu()
{
    int res = -1;
    printf("1  : creer, afficher arbre 1\n"
        "2  : creer, afficher arbre 2\n"
        "3  : creer, afficher arbre 3\n"
        "4  : inserer dans arbre courant, afficher\n"
        "5  : parcours prefixe, infixe, postfixe, largeur\n"
        "6  : detruire arbre\n"
    );
    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}
//-------------------------------------------------
// Créer un arbre à partir d'un schéma descriptif
t_noeud* CN(char s[], t_noeud* g, t_noeud* d)
{
    t_noeud* n;
    n = (t_noeud*)malloc(sizeof(t_noeud));
    strcpy_s(n->dat,DATMAX, s);
    n->g = g;
    n->d = d;
    return n;
}
//-------------------------------------------------
t_noeud* creerArbre1()
{
    return CN("A",
        CN("B",
            CN("D", NULL, NULL),
            CN("E", NULL, NULL)),
        CN("C",
            CN("F",
                CN("H", NULL, NULL),
                NULL),
            CN("G", NULL, NULL))
    );
}

//-------------------------------------------------
t_noeud* creerArbre2()
{
    const int nbNoeud = 9;
    t_noeud** tab;
    t_noeud* r;
    int i;

    tab = (t_noeud**)malloc(sizeof(t_noeud*) * nbNoeud);
    for (i = 0; i < nbNoeud; i++)
        tab[i] = (t_noeud*)malloc(sizeof(t_noeud));
    strcpy_s(tab[0]->dat, DATMAX, "A");
    tab[0]->g = tab[1];
    tab[0]->d = tab[2];

    strcpy_s(tab[1]->dat, DATMAX, "B");
    tab[1]->g = tab[3];
    tab[1]->d = tab[4];

    strcpy_s(tab[2]->dat, DATMAX, "C");
    tab[2]->g = tab[5];
    tab[2]->d = tab[6];

    strcpy_s(tab[3]->dat, DATMAX, "D");
    tab[3]->g = NULL;
    tab[3]->d = NULL;

    strcpy_s(tab[4]->dat, DATMAX, "E");
    tab[4]->g = NULL;
    tab[4]->d = NULL;

    strcpy_s(tab[5]->dat, DATMAX, "F");
    tab[5]->g = tab[7];
    tab[5]->d = NULL;

    strcpy_s(tab[6]->dat, DATMAX, "G");
    tab[6]->g = NULL;
    tab[6]->d = NULL;

    strcpy_s(tab[7]->dat, DATMAX, "H");
    tab[7]->g = NULL;
    tab[7]->d = NULL;

    r = tab[0];
    free(tab);
    return r;
}
//-------------------------------------------------
// Créer un arbre à partir des données aléatoires d'un tableau
t_noeud* creerArbre3()
{
    t_noeud* r;
    t_noeud** tab;
    int taille;
    // taille aléatoire
    taille = 1 + rand() % 100; // min 1 max 100 noeuds
    // création tableau de pointeurs de noeuds
    tab = (t_noeud**)malloc(sizeof(t_noeud*) * taille);
    // initialisation aléatoire des datas des noeuds
    for (int i = 0; i < taille; i++) {
        tab[i] = (t_noeud*)malloc(sizeof(t_noeud));
        strcpy_s(tab[i]->dat, DATMAX, S[rand() % 26]);
    }
    // construction de l'arbre, racine en tab[0]

    // écriture 1
    //for (int i = 1; i <= taille; i++) {
    //    int g = 2 * i - 1;
    //    int d = 2 * i;
    //    tab[i - 1]->g = (g < taille) ? tab[g] : NULL;
    //    tab[i - 1]->d = (d < taille) ? tab[d] : NULL;
    //}

    // écriture 2 
    for (int i = 0, k = 0; i < taille; i++) {
        tab[i]->g = (++k < taille) ? tab[k] : NULL;
        tab[i]->d = (++k < taille) ? tab[k] : NULL;
    }

    r = tab[0];
    free(tab);
    return r;
}
//-------------------------------------------------
//Créer un arbre en insérant des éléments ordonnés
void inserer(t_noeud** racine, t_noeud* n)
{
    t_noeud* x, * prec;
    // si pas de racine il devient racine
    if (*racine == NULL)
        *racine = n;
    // sinon descendre jusqu'à une feuille (fils g et d à NULL)
    else {
        x = *racine;// pour descendre
        prec = NULL;// pour conserver position précédente
        while (x != NULL) {
            prec = x;  // save position précédente
            x = (strcmp(n->dat, x->dat) < 0) ? x->g : x->d;// descente selon n
        }
        // à l'issue accrocher
        if (strcmp(n->dat, prec->dat) < 0)
            prec->g = n;
        else
            prec->d = n;
    }
}
//-------------------------------------------------
// Parcours en profondeur préfixé
void prefixe(t_noeud* r)
{
    if (r != NULL) {
        printf("%s", r->dat);
        prefixe(r->g);
        prefixe(r->d);
    }
}
//-------------------------------------------------
void prefixe_iter(t_noeud* r)
{
    t_noeud** pile;
    int n = 0;
    if (r == NULL)
        printf("arbre inexistant");
    else {
        pile = (t_noeud**)malloc(sizeof(t_noeud*) * taille_dyn(r));
        pile[n++] = r;
        while (n > 0) {
            r = pile[--n];
            printf("%s", r->dat);
            if (r->d)
                pile[n++] = r->d;
            if (r->g)
                pile[n++] = r->g;
        }
        free(pile);
    }
}
//-------------------------------------------------
// parcours en profondeur infixé
void infixe(t_noeud* r)
{
    if (r != NULL) {
        infixe(r->g);
        printf("%s", r->dat);
        infixe(r->d);
    }
}
//-------------------------------------------------
// parcours en profondeur postfixé
void postfixe(t_noeud* r)
{
    if (r != NULL) {
        postfixe(r->g);
        postfixe(r->d);
        printf("%s", r->dat);
    }
}
//-------------------------------------------------
// Parcours en largeur, par niveau
void largeur_iter(t_noeud* r)
{
    t_noeud** file;
    int q = 0, t = 0;
    if (r == NULL)
        printf("arbre inexistant");
    else {
        file = (t_noeud**)malloc(sizeof(t_noeud*) * taille_dyn(r));
        file[t++] = r;
        while (q != t) {
            r = file[q++];
            printf("%s", r->dat);
            if (r->g)
                file[t++] = r->g;
            if (r->d)
                file[t++] = r->d;
        }
    }
}
//-------------------------------------------------
// avoir la taille de l'arbre
int taille_dyn(t_noeud* r)
{
    int res = 0;
    if (r != NULL)
        res = 1 + taille_dyn(r->g) + taille_dyn(r->d);
    return res;
}
//-------------------------------------------------
// Afficher l'arbre
// Afficher un arbre avec indentation
void aff_indent(t_noeud* r, int niveau)
{
    int i;
    if (r != NULL) {
        for (i = 0; i < niveau; i++) // 5 espaces par niveau
            printf("%5s", " ");
        printf("%s\n", r->dat);
        aff_indent(r->g, niveau + 1);
        aff_indent(r->d, niveau + 1);
    }
}
//-------------------------------------------------
// Détruire l'arbre
void detruire_arbre(t_noeud** r)
{
    if (*r != NULL) {
        detruire_arbre(&(*r)->g);
        detruire_arbre(&(*r)->d);
        free(*r);
        *r = NULL;
    }
}
*/
/************************************************************
*                                                           *
*     Version statique                                      *
*       5.1 Créer un arbre binaire							*
*       5.2 Parcourir l'arbre                               *
*	    5.3 Afficher l'arbre	                            *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VIDE     -1
#define DATMAX  80
typedef struct noeuds {
    char dat[DATMAX];
    int g, d;
}t_noeuds;

char* S[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

int menu(void);
// créer arbre
t_noeuds* creerArbre_stat(int*r);

// parcourir arbre
void prefixe_stat(t_noeuds t[], int r);
void infixe_stat(t_noeuds t[], int r);
void postfixe_stat(t_noeuds t[], int r);
void largeur_iter_stat(t_noeuds t[], int r);

// avoir la taille de l'arbre
int taille_dyn_stat(t_noeuds t[],int r);

// afficher, dessiner (sans les arrêtes) arbre
void aff_indent_stat(t_noeuds t[],int r, int niveau);

// détruire arbre
void detruire_arbre_stat(t_noeuds**t);

//-------------------------------------------------
int main()
{
    int fin = 0;
    t_noeuds* tab = NULL;
    int racine=VIDE;

    srand((unsigned)time(NULL));
    while (!fin) {
        switch (menu()) {
        case 1:
            detruire_arbre_stat(&tab);
            tab = creerArbre_stat(&racine); // racine à 0
            break;
        case 2:
            if (tab != NULL) {
                prefixe_stat(tab, racine);
                putchar('\n');

                infixe_stat(tab, racine);
                putchar('\n');
                postfixe_stat(tab, racine);
                putchar('\n');
                largeur_iter_stat(tab, racine);
                putchar('\n');
            }
            break;
        case 3:
            detruire_arbre_stat(&tab);
            break;

        default:
            fin = 1;
            detruire_arbre_stat(&tab);
        }
        aff_indent_stat(tab,racine,0);
    }
    return 0;
}

//-------------------------------------------------
int menu()
{
    int res = -1;
    printf("1  : creer, afficher arbre 1\n"
        "2  : parcours prefixe, infixe, postfixe, largeur\n"
        "3  : detruire arbre\n"
    );
    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}
//-------------------------------------------------
// Créer un arbre à partir des données aléatoires d'un tableau
// ici la racine est à 0
t_noeuds* creerArbre_stat(int*r)
{
    t_noeuds* t;
    int nb, i, k;
    nb = 1 + rand() % 50;
    t = (t_noeuds*)malloc(sizeof(t_noeuds) * nb);
    for (i = 0, k = 0; i < nb; i++) {
        strcpy_s(t[i].dat, DATMAX, S[rand() % 26]);
        t[i].g = (++k < nb) ? k : -1;
        t[i].d = (++k < nb) ? k : -1;
    }
    *r = 0;
    return t;
}

//-------------------------------------------------
// Parcours en profondeur préfixé
void prefixe_stat(t_noeuds t[],int r)
{
    if (r != VIDE) {
        printf("%s", t[r].dat);
        prefixe_stat(t, t[r].g);
        prefixe_stat(t, t[r].d);
    }
}
//-------------------------------------------------
// parcours en profondeur infixé
void infixe_stat(t_noeuds t[],int r)
{
    if (r != VIDE) {
        infixe_stat(t, t[r].g);
        printf("%s", t[r].dat);
        infixe_stat(t, t[r].d);
    }
}
//-------------------------------------------------
// parcours en profondeur postfixé
void postfixe_stat(t_noeuds t[], int r)
{
    if (r != VIDE) {
        postfixe_stat(t, t[r].g);
        postfixe_stat(t, t[r].d);
        printf("%s", t[r].dat);
    }
}
//-------------------------------------------------
// Parcours en largeur, par niveau
void largeur_iter_stat(t_noeuds t[],int r)
{
    t_noeuds* file, racine;
    int queue = 0, tete = 0;
    if (r == VIDE)
        printf("arbre inexistant");
    else {
        file = (t_noeuds*)malloc(sizeof(t_noeuds) * taille_dyn_stat(t, r));
        file[queue++] = t[r];
        while (queue != tete) {
            racine = file[tete++];
            printf("%s", racine.dat);
            if (racine.g != VIDE)
                file[queue++] = t[racine.g];
            if (racine.d != VIDE)
                file[queue++] = t[racine.d];
        }
        free(file);
    }
}
//-------------------------------------------------
// avoir la taille de l'arbre
int taille_dyn_stat(t_noeuds t[],int r)
{
    int res = 0;
    if (r != VIDE)
        res = 1 + taille_dyn_stat(t, t[r].g) + taille_dyn_stat(t, t[r].d);
    return res;
}

//-------------------------------------------------
// Afficher l'arbre
// Afficher un arbre avec indentation
void aff_indent_stat(t_noeuds t[], int r, int niveau)
{
    int i;
    if (t == NULL)
        printf("arbre vide\n");
    else if(r != VIDE) {
        for (i = 0; i < niveau; i++) // 5 espaces par niveau
            printf("%5s", " ");
        printf("%s\n", t[r].dat);
        aff_indent_stat(t, t[r].g, niveau + 1);
        aff_indent_stat(t, t[r].d, niveau + 1);
    }
}

//-------------------------------------------------
// Détruire l'arbre
void detruire_arbre_stat(t_noeuds** t)
{
    if (*t != NULL) {
        free(*t);
        *t = NULL;
    }
}
*/
/************************************************************
*                                                           *
*     5.3.2 Dessiner un arbre sans les liens                *
*                                                           *
*************************************************************/
/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define DATMAX  80
typedef struct noeud {
    char dat[DATMAX];
    struct noeud* g, * d;
}t_noeud;

char* S[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

t_noeud* creerArbre3()
{
    t_noeud* r;
    t_noeud** tab;
    int taille;
    // taille aléatoire
    taille = 1 + rand() % 20; // min 1 max 10 noeuds
    // création tableau de pointeurs de noeuds
    tab = (t_noeud**)malloc(sizeof(t_noeud*) * taille);
    // initialisation aléatoire des datas des noeuds
    for (int i = 0; i < taille; i++) {
        tab[i] = (t_noeud*)malloc(sizeof(t_noeud));
        strcpy_s(tab[i]->dat, DATMAX, S[rand() % 26]);
    }
    // construction de l'arbre, racine en tab[0]

    // écriture 2 
    for (int i = 0, k = 0; i < taille; i++) {
        tab[i]->g = (++k < taille) ? tab[k] : NULL;
        tab[i]->d = (++k < taille) ? tab[k] : NULL;
    }

    r = tab[0];
    free(tab);
    return r;
}
int menu()
{
    int res = -1;
    printf("1  : creer, afficher arbre 1\n");
    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}
void detruire_arbre(t_noeud** r)
{
    if (*r != NULL) {
        detruire_arbre(&(*r)->g);
        detruire_arbre(&(*r)->d);
        free(*r);
        *r = NULL;
    }
}
void gotoxy(int x, int y)
{
    COORD c = { x,y };
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, c);
}
void dessin_arbre(t_noeud* r, int* x, int y)
{
    if (r != NULL) {
        dessin_arbre(r->g, x, y + 2);
        *x += 5;
        gotoxy(*x, y);
        printf("%s", r->dat);
        dessin_arbre(r->d, x, y + 2);
    }
}
// pour obtenir la hauteur de l'arbre
int hauteur_dyn(t_noeud* r)
{
    int h = 0;
    if (r != NULL)
        h = 1 + max(hauteur_dyn(r->g), hauteur_dyn(r->d));
    return h;
}

int main()
{
    int fin = 0;
    t_noeud* r = NULL;
    int x;

    srand((unsigned)time(NULL));
    while (!fin) {
        switch (menu()) {
        case 1:
            detruire_arbre(&r);
            r = creerArbre3();
            break;
        default:
            fin = 1;
            detruire_arbre(&r);
            break;
        }
        // affichage
        system("cls");
        x = 0;
        dessin_arbre(r, &x, 0);
        gotoxy(0, hauteur_dyn(r) * 2 + 1);
    }
    return 0;
}
*/
/************************************************************
*                                                           *
*     5.4 Obtenir des propriétés de l'arbre binaire          *
*     5.5 copie d'arbres binaires                           *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noeud {
    int val;
    struct noeud* g, * d;
}t_noeud;


typedef struct noeuds {
    int val;
    int g, d;
}t_noeuds;

int         menu(void);
t_noeud*    creerArbre_dyn(void);
t_noeuds*   creerArbre_stat(void);
void        aff_indent_dyn(t_noeud* r, int niveau);
void        aff_indent_stat(t_noeuds t[], int r, int niveau);
void        detruire_arbre_dyn(t_noeud** r);
void        detruire_arbre_stat(t_noeuds** r);
int         taille_dyn(t_noeud* r);
int         taille_stat(t_noeuds t[], int r);
int         hauteur_dyn(t_noeud* r);
int         hauteur_stat(t_noeuds t[], int r);
_Bool       feuille_dyn(t_noeud* r);
_Bool       feuille_stat(t_noeuds t[], int r);
int         compteFeuille_dyn(t_noeud* r);
int         compteFeuille_stat(t_noeuds t[], int r);
void        listerFeuille_dyn(t_noeud* r);
void        listerFeuille_stat(t_noeuds t[], int r);
int         sommeVal_dyn(t_noeud* r);
int         sommeVal_stat(t_noeuds t[], int r);
int         maxVal_dyn(t_noeud* r);
int         maxVal_stat(t_noeuds t[], int r);
t_noeud*    chercheVal_dyn(t_noeud* r, int val);
int         chercheVal_stat(t_noeuds t[], int r, int val);
t_noeud*    copieArbre_dyn(t_noeud* r);
t_noeuds*   copieArbre_stat(t_noeuds t[], int r);
//-------------------------------------------------
int main()
{
    int fin = 0, val, i;
    t_noeud* r = NULL, * r2 = NULL;
    t_noeuds* t = NULL, * t2 = NULL;
    t_noeud* res = NULL;


    while (!fin) {
        switch (menu()) {

            // TESTS ARBRE DYNAMIQUE
        case 1:
            detruire_arbre_dyn(&r);
            r = creerArbre_dyn();
            aff_indent_dyn(r, 0);
            printf("taille          : %d\n", taille_dyn(r));
            printf("hauteur         : %d\n", hauteur_dyn(r));
            printf("nb feuilles     : %d\n", compteFeuille_dyn(r));
            printf("somme valeurs   : %d\n", sommeVal_dyn(r));
            printf("plus grande val : %d\n", maxVal_dyn(r));
            printf("liste feuilles  :\n");
            listerFeuille_dyn(r);
            printf("entrer val noeud a chercher :\n");
            scanf_s("%d", &val);
            rewind(stdin);
            res = chercheVal_dyn(r, val);
            if (res)
                printf("trouve noeud : %d\n", res->val);
            else
                printf("val non presente \n");
            break;

        case 2:
            detruire_arbre_dyn(&r2);
            r2 = copieArbre_dyn(r);
            printf("affiche arbre duplique :\n");
            aff_indent_dyn(r2, 0);
            break;


            // TESTS ARBRE STATIQUE
        case 3:
            detruire_arbre_stat(&t);
            t = creerArbre_stat();
            aff_indent_stat(t, 0, 0);
            printf("taille          : %d\n", taille_stat(t, 0));
            printf("hauteur         : %d\n", hauteur_stat(t, 0));
            printf("nb feuilles     : %d\n", compteFeuille_stat(t, 0));
            printf("somme valeurs   : %d\n", sommeVal_stat(t, 0));
            printf("plus grande val : %d\n", maxVal_stat(t, 0));
            printf("liste feuilles  :\n");
            listerFeuille_stat(t, 0);
            printf("entrer val noeud a chercher :\n");
            scanf_s("%d", &val);
            rewind(stdin);
            i = chercheVal_stat(t, 0, val);
            if (i >= 0)
                printf("trouve noeud : %d\n", t[i].val);
            else
                printf("val non presente \n");
            break;
        case 4:
            detruire_arbre_stat(&t2);
            t2 = copieArbre_stat(t, 0);
            printf("affiche arbre duplique :\n");
            aff_indent_stat(t2, 0, 0);
            break;
        default: fin = 1;
        }
    }
    return 0;
}
//-------------------------------------------------
int menu()
{
    int res = -1;
    printf("1  : creer arbre dynamique aleatoire,afficher \n"
           "2  : dupliquer arbre dynamique\n"
           "3  : creer arbre statique aleatoire,afficher\n"
           "4  : dupliquer arbre statique\n"
    );
    scanf_s("%d", &res);
    rewind(stdin);
    printf("_________\n");
    return res;
}
//-------------------------------------------------
t_noeud* creerArbre_dyn()
{
    t_noeud* r;
    t_noeud** tab;
    int i, k, taille;
    // taille aléatoire
    taille = 1 + rand() % 50; // min 1 max 50 noeuds
    // création tableau de pointeurs de noeuds
    tab = (t_noeud**)malloc(sizeof(t_noeud*) * taille);
    // initialisation aléatoire des datas des noeuds
    for (i = 0; i < taille; i++) {
        tab[i] = (t_noeud*)malloc(sizeof(t_noeud));
        tab[i]->val = rand() % 256;
    }
    // construction de l'arbre, racine en tab[0]
    for (i = 0, k = 0; i < taille; i++) {
        tab[i]->g = (++k < taille) ? tab[k] : NULL;
        tab[i]->d = (++k < taille) ? tab[k] : NULL;
    }
    r = tab[0];
    free(tab);
    return r;
}
//-------------------------------------------------
t_noeuds* creerArbre_stat()
{
    t_noeuds* t;
    int nb, i, k;
    nb = 1 + rand() % 50;
    t = (t_noeuds*)malloc(sizeof(t_noeuds) * nb);
    for (i = 0, k = 0; i < nb; i++) {
        t[i].val = rand() % 256;
        t[i].g = (++k < nb) ? k : -1;
        t[i].d = (++k < nb) ? k : -1;
    }
    return t;
}
//-------------------------------------------------
void aff_indent_dyn(t_noeud* r, int niveau)
{
    int i;
    if (r != NULL) {
        for (i = 0; i < niveau; i++) // 5 espaces par niveau
            printf("%5s", " ");
        printf("%4d\n", r->val);
        aff_indent_dyn(r->g, niveau + 1);
        aff_indent_dyn(r->d, niveau + 1);
    }
}
//-------------------------------------------------
void aff_indent_stat(t_noeuds t[], int r, int niveau)
{
    int i;
    if (t == NULL)
        printf("arbre inexistant\n");
    else if (r != -1) {
        for (i = 0; i < niveau; i++) // 5 espaces par niveau
            printf("%5s", " ");
        printf("%4d\n", t[r].val);
        aff_indent_stat(t, t[r].g, niveau + 1);
        aff_indent_stat(t, t[r].d, niveau + 1);
    }
}
//-------------------------------------------------
void detruire_arbre_dyn(t_noeud** r)
{
    if (*r != NULL) {
        detruire_arbre_dyn(&(*r)->g);
        detruire_arbre_dyn(&(*r)->d);
        free(*r);
        *r = NULL;
    }
}
//-------------------------------------------------
void detruire_arbre_stat(t_noeuds** r)
{
    if (*r != NULL) {
        free(*r);
        *r = NULL;
    }
}
//-------------------------------------------------
int taille_dyn(t_noeud* r)
{
    int res = 0;
    if (r != NULL)
        res = 1 + taille_dyn(r->g) + taille_dyn(r->d);
    return res;
}
//-------------------------------------------------
int taille_stat(t_noeuds t[], int r)
{
    int res = 0;
    if (r != -1)
        res = 1 + taille_stat(t, t[r].g) + taille_stat(t, t[r].d);
    return res;
}
//-------------------------------------------------
int hauteur_dyn(t_noeud* r)
{
    int h = 0;
    if (r != NULL)
        // max est une directive macro dans stdlib.h
        h = 1 + max(hauteur_dyn(r->g), hauteur_dyn(r->d));
    return h;
}
//-------------------------------------------------
int hauteur_stat(t_noeuds t[], int r)
{
    int h = 0;
    if (r != -1)
        h = 1 + max(hauteur_stat(t, t[r].g), hauteur_stat(t, t[r].d));
    return h;
}
//-------------------------------------------------
_Bool feuille_dyn(t_noeud* r)
{
    return (r->g == NULL && r->d == NULL);
}
//-------------------------------------------------
_Bool feuille_stat(t_noeuds t[], int r)
{
    return (t[r].g == -1 && t[r].d == -1);
}
//-------------------------------------------------
int compteFeuille_dyn(t_noeud* r)
{
    int nb = 0;
    if (r != NULL) {
        if (feuille_dyn(r))
            nb = 1;
        else
            nb = compteFeuille_dyn(r->g) + compteFeuille_dyn(r->d);
    }
    return nb;
}
//-------------------------------------------------
int compteFeuille_stat(t_noeuds t[], int r)
{
    int nb = 0;
    if (r != -1) {
        if (feuille_stat(t, r))
            nb = 1;
        else
            nb = compteFeuille_stat(t, t[r].g) + compteFeuille_stat(t, t[r].d);
    }
    return nb;
}
//-------------------------------------------------
void listerFeuille_dyn(t_noeud* r)
{
    if (r != NULL) {
        if (feuille_dyn(r))
            printf("%d\n", r->val);
        listerFeuille_dyn(r->g);
        listerFeuille_dyn(r->d);
    }
}
//-------------------------------------------------
void listerFeuille_stat(t_noeuds t[], int r)
{
    if (r != -1) {
        if (feuille_stat(t, r))
            printf("%d\n", t[r].val);
        listerFeuille_stat(t, t[r].g);
        listerFeuille_stat(t, t[r].d);
    }
}
//-------------------------------------------------
int sommeVal_dyn(t_noeud* r)
{
    int res = 0;
    if (r != NULL)
        res = sommeVal_dyn(r->g)
        + sommeVal_dyn(r->d)
        + r->val;
    return res;
}
//-------------------------------------------------
int sommeVal_stat(t_noeuds t[], int r)
{
    int res = 0;
    if (r != -1)
        res = sommeVal_stat(t, t[r].g)
        + sommeVal_stat(t, t[r].d)
        + t[r].val;
    return res;
}
//-------------------------------------------------
int maxVal_dyn(t_noeud* r)
{
    int res = 0;
    if (r != NULL) {
        res = max(maxVal_dyn(r->g), maxVal_dyn(r->d));
        res = max(res, r->val);
    }
    return res;
}
//-------------------------------------------------
int maxVal_stat(t_noeuds t[], int r)
{
    int res = 0;
    if (r != -1) {
        res = max(maxVal_stat(t, t[r].g), maxVal_stat(t, t[r].d));
        res = max(res, t[r].val);
    }
    return res;
}
//-------------------------------------------------
t_noeud* chercheVal_dyn(t_noeud* r, int val)
{
    t_noeud* res = NULL;
    if (r != NULL) {
        if (r->val == val)
            res = r;
        else {
            res = chercheVal_dyn(r->g, val);
            if (res == NULL)
                res = chercheVal_dyn(r->d, val);
        }
    }
    return res;
}
//-------------------------------------------------
int chercheVal_stat(t_noeuds t[], int r, int val)
{
    int res = -1;
    if (r != -1) {
        if (t[r].val == val)
            res = r;
        else {
            res = chercheVal_stat(t, t[r].g, val);
            if (res == -1)
                res = chercheVal_stat(t, t[r].d, val);
        }
    }
    return res;
}
//-------------------------------------------------
t_noeud* copieArbre_dyn(t_noeud* r)
{
    t_noeud* res = NULL;
    if (r != NULL) {
        res = (t_noeud*)malloc(sizeof(t_noeud));
        res->val = r->val;
        res->g = copieArbre_dyn(r->g);
        res->d = copieArbre_dyn(r->d);
    }
    return res;
}
//-------------------------------------------------
t_noeuds* copieArbre_stat(t_noeuds t[], int r)
{
    t_noeuds* res = NULL;
    int taille;
    if (t != NULL) {
        taille = taille_stat(t, r);
        res = (t_noeuds*)malloc(sizeof(t_noeuds) * taille);
        memcpy(res, t, sizeof(t_noeuds) * taille);
    }
    return res;
}
*/
/************************************************************
*                                                           *
*     5.7 Conversion statique-dynamique d'un arbre binaire  *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>

// noeud arbre dynamique
typedef struct noeud{
   int val;
   struct noeud*g, *d;
}t_noeud;

// noeud arbre statique
typedef struct noeuds{
   int val;
   int g, d;
}t_noeuds;

int         menu                    (void);
t_noeud*    creerArbre_dyn          (void);
t_noeuds*   creerArbre_stat         (void);
t_noeud*    statToDyn               (t_noeuds*rs,int r);
int         taille_dyn              (t_noeud*rd);
t_noeuds*   allouer_tab             (t_noeud*rd);
t_noeuds*   dynToStat               (t_noeud*rd);
void        detruire_arbre_dyn      (t_noeud**rd);
void        detruire_arbre_stat     (t_noeuds**rs);
void        aff_indent_dyn          (t_noeud*rd,int niveau);
void        aff_indent_stat         (t_noeuds t[],int r,int niveau);
//-------------------------------------------------
int main()
{
int fin=0;
t_noeud*rd=NULL;
t_noeuds*rs=NULL;

   while(!fin){
      switch(menu()){
         case 1 :
         // détruire anciens
            detruire_arbre_dyn(&rd);
            detruire_arbre_stat(&rs);
         // creer arbre dynamque + affiche
            rd=creerArbre_dyn();
            printf("arbre dynamique :\n");
            aff_indent_dyn(rd,0);
         // conversion + affiche
            rs=dynToStat(rd);
            printf("conversion en statique :\n");
            aff_indent_stat(rs,0,0);
            break;
         case 2 :
         //effacer arbres anciens
            detruire_arbre_stat(&rs);
            detruire_arbre_dyn(&rd);
         //creer arbre static + affiche
            rs=creerArbre_stat();
            printf("arbre statique :\n");
            aff_indent_stat(rs,0,0);
         // convertir en dynamique + affiche
            rd=statToDyn(rs,0);
            printf("conversion en dynamique :\n");
            aff_indent_dyn(rd,0);
            break;

         default : fin=1;
      }
   }
   return 0;
}
//-------------------------------------------------
int menu()
{
int res=-1;
   printf(  "1  : creer arbre dynamique + conversion en statique + affichage \n"
            "2  : creer arbre statique + conversion en dynamique + affichage\n"
         );
   scanf_s("%d",&res);
   rewind(stdin);
   return res;
}
//-------------------------------------------------
t_noeud* creerArbre_dyn()
{
t_noeud*r;
t_noeud**tab;
int i,k,taille;
   // taille aléatoire
   taille=1+rand()%50; // min 1 max 50 noeuds
   // création tableau de pointeurs de noeuds
   tab=(t_noeud**)malloc(sizeof(t_noeud*)*taille);
   // initialisation aléatoire des datas des noeuds
   for(i=0;i<taille;i++){
      tab[i]=(t_noeud*)malloc(sizeof(t_noeud));
      tab[i]->val=rand()%256;
   }
   // construction de l'arbre, racine en tab[0]
   for (i=0,k=0; i<taille; i++){
      tab[i]->g=(++k<taille)?tab[k]: NULL;
      tab[i]->d=(++k<taille)?tab[k]: NULL;
   }
   r=tab[0];
   free(tab);
   return r;
}
//-------------------------------------------------
t_noeuds* creerArbre_stat()
{
t_noeuds*t;
int nb,i,k;
   nb=1+rand()%50;
   t=(t_noeuds*)malloc(sizeof(t_noeuds)*nb);
   for(i=0,k=0; i<nb; i++){
      t[i].val=rand()%256;
      t[i].g=(++k<nb)?k:-1;
      t[i].d=(++k<nb)?k:-1;
   }
   return t;
}
//-------------------------------------------------
//Conversion d'un arbre statique en arbre dynamique
t_noeud* statToDyn(t_noeuds*rs,int r)
{
t_noeud*rd=NULL;
   if (r!=-1){
      rd=(t_noeud*)malloc(sizeof(t_noeud));
      rd->val=rs[r].val;
      rd->g=statToDyn(rs,rs[r].g);
      rd->d=statToDyn(rs,rs[r].d);
   }
   return rd;
}
//-------------------------------------------------
//conversion arbre dynamique en arbre statique :
//1) avoir la taille de l'arbre dynamique
//2) créer un tableau dynamique de taille noeuds statiques
//3) recopier les données de chaque noeuds avec la structure de l'arbre
//4) regrouper 1,2,3 dans une seule fonction
int taille_dyn(t_noeud*rd)
{
int res=0;
   if (rd!=NULL)
      res= 1 + taille_dyn(rd->g) + taille_dyn(rd->d);
   return res;
}
//------------------------------------------------- 2
t_noeuds*allouer_tab(t_noeud*rd)
{
t_noeuds*rs=NULL;
   if (rd)
      rs=(t_noeuds*)malloc(sizeof(t_noeuds)*taille_dyn(rd));
   return rs;
}
//------------------------------------------------- 3
int copie_dyn_stat(t_noeud*rd,t_noeuds*rs,int *pos)
{
int res=-1;
   if(rd!=NULL){
      res=*pos;
      (*pos)++;
      rs[res].val=rd->val;
      rs[res].g=copie_dyn_stat(rd->g,rs,pos);
      rs[res].d=copie_dyn_stat(rd->d,rs,pos);
   }
   return res;
}
//------------------------------------------------- 4
t_noeuds* dynToStat(t_noeud*rd)
{
t_noeuds*rs=NULL;
int pos=0;
   rs=allouer_tab(rd);
   copie_dyn_stat(rd,rs,&pos);
   return rs;
}
//-------------------------------------------------
void detruire_arbre_dyn(t_noeud**r)
{
   if(*r!=NULL){
      detruire_arbre_dyn(&(*r)->g);
      detruire_arbre_dyn(&(*r)->g);
      free(*r);
      *r=NULL;
   }
}
//-------------------------------------------------
void detruire_arbre_stat(t_noeuds**r)
{
   if(*r!=NULL){
      free(*r);
      *r=NULL;
   }
}
//-------------------------------------------------
void aff_indent_dyn(t_noeud*r,int niveau)
{
int i;
   if (r!=NULL){
      for(i=0; i<niveau; i++) // 5 espaces par niveau
         printf("%5s"," ");
      printf("%4d\n",r->val);
      aff_indent_dyn(r->g,niveau+1);
      aff_indent_dyn(r->d,niveau+1);
   }
}
//-------------------------------------------------
void aff_indent_stat(t_noeuds t[],int r,int niveau)
{
int i;
    if(t==NULL)
        printf("arbre inexistant\n");
    else if (r!=-1){
        for(i=0; i<niveau; i++) // 5 espaces par niveau
            printf("%5s"," ");
        printf("%4d\n",t[r].val);
        aff_indent_stat(t,t[r].g,niveau+1);
        aff_indent_stat(t,t[r].d,niveau+1);
    }
}
*/
/************************************************************
*                                                           *
*     Sauver un arbre dynamique ou statique                 *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>

// noeud arbre dynamique
typedef struct noeud {
    int val;
    struct noeud* g, * d;
}t_noeud;

// noeud arbre statique
typedef struct noeuds {
    int val;
    int g, d;
}t_noeuds;

int         menu(void);
t_noeud*    creerArbre_dyn(void);
t_noeuds*   creerArbre_stat(void);

// load and save arbre dyn
void        save_arbre_dyn(t_noeud* rd);
int         taille_dyn(t_noeud* rd);
t_noeuds*   allouer_tab(t_noeud* rd);
t_noeuds*   dynToStat(t_noeud* rd);
void        lireNoeud(FILE* f, int nieme, t_noeuds* enr);
t_noeud*    fileToDyn(FILE* f, int r);
t_noeud*    loadArbre_dyn(void);

// load and save arbre stat
void        save_arbre_stat(t_noeuds* rs, int r);
int         taille_stat(t_noeuds* rs, int r);
int         taille_file(FILE* f, int r);
t_noeuds*   loadArbre_stat(void);

void        detruire_arbre_dyn(t_noeud** rd);
void        detruire_arbre_stat(t_noeuds** rs);
void        aff_indent_dyn(t_noeud* rd, int niveau);
void        aff_indent_stat(t_noeuds t[], int r, int niveau);
//-------------------------------------------------
int main()
{
    int fin = 0;
    t_noeud* rd = NULL;
    t_noeuds* rs = NULL;

    while (!fin) {
        switch (menu()) {
        case 1:
            // création, affichage
            detruire_arbre_dyn(&rd);
            rd = creerArbre_dyn();
            printf("abre dynamique original :\n");
            aff_indent_dyn(rd, 0);
            // save, destruction original, load, affichage
            save_arbre_dyn(rd);
            detruire_arbre_dyn(&rd);
            rd = loadArbre_dyn();
            printf("abre dynamique save + load :\n");
            aff_indent_dyn(rd, 0);
            break;
        case 2:
            // création, affichage
            detruire_arbre_stat(&rs);
            rs = creerArbre_stat();
            printf("arbre statique original :\n");
            aff_indent_stat(rs, 0, 0);
            // save, destruction original, load, affichage
            save_arbre_stat(rs, 0);
            detruire_arbre_stat(&rs);
            rs = loadArbre_stat();
            printf("arbre statique save + load :\n");
            aff_indent_stat(rs, 0, 0);
            break;

        default: fin = 1;
        }
    }
    return 0;
}
//-------------------------------------------------
int menu()
{
    int res = -1;
    printf("1  : creer arbre dynamique, sauver, loader,afficher \n"
        "2  : creer arbre statique,  sauver, loader, afficher\n"
    );
    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}
//-------------------------------------------------
t_noeud* creerArbre_dyn()
{
    t_noeud* r;
    t_noeud** tab;
    int i, k, taille;
    // taille aléatoire
    taille = 1 + rand() % 50; // min 1 max 50 noeuds
    // création tableau de pointeurs de noeuds
    tab = (t_noeud**)malloc(sizeof(t_noeud*) * taille);
    // initialisation aléatoire des datas des noeuds
    for (i = 0; i < taille; i++) {
        tab[i] = (t_noeud*)malloc(sizeof(t_noeud));
        tab[i]->val = rand() % 256;
    }
    // construction de l'arbre, racine en tab[0]
    for (i = 0, k = 0; i < taille; i++) {
        tab[i]->g = (++k < taille) ? tab[k] : NULL;
        tab[i]->d = (++k < taille) ? tab[k] : NULL;
    }
    r = tab[0];
    free(tab);
    return r;
}
//-------------------------------------------------
t_noeuds* creerArbre_stat()
{
    t_noeuds* t;
    int nb, i, k;
    nb = 1 + rand() % 50;
    t = (t_noeuds*)malloc(sizeof(t_noeuds) * nb);
    for (i = 0, k = 0; i < nb; i++) {
        t[i].val = rand() % 256;
        t[i].g = (++k < nb) ? k : -1;
        t[i].d = (++k < nb) ? k : -1;
    }
    return t;
}
//-------------------------------------------------
//sauvegarde arbre dynamique

void save_arbre_dyn(t_noeud* rd)
{
    FILE* f;
    int nb;
    t_noeuds* rs;
    fopen_s(&f,"save arbre.bin", "wb");
    if (f == NULL || rd == NULL)
        printf("probleme fichier ou arbre inexistant\n");
    else {
        rs = dynToStat(rd);
        nb = taille_dyn(rd);
        fwrite(rs, sizeof(t_noeuds), nb, f);
        fclose(f);
    }
}
//-------------------------------------------------
//conversion arbre dynamique en arbre statique

// avoir la taille
int taille_dyn(t_noeud* rd)
{
    int res = 0;
    if (rd != NULL)
        res = 1 + taille_dyn(rd->g) + taille_dyn(rd->d);
    return res;
}
// 2 allouer tableau
t_noeuds* allouer_tab(t_noeud* rd)
{
    t_noeuds* rs = NULL;
    if (rd)
        rs = (t_noeuds*)malloc(sizeof(t_noeuds) * taille_dyn(rd));
    return rs;
}
// 3 copie de l'arbre dynamique en statique
int copie_dyn_stat(t_noeud* rd, t_noeuds* rs, int* pos)
{
    int res = -1;
    if (rd != NULL) {
        res = *pos;
        (*pos)++;
        rs[res].val = rd->val;
        rs[res].g = copie_dyn_stat(rd->g, rs, pos);
        rs[res].d = copie_dyn_stat(rd->d, rs, pos);
    }
    return res;
}
// 4 regroupement des 3 opérations ci-dessus
t_noeuds* dynToStat(t_noeud* rd)
{
    t_noeuds* rs = NULL;
    int pos = 0;
    rs = allouer_tab(rd);
    copie_dyn_stat(rd, rs, &pos);
    return rs;
}
//-------------------------------------------------
//chargement arbre en dynamique dans le programme

// lecture d'un noeud i dans le fichier
void lireNoeud(FILE* f, int nieme, t_noeuds* enr)
{
    fseek(f, sizeof(t_noeuds) * nieme, SEEK_SET);
    fread(enr, sizeof(t_noeuds), 1, f);
}

// conversion de statique sur fichier en dynamique dans le programme
t_noeud* fileToDyn(FILE* f, int r)
{
    t_noeud* n = NULL;
    t_noeuds enr;
    if (r != -1) {
        lireNoeud(f, r, &enr);
        n = (t_noeud*)malloc(sizeof(t_noeud));
        n->val = enr.val;
        n->g = fileToDyn(f, enr.g);
        n->d = fileToDyn(f, enr.d);
    }
    return n;
}

//Loader un arbre en dynamique dans le prg
t_noeud* loadArbre_dyn()
{
    FILE* f;
    t_noeud* rd = NULL;
    if (fopen_s(&f,"save arbre.bin", "rb") != 0)
        printf("probleme ouverture du fichier\n");
    else {
        rd = fileToDyn(f, 0);
        fclose(f);
    }
    return rd;
}
//-------------------------------------------------
void detruire_arbre_dyn(t_noeud** r)
{
    if (*r != NULL) {
        detruire_arbre_dyn(&(*r)->g);
        detruire_arbre_dyn(&(*r)->g);
        free(*r);
        *r = NULL;
    }
}
//-------------------------------------------------
void aff_indent_dyn(t_noeud* r, int niveau)
{
    int i;
    if (r != NULL) {
        for (i = 0; i < niveau; i++) // 5 espaces par niveau
            printf("%5s", " ");
        printf("%4d\n", r->val);
        aff_indent_dyn(r->g, niveau + 1);
        aff_indent_dyn(r->d, niveau + 1);
    }
}
//-------------------------------------------------
//Sauver un arbre statique dans le programme

//1  obtenir la taille arbre statique
int taille_stat(t_noeuds* rs, int r)
{
    int res = 0;
    if (r != -1)
        res = 1 + taille_stat(rs, rs[r].g) + taille_stat(rs, rs[r].d);
    return res;
}

//2   sauvegarde
void save_arbre_stat(t_noeuds* rs, int r)
{
    FILE* f;
    int nb;
    fopen_s(&f,"save arbre.bin", "wb");
    if (f == NULL || rs == NULL)
        printf("probleme fichier ou arbre inexistant\n");
    else {
        // attention suppose un arbre complet dans lequel la taille du tableau
        // correspond au nombre des noeuds. Sinon il faut calculer autrement
        // la taille du tableau
        nb = taille_stat(rs, r);
        fwrite(rs, sizeof(t_noeuds), nb, f);
        fclose(f);
    }
}
//-------------------------------------------------
//loader un arbre en statique dans le programme

// 1 obtenir la taille de l'arbre sur le fichier
int taille_file(FILE* f, int r)
{
    t_noeuds enr;
    int res = 0;
    if (r != -1) {
        lireNoeud(f, r, &enr);
        res = 1 + taille_file(f, enr.g) + taille_file(f, enr.d);
    }
    return res;
}

// 2 loader l'arbre
t_noeuds* loadArbre_stat()
{
    FILE* f;
    t_noeuds* rs = NULL;
    int nb;

    if (fopen_s(&f,"save arbre.bin", "rb") != 0)
        printf("probleme fichier\n");
    else {
        nb = taille_file(f, 0);
        rewind(f);
        rs = (t_noeuds*)malloc(sizeof(t_noeuds) * nb);
        fread(rs, sizeof(t_noeuds), nb, f);
        fclose(f);
    }
    return rs;
}
//-------------------------------------------------
void detruire_arbre_stat(t_noeuds** r)
{
    if (*r != NULL) {
        free(*r);
        *r = NULL;
    }
}
//-------------------------------------------------
void aff_indent_stat(t_noeuds t[], int r, int niveau)
{
    int i;
    if (t == NULL)
        printf("arbre inexistant\n");
    else if (r != -1) {
        for (i = 0; i < niveau; i++) // 5 espaces par niveau
            printf("%5s", " ");
        printf("%4d\n", t[r].val);
        aff_indent_stat(t, t[r].g, niveau + 1);
        aff_indent_stat(t, t[r].d, niveau + 1);
    }
}
*/
/************************************************************
*                                                           *
*     arbre binaire sur fichier                             *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>

// noeud arbre statique
typedef struct noeuds{
   int val;
   int g, d;
}t_noeuds;

//-------------------------------------------------
void lire_noeud(FILE* f, int nieme, t_noeuds* enr)
{
    fseek(f, sizeof(t_noeuds) * nieme, SEEK_SET);
    fread(enr, sizeof(t_noeuds), 1, f);
}
void ecrire_noeud(FILE* f, int nieme, t_noeuds* enr)
{
    fseek(f, sizeof(t_noeuds) * nieme, SEEK_SET);
    fwrite(enr, sizeof(t_noeuds), 1, f);
}
//-------------------------------------------------
void aff_indent_file(FILE*f, int r,int niveau)
{
t_noeuds enr;
int i;
   if (r!=-1){
      lireNoeud(f,r,&enr);
      for (i=0; i<niveau; i++)
         printf("%5s"," ");
      printf("%d",enr.val);
      aff_indent_file(f,enr.g,niveau+1);
      aff_indent_file(f,enr.d,niveau+1);
   }
}
*/

