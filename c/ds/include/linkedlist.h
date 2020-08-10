/********************************************************************************
 * linkedlist.h		                                                            *            
 *                                                                              *
 * Declares linkedlist's API                                                    *
 *													                            *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * DATE: 10/08/2020        					    	                            *            *
 *******************************************************************************/
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include "utils.h"
 /*******************************************************************************/
 /****************************   TYPE DECLARATIONS   ****************************/
 /*******************************************************************************/
typedef int (*cmp_func_t)(const void *data, const void *list_data, void *param);
typedef int (*act_func_t)(void *list_data, void *param);
typedef struct linkedlist list_t;
typedef struct list_node l_iter_t;
/*******************************************************************************/
/************************    END OF TYPE DECLARATIONS    ***********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*******************************************************************************/
/*  Description:
*   Parameters:
*   Return value:
*   Error Value:     */
list_t *ListCreate(void);
/*  Description:
    Parameters:      */
size_t ListSize(const list_t *lst);
/*  Description:
*   Parameters:      */
int ListIsEmpty(const list_t *lst);
/*  Description:
*   Parameters:      */
l_iter_t *ListHead(const list_t *lst);
/*  Description:
*   Parameters:      */
l_iter_t *ListTail(const list_t *lst);
/*  Description:
*   Parameters:      */
l_iter_t *ListNext(const l_iter_t *iter);
/*  Description:
*   Parameters:      */
l_iter_t *ListPrev(const l_iter_t *iter);
/*  Description:
    Parameters:      */
int ListPushFront(list_t *lst, const void *data);
/*  Description:
*   Parameters:      */
int ListPushBack(list_t *lst, const void *data);
/*  Description:
    Parameters:      */
void ListPopFront(list_t *lst);
/*  Description:
    Parameters:      */
void ListPopBack(list_t *lst);
/*  Description:
    Parameters:      */
int ListSameIter(const l_iter_t *iter1, const l_iter_t *iter2);
/*  Description:
*   Parameters:      */
void *ListGetData(const l_iter_t *iter);
/*  Description:
*   Parameters:     b */
int ListAdd(l_iter_t *add_location, const void *data);
/*  Description:
*   Parameters:
    Return Value*:   */
void ListRemove(l_iter_t *iter);
/*  Description:
*   Parameters:
*   Return value:
*   Error Value:     */
l_iter_t *ListFind(const l_iter_t *from, const l_iter_t *to,
    cmp_func_t cmp, void *param, const void *data);
/*  Description:
*   Parameters:      */
int ListForEach(l_iter_t *from, const l_iter_t *to,
    act_func_t actfnc, void *param);
/*  Description:
*   Parameters:      */
void ListCutAndConcate(l_iter_t *conc_to, l_iter_t *range_from, l_iter_t *range_to);
/*  Description:    Frees linkedlist allocated memory
*   Parameters:     linkedlist:   linkelist_tYPE to free */
void ListDestroy(list_t *lst);
#endif /*__LINKEDLIST_H__*/
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/
