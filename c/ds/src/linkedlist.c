/********************************************************************************
 * linkedlist.c		                                                            *
 *                                                                              *
 * Implements linkedlist's API                                                  *
 *                                                                              *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * DATE: 10/08/2020           					    	                        *
 *******************************************************************************/

#include "utils.h"      /* macros   */
#include "linkedlist.h" /* library  */
#include <stdlib.h>     /* calloc   */
#include <assert.h>     /* assert   */
 /*******************************************************************************/
 /***********************   PRIVATE FUNCTION DECLARATIONS   *********************/
 /*******************************************************************************/
l_iter_t *_LNodeCreate(const void *data, const l_iter_t* next,
    const l_iter_t* prev);
void _LNodeDestroy(l_iter_t * iter);
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DECLARATIONS   ******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
struct list_node
{
    void *data;
    struct list_node *next;
    struct list_node *prev;
};

struct linkedlist
{
    struct list_node *head;
    struct list_node *tail;
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
list_t *ListCreate(void)
{
    list_t *new_list = calloc(1, sizeof(*new_list));
    l_iter_t *new_head = _LNodeCreate((void*)0XDEADBEAF, NULL, NULL);
    l_iter_t *new_tail = _LNodeCreate((void*)0XBADCAFFEE, NULL, NULL);
    if (new_list == NULL || new_head == NULL || new_tail == NULL)
    {
        free(new_list);
        free(new_head);
        free(new_tail);
        return NULL;
    }
    new_head->next = new_tail;
    new_tail->prev = new_head;
    new_list->head = new_head;
    new_list->tail = new_tail;
    return new_list;
}
/*******************************************************************************/
size_t ListSize(const list_t *lst)
{
    l_iter_t *runner = NULL, *tail = NULL;
    size_t size = 0;
    assert(NULL != lst);
    runner = ListBegin(lst), tail = ListTail(lst);
    while (!ListSameIter(runner, tail))
    {
        ++size;
        runner = ListNext(runner);
    }
    return size;
}
/*******************************************************************************/
int ListIsEmpty(const list_t *lst)
{
    assert(NULL != lst);
    return ListSize(lst) == 0;
}
/*******************************************************************************/
l_iter_t *ListBegin(const list_t *lst)
{
    assert(NULL != lst);
    return lst->head->next;
}
/*******************************************************************************/
l_iter_t *ListTail(const list_t *lst)
{
    assert(NULL != lst);
    return lst->tail;
}
/*******************************************************************************/
l_iter_t * ListNext(const l_iter_t *iter)
{
    assert(NULL != iter);
    return iter->next;
}
/*******************************************************************************/
l_iter_t * ListPrev(const l_iter_t  *iter)
{
    assert(NULL != iter);
    return iter->prev;
}
/*******************************************************************************/
l_iter_t *ListPushFront(list_t *lst, const void *data)
{
    l_iter_t *new_node = NULL;
    assert(NULL != lst);
    new_node = _LNodeCreate(data, ListBegin(lst), lst->head);
    if (NULL == new_node)
        return NULL;
    ListNext(new_node)->prev = new_node;
    lst->head->next = new_node;
    return new_node;
}
/*******************************************************************************/
l_iter_t *ListPushBack(list_t *lst, const void *data)
{
    l_iter_t *new_node = NULL;
    assert(NULL != lst);
    new_node = _LNodeCreate(data, ListTail(lst), ListPrev(ListTail(lst)));
    if (NULL == new_node)
        return NULL;
    ListTail(lst)->prev = new_node;
    ListPrev(new_node)->next = new_node;
    return new_node;
}
/*******************************************************************************/
void ListPopFront(list_t *lst)
{
    l_iter_t *to_delete = NULL, *new_first_element = NULL;
    assert(NULL != lst);
    to_delete = ListBegin(lst);
    new_first_element = ListNext(to_delete);
    lst->head->next = new_first_element;
    new_first_element->prev = lst->head;
    _LNodeDestroy(to_delete);
}
/*******************************************************************************/
void ListPopBack(list_t *lst)
{
    l_iter_t *to_delete = NULL, *tail = NULL, *new_prev = NULL;
    assert(NULL != lst);
    tail = ListTail(lst);
    to_delete = ListPrev(tail);
    new_prev = ListPrev(to_delete);
    tail->prev = new_prev;
    new_prev->next = tail;
    _LNodeDestroy(to_delete);
}
/*******************************************************************************/
int ListSameIter(const l_iter_t *iter1, const l_iter_t *iter2)
{
    assert(NULL != iter1 && NULL != iter2);
    return iter1 == iter2;
}
/*******************************************************************************/
void *ListGetData(const l_iter_t *iter)
{
    assert(NULL != iter);
    return iter->data;
}
/*******************************************************************************/
l_iter_t *ListAddBefore(l_iter_t *add_before_me, const void *data)
{
    l_iter_t *new = NULL;
    assert(NULL != add_before_me);
    new = _LNodeCreate(data, add_before_me, ListPrev(add_before_me));
    if (NULL == new)
        return NULL;
    ListPrev(add_before_me)->next = new;
    add_before_me->prev = new;
    return new;
}
/*******************************************************************************/
l_iter_t *ListRemove(l_iter_t *iter)
{
    l_iter_t * to_return = NULL;
    assert(NULL != iter);
    to_return = ListPrev(iter)->next = ListNext(iter);
    ListNext(iter)->prev = ListPrev(iter);
    _LNodeDestroy(iter);
    return to_return;
}
/*******************************************************************************/
l_iter_t *ListFind(const l_iter_t *from, const l_iter_t *to,
    cmp_func_t cmp, void *param, const void *data)
{
    int flag = 1;
    assert(from != NULL);
    assert(to != NULL);
    assert(cmp != NULL);

    while (!ListSameIter(from, to) && flag)
    {
        flag = cmp(data, ListGetData(from), param);
        from = (flag) ? ListNext(from): from;
    }
    return (flag)? NULL : (l_iter_t *)from;
}
/*******************************************************************************/
int ListForEach(l_iter_t *from, const l_iter_t *to,
    act_func_t actfnc, void *param)
{
    int flag = 0;
    assert(from != NULL);
    assert(to != NULL);
    assert(actfnc != NULL);

    while (!ListSameIter(to, from) && !flag)
    {
        flag = actfnc(ListGetData(from), param);
        from = ListNext(from);
    }
    return flag;
}
/*******************************************************************************/
void ListCutAndConcate(l_iter_t *conc_to, l_iter_t *range_from, l_iter_t *range_to)
{
    assert(conc_to != NULL);
    assert(range_from != NULL);
    assert(range_to != NULL);
    ListPrev(range_from)->next = range_to;
    range_to->prev = ListPrev(range_from);
    range_from->prev = conc_to;
    ListNext(conc_to)->prev = ListPrev(range_to);
    conc_to->next = range_from;
}
/*******************************************************************************/
void ListDestroy(list_t *lst)
{
    l_iter_t *runner = NULL;
    assert(NULL != lst);
    runner = ListBegin(lst);
    while (!ListSameIter(runner, ListTail(lst)))
    {
        runner = ListRemove(runner);
    }
    _LNodeDestroy(lst->head), _LNodeDestroy(lst->tail);
    lst->head = lst->tail = NULL;
    free(lst);
}
/*******************************************************************************/
/**********************   END OF API FUNCTION DEFINITIONS   ********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DEFINITIONS   **********************/
/*******************************************************************************/
l_iter_t *_LNodeCreate(const void *data, const l_iter_t* next,
    const l_iter_t* prev)
{
    l_iter_t *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
        return NULL;
    new_node->data = (void *)data;
    new_node->next = (l_iter_t *)next;
    new_node->prev = (l_iter_t *)prev;
    return new_node;
}

/*******************************************************************************/
void _LNodeDestroy(l_iter_t * iter)
{
    assert(NULL != iter);
    iter->data = NULL;
    iter->next = NULL;
    iter->prev = NULL;
    free(iter);
}
/*******************************************************************************/
/********************   END OF PRIVATE FUNCTION DEFINITIONS   ******************/
/*******************************************************************************/