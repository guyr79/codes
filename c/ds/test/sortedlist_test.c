/********************************************************************************
 * sortedlist_test.c		                                                    *
 *                                                                              *
 * Implements tests for sortedlist'S API                                        *
 *													                            *
 * Author: Guy Rosen								                            *
 * Reviewer: REVIEWER                                                           *
 * DATE: 13/08/2020        					    	                            *
 ********************************************************************************/
#include <stdio.h>      /* printf       */
#include <stdlib.h>     /* EXIT_SUCCESS */
#include <string.h>     /* strcmp       */
#include "sortedlist.h" /* library      */
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
int SLFuncCreateSizeEmptyBeginTailTest(void);
int SLFUNCInsertPopRemoveFindTest(void);
int SLFUNCMergeTest(void);
/*
int SLFUNC_sortedlist5_Test(void);
int SLFUNC_sortedlist6_Test(void);
int SLFUNC_sortedlist7_Test(void);
int SLFUNC_sortedlist8_Test(void);
int SLFUNC_sortedlist9_Test(void);
int SLFUNC_sortedlist10_Test(void);
int SLFUNC_sortedlist11_Test(void);
int SLFUNC_sortedlist12_Test(void);
int SLFUNC_sortedlist13_Test(void);
int SLFUNC_sortedlist14_Test(void);
*/
/*******************************************************************************/
/*******************   END OF TEST FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DECLARATIONS   **********************/
/*******************************************************************************/
int _TestInit(void);
void _TestEnd(void);
int IntSLCmp(const void *data, const void * sl_data, void *param);
int StrSLCmp(const void *data, const void * sl_data, void *param);
void _SListPrintInt(slist_t* lst);
int _IntInsertRemoveFindTest();
int _StrInsertRemoveFindTest();
/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/****************   GLOBAL AND STATIC VARIABLES DEFINITIONS   ******************/
/*******************************************************************************/
slist_t *so_lsts[4] ={ NULL };
int nums[] ={ 5, 9, 20, 3, 1, 8, 10 };
char strs[][6] ={ "Ortal", "Guy", "Tamar", "Irad", "David" };
int merge_src[] ={ 3, 1, 9, 8 };
int merge_dest[] ={ 5, 0, 15, 7 };
slist_t *dest =  NULL, *src = NULL;
/*******************************************************************************/
/**************   END OF GLOBAL AND STATIC VARIABLES DEFINITIONS   *************/
/*******************************************************************************/

/*******************************************************************************/
int main(void)
{
    if (EXIT_SUCCESS != _TestInit())
    {
        puts("initialization failed");
        _TestEnd();
        return EXIT_FAILURE;
    }
    RUN_TEST(SLFuncCreateSizeEmptyBeginTailTest);
    RUN_TEST(SLFUNCInsertPopRemoveFindTest);
    RUN_TEST(SLFUNCMergeTest);
    /*
    RUN_TEST(SLFUNC_sortedlist5_TEST);
    RUN_TEST(SLFUNC_sortedlist6_TEST);
    RUN_TEST(SLFUNC_sortedlist7_TEST);
    RUN_TEST(SLFUNC_sortedlist8_TEST);
    RUN_TEST(SLFUNC_sortedlist9_TEST);
    RUN_TEST(SLFUNC_sortedlist10_TEST);
    RUN_TEST(SLFUNC_sortedlist11_TEST);
    RUN_TEST(SLFUNC_sortedlist12_TEST);
    RUN_TEST(SLFUNC_sortedlist13_TEST);
    RUN_TEST(SLFUNC_sortedlist14_TEST);*/
    _TestEnd();
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DEFINITIONS   *************************/
/*******************************************************************************/
int SLFuncCreateSizeEmptyBeginTailTest(void)
{
    size_t i = 0;
    int isempty = 0, size = 0;
    sliter_t tail = NULL;
    for (; i < ARR_SIZE(so_lsts); ++i)
    {
        isempty = SListIsEmpty(so_lsts[i]);
        size = SListSize(so_lsts[i]);
        tail = SListTail(so_lsts[i]);
        if (1 != isempty && 0 != size &&
            1 != SListIsSameIter(tail, SListBegin(so_lsts[i])))
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int SLFUNCInsertPopRemoveFindTest(void)
{
    if (_IntInsertRemoveFindTest() == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (_StrInsertRemoveFindTest() == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int SLFUNCMergeTest(void)
{
    int *bench_arr = calloc(ARR_SIZE(merge_dest) + ARR_SIZE(merge_dest),
        sizeof(int));
    size_t i = 0;
    sliter_t runner = NULL;
    for (i = 0; i < ARR_SIZE(merge_src); i++)
    {
        SListInsert(src, &merge_src[i], NULL);
        bench_arr[i] = merge_src[i];
    }
    for (i = 0; i < ARR_SIZE(merge_dest); i++)
    {
        SListInsert(dest, &merge_dest[i], NULL);
        bench_arr[ARR_SIZE(merge_src) + i] = merge_dest[i];
    }
    _SListPrintInt(src);
    _SListPrintInt(dest);
    qsort(bench_arr, ARR_SIZE(merge_dest) + ARR_SIZE(merge_dest),
        sizeof(int), IntQsortFunc);
    SListMerge(dest, src, NULL);
    _SListPrintInt(dest);
    runner = SListBegin(dest);
    for (i = 0; i < ARR_SIZE(merge_dest) + ARR_SIZE(merge_dest); ++i)
    {
        if (bench_arr[i] != *(int *)SListGetData(runner))
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
        runner = SListNext(runner);
    }
    if (!SListIsSameIter(runner, SListTail(dest)))
    {
        free(bench_arr);
        return EXIT_FAILURE;
    }
    free(bench_arr);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/*int SLFUNC_sortedlist5_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist6_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist7_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist8_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist9_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist10_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist11_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist12_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist13_Test(void)
{

}
/*******************************************************************************/
/*int SLFUNC_sortedlist14_Test(void)
{

}
/*******************************************************************************/
/********************   END OF TEST FUNCTION DEFINITIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DEFINITIONS   ***********************/
/*******************************************************************************/
int _TestInit(void)
{
    size_t i = 0;
    for (; i < ARR_SIZE(so_lsts); ++i)
    {
        so_lsts[i] = SListCreate(((i > 1) ? StrSLCmp : IntSLCmp));
        if (so_lsts[i] == NULL)
            return EXIT_FAILURE;
    }
    dest = SListCreate(IntSLCmp);
    src = SListCreate(IntSLCmp);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
void _TestEnd(void)
{
    size_t i = 0;
    for (; i < ARR_SIZE(so_lsts); ++i)
        SListDestroy(so_lsts[i]);
    SListDestroy(dest);
    SListDestroy(src);
}
/*******************************************************************************/
int IntSLCmp(const void *data, const void *sl_data, void *param)
{
    UNUSED(param);
    return IntQsortFunc(data, sl_data);
}
/*******************************************************************************/
int StrSLCmp(const void *data, const void * sl_data, void *param)
{
    UNUSED(param);
    return StrQSortFunc(data, sl_data);
}
/*******************************************************************************/
void _SListPrintInt(slist_t* lst)
{
    sliter_t runner = NULL, tail = NULL;
    runner = SListBegin(lst), tail = SListTail(lst);
    putchar('{');
    while (!SListIsSameIter(runner, tail))

    {
        printf("%d  ", *(int *)SListGetData(runner));
        runner = SListNext(runner);
    }
    puts("}");
}
/*******************************************************************************/
int _IntInsertRemoveFindTest()
{
    int *bench_arr = calloc(ARR_SIZE(nums), sizeof(int));
    size_t i = 0;
    sliter_t runner = NULL;
    for (; i < ARR_SIZE(nums);++i)
    {
        bench_arr[i] = nums[i];
    }
    qsort(bench_arr, ARR_SIZE(nums), sizeof(int), IntQsortFunc);
    for (i = 0; i < ARR_SIZE(nums); ++i)
    {
        SListInsert(so_lsts[0], &nums[i], NULL);
    }
    _SListPrintInt(so_lsts[0]);
    runner = SListBegin(so_lsts[0]);
    for (i = 0; i < ARR_SIZE(nums); ++i)
    {
        if (bench_arr[i] != *(int*)SListGetData(runner))
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
        runner = SListNext(runner);
    }
    if (!SListIsSameIter(runner, SListTail(so_lsts[0])))
    {
        free(bench_arr);
        return EXIT_FAILURE;
    }
    for (i = 0; i < ARR_SIZE(nums); ++i)
    {
        int siter_num = 0;
        sliter_t siter = SListFind(SListBegin(so_lsts[0]),
            (SListTail(so_lsts[0])), IntSLCmp, NULL, &bench_arr[i]);
        if (siter == NULL)
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
        siter_num = *(int *)SListGetData(siter);
        if (siter_num != bench_arr[i])
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
        SListPopFront(so_lsts[0]);
        siter = SListFind(SListBegin(so_lsts[0]),
            SListTail(so_lsts[0]), IntSLCmp, NULL, &bench_arr[i]);
        if (siter != NULL)
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
    }


    free(bench_arr);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int _StrInsertRemoveFindTest()
{
    char  bench_str[5][6] ={ 0 };
    size_t i = 0;
    sliter_t runner = NULL;
    for (i = 0; i < ARR_SIZE(bench_str);++i)
    {
        strcpy(bench_str[i], strs[i]);
    }
    qsort(bench_str, ARR_SIZE(bench_str), sizeof(*bench_str), StrQSortFunc);
    for (i = 0; i < ARR_SIZE(strs); ++i)
    {
        SListInsert(so_lsts[2], &strs[i], NULL);
    }

    runner = SListBegin(so_lsts[2]);
    for (i = 0; i < ARR_SIZE(bench_str); ++i)
    {
        if (strcmp(bench_str[i], (char *)SListGetData(runner)))
            return EXIT_FAILURE;
        runner = SListNext(runner);
    }
    if (!SListIsSameIter(runner, SListTail(so_lsts[2])))
        return EXIT_FAILURE;

    for (i = ARR_SIZE(strs) - 1; !SListIsEmpty(so_lsts[2]); --i)
    {
        char *siter_str = NULL;
        sliter_t siter = SListFind(SListBegin(so_lsts[2]),
            (SListTail(so_lsts[2])), StrSLCmp, NULL, &bench_str[i]);
        if (siter == NULL)
        {
            return EXIT_FAILURE;
        }
        siter_str = (char *)SListGetData(siter);
        if (strcmp(siter_str, bench_str[i]))
        {
            return EXIT_FAILURE;
        }
        SListPopBack(so_lsts[2]);
        siter = SListFind(SListBegin(so_lsts[2]),
            SListTail(so_lsts[2]), StrSLCmp, NULL, &bench_str[i]);
        if (siter != NULL)
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DEFINITIONS   *******************/
/*******************************************************************************/