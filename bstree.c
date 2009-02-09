/*
 *  GPL
 *
 *  Written by Diogo Sousa aka orium
 *  Copyright (C) 2008 Diogo Sousa
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

/* TODO: 
 *       * Deletion
 *       * Rebalancing
 */

#include <stdlib.h>
#include <stdio.h>

#include "bstree.h"

static struct bstree_node *alloc_bstree_node(void);
static int bstree_insert(struct bstree_node *,
						 struct bstree_node *, 
						 int (*)(const void *, const void *));
static struct bstree_node *bstree_search_recursive(struct bstree_node *,
									 void *, 
									 int (*)(const void *, const void *));

static struct bstree_node *alloc_bstree_node(void)
{
	struct bstree_node *r;
	
	r=malloc(sizeof(*r));
	
	if (r == NULL)
		abort();
	
	return r;
}

static int bstree_insert(struct bstree_node *tree_node,
						 struct bstree_node *node, 
						 int (*cmp)(const void *, const void *))
{
	struct bstree_node **dn;
	int d;
	
	d=cmp(node->data,tree_node->data);
	
	if (!d)
		return -1;
	
	if (d > 0)
		dn=&tree_node->right;
	else
		dn=&tree_node->left;
	
	if (*dn == NULL)
	{
		*dn=node;
		node->left=NULL;
		node->right=NULL;
		node->parent = tree_node;
	}
	else
		return bstree_insert(*dn,node,cmp);
	
	return 0;
}

int bstree_add(struct bstree_node **root,
			   void *data, 
			   int (*cmp)(const void *, const void *))
{
	struct bstree_node *node;
	
	if (data == NULL) /* This may be used as a special value */
		return -1;
	
	node=alloc_bstree_node();
	node->data=data;
	
	if (*root == NULL)
	{
		*root=node;
		node->left=NULL;
		node->right=NULL;
		node->parent = NULL;
		return 0;
	}
	
	return bstree_insert(*root,node,cmp);
}

void bstree_walk(struct bstree_node *node,
				 void (*action)(void *))
{
	if (node == NULL)
		return;
	
	action(node->data);
	
	bstree_walk(node->left,action);
	bstree_walk(node->right,action);
}

void bstree_free(struct bstree_node *node,
				 void (*action)(void *))
{
	if (node == NULL)
		return;
	
	if (action != NULL)
		action(node->data);
	
	bstree_free(node->left,action);
	bstree_free(node->right,action);
	
	free(node);
}

static struct bstree_node *bstree_search_recursive(struct bstree_node *tree_node,
									 void *needle, 
									 int (*cmp)(const void *, const void *))
{
	struct bstree_node **dn;
	int d;
	
	d=cmp(needle,tree_node->data);
	
	if (!d)
		return tree_node;
	
	if (d > 0)
		dn=&tree_node->right;
	else
		dn=&tree_node->left;
	
	if (*dn != NULL)
		return bstree_search_recursive(*dn,needle,cmp);
	
	return NULL;
}

void *bstree_search(struct bstree_node *root,
					void *needle,
					int (*cmp)(const void *, const void *))
{
	struct bstree_node *found;
	if (root == NULL)
		return NULL;
	
	found = bstree_search_recursive(root,needle,cmp);
	if(found) 
		return found->data;
	else 
		return NULL;
}


int bstree_delete(struct bstree_node *root,
				  void *needle,
				  int (*cmp)(const void *, const void *),
				  void (*del)(void *))
{
	struct bstree_node *toDelete = NULL;
	
	if(!root || !cmp)
		return 0;
	
	toDelete = bstree_search_recursive(root, needle, cmp);
	if(toDelete)
	{
		struct bstree_node *parent = toDelete->parent;
		/* in case the guy is alone */
		if(!toDelete->left && !toDelete->right)
		{
			if(parent)
			{
				if(parent->left == toDelete)
					parent->left = NULL;
				else
					parent->right = NULL;
			}
			if(del)
				(del)(toDelete->data);
			free(toDelete);
		}
		else if(!toDelete->left)
		{
			if(parent)
			{
				if(parent->left == toDelete)
					parent->left = toDelete->right;
				else
					parent->right = toDelete->right;
			}
			if(del)
				(del)(toDelete->data);
			free(toDelete);
		}	
		else if(!toDelete->right)
		{
			if(parent)
			{
				if(parent->left == toDelete)
					parent->left = toDelete->left;
				else
					parent->right = toDelete->left;
			}
			if(del)
				(del)(toDelete->data);
			free(toDelete);
		}	
		else
		{
			/* the guy has 2 children : we don't delete it, we just find a 
			 replacement suitable to replace its value and delete this
			 "replacement" */
			struct bstree_node *successor = toDelete->left;
			struct bstree_node *p = successor;
			while(p->data)
			{
				if(cmp(successor->data,p->data) == 1)
					successor = p;
				p = p->left;
			}
			/* should have found a possible successor */
			toDelete->data = successor->data;
			if(bstree_delete(toDelete,successor,cmp,del))
				printf("2 children case: successful");
		}
		return 1;
	}
	else 
		return 0;
	
}

