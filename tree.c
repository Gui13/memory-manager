#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

/*
 Node Related Functions: node_new, node_find, node_add
 */

/* allocate a new node */
node *node_new(void *data, node *parent)
{
	node *new = malloc(sizeof(node));
	if(new)
	{
		new->data = data;
		new->left = NULL;
		new->right = NULL;
		new->parent = parent;
		return new;
	}
	else return NULL;
}

/* finds a given node key into the tree */
node *node_find(node *this, void *toFind, tree_compare_func compare)
{
	int difference = 0;
	if(!this || !compare)
		return NULL;
	
	difference = (compare)(this->data,toFind);
	
	if( difference == BIGGER) /* toFind is BIGGER than data */
		return node_find(this->right,toFind,compare);
	else if( difference == SMALLER)
		return node_find(this->left,toFind,compare);
	else
		return this;
}
/* inserts a node in a tree. */
int	node_insert(node *this, void *data, node *parent, tree_compare_func compare)
{
	int difference = 0;
	node **tmp;
	
	if(!compare)
		return -1;
	if(!this)
	{
		this = node_new(data, parent);
	return 0;
	}
	
	difference = (compare)(this->data,data);

	
	if(difference == EQUAL)
		return -1;
	if(difference == BIGGER)
		tmp = &(this->right);
	else 
		tmp = &(this->left);
	
	if(*tmp == NULL)
		*tmp = node_new(data, parent);
	else 
		return node_insert(*tmp,data,this,compare);
	
	return 0;
}

int node_delete(node *this, void *data, tree_compare_func compare, tree_delete_data del_func, void *pvdata)
{
	node *toDelete = NULL;

	if(!this || !compare || !data)
		return 0;

	toDelete = node_find(this, data, compare);
	if(toDelete)
	{
		node *parent = toDelete->parent;
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
			(del_func)(pvdata,toDelete->data);
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
			(del_func)(pvdata,toDelete->data);
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
			(del_func)(pvdata,toDelete->data);
			free(toDelete);
		}	
		else
		{
			/* the guy has 2 children : we don't delete it, we just find a 
			 replacement suitable to replace its value and delete this
			 "replacement" */
			node *successor = toDelete->left;
			node *p = successor;
			while(p->data)
			{
				if(compare(successor->data,p->data) == BIGGER)
					successor = p;
				p = p->left;
			}
			/* should have found a possible successor */
			toDelete->data = successor->data;
			if(node_delete(toDelete,successor,compare,del_func,pvdata))
				printf("2 children case: successful");
		}
		return 1;
	}
	else 
		return 0;
}

void node_walk_tree(node *this, tree_walk_func walk_func, void *pvdata)
{
	if(!this || !walk_func)
		return;
	
	node_walk_tree(this->left,walk_func,pvdata);
	(walk_func)(pvdata,this->data);
	node_walk_tree(this->right,walk_func,pvdata);
	
}


