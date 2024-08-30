#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 
#include <conio.h> 

// taille de la zone de jeu 
#define TX  80 
#define TY  24 

// position de départ de la zone de jeu 
#define STARTX  2 
#define STARTY  2 

// Les quatre directions 
enum { NORD, EST, SUD, OUEST };

// l'ensemble des variables pour la composition 
// du circuit
int D1, P1, D2, P2, D3, P3, D4, P4, D5, P5, D6, P6, NBTRAIT, NBTOUR;

// ensemble des variables pour avoir une voiture 
// (position, vitesse, direction, nombre de pas, 
// trait courant, compte-tours) 
int X, Y, VIT, DIR, PAS, IDTRAIT, TOUR;

// les déclarations des fonctions 
void    create_circuit1(void);
void    select_trait(void);
void    avancer(int l, int color1, int color2);
void    afficher(int x, int y, int l, int color);
void    gotoxy(int x, int y);
void    textcolor(int color);
void    pause(int x, int y);
/********************************************************
ACTION
********************************************************/
int main()
{
    int start = 0; // pour contrôle du temps 

    srand(time(NULL));

    // création circuit et initialisation voiture 
    create_circuit1();
    while (TOUR < NBTOUR) {
        // contrôle vitesse voiture 
        if (clock() > start + VIT) {
            start = clock();

            //nouveau trait ? 
            if (PAS == 0)
                select_trait();

            // avancer, lettre v pour voiture, 
            // effacement en noir, couleur voiture rouge 
            avancer('v', 0, 10);
        }
    }
    pause(0, TY);
    return 0;
}
/********************************************************
CREATION DU CIRCUIT
********************************************************/
/*
Un seul circuit. C'est un carré de 10 sur 10, deux tours
prévus. Initialisation des variables circuit en conséquence.
Initialisation de la voiture
*/
void create_circuit1()
{
    // définition du circuit 
    D1 = EST; // trait 1 
    P1 = 10;
    D2 = SUD;
    P2 = 10;
    D3 = OUEST;
    P3 = 10;
    D4 = NORD;
    P4 = 10;
    NBTRAIT = 4;
    NBTOUR = 2;

    // la voiture 
    X = STARTX;
    Y = STARTY;
    PAS = 0; // au départ rien 
    IDTRAIT = 0;
    TOUR = 0;
    VIT = 0;

}
/********************************************************
AVANCER
********************************************************/
/*
Sélection du trait à parcourir
*/
void select_trait()
{
    // contrôler si un tour a été effectué et affichage 
    // du nombre de tours réalisés 
    if (IDTRAIT == NBTRAIT) {
        TOUR++;
        IDTRAIT = 0;
        gotoxy(TX / 2, TY / 2);
        textcolor(12); // couleur vert 
        printf("TOUR : %d", TOUR);
    }

    // changement de la vitesse de la voiture (chaque trait 
    // est parcouru à une vitesse différente 
    VIT = 150 + rand() % 150;

    // sélection du trait 
    switch (IDTRAIT) {
    case 0:  // trait 1 
        DIR = D1;
        PAS = P1;
        break;
    case 1:  // trait 2 
        DIR = D2;
        PAS = P2;
        break;
    case 2:  // etc. 
        DIR = D3;
        PAS = P3;
        break;
    case 3:
        DIR = D4;
        PAS = P4;
        break;
    case 4:
        DIR = D5;
        PAS = P5;
        break;
    case 5:
        DIR = D6;
        PAS = P6;
        break;
    }
    // préparer pour le trait suivant 
    IDTRAIT++;
}
/*
Parcourir le trait courant
*/
void avancer(int l, int color1, int color2)
{
    if (PAS > 0) {
        // supprimer un pas 
        PAS--;

        // effacer 
        afficher(X, Y, l, color1);

        // déplacer selon direction 
        switch (DIR) {
        case NORD:     Y--;    break;
        case EST:      X++;    break;
        case SUD:      Y++;    break;
        case OUEST:    X--;    break;
        }

        // afficher à la nouvelle position 
        afficher(X, Y, l, color2);
    }
}
/*
afficher une position
*/
void afficher(int x, int y, int l, int color)
{
    gotoxy(x, y);
    textcolor(color);
    putchar(l);
}
/********************************************************
OUTILS
********************************************************/
void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void textcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void pause(int x, int y)
{
    gotoxy(x, y);
    printf("Appuyez sur Enter pour continuer...");
    rewind(stdin);
    char c = getchar();
}
/********************************************************
********************************************************/
