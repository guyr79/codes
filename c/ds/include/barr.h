/********************************************************************************
 * barr.h		                                                                *
 *                                                                              *
 * Declares bit array's API                                                     *
 *													                            *
 * Author: Guy Rosen													        *
 * Reviewer: Irad Ratmansky                                                     *
 * 03.06.2020           					    	                            *
 *******************************************************************************/
#ifndef BARR_H
#define BARR_H

#include "utils.h"
/*******************************************************************************/
/****************************   TYPE DECLARATIONS   ****************************/
/*******************************************************************************/
/* barr_t represents bit array */
typedef struct bit_array barr_t;
enum state
{
    OFF,
    ON
};
/*******************************************************************************/
/************************    END OF TYPE DECLARATIONS    ***********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*******************************************************************************/

/*  Description:    creates a new bit_array of size SIZE, 
*                   of which its members initialized to 0 
*   Parameters:     size:   Represents size of the new created bit_array
*   Return value:   pointer to new created bit_array 
*   Error Value:    upon error returns NULL */
barr_t *BarrCreate(uint size);
/*  Description:    copies SRC to a new bit_array  
*   Parameters:     src:   bit_array to copy. 
*   Return value:   pointer to new created bit_array
*   Error Value:    upon error returns NULL */
barr_t *BarrCopy(const barr_t *src);
/*  Description:    Compares between two bit_arrays  
*   Parameters:     b1, b2:   bit_arrays to compare 
    Return Value*:  1 if equale, 0 otherwise */
uint BarrIsEquale(const barr_t *b1, const barr_t *b2);
/*  Description:    generates a new barr_ptr of size SIZE with random values  
*   Parameters:     size:   bit_array to question. Must not be NULL */
barr_t *BarrGenerate(uint size);
/*  Description:    returns barr_ptr array's size  
*   Parameters:     Represents size of the new created bit_array */
uint BarrSize(const barr_t *barr_ptr);
/*  Description:    set all bits in barr_ptr to VALUE
    Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL
*                   value:      value to be set per bit.
                                If value > 1 bit is set to 1 */
void BarrSetAllBitsValue(barr_t *barr_ptr, uint value);
/*  Description:    set all bits in barr_ptr to on
    Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL */
void BarrSetAllBitsOn(barr_t *barr_ptr);
/*  Description:    set all bits in barr_ptr to on
    Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL */
void BarrSetAllBitsOff(barr_t *barr_ptr);
/*  Description:    sets index bit to VALUE  
*   Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL
*                   index:      bit to manipulate. index < barr_ptr->size 
*                   value:      value to be set for bit.
*                               If value > 1 bit is set to 1 */
void BarrSetBitValue(barr_t *barr_ptr, uint index, uint value);
/*  Description:    sets index bit on  
*   Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL
*                   index:      bit to manipulate. index < barr_ptr->size */
void BarrSetBitOn(barr_t *barr_ptr, uint index);
/*  Description:    sets index bit off  
*   Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL
*                   index:      bit to manipulate. index < barr_ptr->size */
void BarrSetBitOff(barr_t *barr_ptr, uint index);
/*  Description:    check if index bit is on  
*   Parameters:     barr_ptr:   bit_array to check. Must not be NULL
*                   index:      bit to check. index < barr_ptr->size */
uint BarrBitIsOn(const barr_t *barr_ptr, uint index);
/*  Description:    check if index bit is off  
*   Parameters:     barr_ptr:   bit_array to check. Must not be NULL
*                   index:      bit to check. index < barr_ptr->size */
uint BarrBitIsOff(const barr_t *barr_ptr, uint index);
/*  Description:    flips index bit state  
*   Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL
*                   index:      bit to manipulate. index < barr_ptr->size */
void BarrFlipBit(barr_t *barr_ptr, uint index);
/*  Description:    counts all bits in ON state  
*   Parameters:     barr_ptr:   bit_array to investigate. Must not be NULL */
uint BarrCountBitsOn(const barr_t *barr_ptr);
/*  Description:    counts all bits in OFF state  
*   Parameters:     barr_ptr:   bit_array to investigate. Must not be NULL */
uint BarrCountBitsOff(const barr_t *barr_ptr);
/*  Description:    mirrors left and right side using BARR_PTR's mid_point
*                   as anchore
*   Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL */
void BarrMirror(barr_t *barr_ptr);
/*  Description:    rotates BARR_PTR to the left STEPS times
*   Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL */
void BarrRotL(barr_t *barr_ptr, long steps);
/*  Description:    rotates BARR_PTR to the right STEPS times
*   Parameters:     barr_ptr:   bit_array to manipulate. Must not be NULL */
void BarrRotR(barr_t *barr_ptr, uint steps);
#ifndef NDEBUG
const ulong *BarrGetInnerArray(const barr_t *barr_ptr);
#endif /*NDEBUG*/
/*  Description:    Frees BARR_PTR allocated memory
*   Parameters:     barr_ptr:   bit_array to free */
void BarrDestroy(barr_t *barr_ptr);
#endif
/*******************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/