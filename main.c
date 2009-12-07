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
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "memory_manager.h"


int main(void)
{

	char *tmp = NULL;
	int k=0;
	char *string = "Blablastring";
	int length = strlen(string);

	for(k=0; k<15;k++)
	{
		tmp = MM_CALLOC(length+1,sizeof(char));
		strcpy(tmp,string);
		tmp[length] = '\0';
		if(k%3 == 0)
			MM_FREE(tmp);
	}

	mm_stats();

	return 0;
}
