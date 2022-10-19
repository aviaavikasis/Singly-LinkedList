/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Gal Cohen                               *
 * 10/06/2022                                        *
 * Description : imlementation of single             *
 * linkedlist                                        *
 *                                                   *
 *****************************************************/

#include "slist.h" 
#include <assert.h>  /* assert */
#include <stdlib.h>  /* malloc */

typedef struct node {
   void *data;
   struct node *next;
}node_ty;

struct slist 
{
   node_ty *head;
   node_ty *tail;
};


slist_ty* SlistCreate(void)
{
	slist_ty *slist = (slist_ty*)malloc(sizeof(slist_ty));
	if(NULL == slist)
	{
		return NULL;
	}
	slist -> head = (node_ty*)malloc(sizeof(node_ty));
	if(NULL == slist -> head)
	{
		return NULL;
	}
	slist -> tail = slist -> head;
	assert(NULL != slist -> head);
	slist -> head -> next = NULL;
	slist -> head -> data = slist;
		
	return slist;
}


slist_iterator_ty SlistInsertBefore(slist_iterator_ty position, void *data)
{
	slist_iterator_ty new_node = NULL;
	assert(NULL != position);
	assert(NULL != data);
	new_node = (slist_iterator_ty)malloc(sizeof(node_ty));
	if(NULL == new_node)
	{
		return NULL;
	}
	new_node -> data = position -> data;
	position -> data = data;
	new_node -> next = position -> next;
	position -> next = new_node;
	
	if (NULL == new_node -> next)
	{
		((slist_ty*)(new_node -> data)) -> tail = new_node;
	}

	return new_node;
}


slist_iterator_ty SlistRemove(slist_iterator_ty iterator)  
{
	assert(NULL != iterator);
	if(NULL != iterator -> next)
	{
		slist_iterator_ty free_ptr = iterator -> next;
		iterator -> data = iterator -> next -> data;
		iterator -> next = iterator -> next -> next;
		free(free_ptr);
		if(NULL == iterator -> next)
		{
			((slist_ty*)(iterator -> data)) -> tail = iterator;
		}
	}
	return iterator;
}


void SlistSetData(slist_iterator_ty iterator, void *data)
{
	assert(NULL != iterator);
	assert(NULL != data);
	if(NULL != iterator -> next)
	{
		iterator -> data = data;
	}
}


void *SlistGetData(const slist_iterator_ty iterator)
{
	assert(NULL != iterator);
	return (NULL != iterator -> next) ? iterator -> data : NULL;
}


size_t SlistSize(const slist_ty *slist)
{
	size_t counter = 0;
	node_ty *run_ptr = slist -> head;
	assert(NULL != slist);
	while(slist != run_ptr -> data)
	{
		++counter;
		run_ptr = run_ptr -> next; 
	}
	return counter;
}


int SlistIsEmpty(const slist_ty *slist)
{
	assert(NULL != slist);
	return (slist -> head == slist -> tail);
}


void SlistDestroy(slist_ty *slist)
{
	node_ty *free_ptr = slist -> head;
	node_ty *hold_next_node_ptr = slist -> head;
	assert(NULL != slist);
	
	while( NULL != free_ptr )
	{
		hold_next_node_ptr = free_ptr -> next;
		free(free_ptr);
		free_ptr = hold_next_node_ptr;
	}
	
	free(slist);
}


slist_iterator_ty SlistBegin(const slist_ty *slist)
{
	assert(NULL != slist);
	return slist -> head;
}


slist_iterator_ty SlistEnd(const slist_ty *slist)
{
	assert(NULL != slist);
	return slist -> tail;
}


slist_iterator_ty SlistNext(slist_iterator_ty iterator)
{
	assert(NULL != iterator);
	return iterator -> next;
}


int SlistIterIsEqual(const slist_iterator_ty iterator1, const slist_iterator_ty iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	return (iterator1 == iterator2);
}


int SlistForEach(slist_iterator_ty from, slist_iterator_ty to, action_ty action_func, void *param)
{
	int return_function = 0;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action_func);
	assert(NULL != param);
	
	while(!SlistIterIsEqual(from , to))
	{
		return_function = action_func(from -> data , param);
		if(return_function != 0)
		{
			return return_function;
		}
		from = from -> next;	
	}
	return return_function;
}


slist_iterator_ty SlistFind(slist_iterator_ty from, slist_iterator_ty to, is_match_ty match_func, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	assert(NULL != param);
	
	while(!SlistIterIsEqual(from -> next, to) && match_func(from -> data , param) != 1)
	{
		from = from -> next;	
	}	
	return from;
}

void SlistAppend(slist_ty *dest, slist_ty *src)
{	
	node_ty *src_begin_ptr = SlistBegin(src);
	node_ty *dest_end_ptr = SlistEnd(dest);
	
	assert(NULL != dest);
	assert(NULL != src);
	
	SlistEnd(src) -> data = dest;
	dest -> tail = SlistEnd(src);
	dest_end_ptr -> data = src_begin_ptr -> data;
	dest_end_ptr -> next = src_begin_ptr -> next;
	free(src_begin_ptr);
}











