/********************************************************************************
 * barr.c		                                                                *
 *                                                                              *
 * Implements bit array's API                                                   *
 *                                                                              *
 * Author: Guy Rosen													        *
 * Reviewer: Irad Ratmansky                                                     *
 * 03.06.2020           					    	                            *
 *******************************************************************************/
#include <stdio.h>  /* TO DELETE    */
#include <assert.h> /* assert       */
#include <stdlib.h> /* calloc       */
#include <string.h> /* memmove      */
#include <limits.h> /* ULONG_MAX    */
#include <stdlib.h> /* srand()      */
#include <time.h>   /* time()       */
#include "barr.h"   /* library      */
#include "utils.h"  /* macros       */

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/
uint _BarrInnerArrSize(const barr_t *barr_ptr);
uint GetCountFromCountLutTable(uint byte_value);
void _BarrSwapBits(barr_t *barr_ptr, uint ind1, uint ind2);
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DECLARATIONS   ******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
#define GET_CELL_BY_INDEX(x) ((x) / BITS_IN_WORD)
struct bit_array
{
    ulong *array;
    uint size; /* size in number of bits */
};
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/*************************   API FUNCTION DEFINITIONS   ************************/
/*******************************************************************************/
barr_t *BarrCreate(uint size)
{
    barr_t *new_barr;
    uint new_bar_arr_size;
    assert(size > 0);

    if ((new_barr = (barr_t *)malloc(sizeof(*new_barr))) == NULL)
        return NULL;
    new_barr->size = size;
    new_bar_arr_size = _BarrInnerArrSize(new_barr); /* size in num of bytes */
    if ((new_barr->array =
             calloc(new_bar_arr_size, BYTES_IN_WORD)) == NULL)
        return NULL;

    return new_barr;
}
/*******************************************************************************/
barr_t *BarrCopy(const barr_t *src)
{
    barr_t *src_copy;
    if (NULL == src || (src_copy = BarrCreate(BarrSize(src))) == NULL)
        return NULL;
    memmove(src_copy->array, src->array,
            _BarrInnerArrSize(src) * BYTES_IN_WORD);
    return src_copy;
}
/*******************************************************************************/
uint BarrIsEquale(const barr_t *b1, const barr_t *b2)
{
    uint i, lastCell, flag = 1;

    if (b1 == b2)
        return 1;
    if ((NULL == b1 && NULL != b2) || (NULL == b2 && NULL != b1))
        return 0;
    if (BarrSize(b1) != BarrSize(b2))
        return 0;

    lastCell = _BarrInnerArrSize(b1) - 1;

    for (i = 0; i < lastCell && flag; ++i)
    {
        flag *= (b1->array[i] == b2->array[i]);
    }

    return flag;
}
/*******************************************************************************/
barr_t *BarrGenerate(uint size)
{
    uint i;
    barr_t *barr_ptr = BarrCreate(size);
    if (NULL == barr_ptr)
        return NULL;
    srand(time(NULL));
    for (i = 0; i < size; ++i)
    {
        BarrSetBitValue(barr_ptr, i, rand() & 1);
    }
    return barr_ptr;
}
/*******************************************************************************/
uint BarrSize(const barr_t *barr_ptr)
{
    assert(NULL != barr_ptr);
    return barr_ptr->size;
}
/*******************************************************************************/
void BarrSetAllBitsValue(barr_t *barr_ptr, uint value)
{
    uint arr_size;
    assert(NULL != barr_ptr);
    arr_size = _BarrInnerArrSize(barr_ptr);
    if (value)
    {
        uint bits_to_set_off;
        uint remaining_bits = BarrSize(barr_ptr) % BITS_IN_WORD;
        bits_to_set_off = (remaining_bits) ? BITS_IN_WORD - remaining_bits : 0;
        memset(barr_ptr->array, UCHAR_MAX, (arr_size)*BYTES_IN_WORD);
        barr_ptr->array[arr_size - 1] = ULONG_MAX >> bits_to_set_off;
    }
    else
    {
        memset(barr_ptr->array, 0, arr_size * BYTES_IN_WORD);
    }
}
/*******************************************************************************/
void BarrSetAllBitsOn(barr_t *barr_ptr)
{
    BarrSetAllBitsValue(barr_ptr, 1);
}
/*******************************************************************************/
void BarrSetAllBitsOff(barr_t *barr_ptr)
{
    BarrSetAllBitsValue(barr_ptr, 0);
}
/*******************************************************************************/
void BarrSetBitValue(barr_t *barr_ptr, uint index, uint value)
{
    ulong mask = (ULONG_0_BIT << (index % BITS_IN_WORD));
    ulong *cell_to_set;
    mask = (value) ? mask : ~mask;

    assert(NULL != barr_ptr && BarrSize(barr_ptr) > index);

    cell_to_set = &(barr_ptr->array[GET_CELL_BY_INDEX(index)]);
    *cell_to_set =
        (value) ? (*cell_to_set | mask) : (*cell_to_set & mask);
}
/*******************************************************************************/
void BarrSetBitOn(barr_t *barr_ptr, uint index)
{
    BarrSetBitValue(barr_ptr, index, 1);
}
/*******************************************************************************/
void BarrSetBitOff(barr_t *barr_ptr, uint index)
{
    BarrSetBitValue(barr_ptr, index, 0);
}
/*******************************************************************************/
uint BarrBitIsOn(const barr_t *barr_ptr, uint index)
{
    uint cell_index = GET_CELL_BY_INDEX(index);
    uint bit_index = (index % BITS_IN_WORD);
    const ulong *inner_arr;
    assert(NULL != barr_ptr && BarrSize(barr_ptr) > index);
    inner_arr = barr_ptr->array;
    return ((inner_arr[cell_index] >> bit_index) & ULONG_0_BIT) ? ON : OFF;
}
/*******************************************************************************/
uint BarrBitIsOff(const barr_t *barr_ptr, uint index)
{
    return !BarrBitIsOn(barr_ptr, index);
}
/*******************************************************************************/
void BarrFlipBit(barr_t *barr_ptr, uint index)
{
    assert(NULL != barr_ptr && BarrSize(barr_ptr) > index);
    BarrSetBitValue(barr_ptr, index, !BarrBitIsOn(barr_ptr, index));
}
/*******************************************************************************/
uint BarrCountBitsOn(const barr_t *barr_ptr)
{
    const ulong *inner_arr;
    const uchar *uchar_runner;
    uint inner_arr_size, inner_arr_size_as_char_arr, i, bit_cnt = 0;

    assert(NULL != barr_ptr);
    inner_arr = barr_ptr->array;
    inner_arr_size = _BarrInnerArrSize(barr_ptr);
    inner_arr_size_as_char_arr = inner_arr_size * BYTES_IN_WORD;
    uchar_runner = (const uchar *)inner_arr;
    for (i = 0; i < inner_arr_size_as_char_arr; ++i)
    {
        bit_cnt += GetCountFromCountLutTable(*(uchar_runner + i));
    }
    return bit_cnt;
}
/*******************************************************************************/
uint BarrCountBitsOff(const barr_t *barr_ptr)
{
    assert(NULL != barr_ptr);

    return BarrSize(barr_ptr) - BarrCountBitsOn(barr_ptr);
}
/*******************************************************************************/
void BarrMirror(barr_t *barr_ptr)
{
    uint mid_barr_ind, ind1, ind2, barr_size;
    assert(NULL != barr_ptr);

    barr_size = BarrSize(barr_ptr);
    mid_barr_ind = barr_size >> 1;
    ind1 = mid_barr_ind - 1;
    ind2 = (barr_size & 1) ? (mid_barr_ind + 1) : (mid_barr_ind);
    for (; ind2 < barr_size; --ind1, ++ind2)
    {
        _BarrSwapBits(barr_ptr, ind1, ind2);
    }
}
/*******************************************************************************/
void BarrRotL(barr_t *barr_ptr, size_t steps)
{
    size_t i, k, m;
    size_t barr_size;
    size_t gcd;
    enum state temp;
    assert(NULL != barr_ptr);
    barr_size = BarrSize(barr_ptr);
    steps %= barr_size;
    gcd = GCD(barr_size, steps);
    for (i = 0; i < gcd; ++i)
    {
        temp = BarrBitIsOn(barr_ptr, i);
        k = i;
        m = (k + steps < barr_size) ? (k + steps) : (k + steps - barr_size);
        do
        {
            BarrSetBitValue(barr_ptr, k, BarrBitIsOn(barr_ptr, m));
            k = m;
            m = (k + steps < barr_size) ? (k + steps) : (k + steps - barr_size);
        } while (m != i);
        BarrSetBitValue(barr_ptr, k, temp);
    }
}
/*******************************************************************************/
void BarrRotR(barr_t *barr_ptr, uint steps)
{
    uint equivalent_left_step, barr_size;
    assert(NULL != barr_ptr);
    barr_size = BarrSize(barr_ptr);
    steps %= barr_size;
    equivalent_left_step = barr_size - steps;
    BarrRotL(barr_ptr, equivalent_left_step);
}
/*******************************************************************************/
void BarrLUTMirror(barr_t *barr_ptr);
/*******************************************************************************/
#ifndef NDEBUG
const ulong *BarrGetInnerArray(const barr_t *barr_ptr)
{
    assert(NULL != barr_ptr);
    return barr_ptr->array;
}
/*******************************************************************************/
void BarrPrint(const barr_t *barr_ptr)
{
    UNUSED(barr_ptr);
}
#endif /*NDEBUG*/
/*******************************************************************************/
void BarrDestroy(barr_t *barr_ptr)
{
    free(barr_ptr->array);
    barr_ptr->array = NULL;
    barr_ptr->size = 0;
    free(barr_ptr);
}
/**********************   END OF API FUNCTION DEFINITIONS   ********************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   PRIVATE FUNCTION DEFINITIONS   **********************/
/*******************************************************************************/
uint _BarrInnerArrSize(const barr_t *barr_ptr)
{
    return 1 + GET_CELL_BY_INDEX(BarrSize(barr_ptr) - 1);
}
/*******************************************************************************/
uint GetCountFromCountLutTable(uint byte_value)
{
    static uint count_bits_lut_table[256] = {0};
    static uint initialize_table_flag = 1;

    if (initialize_table_flag)
    {
        uint i, j;
        for (i = 1; i <= UCHAR_MAX; ++i)
        {
            j = i;
            while (j)
            {
                ++count_bits_lut_table[i];
                j &= (j - 1);
            }
        }
        initialize_table_flag = 0;
    }

    return count_bits_lut_table[byte_value];
}
/*******************************************************************************/
void _BarrSwapBits(barr_t *barr_ptr, uint ind1, uint ind2)
{
    enum state ind1_bit_state;
    enum state ind2_bit_state;
    assert(NULL != barr_ptr && BarrSize(barr_ptr) > ind1 &&
           BarrSize(barr_ptr) > ind2);
    ind1_bit_state = BarrBitIsOn(barr_ptr, ind1);
    ind2_bit_state = BarrBitIsOn(barr_ptr, ind2);

    BarrSetBitValue(barr_ptr, ind1, ind2_bit_state);
    BarrSetBitValue(barr_ptr, ind2, ind1_bit_state);
}
/*******************************************************************************/
/********************   END OF PRIVATE FUNCTION DEFINITIONS   ******************/
/*******************************************************************************/