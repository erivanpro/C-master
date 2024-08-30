/********************************************************************
*                                                                   *
*       CHAPITRE 12 : Les listes en C                  *
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
*       1.2 Implémenter une liste simple				    *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Structure de donnée d'un maillon
#define NOMMAX  80
typedef struct elem {

    int val;
    char s[NOMMAX];
    struct elem* suiv;
}t_elem;

int menu()
{
    int choix = 0;
    printf("1 Creer une liste de taille aleatoire\n"
        "2 Ajouter\n"
        "3 Inserer (ordre croissant)\n"
        "4 Supprimer debut\n"
        "5 Supprimer les maillons d'une valeur donnee\n"
        "6 detruire liste\n"
        "7 Sauver liste\n"
        "8 Charger liste\n");

    scanf_s("%d", &choix);
    rewind(stdin);

    return choix;
}

//Initialiser un maillon
t_elem* init()
{
    char* n[26] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
               "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

    t_elem* e = malloc(sizeof(t_elem));
    e->val = rand() % 21;
    strcpy_s(e->s, NOMMAX, n[rand() % 26]);
    e->suiv = NULL;
    return e;
}

//Ajouter au début
t_elem* ajout_debut1(t_elem* prem, t_elem* e)
{
    e->suiv = prem;
    prem = e;
    return prem;
}
void ajout_debut2(t_elem** prem, t_elem* e)
{
    e->suiv = *prem;
    *prem = e;
}

// Parcourir la liste
void parcourir(t_elem* prem)
{
    if (prem == NULL)
        printf("liste vide");
    else
        while (prem != NULL) {
            printf("%d%s--", prem->val, prem->s);
            prem = prem->suiv;
        }
    putchar('\n');
}

//Insérer
t_elem* inserer1(t_elem* prem, t_elem* e)
{
    t_elem* n, * prec;
    // si liste vide ou ajouter en premier
    if (prem == NULL || e->val <= prem->val) {  // attention <=
        e->suiv = prem;
        prem = e;
    }
    else {  // sinon chercher place précédente, insérer après
        n = prec = prem;
        while (n != NULL && e->val > n->val) {
            prec = n;
            n = n->suiv;
        }
        e->suiv = n;
        prec->suiv = e;
    }
    return prem;
}

void inserer2(t_elem** prem, t_elem* e)
{
    t_elem* n, * prec;
    if (*prem == NULL || e->val <= (*prem)->val){  // si au début
        e->suiv = *prem;
        *prem = e;
    }
    else {  // sinon chercher place
        n = prec = *prem;
        while (n != NULL && e->val > n->val) {
            prec = n;
            n = n->suiv;
        }
        e->suiv = n;
        prec->suiv = e;
    }
}

//Supprimer au début
void supprimer_debut(t_elem** prem)
{
    t_elem* n;
    if (*prem != NULL) {
        n = *prem;
        *prem = (*prem)->suiv;
        free(n);
    }
}

//Supprimer un élément sur critère
t_elem* critere_supp_un1(t_elem* prem, int val)
{
    t_elem* e = prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                prem = e->suiv;
            else
                prec->suiv = e->suiv;
        }
        else
            prec = e;
        e = e->suiv;
        if (n != NULL)
            free(n);
    }
    return prem;

}

void critere_supp_un2(t_elem** prem, int val)
{
    t_elem* e = *prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                *prem = e->suiv;
            else
                prec->suiv = e->suiv;
        }
        else
            prec = e;
        e = e->suiv;
        if (n != NULL)
            free(n);
    }
}

//Détruire la liste
void detruire_liste(t_elem** prem)
{
    t_elem* n;
    while (*prem != NULL) {
        n = *prem;
        *prem = (*prem)->suiv;
        free(n);
    }
    //ici *prem vaut NULL
}

void detruire_liste2(t_elem** prem)
{
    while (*prem != NULL)
        supprimer_debut(prem);
    //ici *prem vaut NULL
}

//Sauvegarder la liste
void sauver_liste(t_elem* prem)
{
    FILE* f;
    // si liste non vide
    if (prem != NULL) {

        //ouvrir un fichier binaire en écriture : suffixe b
        if (fopen_s(&f,"save liste.bin", "wb") == 0) {

            // parcourir la liste jusque fin
            while (prem != NULL) {

                // copier chaque maillon
                fwrite(prem, sizeof(t_elem), 1, f);

                // passer au maillon suivant
                prem = prem->suiv;
            }
            fclose(f);	// fermer le fichier
        }
        else
            printf("erreur création fichier\n");
    }
    else
        printf("pas de sauvegarde pour une liste vide\n");
}

// charger une liste
t_elem* load_liste()
{
    FILE* f;
    t_elem* prem = NULL, * p, e;
    if (fopen_s(&f,"save liste.bin", "rb") == 0) {
        prem = malloc(sizeof(t_elem));
        fread(prem, sizeof(t_elem), 1, f);
        p = prem;
        while (fread(&e, sizeof(t_elem), 1, f)) {
            p->suiv = malloc(sizeof(t_elem));
            p = p->suiv;
            *p = e;
            p->suiv = NULL;
        }
        fclose(f);
    }
    else
        printf("erreur ou fichier inexistant");
    return prem;
}

int main()
{
    t_elem* premier = NULL;
    t_elem* nouveau;
    int fin = 0;
    int i, nb;

    srand((unsigned)time(NULL));
    while (!fin) {
        i = menu();
        switch (i) {

        case 1: //Creer une liste de taille aleatoire

            if (premier != NULL) // détruire la liste existante
                detruire_liste2(&premier);

            nb = 1 + rand() % 20;
            for (i = 0; i < nb; i++) {
                nouveau = init();
                //premier = ajout_debut1(premier, nouveau); // test
                ajout_debut2(&premier, nouveau);
            }
            printf("%d elements :\n", nb);
            break;

        case 2: // Ajouter
            nouveau = init();
            ajout_debut2(&premier, nouveau); // test fonct 2
            break;

        case 3: // Inserer (ordre croissant)
            nouveau = init();
            inserer2(&premier, nouveau);
            // premier=inserer1(premier,nouveau);
            break;

        case 4: //Supprimer debut:
            supprimer_debut(&premier);
            break;

        case 5: // Supprimer un maillon d'une valeur donnee
            printf("entrer la valeur à supprimer :\n");
            scanf_s("%d", &nb);
            rewind(stdin);
            critere_supp_un2(&premier, nb);
            //premier=critere_supp_un1(premier,nb);
            break;

        case 6: // detruire liste
            detruire_liste(&premier); // test fonct1
            break;

        case 7: // Sauver liste
            sauver_liste(premier);
            break;

        case 8: // Charger liste
            premier = load_liste();
            break;

        default:
            fin = 1;
            detruire_liste2(&premier); // test fonct2
            detruire_liste(&premier);
            break;
        }
        parcourir(premier);
    }

    return 0;
}
*/
/************************************************************
*                                                           *
*       1.3 Implémenter une liste simple circulaire         *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Structure de données liste circulaire
#define NOMMAX  80
typedef struct elem {

    int val;		// 1 : les données
    char s[NOMMAX];

    struct elem* suiv;	// 2 : pour construire la liste

}t_elem;

// chaines en globale pour simuler des donnés
char* N[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
           "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

// pour choix dans le main
int menu()
{
    int choix = 0;
    printf("1 Ajouter\n"
        "2 supprimer\n"
        "3 detruire\n");
    scanf_s("%d", &choix);
    rewind(stdin);

    return choix;
}

//Initialiser un maillon
t_elem* init_elem(int val, char s[])
{
    t_elem* e;
    e = (t_elem*)malloc(sizeof(t_elem));
    e->val = val;
    strcpy_s(e->s,NOMMAX, s);
    e->suiv = e;     // pas de NULL, pointe sur lui-même
    return e;
}

//Ajouter un maillon
void ajout_suiv(t_elem** cour, t_elem* e)
{
    if (*cour == NULL)	// cas liste vide avec modif de courant
        *cour = e;
    else {
        e->suiv = (*cour)->suiv; // pas de modif de courant
        (*cour)->suiv = e;
    }
}

//Parcourir la liste
void affiche(t_elem* cour)
{
    t_elem* p;
    if (cour == NULL)
        printf("liste vide\n");
    else {
        p = cour;
        do {
            printf("%d%s--", p->val, p->s);
            p = p->suiv;
        } while (p != cour);
        putchar('\n');
    }
}

//Supprimer un maillon
void supp_suiv(t_elem** cour)
{
    t_elem* e;
    if (*cour != NULL) {
        e = (*cour)->suiv;
        (*cour)->suiv = e->suiv;
        if (*cour == e)
            *cour = NULL;
        free(e);
    }
}

//Détruire la liste
void detruire_liste(t_elem** cour)
{
    t_elem* p, * sup;
    if (*cour != NULL) {
        p = (*cour)->suiv;
        while (p != *cour) {
            sup = p;
            p = p->suiv;
            free(sup);
        }
        free(*cour);
        *cour = NULL;
    }
}

int main()
{
    t_elem* courant = NULL;
    t_elem* nouveau;
    int fin = 0;;
    int i;

    srand((unsigned)time(NULL));
    while (!fin) {
        i = menu();
        switch (i) {

        case 1: //ajouter
            nouveau = init_elem(rand() % 100, N[rand() % 26]);
            ajout_suiv(&courant, nouveau);
            break;

        case 2: // supprimer
            supp_suiv(&courant);
            break;

        case 3: // detruire
            detruire_liste(&courant);
            break;

        default:
            fin = 1;
            detruire_liste(&courant); // test fonct2
        }
        affiche(courant);
    }
    return 0;
}
*/
/************************************************************
*                                                           *
*       1.4 Implémenter une liste symétrique                *
*                                                           *
*************************************************************/
/*
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NOMMAX  80
typedef struct elem {
    // les datas
    int val;
    char s[NOMMAX];
    // mécanique de la chaine
    struct elem* suiv;
    struct elem* prec;
}t_elem;


// pour choix dans le main
int menu()
{
    int choix = 0;
    printf("1 Ajouter debut\n"
        "2 Ajouter fin\n"
        "3 Supprimer un element\n"
        "4 Copier\n"
        "5 Detruire\n");
    scanf_s("%d", &choix);
    rewind(stdin);

    return choix;
}

//Initialiser un élément
t_elem* init_elem()
{
    char* n[26] = { "A","B","C","D","E","F","G","H","I","J","K","L","M",
               "N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };

    t_elem* e = malloc(sizeof(t_elem));
    e->val = rand() % 26;
    strcpy_s(e->s,NOMMAX, n[rand() % 26]);
    e->suiv = NULL;
    e->prec = NULL;
    return e;
}

//Ajouter un élément au début
void ajouter_debut(t_elem** prem, t_elem* e)
{
    if (*prem) { // si déjà des éléments
        e->suiv = *prem;
        (*prem)->prec = e;	// lien vers précédent
        *prem = e;
    }
    else
        *prem = e;
}

//Ajouter un élément à la fin
void ajouter_fin(t_elem** prem, t_elem* e)
{
    t_elem* p;
    // si liste vide
    if (*prem == NULL)
        *prem = e;
    // sinon chercher dernier maillon
    else {
        p = *prem;
        while (p->suiv != NULL)
            p = p->suiv;
        // et ajouter le nouveau
        p->suiv = e;
        e->prec = p;
    }
    //remarque : avec une liste symétrique il peut être interessant
    //de conserver en permanence un pointeur sur le dernier maillon
    // afin d'accèder directement aux deux bouts de la chaine.
}

//Parcourir, afficher la liste
void afficher_chaine(t_elem* prem)
{
    if (prem == NULL)
        printf("liste vide\n");
    while (prem != NULL) {
        printf("%d%s--", prem->val, prem->s);
        prem = prem->suiv;
    }
    putchar('\n');
}

//Supprimer un élément
void supp_elem(t_elem** prem, t_elem* e)
{
    if (e->suiv != NULL)
        e->suiv->prec = e->prec;
    if (e->prec != NULL)
        e->prec->suiv = e->suiv;
    if (e == *prem)
        *prem = e->suiv;
}
//
void supp_elem_critere(t_elem** prem, int val)
{
    t_elem* e, * sup;
    if (*prem) {
        e = *prem;
        while (e != NULL) {
            sup = NULL;
            if (e->val == val) {
                supp_elem(prem, e);
                sup = e;
            }
            e = e->suiv;
            if (sup)
                free(sup);
        }
    }
}

//Détruire la liste
void detruire_liste(t_elem** prem)
{
    t_elem* sup;
    while (*prem != NULL) {
        sup = *prem;
        *prem = (*prem)->suiv;
        free(sup);
    }
}

//Copier une liste
t_elem* copie_liste(t_elem* prem)
{
    t_elem* prem2 = NULL, * e, * p;

    if (prem != NULL) {
        // le premier pour la nouvelle liste
        prem2 = (t_elem*)malloc(sizeof(t_elem)); // allocation + copie
        prem2->val = prem->val;
        strcpy_s(prem2->s, NOMMAX, prem->s);
        prem2->suiv = prem2->prec = NULL;

        p = prem2;
        prem = prem->suiv;

        // les suivants
        while (prem != NULL) {
            e = (t_elem*)malloc(sizeof(t_elem)); // nouveau copié
            e->val = prem->val;
            strcpy_s(e->s, NOMMAX, prem->s);
            e->suiv = NULL;

            p->suiv = e;         // ajouté à la nouvelle liste
            e->prec = p;
            p = e;
            prem = prem->suiv;
        }
    }
    return prem2;
}

int main()
{
    t_elem* premier = NULL;
    t_elem* copie = NULL;
    t_elem* e;
    int fin = 0;;
    int i, val;

    srand((unsigned)time(NULL));
    while (!fin) {
        i = menu();
        switch (i) {

        case 1: //ajouter debut
            e = init_elem();
            ajouter_debut(&premier, e);
            break;

        case 2: //ajouter fin
            e = init_elem();
            ajouter_fin(&premier, e);
            break;

        case 3: // supprimer
            printf("entrer la valeur de l'element a supprimer :\n");
            scanf_s("%d", &val);
            rewind(stdin);
            supp_elem_critere(&premier, val);
            break;

        case 4: // copier
            if (copie != NULL)
                detruire_liste(&copie);
            copie = copie_liste(premier);
            afficher_chaine(copie);
            break;

        case 5: // detruire
            detruire_liste(&premier);
            break;

        default:
            fin = 1;
            detruire_liste(&premier); // test fonct2
        }
        afficher_chaine(premier);
    }
    return 0;
}
*/
