/********************************************************************************
 * Linkedlist_test.c		                                                    *
 *                                                                              *
 * Implements tests for linkedlist'S API                                        *
 *													                            *
 * Author: Guy Rosen								                            *
 * Reviewer: REVIEWER                                                           *
 * DATE: 10/08/2020        					    	                            *
 ********************************************************************************/
#include <stdio.h>      /* printf       */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include "linkedlist.h" /* library      */
#include "utils.h"      /* RUN_TEST     */

 /*******************************************************************************/
 /***********************   MACROS AND TYPES DEFINITIONS   **********************/
 /*******************************************************************************/

 /*******************************************************************************/
 /*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
 /*******************************************************************************/

 /*******************************************************************************/
 /***********************   TEST FUNCTION DECLARATIONS   ************************/
 /*******************************************************************************/
int LinkedlistCreateTest(void);
int LinkedlistPushPopTest(void);
int LinkedListAddBeforeRemoveTest(void);
int LinkedlistCutAndConcateTest(void);
int LinkedlistForEachAndFindTest(void);
/*
int Linkedlist_FUNC_linkedlist6_Test(void);
int Linkedlist_FUNC_linkedlist7_Test(void);
int Linkedlist_FUNC_linkedlist8_Test(void);
int Linkedlist_FUNC_linkedlist9_Test(void);
int Linkedlist_FUNC_linkedlist10_Test(void);
int Linkedlist_FUNC_linkedlist11_Test(void);
int Linkedlist_FUNC_linkedlist12_Test(void);
int Linkedlist_FUNC_linkedlist13_Test(void);
int Linkedlist_FUNC_linkedlist14_Test(void);
*/
/*******************************************************************************/
/*******************   END OF TEST FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DECLARATIONS   **********************/
/*******************************************************************************/
void _ListPrintInt(list_t *lst);
list_t *_initSampleList();
int IntCmp(const void *data, const void *list_data, void *param);
int IntActFnc(void *list_data, void *param);
/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/*****************   GLOBAL AND STATIC VARIABLES DEFINITIONS   *****************/
/*******************************************************************************/
int nums[] ={ 5, 10, 20 };
/*******************************************************************************/
/*************   END OF GLOBAL AND STATIC VARIABLES DEFINITIONS   **************/
/*******************************************************************************/

/*******************************************************************************/
int main(void)
{
    RUN_TEST(LinkedlistCreateTest);
    RUN_TEST(LinkedlistPushPopTest);
    RUN_TEST(LinkedListAddBeforeRemoveTest);
    RUN_TEST(LinkedlistCutAndConcateTest);
    RUN_TEST(LinkedlistForEachAndFindTest);
    return EXIT_SUCCESS;
    /*
        RUN_TEST(Linkedlist_FUNC_linkedlist6_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist7_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist8_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist9_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist10_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist11_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist12_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist13_TEST);
        RUN_TEST(Linkedlist_FUNC_linkedlist14_TEST);
    */
}
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DEFINITIONS   *************************/
/*******************************************************************************/
int LinkedlistCreateTest(void)
{
    list_t *lst = ListCreate();
    if (lst == NULL || !ListIsEmpty(lst))
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }
    if (ListSize(lst))
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }
    if (ListBegin(lst) != ListTail(lst))
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }
    ListDestroy(lst);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int LinkedlistPushPopTest(void)
{
    list_t *lst = NULL;
    l_iter_t *runner = NULL;
    int i=0;

    lst = _initSampleList();
    if (NULL == lst)
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }

    if (ListSize(lst)!=3)
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }

    runner = ListBegin(lst);

    for (i = 2; i>=0; --i)
    {
        int data;
        data = *(int *)ListGetData(runner);
        if (data != nums[i])
        {
            ListDestroy(lst);
            return EXIT_FAILURE;
        }
        runner = ListNext(runner);
    }

    ListPopFront(lst);
    if (ListSize(lst)!=2)
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }

    runner = ListBegin(lst);

    for (i = 1; i>=0; --i)
    {
        int data;
        data = *(int *)ListGetData(runner);
        if (data != nums[i])
        {
            ListDestroy(lst);
            return EXIT_FAILURE;
        }
        runner = ListNext(runner);
    }

    ListPopBack(lst);
    if (ListSize(lst)!=1)
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }

    if (nums[1] != *(int *)ListGetData(ListBegin(lst)))
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }

    ListDestroy(lst);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int LinkedListAddBeforeRemoveTest(void)
{
    list_t *lst = NULL;
    l_iter_t *runner = NULL, *tail = NULL;
    int i=0;

    lst = _initSampleList();
    if (NULL == lst)
        return EXIT_FAILURE;

    runner = ListNext(ListBegin(lst));
    ListRemove(runner);
    if (ListSize(lst)!= 2)
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }
    runner = ListBegin(lst);
    if (*(int *)ListGetData(runner) != nums[2])
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }
    if (*(int *)ListGetData(ListNext(runner)) != nums[0])
    {
        ListDestroy(lst);
        return EXIT_FAILURE;
    }
    ListAddBefore(ListNext(runner), &nums[1]);

    runner = ListBegin(lst);
    tail = ListTail(lst);
    i = 3;
    while (!ListSameIter(runner, tail))
    {
        --i;
        if (i <0 || *(int*)ListGetData(runner) != nums[i])
        {
            ListDestroy(lst);
            return EXIT_FAILURE;
        }
        runner = ListNext(runner);
    }
    ListDestroy(lst);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int LinkedlistCutAndConcateTest(void)
{
    list_t *lst1 = NULL, *lst2 = NULL;
    l_iter_t *runner = NULL, *tail = NULL;
    int i = 0, bm_arr[6] ={ 20, 20, 10, 5, 10, 5 };
    lst1 = _initSampleList();
    lst2 = _initSampleList();
    runner = ListBegin(lst1);
    ListCutAndConcate(runner, ListBegin(lst2), ListTail(lst2));
    tail = ListTail(lst1);
    _ListPrintInt(lst1);
    while (!ListSameIter(runner, tail))
    {
        if (i>5 || *(int*)ListGetData(runner)!=bm_arr[i])
        {
            ListDestroy(lst1);
            ListDestroy(lst2);
            return EXIT_FAILURE;
        }
        ++i;
        runner = ListNext(runner);
    }
    ListDestroy(lst1);
    ListDestroy(lst2);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int LinkedlistForEachAndFindTest(void)
{
    list_t *lst = NULL;
    l_iter_t *runner = NULL, *tail = NULL, *temp = NULL;
    int i=0, test_Val = 1, bm_arr[] ={ 5, 10, 20 };

    lst = _initSampleList();
    if (NULL == lst)
        return EXIT_FAILURE;
    runner = ListBegin(lst);
    tail = ListTail(lst);
    i = 3;
    while (!ListSameIter(runner, tail))
    {
        --i;
        temp = ListFind(ListBegin(lst), tail, IntCmp, NULL, &nums[i]);
        if (temp == NULL || i < 0 || *(int*)ListGetData(runner) != nums[i])
        {
            ListDestroy(lst);
            return EXIT_FAILURE;
        }
        runner = ListNext(runner);
    }
    temp = ListFind(ListBegin(lst), tail, IntCmp, NULL, &test_Val);
    if (NULL != temp)
        return EXIT_FAILURE;

    runner = ListBegin(lst);
    ListForEach(runner, tail, IntActFnc, &test_Val);
    i = 3;
    while (!ListSameIter(runner, tail))
    {
        --i;
        if (i < 0)
        {
            ListDestroy(lst);
            return EXIT_FAILURE;
        }
        temp = ListFind(ListBegin(lst), tail, IntCmp, NULL, &bm_arr[i]);
        if (NULL != temp)
        {
            ListDestroy(lst);
            return EXIT_FAILURE;
        }
        temp = ListFind(ListBegin(lst), tail, IntCmp, NULL, &nums[i]);
        if (temp == NULL || *(int*)ListGetData(runner)
            != bm_arr[i] + test_Val)
        {
            ListDestroy(lst);
            return EXIT_FAILURE;
        }
        runner = ListNext(runner);
    }
    ListDestroy(lst);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/********************   END OF TEST FUNCTION DEFINITIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DEFINITIONS   ***********************/
/*******************************************************************************/
void _ListPrintInt(list_t* lst)
{
    l_iter_t *runner = NULL, *tail = NULL;
    runner = ListBegin(lst), tail = ListTail(lst);
    putchar('{');
    while (!ListSameIter(runner, tail))

    {
        printf("%d  ", *(int *)ListGetData(runner));
        runner = ListNext(runner);
    }
    puts("}");
}
/*******************************************************************************/
list_t *_initSampleList()
{
    list_t *lst = NULL;

    lst = ListCreate();
    if (NULL == lst)
        return NULL;
    ListPushFront(lst, &nums[1]);
    ListPushBack(lst, &nums[0]);
    ListPushFront(lst, &nums[2]);
    return lst;
}
/*******************************************************************************/
int IntCmp(const void *data, const void *list_data, void *param)
{
    UNUSED(param);
    return *(int *)data == *(int *)list_data;
}
/*******************************************************************************/
int IntActFnc(void *list_data, void *param)
{
    *(int *)list_data += *(int *)param;
    return 0;
}
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DEFINITIONS   *******************/
/*******************************************************************************/