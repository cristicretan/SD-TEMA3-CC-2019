/*
 * @Author: Cristi Cretan
 * @Date:   27-04-2019 19:30:54
 * @Last Modified by:   Cristi Cretan
 * @Last Modified time: 08-05-2019 16:57:45
 */

#include "binaryTree.h"

/**
 * Initialises a generic Binary tree with a given item and compare function.
 * @param item         [Pointer to the item]
 * @param compare_func [Pointer to the compare function]
 * @return             [Returns initialises Binary Tree]
 */
BinaryTree initBinaryTree(void *item, int (*compare_func) (const void*, const void*), BinaryTree parent)
{
	BinaryTree BST = (BinaryTree)malloc(sizeof(struct binaryTree));

	if (!BST)
	{
		fprintf(stderr, MEMERROR);
		exit(1);
	}

	BST->size = 1;
	BST->item = item;
	BST->parent = parent;
	BST->compare_func = compare_func;
	BST->left = NULL;
	BST->right = NULL;

	return BST;
}

/**
 * Inserts in given Binary Tree with a given compare function.
 * @param BST          [Binary Tree to insert into]
 * @param item         [Item to insert]
 * @param compare_func [Compare function]
 * @return             [Binary Tree with item inserted]
 */
BinaryTree insertInBinaryTree(BinaryTree BST, void *item, int (*compare_func) (const void*, const void*))
{
	if (!BST)
		return initBinaryTree(item, compare_func, NULL);

	if (BST->compare_func(BST->item, item) > 0)
	{
		if (!BST->left)
		{
			BST->left = initBinaryTree(item, compare_func, BST);

			for (BinaryTree iter = BST; iter; iter = iter->parent)
				iter->size++;

			return BST;
		}
		else
		{
			BST->left = insertInBinaryTree(BST->left, item, compare_func);
			return BST;
		}
	}
	else if (BST->compare_func(BST->item, item) < 0)
	{
		if (!BST->right)
		{
			BST->right = initBinaryTree(item, compare_func, BST);

			for (BinaryTree iter = BST; iter; iter = iter->parent)
				iter->size++;

			return BST;
		}
		else
		{
			BST->right = insertInBinaryTree(BST->right, item, compare_func);
			return BST;
		}
	}

	return BST;
}

/**
 * Returns the item if the binary tree given contains it, NULL otherwise.
 * @param  BST  [Binary Tree to search in]
 * @param  item [Item to search for]
 * @return      [NULL if it's not found, the item if it's found]
 */
void *containsInBinaryTree(BinaryTree BST, void *item)
{
	if (!BST)
		return NULL;

	if (BST->compare_func(BST->item, item) == 0)
		return BST->item;

	if (BST->compare_func(BST->item, item) > 0)
		return containsInBinaryTree(BST->left, item);

	return containsInBinaryTree(BST->right, item);
}

/**
 * Returns the minimum element from the binary search tree.
 * @param  BST [The binary search tree]
 * @return     [The minimum element if it has one, NULL otherwise]
 */
void *minimumBST(BinaryTree BST)
{
	if (!BST->left)
		return BST->item;
	else
		return minimumBST(BST->left);

	return NULL;
}

/**
 * Deletes item from binary tree.
 * @param  BST  [Binary Tree to delete from]
 * @param  item [Item to delete]
 * @return      [The binary tree without the item that has to be deleted]
 */
BinaryTree deleteInBinaryTree(BinaryTree BST, void *item)
{
	if (!BST)
		return NULL;

	if (BST->compare_func(BST->item, item) > 0)
		BST->left = deleteInBinaryTree(BST->left, item);
	else if (BST->compare_func(BST->item, item) < 0)
		BST->right = deleteInBinaryTree(BST->right, item);
	else
	{
		if (!BST->left && !BST->right)
		{
			void *tmp = minimumBST(BST->right);
			free(BST->item);
			BST->item = tmp;
			BST->right = deleteInBinaryTree(BST->right, item);
		}
		else
		{
			BinaryTree toDEL = BST;

			for (BinaryTree iter = BST; iter; iter = iter->parent)
				iter->size--;

			if (BST->left) BST = BST->left;
			else BST = BST->right;

			free(toDEL->item);
			free(toDEL);
		}
	}

	return BST;
}

/**
 * Clones a binary search tree in a new one and returns the new one.
 * @param  BST [Binary search tree to be cloned]
 * @return     [Cloned binary search tree]
 */
BinaryTree copyBST(BinaryTree BST)
{
	if (!BST)
		return NULL;

	BinaryTree new = initBinaryTree(BST->item, BST->compare_func, BST->parent);

	new->left = copyBST(BST->left);
	new->right = copyBST(BST->right);

	return new;
}

/**
 * Returns the size of the binary search tree.
 * @param  BST [Binary search tree]
 * @return     [The number of items in the binary search tree]
 */
int checkBSTsize(BinaryTree BST)
{
	if (!BST)
		return 0;

	return (checkBSTsize(BST->left) + 1 + checkBSTsize(BST->right));
}

/**
 * Frees an binary search tree that contains actor structure.
 * @param  BST [Binary search tree]
 * @return     [NULL]
 */
BinaryTree freeActorBinaryTree(BinaryTree BST)
{
	if (!BST)
		return NULL;

	freeActorBinaryTree(BST->left);
	freeActorBinaryTree(BST->right);

	Actor toFree = (Actor)BST->item;

	toFree = freeActor(toFree);
	free(BST);

	return NULL;
}
