#ifndef RECTANGLE_H_
#define RECTANGLE_H_

typedef struct Rec
{
	int x, y, h, w;

	struct Rec* leg;
}Rec;

Rec* newRec(int, int, int, int);

void addRec(Rec**, Rec*);

void delRec(Rec**);

int checkColl(Rec*, Rec*);

#endif