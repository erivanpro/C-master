/*************************************************************
fourmi 1 : une fourmi mobile à l'écran
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
// en global définition du type de la structure fourmi
typedef struct {
	float x, y; // la position de la fourmi
	float dx, dy; // le déplacement
	int color; // la couleur
	int lettre; // l'apparence
}fourmi;

// Limites de la zone de jeu
const int TX = 40;
const int TY = 20;

// les actions
fourmi	init(void);
void	affiche(fourmi f, int color);
fourmi	avance(fourmi f);
int		top(int*start, int dur);
void	gotoxy(int x, int y);
void	textcolor(int color);
/*************************************************************
ACTION
*************************************************************/
int main()
{
	int start = 0;
	fourmi f;
	srand(time(NULL));
	f = init();
	while (!_kbhit()){
		if (top(&start, 75)){
			affiche(f, 0); // effacer
			f = avance(f); // changer la position
			affiche(f, f.color); // réafficher
		}
	}
	return 0;
}
/*************************************************************
INITIALISATION
*************************************************************/
fourmi init()
{
	fourmi f;
	f.x = rand() % TX;
	f.y = rand() % TY;
	f.dx = ((float)rand() / RAND_MAX) * 4 - 2;
	f.dy = ((float)rand() / RAND_MAX) * 4 - 2;
	f.lettre = 'A' + rand() % 26;
	f.color = 1 + rand() % 255;
	return f;
}
/*************************************************************
AFFICHAGE
*************************************************************/
void affiche(fourmi f, int color)
{
	gotoxy(f.x, f.y);
	textcolor(color);
	putchar(f.lettre);
}
/*************************************************************
MOUVEMENT
*************************************************************/
fourmi avance(fourmi f)
{
	f.x += f.dx;
	if (f.x < 0){
		f.x = 0;
		f.dx = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.x >= TX){
		f.x = TX - 1;
		f.dx = ((float)rand() / RAND_MAX)* -2;
	}
	f.y += f.dy;
	if (f.y < 0){
		f.y = 0;
		f.dy = ((float)rand() / RAND_MAX) * 2;
	}
	if (f.y >= TY){
		f.y = TY - 1;
		f.dy = ((float)rand() / RAND_MAX)* -2;
	}
	return f;
}
/*************************************************************
OUTILS
*************************************************************/
int top(int*start, int dur)
{
	int res = 0;
	if (clock()>*start + dur){
		*start = clock();
		res = 1;
	}
	return res;
}
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
/*************************************************************
*************************************************************/