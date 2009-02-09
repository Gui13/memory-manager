#ifndef TREE_H_
#define TREE_H_

#define FALSE 0
#define TRUE !(FALSE)


enum {
	SMALLER = -1,
	EQUAL = 0,
	BIGGER = 1
};

/* should return BIGGER if data2 is BIGGER than data 1 */
typedef int (*tree_compare_func)(void * data1, void *data2);

/* function called when deleting a node, to free any eventual 
 data associated with a node*/
typedef void (*tree_delete_data)(void *pvdata, void *data);

/* function called when walking the tree */
typedef void (*tree_walk_func)(void *pvdata, void *data);

typedef struct _node node;

struct _node
{
	void *data;
	
	node *parent;
	node *left;
	node *right;
};

node	*node_new(void *data, node *parent);
int		node_insert(node* insertnode, void *data, node *parent, tree_compare_func compare);
node	*node_find(node *tree, void *toFind, tree_compare_func compare);
int		node_remove(node *tree, void *toRemove, tree_compare_func compare, tree_delete_data del_func, void *pvdata);
void	node_walk_tree(node *tree, tree_walk_func walk_func, void *pvdata); 

#endif