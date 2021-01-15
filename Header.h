#ifndef HEADER_H_
#define HEADER_H_
#include "Procesare.h"
#include "Filtrare.h"
#include "Queue.h"
#include "Rectangle.h"

int searchRec(Rec*** , Rec*);

int countRec();

void DilateImg(Matr** , int);

void ErodeImg(Matr** , int);

void OpenImg(Matr**, int);

void CloseImg(Matr**, int);

Byte* subtractingImage(Byte*, Byte*, int, int, int);

void blobFilter(Matr** , int);

Rec* fenceBlob(Matr**);

void drawBlob(Byte**, int, Rec*);

Byte* PipeLine(Byte** , Byte**, int, int);

//Rec* growReg(procBM* src, int x, int y, int thresh);

#endif