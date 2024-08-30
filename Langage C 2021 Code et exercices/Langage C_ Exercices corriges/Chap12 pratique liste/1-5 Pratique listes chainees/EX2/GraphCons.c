#include "GraphCons.h"


/*
Baptis�e de GraphCons pour graphique console cette simple librairie
permet des cr�ations de jeux. Elle se compose des fichiers GraphCons.c
et GraphCons.h. Ces fichiers doivent �tre int�gr�s au projet et compil�s
avec lui.

GraphCons s'appuie sur l'API Win32 et l'ensemble des biblioth�ques
fournies avec Windows.h. Notamment elle comprend tout ce qui concerne la
console (kernel32.lib et kernel32.dll). Je ne suis pas un expert et certains 
points peuvent surement �tre am�lior�s. La documentation pour l'utilisation
de la console se trouve ici :
https://docs.microsoft.com/en-us/windows/console/console-reference


J'esp�re pouvoir pousser plus loin le d�veloppement de GraphCons, notamment en
introduisant le principe de pseudo images bitmap. Il faudrait �galement g�rer la
taille des polices utilis�es par la console ce qui permettrait d'�largir
consid�rablement la r�solution de la console.

Personnellement j'aime bien l'univers console qui rappelle les premi�res
heures de l'informatique et s'int�gre parfaitement dans l'ascii art.

Si vous trouvez de meilleurs solutions � certaines fonctionnalit�s de la librairie
n'h�sitez pas � me faire connaitre vos solutions, merci pour toutes ces �ventuelles 
corrections et am�liorations !
fdr@free.fr

*/

/************************************************************
GENERAL
*************************************************************
	Handle sur la console en sortie, indispensable pour toutes
	les op�rations d'affichage dans la console et de
	redimensionnement de la console.
*/
HANDLE G_GetConsOut()
{
	static HANDLE h = NULL;
	if (h == NULL) {
		h = GetStdHandle(STD_OUTPUT_HANDLE);
		if (h == INVALID_HANDLE_VALUE)
			exit(EXIT_FAILURE);
	}
	return h;
}
/*
	Handle sur le console en entr�e, indispensable pour la
	maitrise des �v�nements, clavier, souris etc.
*/
static DWORD StartMode = 0;
HANDLE G_GetConsIn()
{
	static HANDLE h = NULL;

	if (h == NULL) {

		h = GetStdHandle(STD_INPUT_HANDLE);
		if (h == INVALID_HANDLE_VALUE)
			exit(EXIT_FAILURE);
		if (!GetConsoleMode(h, &StartMode))
			printf("Error GetConsoleMode, StartMode perdu\n");
	}
	return h;
}
/* Param�trage du mode de la console.

Les bits et leurs attributions pour la fonction SetConsoleMode() :
https://docs.microsoft.com/en-us/windows/console/setconsolemode

0x200	(10 0000 0000)	ENABLE_VIRTUAL_TERMINAL_INPUT		-			-
0x100	( 1 0000 0000)	?									default		-
0x80	(   1000 0000)	ENABLE_EXTENDED_FLAGS				default		souris
0x40	(    100 0000)	ENABLE_QUICK_EDIT_MODE				default		-
0x20	(     10 0000)	ENABLE_INSERT_MODE					default		-
0x10	(      1 0000)	ENABLE_MOUSE_INPUT					default		souris
0x8		(        1000)	ENABLE_WINDOW_INPUT					-			-
0x4		(         100)	ENABLE_ECHO_INPUT					default		-
0x2		(          10)	ENABLE_LINE_INPUT					default		-
0x1		(           1)	ENABLE_PROCESSED_INPUT				default		-

Nous n'utilisons pas le redimensionnement de la fen�tre et pour la souris il faut d�connecter 
explicitement ENABLE_QUICK_EDIT_MODE

*/
// Le mode par d�faut est en r�alit� le mode Edit avec en plus le bit 0X100 � 1 (1 0000 0000) 
// ce bit n'est pas document� mais peut-�tre sert-il tout de m�m quelque part... dans le doute
// je conserve.
_Bool G_SelectDefaultMode()
{
	int res = TRUE;
	if (!SetConsoleMode(G_GetConsIn(), StartMode)) {
		printf("Error select edit mode\n");
		res = FALSE;
	}
	return res;
}
// le mode edit doit absolument �tre s�lectionn� avant l'utilisation de fonctions standart
// d'entr�es sur la console comme scanf et fgets.
_Bool G_SelectEditMode()
{
	_Bool res = TRUE;
	DWORD mode = 0;
	mode = ENABLE_EXTENDED_FLAGS | ENABLE_QUICK_EDIT_MODE | ENABLE_INSERT_MODE | 
		   ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(G_GetConsIn(), mode)) {
		printf("Error select edit mode\n");
		res = FALSE;
	}
	return res;
}
// Cette fonction de s�lection du mode Event est appel�e par la fonction G_PollEvent(). 
// S'il y a r�cup�ration d'�v�nements le mode courant devient celui-ci. Pour utiliser 
// n�anmoins scanf ou fgets il est n�c�ssaire juste avant de r�tablir le mode Edit
// avec un appel � la fonction G_SelectEditMode()
_Bool G_SelectEventMode()
{
	_Bool res = TRUE;
	DWORD mode = 0;
	mode = (/*ENABLE_WINDOW_INPUT |*/ ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS) & 
		      ~(ENABLE_QUICK_EDIT_MODE /*| ENABLE_WINDOW_INPUT*/);
	if (!SetConsoleMode(G_GetConsIn(), mode)) {
		printf("Error select event mode\n");
		res = FALSE;
	}
	return res;
}
/**********************************************
Supprime le curseur en �criture si false, l'affiche si true
*/
_Bool G_ConsCursor(_Bool val)
{
	CONSOLE_CURSOR_INFO cursorInfo;

	if (!GetConsoleCursorInfo(G_GetConsOut(), &cursorInfo))
		return FALSE;
	cursorInfo.bVisible = val;
	if (!SetConsoleCursorInfo(G_GetConsOut(), &cursorInfo))
		return FALSE;
	return TRUE;
}
_Bool G_ConsCursorEtat()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(G_GetConsOut(), &cursorInfo);
	return cursorInfo.bVisible;
}
/*****************************************
	Permet de stoper le d�roulement du programme
*/
void G_GraphPause(int x, int y, int color)
{
	G_Gotoxy(x, y);
	G_TextColor(color);
	printf("Presser Enter pour quitter");
	getchar();
}
void G_Pause()
{
	printf("Presser Enter pour quitter");
	getchar();
}
/************************************************************
TEMPS, TOPAGE
************************************************************/
/*
chronom�trage des espace de temps pour controler la
vitesse des animations
*/
int G_Top(int dur)
{
	static int start = 0;
	int res = 0;
	if (clock() > start + dur) {
		start = clock();
		res = 1;
	}
	return res;
}
void G_Attendre(int dure)
{
	int start = clock();
	while (clock() < start + dure) {}
}
/************************************************************
PLEIN ECRAN ET GESTION FENETRE CONSOLE (Dimension et r�solution 
en caract�re, position � l'�cran...)
*************************************************************

Plein �cran
 L'objectif du plein �cran est de simuler une page graphique et la taille de la surface
 doit �tre parfaitement ajust�e avec le buffer console, sans ascenceur pour la hauteur
 ou pour la largeur.
 A priori le passage en plein �cran revient � prendre tout l'�cran 
 comme avec une fen�tre sans la barre de controle. Cependant le buffer
 de la console peut �tre plus petit. Si l'on ajuste le buffer les  
 informations CONSOLE_SCREEN_BUFFER_INFO ne sont pas toutes mises � 
 jour ce qui peut poser un probl�me si l'on utilise ensuite la fonction
 G_ConsResize().
 */
_Bool G_PleinEcran()
{
	HANDLE h = G_GetConsOut();

	// sans ces premi�res instructions j'ai toujours un ascenceur
	// en bas (?.. il y a surement mieux � faire)
	COORD max = GetLargestConsoleWindowSize(h);
	if (!SetConsoleScreenBufferSize(h, max))
		return FALSE;

	COORD c;
	//https://docs.microsoft.com/en-us/windows/console/setconsoledisplaymode
	if (!SetConsoleDisplayMode(h, CONSOLE_FULLSCREEN_MODE, &c))
		return FALSE;
	
	// Le plein �cran donne un peu plus de place que le mode fen�tre
	max = GetLargestConsoleWindowSize(h);
	if (!SetConsoleScreenBufferSize(h, max))
		return FALSE;

	return TRUE;
}
/*****************************************************************************
Fen�tre la plus grange possible, alternative au plein �cran
*/
_Bool G_ConsResizeMax()
{
	HANDLE h = G_GetConsOut();

	DWORD mode = 0;
	GetConsoleDisplayMode(&mode);
	if (mode == CONSOLE_FULLSCREEN) {
		COORD c;
		if (!SetConsoleDisplayMode(h, CONSOLE_WINDOWED_MODE, &c))
			return FALSE;
	}
	COORD max = GetLargestConsoleWindowSize(h);
	if (!SetConsoleScreenBufferSize(h, max))
		return FALSE;

	// si le mode �tait plein �cran les infos relatives � taille de fen�tre ne correspondent 
	// pas aux dimensions de l'�cran et un appel : 
	// G_ConsResize(max.X,max.Y); 
	// ne donne pas forc�ment une fen�tre de la bonne taille. Le plus simple pour rem�dier �
	// cela est de dimensionner ici la fen�tre sur la taille maximum obtenue pr�c�dement
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;
	info.srWindow.Top = 0;
	info.srWindow.Left = 0;
	info.srWindow.Bottom = max.Y - 1;
	info.srWindow.Right = max.X - 1;

	if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
		return FALSE;

	// d�placer la fen�tre dans le coin haut-gauche
	G_ConsPosition(0, 0);
		
	return TRUE;
}
/**********************************************
Positionner la fen�tre.
Positionne la fen�tre � des coordonn�es pixels dans l'�cran.
*/
void G_ConsPosition(int x, int y)
{
	// remarque : le fullscreen est en fait une fen�tre sans
	// barre de controle et qui couvre tout l'�cran. Il
	// est donc possible de la d�placer mais nous pr�f�rons �viter.
	// (Cependant on pourrait peut-�tre envisager une console
	// sans barre de controle et d'une dimension choisie positionn�e
	// n'importe ou dans l'�cran)
	DWORD mode = 0;
	GetConsoleDisplayMode(&mode);
	if (mode != CONSOLE_FULLSCREEN) {
		HWND consoleWindow = GetConsoleWindow();
		RECT r;

		//r�cup�re les dimensions en pixel de la fen�tre 
		GetWindowRect(consoleWindow, &r);

		//https://docs.microsoft.com/en-us/windows/desktop/api/winuser/nf-winuser-setwindowpos
		SetWindowPos(consoleWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
}
/**********************************************
Centrer la console dans l'�cran
*/
void G_ConsCenter()
{
	DWORD mode = 0;
	GetConsoleDisplayMode(&mode);
	if (mode != CONSOLE_FULLSCREEN) {
		//obtenir un handle sur la fen�tre console
		HWND consoleWindow;
		consoleWindow = GetConsoleWindow(); //GetForegroundWindow();

		// obtenir un handle pour l'�cran et le rectangle correspondant
		HWND   hwndScreen;
		RECT   rectScreen;
		hwndScreen = GetDesktopWindow();
		GetWindowRect(hwndScreen, &rectScreen); // donne le rectangle de la fen�tre et sa position

		/* // autre solution pour obtenir la taille de l'�cran
		MONITORINFO target;
		target.cbSize = sizeof(MONITORINFO);
		HMONITOR hMon = MonitorFromWindow(GetDesktopWindow(), MONITOR_DEFAULTTOPRIMARY);
		GetMonitorInfo(hMon, &target);
		*/

		// pour simplifier le calcul positionner la fen�tre console dans le coin haut gauche  
		// sans modifier sa taille (la fen�tre est invisible )
		SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_HIDEWINDOW | SWP_NOSIZE | SWP_NOZORDER);

		// obtenir la taille de la fen�tre console ( width and height )
		RECT rectConsole;
		GetWindowRect(consoleWindow, &rectConsole);
		int Width = rectConsole.left = rectConsole.right;
		int Height = rectConsole.bottom - rectConsole.top;

		//centrer et voir la fen�tre console 	
		int ConsolePosX;
		int ConsolePosY;
		ConsolePosX = ((rectScreen.right - rectScreen.left) / 2 - Width / 2);
		ConsolePosY = ((rectScreen.bottom - rectScreen.top) / 2 - Height / 2);
		SetWindowPos(consoleWindow, NULL, ConsolePosX, ConsolePosY, 0, 0, SWP_SHOWWINDOW | SWP_NOZORDER | SWP_NOSIZE);
	}
}

/**********************************************
	G_ConsResize fonction
	redimensionne la fen�tre console, partie visible et
	partie m�moire sont ajust�es.
*/
_Bool G_ConsResize(int width, int height)
{
	HANDLE h = G_GetConsOut();

	// si plein �cran, passer en mode fen�tr�
	DWORD mode = 0;
	GetConsoleDisplayMode(&mode);
	if (mode == CONSOLE_FULLSCREEN) {
		COORD c;
		if (!SetConsoleDisplayMode(h, CONSOLE_WINDOWED_MODE, &c))
			return FALSE;
		G_ConsResizeMax();
	}

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	// r�cup�ration des tailles maximum et minimum support�es par la
	// console selon la police active. La fonction G_ConsMinSize()
	// retourne 17x2 avec une police par default. C'est petit.
	// Au-dessous le fonctionnement n'est pas assur�.
	// Eventuellement on peut prendre 20x5, c'est pas mal.
	COORD max = GetLargestConsoleWindowSize(h);
	COORD min = {20,5}; // G_ConsMinSize(h);//
	width = (width > max.X) ? max.X :
		((width < min.X) ? min.X : width);
	height = (height > max.Y) ? max.Y :
		((height < min.Y) ? min.Y : height);

	// si la hauteur  demand�e est inf�rieure � la
	// hauteur actuelle
	if (height < info.dwSize.Y) {

		// diminuer d'abord le rect fen�tre
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		// ensuite le buffer correspondant
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	// si la taille demand�e est sup�rieure �
	// la taille actuelle
	else if (height > info.dwSize.Y) {
		// d'abord augmenter la taille du buffer
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		// ensuite le rectangle correspondant de la fen�tre
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;
	}
	// idem pour la largeur
	if (width < info.dwSize.X) {
		info.srWindow.Right = width - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	else if (width > info.dwSize.X) {
		info.dwSize.X = width;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		info.srWindow.Right = width - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;
	}
	return TRUE;
}
/**********************************************
G_ConsMinSize fonction
R�cup�re une taille minimum pour la fen�tre console.
Le principe n'est pas absolument juste car la mesure
minimum de la fen�tre est donn�es en pixels alors que
celle des lettres ne l'est pas. Cependant le r�sultat
obtenu est acceptable.
*/
/*
COORD G_ConsMinSize(HANDLE h)
{
	// taille min de la fenetre en pixel
	COORD wsize;
	wsize.X = GetSystemMetrics(SM_CXMIN);
	wsize.Y = GetSystemMetrics(SM_CYMIN);

	// taille des caract�res en pixel
	CONSOLE_FONT_INFO font;
	COORD fsize;
	GetCurrentConsoleFont(h, TRUE, &font);
	fsize = GetConsoleFontSize(h, font.nFont);

	// nombre de caract�res minimum
	COORD min = { wsize.X / fsize.X , wsize.Y / fsize.Y };
	return min;
}
*/
/***************************************
Obtenir les largeur et hauteur de la console
*/
int G_ConsTX()
{
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	if (!GetConsoleScreenBufferInfo(G_GetConsOut(), &info))
		return FALSE;

	return info.dwSize.X;
}
int G_ConsTY()
{
	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	if (!GetConsoleScreenBufferInfo(G_GetConsOut(), &info))
		return FALSE;

	return info.dwSize.Y;
}
/**********************************************
Fonction pour remplir la fenetre console avec une couleur
et une lettre. La couleur couvre � la fois le fond (back :
4 bits de gauche) et la lettre (le for : les quatre bits
de droite)
*/
_Bool G_ConsClearTo(int bcolor, int fcolor, char lettre)
{
	_Bool cursetat = G_ConsCursorEtat();

	CONSOLE_SCREEN_BUFFER_INFO info = {0};
	if (!GetConsoleScreenBufferInfo(G_GetConsOut(), &info))
		return FALSE;

	int nb = info.dwSize.X * info.dwSize.Y;
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*nb);
	if (dat != NULL) {
		for (int i = 0; i < nb; i++) {
			dat[i].Attributes = (bcolor << 4) + fcolor;
			dat[i].Char.AsciiChar = lettre;
		}

		SMALL_RECT src = { 0 };
		src.Right = info.srWindow.Right + 1;
		src.Bottom = info.srWindow.Bottom + 1;

		SMALL_RECT dest = src;
		G_Blit(dat, &src, &dest);
		free(dat);
	}
	else
		return FALSE;

	// le curseur en �criture est plac� en haut gauche
	G_Gotoxy(0, 0);
	G_ConsCursor(cursetat);

	return TRUE;
}
/**********************************************
Effacer la console avec des espaces noirs
*/
_Bool G_ConsClear()
{
	return G_ConsClearTo(BLACK, BLACK, ' ');
}
/************************************************************
COULEUR
*************************************************************/
void G_TextColor(int color)
{
	SetConsoleTextAttribute(G_GetConsOut(), color);
}

/************************************************************
AFFICHAGES DANS LA CONSOLE
************************************************************/
/*
D�placer le curseur en �criture dans la fen�tre console
*/
_Bool G_Gotoxy(int x, int y)
{
	COORD c = { x,y };

	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	if (!GetConsoleScreenBufferInfo(G_GetConsOut(), &info))
		return FALSE;

	// controler que le curseur ne sort pas de la fen�tre
	if (c.X >= info.srWindow.Left && c.X <= info.srWindow.Right &&
		c.Y >= info.srWindow.Top && c.Y <= info.srWindow.Bottom)
		SetConsoleCursorPosition(G_GetConsOut(), c);

	return TRUE;
}
/**********************************************
	Afficher directement dans la console un block dat de
	CHAR_INFO depuis le rectangle source pris dans dat et �
	destination du rectangle dest visible dans la console.
	Les champs right et bottom correspondent respectivement
	� la taille de la largeur et de la hauteur.

	Le param�tre constdest d�termine le rectangle d'affichage dans la
	console. C'est un param�te en entr�e et en sortie. En sortie il
	retourne le rectangle effectivement affich� dans la console.
	La fonction WriteConsoleOutPut() controle donc les possibles
	d�bordements du buffer de la console : �crire en dehors ne
	produit pas d'erreur.

	Documentation de la fonction WriteConsoleOutPut():
	https://docs.microsoft.com/en-us/windows/console/writeconsoleoutput
*/
_Bool G_Blit(CHAR_INFO*dat, SMALL_RECT*datsrc, SMALL_RECT*consdest)
{
	COORD taille = { datsrc->Right,datsrc->Bottom };
	COORD pos = { datsrc->Left, datsrc->Top };

	if (!WriteConsoleOutput(G_GetConsOut(), dat, taille, pos, consdest))
		return FALSE;
	return TRUE;
}
/**********************************************
	D�riv�e de la fonction pr�c�dente pour afficher
	le caract�re 'lettre' dans la console � la position
	x, y avec bcolor en fond et fcolor en lettre.
	Plus rapide queG_Gotoxy()
*/
void G_DrawChar(int x, int y, int lettre, int bcolor, int fcolor)
{
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO));
	if (dat != NULL) {
		// attention : multiplier par 16 pour
		// passer � couleur de fond (ou << 4 �quivalent)
		dat->Attributes = (((WORD)bcolor) << 4) + ((WORD)fcolor);
		dat->Char.AsciiChar = lettre;

		// casts pour small rect ensuite
		SHORT left = 0, top = 0, right = 1, bottom = 1;
		SMALL_RECT src = { left,top,right,bottom };

		left = x, top = y, right = x + 1, bottom = y + 1;
		SMALL_RECT dest = { left,top,right,bottom };
		G_Blit(dat, &src, &dest);
		free(dat);
	}
}

/************************************************************
TRACES GEOMETRIQUES
*************************************************************
Tracer une ligne horizontale depuis la position (x1,y) jusque
(x2, y) avec la lette lettre et de couleurs bcolor pour le fond,
fcolor pour la lettre. La position d'arriv�e ne fait pas partie
du segment.
*/
void G_LigneH(int x1, int y, int x2, int lettre, int bcolor, int fcolor)
{
	// si x1 apr�s x2 inverser
	if (x1 > x2) {
		x1 ^= x2;
		x2 ^= x1;
		x1 ^= x2;
	}
	int tx = x2 - x1;
	if (tx == 0)
		return;
	else if (tx == 1)
		G_DrawChar(x1, y, lettre, bcolor, fcolor);
	else {
		CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*tx);
		if (dat != NULL) {
			// attention : multiplier par 16 pour
			// passer � couleur de fond (ou << 4 �quivalent)
			for (int i = 0; i < tx; i++) {
				dat[i].Attributes = (((WORD)bcolor) << 4) + ((WORD)fcolor);
				dat[i].Char.AsciiChar = lettre;
			}

			// casts pour small rect ensuite
			SHORT left = 0, top = 0, right = tx, bottom = 1;
			SMALL_RECT src = { left,top,right,bottom };

			left = x1, top = y, right = x2, bottom = y + 1;
			SMALL_RECT dest = { left,top,right,bottom };
			G_Blit(dat, &src, &dest);
			free(dat);
		}
	}
}
/**********************************************
Tracer une ligne verticale depuis la position (x,y1)
jusque (x, y2) avec la lette lettre et de couleurs
bcolor pour le fond, fcolor pour la lettre. La position
d'arriv�e ne fait pas partie du segment.
*/
void G_LigneV(int x, int y1, int y2, int lettre, int bcolor, int fcolor)
{
	// si y1 apr�s y2 inverser
	if (y1 > y2) {
		y1 ^= y2;
		y2 ^= y1;
		y1 ^= y2;
	}
	int ty = y2 - y1;

	if (ty == 0)
		return;
	else if (ty == 1)
		G_DrawChar(x, y1, lettre, bcolor, fcolor);
	else {
		CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*ty);
		if (dat != NULL) {
			// attention : multiplier par 16 pour
			// passer � couleur de fond (ou << 4 �quivalent)
			for (int i = 0; i < ty; i++) {
				dat[i].Attributes = (((WORD)bcolor) << 4) + ((WORD)fcolor);
				dat[i].Char.AsciiChar = lettre;
			}

			// casts en SHORT pour small rect ensuite
			SHORT left = 0, top = 0, right = 1, bottom = ty;
			SMALL_RECT src = { left,top,right,bottom };

			left = x, top = y1, right = x + 1, bottom = y2;
			SMALL_RECT dest = { left,top,right,bottom };
			G_Blit(dat, &src, &dest);
			free(dat);
		}
	}
}
/**********************************************
Tracer le contour d'un rectangle compris entre les
coordonn�es (x1,y1) et (x2, y2) de la lettre lettre
et des couleurs bcolor pour le fond, fcolor pour la
lettre. x1 corespond � left, y1 � top, x2 � right,
y2 � bottom. Right et botom ne constiuent les lmites
hors trac�.
*/
void G_Rect(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor)
{
	if (x1 > x2) {
		x1 ^= x2;
		x2 ^= x1;
		x1 ^= x2;
	}
	if (y1 > y2)
	{
		y1 ^= y2;
		y2 ^= y1;
		y1 ^= y2;
	}
	if (x2 - x1 == 0 && y2 - y1 == 0)
		return;
	else if (x2 - x1 == 1 && y2 - x1 == 1) {
		G_DrawChar(x1, x2, lettre, bcolor, fcolor);
	}
	else {
		G_LigneH(x1, y1, x2, lettre, bcolor, fcolor);
		G_LigneV(x2 - 1, y1, y2, lettre, bcolor, fcolor);
		G_LigneH(x1, y2 - 1, x2, lettre, bcolor, fcolor);
		G_LigneV(x1, y1, y2, lettre, bcolor, fcolor);
	}
}
/**********************************************
Tracer le contour d'un rectangle compris entre les
coordonn�es (x1,y1) et (x2, y2) de la lettre lettre
et des couleurs bcolor pour le fond. A la diff�rence
de la fonction G_Rect() chaque c�t� peut prendre
une couleur sp�cifique pour la lettre et le fond.
Ces couleurs sont pass�es avec deux tableaux. bcolors
pour les 4 couleurs de fond et fcolors pour les 4
couleurs de lettre.
En 0 couleurs ligne horizontale en haut
En 1 couleurs ligne horizontale du bas
en 2 couleurs ligne verticale de gauche
en 3 couleurs ligne verticale de droite
*/
void G_RectColors(int x1, int y1, int x2, int y2, int lettre, int bcolors[4], int fcolors[4])
{
	if (x1 > x2) {
		x2 ^= x1;
		x1 ^= x2;
	}
	if (y1 > y2)
	{
		y1 ^= y2;
		y2 ^= y1;
		y1 ^= y2;
	}
	if (x2 - x1 == 0 && y2 - y1 == 0)
		return;
	else if (x2 - x1 == 1 && y2 - x1 == 1) {
		G_DrawChar(x1, x2, lettre, bcolors[0], fcolors[0]);
	}
	else {
		G_LigneH(x1, y1, x2, lettre, bcolors[0], fcolors[0]);
		G_LigneH(x1, y2 - 1, x2, lettre, bcolors[1], fcolors[1]);
		G_LigneV(x1, y1, y2, lettre, bcolors[2], fcolors[2]);
		G_LigneV(x2 - 1, y1, y2, lettre, bcolors[3], fcolors[3]);
	}
}
/**********************************************
Tracer un rectangle plein compris entre les coordonn�es
(x1,y1) et (x2, y2) de la lettre lettre et des couleurs
bcolor pour le fond, fcolor pour la lettre.
*/
void G_FillRect(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor)
{
	if (x1 > x2) {
		x1 ^= x2;
		x2 ^= x1;
		x1 ^= x2;
	}
	if (y1 > y2)
	{
		y1 ^= y2;
		y2 ^= y1;
		y1 ^= y2;
	}
	int tx = x2 - x1;
	int ty = y2 - y1;

	if (tx == 0 && ty == 0)
		return;
	else if (tx == 1 && ty == 1) {
		G_DrawChar(x1, x2, lettre, bcolor, fcolor);
	}
	else {
		CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO)*ty*tx);
		if (dat != NULL) {
			for (int i = 0; i < ty * tx; i++) {
				dat[i].Attributes = (((WORD)bcolor) << 4) + ((WORD)fcolor);
				dat[i].Char.AsciiChar = lettre;
			}

			SHORT left = 0, top = 0, right = tx, bottom = ty;
			SMALL_RECT src = { left,top,right,bottom };

			left = x1, top = y1, right = x2, bottom = y2;
			SMALL_RECT dest = { left,top,right,bottom };
			G_Blit(dat, &src, &dest);
			free(dat);
		}
	}
}
/**********************************************
Tracer des lignes dans n'importe quelles directions
depuis le point x1, y1 jusqu'au point x2,y2 avec la
lettre lettre de de couleurs bcolor pour le fond et
fcolor pour la lettre.
*/
void G_DrawLigne(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor)
{
	int pasx, pasy, absx, absy, i;

	int x = x2 - x1;
	int y = y2 - y1;
	pasx = (x > 0) ? 1 : -1;
	pasy = (y > 0) ? 1 : -1;

	absx = abs(x);
	absy = abs(y);

	G_DrawChar(x1, y1, lettre, bcolor, fcolor);

	if (x == 0) { // ligne verticale
		for (i = 0; i < absy; i++) {
			y1 += pasy;
			G_DrawChar(x1, y1, lettre, bcolor, fcolor);
		}
	}
	else if (y == 0) { // ligne horizontale
		for (i = 0; i < absx; i++) {
			x1 += pasx;
			G_DrawChar(x1, y1, lettre, bcolor, fcolor);
		}
	}
	else if (absx == absy) { // diagonales 45�
		for (i = 0; i < absx; i++) {
			x1 += pasx;
			y1 += pasy;
			G_DrawChar(x1, y1, lettre, bcolor, fcolor);
		}
	}

	// TODO : v�rifier exactitude du point d'arriv�e pour les deux
	// derniers cas

	else if (absx > absy) { // inclin�e en dessous de 45�
		int res = 0;
		// compte tenu du fait que le 0 compte il y a un pas
		// supl�mentaire � la fin qui fausse un peu le r�sultat
		// supprimer un pour absx ne r�gle pas ce probl�me, � v�rifier.
		for (i = 0; i < absx; i++) {
			x1 += pasx;
			res += absy;
			if (res >= absx) {
				res -= absx;
				y1 += pasy;
			}
			G_DrawChar(x1, y1, lettre, bcolor, fcolor);
		}
	}
	else { // inclin�e au dessus de 45�
		int res = 0;
		// Idem r�sultat l�g�rement fauss� � la fin de la droite
		for (i = 0; i < absy; i++) {
			y1 += pasy;
			res += absx;
			if (res >= absy) {
				res -= absy;
				x1 += pasx;
			}
			G_DrawChar(x1, y1, lettre, bcolor, fcolor);
		}
	}
}
// TODO
/**********************************************
en reprenant l'algorithme de G_TraceLigne() stocker
tous les points d'une ligne
*/
/*
COORD* G_StockLigne(int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor)
{
	COORD*tab = NULL;


	return tab;
}
*/
/**********************************************
en reprenant l'algorithme de G_TraceLigne() tracer
une ligne dans une matrice
*/
/*
void G_DrawLigneMat(int(*m)[], int tx, int ty, int x1, int y1, int x2, int y2, int lettre, int bcolor, int fcolor)
{
	;
}
*/
/**********************************************
La fonction G_DrawLigneAngle trace un segment depuis
la position x, y selon l'angle angle et de la distance dist.
La position d'arriv�e et sortie en ax et ay. Le trac� utilise
la lettre ainsi que les couleurs donn�es en param�tre.
*/
void G_DrawLigneAngle(int x, int y, int angle, int dist, int*ax, int*ay, int lettre, int bcolor, int fcolor)
{
	const double pi = 3.1416;
	const double degre = pi * 2 / 360.0;

	double dax = *ax;
	double day = *ay;
	dax = x + dist * cos(angle*degre);
	day = y - dist * sin(angle*degre);

	// arrondir
	*ax = (dax >= (int)dax + 0.5) ? (int)dax + 1 : (int)dax;
	*ay = (day >= (int)day + 0.5) ? (int)day + 1 : (int)day;

	G_DrawLigne(x, y, *ax, *ay, lettre, bcolor, fcolor);
}
/**********************************************
Tracer le contour d'un cercle
Attention visuellement il s'agit plut�t d'oval
parce que nous sommes en mode caract�res et que
les caract�res sont en g�n�ral plus hauts que larges.
*/
void G_DrawCercle(int x, int y, int rayon, int lettre, int bcolor, int fcolor)
{
	int cx, cy, f1, f2, f;

	cx = x;
	cy = y + rayon;
	f = 0;
	while (cy >= y) {
		G_DrawChar(cx, cy, lettre, bcolor, fcolor);
		G_DrawChar(2 * x - cx, cy, lettre, bcolor, fcolor);
		G_DrawChar(2 * x - cx, 2 * y - cy, lettre, bcolor, fcolor);
		G_DrawChar(cx, 2 * y - cy, lettre, bcolor, fcolor);

		f1 = f + 1 + 2 * (cx - x);
		f2 = f + 1 - 2 * (cy - y);

		if (abs(f1) < abs(f2)) {
			cx += 1;
			f = f1;
		}
		else {
			cy -= 1;
			f = f2;
		}
	}
}
//TODO
/**********************************************
tracer un cercle plein
*/
/*
void G_FillCercle(int x, int y, int rayon, int lettre, int bcolor, int fcolor)
{

}
*/
/**********************************************
Stocker les points du contour d'un cercle
*/
/*
COORD* G_StockCercle(int x, int y, int rayon, int lettre, int bcolor, int fcolor)
{
	COORD*tab = NULL;


	return tab;
}
*/
/**********************************************
Tracer un cercle dans une matrice
*/
/*
void G_FillCercleMat(int(*m)[], int tx, int ty, int x, int y, int rayon, int lettre, int bcolor, int fcolor)
{
	;
}
*/
//TODO
/************************************************************
SIMULATION DE BITMAPS
*************************************************************/


/************************************************************
GESTION DES EVENEMENTS
*************************************************************
Doc : https://docs.microsoft.com/en-us/windows/console/input-record-str

La fonction principale de r�cup�ration des �v�nements.
Ici nous r�cup�rons les �v�nements un par un.
*/
static INPUT_RECORD EventRec;

int G_PollEvent()
{
	DWORD num = 0;  // unsigned int
	DWORD mode = 0;

	// r�initialiser le buffer d'entr�e
	memset(&EventRec, 0, sizeof(INPUT_RECORD));

	if (!G_SelectEventMode())
		return 0;

	// pour ne pas bloquer r�cup�rer un �v�nement suniquemenent s'il y en a
	GetNumberOfConsoleInputEvents(G_GetConsIn(), &num);
	if (num)
		// ReadConsoleInput retourne 0 en cas d'erreur
		// Doc : https://docs.microsoft.com/en-us/windows/console/readconsoleinput
		num = ReadConsoleInput(G_GetConsIn(), &EventRec, 1, &num);

	return num;
}
/**********************************
Fonction inverse de la pr�c�dente il s'agit de vider
le buffer d'entr�e des �v�nements en attente.

*/
_Bool G_FlushEvent()
{
	if (!G_SelectEventMode())
		return FALSE;
	
	// vider le buffer des �v�nements
	DWORD readevent = 0, num = 0;
	GetNumberOfConsoleInputEvents(G_GetConsIn(), &num);
	if (num) {
		INPUT_RECORD*ev = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD)*num);
		if (ev != NULL) {
			ReadConsoleInput(G_GetConsIn(), ev, num, &readevent);
			free(ev);
		}
	}
	// r�initialiser l'entr�e EventRec
	memset(&EventRec, 0, sizeof(INPUT_RECORD));

	// si le nombre lu ne correspond pas au nombre de la file, erreur
	if (readevent != num)
		return FALSE;

	return TRUE;
}

_Bool G_KeyPressed()
{
	return EventRec.EventType == KEY_EVENT && EventRec.Event.KeyEvent.bKeyDown;

}
_Bool G_KeyPressDown()
{
	return EventRec.EventType == KEY_EVENT && EventRec.Event.KeyEvent.bKeyDown;
}

_Bool G_KeyPressUp()
{
	return EventRec.EventType == KEY_EVENT && !EventRec.Event.KeyEvent.bKeyDown;
}
/*	La G_KeyDown() permet de savoir si une touche du clavier est appuy�e ou pas
	en utilisant le codeage virtual-key fourni par microsoft. Chaque touche est
	identifi�e par une constante dont le nom commence par VK_ , par exemple
	VK_RETURN pour enter, VK_ESCAPE pour escape etc.
	Notons que les clics de la souris peuvent aussi �tre identifi�s par ces codes :
	VK_LBUTTON pour clic gauche, VK_RBUTTON pour clic droit, VK_MBUTTON pour celui
	du milieu.
	Consulter la documentation :
	https://docs.microsoft.com/fr-fr/windows/desktop/inputdev/virtual-key-codes
	*/
_Bool G_KeyDown(int vk_touche)
{
	return EventRec.Event.KeyEvent.bKeyDown && EventRec.Event.KeyEvent.wVirtualKeyCode == vk_touche;
}
_Bool G_KeyUp(int vk_touche)
{
	return !EventRec.Event.KeyEvent.bKeyDown && EventRec.Event.KeyEvent.wVirtualKeyCode == vk_touche;
}
char G_KeyAscii()
{
	return EventRec.Event.KeyEvent.uChar.AsciiChar;
}
WORD G_KeyVK()
{
	return EventRec.Event.KeyEvent.wVirtualKeyCode;
}

_Bool G_MouseEvent()
{
	return	EventRec.EventType == MOUSE_EVENT;
}
_Bool G_MouseEventClic()
{
	return EventRec.Event.MouseEvent.dwButtonState != 0;
}
/* les valeurs des boutons pour la console :

The leftmost mouse button.
FROM_LEFT_1ST_BUTTON_PRESSED 0x0001		: Gauche

The second button from the left.
FROM_LEFT_2ND_BUTTON_PRESSED 0x0004		: milieu (souris ordinaire)

The third button from the left.
FROM_LEFT_3RD_BUTTON_PRESSED 0x0008

The fourth button from the left.
FROM_LEFT_4TH_BUTTON_PRESSED 0x0010

The rightmost mouse button.
RIGHTMOST_BUTTON_PRESSED 0x0002			: droite

Documentation :
https://docs.microsoft.com/en-us/windows/console/mouse-event-record-str
*/
_Bool G_MouseClic(int button)
{
	return	EventRec.EventType == MOUSE_EVENT &&
		EventRec.Event.MouseEvent.dwButtonState & button;
}
_Bool G_MouseEventWeel() // roulette verticale
{
	return	EventRec.EventType == MOUSE_EVENT &&
		EventRec.Event.MouseEvent.dwEventFlags == MOUSE_WHEELED;
}
_Bool G_MouseEventMove()
{
	return	EventRec.EventType == MOUSE_EVENT &&
		EventRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED;
}
int G_MouseX()
{
	return EventRec.Event.MouseEvent.dwMousePosition.X;
}
int G_MouseY()
{
	return EventRec.Event.MouseEvent.dwMousePosition.Y;
}


