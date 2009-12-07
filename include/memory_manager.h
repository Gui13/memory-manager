/*
 *  memory_manager.h
 *  MemoryManager
 *
 *  Created by Guillaume BIENKOWSKI on 11/02/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _MEMORY_MANAGER_H
#define _MEMORY_MANAGER_H

#include <stdlib.h>

typedef struct _memory_allocation memory_allocation;

#define MM_MALLOC(a) mm_malloc((a),__FILE__,__LINE__)
#define MM_CALLOC(a,b) mm_calloc((a),(b),__FILE__,__LINE__)
#define MM_FREE(a) mm_free((a))



extern void *mm_malloc(size_t sz, char *file, int line);
extern void *mm_calloc(size_t times, size_t sz, char *file, int line);
extern void mm_free( void *pt);
extern void mm_stats(void);


#endif
