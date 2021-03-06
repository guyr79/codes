/********************************************************************************
 * circ_buf.c		                                                            *
 *                                                                              *
 * Implements circ_buf's API                                                    *
 *                                                                              *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                           *
 * DATE           					    	                                    *
 *******************************************************************************/
#include <string.h>   /* memmove  */
#include <stdlib.h>   /* calloc   */
#include <assert.h>   /* assert   */
#include "utils.h"    /* macros   */
#include "circ_buf.h" /* library  */
/*******************************************************************************/
/***********************   PRIVATE FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/
void _CBInit(cbuf_t *cb, size_t capacity);
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DECLARATIONS   ******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
#define GET_CBUF_SIZE(cap) (offsetof(cbuf_t, _buf) + cap)
struct circular_buffer
{
    size_t _cap;
    size_t _r_ind;
    size_t _w_ind;
    char _buf[1];
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
cbuf_t *CBCreate(size_t capacity)
{
    cbuf_t *cb;
    assert(0 < capacity);
    cb = calloc(GET_CBUF_SIZE(capacity), 1);
    if (NULL == cb)
        return NULL;
    _CBInit(cb, capacity);
    return cb;
}
/*******************************************************************************/
cbuf_t *CBCopy(cbuf_t *other)
{
    cbuf_t *cb = NULL;
    if (other == NULL)
        return NULL;
    cb = CBCreate(other->_cap);
    memmove(cb, other, GET_CBUF_SIZE(other->_cap));
    return cb;
}
/*******************************************************************************/
size_t CBGetCapacity(const cbuf_t *cb)
{
    assert(NULL != cb);
    return cb->_cap;
}
/*******************************************************************************/
int CBIsEmpty(const cbuf_t *cb)
{
    assert(NULL != cb);
    return (cb->_r_ind == cb->_w_ind);
}
/*******************************************************************************/
size_t CBGetFreeSpace(const cbuf_t *cb)
{
    assert(NULL != cb);
    return cb->_cap - (cb->_r_ind - cb->_w_ind);
}
/*******************************************************************************/
int CBEquals(cbuf_t *cb1, cbuf_t *cb2)
{
    if (cb1 == cb2)
        return 1;
    if (cb1->_cap != cb2->_cap)
    {
        return 0;
    }
    return (memcmp(cb1, cb2, cb1->_cap) == 0);
}
/*******************************************************************************/
ssize_t CBRead(cbuf_t *cb, const void *src, size_t count)
{
    size_t available_space = 0;
    size_t r_ind;

    assert(NULL != cb);
    assert(NULL != src);
    if (0 == count)
        return 0;
    available_space = CBGetFreeSpace(cb);
    if (0 == available_space)
        return -1;
    count = (count > available_space) ? available_space : count;
    r_ind = cb->_r_ind % cb->_cap;
    if (r_ind + count < cb->_cap)
    {
        memmove(cb->_buf + r_ind, src, count);
    }
    else
    {
        memmove(cb->_buf + r_ind, src, cb->_cap - r_ind);
        memmove(cb->_buf, src, r_ind + count - cb->_cap);
    }
    cb->_r_ind += count;
    return count;
}
/*******************************************************************************/
ssize_t CBWrite(cbuf_t *cb, void *dst, size_t count)
{
    size_t bytes_to_read = 0;
    size_t w_ind;

    assert(NULL != cb);
    assert(NULL != dst);
    if (0 == count)
        return 0;
    bytes_to_read = cb->_cap - CBGetFreeSpace(cb);
    if (0 == bytes_to_read)
        return -1;
    count = (count > bytes_to_read) ? bytes_to_read : count;
    w_ind = cb->_w_ind % cb->_cap;
    if (w_ind + count < cb->_cap)
    {
        memmove(dst, cb->_buf + w_ind, count);
    }
    else
    {
        memmove(dst, cb->_buf + w_ind, cb->_cap - w_ind);
        memmove(dst, cb->_buf, w_ind + count - cb->_cap);
    }
    cb->_w_ind += count;
    return count;
}
/*******************************************************************************/
void CBDestroy(cbuf_t *cb)
{
    cb->_r_ind = 0, cb->_w_ind = 0;
    memset(cb->_buf, '\0', cb->_cap);
    cb->_cap = 0;
    free(cb);
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

/*******************************************************************************/

/**********************   END OF API FUNCTION DEFINITIONS   ********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DEFINITIONS   **********************/
/*******************************************************************************/
void _CBInit(cbuf_t *cb, size_t capacity)
{
    cb->_cap = capacity, cb->_w_ind = 0, cb->_r_ind = 0;
}
/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/
/********************   END OF PRIVATE FUNCTION DEFINITIONS   ******************/
/*******************************************************************************/