#include "list.h"
#include <assert.h>
#include <stdio.h>

void SlistCreateTest();
void SlistInsertBeforeTest();
void SlistBeginTest();
void SlistEndTest();
void SlistNextTest();
void SlistRemoveTest(); 
void SlistSetDataTest();
void SlistSizeTest();
void SlistIsEmptyTest();
void SlistIterIsEqualTest();
void SlistForEachTest();
void SlistFindTest();
void SlistAppendTest();
/* help functions for find and foreach tests */
int SumList(void* num , void* result);
int MultList(void* num , void* result);
int FindNumInList(const void* num , void* value);


int main()
{
	SlistCreateTest();
	SlistInsertBeforeTest();
	SlistBeginTest();
	SlistEndTest();
	SlistNextTest();
	SlistRemoveTest(); 
	SlistSetDataTest();
	SlistSizeTest();
	SlistIsEmptyTest();
	SlistIterIsEqualTest();
	SlistForEachTest();
	SlistFindTest();
	SlistAppendTest();
	printf("\n\n->->->->->->->->-> success!!! <-<-<-<-<-<-<-<-<-<\n\n\n");
	
	return 0;
}


void SlistCreateTest()
{
	slist_ty *slist = SlistCreate();
	assert(NULL != slist);
	SlistDestroy(slist);
}


void SlistInsertBeforeTest()
{
	int a = 12;
	int b = 11;
	slist_ty *slist = SlistCreate();
	slist_iterator_ty iterator = SlistBegin(slist);
    SlistInsertBefore(iterator , (void*)&a);
	iterator = SlistBegin(slist);
    assert(*((int*)SlistGetData(iterator)) == 12);
    SlistInsertBefore(iterator , (void*)&b);
    iterator = SlistBegin(slist);
	assert(*((int*)SlistGetData(iterator)) == 11);
    SlistDestroy(slist);
}

void SlistBeginTest()
{
	int a = 12;
	int b = 11;
	slist_ty *slist = SlistCreate();
	assert(SlistGetData(SlistBegin(slist)) == NULL);
	
    SlistInsertBefore(SlistBegin(slist) , (void*)&a);
    assert(*((int*)SlistGetData(SlistBegin(slist))) == 12);
    SlistInsertBefore(SlistBegin(slist) , (void*)&b);
    assert(*((int*)SlistGetData(SlistBegin(slist))) == 11);
    SlistDestroy(slist);
}

void SlistEndTest()
{
	char a = 2;
	char b = 3;
	slist_ty *slist = SlistCreate();
	assert(SlistGetData(SlistEnd(slist)) == NULL);
	
    SlistInsertBefore(SlistEnd(slist) , (void*)&a);
    assert(*((char*)SlistGetData(SlistBegin(slist))) == 2);
    SlistInsertBefore(SlistEnd(slist) , (void*)&b);
    assert(*((char*)SlistGetData(SlistBegin(slist))) == 2);
    SlistDestroy(slist);	
}


void SlistNextTest()
{
	slist_ty *slist = SlistCreate();
	slist_iterator_ty iterator = SlistBegin(slist);
	int i = 0;
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist) , (void*)(arr + i));
	}
	for (i = 0 ; i < 5 ; ++i)
	{
		iterator = SlistNext(iterator);
	}
	assert(*((int*)SlistGetData(iterator)) == 5);
	SlistDestroy(slist);	
}


void SlistRemoveTest()
{
	slist_ty *slist = SlistCreate();
	slist_iterator_ty iterator = NULL;
	int i = 0;
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	
	assert(SlistRemove(SlistBegin(slist)) == SlistBegin(slist));
	
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist) , (void*)(arr + i));
	}
	
	iterator = SlistBegin(slist);
	
	for (i = 0 ; i < 5 ; ++i)
	{
		iterator = SlistNext(iterator);
	}	
	
	iterator = SlistRemove(iterator);
	assert(*((int*)SlistGetData(iterator)) == 4);
	SlistDestroy(slist);			
} 



void SlistSetDataTest()
{
	slist_ty *slist = SlistCreate();
	slist_iterator_ty iterator = NULL;
	int i = 0;
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist) , (void*)(arr + i));
	}
	
	iterator = SlistBegin(slist);
	
	for (i = 0 ; i < 5 ; ++i)
	{
		iterator = SlistNext(iterator);
	}	
	
	i = 25;
	SlistSetData(iterator , (void*)&i);
	assert(*((int*)SlistGetData(iterator)) == 25);
	SlistDestroy(slist);
}



void SlistSizeTest()
{
	slist_ty *slist = SlistCreate();
	int i = 0;
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist) , (void*)(arr + i));
	}
	
	assert(SlistSize(slist) == 10);
    SlistRemove(SlistBegin(slist));
	assert(SlistSize(slist) == 9);
	SlistDestroy(slist);
}


void SlistIsEmptyTest()
{
	double x = 3.68;
	slist_ty *slist = SlistCreate();
	assert(SlistIsEmpty(slist) == 1);
	SlistInsertBefore(SlistBegin(slist) , (void*)&x);
	assert(SlistIsEmpty(slist) == 0);
	SlistDestroy(slist);
}


void SlistIterIsEqualTest()
{
	double x = 3.68;
	slist_ty *slist = SlistCreate();
	assert(SlistIterIsEqual(SlistBegin(slist) , SlistEnd(slist)) == 1);
	SlistInsertBefore(SlistBegin(slist) , (void*)&x);
	assert(SlistIterIsEqual(SlistBegin(slist) , SlistEnd(slist)) == 0);
	SlistDestroy(slist);
}


void SlistForEachTest()
{
	slist_ty *slist = SlistCreate();
	action_ty action_func1 = &SumList;
	action_ty action_func2 = &MultList;
	int i = 0;
	int sum_of_list = 0;
	int mult_of_list = 1;

	int arr[10] = {2,2,2,2,2,2,2,2,2,2};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist) , (void*)(arr + i));
	}
	
	SlistForEach(SlistBegin(slist) , SlistEnd(slist) , action_func1 ,  (void*)&sum_of_list);
	assert(sum_of_list == 20);
	
	SlistForEach(SlistBegin(slist) , SlistEnd(slist) , action_func2 ,  (void*)&mult_of_list);
	assert(mult_of_list == 1024);
	SlistDestroy(slist);	
}


void SlistFindTest()
{
	slist_ty *slist = SlistCreate();
	is_match_ty match_func = &FindNumInList;
	slist_iterator_ty iterator = NULL;
	int test_value = 4;
	int i = 0;

	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist) , (void*)(arr + i));
	}
	
	iterator = SlistFind(SlistBegin(slist) , SlistEnd(slist) , match_func ,  (void*)&test_value);
	assert(*((int*)SlistGetData(iterator)) == 4);
	
	test_value = 11;
	iterator = SlistFind(SlistBegin(slist) , SlistEnd(slist) , match_func ,  (void*)&test_value);
	assert(*((int*)SlistGetData(iterator)) == 1);

	SlistDestroy(slist);	
}

void SlistAppendTest()
{
	slist_ty *slist1 = SlistCreate();
	slist_ty *slist2 = SlistCreate();
	slist_ty *slist3 = SlistCreate();
	slist_ty *slist4 = SlistCreate();
	int i = 0;
	slist_iterator_ty iterator = NULL;

	int arr1[10] = {10,9,8,7,6,5,4,3,2,1};
	int arr2[10] = {20,19,18,17,16,15,14,13,12,11};
	
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist1) , (void*)(arr1 + i));
	}	
	
	for (i = 0 ; i < 10 ; ++i)
	{
		SlistInsertBefore(SlistBegin(slist2) , (void*)(arr2 + i));
	}	
	
	SlistAppend(slist1 , slist2);
	iterator = SlistBegin(slist1);
	
	for (i = 1 ; i < 13 ; ++i)
	{
		iterator = SlistNext(iterator);
	}
	
	assert(*((int*)SlistGetData(iterator)) == 13);

	SlistInsertBefore(SlistBegin(slist4) , (void*)(arr1 + 4));
	SlistAppend(slist3 , slist4);
	assert(*((int*)SlistGetData(SlistBegin(slist3))) == 6);

	SlistDestroy(slist1);
	SlistDestroy(slist3);
		
}


int SumList(void* num , void* result)
{
	*((int*)result) += *((int*)num);
	return 0;
}

int MultList(void* num , void* result)
{
	*((int*)result) *= *((int*)num);
	return 0;
}

int FindNumInList(const void* num , void* value)
{
	return (*((int*)num) == *((int*)value)) ? 1 : 0;
}




