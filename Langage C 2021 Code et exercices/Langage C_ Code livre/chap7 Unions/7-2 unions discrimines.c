// UNIONS DISCRIMINEES
#include <stdio.h>  
#include <stdlib.h>

typedef enum { TEMPERATURE, VENT, MAXTYPE }TypeData;
typedef enum { NORD, EST, SUD, OUEST, MAXDIR }DirVent;

typedef struct
{
	int idStation;
	int min, max, actuelle;
}Temperature;
typedef struct
{
	int idStation;
	int vitesse;
	int direction;
}Vent;

typedef struct
{
	TypeData type;
	union
	{
		Temperature temp;
		Vent vent;
	};

}Data;
Vent init_vent()
{
	Vent v;

	v.idStation = rand() % 10;
	v.direction = rand() % MAXDIR;
	v.vitesse = rand() % 250;
	return v;
}
void affiche_vent(Vent v)
{
	printf("VENT :\n");
	printf("idStation : %d\n", v.idStation);
	printf("Direction : ");
	switch (v.direction) {
	case NORD: printf("NORD\n");	break;
	case EST: printf("EST\n");		break;
	case SUD: printf("SUD\n");		break;
	case OUEST: printf("OUEST\n");	break;
	}
	printf("Vitesse : %d\n", v.vitesse);
	printf("-----------------\n");
}
Temperature init_temperature()
{
	Temperature t;
	t.idStation = rand() % 10;
	t.actuelle = rand() % 120 - 40;
	t.min = -rand() % 40;
	if (t.min > t.actuelle)
		t.min = t.actuelle;
	t.max = rand() % 80;
	if (t.max < t.actuelle)
		t.max = t.actuelle;
	return t;
}
void affiche_temperature(Temperature t)
{
	printf("TEMPERATURE :\n");
	printf("idStation : %d\n", t.idStation);
	printf("Actuelle : %d\n", t.actuelle);
	printf("Min : %d\n", t.min);
	printf("Max : %d\n", t.max);
	printf("-----------------\n");
}

Data init_data(TypeData type)
{
	Data d;
	d.type = type;
	switch (d.type)
	{
	case TEMPERATURE:
		d.temp = init_temperature();
		break;
	case VENT:
		d.vent = init_vent();
		break;
	}
	return d;
}
void affiche_data(Data d)
{
	switch (d.type)
	{
	case TEMPERATURE:
		affiche_temperature(d.temp);
		break;
	case VENT:
		affiche_vent(d.vent);
		break;
	}
}

int main()
{
	Data d1, d2;

	d1 = init_data(TEMPERATURE);
	affiche_data(d1);

	d2 = init_data(VENT);
	affiche_data(d2);

	return 0;
}
