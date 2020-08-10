/********************************************************************************
 * circ_buf_test.c		                                                        *
 *                                                                              *
 * Implements tests for circ_buf'S API                                          *
 *													                            *
 * Author: Guy Rosen								                            *
 * Reviewer: REVIEWER                                                           *
 * 02/07/2020           					    	                            *
 ********************************************************************************/
#include <stdio.h>    /* printf       */
#include <stdlib.h>   /* EXIT_SUCCESS */
#include <string.h>   /* memcmp       */
#include "circ_buf.h" /* library      */
#include "utils.h"    /* RUN_TEST     */

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
#define NUM_OF_CB (3)
#define ALLOC_MULT ((size_t)10)
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DECLARATIONS   ************************/
/*******************************************************************************/
int CBCreateTest(void);
int CBReadWriteTest(void);
/*
int circ_buf_FUNC_circ_buf3_Test(void);
int circ_buf_FUNC_circ_buf4_Test(void);
int circ_buf_FUNC_circ_buf5_Test(void);
int circ_buf_FUNC_circ_buf6_Test(void);
int circ_buf_FUNC_circ_buf7_Test(void);
int circ_buf_FUNC_circ_buf8_Test(void);
int circ_buf_FUNC_circ_buf9_Test(void);
int circ_buf_FUNC_circ_buf10_Test(void);
int circ_buf_FUNC_circ_buf11_Test(void);
int circ_buf_FUNC_circ_buf12_Test(void);
int circ_buf_FUNC_circ_buf13_Test(void);
int circ_buf_FUNC_circ_buf14_Test(void);
*/
/*******************************************************************************/
/*******************   END OF TEST FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DECLARATIONS   **********************/
/*******************************************************************************/
int _TestInit(void);
void _TestEnd(void);
/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/****************   GLOBAL AND STATIC VARIABLES DEFINITIONS   ******************/
/*******************************************************************************/
cbuf_t *cbs[NUM_OF_CB] = {NULL};
/*******************************************************************************/
/**************   END OF GLOBAL AND STATIC VARIABLES DEFINITIONS   *************/
/*******************************************************************************/

/*******************************************************************************/
int main(void)
{
    if (EXIT_SUCCESS != _TestInit())
    {
        puts("initialization failed");
        return EXIT_FAILURE;
    }
    RUN_TEST(CBCreateTest);
    RUN_TEST(CBReadWriteTest);
    /*
    RUN_TEST(circ_buf_FUNC_circ_buf3_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf4_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf5_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf6_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf7_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf8_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf9_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf10_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf11_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf12_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf13_TEST);
    RUN_TEST(circ_buf_FUNC_circ_buf14_TEST);*/
    _TestEnd();
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DEFINITIONS   *************************/
/*******************************************************************************/
int CBCreateTest(void)
{
    cbuf_t *copies[NUM_OF_CB] = {NULL};
    int i = 0, j = 0;
    for (; i < NUM_OF_CB; ++i)
    {
        copies[i] = CBCopy(cbs[i]);
        if (NULL == copies[i])
        {
            for (; j < i; j++)
                CBDestroy(copies[j]);
            puts("failure due to memory allocation problem. Not test logic");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < NUM_OF_CB; ++i)
    {
        if (CBGetCapacity(cbs[i]) != (i + 1) * ALLOC_MULT)
        {
            for (j = 0; j < NUM_OF_CB; j++)
                CBDestroy(copies[j]);
            return EXIT_FAILURE;
        }
        if (CBGetFreeSpace(cbs[i]) != (i + 1) * ALLOC_MULT)
        {
            for (j = 0; j < NUM_OF_CB; j++)
                CBDestroy(copies[j]);
            return EXIT_FAILURE;
        }
        if (CBIsEmpty(cbs[i]) != 1)
        {
            for (j = 0; j < NUM_OF_CB; j++)
                CBDestroy(copies[j]);
            return EXIT_FAILURE;
        }
        if (!CBEquals(copies[i], cbs[i]))
        {
            for (j = 0; j < NUM_OF_CB; j++)
                CBDestroy(copies[j]);
            return EXIT_FAILURE;
        }
    }

    for (j = 0; j < NUM_OF_CB; j++)
        CBDestroy(copies[j]);

    return EXIT_SUCCESS;
}
/*******************************************************************************/
int CBReadWriteTest(void)
{
    char read_from[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    char write_to[37] = {0};

    if (CBRead(cbs[1], read_from, 0) != 0)
        return EXIT_FAILURE;
    if (CBRead(cbs[1], read_from, 26) != 2 * ALLOC_MULT)
        return EXIT_FAILURE;
    if (CBRead(cbs[1], read_from, 26) != -1)
        return EXIT_FAILURE;
    if (CBWrite(cbs[1], write_to, 15) != 15)
        return EXIT_FAILURE;
    if (CBWrite(cbs[1], write_to + 15, 15) != 5)
        return EXIT_FAILURE;
    if (CBWrite(cbs[1], write_to, 15) != -1)
        return EXIT_FAILURE;
    if (memcmp("abcdefghijklmnopqrst", write_to, 2 * ALLOC_MULT + 1))
        return EXIT_FAILURE;
    if (CBRead(cbs[1], read_from + 20, 16) != 16)
        return EXIT_FAILURE;
    if (CBWrite(cbs[1], write_to + 20, 26) != 16)
        return EXIT_FAILURE;
    if (memcmp(read_from, write_to, 37))
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/*int circ_buf_FUNC_circ_buf3_Test(void)
{

}
/*******************************************************************************/
/*int circ_buf_FUNC_circ_buf4_Test(void)
{

}
/*******************************************************************************/
/*int circ_buf_FUNC_circ_buf5_Test(void)
{

}
/*******************************************************************************/
/*int circ_buf_FUNC_circ_buf6_Test(void)
{

}
/*******************************************************************************/
/********************   END OF TEST FUNCTION DEFINITIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DEFINITIONS   ***********************/
/*******************************************************************************/
int _TestInit(void)
{
    int i = 0;
    for (; i < NUM_OF_CB; ++i)
    {
        cbs[i] = CBCreate(ALLOC_MULT * (i + 1));
        if (NULL == cbs[i])
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
void _TestEnd(void)
{
    int i = 0;
    for (; i < NUM_OF_CB; ++i)
    {
        CBDestroy(cbs[i]);
    }
}
/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DEFINITIONS   *******************/
/*******************************************************************************/