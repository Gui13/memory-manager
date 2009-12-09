/*
 *  GPL
 *
 *  Written by Diogo Sousa aka orium
 *  Copyright (C) 2008 Diogo Sousa
 *  Enhanced by Guillaume BIENKOWSKI
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BSTREE_H_
#define BSTREE_H_


/** 
 * A bstree node may have:
 * 	- a parent (if not first node)
 *  - a right brother
 *  - a left brother
 *  - some data
 */
struct bstree_node
{
	void *data;
	
	struct bstree_node *left;
	struct bstree_node *right;
	struct bstree_node *parent;
};

/* Function to add a data in the tree: cmp is the comparison function */
extern int bstree_add(struct bstree_node **root,
					  void *data, 
					  int (*cmp)(const void *, const void *));

/* function that will walk the binary tree from the passed root to realize the action passed in parameter */
extern void bstree_walk(struct bstree_node *root,
						void (*action)(void *));

/* Function that will walk the tree from the provided root, but will delete the nodes after each passage.
 * The free_data function is the function to use to free the data stored in the leaf */
extern void bstree_free(struct bstree_node *root,
						void (*free_data)(void *));

/* Function that will search the needle from the root, using the compare function for comparison.
 * Returns the found data */
extern void *bstree_search(struct bstree_node *root,
						   void *needle,
						   int (*compare)(const void *, const void *));

/* Will wall the tree from the root, looking for the needle.
 * If found, will use the del function to free the data stored, and 
 * then delete the node */
extern int bstree_delete(struct bstree_node **root,
						 void *needle,
						 int (*cmp)(const void *, const void *),
						 void (*del)(void *));

#endif

