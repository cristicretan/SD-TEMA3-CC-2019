/*
 * @Author: Cristi Cretan
 * @Date:   27-04-2019 19:36:02
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 10-05-2019 21:52:36
 */

#include "helpers.h"

/**
 * Allocates the necessary size for the string given and returns a pointer
 * to the start of the allocated string.
 * @param  c [String to allocated]
 * @return   [Pointer to the start of the allocated string]
 */
char *strdup(const char *c)
{
	int len = strlen(c) + 1;

	char *ret = (char *)malloc(len * sizeof(char));

	if (!ret)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	return (char *)memcpy(ret, c, len);
}

/**
 * Reads a line from the file with the given format.
 * @param  stream [File stream]
 * @return        [String read]
 */
char *readActorLine(FILE *stream)
{
	char letter;
	int cap = CAP;
	int k = 0;

	char *actorName = (char *)malloc(cap * sizeof(char));

	if (!actorName)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	fscanf(stream, "%c", &letter);

	while (true)
	{
		if (letter == '\n')
			break;

		if (k == cap - 1)
		{
			cap *= resizeFactor;

			actorName = (char *)realloc(actorName, cap * sizeof(char));
			if (!actorName)
			{
				fprintf(stderr, MEMERROR);
				exit(1);
			}
		}

		actorName[k++] = letter;

		fscanf(stream, "%c", &letter);
	}
	actorName[k] = '\0';

	return actorName;
}

/**
 * Function that compares 2 actors by their names.
 * @param  a_pointer [Pointer to first actor]
 * @param  b_pointer [Pointer to second actor]
 * @return           [Standard strcmp return]
 */
int myStrcmp(const void *a_pointer, const void *b_pointer)
{
	Actor a = (Actor)a_pointer;
	Actor b = (Actor)b_pointer;

	return strcmp(a->name, b->name);
}

/**
 * Function that compares 2 integers.
 * @param  a_pointer [Pointer to first integer]
 * @param  b_pointer [Pointer to second integer]
 * @return           [Standard comparison return]
 */
int intCompare(const void *a_pointer, const void *b_pointer)
{
	return *(int *)a_pointer - *(int *)b_pointer;
}

/**
 * Function that compares 2 Pair structures.
 * @param  a_pointer [Pointer to first Pair]
 * @param  b_pointer [Pointer to second Pair]
 * @return           [Standard comparison return]
 */
int pairCompare(const void *a_pointer, const void *b_pointer)
{
	Pair a = (Pair)a_pointer;
	Pair b = (Pair)b_pointer;

	return a->cost - b->cost;
}

/**
 * Returns the minimum between 2 integers.
 * @param  a [Fist integer]
 * @param  b [Second integer]
 * @return   [minimum]
 */
int min(int a, int b)
{
	if (a > b)
		return b;
	return a;
}

/**
 * Allocates memory of a single integer and returns the pointer.
 * @param  x [Value of the integer]
 * @return   [Pointer to that value]
 */
int *allocInt(int x)
{
	int *ret = (int *)malloc(sizeof(int));

	if (!ret)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	*ret = x;

	return ret;
}

/**
 * Allocates memory for an Actor structure and it's name field
 * and returns it.
 * @param  actorName [Desired name]
 * @return           [Pointer to the allocated structure]
 */
Actor actorFromName(char *actorName)
{
	Actor new = (Actor)malloc(sizeof(struct actor));

	if (!new)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	new->name = strdup(actorName);

	return new;
}

/**
 * Iterative binary search, it returns the position of the key
 * if it finds it, -1 otherwise.
 * @param  array [Array]
 * @param  left  [Leftmost location]
 * @param  right [Rightmost location]
 * @param  key   [Key to search for]
 * @return       [The location if it's found, -1 otherwise]
 */
int binarySearch(int *array, int left, int right, int key)
{
	if(right == 0)
		return -1;
	
	while (left <= right)
	{
		int mid = left + (right - left)/2;

		if (array[mid] == key)
			return mid;

		if (array[mid] < key)
			left = mid + 1;
		else
			right = mid - 1;
	}

	return -1;
}

/**
 * Frees a structure of type Actor.
 * @param  actor [Actor structure]
 * @return       [NULL]
 */
Actor freeActor(Actor actor)
{
	free(actor->name);
	free(actor);
	return NULL;
}

/**
 * Makes Pair structure from 2 given integers.
 * @param  node [First integer]
 * @param  cost [Second integer]
 * @return      [Pair]
 */
Pair make_pair(int node, int cost)
{
	Pair pair = (Pair)malloc(sizeof(struct pair));

	if (!pair)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	pair->node = node;
	pair->cost = cost;

	return pair;
}
