/*
 * @Author: Cristi Cretan
 * @Date:   27-04-2019 19:36:27
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 10-05-2019 16:51:30
 */
#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MEMERROR      "Memory was not correcly allocated.\n"
#define MAX           100001
#define CAP           4
#define resizeFactor  2
#define INF           0x3f3f3f3f

typedef struct actor
{
	int id;
	char *name;
} *Actor;

typedef struct pair
{
	int node, cost;
} *Pair;

char *strdup(const char *c);
char *readActorLine(FILE *stream);
int myStrcmp(const void *a_pointer, const void *b_pointer);
int intCompare(const void *a_pointer, const void *b_pointer);
int pairCompare(const void *a_pointer, const void *b_pointer);
int min(int a, int b);
int *allocInt(int x);
Actor actorFromName(char *actorName);
int binarySearch(int *array, int left, int right, int key);
Actor freeActor(Actor actor);
Pair make_pair(int node, int cost);
#endif
