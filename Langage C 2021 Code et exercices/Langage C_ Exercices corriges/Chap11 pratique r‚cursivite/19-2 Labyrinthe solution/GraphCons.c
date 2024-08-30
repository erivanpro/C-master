#include "GraphCons.h"


/*
Baptisée de GraphCons pour graphique console cette simplee librairie
permet des créations de jeux. Elle se compose des fichiers GraphCons.c
et GraphCons.h. Ces fichier doivent être intégrés au projet et compilés
avec lui.

GraphCons s'appuie sur l'API Win32 et l'ensemble des bibliothèques
fournies avec Windows.h. Notamment elle comprend tout ce qui concerne la
console (kernel32.lib et kernel32.dll). La documentation pour l'utilisation
de la console se trouve ici :
https://docs.microsoft.com/en-us/windows/console/console-reference

Malheureusement depuis la mise à jour 1809 de windows 10 certaines fonctions
ne marchent plus, par exemple le plein écran qui a été plus compliqué à obtenir
et la souris ne fonctionne plus. J'ai signalé ce problème à Microsoftet à ce jour
je ne sais pas encore si c'est intentionnel et nécessite une documentation à venir
ou s'il s'agit d'un bug. Sur cette question vous pouvez consulter :
https://github.com/MicrosoftDocs/Console-Docs/issues/85

J'espère pouvoir pousser plus loin le développement de GraphCons, notamment en
introduisant le principe de pseudo images bitmap. Il faudrait également gérer la
taille des polices utilisées par la console ce qui permettrait d'élargir
considérablement la résolution de la console.

Personnellement j'aime bien l'univers console qui rappelle les premières
heures de l'informatique et s'intègre parfaitement dans l'ascii art.

Si vous trouvez mieux n'hésitez pas à me faire connaitre vos solutions,
merci pour toutes ces éventuelles corrections et améliorations !
fdr@free.fr

*/


/************************************************************
GENERAL
*************************************************************
	Handle sur la console en sortie, indispensable pour toutes
	les opérations d'affichage dans la console et de
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
	Handle sur le console en entrée, indispensable pour la
	maitrise des événements, clavier, souris etc.
*/
HANDLE G_GetConsIn()
{
	static HANDLE h = NULL;

	if (h == NULL) {

		h = GetStdHandle(STD_INPUT_HANDLE);
		if (h == INVALID_HANDLE_VALUE)
			exit(EXIT_FAILURE);
	}
	return h;
}
/**********************************************
supprime le curseur en écriture si false, l'affiche si true
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
	Permet de stoper le déroulement du programme
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
chronométrage des espace de temps pour controler la
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
DIMENSIONS CONSOLE (RESOLUTION)
*************************************************************/
_Bool G_PleinEcran()
{
	/*
	// Solution 1 : agrandit et déplace la fenêtre qui couvre l'écran en
	// conservant la barre de controle en haut de la fenêtre. La taille
	// du buffer associé à la console s'adapte. C'est équivalent à un clic
	// sur "Agrandir dans la zone de controle de la barre de fenêtre.
	// l'inconvénient c'est que cette barre reste visible et que la console
	// reste collée aux bords haut et gauche même  an cas de redimensionnement
	// ensuite
	HWND hwnd = GetForegroundWindow();
	return ShowWindow(hwnd, SW_MAXIMIZE);
	*/

	/*
	 Solution 2 : La fenêtre masque tout l'écran et fait disparaitre la
	 barre de contrôle du haut de l'écran, nécessite alors de prévoir un
	 moyen de quitter l'application sans la croix rouge en haut et à
	 droite de la fenêtre.

	 Le dernier paramètre PCOORD  (COORD*) de la fonction :
	BOOL WINAPI SetConsoleDisplayMode(HANDLE hConsoleOutput,DWORD  dwFlags,
									  PCOORD lpNewScreenBufferDimensions);
	 est de type COORD* et permet éventuellement de récupérer en sortie
	 la nouvelle taille de fenêtre en nombres caratères ici il n'est pas
	 utilisé (NULL). La paramètre DWORD peut prendre deux valeurs :
	 CONSOLE_FULLSCREEN_MODE pour un plein écran total
	 CONSOLE_WINDOWED_MODE pour le mode fenêtré.

	 Malheureusement cette solution semble dépendre de paramètrages occultes
	 liés aux différentes versions de windows 10 et en labsence de documentation,
	 difficile à utiliser.
	*/
    /*
	if (!SetConsoleDisplayMode(G_GetConsOut(), CONSOLE_FULLSCREEN_MODE, NULL))
		return FALSE;
    */
	/* Solution 3 :
	Eventuellement il y a encore une autre solution : simuler la combinaison de
	touches qui permet le passage en plein écran et sa sortie. Cette solution
	n'agit pas sur la taille du buffer de la console.

	*/


	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

	// remarque : pour revenir à la fenêtre :
	//keybd_event(VK_MENU, 0x38, 0, 0);
	//keybd_event(VK_RETURN, 0x1c, 0, 0);
	//keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	//keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);

	// Adapter le buffer fenêtre
	COORD max = GetLargestConsoleWindowSize(G_GetConsOut());
	if (!SetConsoleScreenBufferSize(G_GetConsOut(), max))
		return FALSE;

	// adapter le rect fenêtre
	SMALL_RECT f = { 0,0,max.X-1,max.Y-1 };
	if (!SetConsoleWindowInfo(G_GetConsOut(), TRUE, &f))
		return FALSE;

	// vider la pile des événements de ces quatre appels clavier
	G_FlushEvent();

	return TRUE;
}
_Bool G_ConsResizeMax()
{
	COORD max = GetLargestConsoleWindowSize(G_GetConsOut());
	return G_ConsResize(max.X, max.Y);
}
/**********************************************
	G_ConsResize fonction
	redimensionne la fenêtre console, partie visible et
	partie mémoire sont ajustées.
*/
_Bool G_ConsResize(int width, int height)
{
	HANDLE h = G_GetConsOut();

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(h, &info))
		return FALSE;

	// récupération des tailles maximum et minimum supportées par la
	// console selon la police active. La fonction G_ConsMinSize()
	// retourne 17x2 avec une police par default. C'est petit.
	// Au-dessous le fonctionnement n'est pas assuré.
	// Eventuellement on peut prendre 20x5, c'est pas mal.
	COORD max = GetLargestConsoleWindowSize(h);
	COORD min = {20,5}; // G_ConsMinSize(h);//
	width = (width > max.X) ? max.X :
		((width < min.X) ? min.X : width);
	height = (height > max.Y) ? max.Y :
		((height < min.Y) ? min.Y : height);

	// si la hauteur  demandée est inférieure à la
	// hauteur actuelle
	if (height < info.dwSize.Y) {

		// diminuer d'abord le rect fenêtre
		info.srWindow.Bottom = height - 1;
		if (!SetConsoleWindowInfo(h, TRUE, &info.srWindow))
			return FALSE;

		// ensuite le buffer correspondant
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;
	}
	// si la taille demandée est supérieure à
	// la taille actuelle
	else if (height > info.dwSize.Y) {
		// d'abord augmenter la taille du buffer
		info.dwSize.Y = height;
		if (!SetConsoleScreenBufferSize(h, info.dwSize))
			return FALSE;

		// ensuite le rectangle correspondant de la fenêtre
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
Récupère une taille minimum pour la fenêtre console.
Le principe n'est pas absolument juste car la mesure
minimum de la fenêtre est données en pixels alors que
celle des lettres ne l'est pas. Cependant le résultat
obtenu est acceptable.
*/
/*
COORD G_ConsMinSize(HANDLE h)
{
	// taille min de la fenetre en pixel
	COORD wsize;
	wsize.X = GetSystemMetrics(SM_CXMIN);
	wsize.Y = GetSystemMetrics(SM_CYMIN);

	// taille des caractères en pixel
	CONSOLE_FONT_INFO font;
	COORD fsize;
	GetCurrentConsoleFont(h, TRUE, &font);
	fsize = GetConsoleFontSize(h, font.nFont);

	// nombre de caractères minimum
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
et une lettre. La couleur couvre à la fois le fond (back :
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

	// le curseur en écriture est placé en haut gauche
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
Déplacer le curseur en écriture dans la fenêtre console
*/
_Bool G_Gotoxy(int x, int y)
{
	COORD c = { x,y };

	CONSOLE_SCREEN_BUFFER_INFO info = { 0 };
	if (!GetConsoleScreenBufferInfo(G_GetConsOut(), &info))
		return FALSE;

	// controler que le curseur ne sort pas de la fenêtre
	if (c.X >= info.srWindow.Left && c.X <= info.srWindow.Right &&
		c.Y >= info.srWindow.Top && c.Y <= info.srWindow.Bottom)
		SetConsoleCursorPosition(G_GetConsOut(), c);

	return TRUE;
}
/**********************************************
	Afficher directement dans la console un block dat de
	CHAR_INFO depuis le rectangle source pris dans dat et à
	destination du rectangle dest visible dans la console.
	Les champs right et bottom correspondent respectivement
	à la taille de la largeur et de la hauteur.

	Le paramètre constdest détermine le rectangle d'affichage dans la
	console. C'est un paramète en entrée et en sortie. En sortie il
	retourne le rectangle effectivement affiché dans la console.
	La fonction WriteConsoleOutPut() controle donc les possibles
	débordements du buffer de la console : écrire en dehors ne
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
	Dérivée de la fonction précédente pour afficher
	le caractère 'lettre' dans la console à la position
	x, y avec bcolor en fond et fcolor en lettre.
	Plus rapide queG_Gotoxy()
*/
void G_DrawChar(int x, int y, int lettre, int bcolor, int fcolor)
{
	CHAR_INFO*dat = (CHAR_INFO*)malloc(sizeof(CHAR_INFO));
	// attention : multiplier par 16 pour
	// passer à couleur de fond (ou << 4 équivalent)
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

/************************************************************
TRACES GEOMETRIQUES
*************************************************************
Tracer une ligne horizontale depuis la position (x1,y) jusque
(x2, y) avec la lette lettre et de couleurs bcolor pour le fond,
fcolor pour la lettre. La position d'arrivée ne fait pas partie
du segment.
*/
void G_LigneH(int x1, int y, int x2, int lettre, int bcolor, int fcolor)
{
	// si x1 après x2 inverser
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
		// attention : multiplier par 16 pour
		// passer à couleur de fond (ou << 4 équivalent)
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
/**********************************************
Tracer une ligne verticale depuis la position (x,y1)
jusque (x, y2) avec la lette lettre et de couleurs
bcolor pour le fond, fcolor pour la lettre. La position
d'arrivée ne fait pas partie du segment.
*/
void G_LigneV(int x, int y1, int y2, int lettre, int bcolor, int fcolor)
{
	// si y1 après y2 inverser
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
		// attention : multiplier par 16 pour
		// passer à couleur de fond (ou << 4 équivalent)
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
/**********************************************
Tracer le contour d'un rectangle compris entre les
coordonnées (x1,y1) et (x2, y2) de la lettre lettre
et des couleurs bcolor pour le fond, fcolor pour la
lettre. x1 corespond à left, y1 à top, x2 à right,
y2 à bottom. Right et botom ne constiuent les lmites
hors tracé.
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
coordonnées (x1,y1) et (x2, y2) de la lettre lettre
et des couleurs bcolor pour le fond. A la différence
de la fonction G_Rect() chaque côté peut prendre
une couleur spécifique pour la lettre et le fond.
Ces couleurs sont passées avec deux tableaux. bcolors
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
Tracer un rectangle plein compris entre les coordonnées
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

		for (int i = 0; i < ty*tx; i++) {
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
	else if (absx == absy) { // diagonales 45°
		for (i = 0; i < absx; i++) {
			x1 += pasx;
			y1 += pasy;
			G_DrawChar(x1, y1, lettre, bcolor, fcolor);
		}
	}

	// TODO : vérifier exactitude du point d'arrivée pour les deux
	// derniers cas

	else if (absx > absy) { // inclinée en dessous de 45°
		int res = 0;
		// compte tenu du fait que le 0 compte il y a un pas
		// suplémentaire à la fin qui fausse un peu le résultat
		// supprimer un pour absx ne règle pas ce problème, à vérifier.
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
	else { // inclinée au dessus de 45°
		int res = 0;
		// Idem résultat légèrement faussé à la fin de la droite
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
La position d'arrivée et sortie en ax et ay. Le tracé utilise
la lettre ainsi que les couleurs données en paramètre.
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
Attention visuellement il s'agit plutôt d'oval
parce que nous sommes en mode caractères et que
les caractères sont en général plus hauts que larges.
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

La fonction principale de récupération des événements.
Ici nous récupérons les événements un par un.
*/
static INPUT_RECORD EventRec;
int G_PollEvent()
{
	DWORD num = 0;  // unsigned int
	// réinitialiser l'entrée
	memset(&EventRec, 0, sizeof(INPUT_RECORD));

	// sauvegarder le mode courant (qui autorise notamment l'utilisation de scanf_s)
	DWORD oldmode, mode;
	if (!GetConsoleMode(G_GetConsIn(), &oldmode))
		return num;

	// donner accès en écriture et à la souris
	// ENABLE_WINDOW_INPUT donne la possibilié de récupérer les événements de
	// redimensionnement de fenêtre. Doc :
	// https://docs.microsoft.com/en-us/windows/console/setconsolemode
	mode = GENERIC_READ | ENABLE_MOUSE_INPUT;
	SetConsoleMode(G_GetConsIn(), mode);

	GetNumberOfConsoleInputEvents(G_GetConsIn(), &num);
	if (num)
		// ReadConsoleInput retourne 0 en cas d'erreur
		// Doc : https://docs.microsoft.com/en-us/windows/console/readconsoleinput
		num = ReadConsoleInput(G_GetConsIn(), &EventRec, 1, &num);

	// reprendre le mode par défaut (pour utilisation éventuelle de scanf...)
	SetConsoleMode(G_GetConsIn(), oldmode);
	return num;
}
/**********************************
Fonction inverse de la précédente il s'agit de vider
le buffer d'entrée des événements en attente.

*/
_Bool G_FlushEvent()
{
	// sauvegarder le mode courant (qui autorise notamment l'utilisation de scanf_s)
	DWORD oldmode, mode;
	if (!GetConsoleMode(G_GetConsIn(), &oldmode))
		return FALSE;

	// donner accès en écriture et à la souris
	// ENABLE_WINDOW_INPUT donne la possibilié de récupérer les événements de
	// redimensionnement de fenêtre. Doc :
	// https://docs.microsoft.com/en-us/windows/console/setconsolemode
	mode = GENERIC_READ | ENABLE_MOUSE_INPUT;
	SetConsoleMode(G_GetConsIn(), mode);

	// vider le buffer des événements
	DWORD readevent = 0, num = 0;
	GetNumberOfConsoleInputEvents(G_GetConsIn(), &num);
	if (num) {
		INPUT_RECORD*ev = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD)*num);
		ReadConsoleInput(G_GetConsIn(), ev, num, &readevent);
		free(ev);
	}
	// réinitialiser l'entrée EventRec
	memset(&EventRec, 0, sizeof(INPUT_RECORD));

	// reprendre le mode par défaut (pour utilisation éventuelle de scanf...)
	SetConsoleMode(G_GetConsIn(), oldmode);

	// si le nombre lu ne correspond aux nombres dans la file erreur
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
/*	La G_KeyDown() permet de savoir si une touche du clavier est appuyée ou pas
	en utilisant le codeage virtual-key fourni par microsoft. Chaque touche est
	identifiée par une constante dont le nom commence par VK_ , par exemple
	VK_RETURN pour enter, VK_ESCAPE pour escape etc.
	Notons que les clics de la souris peuvent aussi être identifiés par ces codes :
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


