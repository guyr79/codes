/********************************************************************************
 * barr_test.c		                                                            *
 *                                                                              *
 * Implements tests for bit array' API                                          *
 *													                            *
 * Author: Guy Rosen								                            *
 * Reviewer: Irad Ratmansky                                                     *
 * 03.06.2020           					    	                            *
 ********************************************************************************/
#include <stdio.h>  /* printf       */
#include <limits.h> /* ULONG_MAX    */
#include <string.h> /* memcmp       */
#include "barr.h"   /* library      */
#include "utils.h"  /* RUN_TEST     */

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
#define BARR_TEST_SIZE ((uint)3155512)
#define GET_CELL_BY_INDEX(x) ((x) / BITS_IN_WORD)
typedef void (*set_all_func)(barr_t *barr_type);
typedef uint (*check_state_func)(const barr_t *barr_type, uint index);
typedef struct
{
    barr_t *barr_ptr;
    uint flag;
    uint index;
    uint increment_value;
    uint current_cell;
    uint index_mod_bits_in_word;
    ulong benchmark;
    const ulong *inner_arr;
} set_test_params;

typedef struct
{
    set_all_func set_all_funcs[2];
    check_state_func check_state_funcs[2];
} check_funcs;
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DECLARATIONS   ************************/
/*******************************************************************************/
int BarrCreateTest(void);
int BarrCopyTest(void);
int BarrSizeTest(void);
int BarrSetAllBitsOnTest(void);
int BarrSetAllBitsOffTest(void);
int BarrSetBitOnTest(void);
int BarrSetBitOffTest(void);
int BarrBitIsOnTest(void);
int BarrBitIsOffTest(void);
int BarrCountBitsOnTest(void);
int BarrCountBitsOffTest(void);
int BarrMirrorTest(void);
int BarrRotLTest(void);
int BarrRotRTest(void);
/*******************************************************************************/
/*******************   END OF TEST FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DECLARATIONS   **********************/
/*******************************************************************************/
int BarrSetBitTestHelpFunc(barr_t *barr_ptr,
                           void (*TestLogicFunc)(set_test_params *params));
void TestLogicFuncSetBitOn(set_test_params *params);
void TestLogicFuncSetBitOff(set_test_params *params);

int BarrBitStateTestHelpFunc(enum state st);
int BarrCountBitsTestsHelpFunc(enum state st);
/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
int main(void)
{
    RUN_TEST(BarrCreateTest);
    RUN_TEST(BarrCopyTest);
    RUN_TEST(BarrSizeTest);
    RUN_TEST(BarrSetAllBitsOnTest);
    RUN_TEST(BarrSetAllBitsOffTest);
    RUN_TEST(BarrSetBitOnTest);
    RUN_TEST(BarrSetBitOffTest);
    RUN_TEST(BarrBitIsOnTest);
    RUN_TEST(BarrBitIsOffTest);
    RUN_TEST(BarrCountBitsOnTest);
    RUN_TEST(BarrCountBitsOffTest);
    RUN_TEST(BarrMirrorTest);
    RUN_TEST(BarrRotLTest);
    RUN_TEST(BarrRotRTest);
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DEFINITIONS   *************************/
/*******************************************************************************/
int BarrCreateTest(void)
{
    uint return_value = EXIT_SUCCESS;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    if (barr_ptr == NULL && BarrSize(barr_ptr) != BARR_TEST_SIZE)
    {
        return_value = EXIT_FAILURE;
    }
    BarrDestroy(barr_ptr);
    return return_value;
}
/*******************************************************************************/
int BarrCopyTest(void)
{
    barr_t *barr_ptr, *copy_barr_ptr;
    uint flag;
    barr_ptr = BarrGenerate(BARR_TEST_SIZE);
    copy_barr_ptr = BarrCopy(barr_ptr);

    flag = (BarrIsEquale(barr_ptr, copy_barr_ptr)) ? EXIT_SUCCESS : EXIT_FAILURE;
    BarrDestroy(barr_ptr);
    BarrDestroy(copy_barr_ptr);
    return flag;
}
/*******************************************************************************/
int BarrSizeTest(void)
{
    uint r_val;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    r_val = (BarrSize(barr_ptr) == BARR_TEST_SIZE) ? EXIT_SUCCESS : EXIT_FAILURE;
    BarrDestroy(barr_ptr);
    return r_val;
}
/*******************************************************************************/
int BarrSetBitOnTest(void)
{
    uint r_val;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    r_val = BarrSetBitTestHelpFunc(barr_ptr, TestLogicFuncSetBitOn);
    BarrDestroy(barr_ptr);
    return r_val;
}
/*******************************************************************************/
int BarrSetBitOffTest(void)
{
    uint r_val;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    BarrSetAllBitsOn(barr_ptr);
    r_val = BarrSetBitTestHelpFunc(barr_ptr, TestLogicFuncSetBitOff);
    BarrDestroy(barr_ptr);
    return r_val;
}
/*******************************************************************************/
int BarrSetAllBitsOnTest(void)
{
    uint i, r_val;
    uint arr_size = 1 + GET_CELL_BY_INDEX(BARR_TEST_SIZE - 1);
    barr_t *benchmark_barr_ptr;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    benchmark_barr_ptr = BarrCreate(BARR_TEST_SIZE);

    BarrSetAllBitsOn(barr_ptr);
    for (i = 0; i < BARR_TEST_SIZE; ++i)
    {
        BarrSetBitOn(benchmark_barr_ptr, i);
    }

    r_val = memcmp(BarrGetInnerArray(barr_ptr),
                   BarrGetInnerArray(benchmark_barr_ptr),
                   arr_size * BYTES_IN_WORD)
                ? EXIT_FAILURE
                : EXIT_SUCCESS;
    BarrDestroy(barr_ptr);
    BarrDestroy(benchmark_barr_ptr);
    return r_val;
}
/*******************************************************************************/
int BarrSetAllBitsOffTest(void)
{
    uint i, r_val;
    uint arr_size = 1 + GET_CELL_BY_INDEX(BARR_TEST_SIZE - 1);
    barr_t *benchmark_barr_ptr;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    benchmark_barr_ptr = BarrCreate(BARR_TEST_SIZE);

    BarrSetAllBitsOn(barr_ptr);
    BarrSetAllBitsOn(benchmark_barr_ptr);

    BarrSetAllBitsOff(barr_ptr);
    for (i = 0; i < BARR_TEST_SIZE; ++i)
    {
        BarrSetBitOff(benchmark_barr_ptr, i);
    }

    r_val = memcmp(BarrGetInnerArray(barr_ptr),
                   BarrGetInnerArray(benchmark_barr_ptr),
                   arr_size * BYTES_IN_WORD)
                ? EXIT_FAILURE
                : EXIT_SUCCESS;

    BarrDestroy(barr_ptr);
    BarrDestroy(benchmark_barr_ptr);

    return r_val;
}
/*******************************************************************************/
int BarrBitIsOnTest(void)
{
    return BarrBitStateTestHelpFunc(ON);
}
/*******************************************************************************/
int BarrBitIsOffTest(void)
{
    return BarrBitStateTestHelpFunc(OFF);
}
/*******************************************************************************/
int BarrCountBitsOnTest(void)
{
    return BarrCountBitsTestsHelpFunc(ON);
}
/*******************************************************************************/
int BarrCountBitsOffTest(void)
{
    return BarrCountBitsTestsHelpFunc(OFF);
}
/*******************************************************************************/
int BarrMirrorTest(void)
{
    barr_t *barr_ptr, *m_barr_ptr;
    uint i_src, i_m, flag = 1;
    barr_ptr = BarrGenerate(BARR_TEST_SIZE);
    m_barr_ptr = BarrCopy(barr_ptr);

    BarrMirror(m_barr_ptr);
    i_src = 0;
    i_m = BARR_TEST_SIZE - 1;
    for (; i_src < BARR_TEST_SIZE && flag; ++i_src, --i_m)
    {
        flag *= (BarrBitIsOn(barr_ptr, i_src) == BarrBitIsOn(m_barr_ptr, i_m));
    }
    BarrDestroy(barr_ptr);
    BarrDestroy(m_barr_ptr);
    return (flag) ? EXIT_SUCCESS : EXIT_FAILURE;
}
/*******************************************************************************/
int BarrRotLTest(void)
{
    barr_t *barr_ptr, *benchmark;
    uint steps = 660341, i_ba, i_be;
    uint act_steps = steps % BARR_TEST_SIZE;
    uint r_val;
    barr_ptr = BarrGenerate(BARR_TEST_SIZE);
    benchmark = BarrCreate(BARR_TEST_SIZE);

    for (i_be = 0, i_ba = act_steps; i_ba < BARR_TEST_SIZE; ++i_ba, ++i_be)
    {
        BarrSetBitValue(benchmark, i_be, BarrBitIsOn(barr_ptr, i_ba));
    }

    for (i_ba = 0; i_be < BARR_TEST_SIZE; ++i_ba, ++i_be)
    {
        BarrSetBitValue(benchmark, i_be, BarrBitIsOn(barr_ptr, i_ba));
    }

    BarrRotL(barr_ptr, steps);
    r_val = (BarrIsEquale(barr_ptr, benchmark)) ? EXIT_SUCCESS : EXIT_FAILURE;
    BarrDestroy(barr_ptr);
    BarrDestroy(benchmark);
    return r_val;
}
/*******************************************************************************/
int BarrRotRTest(void)
{
    barr_t *barr_ptr, *benchmark;
    uint steps = 660341, i_ba, i_be;
    uint act_steps = steps % BARR_TEST_SIZE;
    uint r_val;
    barr_ptr = BarrGenerate(BARR_TEST_SIZE);
    benchmark = BarrCreate(BARR_TEST_SIZE);

    for (i_ba = 0, i_be = act_steps;
         i_be < BARR_TEST_SIZE; ++i_ba, ++i_be)
    {
        BarrSetBitValue(benchmark, i_be, BarrBitIsOn(barr_ptr, i_ba));
    }

    for (i_be = 0; i_ba < BARR_TEST_SIZE; ++i_ba, ++i_be)
    {
        BarrSetBitValue(benchmark, i_be, BarrBitIsOn(barr_ptr, i_ba));
    }

    BarrRotR(barr_ptr, steps);
    r_val = (BarrIsEquale(barr_ptr, benchmark)) ? EXIT_SUCCESS : EXIT_FAILURE;
    BarrDestroy(barr_ptr);
    BarrDestroy(benchmark);
    return r_val;
}
/*******************************************************************************/
/********************   END OF TEST FUNCTION DEFINITIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DEFINITIONS   ***********************/
/*******************************************************************************/
int BarrSetBitTestHelpFunc(barr_t *barr_ptr,
                           void (*TestLogicFunc)(set_test_params *params))
{
    uint increment_value = 3;
    uint barr_size = BarrSize(barr_ptr);
    set_test_params params;
    params.barr_ptr = barr_ptr;
    params.flag = 1;
    params.index = 0;
    params.increment_value = increment_value;
    params.current_cell = 0;
    params.index_mod_bits_in_word = 0;
    params.benchmark = 0;
    params.inner_arr = BarrGetInnerArray(barr_ptr);

    for (; params.index < barr_size && params.flag; params.index += increment_value)
    {
        params.current_cell = GET_CELL_BY_INDEX(params.index);
        params.index_mod_bits_in_word = params.index % BITS_IN_WORD;
        TestLogicFunc(&params);
    }
    return (params.flag) ? EXIT_SUCCESS : EXIT_FAILURE;
}
/*******************************************************************************/
void TestLogicFuncSetBitOn(set_test_params *params)
{
    BarrSetBitOn(params->barr_ptr, params->index);
    params->flag *=
        !(params->benchmark == params->inner_arr[params->current_cell]);
    params->benchmark |= ULONG_0_BIT << params->index_mod_bits_in_word;
    params->flag *=
        (params->benchmark == params->inner_arr[params->current_cell]);
    params->benchmark *=
        (BITS_IN_WORD > params->index_mod_bits_in_word +
                            params->increment_value);
}
/*******************************************************************************/
void TestLogicFuncSetBitOff(set_test_params *params)
{
    uint next_cell = GET_CELL_BY_INDEX(params->index + params->increment_value);
    uint last_cell_index = GET_CELL_BY_INDEX(BarrSize(params->barr_ptr) - 1);
    params->benchmark = (params->benchmark)
                            ? params->benchmark
                            : params->inner_arr[0];
    BarrSetBitOff(params->barr_ptr, params->index);
    params->flag *=
        !(params->benchmark == params->inner_arr[params->current_cell]);
    params->benchmark &= ~(ULONG_0_BIT << params->index_mod_bits_in_word);
    params->flag *=
        (params->benchmark == params->inner_arr[params->current_cell]);
    if ((next_cell <= last_cell_index) && (next_cell > params->current_cell))
    {
        params->benchmark = params->inner_arr[next_cell];
    }
}
/*******************************************************************************/
int BarrBitStateTestHelpFunc(enum state st)
{
    check_funcs funcs = {{BarrSetAllBitsOff, BarrSetAllBitsOn},
                         {BarrBitIsOff, BarrBitIsOn}};
    uint index, flag = 1;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    funcs.set_all_funcs[st](barr_ptr);
    for (index = 0; (index < BARR_TEST_SIZE) && flag; ++index)
    {
        flag *= funcs.check_state_funcs[st](barr_ptr, index);
    }
    if (!flag)
    {
        return EXIT_FAILURE;
    }
    funcs.set_all_funcs[!st](barr_ptr);
    for (index = 0; (index < BARR_TEST_SIZE) && flag; ++index)
    {
        flag *= funcs.check_state_funcs[!st](barr_ptr, index);
    }
    BarrDestroy(barr_ptr);
    return (flag) ? EXIT_SUCCESS : EXIT_FAILURE;
}
/*******************************************************************************/
int BarrCountBitsTestsHelpFunc(enum state st)
{
    uint i, stop1 = 100, stop2 = 1000, inc1 = 1, inc7 = 7, inc13 = 13;
    uint expected_cnt = 0, r_val;
    barr_t *barr_ptr = BarrCreate(BARR_TEST_SIZE);
    uint (*count_func)(const barr_t *) = BarrCountBitsOn;
    for (i = 0; i < stop1; i += inc1)
    {
        BarrSetBitOn(barr_ptr, i);
        ++expected_cnt;
    }
    for (; i < stop2; i += inc7)
    {
        BarrSetBitOn(barr_ptr, i);
        ++expected_cnt;
    }
    for (; i < BARR_TEST_SIZE; i += inc13)
    {
        BarrSetBitOn(barr_ptr, i);
        ++expected_cnt;
    }

    if (st == OFF)
    {
        expected_cnt = BARR_TEST_SIZE - expected_cnt;
        count_func = BarrCountBitsOff;
    }

    r_val = (count_func(barr_ptr) == expected_cnt) ? EXIT_SUCCESS : EXIT_FAILURE;
    BarrDestroy(barr_ptr);
    return r_val;
}
/*******************************************************************************/
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DEFINITIONS   *******************/
/*******************************************************************************/