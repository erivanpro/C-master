#include"automat.h"

/****************************************************************
*****************************************************************/
void affiche(void)
{
int x, y;
	for (y = 0; y<TY; y++){    
		for (x = 0; x<TX; x++){
			gotoxy(x, y);      
			if (MAT[y][x] == 1)  
				textcolor(192);  
			else
				textcolor(16);   
			putchar(' ');      
		}
	}
}
/****************************************************************
****************************************************************/
void gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(h, c);
}
/****************************************************************
*****************************************************************/
void textcolor(int color)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, color);
}
/****************************************************************
*****************************************************************/