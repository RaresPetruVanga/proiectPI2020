#ifndef FILTRARE_H_
#define FILTRARE_H_

#include "ByteVect.h"

typedef struct Matr {
	Byte** img;
	int x;
	int y;
}Matr;

Matr* newMatr(Byte**, int, int);

void medianFilter(Matr** , int , int);

void delMatr(Matr** src);

#endif