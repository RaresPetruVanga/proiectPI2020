#include "Procesare.h"

Byte* Gray(Byte* bmp, int size)
{
	Byte* rez = (Byte*)malloc(size * 3 * sizeof(Byte));

	int i;

	for (i = 0; i < size; ++i)
	{
		rez[i] = (bmp[i * 3] + bmp[i * 3 + 1] + bmp[i * 3 + 2]) / 3;
	}

	return rez;
}
