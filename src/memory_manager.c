/*
 *  memory_maanger.c
 *  MemoryManager
 *
 *  Created by Guillaume BIENKOWSKI on 11/02/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include "memory_manager.h"
#include "bstree.h"


struct _memory_allocation{
	char *file;
	int  line;
	
	void *pt;
	int size;
};

static struct bstree_node *mm_root = NULL;


/* Callback functions */
static int mm_compare(const void *data1, const void *data2)
{
	memory_allocation *d1 = (memory_allocation *)data1;
	memory_allocation *d2 = (memory_allocation *)data2;
	
	if(d1 || d2)
	{
		if(d2->pt > d1->pt)
			return 1;
		else if (d2->pt < d1->pt)
			return -1;
	}
	
	return 0;
}
static void mm_free_struct(void *data)
{
	if(data)
	{
		memory_allocation *toFree = (memory_allocation *)data;
		if(toFree->file)
			free(toFree->file);
		
		free(toFree);
	}
}

static int mm_nbofallocs=0;
static int mm_sizeofallocs=0;

static void mm_print_func( void *data)
{
	memory_allocation *alloc = (memory_allocation *)data;
	if(alloc)
	{
		printf("@0x%08x:\t%s:%d\t:\t%d bytes\n",
			   alloc->pt,
			   alloc->file,
			   alloc->line,
			   alloc->size);
		mm_nbofallocs++;
		mm_sizeofallocs+=alloc->size;
	}
}

/* the real functions */

void *mm_malloc(size_t sz, char *file, int line)
{
	void *data = malloc(sz);
	if(data)
	{
		memory_allocation *allocation = malloc(sizeof(memory_allocation));
		if(allocation)
		{
			allocation->pt = data;
			allocation->file = file;
			allocation->line = line;
			allocation->size = sz;
			bstree_add(&mm_root, (void *)allocation, mm_compare);
			printf("[MM] Alloc'ed %d bytes at %s:%d\n",allocation->size,allocation->file,allocation->line);
		}
		else 
			printf("[MM] Allocation for handling structure failed\n");
		return data;
	}
	
	return NULL;
}


void *mm_calloc(size_t times, size_t sz, char *file, int line)
{
	void *data = calloc(times,sz);
	if(data)
	{
		memory_allocation *allocation = malloc(sizeof(memory_allocation));
		if(allocation)
		{
			allocation->pt = data;
			allocation->file = file;
			allocation->line = line;
			allocation->size = sz*times;
			bstree_add(&mm_root, (void *)allocation, mm_compare);
			printf("[MM] Alloc'ed %d bytes at %s:%d\n",allocation->size,allocation->file,allocation->line);
		}
		else 
			printf("[MM] Allocation for handling structure failed\n");
		return data;
	}
	
	return NULL;
}

void mm_free( void *pt)
{
	if(pt)
	{
		memory_allocation toSearch;
		toSearch.pt = pt;
		bstree_delete(&mm_root, &toSearch, mm_compare, mm_free_struct);
		free(pt);
	}
	
	return;
}

void mm_stats()
{
	mm_nbofallocs=0;
	mm_sizeofallocs=0;
	printf("################################################\n");
	printf("################ MEMORY MANAGER ################\n");
	printf("################################################\n");
	printf("################# Allocations: #################\n");	
	printf("################################################\n");

	bstree_walk(mm_root, mm_print_func);
	
	printf("################################################\n");
	printf("#       Nb. of allocs: %8d                #\n",mm_nbofallocs);
	printf("#          Total size: %8d bytes          #\n",mm_sizeofallocs);
	printf("################################################\n");

}



