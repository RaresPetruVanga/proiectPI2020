#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#include "Procesare.h"

int* histoGram(procBM* bmp);

int* equalizeHistoGram(procBM* bmp);

Byte* equalizedImage(procBM* bmp);

procBM* bandContrast(procBM* bmp);

#endif