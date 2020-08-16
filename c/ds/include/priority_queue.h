/********************************************************************************
 * priority_queue.h		                                                        *
 *                                                                              *
 * Declares priority_queue's API                                                *
 *													                            *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * DATE: 15/08/2020        					    	                            *
 *******************************************************************************/
#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "utils.h"
/*******************************************************************************/
/****************************   TYPE DECLARATIONS   ****************************/
/*******************************************************************************/
typedef int (*pr_cmp_func_t)(const void *data, const void *list_data, void *param); 
typedef struct priority_queue pq_t;
/*******************************************************************************/
/************************    END OF TYPE DECLARATIONS    ***********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*******************************************************************************/

/*  Description:    creates new priority_queue
*   Parameters:     PriorityFunc - function that defines queu order
                    param - global queue parameters    
*   Return value:   new pririty queue
*   Error Value:    NULL */
pq_t *PQCreate(pr_cmp_func_t PriorityFunc ,void *param);
/*  Description:    inserts new data to priority_queue
*   Parameters:     pq -  priority_queue to manipulate
                    data - data to insert
*   Return value:   1 if enqueue action succeeded. 0 otherwise   
*   Error Value:    0 */
int PQEnQueue(pq_t *pq, void *data);
/*  Description:    deletes first element from priority_queue  
*   Parameters:     pq - priority_queue to manipulate */        
void PQDeQueue(pq_t *pq);
/*  Description:    returns first element data      
*   Parameters:     pq - priority_queue to peek 
    Return value:   data address. Casting may be required */
void *PQPeek(const pq_t *pq);
/*  Description:    returns priority_queue number of stored elements
*   Parameters:     pq - priority_queue to inquire 
*   Return value:   priority_queue number of stored elements    */
size_t PQSize(const pq_t *pq);
/*  Description:    checks whether priority_queue is empty or not
*   Parameters:     pq - priority_queue to inquire 
*   Return value:   1 if priority_queue is empty. 0 otherwise    */
int PQIsEmpty(const pq_t *pq);
/*  Description:    clears all priority_queue elements, without destrying queue  
    Parameters:     pq - priority_queue to manipulate */
void PQClear(pq_t *pq);
/*  Description:    looks for requestes data in the priority_queue. If data is
                    found, deletes it from queue but returns matching data sddress.
                    The PriorityFunc defined for PQCreate can be used to locate
                    data_to_match, but is not mandatory.
                    Note that data will be looked for upon the defined CmpData and
                    priority_queue param value, if required
    Parameters:     pq - priority_queue to manipulate
                    CmpData - function to locate data in pq. See pr_cmp_func_t 
                    typedef declaration 
                    data_to_match - data to search for */
void *PQRemove(pq_t *pq, pr_cmp_func_t CmpData, const void *data_to_match);
/*  Description:    Frees priority_queue pq's allocated memory
*   Parameters:     pq:   priority_queue to free */
void PQDestroy(pq_t *pq);
#endif
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/
