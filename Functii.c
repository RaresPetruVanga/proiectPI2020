#include "Header.h"

int nrTemp, nrTot = 0;

Rec* primaryRecs = NULL;

Rec* previousRecs = NULL;

Rec* currentRecs = NULL;

Rec* lostRecs = NULL;

int searchRec(Rec** vect, Rec* p)
{
	Rec* currentRecs = *vect;

	while (currentRecs != NULL)
	{
		if(checkColl(currentRecs, p))
		{
			return 1;
		}

		currentRecs = currentRecs->leg;
	}

	free(currentRecs);

	return 0;
}

int countRec()
{
	Rec* p = currentRecs;

	Rec* rez = NULL;

	Rec* rezLost = NULL;

	int nr = 0;

	while (p != NULL)
	{
		if (searchRec(&primaryRecs, p) == 0)
		{
			if (searchRec(&previousRecs, p) == 1)
			{
				addRec(&rez, newRec(p->x, p->y, p->h, p->w));

				++nr;

				if (searchRec(&lostRecs, p) == 0)
				{
					++nrTot;
				}
			}
		}
		else
		{
			addRec(&rez, newRec(p->x, p->y, p->h, p->w));

			++nr;
		}

		p = p->leg;
	}

	p = primaryRecs;

	while (p != NULL)
	{
		if (searchRec(&currentRecs, p) == 0)
		{
			if (searchRec(&previousRecs, p) == 1)
			{
				addRec(&rez, newRec(p->x, p->y, p->h, p->w));

				++nr;
			}
			else
			{
				addRec(&rezLost, newRec(p->x - p->h * 2, p->y - p->w * 2, p->h + p->h * 2, p->w + p->w * 2));
			}
		}

		p = p->leg;
	}

	p = rezLost;

	while (p != NULL)
	{
		if (searchRec(&lostRecs, p) == 0)
		{
			addRec(&rezLost, newRec(p->x - p->h * 2, p->y - p->w * 2, p->h + p->h * 2, p->w + p->w * 2));
		}

		p = p->leg;
	}

	delRec(&lostRecs);

	lostRecs = rezLost;

	delRec(&primaryRecs);

	primaryRecs = rez;

	delRec(&previousRecs);

	previousRecs = currentRecs;

	free(p);

	return nr;
}

Byte* PipeLine(Byte** img1, Byte** img2, int h, int w)
{
	int aux1 = nrTemp, aux2 = nrTot;

	Matr* orig = newMatr(makeMatrix(subtractingImage(*img1, *img2, h, w, 20), h, w), h, w);

	medianFilter(&orig, 7, 7);

	OpenImg(&orig, 3);

	blobFilter(&orig, 80);

	CloseImg(&orig, 10);

	currentRecs = fenceBlob(&orig);

	nrTemp = countRec();

	if (aux1 != nrTemp || aux2 != nrTot)
	{
		system("cls");

		printf("Totalitatea masinilor: %d\nMasini in cadrul prezent: %d", nrTot, nrTemp);
	}

	drawBlob(img2, w, primaryRecs);
	
	Byte* rez = makeByte(orig->img, orig->x, orig->y);

	delMatr(&orig);
	
	free(orig);

	return rez;
}

void DilateImg(Matr** src, int depth)
{
	Matr* orig = newMatr(makeEmpty((*src)->x, (*src)->y), (*src)->x, (*src)->y);

	int i, j, x, var;

	for (i = 0; i < (*src)->x; ++i)
	{
		memcpy(orig->img[i], (*src)->img[i], (*src)->y * sizeof(Byte));
	}

	while (depth > 0)
	{
		for (i = 0; i < orig->x; ++i)
		{
			for (j = 0; j < orig->y; ++j)
			{
				var = 0;

				if ((*src)->img[i][j] == 0)
				{
					while (var < 2)
					{
						x = 1 * (var == 0) - 1 * (var == 1);

						if (i + x < orig->x && i + x > -1)
						{
							orig->img[i + x][j] = 0;

							if (j - x < orig->y && j - x > -1)
							{
								orig->img[i + x][j - x] = 0;
							}
						}

						if (j + x < orig->y && j + x > -1)
						{
							orig->img[i][j + x] = 0;

							if (i + x < orig->x && i + x > -1)
							{
								orig->img[i + x][j + x] = 0;
							}
						}

						++var;
					}
				}
			}
		}

		for (i = 0; i < (*src)->x; ++i)
		{
			if (memcmp((*src)->img[i], orig->img[i], orig->y * sizeof(Byte)) != 0)
			{
				memcpy((*src)->img[i], orig->img[i], orig->y * sizeof(Byte));
			}
		}

		--depth;
	}

	delMatr(src);

	free(*src);

	*src = orig;
}

void ErodeImg(Matr** src, int depth)
{
	Matr* orig = newMatr(makeEmpty((*src)->x, (*src)->y), (*src)->x, (*src)->y);

	int i, j, x, var;

	for (i = 0; i < (*src)->x; ++i)
	{
		memcpy(orig->img[i], (*src)->img[i], (*src)->y * sizeof(Byte));
	}

	while (depth > 0)
	{
		for (i = 0; i < orig->x; ++i)
		{
			for (j = 0; j < orig->y; ++j)
			{
				var = 0;

				if ((*src)->img[i][j] == 255)
				{
					while (var < 2)
					{
						x = 1 * (var == 0) - 1 * (var == 1);

						if (i + x < orig->x && i + x > -1)
						{
							orig->img[i + x][j] = 255;

							if (j - x < orig->y && j - x > -1)
							{
								orig->img[i + x][j - x] = 255;
							}
						}

						if (j + x < orig->y && j + x > -1)
						{
							orig->img[i][j + x] = 255;

							if (i + x < orig->x && i + x > -1)
							{
								orig->img[i + x][j + x] = 255;
							}
						}

						++var;
					}
				}
			}
		}

		for (i = 0; i < (*src)->x; ++i)
		{
			if (memcmp((*src)->img[i], orig->img[i], orig->y * sizeof(Byte)) != 0)
			{
				memcpy((*src)->img[i], orig->img[i], orig->y * sizeof(Byte));
			}
		}

		--depth;
	}

	delMatr(src);

	free(*src);

	*src = orig;
}

void OpenImg(Matr** src, int depth)
{
	DilateImg(src, depth);

	ErodeImg(src, depth);
}

void CloseImg(Matr** src, int depth)
{
	ErodeImg(src, depth);

	DilateImg(src, depth);
}

void blobFilter(Matr** src, int n)
{
	Matr* mask = newMatr(makeEmpty((*src)->x, (*src)->y), (*src)->x, (*src)->y);

	Matr* mask2 = newMatr(makeEmpty(mask->x, mask->y), mask->x, mask->y);

	int i, j;

	stack* stk = NULL;

	for (i = 0; i < mask->x; ++i)
	{
		for (j = 0; j < mask->y; ++j)
		{
			if ((*src)->img[i][j] == 255 && mask2->img[i][j] != 255)
			{
				stk = newQue(i, j);

				mask->img[i][j] = 255;

				stack* q = NULL;

				int x, y, var, max = 1;

				do
				{ 
					q = pop(&stk);

					for (var = 0; var < 4; ++var)
					{
						x = q->x + 1 * (var % 2 != 0 && var < 2) - 1 * (var % 2 != 1 && var >= 2);

						y = q->y + 1 * (var < 2 && var % 2 == 0) - 1 * (var >= 2 && var % 2 == 1);

						if (x < mask->x && x > -1 && y < mask->y && y > -1 && (*src)->img[x][y] == 255 && mask->img[x][y] == 0)
						{
							push(&stk, newQue(x, y));

							mask->img[x][y] = 255;

							++max;
						}
					}

					free(q);

				} while (isEmpty(stk) > 0);

				if (max < n)
				{
					for (x = 0; x < mask->x; ++x)
					{
						for (y = 0; y < mask->y; ++y)
						{	
							mask->img[x][y] = 0;

							mask->img[x][y] = 0;
						}
					}
				}
				else
				{
					for (x = 0; x < mask->x; ++x)
					{
						for (y = 0; y < mask->y; ++y)
						{
							if (mask->img[x][y] == 255)
							{
								mask2->img[x][y] = 255;

								mask->img[x][y] = 0;
							}
						}
					}
				}
			}
		}
	}

	delMatr(&mask);

	free(mask);

	delMatr(src);

	free(*src);

	*src = mask2;
}

Rec* fenceBlob(Matr** src)
{
	Rec* vect = NULL;
	
	Matr* mask = newMatr(makeEmpty((*src)->x, (*src)->y), (*src)->x, (*src)->y);

	int i, j;

	stack* stk = NULL;

	for (i = 0; i < mask->x; ++i)
	{
		for (j = 0; j < mask->y; ++j)
		{
			int xVal, yVal, hVal, wVal;

			if ((*src)->img[i][j] == 255 && mask->img[i][j] != 255)
			{
				stk = newQue(i, j);

				mask->img[i][j] = 255;

				stack* q = NULL;

				int x, y, var;

				xVal = i;

				yVal = j;

				hVal = i;

				wVal = j;

				do
				{
					q = pop(&stk);

					for (var = 0; var < 4; ++var)
					{
						x = q->x + 1 * (var % 2 != 0 && var < 2) - 1 * (var % 2 != 1 && var >= 2);

						y = q->y + 1 * (var < 2 && var % 2 == 0) - 1 * (var >= 2 && var % 2 == 1);

						if (x < mask->x && x > -1 && y < mask->y && y > -1 && (*src)->img[x][y] == 255 && mask->img[x][y] == 0)
						{
							push(&stk, newQue(x, y));

							mask->img[x][y] = 255;

							yVal = yVal * (yVal <= y) + y * (yVal > y);

							xVal = xVal * (xVal <= x) + x * (xVal > x);

							hVal = hVal * (hVal >= x) + x * (hVal < x);

							wVal = wVal * (wVal >= y) + y * (wVal < y);
						}
					}

					free(q);

				} while (isEmpty(stk) > 0);

				hVal = hVal - xVal;

				wVal = wVal - yVal;

				addRec(&vect, newRec(xVal, yVal, hVal, wVal));
			}
		}
	}

	Rec* p = vect;

	while (p != NULL)
	{
		for (i = 0; i <= p->h; ++i)
		{
			mask->img[p->x + i][p->y] = 255;

			mask->img[p->x + i][p->y + p->w] = 255;
		}

		for (i = 1; i < p->w; ++i)
		{
			mask->img[p->x][p->y + i] = 255;

			mask->img[p->x + p->h][p->y + i] = 255;
		}

		p = p->leg;
	}

	delMatr(src);

	free(*src);

	*src = mask;

	return vect;
}

void drawBlob(Byte** src, int w, Rec* vect)
{
	Rec* p = vect;

	int i;

	while (p != NULL)
	{
		for (i = 0; i <= p->h; ++i)
		{
			(*src)[(p->x + i) * w * 3 + 3 * (p->y + p->w)] = 255;

			(*src)[(p->x + i) * w * 3 + 3 * (p->y + p->w) + 1] = 255;

			(*src)[(p->x + i) * w * 3 + 3 * (p->y + p->w) + 2] = 255;

			(*src)[(p->x + i) * w * 3 + 3 * p->y] = 255;

			(*src)[(p->x + i) * w * 3 + 3 * p->y + 1] = 255;

			(*src)[(p->x + i) * w * 3 + 3 * p->y + 2] = 255;
		}

		for (i = 1; i < p->w; ++i)
		{
			(*src)[p->x * w * 3 + 3 * (p->y + i) + 1] = 255;

			(*src)[p->x * w * 3 + 3 * (p->y + i) + 2] = 255;

			(*src)[p->x * w * 3 + 3 * (p->y + i)] = 255;

			(*src)[(p->x + p->h) * w * 3 + 3 * (p->y + i) + 1] = 255;

			(*src)[(p->x + p->h) * w * 3 + 3 * (p->y + i) + 2] = 255;

			(*src)[(p->x + p->h) * w * 3 + 3 * (p->y + i)] = 255;
		}

		p = p->leg;
	}

	free(p);
}

Byte* subtractingImage(Byte* sam1, Byte* sam2, int h, int w, int val)
{
	Byte* rez = (Byte*)malloc(h * w * sizeof(Byte));

	Byte* aux1 = Gray(sam1, h * w);

	Byte* aux2 = Gray(sam2, h * w);

	int i;

	for (i = 0; i < h * w; ++i)
	{
		if (abs(aux1[i] - aux2[i]) <  val)
		{
			rez[i] = 0;
		}
		else
		{
			rez[i] = 255;
		}
	}

	free(aux1);

	free(aux2);

	return rez;
}

/*Rec* growReg(procBM* src, int x, int y, int thresh)
{
	Matr* mat = newMatr(makeMatrix(src->vect + getOffset(src), getHeigth(src), getWidth(src)), getHeigth(src), getWidth(src));

	Matr* mask = newMatr(makeEmpty(mat->x, mat->y), mat->x, mat->y);

	mask->img[x][y] = mat->img[x][y];

	stack* stk = newQue(x, y);

	stack* current = NULL;

	int xVal = x, yVal = y, hVal = x, wVal = y;

	do
	{
		current = pop(&stk);

		if (current->x + 1 < mat->x && mask->img[current->x + 1][current->y] == 0 && abs(mat->img[current->x + 1][current->y] - mat->img[x][y]) < thresh)
		{
			push(&stk, newQue(current->x + 1, current->y));

			mask->img[current->x + 1][current->y] = mat->img[current->x + 1][current->y];

			hVal = hVal * (current->x + 1 <= hVal) + (current->x + 1) * (current->x + 1 > hVal);
		}

		if (current->y - 1 > -1 && mask->img[current->x][current->y - 1] == 0 && abs(mat->img[current->x][current->y - 1] - mat->img[x][y]) < thresh)
		{
			push(&stk, newQue(current->x, current->y - 1));

			mask->img[current->x][current->y - 1] = mat->img[current->x][current->y - 1];

			yVal = yVal * (current->y - 1 >= yVal) + (current->y - 1) * (current->y < yVal);
		}

		if (current->x - 1 > -1 && mask->img[current->x - 1][current->y] == 0 && abs(mat->img[current->x - 1][current->y] - mat->img[x][y]) < thresh)
		{
			push(&stk, newQue(current->x - 1, current->y));

			mask->img[current->x - 1][current->y] = mat->img[current->x - 1][current->y];

			xVal = xVal * (current->x - 1 >= xVal) + (current->x - 1) * (current->x < xVal);
		}

		if (current->y + 1 < mat->y && mask->img[current->x][current->y + 1] == 0 && abs(mat->img[current->x][current->y + 1] - mat->img[x][y]) < thresh)
		{
			push(&stk, newQue(current->x, current->y + 1));

			mask->img[current->x][current->y + 1] = mat->img[current->x][current->y + 1];
		
			wVal = wVal * (current->y + 1 <= wVal) + (current->y + 1) * (current->y + 1 > wVal);
		}

		free(current);

	} while (isEmpty(stk) != 0);

	hVal = hVal - xVal;

	wVal = wVal - yVal;

	free(stk);

	delMatr(&mat);

	free(mat);

	Byte* result = makeByte(mask->img, mask->x, mask->y);

	delMatr(&mask);

	free(mask);

	return newRec(xVal, yVal, hVal, wVal);
}*/