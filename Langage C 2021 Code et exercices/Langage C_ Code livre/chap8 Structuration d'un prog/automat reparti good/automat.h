#ifndef AUTOMAT_H 
#define AUTOMAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define TX  80
#define TY  25

// pose problème
//int MAT[TY][TX] = { 0 };
//int SAV[TY][TX] = { 0 };

/*
// solution 1 :
// pas d'initialisation à la définition
// pour éviter une redéfinition à chaque inclusion
// Cela signifie aussi que les tableaux ne sont pas 
// mis à 0 au départ et la fonction d'initialisation
// doit s'en charger.
int MAT[TY][TX];
int SAV[TY][TX];
*/

// Solution 2 :
// les matrices sont définies et initialisées sur 
// un fichier externe et la déclaration (c'est à
// dire l'annonce de l'existence des matrices)
// est déplacée dans la librairie avec le mot clé extern
// les deux matrices sont sur main.c
extern int MAT[TY][TX];
extern int SAV[TY][TX];

void    init_matrice(void);
int     compte_voisins(int x, int y);
void    calcul(void);
void    copie(void);
void    affiche(void);
void    gotoxy(int x, int y);
void    textcolor(int color);

#endif