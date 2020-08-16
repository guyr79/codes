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
/*  Description:    creates new doubly linked list
*   Return value:   new list pointer
*   Error Value:    NULL   */
list_t *ListCreate(void);
/*  Description:    returns list number of stored elements
*   Parameters:     lst - list to inquire
*   return value:   number of elements in the list */
size_t ListSize(const list_t *lst);
/*  Description:    returns 1 if empty. 0 otherwise
*   Parameters:     lst - list to inquire
*   return value:   1 if the list is empty. 0 otherwise */
int ListIsEmpty(const list_t *lst);
/*  Description:    returnes list's first element. If list is empty, returns tail.
*   Parameters:     lst - list to inquire
*   return value:   node address of first element */
l_iter_t *ListBegin(const list_t *lst);
/*  Description:    returnes list's Tail. List's Tail containes no data. In order
                    to get last element use ListPrev(ListTail(lst))
*   Parameters:     lst - list to inquire
*   return value:   node address of tail dummy */
l_iter_t *ListTail(const list_t *lst);
/*  Description:    returnes nexr elements
*   Parameters:     iter - node to inquire
*   return value:   node address which is after iter in the list */
l_iter_t *ListNext(const l_iter_t *iter);
/*  Description:    returnes previous elements
*   Parameters:     iter - node to inquire
*   return value:   node address which prior to iter in the list */
l_iter_t *ListPrev(const l_iter_t *iter);
/*  Description:    creates new node that holds data address at the beginning
                    of the list
*   Parameters:     lst - list to manipulate. data - data address to store
*   Return Value:   new node created if the action was successful. NULL otherwise */
l_iter_t *ListPushFront(list_t *lst, const void *data);
/*  Description:    creates new node that holds data address at the end
                    of the list
*   Parameters:     lst - list to manipulate. data - data address to store
*   Return Value:   new node created if the action was successful. NULL otherwise */
l_iter_t *ListPushBack(list_t *lst, const void *data);
/*  Description:    deletes list's first element, which is pointed by head.
                    Empty list will generate undefined behavior
*   Parameters:     lst - list to manipulate */
void ListPopFront(list_t *lst);
/*  Description:    deletes list's last element, which points to tail.
                    Empty list will generate undefined behavior
*   Parameters:     lst - list to manipulate */
void ListPopBack(list_t *lst);
/*  Description:    returns 1 if nodes are equale, 0 otherwise. Usefule when
                    iteration on all or some nodes are needed.
                    Important: SameIter does not check equality but confirms
                    iter1, iter2 are the same address
*   Parameters:     iter1, iter2 - nodes to inquire
*   return value:   1 if the nodes share same address, 0 otherwise */
int ListSameIter(const l_iter_t *iter1, const l_iter_t *iter2);
/*  Description:    Retrieves node's data. To read data, casting may be required
*   Parameters:     iter - node to inquire
*   Return Value:   iter's stored data address */
void *ListGetData(const l_iter_t *iter);
/*  Description:    adds new node that stores data and which its previous node
                    is add_location node
*   Parameters:     add_before_me - after insertion, the newly created node will
                    come before node add_before_me
                    data - data address to store
*   Return Value:   new node created if the action was successful. NULL otherwise */
l_iter_t *ListAddBefore(l_iter_t *add_before_me, const void *data);
/*  Description:    removes given node. Trying to remove tail/head dummy node
                    will result in undefined behavior
*   Parameters:     iter - node to be removed
*   Return Value:   returns next node in the list (node after iter) */
l_iter_t *ListRemove(l_iter_t *iter);
/*  Description:    finds the first node which adequate to search specifics
*   Parameters:     from - node to start searching from.
                    to - node to finish the search with, excluding. 'to' will not be
                    considered for the search, only as means of search limitation.
                    passing 'to' address that is not in the same list as 'from', or
                    that is prior to 'from' in the list will result in undefined behavior
                    cmp - comparing function. See typedef for cmp_func_t. it receives
                    data, param and node's data parameters to conclude if node's data
                    is the required data. If true cmp returns 1, otherwise cmp returns 0.
                    Must be provided by user.
                    param - data required to cmp function. can be NULL.
                    data - data to look for.
*   Return value:   if successful, returns address of located node. NULL otherwise */
l_iter_t *ListFind(const l_iter_t *from, const l_iter_t *to,
    cmp_func_t cmp, void *param, const void *data);
/*  Description:    performs action on all nodes in a given range by 'from'-'to',
                    excluding 'to' node
*   Parameters:     from - node to start performing action from. passing head will result
                    in undefined behavior
                    to - node to finish the action with, excluding. 'to' will not be
                    considered for the action, only as means of range limitation.
                    passing 'to' address that is not in the same list as 'from', or
                    that is prior to 'from' in the list will result in undefined behavior
                    actfnc - function that performs some action. Given by user
                    (see typedef at top of the document).
                    If action is successful actfnc will return 0. 1 otherwise.
                    Unsuccessful operation of actfnc will result in failure of
                    ListForEach function, but will not undone previous successful
                    operations
                    param - data used by actfnc. Optional and can be NULL
    Return value:   0 on successful operation. 1 otherwise */
int ListForEach(l_iter_t *from, const l_iter_t *to,
    act_func_t actfnc, void *param);
/*  Description:    cuts range of connected nodes from one list and concatenates
                    it to another list
*   Parameters:     conc_to - node to be connected with the first element in the
                    concatenated range
                    range_from - first element in the added range. Its previous node,
                    after performing concatenation, will be conc_to.
                    range_to - last element in the given range. Will not be added.
                    Used only as means of range limitation
                    IMPORTANT: range_from and range_to must come from the same list.
                    Also, conc_to must be come from another list. conc_to can be head
                    but can not be tail. range_from and range_to must not be head or tail.
                    Violating this rules will result in undefined behavior */
void ListCutAndConcate(l_iter_t *conc_to, l_iter_t *range_from, l_iter_t *range_to);
/*  Description:    Frees linkedlist allocated memory
*   Parameters:     lst:   list to destroy and to free its memory */
void ListDestroy(list_t *lst);
#endif /*__LINKEDLIST_H__*/
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/
