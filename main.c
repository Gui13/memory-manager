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

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "bstree.h"

struct integer
{
	int n;
	char *english;
};

int my_cmp(const void *p1, const void *p2)
{
	return ((struct integer *)p1)->n-((struct integer *)p2)->n;
}

void my_twalk_action(void *data)
{
	printf("%d %s\n",((struct integer *)data)->n,
	       ((struct integer *)data)->english);
}

static int nbofdealloc = 0;

void free_integer(void * integer)
{
	nbofdealloc++;
	printf("Freeing %08x\n",integer);
	free(integer);
}


int main(void)
{
	struct bstree_node *bstree_root=NULL;
	/*struct integer i1={1,"one"};
	struct integer i2={2,"two"};
	struct integer i3={3,"three"};	
	struct integer i4={4,"four"};
	struct integer i5={5,"five"};
	struct integer lost={2,NULL};
	struct integer *needle;*/
	int k;
	
	printf("Sleep 2 s");
	sleep(2);
	printf("   OK\n");
	
	printf("%d deallocated for the moment\n",nbofdealloc);
	
	for(k=0; k< 150; k++)
	{
		int r = rand();
		struct integer *tmp = calloc(1,sizeof(struct integer)); 
		tmp->n = r;
		tmp->english = NULL;
		printf("Adding %d to tree\n",r);
		bstree_add(&bstree_root,tmp,my_cmp);
	}
	
	/*
	bstree_add(&bstree_root,&i3,my_cmp);
	bstree_add(&bstree_root,&i1,my_cmp);
	bstree_add(&bstree_root,&i5,my_cmp);
	bstree_add(&bstree_root,&i4,my_cmp);
	bstree_add(&bstree_root,&i2,my_cmp);*/
	
	bstree_walk(bstree_root,my_twalk_action);
	
	
	printf("Deletion test\n");
	
	bstree_free(bstree_root,free_integer);
	printf("Dealloced %d items\n",nbofdealloc);
	
	return 0;
}