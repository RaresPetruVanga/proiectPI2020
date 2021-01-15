#include "HistoGram.h"

int* histoGram(procBM* bmp)
{
	int* rez = (int*)malloc(256 * sizeof(int));
	
	int i;

	for (i = 0; i < 256; ++i)
	{
		rez[i] = 0;
	}

	procBM* gri = newBM(Gray(bmp, NULL), bmp->nrBytes);

	for (i = getOffset(gri); i < gri->nrBytes; ++i)
	{
		++rez[gri->vect[i]];

		i = i + 2;
	}

	return rez;
}

int* equalizeHistoGram(procBM* bmp)
{
	double* temp = (double*)malloc(256 * sizeof(double));

	int* rez = (int*)malloc(256 * sizeof(int));

	int* aux = histoGram(bmp);

	int i, j;

	double nrPix = getHeigth(bmp) * getWidth(bmp) / 3 + 1;

	for (i = 0; i < 256; ++i)
	{
		temp[i] = ((double)aux[i]) / nrPix;
	}

	for (i = 0; i < 256; ++i)
	{
		double sum = 0;

		for (j = 0; j < i + 1; ++j)
		{
			sum = sum + temp[j];
		}

		rez[i] = (int)floor(255 * sum);
	}

	free(temp);

	free(aux);

	return rez;
}

Byte* equalizedImage(procBM* bmp)
{
	int* obj = equalizeHistoGram(bmp);

	Byte* rez = (Byte*)malloc(bmp->nrBytes * sizeof(Byte));

	memcpy(rez, bmp->vect, getOffset(bmp) * sizeof(Byte));

	int i;

	for (i = getOffset(bmp); i < bmp->nrBytes; ++i)
	{
		rez[i] = obj[bmp->vect[i]];
	}

	return rez;
}

procBM* bandContrast(procBM* bmp)
{
	procBM* rez = (procBM*)malloc(sizeof(procBM));

	rez->vect = (Byte*)malloc(bmp->nrBytes * sizeof(Byte));

	Byte* Rband = (Byte*)malloc(bmp->nrBytes * sizeof(Byte));

	Byte* Gband = (Byte*)malloc(bmp->nrBytes * sizeof(Byte));

	Byte* Bband = (Byte*)malloc(bmp->nrBytes * sizeof(Byte));

	rez->nrBytes = bmp->nrBytes;

	int i;

	memcpy(rez->vect, bmp->vect, getOffset(bmp) * sizeof(Byte));

	memcpy(Bband, bmp->vect, getOffset(bmp) * sizeof(Byte));

	memcpy(Gband, bmp->vect, getOffset(bmp) * sizeof(Byte));
	
	memcpy(Rband, bmp->vect, getOffset(bmp) * sizeof(Byte));

	for (i = getOffset(bmp); i < bmp->nrBytes; ++i)
	{
		Bband[i] = bmp->vect[i];

		Bband[i + 1] = bmp->vect[i];

		Bband[i + 2] = bmp->vect[i];

		Gband[i] = bmp->vect[i + 1];

		Gband[i + 1] = bmp->vect[i + 1];

		Gband[i + 2] = bmp->vect[i + 1];

		Rband[i] = bmp->vect[i + 2];

		Rband[i + 1] = bmp->vect[i + 2];

		Rband[i + 2] = bmp->vect[i + 2];

		i = i + 2;
	}

	Bband = equalizedImage(newBM(Bband, bmp->nrBytes));

	Gband = equalizedImage(newBM(Gband, bmp->nrBytes));

	Rband = equalizedImage(newBM(Rband, bmp->nrBytes));

	for (i = getOffset(bmp); i < bmp->nrBytes; ++i)
	{
		rez->vect[i] = Bband[i];

		rez->vect[i + 1] = Gband[i];

		rez->vect[i + 2] = Rband[i];

		i = i + 2;
	}

	free(Bband);

	free(Gband);

	free(Rband);

	return rez;
}
