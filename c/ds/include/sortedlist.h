/********************************************************************************
 * sortedlist.h		                                                            *
 *                                                                              *
 * Declares sortedlist's API                                                    *
 *													                            *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * DATE: 13/08/2020        					    	                            *
 *******************************************************************************/
#ifndef __SORTEDLIST_H__
#define __SORTEDLIST_H__
#include "utils.h"
/*******************************************************************************/
/****************************   TYPE DECLARATIONS   ****************************/
/*******************************************************************************/
typedef struct sortedlist slist_t;
typedef struct list_node *sliter_t;
typedef int (*sl_cmp_func_t)(const void *data, const void *so_lst_data, void *param);
typedef int (*sl_act_func_t)(void *data, void *param);
/*******************************************************************************/
/************************    END OF TYPE DECLARATIONS    ***********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*******************************************************************************/
/*  Description:    creates new sorted_list
*   Parameters:     sl_cmp - a function that recieves adress data to insert,
                    data adress from list, and param address that might be needed
                    for computation. Note that param can be NULL.
                    The function returns int likewise: if data is
                    smaller than list_data returns negative integer.
                    Equales returns zero (0),
                    and bigger returns positive number integer
*   Return value:   new sorted_list pointer
*   Error Value:    NULL  */
slist_t *SListCreate(sl_cmp_func_t sl_cmp);
/*  Description:    returns sorted_list number of stored elements
*   Parameters:     so_lst - list to inquire
*   return value:   number of elements in the list */
size_t SListSize(const slist_t *so_lst);
/*  Description:    returns 1 if empty. 0 otherwise
*   Parameters:     so_lst - list to inquire
*   return value:   1 if the list is empty. 0 otherwise */
int SListIsEmpty(const slist_t *so_lst);
/*  Description:    returnes list's first element. If list is empty, returns tail.
*   Parameters:     so_lst - list to inquire
*   return value:   node address of first element */
sliter_t SListBegin(const slist_t *so_lst);
/*  Description:    returnes list's Tail. List's Tail containes no data. In order
                    to get last element use SListPrev(SListTail(so_lst))
*   Parameters:     so_lst - list to inquire
*   return value:   node address of tail dummy */
sliter_t SListTail(const slist_t *so_lst);
/*  Description:    returns 1 if nodes are equale, 0 otherwise. Usefule when
                    iteration on all or some nodes are needed.
                    Important: SameIter does not check equality but confirms
                    iter1, siter2 are the same address
*   Parameters:     iter1, siter2 - nodes to inquire
*   return value:   1 if the nodes share same address, 0 otherwise */
int SListIsSameIter(const sliter_t siter1, const sliter_t siter2);
/*  Description:    Retrieves node's data. To read data, casting may be required
*   Parameters:     iter - node to inquire
*   Return Value:   iter's stored data address */
void *SListGetData(const sliter_t siter);
/*  Description:    returnes nexr elements
*   Parameters:     siter - node to inquire
*   return value:   node address which is after siter in the list */
sliter_t SListNext(const sliter_t siter);
/*  Description:    returnes previous elements
*   Parameters:     siter - node to inquire
*   return value:   node address which prior to siter in the list */
sliter_t SListPrev(const sliter_t siter);
/*  Description:    creates new node in the sorted_list that holds data address
*   Parameters:     so_lst - list to manipulate. data - data address to store
                    param - parameter that might be needed for order computation and
                    might be used in the list inner order function. Can recieve NULL.
                    See typedef for sl_cmp_func_t declaration
*   Return Value:   new node created if the action was successful. NULL otherwise */
sliter_t SListInsert(slist_t *so_lst, void *data, void *param);
/*  Description:    removes given node. Trying to remove tail/head dummy node
                    will result in undefined behavior
*   Parameters:     siter - node to be removed
*   Return Value:   returns next node in the list (node after iter) */
sliter_t SListRemove(sliter_t siter);
/*  Description:    deletes list's first element, which is pointed by head.
                    Empty list will generate undefined behavior
*   Parameters:     so_lst - list to manipulate */
void *SListPopFront(slist_t *so_lst);
/*  Description:    deletes list's last element, which points to tail.
                    Empty list will generate undefined behavior
*   Parameters:     so_lst - list to manipulate */
void *SListPopBack(slist_t *so_lst);
/*  Description:    finds the first node which adequate to search specifics
*   Parameters:     from - node to start searching from.
                    to - node to finish the search with, excluding. 'to' will not be
                    considered for the search, only as means of search limitation.
                    passing 'to' address that is not in the same list as 'from', or
                    that is prior to 'from' in the list will result in undefined behavior
                    sl_cmp - comparing function. See typedef for sl_cmp_func_t. it receives
                    data, param and node's data parameters to conclude if node's data
                    is the required data. If true sl_cmp returns 0, otherwise sl_cmp
                    returns non-zero number. The function Must be provided by user.
                    param - data required to cmp function. can be NULL.
                    data - data to look for.
*   Return value:   if successful, returns address of located node. NULL otherwise */
sliter_t SListFind(sliter_t from, sliter_t to,
                   sl_cmp_func_t sl_cmp, void *param, const void *data);
/*  Description:    performs action on all nodes in a given range by 'from'-'to',
                    excluding 'to' node
*   Parameters:     from - node to start performing action from. passing head will result
                    in undefined behavior
                    to - node to finish the action with, excluding. 'to' will not be
                    considered for the action, only as means of range limitation.
                    passing 'to' address that is not in the same list as 'from', or
                    that is prior to 'from' in the list will result in undefined behavior
                    sl_act - function that performs some action. Given by user
                    (see typedef at top of the document).
                    If action is successful sl_act will return 0. non-zero otherwise.
                    Unsuccessful operation of sl_act will result in failure of
                    ListForEach function, but will not undone previous successful
                    operations
                    param - data used by sl_act. Optional and can be NULL
    Return value:   0 on successful operation. non-zero otherwise */
int SListForEach(sliter_t from, sliter_t to, sl_act_func_t sl_act, void *param);
/*  Description:    copies src nodes and insert them to dest.
                    Note: List order will be kept according to dest ordering function
                    (see SListCreate)
*   Parameters:     dest - lst to be manipulated. src - list to copy from 
*   Return value:   1 if merge completed succesfully. 0 otherwise.
                    Note that if 0 received dest can still be copied with part of
                    src nodes. To avoid such behavior use SListMergeToNewList 
                    which returns new complete list if succesful and NULL if
                    error happened 
*   Error value:    0 */
int SListMerge(slist_t *dest, const slist_t *src, void *param);
/*  Description:    creates new list and copies src's and dest's nodes to it
*   Parameters:     src1, src2 - lists to copy from 
                    Note: new list order will be kept according to src1 
                    ordering function (see SListCreate) 
*   Return value:   if succesful, new list. NULL otherwise 
*   Error value:    NULL    */
slist_t *SListMergeToNewList(const slist_t *src1, const slist_t *src2, void *param);
/*  Description:    Frees slst allocated memory
*   Parameters:     slst:   sortedlist to free */
void SListDestroy(slist_t *slst);
#endif /*__SORTEDLIST_H__ */
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/
