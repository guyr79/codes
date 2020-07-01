/********************************************************************************
 * stack.c		                                                                *
 *                                                                              *
 * Implements stack's API                                                   *
 *                                                                              *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                     *
 * DATE           					    	                            *
 *******************************************************************************/
#include <stdlib.h> /* malloc   */
#include <assert.h> /* assert   */
#include <string.h> /* memcpy  */
#include "utils.h"  /* macros   */
#include "stack.h"  /* library  */
/*******************************************************************************/
/***********************   PRIVATE FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DECLARATIONS   ******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
#define GET_STACK_SIZE(x, y) (offsetof(stack_t, _data) + x * y)
struct stack
{
    size_t _capacity;
    size_t _element_size;
    size_t _top_of_stack;
    char _data[1]; /* nice trick for capacity defining with 1 malloc only */
};
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/*************************   API FUNCTION DEFINITIONS   ************************/
/*******************************************************************************/
stack_t *StackCreate(size_t capacity, size_t element_size)
{
    stack_t *new_st = NULL;
    assert(element_size > 0);
    assert(capacity > 0);
    new_st = calloc(GET_STACK_SIZE(capacity, element_size), 1);
    if (NULL == new_st)
    {
        return NULL;
    }
    new_st->_capacity = capacity;
    new_st->_element_size = element_size;
    new_st->_top_of_stack = 0;

    return new_st;
}
/*******************************************************************************/
stack_t *StackCopy(stack_t *other)
{
    stack_t *new_st;
    assert(NULL != other);
    new_st = StackCreate(other->_capacity, other->_element_size);
    if (NULL == new_st)
        return NULL;
    memcpy(new_st, other, GET_STACK_SIZE(other->_capacity, other->_element_size));
    return new_st;
}
/*******************************************************************************/
size_t StackSize(const stack_t *st)
{
    assert(NULL != st);
    return st->_top_of_stack;
}
/*******************************************************************************/
size_t StackCapacity(const stack_t *st)
{
    assert(NULL != st);
    return st->_capacity;
}
/*******************************************************************************/
int StackIsEmpty(const stack_t *st)
{
    assert(NULL != st);
    return st->_top_of_stack == 0;
}
/*******************************************************************************/
int StackEquals(const stack_t *st1, const stack_t *st2)
{
    assert(NULL != st1);
    assert(NULL != st2);
    return memcmp(st1,
                  st2, GET_STACK_SIZE(st1->_capacity, st1->_element_size)) == 0;
}
/*******************************************************************************/
int StackPush(stack_t *st, const void *data)
{
    void *dest = NULL;
    assert(NULL != st);
    assert(NULL != data);
    if (st->_top_of_stack == st->_capacity)
        return EXIT_FAILURE;
    dest = (void *)(st->_data + st->_top_of_stack * st->_element_size);
    ++(st->_top_of_stack);
    memcpy(dest, data, st->_element_size);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
void StackPop(stack_t *st)
{
    void *element_to_pop;
    assert(NULL != st);
    assert(st->_top_of_stack > 0);
    st->_top_of_stack--;
    element_to_pop = (void *)(st->_data + (st->_top_of_stack) * st->_element_size);
    memset(element_to_pop, '\0', st->_element_size);
}
/*******************************************************************************/
int StackTop(const stack_t *st, void *target)
{
    void *src;
    assert(NULL != target);
    assert(NULL != st);
    if (st->_top_of_stack == 0)
        return EXIT_FAILURE;
    src = (void *)(st->_data + (st->_top_of_stack - 1) * st->_element_size);
    memcpy(target, src, st->_element_size);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int StackResize(stack_t **st, size_t new_capacity)
{
    stack_t *new_st;
    size_t n_to_copy;
    assert(NULL != st);
    assert(0 < new_capacity);
    new_st = StackCreate(new_capacity, (*st)->_element_size);
    if (NULL == new_st)
    {
        return EXIT_FAILURE;
    }
    new_st->_top_of_stack = ((*st)->_top_of_stack < new_capacity)
                                ? (*st)->_top_of_stack
                                : new_capacity;
    n_to_copy = new_st->_top_of_stack * new_st->_element_size;
    memmove(new_st->_data,(*st)->_data,n_to_copy);
    free(*st);
    *st = new_st;
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

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