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

#ifndef BSTREE_H_
#define BSTREE_H_

struct bstree_node
{
	void *data;
	
	struct bstree_node *left;
	struct bstree_node *right;
	struct bstree_node *parent;
};

extern int bstree_add(struct bstree_node **,
					  void *, 
					  int (*)(const void *, const void *));
extern void bstree_walk(struct bstree_node *,
						void (*)(void *));
extern void bstree_free(struct bstree_node *,
						void (*)(void *));
extern void *bstree_search(struct bstree_node *,
						   void *,
						   int (*)(const void *, const void *));
extern int bstree_delete(struct bstree_node *root,
						 void *needle,
						 int (*cmp)(const void *, const void *),
						 void (*del)(void *));

#endif

