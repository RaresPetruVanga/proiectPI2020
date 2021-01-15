#include <stdlib.h> 
#include "Rectangle.h"

//Constructor pentru tipul de data "Rec"
Rec* newRec(int x, int y, int h, int w)
{
	Rec* p = (Rec*)malloc(sizeof(Rec));

	p->x = x;

	p->y = y;

	p->h = h;

	p->w = w;

	p->leg = NULL;

	return p;
}

//Functie pentru adugarea in lista a unui dreptunghi
void addRec(Rec** src, Rec* obj)
{
	obj->leg = *src;

	(*src) = obj;
}

//Functie de stergere a unei liste de dreptunghiuri
void delRec(Rec** src)
{
	Rec* p;

	while (*src != NULL)
	{
		p = *src;

		(*src) = (*src)->leg;

		free(p);
	}
}

//Functie de detectare a coliziunii dintre doua dreptunghiuri
int checkColl(Rec* recA, Rec* recB)
{
	return (recA->x + recA->w >= recB->x &&
		recB->x + recB->w >= recA->x &&
		recA->y + recA->h >= recB->y &&
		recB->y + recB->h >= recA->y);
}
