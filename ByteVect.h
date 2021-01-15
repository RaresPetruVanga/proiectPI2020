#ifndef BYTEVECT_H_
#define BYTEVECT_H_

#include <stdlib.h>

typedef unsigned char Byte;

typedef struct PixelColor
{
	Byte r, g, b;
}PixelColor;

Byte** makeMatrix(Byte* , int , int);

Byte** makeEmpty(int, int);

Byte* makeByte(Byte** , int , int);

#endif