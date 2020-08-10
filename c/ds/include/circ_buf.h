/********************************************************************************
 * circ_buff.h		                                                            *
 *                                                                              *
 * Declares circ_buff's API                                                     *
 *													                            *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * 02.07.2020        					    	                                *
 *******************************************************************************/
#ifndef __CIRC_BUFF_H__
#define __CIRC_BUFF_H__

#include <sys/types.h> /*  size_t  */
/*******************************************************************************/
/****************************   TYPE DECLARATIONS   ****************************/
/*******************************************************************************/
typedef struct circular_buffer cbuf_t;
/*******************************************************************************/
/************************    END OF TYPE DECLARATIONS    ***********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*******************************************************************************/

/*  Description:    Creates circular buffer of size capacity    
*   Return value:   new cbuf_t pointer
*   Error Value:    NULL */
    cbuf_t *CBCreate(size_t capacity);
/*  Description:    creates new circular buffer identical to other
*   Parameters:     other - circular buffer to copy      
*   Return value:   new identical circular buffer
*   Error Value:    NULL */
    cbuf_t *CBCopy(cbuf_t *other);
/*  Description:    returns circular buffer capacity    */
    size_t CBGetCapacity(const cbuf_t *cb);
/*  Description:    checks if circular buffer is empty
*   return value:   1 if empty, 0 otherwise     */
    int CBIsEmpty(const cbuf_t *cb);
/*  Description:    returns free space in buffer    */
    size_t CBGetFreeSpace(const cbuf_t *cb);
/*  Description:    reads count bytes from src
    Parameters:     src - source reading from
                    cb - circular buffer to read into
                    count - number of bytes to read from src   
    Return value:   number of bytes succesfully read. On error returns -1 */
    ssize_t CBRead(cbuf_t *cb, const void* src, size_t count);
/*  Description:    writes count bytes to dst
    Parameters:     dst - destination writing to
                    cb - circular buffer to write from
                    count - number of bytes to write to dst   
    Return value:   number of bytes succesfully write. On error returns -1 */
    ssize_t CBWrite(cbuf_t *cb, void *dst, size_t count);
/*  Description:    determines if cb1 equals to cb2      */
    int CBEquals(cbuf_t *cb1, cbuf_t *cb2);
/*  Description:      
*   Parameters:      */

/*  Description:    Frees cb allocated memory
*   Parameters:     cb:   circular buffer to free */
    void CBDestroy(cbuf_t *cb);
#endif
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/
