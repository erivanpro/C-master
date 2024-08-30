/********************************************************************
*                                                                   *
*       CHAPITRE 12 : 6. Arbre binaire de recherche                  *
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
*          6.2 Structure de données                         *
*          6.3 Insérer un élément selon sa clé              *
*          6.4 Rechercher un élément selon sa clé           *
*          6.5 Supprimer un élément                         *
*          6.6 Lister tous les éléments                     *
*          6.7 Afficher l'arbre                             *
*          6.8 Test dans le main()                          *                                                  *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define MAXNOEUD  15
#define PASY      2
typedef struct noeud {
    char* dat;
    struct noeud* g, * d;
}t_noeud;

int         menu(void);
int         compareCle(char* dat1, char* dat2);
void        inserer(t_noeud** r, char* dat);
t_noeud*    creerArbre_Alea(int nb);
t_noeud*    rechercher(t_noeud* r, char* dat);
void        graphInfixe(t_noeud* r, int* x, int y);
int         hauteur(t_noeud* r);
void        afficheArbre(t_noeud* r);
void        detruireArbre(t_noeud** r);
t_noeud**   listerArbre(t_noeud* r, int* nbNoeud);
int         taille_dyn(t_noeud* r);
void        affiche_liste(t_noeud* t[], int nb);
void        detruireListe(t_noeud*** l);
t_noeud*    suppNoeud(t_noeud** r, char* dat);
t_noeud*    rameneNoeudMax(t_noeud** r);
// tools
void        gotoxy(int x, int y);
int         wherey(void);
//-------------------------------------------------
int main()
{
    int fin = 0;
    t_noeud* r = NULL;
    t_noeud* n = NULL;
    char cle[16];

    srand((unsigned)time(NULL));
    while (!fin) {
        switch (menu()) {
        case 1:
            detruireArbre(&r);
            r = creerArbre_Alea(1 + rand() % MAXNOEUD);
            afficheArbre(r);
            break;
        case 2 :
        {
            char s[256];
            printf("choississez une cle : ");
            int cle = 0;
            scanf_s("%d", &cle);
            sprintf_s(s, 256, "%d/%c%c", cle, 'A' + rand() % 26, 'A' + rand() % 26);
            inserer(&r, s);
            afficheArbre(r);
        }
            break;
        case 3:
            if (r != NULL) {
                printf("entrer la cle du noeud a trouver :\n");
                fgets(cle, 16, stdin);
                n = rechercher(r, cle);
                if (n != NULL)
                    printf("trouve : %s\n", n->dat);
                else
                    printf("non trouve dans l'arbre\n");
            }
            else
                printf("arbre vide\n");
            break;

        case 4:
            if (r != NULL) {
                printf("entrer la cle du noeud a supprimer :\n");
                fgets(cle, 16, stdin);
                n = suppNoeud(&r, cle);
                if (n != NULL) {
                    free(n->dat);
                    free(n);
                }
                else
                    printf("pas de cle %s\n", cle);
                afficheArbre(r);
            }
            else
                printf("arbre vide\n");
            break;

        case 5:
            if (r != NULL) {
                int nb = 0;
                t_noeud** t = listerArbre(r, &nb);
                affiche_liste(t, nb);
                detruireListe(&t);
            }
            else
                printf("arbre vide\n");
            break;

        default: fin = 1;
        }
    }
    detruireArbre(&r);
    return 0;
}
//-------------------------------------------------
int menu()
{
    int res = -1;
    printf("1  : creer arbre de recherche, afficher \n"
        "2  : inserer afficher\n"
        "3  : rechercher\n"
        "4  : supprimer\n"
        "5  : lister\n"
    );

    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}
//-------------------------------------------------
int compareCle(char* dat1, char* dat2)// d1 comparé à d2
{
    int d1, d2;
    d1 = atoi(dat1);
    d2 = atoi(dat2);
    return(d1 == d2) ? 0 : ((d1 < d2) ? -1 : 1);
}
//-------------------------------------------------
void inserer(t_noeud** r, char* dat)
{
    t_noeud* n;
    int cmp;
    if (*r == NULL) {
        n = (t_noeud*)malloc(sizeof(t_noeud));
        int taille = strlen(dat) + 1;// +1 pour \0
        n->dat = (char*)malloc(taille);
        strcpy_s(n->dat, taille, dat);
        n->g = n->d = NULL;
        *r = n;
    }
    else if ((cmp = compareCle(dat, (*r)->dat)) == 0)//
        printf("erreur : la cle %s existe deja\n", dat);// pas 2 clés identiques
    else if (cmp < 0)
        inserer(&(*r)->g, dat);// passage adresse du pointeur fils gauche
    else
        inserer(&(*r)->d, dat);// passage adresse du pointeur fils droit
}
//-------------------------------------------------
t_noeud* creerArbre_Alea(int nb)
{
    t_noeud* r = NULL;
    char s[256];
    int i;
    for (i = 0; i < nb; i++) {
        sprintf_s(s, 256, "%d/%c%c", rand() % 100, 'A' + rand() % 26, 'A' + rand() % 26);
        inserer(&r, s);
    }
    return r;
}
//-------------------------------------------------
t_noeud* rechercher(t_noeud* r, char* dat)
{
    int cmp;
    t_noeud* res = NULL;
    if (r != NULL) {
        if ((cmp = compareCle(dat, r->dat)) == 0)
            res = r;
        else if (cmp < 0)
            res = rechercher(r->g, dat);
        else
            res = rechercher(r->d, dat);
    }
    return res;
}
//-------------------------------------------------
void graphInfixe(t_noeud* r, int* x, int y)
{
    if (r != NULL) {
        graphInfixe(r->g, x, y + PASY);
        gotoxy(*x, y);
        printf("%s", r->dat);
        *x += strlen(r->dat);//PASX;
        graphInfixe(r->d, x, y + PASY);
    }
}
//-------------------------------------------------
int hauteur(t_noeud* r)
{
    int res = 0;
    if (r != NULL)
        res = 1 + max(hauteur(r->g), hauteur(r->d));
    return res;
}
//-------------------------------------------------
void afficheArbre(t_noeud* r)
{
    int y = wherey() + 1;
    int x = 0;
    graphInfixe(r, &x, y);
    gotoxy(0, y + (hauteur(r) * PASY));
    printf("hauteur de l'arbre : %d\n", hauteur(r));
}
//-------------------------------------------------
void detruireArbre(t_noeud** r)
{
    if (*r != NULL) {
        detruireArbre(&(*r)->g);
        detruireArbre(&(*r)->d);
        free((*r)->dat);
        free(*r);
        *r = NULL;
    }
}
//-------------------------------------------------
t_noeud** listerArbre(t_noeud* r, int* nbNoeud)
{
    int t, q;
    t_noeud** tab = NULL;
    *nbNoeud = taille_dyn(r);
    if (*nbNoeud > 0) {
        tab = (t_noeud**)malloc(sizeof(t_noeud*) * (*nbNoeud));
        t = 0;
        q = 1;
        tab[t] = r;                  // racine en tête
        while (q < *nbNoeud) {
            if (tab[t]->g)          // si fils gauche ajouter
                tab[q++] = tab[t]->g;
            if (tab[t]->d)          // si fils droit ajouter
                tab[q++] = tab[t]->d;
            t++;                    // passer au suivant
        }
    }
    return tab;
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
void affiche_liste(t_noeud* t[], int nb)
{
    for (int i = 0; i < nb; i++) {
        printf("%s--", t[i]->dat);
    }
    putchar('\n');
}
//-------------------------------------------------
void detruireListe(t_noeud*** l)
{
    if (*l) {
        free(*l);
        *l = NULL;
    }
}
//-------------------------------------------------
t_noeud* suppNoeud(t_noeud** r, char* dat)
{
    int cmp;
    t_noeud* res = NULL;

    if (*r != NULL) {
        if ((cmp = compareCle(dat, (*r)->dat)) < 0)
            res = suppNoeud(&(*r)->g, dat);
        else if (cmp > 0)
            res = suppNoeud(&(*r)->d, dat);
        else {     // noeud trouvé, suppression
            res = *r;
            if (res->d == NULL)
                *r = res->g;
            else if (res->g == NULL)
                *r = res->d;
            else { // un fils gauche et un fils droit
                   // suppression plus grand à gauche
                res = rameneNoeudMax(&(*r)->g);
                int taille = strlen(res->dat) + 1;
                (*r)->dat = (char*)realloc((*r)->dat, taille);
                strcpy_s((*r)->dat, taille, res->dat);
            }
        }
    }
    return res;
}
//-------------------------------------------------
t_noeud* rameneNoeudMax(t_noeud** r)
{
    t_noeud* pg = NULL;
    if (*r != NULL) {
        if ((*r)->d == NULL) { // plus grand trouvé
            pg = *r;
            *r = (*r)->g;
        }
        else
            pg = rameneNoeudMax(&(*r)->d);
    }
    return pg;
}
//-------------------------------------------------
void gotoxy(int x, int y)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x,y };
    SetConsoleCursorPosition(h, c);
}
//-------------------------------------------------
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.Y;
}
*/
/************************************************************
*                                                           *
*     6.9 Dessiner l'arbre (avec les liens)                 *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


#define MAXNOEUD  15
#define PASY      2
typedef struct noeud {
    char* dat; // cle + datas
    int x, y;  // position
    struct noeud* g, * d;
}t_noeud;


int         menu(void);
int         compareCle(char* dat1, char* dat2);
void        inserer(t_noeud** r, char* dat);
t_noeud*    creerArbre_Alea(int nb);
t_noeud**   listerArbre(t_noeud* r, int* nbNoeud);
int         taille_dyn(t_noeud* r);
void        initPosNoeud(t_noeud* r, int* x, int y);
void        gotoxy(int x, int y);
void        dessinArbre(t_noeud* t[], int nbNoeud);
int         wherey(void);
void        detruireArbre(t_noeud** r);
//-------------------------------------------------
int main()
{
    int fin = 0, nb, x;
    t_noeud* r = NULL;
    t_noeud** t = NULL;

    srand((unsigned)time(NULL));
    while (!fin) {
        switch (menu()) {
        case 1:
            r = creerArbre_Alea(1 + rand() % MAXNOEUD);
            x = 0;
            initPosNoeud(r, &x, wherey() + 1);
            t = listerArbre(r, &nb);
            dessinArbre(t, nb);
            detruireArbre(&r);
            free(t);
            gotoxy(0, wherey() + 2);
            break;

        default: fin = 1;
        }
    }
    detruireArbre(&r);
    return 0;
}
//-------------------------------------------------
int menu()
{
    int res = -1;
    printf("1  : creer arbre de recherche, dessiner \n"
    );
    scanf_s("%d", &res);
    rewind(stdin);
    return res;
}
//-------------------------------------------------
int compareCle(char* dat1, char* dat2)// d1 comparé à d2
{
    int d1, d2;
    d1 = atoi(dat1);
    d2 = atoi(dat2);
    return(d1 == d2) ? 0 : ((d1 < d2) ? -1 : 1);
}
//-------------------------------------------------
void inserer(t_noeud** r, char* dat)
{
    t_noeud* n;
    int cmp;
    if (*r == NULL) {
        n = (t_noeud*)malloc(sizeof(t_noeud));
        int taille = strlen(dat) + 1;// +1 pour \0
        n->dat = (char*)malloc(taille);
        strcpy_s(n->dat, taille, dat);
        n->g = n->d = NULL;
        *r = n;
    }
    else if ((cmp = compareCle(dat, (*r)->dat)) == 0)//
        printf("erreur : la cle %s existe deja\n", dat);// pas 2 clés identiques
    else if (cmp < 0)
        inserer(&(*r)->g, dat);// passage adresse du pointeur fils gauche
    else
        inserer(&(*r)->d, dat);// passage adresse du pointeur fils droit
}
//-------------------------------------------------
t_noeud* creerArbre_Alea(int nb)
{
    t_noeud* r = NULL;
    char s[256];
    int i;
    for (i = 0; i < nb; i++) {
        sprintf_s(s, 256, "%d/%c%c", rand() % 100, 'A' + rand() % 26, 'A' + rand() % 26);
        inserer(&r, s);
    }
    return r;
}
//-------------------------------------------------
t_noeud** listerArbre(t_noeud* r, int* nbNoeud)
{
    int t, q;
    t_noeud** tab = NULL;
    *nbNoeud = taille_dyn(r);
    if (*nbNoeud > 0) {
        tab = (t_noeud**)malloc(sizeof(t_noeud*) * (*nbNoeud));
        t = 0;
        q = 1;
        tab[t] = r;                  // racine en tête
        while (q < *nbNoeud) {
            if (tab[t]->g)          // si fils gauche ajouter
                tab[q++] = tab[t]->g;
            if (tab[t]->d)          // si fils droit ajouter
                tab[q++] = tab[t]->d;
            t++;                    // passer au suivant
        }
    }
    return tab;
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
void initPosNoeud(t_noeud* r, int* x, int y)
{
    if (r != NULL) {
        initPosNoeud(r->g, x, y + PASY);
        r->x = *x;
        *x = *x + strlen(r->dat);
        r->y = y;
        initPosNoeud(r->d, x, y + PASY);
    }
}
//-------------------------------------------------
// dessiner l'arbre
void gotoxy(int x, int y)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h, c);
}

void dessinArbre(t_noeud* t[], int nbNoeud)
{
    int i, x, y, fx, dep;

    if (t != NULL) {
        for (i = 0; i < nbNoeud; i++) {
            x = t[i]->x;
            y = t[i]->y;
            gotoxy(x, y);
            printf("%s", t[i]->dat);
            if (t[i]->g) { // tracer trait pour fils gauche
                fx = t[i]->g->x + 2;
                dep = x;
                while (--dep > fx) { // trait de parent à fils vers gauche
                    gotoxy(dep, y);
                    putchar('_');
                }
                gotoxy(dep, y + 1);
                putchar('|');
            }
            if (t[i]->d) { // tracer trait pour fils droit
                fx = t[i]->d->x + 2;
                dep = x + strlen(t[i]->dat);
                while (dep < fx) {
                    gotoxy(dep, y);
                    putchar('_');
                    dep++;
                }
                gotoxy(dep, y + 1);
                putchar('|');
            }
        }
    }
}
//-------------------------------------------------
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(h, &info);
    return info.dwCursorPosition.Y;
}
//-------------------------------------------------
void detruireArbre(t_noeud** r)
{
    if (*r != NULL) {
        detruireArbre(&(*r)->g);
        detruireArbre(&(*r)->d);
        free((*r)->dat);
        free(*r);
        *r = NULL;
    }
}
*/

/* // quelques fonctins supplémentaires

/ ------------------------------------------------ -
void textcolor(int color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    free(h);
}
//-------------------------------------------------
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info.dwCursorPosition.X;
}

//-------------------------------------------------
void clrscr(int color)
{
    DWORD written;

    FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        color, 2000, (COORD) { 0, 0 }, & written);
    FillConsoleOutputCharacter(GetStdHandle
    (STD_OUTPUT_HANDLE), ' ',
        2000, (COORD) { 0, 0 }, & written);
    gotoxy(0, 0);
}*/

