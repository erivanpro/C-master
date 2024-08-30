#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// les données communes aux quatre types
#define TRONC_COMMUN	int type; \
						int x;\
						int y;\
						int dx;\
						int dy;

typedef struct TroncCommun {
	TRONC_COMMUN
}TroncCommun;

// les quatre types
typedef struct Dragon {
	TRONC_COMMUN
	int flamme;
	char cuirasse;
}Dragon;
typedef struct Troll {
	TRONC_COMMUN
	int muscle;
	float masse;
}Troll;
typedef struct Nain {
	TRONC_COMMUN
	int hache;
	long barbe;
}Nain;
typedef struct Orc{
	TRONC_COMMUN
	int poignard;
	double griffes;
}Orc;

// un union récapitule les quatre types
typedef union {
	int type;
	TroncCommun commun;
	Dragon dragon;
	Troll troll;
	Nain nain;
	Orc orc;
}Ennemi;

// quatre types identifiés par des constantes
enum { DRAGON=1, TROLL, NAIN, ORC };

int main()
{
	Dragon dragon = { DRAGON,11,12,13,14,15,16 };
	Troll troll = { TROLL,21,22,23,24,25,26 };
	Nain nain = { NAIN,31,32,33,34,35,36 };
	Orc orc = { ORC,41,42,43,44,45,46 };

	// un ennemi peut indiféremment être l'un des quatre
	// types prévus
	Ennemi ennemi;
	switch (rand() % 4) {
		// dragon ?
		case 0: ennemi.dragon = dragon;	break;// Dragon ?
		case 1: ennemi.troll = troll;	break;// Troll ?
		case 2: ennemi.nain = nain;		break;// Nain ?
		case 3: ennemi.orc = orc;		break;// Orc ?
	}
	// nous reconnaissons le type grace au champ type
	// commun à tous les ennemis et nous pouvons agir
	// selon le type :
	switch (ennemi.type) {
		case 1: printf("Dragon\n"); break;
		case 2: printf("Troll\n"); break;
		case 3: printf("Nain\n"); break;
		case 4: printf("Orc\n"); break;
	}
	
	// De plus quelque soit le type de l'ennemi nous pouvons accéder 
	// à ses données de position et de déplacement en passant par le 
	// champ des variables communes, par exemple :
	Ennemi e1, e2; 
	e1.dragon = dragon;
	e2.troll = troll;
		
	printf("Dragon en passant par commun : \n");
	printf("   type     : %d,%d \n", e1.type, e1.commun.type);
	printf("   x, y     : %d,%d \n", e1.commun.x, e1.commun.y);
	printf("   dx,dy    : %d,%d \n", e1.commun.dx, e1.commun.dy);
	
	printf("Dragon en passant par dragon: \n");
	printf("   type     : %d\n", e1.dragon.type);
	printf("   x, y     : %d,%d \n", e1.dragon.x, e1.dragon.y);
	printf("   dx,dy    : %d,%d \n", e1.dragon.dx, e1.dragon.dy);
	printf("   flamme   : %d\n", e1.dragon.flamme);
	printf("   cuirasse : %d\n", e1.dragon.cuirasse);

	printf("Troll en passant par commun : \n");
	printf("   type   : %d,%d \n", e2.type, e2.commun.type);
	printf("   x, y   : %d,%d \n", e2.commun.x, e2.commun.y);
	printf("   dx,dy  : %d,%d \n", e2.commun.dx, e2.commun.dy);
	
	printf("Troll en passant par troll : \n");
	printf("   type   : %d\n", e2.troll.type);
	printf("   x, y   : %d,%d \n", e2.troll.x, e2.troll.y);
	printf("   dx,dy  : %d,%d \n", e2.troll.dx, e2.troll.dy);
	printf("   masse  : %d\n", e2.troll.masse);
	printf("   muscle : %d\n", e2.troll.muscle);
	
	return 0;
}