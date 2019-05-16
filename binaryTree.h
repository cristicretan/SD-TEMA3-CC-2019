/*
 * @Author: Cristi Cretan
 * @Date:   27-04-2019 19:31:38
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 07-05-2019 22:03:26
 */
#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__

#include "helpers.h"
#include "list.h"

typedef struct binaryTree
{
	int size;
	void *item;
	int (*compare_func)(const void*, const void*);
	struct binaryTree *parent;
	struct binaryTree *left;
	struct binaryTree *right;
} *BinaryTree;

BinaryTree initBinaryTree(void *item, int (*compare_func) (const void*, const void*), BinaryTree parent);
BinaryTree insertInBinaryTree(BinaryTree BST, void *item, int (*compare_func) (const void*, const void*));
void *containsInBinaryTree(BinaryTree BST, void *item);
void *minimumBST(BinaryTree BST);
BinaryTree deleteInBinaryTree(BinaryTree BST, void *item);
BinaryTree copyBST(BinaryTree BST);
int checkBSTsize(BinaryTree BST);
BinaryTree freeActorBinaryTree(BinaryTree BST);
#endif
