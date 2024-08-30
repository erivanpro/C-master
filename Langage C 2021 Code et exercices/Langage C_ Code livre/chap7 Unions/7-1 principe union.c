#include <stdio.h>

typedef union {
	char c;
	int i;
	float f;
	double d;
}utest;


int main()
{
	utest u;
	printf("%d\n", sizeof(u)); // imprime 8, taille du double

	u.c = 'A'; // u pris comme char, 8 octets
	printf("%c, %d octets\n", u.c, sizeof(u));

	u.i = 350; // u pris comme int, 8 octets
	printf("%d, %d octets\n", u.i, sizeof(u));

	u.f = 1.5; // u pris comme float, 8 octets
	printf("%f, %d octets\n", u.f, sizeof(u));

	u.d = 2.5; // u pris comme double, 8 octets
	printf("%lf, %d octets\n", u.d, sizeof(u));

	return 0;
}
