#ifndef __ILRD_OL127_128_SLINKED_LIST_H__
#define __ILRD_OL127_128_SLINKED_LIST_H__

#include <stddef.h> /* size_t */

 
typedef struct slist slist_ty;
typedef struct node *slist_iterator_ty;
typedef int (*is_match_ty)(const void *data, void *params);
typedef int (*action_ty)(void *data, void *params);

slist_ty *SlistCreate(void);

void SlistDestroy(slist_ty *slist); 
/* insert data before position , and return iterator to node that hold the source value of position */
slist_iterator_ty SlistInsertBefore(slist_iterator_ty position, void *data); 
/* return iterator to head of list */
slist_iterator_ty SlistBegin(const slist_ty *slist);
/* return iterator to the next position after end of list */
slist_iterator_ty SlistEnd(const slist_ty *slist);
/* return iterator to next value in list */
slist_iterator_ty SlistNext(const slist_iterator_ty iterator);
/* remove value that point by iterator and return iterator to next value */
slist_iterator_ty SlistRemove(slist_iterator_ty iterator); 

void SlistSetData(slist_iterator_ty iterator, void *data);

void *SlistGetData(const slist_iterator_ty iterator);

size_t SlistSize(const slist_ty *slist);

int SlistIsEmpty(const slist_ty *slist);

int SlistIterIsEqual(const slist_iterator_ty iterator1, const slist_iterator_ty iterator2);
/* execute given function for each element in list , from from pointer to to pointer , not include to */
int SlistForEach(slist_iterator_ty from, slist_iterator_ty to, action_ty action_func, void *param); 
 
slist_iterator_ty SlistFind(slist_iterator_ty from, slist_iterator_ty to, is_match_ty match_func, void *param);

void SlistAppend(slist_ty *dest, slist_ty *src);

slist_iterator_ty SlistSlice(slist_iterator_ty where, slist_iterator_ty from, slist_iterator_ty to);


#endif /* __ILRD_OL127_128_SLINKED_LIST_H__ */
