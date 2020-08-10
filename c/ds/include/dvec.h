/********************************************************************************
 * dvec.h		                                                                *
 *                                                                              *
 * Declares bit array's API                                                     *
 *													                            *
 * Author: Guy Rosen													        *
 * Reviewer: Irad Ratmansky                                                     *
 * 27.06.2020           					    	                            *
 *******************************************************************************/
#ifndef __DVEC_H__
#define __DVEC_H__

#include "utils.h"
#include <stddef.h> /*  size_t */
/*******************************************************************************/
/****************************   TYPE DECLARATIONS   ****************************/
/*******************************************************************************/
typedef struct dvec dvec_t;
/*******************************************************************************/
/************************    END OF TYPE DECLARATIONS    ***********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*******************************************************************************/

/*  Description:    creates a dinamic vector
*   Parameters:     elm_size - element size, capacity - initial num of elements 
*   Return value:   new dvec
*   Error Value:    NULL                                                        
    Complexity:     o(1)                                                        */
dvec_t *DvecCreate(size_t elm_size, size_t capacity);
/*  Description:    returns number of elements in dvec
*   Parameters:     dv - the dvec in question
    complexity:     o(1)                                                        */
size_t DVecSize(const dvec_t *dv);
/*  Description:    returns current capacity dvec 
*   Parameters:     dv - the dvec in question                                   */
size_t DVecCapacity(const dvec_t *dv);
/*  Description:    insert data in address date to dvec dv      
*   Parameters:     
    complexity:     o(1)                                                        */
int DVecPushBack(dvec_t *dv, const void *data);  
/*  Description:    pops element from dvec      
*   Parameters:                                                                 
*   complexity:     o(1)                                                        */
void DVecPopBack(dvec_t *dv);
/*  Description:    returns item requested by index address of an element in dvec    
    Parameters:     index - defines requested item                              
*   complexity:     o(1)                                                        */
void *DVecGetItemAddress(dvec_t *dv, size_t index);
/*  Description:    Frees dvec's allocated memory
*   Parameters:     dv:   dvec_t to free 
    complexity:     o(1)                                                        */
void DvecDestroy(dvec_t *dv);

#endif
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/
