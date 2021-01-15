#include "Filtrare.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

Matr* newMatr(Byte** mat, int h, int w)
{
	Matr* obj = (Matr*)malloc(sizeof(Matr));

	obj->img = mat;

	obj->x = h;

	obj->y = w;

	return obj;
}

void medianFilter(Matr** src, int facth, int factw)
{
	int i, j, k, l, c, a;

	int valh = (facth / 2 + 1);

	for (i = 0; i < (*src)->x; ++i)
	{
		c = valh * (factw / 2 + 1);

		a = 0;

		for (k = -facth / 2; k < facth / 2; ++k)
		{
			for (l = 0; l < factw / 2; ++l)
			{
				if (i + k >= 0 && i + k < (*src)->x)
				{
					if ((*src)->img[i + k][l] == 255)
					{
						++a;
					}
				}
			}
		}

		if (a > (c / 2))
		{
			(*src)->img[i][0] = 255;
		}
		else
		{
			(*src)->img[i][0] = 0;
		}

		for (j = 1; j < (*src)->y; ++j)
		{
			if (j - factw / 2 <= 0)
			{
				c = c + valh;
			}

			if (j + factw / 2 >= (*src)->y)
			{
				c = c - valh;
			}
			
			for (k = -facth / 2; k <= facth / 2; ++k)
			{
				if (i + k >= 0 && i + k < (*src)->x)
				{
					if (j - factw / 2 > 0 && j + factw / 2 < (*src)->y)
					{
						a = a - ((*src)->img[i + k][j - factw / 2 - 1] == 255) + ((*src)->img[i + k][j + factw / 2] == 255);
					}
					else
					{
						a = a + (j - factw / 2 <= 0) * ((*src)->img[i + k][j + factw / 2] == 255) - (j + factw / 2 >= (*src)->y) * ((*src)->img[i + k][j - factw / 2 - 1] == 255);
					}
				}
			}

			if (a > (c / 2))
			{
				if ((*src)->img[i][j] != 255)
				{
					(*src)->img[i][j] = 255;
				
					++a;
				}
			}
			else
			{
				if ((*src)->img[i][j] != 0)
				{
					(*src)->img[i][j] = 0;
				
					--a;
				}
			}
		}

		if (i - facth / 2 < 0)
		{
			++valh;
		}
		
		if (i + facth / 2 > (*src)->x)
		{
			--valh;
		}
	}
}

void delMatr(Matr** src)
{
	int i;

	for (i = 0; i < (*src)->x; ++i)
	{
		free((*src)->img[i]);
	}

	free((*src)->img);
}