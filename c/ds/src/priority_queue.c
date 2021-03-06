/********************************************************************************
 * priority_queue.c		                                                        *
 *                                                                              *
* Implements priority_queue's API                                               *
 *                                                                              *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * DATE: 15/08/2020          					    	                        *
 *******************************************************************************/
#include <stdlib.h>         /* calloc               */
#include <assert.h>         /* assert               */
#include "utils.h"          /* macros               */
#include "priority_queue.h" /* library              */
#include "sortedlist.h"     /* sorted_list library  */
/*******************************************************************************/
/***********************   PRIVATE FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DECLARATIONS   ******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
struct priority_queue
{
    slist_t *so_lst;
    void *param;
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
pq_t *PQCreate(pr_cmp_func_t PriorityFunc, void *param)
{
    pq_t *pq = NULL;
    assert(NULL != PriorityFunc);
    if (NULL == (pq = calloc(1, sizeof(*pq))))
        return NULL;
    if (NULL == (pq->so_lst = SListCreate(PriorityFunc)))
    {
        free(pq);
        return NULL;
    }
    pq->param = param;
    return pq;
}
/*******************************************************************************/
int PQEnQueue(pq_t *pq, void *data)
{
    assert(NULL != pq);
    return NULL != SListInsert(pq->so_lst, data, pq->param);
}
/*******************************************************************************/
void PQDeQueue(pq_t *pq)
{
    assert(NULL != pq);
    SListPopFront(pq->so_lst);
}
/*******************************************************************************/
void *PQPeek(const pq_t *pq)
{
    assert(NULL != pq);
    return SListGetData(SListBegin(pq->so_lst));
}
/*******************************************************************************/
size_t PQSize(const pq_t *pq)
{
    assert(NULL != pq);
    return SListSize(pq->so_lst);
}
/*******************************************************************************/
int PQIsEmpty(const pq_t *pq)
{
    assert(NULL != pq);
    return PQSize(pq) == 0;
}
/*******************************************************************************/
void PQClear(pq_t *pq)
{
    assert(NULL != pq);
    while (!PQIsEmpty(pq))
    {
        PQDeQueue(pq);
    }
}
/*******************************************************************************/
void *PQRemove(pq_t *pq, pr_cmp_func_t CmpData, const void *data_to_match)
{
    slist_t *so_lst = NULL;
    sliter_t to_remove = NULL;
    void *data_to_return = NULL;
    assert(NULL != pq);
    so_lst = pq->so_lst;
    to_remove = SListFind(SListBegin(so_lst),
                          SListTail(so_lst), CmpData, pq->param, data_to_match);
    if (NULL != to_remove)
    {
        data_to_return = SListGetData(to_remove);
        SListRemove(to_remove);
    }

    return data_to_return;
}
/*******************************************************************************/
void PQDestroy(pq_t *pq)
{
    SListDestroy(pq->so_lst);
    pq->so_lst = NULL;
    pq->param = NULL;
    free(pq);
}
/*******************************************************************************/
/**********************   END OF API FUNCTION DEFINITIONS   ********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DEFINITIONS   **********************/
/*******************************************************************************/

/*******************************************************************************/
/********************   END OF PRIVATE FUNCTION DEFINITIONS   ******************/
/*******************************************************************************/