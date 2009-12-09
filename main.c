#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "memory_manager.h"

/* For testing */
int main(void)
{

	char *tmp = NULL;
	int k=0;
	char *string = "Blablastring";
	int length = strlen(string);

	for(k=0; k<1500;k++)
	{
		tmp = MM_CALLOC(length+1,sizeof(char));
		strcpy(tmp,string);
		tmp[length] = '\0';
		if(k%3 == 0)
		{
			MM_FREE(tmp);
		}
		if(k%100 == 0)
			printf("%d\n", k);
	}

	mm_stats();

	return 0;
}
