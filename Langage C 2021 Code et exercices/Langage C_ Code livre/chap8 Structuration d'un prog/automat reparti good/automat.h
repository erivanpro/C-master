#ifndef AUTOMAT_H 
#define AUTOMAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define TX  80
#define TY  25

// pose probl�me
//int MAT[TY][TX] = { 0 };
//int SAV[TY][TX] = { 0 };

/*
// solution 1 :
// pas d'initialisation � la d�finition
// pour �viter une red�finition � chaque inclusion
// Cela signifie aussi que les tableaux ne sont pas 
// mis � 0 au d�part et la fonction d'initialisation
// doit s'en charger.
int MAT[TY][TX];
int SAV[TY][TX];
*/

// Solution 2 :
// les matrices sont d�finies et initialis�es sur 
// un fichier externe et la d�claration (c'est �
// dire l'annonce de l'existence des matrices)
// est d�plac�e dans la librairie avec le mot cl� extern
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