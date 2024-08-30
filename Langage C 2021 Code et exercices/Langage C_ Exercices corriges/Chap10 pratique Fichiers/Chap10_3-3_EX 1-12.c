/*
*   Pour tester la solution d'un exercice il faut :
*   - faire un projet c en mode console
*   - copier le code correspondant dans le fichier c
*   - compiler et ex�cuter
*
*   ou
*   - copier tous dans le fichier c du projet
*   - enlever le commentaires de l'exercice � tester mettre en commentaire tous les autres
    ( pour obtenir ce r�sultat il suffit de fermer le commentaire de l'�nonc� de l'exercie
     � tester en laissant ouverts tous les autres)
*   - compiler et ex�cuter
*/
/************************************************************************
*   Chapitre 6 : Les pointeurs                                    *
*   3.   Pointeurs en param�tre de fonction                             *
*   3.3 Mise en pratique : passage par r�f�rence                        *
*************************************************************************

/*********************************
Passage par r�f�rence, base
**********************************
Exercice 1
Dans un programme, une fonction initialise deux entiers et un r�el avec des
valeurs al�atoires. Une autre fonction affiche les valeurs obtenues
Le programme quitte sur commande de l'utilisateur
*
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void init(int*i1, int*i2, float*f)
{
    *i1=rand()%1000;
    *i2=rand()%1000;
    *f=((float)rand()/RAND_MAX)*1000;
}
int main()
{
char continuer='o';
int v1,v2;
float f;
    srand(time(NULL));
    while(continuer=='o'){

        init(&v1,&v2,&f);
        printf("v1 : %d\nv2 : %d\nf : %f\n",v1,v2,f);

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Exercice 2
Dans un programme une fonction retourne le quotient et le reste de la division
d'un entier p par un entier q ; p et q sont obtenus soit de fa�on al�atoire soit
entr�s par l'utilisateur. Le programme quitte sur commande de l'utilisateur.
*
#include <stdlib.h>
#include <stdio.h>

void fonct(int p, int q, int*val, int*rest)
{
    *val= p/q;
    *rest=p%q;
}
int main()
{
char continuer='o';
int v1,v2,q,r;

    while(continuer=='o'){
        v1=rand()%1000;
        v2=1+rand()%1000;
        fonct( v1,v2 ,&q,&r);

        printf("%d/%d=%d reste %d\n",v1,v2,q,r);

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Exercice 3
Dans une fonction les  valeurs de deux variables pass�es par r�f�rence
sont �chang�es. Faire un programme avec saisie des valeurs et affichage
�change, affichage du r�sultat, quitter ou recommencer
*
#include <stdlib.h>
#include <stdio.h>

void echange(int*v1,int*v2)
{
int tmp;
    tmp=*v1;
    *v1=*v2;
    *v2=tmp;
}

int main()
{
char continuer='o';
int v1,v2;
    while(continuer=='o'){

        printf("entrer deux valeurs :");
        scanf("%d%d",&v1,&v2);
        rewind(stdin);

        printf("v1=%d, v2=%d\n",v1,v2);
        echange(&v1,&v2);
        printf("v1=%d, v2=%d\n",v1,v2);

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Exercice 4
Soit une structure comprenant une position (r�el), un d�placement (r�el),
une lettre (entier) et une couleur (entier).  dans un programme :
d�finir un type et d�clarer deux structures
�crire une fonction qui permet d'initialiser deux structures en un seul appel
(les structures sont pass�es par r�f�rence).
�crire une fonction qui permet d'�changer les contenus des deux structures.
quitter ou recommencer.
*
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct{
    float x,y,dx,dy;
    int l;
    int color;
}t_test;

t_test _init()
{
t_test t;
    t.x=rand()%100;
    t.y=rand()%100;
    t.dx=rand()%4-2;
    t.dy=rand()%4-2;
    t.l='A'+rand()%26;
    t.color=rand()%255;
    return t;
}

void init(t_test*t1, t_test*t2)
{
    *t1=_init();
    *t2=_init();
}

void echange(t_test*t1, t_test*t2)
{
t_test tmp;
    tmp=*t1;
    *t1=*t2;
    *t2=tmp;
}

void affiche(t_test t)
{
        printf("pos(%.2f-%.2f), dep(%.2f-%.2f), color(%d), lettre %c\n",
               t.x,t.y,t.dx,t.dy,t.color,t.l);
}
int main()
{
char continuer='o';
t_test t1,t2;

    srand(time(NULL));
    while(continuer=='o'){

        init(&t1,&t2);
        affiche(t1);
        affiche(t2);
        echange(&t1,&t2);
        affiche(t1);
        affiche(t2);


        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Exercice 5
Dans un programme :
�crire une fonction d'allocation dynamique d'un tableau de n entiers
(la taille est obtenue soit via l'utilisateur, soit de fa�on al�atoire)
�crire une fonction d'initialisation du tableau avec des valeurs comprises
entre un seuil bas et  un seuil haut fournis en param�tre de la fonction.
�crire une fonction de r�cup�ration des seuils bas et haut
�crire une fonction d'affichage d'un  tableau de n �l�ments
�crire une fonction qui permet au contexte d'appel de d�terminer les valeurs
maximale et minimale d'un tableau d'entiers de taille n pass� en argument.
La fonction ne retourne rien mais les valeurs doivent pouvoir �tre r�cup�r�es
dans le contexte d'appel sans utilisation de variable globale.
Tester dans un programme qui s'arr�te lorsque l'utilisateur le demande.
*
#include <stdlib.h>
#include <stdio.h>

int* alloue(int nb)
{
    return malloc(sizeof(int)*nb);
}

void init(int t[],int nb, int sb, int sh)
{
int i;
    for (i=0; i<nb; i++)
        t[i]=sb+rand()%(sh-sb);
}

void recup_seuil(int*sb, int*sh)
{
    printf("entrer seuil bas et seuil haut : ");
    scanf("%d%d",sb,sh);
    rewind(stdin);
}
void affiche(int t[], int nb)
{
 int i;
        for (i=0; i<nb; i++)
            printf("%d ",t[i]);
        putchar('\n');
}
void min_max(int t[], int nb,int*min, int*max)
{
int i;
    *min=100000;
    *max=0;
    for (i=0; i<nb; i++){
        if(t[i]<*min)
            *min=t[i];
        if(t[i]>*max)
            *max=t[i];
    }
}

int main()
{
char continuer='o';
int*tab, nb,sb,sh,min,max;

    while(continuer=='o'){
        printf("entrer une taille de tableau : ");
        scanf("%d",&nb);
        rewind(stdin);
        if(nb<1)
            nb=1;

        tab=alloue(nb);
        recup_seuil(&sb,&sh);
        init(tab,nb,sb,sh);
        affiche(tab,nb);
        min_max(tab,nb,&min,&max);
        printf("min : %d\n",min);
        printf("max : %d\n",max);
        free(tab);


        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************************
Passage par r�f�rence, op�rateurs bit � bit
**********************************************
Exercice 6
Vous devez r�aliser en C  une librairie pour programmer des micro-contr�leurs.
Voici quelques unes des fonctions � faire :

bit_clear()
Syntaxe�: bit_clear(var,bit)
r�le�   : mettre � 0 le bit "bit de la variable "var"
exemple�: bit_clear(a, 3)�;  // met � 0 le bit 3 de a

bit_set()
Syntaxe�: bit_set(var, bit)
R�le�   : mettre � 1 le bit "bit de la variable "var"
Exemple�: bit_set(a,5)�; met � 1 le bit 5 de a

bit_test()
Syntaxe�: bit_test(var, bit)
R�le�   : test l'�tat du bit "bit" de la variable "var"
Exemple�: a=2�;
          bit_test(a, 2)�; retourne 1, bit 2 de a � 1

get_oct()
Syntaxe�: get_oct(var,oct)
R�le�   : retourne la valeur de l'octet "oct" de la
          variable "var"
Exemple�: a=0xFF00�;
          get_oct(a,2)�; retourne 255

set_oct()
Syntaxe�: set_oct(adresse,oct,val)
R�le�   : met � "val" l'octet "oct" de la variable
          "var"
Exemple�: a=0�;
          set_oct(&a,0,0xF)�; donne la valeur d�cimale
                              15 � l'octet 0 de a

set_hight()
Syntaxe�: set_hight(adresse,oct)
R�le�   : met � 1 les bits de l'octet "oct"
Exemple�: a=0
          set_hight(&a,3)�; met � 1 les 8 bits du
                            dernier octet de a

set_low()
Syntaxe�: set_low(adresse,oct)
R�le�   : met � 0 les bits de l'octet "oct"
Exemple�: a=7654
          set_hight(&a,0)�; met � 0 les 8 bits du
                            premier octet de a

rotate_left()
Syntaxe�: rotate_left(adress,oct, n)
R�le�   : rotation � gauche de n positions de l'octet
          "oct"
Exemple�: a=512�;
          rotate_left(&a,2,3)�; fait tourner de trois
                                bits vers gauche
                                l'octet 2 de a

rotate_right()
Syntaxe�: rotate_right(adress,oct, n)
R�le�   : rotation � droite de n positions de l'octet
          "oct"
Exemple�: a=512�;
          rotate_right(&a,2,3)�; fait tourner de trois
                                bits vers droite
                                l'octet 2 de a
*
#include <stdlib.h>
#include <stdio.h>

int main()
{
char continuer='o';

    while(continuer=='o'){

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/***********************************
Passage de pointeurs par r�f�rence
************************************
Exercice 7
Dans un programme, dans la boucle principale :
les tailles d'un tableau de floats et la taille d'un tableau d'entiers sont
donn�es au hasard
une fonction alloue dynamiquement les deux tableaux � la fois
une fonction initialise les deux tableaux
une fonction affiche les deux tableaux
quitter ou recommencer, attention � la m�moire.
*
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void alloue(int**i,int nbi, float**f, int nbf)
{
int k;
    *i=(int*)malloc(sizeof(int)*nbi);
    *f=(float*)malloc(sizeof(float)*nbf);
}
void init(int*i, int nbi, float*f, int nbf)
{
int k;
    for (k=0;k<nbi; k++)
        i[k]=rand()%100;
    for (k=0; k<nbf; k++)
        f[k]=(rand()%1000)/100.0;
}
void affiche(int*i, int nbi, float*f, int nbf)
{
int k;
    for (k=0;k<nbi; k++)
        printf("%3d",i[k]);
    putchar('\n');
    for (k=0; k<nbf; k++)
        printf("%5.2f",f[k]);
    putchar('\n');
}
void libere(int**i, float**f)
{
    free(*i);
    *i=NULL; // le passage par r�f�rence permet �a (i dans le main passe � NULL)
    free(*f);
    *f=NULL;
}

int main()
{
char continuer='o';
float*f;
int*i,nbi,nbf;

    srand(time(NULL));
    while(continuer=='o'){

        nbi=1+rand()%20;
        nbf=1+rand()%20;

        alloue(&i,nbi,&f,nbf);
        init(i,nbi,f,nbf);
        affiche(i,nbi,f,nbf);
        libere(&i,&f);

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Exercice 8
dans un programme
l'utilisateur entre la taille d'une matrice
la matrice est allou�e dynamiquement dans une proc�dure (pas de retour)
une fonction initialise la matrice avec des valeurs
une fonction affiche la matrice
quitter ou recommencer, attention m�moire
*
#include <stdlib.h>
#include <stdio.h>

void alloue(int***m, int ty, int tx)
{
int y;
    *m=(int**)malloc(sizeof(int*)*ty);
    for (y=0; y<ty; y++)
        (*m)[y]=(int*)malloc(sizeof(int)*tx);
}

void init(int**m, int ty, int tx)
{
 int y,x;

    for (y=0; y<ty; y++)
        for (x=0; x<tx; x++)
            m[y][x]=rand()%100;
}

void affiche(int**m, int ty, int tx)
{
 int y,x;

    for (y=0; y<ty; y++){
        for (x=0; x<tx; x++)
            printf("%3d",m[y][x]);
        putchar('\n');
    }
}
void libere (int***m, int ty)
{
int y;
    for (y=0; y<ty; y++)
        free((*m)[y]);
    free(*m);
    *m=NULL;
}

int main()
{
char continuer='o';
int**m,tx, ty;

    while(continuer=='o'){

        ty=1+rand()%20;
        tx=1+rand()%20;
        alloue(&m,ty,tx);
        init(m,ty,tx);
        affiche(m,ty,tx);
        libere(&m,ty);

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Exercice 9
Dans une programme, quatre chaines de caract�res sont d�clar�es sous la forme :
char*s1,*s2,*s3,*s4;
une fonction permet de saisir les quatre chaines de caract�res � la fois
une fonction permet de les afficher une par une
quitter ou recommencer
*
#include <stdlib.h>
#include <stdio.h>

char* saisie(char*msg)
{
char buf[256];
char*s;
    printf("%s",msg);
    fgets(buf,256,stdin);
    s=(char*)malloc(sizeof(char)*(strlen(buf)+1));
    strcpy(s,buf);
    return s;
}

void saisie_all(char**s1,char**s2,char**s3,char**s4)
{
    *s1=saisie("entrer chaine 1 :");
    *s2=saisie("entrer chaine 2 :");
    *s3=saisie("entrer chaine 3 :");
    *s4=saisie("entrer chaine 4 :");
}

// lib�ration :
// si j'�cris
//void libere_all(char*s1,char*s2,char*s3,char*s4)
//{
//    free(s1);
//    free(s2);
//    free(s3);
//    free(s4);
// les blocs aux adresses sp�cifi�essont bien d�allou�es mais les pointeurs
// s1, s2, s3, s4 dans le main contiennent toujours ces adresses
// }
//
// de ce fait il peut �tre int�ressant de mettre ces pointeurs � NULL afin
// que le programme puisse tester la validit� des adresses, dans ce cas un
// passage par r�f�rence est n�cessaire :
void libere_all(char**s1,char**s2,char**s3,char**s4)
{
    free(*s1);
    *s1=NULL;
    free(*s2);
    *s2=NULL;
    free(*s3);
    *s3=NULL;
    free(*s4);
    *s4=NULL;
}

int main()
{
char continuer='o';
char*s1,*s2,*s3,*s4;

    while(continuer=='o'){

        saisie_all(&s1,&s2,&s3,&s4);
        printf("%s",s1);
        printf("%s",s2);
        printf("%s",s3);
        printf("%s",s4);
        libere_all(&s1,&s2,&s3,&s4);

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Exercice 10
Dans un jeu il y a des trolls avec une position (x,y) et une couleur.
d�finir une structure t_troll
�crire une fonction d'allocation dynamique de tableau de t_troll
� 5 dimensions avec utilisation de return.
�crire une fonction d'allocation dynamique de tableau de t_troll
� 5 dimensions sans utilisation du return.
Ensuite toujours sans return d�composer l'allocation en �crivant
une fonction pour
chaque dimension (pour chaque nouvelle dimension appeler la fonction
de la dimension pr�c�dente, comme une sorte de cascade) :
Ecrire une fonction qui alloue un tableau � une dimension de t_troll
dont la taille est donn�e en param�tre.
Ecrire une fonction qui alloue un tableau � deux dimensions dont les
tailles sont donn�es en param�tre.
Ecrire une fonction qui alloue un tableau � trois dimensions dont les
tailles sont donn�es en param�tre.
Ecrire une fonction qui alloue un tableau � quatre dimensions dont les
tailles sont donn�es en param�tre.
Ecrire une fonction qui alloue un tableau � cinq dimensions dont les
tailles sont donn�es en param�tre.
Dans un main donnez un exemple d'appel qui permet d'avoir un tableau de
t_troll � 5 dimensions chacune entr�e par l'utilisateur.
Tester les programme, ajouter initialisation et affichage.
*
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct{
    int x,y,color;
}t_troll;

t_troll***** alloue1(int d5,int d4, int d3, int d2, int d1)
{
t_troll***** t;
int i,j,k,l;
    t=(t_troll*****)malloc(sizeof(t_troll****)*d5);
    for (i=0; i<d5; i++){
        t[i]=(t_troll****)malloc(sizeof(t_troll***)*d4);
        for (j=0; j<d4; j++){
            t[i][j]=(t_troll***)malloc(sizeof(t_troll**)*d3);
            for (k=0; k<d3; k++){
                t[i][j][k]=(t_troll**)malloc(sizeof(t_troll*)*d2);
                for (l=0; l<d2; l++){
                    t[i][j][k][l]=(t_troll*)malloc(sizeof(t_troll)*d1);
                }
            }
        }
    }

    return t;
}

void alloue2(t_troll******t,int d5,int d4, int d3, int d2, int d1)
{
int i,j,k,l;
    *t=(t_troll*****)malloc(sizeof(t_troll****)*d5);
    for (i=0; i<d5; i++){
        (*t)[i]=(t_troll****)malloc(sizeof(t_troll***)*d4);
        for (j=0; j<d4; j++){
            (*t)[i][j]=(t_troll***)malloc(sizeof(t_troll**)*d3);
            for (k=0; k<d3; k++){
                (*t)[i][j][k]=(t_troll**)malloc(sizeof(t_troll*)*d2);
                for (l=0; l<d2; l++){
                    (*t)[i][j][k][l]=(t_troll*)malloc(sizeof(t_troll)*d1);
                }
            }
        }
    }
}

void libere(t_troll******t, int d5,int d4, int d3, int d2)
{
int i,j,k,l;

    for (i=0; i<d5; i++){
        for (j=0; j<d4; j++){
            for (k=0; k<d3; k++){
                for (l=0; l<d2; l++){
                    free((*t)[i][j][k][l]);
                }
                free((*t)[i][j][k]);
            }
            free((*t)[i][j]);
        }
        free((*t)[i]);
    }
    free(*t);
    *t=NULL;   // le passage par r�f�rence sert uniquement � pouvoir faire �a :
               // mettre le pointeur du contexte d'appel � NULL
}

t_troll init()
{
t_troll t;
    t.x=rand()%800;
    t.y=rand()%600;
    t.color=rand()%255;
    return t;
}
void init_all(t_troll*****t,int d5,int d4, int d3, int d2, int d1)
{
int i,j,k,l,m;
    for (i=0;i<d5; i++)
        for(j=0; j<d4; j++)
            for(k=0; k<d3; k++)
                for (l=0; l<d2; l++)
                    for (m=0; m<d1; m++){
                        t[i][j][k][l][m]=init();
                    }
}

void affiche_all(t_troll*****t,int d5,int d4, int d3, int d2, int d1)
{
int i,j,k,l,m;
    for (i=0;i<d5; i++)
        for(j=0; j<d4; j++)
            for(k=0; k<d3; k++)
                for (l=0; l<d2; l++)
                    for (m=0; m<d1; m++){
                        printf("t[%d][%d][%d][%d][%d] x=%4d, y=%4d, color=%4d\n"
                               ,i,j,k,l,m,
                               t[i][j][k][l][m].x,
                               t[i][j][k][l][m].y,
                               t[i][j][k][l][m].color);
                    }
}

void alloueD1(t_troll**t,int d1)
{
   *t=(t_troll*)malloc(sizeof(t_troll)*d1);
}
void alloueD2(t_troll***t,int d2,int d1)
{
int i;
    *t=(t_troll**)malloc(sizeof(t_troll*)*d2);
    for (i=0; i<d2; i++)
        //alloueD1(&(*t)[i],d1);
        alloueD1( *t+i,d1);
}
void alloueD3(t_troll****t,int d3,int d2, int d1)
{
int i;
    *t=(t_troll***)malloc(sizeof(t_troll**)*d3);
    for (i=0; i<d3; i++)
        //alloueD1(&(*t)[i],d1);
        alloueD2(*t+i,d2,d1);
}
void alloueD4(t_troll*****t,int d4,int d3,int d2, int d1)
{
int i;
    *t=(t_troll****)malloc(sizeof(t_troll***)*d4);
    for (i=0; i<d4; i++)
        //alloueD1(&(*t)[i],d1);
        alloueD3(*t+i,d3,d2,d1);
}
void alloueD5(t_troll******t,int d5,int d4,int d3,int d2, int d1)
{
int i;
    *t=(t_troll*****)malloc(sizeof(t_troll****)*d5);
    for (i=0; i<d5; i++)
        //alloueD1(&(*t)[i],d1);
        alloueD4(*t+i,d4,d3,d2,d1);
}

int main()
{
char continuer='o';
t_troll *****t1,*****t2,*****t3;
int d5,d4,d3,d2,d1;

    srand(time(NULL));
    while(continuer=='o'){

        // pour entrer utilisateur utiliser scanf
        // des valeurs al�atoires c'est plus rapide pour le test
        d5=1+rand()%5;
        d4=1+rand()%5;
        d3=1+rand()%5;
        d2=1+rand()%5;
        d1=1+rand()%5;

        printf("TEST 1-------------------\n");
        t1=alloue1(d5,d4,d3,d2,d1);
        init_all(t1,d5,d4,d3,d2,d1);
        affiche_all(t1,d5,d4,d3,d2,d1);
        libere(&t1,d5,d4,d3,d2);
        system("PAUSE");

        printf("TEST 2-------------------\n");
        alloue2(&t2,d5,d4,d3,d2,d1);
        init_all(t2,d5,d4,d3,d2,d1);
        affiche_all(t2,d5,d4,d3,d2,d1);
        libere(&t2,d5,d4,d3,d2);
        system("PAUSE");

        printf("TEST 3-------------------\n");
        alloueD5(&t3,d5,d4,d3,d2,d1);
        init_all(t3,d5,d4,d3,d2,d1);
        affiche_all(t3,d5,d4,d3,d2,d1);
        libere(&t3,d5,d4,d3,d2);
        system("PAUSE");

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
Passage de tableaux dynamiques
**********************************
Exercice 11
Dans un programme un tableau dynamique est d�clar� :
int *tab;
D'apr�s ces prototypes  :
void 	alloue1 	(int**t, int taille);
void 	alloue2	(int taille);
int* 	alloue3	(int taille);
void 	initialise1	(int t[], int taille);
void 	initialise2 	(int**t);
void 	initialise3	(int*t);
int*	initialise4	(void);

Quelles fonctions peuvent utiliser tab comme argument ? �crire les fonctions que
vous avez d�sign�es comme bonnes et faire un programme de test. Donnez les raisons
pour lesquelles vous avez rejet� les autres.
*
#include <stdlib.h>
#include <stdio.h>

void 	alloue1 	(int**t, int taille)
{
    *t=malloc(sizeof(int)*taille);
}

int *TAB2; // en global
void 	alloue2	(int taille)
{
    TAB2=(int*)malloc(sizeof(int)*taille);
}
int* 	alloue3	(int taille)
{
int *t=malloc(sizeof(int)*taille);
    return t;
}
void 	initialise1	(int t[], int taille)
{
int i;
    for (i=0; i<taille; i++)
        t[i]=rand()%100;
}
//void 	initialise2 	(int**t)
// possible mais mauvaise parce que l'allocation a lieu en dehors de l'initialisation

#define T3   10
void 	initialise3	(int*t)// suppose une taille de tableau en global
{
int i;
    for (i=0; i<T3; i++)
        t[i]=rand()%100;
}

//int*	initialise4	(void);
// possible mais mauvaise parce que l'allocation a lieu en dehors de l'initialisation

void affiche(int t[], int taille)
{
int i;
    for (i=0; i<taille; i++)
        printf("%3d",t[i]);
    putchar('\n');
}
int main()
{
char continuer='o';
int*tab1,*tab3;
int t1,t2;
    while(continuer=='o'){

        printf("tab1 :\n");
        t1=1+rand()%20;
        alloue1(&tab1,t1);
        initialise1(tab1,t1);
        affiche(tab1,t1);
        printf("-----------------\n");

        printf("TAB2 (global):\n");
        t2=1+rand()%20;
        alloue2(t2);
        initialise1(TAB2,t2); // remarque : serait plus rigoureux qu'ici aussi le tableau soit consid�r� global
        affiche(TAB2,t2);
        printf("-----------------\n");

        printf("tab3 :\n");
        tab3=alloue3(T3);
        initialise3(tab3);
        affiche(tab3,T3);
        printf("-----------------\n");

        free(tab1);
        free(TAB2);
        free(tab3);

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }

    return 0;
}
/*********************************
Exercice 12
Dans un programme une matrice dynamique est d�clar�e :
int **mat;
D'apr�s ces prototypes  :
void 	alloue1 	(int***m, int lig, int col);
int** 	alloue2	(int lig, int col);
int* 	alloue3	(int*m[],int lig,int col);
void 	initialise1	(int m[][]);
void 	initialise2 	(int**m, int lig, int col);
void 	initialise3	(int*t, int lig);
int**	initialise4	(void);

Quelles fonctions peuvent utiliser tab comme argument ?
Ecrire les fonctions que vous avez d�sign�es comme bonnes
et faire un programme de test. Donnez les raisons pour lesquelles
vous avez rejet� les autres.
*
#include <stdlib.h>
#include <stdio.h>

void 	alloue1 	(int***m, int lig, int col)
{
int i;
    *m=(int**)malloc(sizeof(int*)*lig);
    for (i=0; i<lig; i++)
        (*m)[i]=(int*)malloc(sizeof(int)*col);
}
int** 	alloue2	(int lig, int col)
{
int **m,i;
    m=(int**)malloc(sizeof(int*)*lig);
    for (i=0; i<lig; i++)
        m[i]=(int*)malloc(sizeof(int)*col);
    return m;
}
//int* 	alloue3	(int*m[],int lig,int col); err conception, le param�tre m est en trop

//void 	initialise1	(int m[][]);
// err compilation pour une matrice m peut s'�crire :
// int**m, int* m[], int m[][DIM] (avec la dimension voulue specifi�e en DIM)

void 	initialise2 	(int**m, int lig, int col)
{
int i, j;
    for (i=0; i<lig; i++)
        for (j=0; j<col; j++)
            m[i][j]=rand()%100;
}

//void 	initialise3	(int*t, int lig); err int*t n'est pas une matrice

// int**	initialise4	(void);
// possible mais mauvais parce que l'allocation a lieu en dehors de l'initialisation

void affiche(int**m, int lig, int col)
{
int i, j;
    for (i=0; i<lig; i++){
        for (j=0; j<col; j++)
            printf("%3d",m[i][j]);
        putchar('\n');
    }
}

void libere(int**m,int ty)
{
int i;
    for (i=0; i<ty; i++)
        free(m[i]);
    free(m);
}

int main()
{
char continuer='o';
int**m1,**m2;
int ty,tx;
    while(continuer=='o'){
        printf("matrice 1 :\n");
        ty=1+rand()%10;
        tx=1+rand()%20;
        alloue1(&m1,ty,tx);
        initialise2(m1,ty,tx);
        affiche(m1,ty,tx);
        libere(m1,ty);
        printf("--------------\n");

        printf("matrice 2 :\n");
        ty=1+rand()%10;
        tx=1+rand()%20;
        m2=alloue2(ty,tx);
        initialise2(m2,ty,tx);
        affiche(m2,ty,tx);
        libere(m2,ty);
        printf("--------------\n");

        printf("continuer ? (o/n)");
        scanf("%c",&continuer);
        rewind(stdin);
    }
    return 0;
}
/*********************************
*/
