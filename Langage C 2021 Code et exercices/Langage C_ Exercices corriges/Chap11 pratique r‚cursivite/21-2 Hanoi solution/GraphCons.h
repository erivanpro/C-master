#ifndef GRAPHCONS_H
#define GRAPHCONS_H

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

/************************************************************
GENERAL
*************************************************************/
enum {
	BLACK,				// 0
	DARK_BLUE,			// 1
	DARK_GREEN,			// 2
	DARK_CYAN,			// 3
	DARK_RED,			// 4
	DARK_MAGENTA,		// 5
	DARK_YELLOW,		// 6
	DARK_WHITE,			// 7
	BRIGHT_BLACK,		// 8
	BRIGHT_BLUE,		// 9
	BRIGHT_GREEN,		// 10
	BRIGHT_CYAN,		// 11
	BRIGHT_RED,			// 12
	BRIGHT_MAGENTA,		// 13
	BRIGHT_YELLOW,		// 14
	WHITE,				// 15
	COLORMAX,			// 16
	INVISIBLE = 0
};

HANDLE G_GetConsOut();
HANDLE G_GetConsIn(void);
_Bool G_ConsCursor(_Bool val);
_Bool G_ConsCursorEtat(void);
void G_GraphPause(int x, int y, int color);
void G_Pause(void);
/************************************************************
TEMPS, TOPAGE
************************************************************/
int G_Top(int dur);
void G_Attendre(int dure);
/************************************************************
DIMENSIONS CONSOLE (RESOLUTION)
*************************************************************/
_Bool G_PleinEcran(void);
_Bool G_ConsResizeMax();
_Bool G_ConsResize(int width, int height);
COORD G_ConsMinSize(HANDLE h);
int G_ConsTX(void);
int G_ConsTY(void);
_Bool G_ConsClearTo(int backcolor, int forecolor, char lettre);
_Bool G_ConsClear(void);
/************************************************************
COULEUR
*************************************************************/
void G_TextColor(int color);

/************************************************************
AFFICHAGES DANS LA CONSOLE
*************************************************************/
_Bool G_Gotoxy(int x, int y);
_Bool G_Blit(CHAR_INFO*dat, SMALL_RECT*datsrc, SMALL_RECT*consdest);
void G_DrawChar(int x, int y, int lettre, int backcolor, int forecolor);

/************************************************************
TRACES GEOMETRIQUES
*************************************************************/
void G_LigneH(int x1, int y, int x2, int lettre, int bcolor, int fcolor);
void G_LigneV(int x, int y1, int y2, int lettre, int bcolor, int fcolor);
void G_Rect(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor);
void G_RectColors(int x1, int y1, int x2, int y2, int lettre, int bcolors[4], int fcolors[4]);
void G_FillRect(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor);
void G_DrawLigne(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor);
//COORD* G_StockLigne(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor);
//void G_DrawLigneMat(int(*m)[], int tx, int ty, int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor);
void G_DrawLigneAngle(int x, int y, int angle, int dist, int*ax, int *ay, int lettre, int bcolor, int fcolor);
void G_DrawCercle(int x, int y, int rayon, int lettre, int bcolor, int fcolor);
//COORD* G_StockCercle(int x, int y, int rayon, int lettre, int bcolor, int fcolor);
//void G_FillCercle(int x, int y, int rayon, int lettre, int bcolor, int fcolor);
//void G_FillCercleMat(int(*m)[], int tx, int ty, int x, int y, int rayon, int lettre, int bcolor, int fcolor);
/************************************************************
GESTION DES EVENEMENTS
*************************************************************/
int G_PollEvent(void);
_Bool G_FlushEvent(void);
_Bool G_KeyPressed(void);
_Bool G_KeyPressDown(void);
_Bool G_KeyPressUp(void);
_Bool G_KeyDown(int vk_touche);
_Bool G_KeyUp(int vk_touche);
char G_KeyAscii(void);
WORD G_KeyVK(void);
_Bool G_MouseEvent(void);
_Bool G_MouseEventClic(void);
_Bool G_MouseEventWeel(void);
_Bool G_MouseEventMove(void);
_Bool G_MouseClic(int button);
int G_MouseX(void);
int G_MouseY(void);


#endif