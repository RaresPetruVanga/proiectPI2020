#include <stdlib.h>
#include "ByteVect.h"

Byte** makeMatrix(Byte* vec, int h, int w)
{
	Byte** pix = (Byte**)malloc(h * sizeof(Byte*));

	int i, j;

	int k = 0;

	for (i = 0; i < h; ++i)
	{
		pix[i] = (Byte*)malloc(w * sizeof(Byte));
	}

	for (i = 0; i < h; ++i)
	{
		for (j = 0; j < w; ++j)
		{
			pix[i][j] = vec[k];

			++k;
		}
	}

	return pix;
}

Byte** makeEmpty(int h, int w)
{
	Byte** pix = (Byte**)malloc(h * sizeof(Byte*));

	int i, j;

	for (i = 0; i < h; ++i)
	{
		pix[i] = (Byte*)malloc(w * sizeof(Byte));
	
		for (j = 0; j < w; ++j)
		{
			pix[i][j] = 0;
		}
	}

	return pix;
}

Byte* makeByte(Byte** pix, int h, int w)
{
	Byte* rez = (Byte*)malloc(w * h * sizeof(Byte));

	int i, j;

	int k = 0;

	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; ++j)
		{
			rez[k] = pix[i][j];
		
			++k;
		}
	}

	return rez;
}