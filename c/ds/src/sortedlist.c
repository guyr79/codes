/********************************************************************************
 * sortedlist.c		                                                            *
 *                                                                              *
 * Implements sortedlist's API                                                  *
 *                                                                              *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * DATE: 13/08/2020           					    	                        *
 *******************************************************************************/
#include <stdlib.h>     /* calloc               */
#include <assert.h>     /* assert               */
#include "utils.h"      /* macros               */
#include "linkedlist.h" /* linkedlist library   */
#include "sortedlist.h" /* library              */
                        /*******************************************************************************/
                        /***********************   PRIVATE FUNCTION DECLARATIONS   *********************/
                        /*******************************************************************************/

/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DECLARATIONS   ******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
struct sortedlist
{
    list_t *lst;
    sl_cmp_func_t sl_cmp;
};
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/*****************   GLOBAL AND STATIC VARIABLES DEFINITIONS   *****************/
/*******************************************************************************/

/*******************************************************************************/
/*************   END OF GLOBAL AND STATIC VARIABLES DEFINITIONS   **************/
/*******************************************************************************/

/*******************************************************************************/
/*************************   API FUNCTION DEFINITIONS   ************************/
/*******************************************************************************/
slist_t *SListCreate(sl_cmp_func_t sl_cmp)
{
    slist_t *so_lst = calloc(1, sizeof(*so_lst));
    assert(NULL != sl_cmp);
    if (NULL == so_lst)
        return NULL;
    so_lst->lst = ListCreate();
    if (NULL == so_lst->lst)
    {
        free(so_lst);
        return NULL;
    }
    so_lst->sl_cmp = sl_cmp;
    return so_lst;
}
/*******************************************************************************/
size_t SListSize(const slist_t *so_lst)
{
    assert(NULL != so_lst);
    return ListSize(so_lst->lst);
}
/*******************************************************************************/
int SListIsEmpty(const slist_t *so_lst)
{
    assert(NULL != so_lst);
    return ListIsEmpty(so_lst->lst);
}
/*******************************************************************************/
sliter_t SListBegin(const slist_t *so_lst)
{
    assert(NULL != so_lst);
    return ListBegin(so_lst->lst);
}
/*******************************************************************************/
sliter_t SListTail(const slist_t *so_lst)
{
    assert(NULL != so_lst);
    return ListTail(so_lst->lst);
}
/*******************************************************************************/
int SListIsSameIter(const sliter_t siter1, const sliter_t siter2)
{
    return ListSameIter(siter1, siter2);
}
/*******************************************************************************/
void *SListGetData(const sliter_t siter)
{
    return ListGetData(siter);
}
/*******************************************************************************/
sliter_t SListNext(const sliter_t siter)
{
    return ListNext(siter);
}
/*******************************************************************************/
sliter_t SListPrev(const sliter_t siter)
{
    return ListPrev(siter);
}
/*******************************************************************************/
sliter_t SListInsert(slist_t *so_lst, void *data, void *param)
{
    sliter_t runner = NULL, tail = NULL;
    int flag = 0;
    assert(NULL != so_lst);
    runner = ListBegin(so_lst->lst);
    tail = ListTail(so_lst->lst);
    while (!SListIsSameIter(runner, tail) && !flag)
    {
        flag = so_lst->sl_cmp(data, SListGetData(runner), param) < 0;
        runner = (flag) ? runner : SListNext(runner);
    }
    return ListAddBefore(runner, data);
}
/*******************************************************************************/
sliter_t SListRemove(sliter_t siter)
{
    assert(NULL != siter);
    return ListRemove(siter);
}
/*******************************************************************************/
void *SListPopFront(slist_t *so_lst)
{
    void *data = NULL;
    assert(NULL != so_lst);
    data = SListGetData(SListBegin(so_lst));
    SListRemove(SListBegin(so_lst));
    return data;
}
/*******************************************************************************/
void *SListPopBack(slist_t *so_lst)
{
    void *data = NULL;
    assert(NULL != so_lst);
    data = SListGetData(SListPrev(SListTail(so_lst)));
    SListRemove(SListPrev(SListTail(so_lst)));
    return data;
}
/*******************************************************************************/
sliter_t SListFind(sliter_t from, sliter_t to,
                   sl_cmp_func_t sl_cmp, void *param, const void *data)
{
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != sl_cmp);
    return ListFind(from, to, sl_cmp, param, data);
}
/*******************************************************************************/
int SListForEach(sliter_t from, sliter_t to, sl_act_func_t sl_act, void *param)
{
    assert(NULL != from);
    assert(NULL != to);
    assert(NULL != sl_act);
    return ListForEach(from, to, sl_act, param);
}
/*******************************************************************************/
int SListMerge(slist_t *dest, const slist_t *src, void *param)
{
    sliter_t src_runner = NULL, success = (sliter_t)0XDEADBEEF;
    assert(NULL != dest);
    assert(NULL != src);
    src_runner = SListBegin(src);
    while (NULL != success && !SListIsSameIter(src_runner, SListTail(src)))
    {
        success = SListInsert(dest, SListGetData(src_runner), param);
        src_runner = SListNext(src_runner);
    }
    return (NULL != success) ? 1 : 0;
}
/*******************************************************************************/
slist_t *SListMergeToNewList(const slist_t *src1, const slist_t *src2, void *param)
{
    slist_t *new_lst = NULL;
    sliter_t src1_runner = NULL, success = (sliter_t)0XDEAFBEEF;
    assert(NULL != src1);
    assert(NULL != src2);
    new_lst = SListCreate(src1->sl_cmp);
    src1_runner = SListBegin(src1);
    while (success != NULL && !SListIsSameIter(src1_runner, SListTail(src1)))
    {
        SListInsert(new_lst, SListGetData(src1_runner), param);
        src1_runner = SListNext(src1_runner);
    }
    if (NULL == success)
    {
        SListDestroy(new_lst);
        new_lst = NULL;
    }
    else if (0 == SListMerge(new_lst, src2, param))
    {
        SListDestroy(new_lst);
        new_lst = NULL;
    }
    return new_lst;
}
/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/
void SListDestroy(slist_t *slst)
{
    ListDestroy(slst->lst);
    slst->lst = NULL;
    slst->sl_cmp = NULL;
    free(slst);
}
/*******************************************************************************/

/**********************   END OF API FUNCTION DEFINITIONS   ********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DEFINITIONS   **********************/
/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/
/********************   END OF PRIVATE FUNCTION DEFINITIONS   ******************/
/*******************************************************************************/