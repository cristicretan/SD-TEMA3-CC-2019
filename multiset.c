/*
* @Author: Cristi Cretan
* @Date:   22-04-2019 22:53:49
* @Last Modified by:   Cristi Cretan
* @Last Modified time: 10-05-2019 10:48:38
*/

#include "multiset.h"

/**
 * Initialises multiset.
 * @return [Initialised multiset]
 */
Multiset initMultiset()
{
	Multiset H = (Multiset)malloc(sizeof(struct multiset));

	H->size = 0;
	H->capacity = MAX;

	return H;
}

/**
 * Puts an item from a given index down the multiset, where it's place should be.
 * @param  H     [Multiset]
 * @param  index [Given index]
 * @return       [Multiset with the item in the correct place]
 */
Multiset siftDown(Multiset H, int index)
{
	int maxIndex = index;

	int l = index * 2 + 1;
	
	if(l < H->size && H->vector[l]->cost < H->vector[maxIndex]->cost)
		maxIndex = l;

	int r = index * 2 + 2;

	if(r < H->size && H->vector[r]->cost < H->vector[maxIndex]->cost)
		maxIndex = r;

	if(index != maxIndex)
	{
		Pair aux = H->vector[index];

		H->vector[index] = H->vector[maxIndex];

		H->vector[maxIndex] = aux;

		H = siftDown(H, maxIndex);
	}

	return H;
}

/**
 * Puts an item from a given index up the multiset, where it should be.
 * @param  H     [Multiset]
 * @param  index [Given index]
 * @return       [Multiset with item in the correct place]
 */
Multiset siftUp(Multiset H, int index)
{
	while(index >= 0 && H->vector[(index - 1) / 2]->cost > H->vector[index]->cost)
	{
		Pair aux = H->vector[(index - 1) / 2];

		H->vector[(index - 1) / 2] = H->vector[index];

		H->vector[index] = aux;

		index = (index - 1) / 2;
	}

	return H;
}

/**
 * Checks if the multiset is empty.
 * @param  H [Multiset]
 * @return   [True if it's empty, false otherwise]
 */
bool isEmptyMultiset(Multiset H)
{
	if(!H || H->size == 0)
		return true;
	
	return false;
}

/**
 * Insert an item the multiset.
 * @param  H     [Multiset]
 * @param  value [Item]
 * @return       [Multiset with the item inserted]
 */
Multiset insert(Multiset H, Pair value)
{
	H->vector[H->size] = value;

	H = siftUp(H, H->size);
	H->size++;

	return H;
}

/**
 * Extracts the minimum item from the multiset.
 * @param  H [Multiset]
 * @return   [Item if it's exists, NULL otherwise]
 */
Pair extractMin(Multiset H)
{
	if(H && H->size >= 0)
	{
		Pair max;
		max = H->vector[0];

		H->vector[0] = H->vector[H->size - 1];
		H->size--;
		H = siftDown(H, 0);

		return max;
	}
	return NULL;
}

/**
 * Frees multiset.
 * @param  H [Multiset]
 * @return   [NULL]
 */
Multiset freeMultiset(Multiset H)
{
	free(H);
	return NULL;
}
