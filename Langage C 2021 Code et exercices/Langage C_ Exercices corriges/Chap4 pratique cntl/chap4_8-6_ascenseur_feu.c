/*
DEUXIEME PARTIE : TOUR, ASCENSEUR ET FEU
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// affichage
const int DECX=5; // initialisation obligatoire � la
const int DECY=5; // d�claration pour les constantes

// immeuble
int NBETAGE;
int COULEUR;

// incendie, nouveau
const int COULEURFEU=12;        // rouge
int IBAS;       // etage bas de l'incendie
int IHAUT;      // etage haut de l'incendie

// les variables immeuble et les variables feu en globale
// signifient que les fonctions qui op�rent des traitements dessus
// pourront y acc�der directement. C'est ad�quat s'il n'y a qu'un seul
// immeuble et un seul feu par immeuble.

// gestion immeuble-ascenseur
void    creer_immeuble      (int min, int max);
void    affiche_immeuble    (int posasc);
void    affiche_etage       (int y,int color);
void    gotoxy              (int x, int y);
void    textcolor           (int color);
int     select_etage        (void);
int     cntl_feu            (int etage, int posasc);        // nouveau
int     move                (int y, int etage);             // du nouveau
void    attendre            (int duree);                    // nouveau
void    propage_feu         (int posasc);                   // nouveau
void    affiche_feu         (int bas, int haut, int color); // nouveau
/**********************************************
**********************************************/
int main()
{
int etage, posasc=0;
    srand(time(NULL));
    creer_immeuble(10,20);
    affiche_immeuble(posasc); // couleur lettre

    while(1){

        // l'�tage � atteindre
        etage=select_etage();
        if(etage<0)// une valeur n�gative met fin au programme
            break;
        // l'�tage peut �tre modifi� s'il y a un feu
        etage=cntl_feu(etage,posasc);

        // au d�part, la position ascenseur et l'�tage � atteindre
        // � lissue, la position ascenseur est �gale � l'�tage atteint
        posasc=move( posasc, etage);

        // g�n�ration de l'incendie avec affichage
        propage_feu(posasc);

    }
    gotoxy(DECX,DECY+NBETAGE+2);
    return 0;
}

/**********************************************
avoir l'immeuble (constructeur)
**********************************************/
void creer_immeuble(int min, int max)
{
    COULEUR=1+rand()%15;
    if (COULEUR==COULEURFEU)
        COULEUR++;

    NBETAGE=rand()%(max-min)+min;
    // pas d'incendie au d�part
    IBAS=IHAUT=-1;
}
/**********************************************
afficher l'immeuble (�tage par �tage)
**********************************************/
void affiche_immeuble(int posasc)
{
int y;
    for (y=0; y<=NBETAGE; y++)
        affiche_etage(y,COULEUR);
    affiche_etage(posasc,COULEUR<<4);  // inverse
}
/**********************************************
afficher un �tage
**********************************************/
void affiche_etage(int y,int color)
{
int posy;
    posy=NBETAGE-y; // inverser, partir du bas
    gotoxy(DECX,DECY+posy);
    textcolor(color);
    printf("%2d",y);
}
/**********************************************
tools curseur �criture
( tools : en quelque sorte, ne fait pas partie
 de l'algorithme sp�cifique � la tour infernale)
**********************************************/
void gotoxy(int x, int y)
{
COORD c;

    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/**********************************************
tools couleur
**********************************************/
void textcolor(int color)
{
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}
/**********************************************
S�lectionner un �tage � atteindre
**********************************************/
int select_etage()
{
int etage;
    //affichage s�lecteur
    textcolor(10);
    gotoxy(DECX*2,DECY+NBETAGE/2);
    printf("Entrer etage :     "); // avec effacement ancienne valeur

    // recup�ration �tage
    gotoxy(DECX*2+15,DECY+NBETAGE/2);
    scanf("%d",&etage);
    rewind(stdin);

    if(etage>NBETAGE)
        etage=NBETAGE;

    return etage;
}
/**********************************************
il s'agit ici de v�rifier si l'�tage � atteindre
est en feu ou non.
Si oui s'arr�ter d�s que le feu est rencontr�
**********************************************/
int cntl_feu(int etage, int posasc)
{
    // si �tage demand� dans feu
    if(etage>=IBAS && etage <=IHAUT){
        // si on monte
        if(posasc<etage)
            etage=IBAS-1;
        // si on descend
        // remarque : etage ne peut pas �tre �gal � posasc ET dans le feu
        else
            etage=IHAUT+1;
    }
    return etage;
}
/**********************************************
le mouvement tient compte maintenant des �tages
en feu : la couleur change
**********************************************/
int move( int y, int etage)
{
int color,pas;

    pas=(y<etage)? 1: -1;
    while(y!=etage){
        // effacer : si feu ou pas la couleur change
        color=(y>=IBAS && y<=IHAUT) ? COULEURFEU : COULEUR ;
        affiche_etage(y,color);
        // bouger
        y+=pas;
        // afficher
        color=(y>=IBAS && y<=IHAUT) ? COULEURFEU : COULEUR ;
        affiche_etage(y,color<<4);
        attendre(100);
    }
    return y;
}
/**********************************************
tools pour ralentir
**********************************************/
void attendre(int duree)
{
    int start=clock();
    while(clock()<start+duree){}
}
/**********************************************
L'incendie, plusieurs possibilit�s, � choisir :
- une case
- plusieurs cases avec taille fixe
- plusieurs cases avec taille variable  -> X // int�gre les deux pr�c�dentes
- propagation                           -> X // succession de la pr�c�dente
- plusieurs incendies

REMARQUE :
la fonction acc�de directement aux variables de l'incendie
IHAUT,IBAS et COULEURFEU qui sont d�clar�es en globale, de
m�me que les variables immeuble NBETAGE et COULEUR.
De ce fait la fonction ne peut �tre utilis�e que pour un
immeuble et un feu dans l'immeuble.
**********************************************/
void propage_feu(int posasc)
{
    // fonctionnement al�atoire
    if( rand()%1000>600){
        // si aucun incendie,en allumer un � un �tage
        if(IHAUT==-1){
            IHAUT=rand()%(NBETAGE+1);//nbetage fait partie de l'immeuble
            if(IHAUT==posasc){ // �viter la position o� se trouve l'ascenseur
                int deplace=rand()%2*2-1; //en dessus ou en dessous
                IHAUT = (IHAUT+deplace+NBETAGE+1)%(NBETAGE+1); // attention aux bords
            }
            IBAS=IHAUT; // un seul �tage pour commencer
        }
        // si d�j� un incendie, propager ou r�duire
        else{
            // propager 70% de chances, ne pas toucher � l'ascenseur
            if(rand()%100<=70){
                if(rand()%100<=70){ // vers le haut 70% de chance
                    if(IHAUT+1!=posasc && IHAUT+1<=NBETAGE)
                        IHAUT++;
                }
                else // vers le bas 30%
                    if(IBAS-1!=posasc && IBAS-1>0)
                        IBAS--;
            }
            // r�duire 30% de chances, ne pas oublier affichage (effacer feu)
            else{
                // conserver anciennes positions du feu pour effacement ensuite
                int ihaut=IHAUT;
                int ibas=IBAS;

                if (IHAUT==IBAS) // �teindre
                    IBAS=IHAUT=-1;
                else{
                    if(rand()%100<=50) // du haut 50% de chance
                        IHAUT--;
                    else
                        IBAS++ ; // du bas 50%
                }
                affiche_feu(ibas,ihaut,COULEUR);
            }
        }
        affiche_feu(IBAS,IHAUT,COULEURFEU);
    }
}
/**********************************************
**********************************************/
void affiche_feu(int bas, int haut, int color)
{
int y;
    if(haut!=-1){ // si feu uniquement
        for (y=bas; y<=haut; y++)
            affiche_etage(y,color);
    }
}
/**********************************************
**********************************************/
