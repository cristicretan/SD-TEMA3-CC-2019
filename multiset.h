/*
* @Author: Cristi Cretan
* @Date:   22-04-2019 22:54:10
* @Last Modified by:   Cristi Cretan
* @Last Modified time: 04-05-2019 11:12:27
*/
#ifndef __MULTISET_H__
#define __MULTISET_H__

#include "helpers.h"

typedef struct multiset
{
	Pair vector[MAX];
	int size;
	int capacity;
} *Multiset;

Multiset initMultiset();
Multiset siftDown(Multiset H, int index);
Multiset siftUp(Multiset H, int index);
bool isEmptyMultiset(Multiset H);
Multiset insert(Multiset H, Pair value);
Pair extractMin(Multiset H);
Multiset freeMultiset(Multiset H);
#endif
