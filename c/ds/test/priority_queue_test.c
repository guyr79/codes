/********************************************************************************
 * priority_queue_test.c		                                                *
 *                                                                              *
 * Implements tests for priority_queue'S API                                    *
 *													                            *
 * Author: Guy Rosen								                            *
 * Reviewer: REVIEWER                                                           *
 * DATE: 15/08/2020         					    	                        *
 ********************************************************************************/
#include <stdio.h>          /* printf       */
#include <stdlib.h>         /* EXIT_SUCCESS */
#include "priority_queue.h" /* library      */
#include "utils.h"          /* RUN_TEST     */

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/

/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DECLARATIONS   ************************/
/*******************************************************************************/
int PQCreateIsEmptyTest(void);
int PQEnqueueDequeuPeekSizeTest(void);
int PQRemoveTest(void);
int PQClearTest(void);
/*
int priority_queue_FUNC_priority_queue5_Test(void);
int priority_queue_FUNC_priority_queue6_Test(void);
int priority_queue_FUNC_priority_queue7_Test(void);
int priority_queue_FUNC_priority_queue8_Test(void);
int priority_queue_FUNC_priority_queue9_Test(void);
int priority_queue_FUNC_priority_queue10_Test(void);
int priority_queue_FUNC_priority_queue11_Test(void);
int priority_queue_FUNC_priority_queue12_Test(void);
int priority_queue_FUNC_priority_queue13_Test(void);
int priority_queue_FUNC_priority_queue14_Test(void);
*/
/*******************************************************************************/
/*******************   END OF TEST FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/
int _TestInit(void);
void _TestEnd(void);
int IntPQCmp(const void *data, const void *sl_data, void *param);
int StrPQCmp(const void *data, const void *sl_data, void *param);
int SetIntPQDataAndBenchArr(pq_t *pq, int *bench_arr);
/*******************************************************************************/
/**********************   PRIVATE FUNCTION DECLARATIONS   **********************/
/*******************************************************************************/

/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/****************   GLOBAL AND STATIC VARIABLES DEFINITIONS   ******************/
/*******************************************************************************/
pq_t *pq_tst = NULL;
int tst_nums[] = {5, 2, 9, 7, 3, 6};
int tst_nums_bench[] = {15, 12, 19, 17, 13, 16};
/*******************************************************************************/
/**************   END OF GLOBAL AND STATIC VARIABLES DEFINITIONS   *************/
/*******************************************************************************/

/*******************************************************************************/
int main(void)
{
    if (EXIT_SUCCESS != _TestInit())
    {
        puts("initialization failed");
        _TestEnd();
        return EXIT_FAILURE;
    }
    RUN_TEST(PQCreateIsEmptyTest);
    RUN_TEST(PQEnqueueDequeuPeekSizeTest);
    RUN_TEST(PQRemoveTest);
    RUN_TEST(PQClearTest);
    _TestEnd();
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DEFINITIONS   *************************/
/*******************************************************************************/
int PQCreateIsEmptyTest(void)
{
    return (PQIsEmpty(pq_tst)) ? EXIT_SUCCESS : EXIT_FAILURE;
}
/*******************************************************************************/
int PQEnqueueDequeuPeekSizeTest(void)
{
    size_t i = 0;
    int *bench_arr = calloc(ARR_SIZE(tst_nums), sizeof(int));
    if (NULL == bench_arr)
        return EXIT_FAILURE;
    if (EXIT_FAILURE == SetIntPQDataAndBenchArr(pq_tst, bench_arr))
        return EXIT_FAILURE;
    for (i = 0; i < ARR_SIZE(tst_nums); ++i)
    {
        if (PQSize(pq_tst) != ARR_SIZE(tst_nums) - i)
            return EXIT_FAILURE;
        if (*(int *)PQPeek(pq_tst) != bench_arr[i])
            return EXIT_FAILURE;
        PQDeQueue(pq_tst);
    }
    if (!PQIsEmpty(pq_tst))
    {
        return EXIT_FAILURE;
    }
    free(bench_arr);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int PQRemoveTest(void)
{
    size_t i = 0;
    void *data = NULL;
    int *bench_arr = calloc(ARR_SIZE(tst_nums), sizeof(int));
    if (NULL == bench_arr)
        return EXIT_FAILURE;
    if (EXIT_FAILURE == SetIntPQDataAndBenchArr(pq_tst, bench_arr))
        return EXIT_FAILURE;
    for (; i < ARR_SIZE(tst_nums); ++i)
    {
        size_t k = 0, flag = 0;
        if (ARR_SIZE(tst_nums) - i != PQSize(pq_tst))
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
        if (NULL != PQRemove(pq_tst, IntPQCmp, &tst_nums_bench[i]))
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
        if (NULL == (data = PQRemove(pq_tst, IntPQCmp, &tst_nums[i])))
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
        for (; k < ARR_SIZE(tst_nums) && flag == 0; ++k)
        {
            flag = (*(int *)data == bench_arr[k]);
        }
        if (0 == flag)
        {
            free(bench_arr);
            return EXIT_FAILURE;
        }
    }
    free(bench_arr);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int PQClearTest(void)
{
    int *bench_arr = calloc(ARR_SIZE(tst_nums), sizeof(int));
    if (NULL == bench_arr)
        return EXIT_FAILURE;
    if (EXIT_FAILURE == SetIntPQDataAndBenchArr(pq_tst, bench_arr))
    {
        free(bench_arr);
        return EXIT_FAILURE;
    }
    if (ARR_SIZE(tst_nums) != PQSize(pq_tst))
    {
        free(bench_arr);
        return EXIT_FAILURE;
    }
    PQClear(pq_tst);
    if (PQSize(pq_tst) != 0)
    {
        free(bench_arr);
        return EXIT_FAILURE;
    }
    if (EXIT_FAILURE == SetIntPQDataAndBenchArr(pq_tst, bench_arr))
    {
        free(bench_arr);
        return EXIT_FAILURE;
    }
    free(bench_arr);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/********************   END OF TEST FUNCTION DEFINITIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DEFINITIONS   ***********************/
/*******************************************************************************/
int _TestInit(void)
{
    return (NULL == (pq_tst = PQCreate(IntPQCmp, NULL)))
               ? EXIT_FAILURE
               : EXIT_SUCCESS;
}
/*******************************************************************************/
void _TestEnd(void)
{
    PQDestroy(pq_tst);
}
/*******************************************************************************/
int IntPQCmp(const void *data, const void *sl_data, void *param)
{
    UNUSED(param);
    return IntQsortFunc(data, sl_data);
}
/*******************************************************************************/
int SetIntPQDataAndBenchArr(pq_t *pq, int *bench_arr)
{
    size_t i = 0;
    for (; i < ARR_SIZE(tst_nums); ++i)
    {
        if (0 == PQEnQueue(pq, &tst_nums[i]))
        {
            return EXIT_FAILURE;
        }
        bench_arr[i] = tst_nums[i];
    }
    qsort(bench_arr, ARR_SIZE(tst_nums), sizeof(int), IntQsortFunc);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DEFINITIONS   *******************/
/*******************************************************************************/