/********************************************************************************
 *stack.h		                                                                *
 *                                                                              *
 * Declares stack's API                                                          *
 *													                            *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * 30.06.2020           					    	                            *
 *******************************************************************************/
#ifndef STACK_H
#define STACK_H

#include "utils.h"
/*******************************************************************************/
/****************************   TYPE DECLARATIONS   ****************************/
/*******************************************************************************/
typedef struct stack stack_t;
/*******************************************************************************/
/************************    END OF TYPE DECLARATIONS    ***********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*******************************************************************************/

/*  Description:    create new stack 
*   Parameters:     capacity: size of storage. element_size: size of element 
*   Return value:   new stack pointer   
*   Error Value:    NULL    */
stack_t *StackCreate(size_t capacity, size_t element_size);
/*  Description:    returns a net stack which is an exact copy of other
*   Parameters:     other - stack to copy 
*   return Value:   pointer to copied stack
*   Error value:    NULL    */
stack_t *StackCopy(stack_t *other);
/*  Description:    returns number of elements currently in stack;  
*   Parameters:     st - stack inquired*/
size_t StackSize(const stack_t *st);
/*  Description:    returns capacity of stack;  
*   Parameters:     st - stack inquired*/
size_t StackCapacity(const stack_t *st);
/*  Description:    checks if stacl is empty
    Parameters:     st - stack inquired
    Return Value:   1 if empty, 0 otherwise */
int StackIsEmpty(const stack_t *st);
/*  Description:    returns 1 if stacks are equale (same capacity, data etc.)
                    0 otherwise  
*   Parameters:     st1, st2 - stacks to compare */
int StackEquals(const stack_t *st1, const stack_t *st2);
/*  Description:    push an element into stack if there is available space
*   Parameters:     st - stack to push into. data - address of element to push  
    Return Value:   EXIT_SUCCESS on successful push, EXIT_FAILURE otherwise */
int StackPush(stack_t *st, const void *data);
/*  Description:    pops an element from stack     
*   Parameters:     st - stack to pop from */
void StackPop(stack_t *st);
/*  Description:    getting data from top of stack 
*   Parameters:     st - stack to get top from, target - address for copy top
    Return Value:   EXIT_FAILURE when stack is empty, EXIT_SUCCESS otherwise */
int StackTop(const stack_t *st, void *target);
/*  Description:    resize stack to new capacity
*   Parameters:     st - stack inquired, new_capacity - new capacity of stack
    Notes:          data is kept. If reducing size, data is kept up until end
                    of new capacity */
int StackResize(stack_t **st, size_t new_capacity);
/*  Description:    
*   Parameters:     */

/*  Description:    
*   Parameters:     */

/*  Description:      
*   Parameters:     */

/*  Description:      
*   Parameters:     */

/*  Description:      
*   Parameters:     */

/*  Description:      
*   Parameters:     */

/*  Description:    
*   Parameters:     */

/*  Description:    
*   Parameters:     */

/*  Description:    
*   Parameters:     */

/*  Description:    Frees stack's allocated memory
*   Parameters:     st:  stack to free */
void StackDestroy(stack_t *st);

#endif
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/
