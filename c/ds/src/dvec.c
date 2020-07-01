/********************************************************************************
 * NAME.c		                                                                *
 *                                                                              *
 * Implements NAME's API                                                   *
 *                                                                              *
 * Author: Guy Rosen													        *
 * Reviewer: REVIEWER                                                     *
 * DATE           					    	                            *
 *******************************************************************************/

#include <malloc.h> /* reallocarray */
#include <stdlib.h> /*  malloc  */
#include <string.h> /*  memcpy  */
#include <assert.h> /*  assert  */
#include "dvec.h"   /*  library */
#include "utils.h"  /*  macros  */

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/
int ResizeDvecInnerVector(dvec_t *dv, size_t new_capacity);
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DECLARATIONS   ******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
#define RESIZE_FACTOR (2)
#define DECREASE_THRESHOLD (4)

struct dvec
{
    size_t element_size;
    size_t capacity;
    void *start; /*  start of array  */
    void *top;   /*  end of array (next empty place) */
};

const size_t MIN_DVEC_SIZE = 32;
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/*************************   API FUNCTION DEFINITIONS   ************************/
/*******************************************************************************/
dvec_t *DvecCreate(size_t elm_size, size_t capacity)
{
    size_t dvec_size = MIN_DVEC_SIZE;
    dvec_t *dv;
    assert(0 < capacity);
    assert(0 < elm_size);
    if (capacity > dvec_size)
    {
        while ((dvec_size <<= 1) < capacity)
        {
        }
    }
    if (NULL == (dv = (dvec_t *)malloc(sizeof(dvec_t))))
    {
        return NULL;
    }
    if (NULL == (dv->start = malloc(dvec_size * elm_size)))
    {
        free(dv);
        return NULL;
    }
    dv->capacity = dvec_size;
    dv->element_size = elm_size;
    dv->top = dv->start;

    return dv;
}
/*******************************************************************************/
size_t DVecSize(const dvec_t *dv)
{
    assert(NULL != dv);
    return ((size_t)dv->top - (size_t)dv->start) / dv->element_size;
}
/*******************************************************************************/
size_t DVecCapacity(const dvec_t *dv)
{
    assert(NULL != dv);
    return dv->capacity;
}
/*******************************************************************************/
int DVecPushBack(dvec_t *dv, const void *data)
{
    assert(NULL != data);
    assert(NULL != dv);
    if (DVecSize(dv) == DVecCapacity(dv))
    {
        if (ResizeDvecInnerVector(dv,
                                  DVecCapacity(dv) *
                                      RESIZE_FACTOR) == EXIT_FAILURE)
            return EXIT_FAILURE;
    }
    memcpy(dv->top, data, dv->element_size);
    dv->top = (void *)((size_t)dv->top + dv->element_size);

    return EXIT_SUCCESS;
}
/*******************************************************************************/
void DVecPopBack(dvec_t *dv)
{
    assert(NULL != dv);
    assert(dv->top > dv->start);
    dv->top = (void *)((size_t)dv->top - dv->element_size);
    if (DVecSize(dv) == DVecCapacity(dv) / DECREASE_THRESHOLD &&
        DVecCapacity(dv) > MIN_DVEC_SIZE)
    {
        ResizeDvecInnerVector(dv, DVecCapacity(dv) / RESIZE_FACTOR);
        dv->top = (void *)((size_t)dv->top + dv->element_size);
    }
}
/*******************************************************************************/
void *DVecGetItemAddress(dvec_t *dv, size_t index)
{
    assert(NULL != dv);
    assert(DVecCapacity(dv) > index);
    return (void *)((size_t)dv->start + index * dv->element_size);
}
/*******************************************************************************/
void DvecDestroy(dvec_t *dv)
{
    if (NULL == dv)
        return;
    free(dv->start);
    dv->top = NULL;
    dv->start = NULL;
    free(dv);
}
/*******************************************************************************/
/**********************   END OF API FUNCTION DEFINITIONS   ********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DEFINITIONS   **********************/
/*******************************************************************************/
int ResizeDvecInnerVector(dvec_t *dv, size_t new_capacity)
{
    size_t size = DVecSize(dv);
    if ((dv->start = reallocarray(dv->start, new_capacity,
                                  dv->element_size)) == NULL)
    {
        return EXIT_FAILURE;
    }
    dv->top = (void *)((size_t)dv->start + size * dv->element_size);
    dv->capacity = new_capacity;
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/
/********************   END OF PRIVATE FUNCTION DEFINITIONS   ******************/
/*******************************************************************************/