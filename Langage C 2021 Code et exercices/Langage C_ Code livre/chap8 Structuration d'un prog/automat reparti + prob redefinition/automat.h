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
int MAT[TY][TX] = { 0 };
int SAV[TY][TX] = { 0 };

void    init_matrice(void);
int     compte_voisins(int x, int y);
void    calcul(void);
void    copie(void);
void    affiche(void);
void    gotoxy(int x, int y);
void    textcolor(int color);

#endif