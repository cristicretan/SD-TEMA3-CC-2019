/*
 * @Author: Cristi Cretan
 * @Date:   22-04-2019 17:53:49
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 08-05-2019 16:32:50
 */
#include "helpers.h"
#include "binaryTree.h"
#include "graph.h"

/**
 * Determines the number of independent productions
 * of actors.
 * @param  G [Graph]
 * @return   [Integer representing the number of productions]
 */
int numberOfProductions(Graph G)
{
	int numberProductions = 0;

	for (int i = 0; i < G->V; ++i)
		if (G->distance[i] == 0)
		{
			numberProductions++;
			G = DFS(G, i);
		}
	return numberProductions;
}

/**
 * Determines the degree of kinship between 2 separate actors. The degree of
 * kinship represents what is the minimum number of actors that I have to get
 * to before getting to the actor I want.
 * @param  G          [Graph]
 * @param  BST        [Binary Search Tree with Actor's name and id]
 * @param  actorName1 [The name of the first actor]
 * @param  actorName2 [The name of the second actor]
 * @return            [The degree of kinship]
 */
int degreeOfKinship(Graph G, BinaryTree BST, char *actorName1, char *actorName2)
{
	Actor toSearch1 = actorFromName(actorName1);
	Actor toSearch2 = actorFromName(actorName2);


	Actor actor1 = (Actor)containsInBinaryTree(BST, toSearch1);
	Actor actor2 = (Actor)containsInBinaryTree(BST, toSearch2);

	G = BFS(G, actor1->id);

	toSearch1 = freeActor(toSearch1);
	toSearch2 = freeActor(toSearch2);

	return G->distance[actor2->id];
}

/**
 * Prints a full binary search tree of actors in lexicographical order
 * in a specified file.
 * @param BST [Binary Tree of actors]
 * @param stream   [File stream to print into]
 */
void printActorTree(BinaryTree BST, FILE *stream)
{
	if (BST)
	{
		printActorTree(BST->left, stream);
		Actor actor = (Actor)BST->item;
		fprintf(stream, "%s\n", actor->name);
		printActorTree(BST->right, stream);
	}
}

/**
 * Determines the cut vertices of a given graph and prints the number of such
 * cut vertices and every cut vertex in lexicographical order into the
 * specified stream.
 * @param G [Graph]
 * @param stream [File stream]
 */
void cutVertex(Graph G, FILE *stream)
{
	BinaryTree cutVertices = NULL;

	int *idx = (int *)malloc(G->V * sizeof(int));

	if (!idx)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	int *low = (int *)malloc(G->V * sizeof(int));

	if (!low)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	for (int i = 0; i < G->V; ++i)
	{
		idx[i] = -1;
		low[i] = INF;
	}

	for (int i = 0; i < G->V; ++i)
		if (idx[i] == -1)
			cutVertices = articulationP(G, cutVertices, i, idx, low, i);

	fprintf(stream, "%d\n", cutVertices->size);

	printActorTree(cutVertices, stream);

	free(idx);
	free(low);
	cutVertices = freeActorBinaryTree(cutVertices);
}

/**
 * Determines a maximal clique from a given graph, which is nothing but a
 * complete maximal subgraph of the original graph, using Bron-Kerbosch.
 * @param G   [Graph]
 * @param BST [Binary Search Tree on Actors]
 * @param stream   [File stream]
 */
void maximalClique(Graph G, BinaryTree BST, FILE *stream)
{
	BinaryTree R = NULL;
	List P = NULL;
	List X = NULL;
	int mx = 0;

	for (int i = 0; i < G->V; ++i)
	{
		int *toADD = allocInt(i);

		P = addLast(P, toADD, intCompare);
	}

	BinaryTree Rans = NULL;

	for (int i = 0; i < G->V; ++i)
	{
		X = NULL;
		R = NULL;
		R = BronKerbosch(G, R, P, X);

		R->size = checkBSTsize(R);

		if (R->size > mx)
		{
			mx = R->size;
			Rans = freeActorBinaryTree(Rans);
			Rans = copyBST(R);
			Rans->size = mx;
		}
		P = freeIntList(P);
		for (int j = i; j < G->V; ++j)
		{
			int *toADD = allocInt(j);

			P = addLast(P, toADD, intCompare);
		}

		for (int j = 0; j < i; ++j)
		{
			int *toADD = allocInt(j);

			*toADD = j;

			P = addLast(P, toADD, intCompare);
		}
	}

	Rans->size = checkBSTsize(Rans);

	fprintf(stream, "%d\n", Rans->size);

	printActorTree(Rans, stream);

	R = freeActorBinaryTree(R);
	P = freeIntList(P);
	X = freeIntList(X);
}

/**
 * Main program driver function. Takes as arguments which task to solve and
 * the input file and output file.
 * @param  argc [Number of arguments]
 * @param  argv [Arguments array]
 */
int main(int argc, char *argv[])
{
	Graph G = initGraph(MAX);
	BinaryTree BST = NULL;
	int N;
	FILE *f = fopen(argv[2], "r");

	if (!f)
	{
		perror(argv[2]);
		exit(1);
	}

	fscanf(f, "%d\n", &N);

	for (int i = 0; i < N; ++i)
	{
		char *movieName = readActorLine(f);
		int actnr;

		fscanf(f, "%d\n", &actnr);

		char **actorNames = (char **)malloc(actnr * sizeof(char *));

		for (int j = 0; j < actnr; ++j)
		{
			actorNames[j] = readActorLine(f);

			Actor toADD = actorFromName(actorNames[j]);

			Actor check = NULL;
			check = (Actor)containsInBinaryTree(BST, toADD);

			if (!check)
			{
				if (!BST)
				{
					toADD->id = 0;
					BST = insertInBinaryTree(BST, toADD, myStrcmp);
				}
				else
				{
					toADD->id = BST->size;
					BST = insertInBinaryTree(BST, toADD, myStrcmp);
				}
			}
			else
				toADD = freeActor(toADD);
		}

		for (int j = 0; j < actnr; ++j)
			for (int k = j + 1; k < actnr; ++k)
			{
				Actor toSearch1 = actorFromName(actorNames[j]);
				Actor toSearch2 = actorFromName(actorNames[k]);

				Actor first = (Actor)containsInBinaryTree(BST, toSearch1);
				Actor second = (Actor)containsInBinaryTree(BST, toSearch2);

				G = insertEdge(G, first->id, second->id, first->name, intCompare);
				G = insertEdge(G, second->id, first->id, second->name, intCompare);

				toSearch1 = freeActor(toSearch1);
				toSearch2 = freeActor(toSearch2);
			}

		free(movieName);

		for (int j = 0; j < actnr; ++j)
			free(actorNames[j]);
		free(actorNames);

	}

	G = reallocGraph(G, BST->size);

	if (strcmp(argv[1], "-c1") == 0)
	{
		FILE *g = fopen(argv[3], "w");

		if (!g)
		{
			perror(argv[3]);
			exit(1);
		}

		fprintf(g, "%d\n", numberOfProductions(G));

		fclose(g);
	}
	else if (strcmp(argv[1], "-c2") == 0)
	{
		FILE *g = fopen(argv[3], "w");

		if (!g)
		{
			perror(argv[3]);
			exit(1);
		}

		char *actorName1 = readActorLine(f);
		char *actorName2 = readActorLine(f);

		fprintf(g, "%d\n", degreeOfKinship(G, BST, actorName1, actorName2));

		free(actorName1);
		free(actorName2);
		fclose(g);
	}
	else if (strcmp(argv[1], "-c3") == 0)
	{
		FILE *g = fopen(argv[3], "w");

		if (!g)
		{
			perror(argv[3]);
			exit(1);
		}

		cutVertex(G, g);

		fclose(g);
	}
	else if (strcmp(argv[1], "-b") == 0)
	{
		FILE *g = fopen(argv[3], "w");

		if (!g)
		{
			perror(argv[3]);
			exit(1);
		}

		maximalClique(G, BST, g);

		fclose(g);
	}
	fclose(f);

	G = freeGraph(G);
	BST = freeActorBinaryTree(BST);
	return 0;
}
