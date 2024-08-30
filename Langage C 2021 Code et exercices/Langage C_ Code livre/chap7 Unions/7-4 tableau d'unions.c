#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRONC_COMMUN	int type;\
						int x;\
						int y;\
						int dx;\
						int dy;

typedef struct TroncCommun {
	TRONC_COMMUN
}TroncCommun;

enum{DRAGON = 1, TROLL,NAIN,ORC };

typedef struct Dragon {
	TRONC_COMMUN
	int flamme;
	char cuirasse;
}Dragon;
Dragon CreateDragon()
{
	Dragon d;
	d.type = DRAGON;
	d.x = rand() % 100;
	d.y = rand() % 100;
	d.dx = rand() % 100;
	d.dy = rand() % 100;
	d.flamme = rand() % 1000;
	d.cuirasse = rand() % 1000;
	return d;
}

typedef struct Troll {
	TRONC_COMMUN
	int muscle;
	float masse;
}Troll;
Troll CreateTroll()
{
	Troll t;
	t.type = TROLL;
	t.x = rand() % 100;
	t.y = rand() % 100;
	t.dx = rand() % 100;
	t.dy = rand() % 100;
	t.masse = rand() % 1000;
	t.muscle = rand() % 1000;
	return t;
}

typedef struct Nain {
	TRONC_COMMUN
	int hache;
	long barbe;
}Nain;
Nain CreateNain()
{
	Nain n;
	n.type = NAIN;
	n.x = rand() % 100;
	n.y = rand() % 100;
	n.dx = rand() % 100;
	n.dy = rand() % 100;
	n.hache = rand() % 1000;
	n.barbe = rand() % 1000;
	return n;
}

typedef struct Orc {
	TRONC_COMMUN
	int poignard;
	double griffes;
}Orc;
Orc CreateOrc()
{
	Orc o;
	o.type = ORC;
	o.x = rand() % 100;
	o.y = rand() % 100;
	o.dx = rand() % 100;
	o.dy = rand() % 100;
	o.griffes = rand() % 1000;
	o.poignard = rand() % 1000;
	return o;
}

// gestion simultanée des types différents dans un même tableau
typedef union {
	int type;
	TroncCommun commun;
	Dragon dragon;
	Troll troll;
	Nain nain;
	Orc orc;
}Ennemi;
void InitEnnemis(Ennemi e[], int nb)
{
	int i;
	for (i = 0; i < 10; i++) {
		switch (rand() % 4) {
		case 0: e[i].dragon = CreateDragon();	break;
		case 1: e[i].troll = CreateTroll();		break;
		case 2: e[i].nain = CreateNain();		break;
		case 3: e[i].orc = CreateOrc();			break;
		}
	}
}
void AfficheEnnemis(Ennemi e[], int nb)
{
	int i;
	char s[256];
	for (i = 0; i < nb; i++) {
		switch (e[i].type) {
		case DRAGON: 
			sprintf_s(s,256, "Dragon\nflammes : %d\ncuirasse : %d\n",
					        e[i].dragon.flamme, e[i].dragon.cuirasse);
			break;
		case TROLL: 
			sprintf_s(s,256, "Troll\nmasse : %.2f\nmuscle : %d\n",
					        e[i].troll.masse, e[i].troll.muscle);
			break;
		case NAIN:
			sprintf_s(s,256, "Nain\nhache : %d\nbarbe : %d\n",
					    e[i].nain.hache, e[i].nain.barbe);
			break;
		case ORC: 
			sprintf_s(s,256, "Orc\ngriffes : %.2lf\npoignard : %d\n",
					        e[i].orc.griffes, e[i].orc.poignard);
			break;
		}
		printf("%s", s);
		printf("Coords : %d,%d,%d,%d\n", e[i].commun.x, e[i].commun.y,
										e[i].commun.dx, e[i].commun.dy);
		printf("--------\n");
	}
}
void AvanceEnnemis(Ennemi e[], int nb)
{
	int i;
	for (i = 0; i < nb; i++)
	{
		e[i].commun.x += e[i].commun.dx;
		e[i].commun.y += e[i].commun.dy;
	}
}

int main()
{
	Ennemi E[10];
	
	srand(time(NULL));
	
	InitEnnemis(E, 10);
	AfficheEnnemis(E, 10);
	printf("*************\n");
	AvanceEnnemis(E, 10);
	AfficheEnnemis(E, 10);

	return 0;
}