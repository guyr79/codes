/********************************************************************************
 * stack_test.c		                                                            *
 *                                                                              *
 * Implements tests for stack'S API                                             *
 *													                            *
 * Author: Guy Rosen								                            *
 * Reviewer: REVIEWER                                                           *
 * 30.06.2020           					    	                            *
 ********************************************************************************/
#include <stdio.h>  /* printf       */
#include <stdlib.h> /* EXIT_SUCCESS/FAILURE */
#include <assert.h> /* assert   */
#include "stack.h"  /* library      */
#include "utils.h"  /* RUN_TEST     */

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
#define NUM_OF_STACKS_IN_TEST (6)
#define CAPACITY_MULT (5)
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DECLARATIONS   ************************/
/*******************************************************************************/
int StackCreateTest(void);
int StackPushTest(void);
int StackPopTest(void);
int StackResizeTest(void);
/*
int Stack_Func5_Test(void);
int Stack_Func6_Test(void);
int Stack_Func7_Test(void);
int Stack_Func8_Test(void);
int Stack_Func9_Test(void);
int Stack_Func10_Test(void);
int Stack_Func11_Test(void);
int Stack_Func12_Test(void);
int Stack_Func13_Test(void);
int Stack_Func14_Test(void);
*/
/*******************************************************************************/
/*******************   END OF TEST FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DECLARATIONS   **********************/
/*******************************************************************************/
int init();
void end();
/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/*****************   GLOBAL AND STATIC VARIABLES DEFINITIONS   *****************/
/*******************************************************************************/
stack_t *stacks[NUM_OF_STACKS_IN_TEST] = {NULL};
int j, j_compare;
char c = 'a', c_compare;
double d = 1.23, d_compare;
/*******************************************************************************/
/*************   END OF GLOBAL AND STATIC VARIABLES DEFINITIONS   **************/
/*******************************************************************************/

/*******************************************************************************/
int main(void)
{
    if (EXIT_SUCCESS != init())
    {
        puts("initialization failed");
        return EXIT_FAILURE;
    }
    RUN_TEST(StackCreateTest);
    RUN_TEST(StackPushTest);
    RUN_TEST(StackPopTest);
    RUN_TEST(StackResizeTest);
    /*
    RUN_TEST(Stack_Func5_TEST);
    RUN_TEST(Stack_Func6_TEST);
    RUN_TEST(Stack_Func7_TEST);
    RUN_TEST(Stack_Func8_TEST);
    RUN_TEST(Stack_Func9_TEST);
    RUN_TEST(Stack_Func10_TEST);
    RUN_TEST(Stack_Func11_TEST);
    RUN_TEST(Stack_Func12_TEST);
    RUN_TEST(Stack_Func13_TEST);
    RUN_TEST(Stack_Func14_TEST);
*/
    end();
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DEFINITIONS   *************************/
/*******************************************************************************/
int StackCreateTest(void)
{
    size_t i;
    for (i = 0; i < (NUM_OF_STACKS_IN_TEST >> 1); ++i)
    {
        if (StackSize(stacks[i]) != 0)
            return EXIT_FAILURE;
        if (StackCapacity(stacks[i]) != (i + 1) * CAPACITY_MULT)
            return EXIT_FAILURE;
        if (StackIsEmpty(stacks[i]) != 1)
            return EXIT_FAILURE;
        if (StackSize(stacks[i + 3]) != 0)
            return EXIT_FAILURE;
        if (StackCapacity(stacks[i + 3]) != (i + 1) * CAPACITY_MULT)
            return EXIT_FAILURE;
        if (StackIsEmpty(stacks[i + 3]) != 1)
            return EXIT_FAILURE;
        if (StackEquals(stacks[i], stacks[i + 3]) != 1)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int StackPushTest(void)
{
    int i;
    stack_t *b1, *b2, *b3;
    --c;
    for (i = 0; i < CAPACITY_MULT; ++i)
    {
        ++c;
        if (StackPush(stacks[0], &c) != EXIT_SUCCESS)
            return EXIT_FAILURE;
        StackTop(stacks[0], &c_compare);
        if (c_compare != c)
            return EXIT_FAILURE;
    }
    j = -1;
    for (i = 0; i < CAPACITY_MULT * 2; ++i)
    {
        ++j;
        if (StackPush(stacks[1], &j) != EXIT_SUCCESS)
            return EXIT_FAILURE;
        StackTop(stacks[1], &j_compare);
        if (j_compare != i)
            return EXIT_FAILURE;
    }

    for (i = 0; i < CAPACITY_MULT * 3; ++i)
    {
        d = d + 1;
        if (StackPush(stacks[2], &d) != EXIT_SUCCESS)
            return EXIT_FAILURE;
        StackTop(stacks[2], &d_compare);
        if (d_compare != d)
            return EXIT_FAILURE;
    }

    b1 = StackCopy(stacks[0]);
    if (!StackEquals(b1, stacks[0]))
        return EXIT_FAILURE;

    b2 = StackCopy(stacks[1]);
    if (!StackEquals(stacks[1], b2))
        return EXIT_FAILURE;

    b3 = StackCopy(stacks[2]);
    if (!StackEquals(b3, stacks[2]))
        return EXIT_FAILURE;

    if (StackPush(stacks[0], &c) != EXIT_FAILURE)
        return EXIT_FAILURE;
    if (StackPush(stacks[1], &i) != EXIT_FAILURE)
        return EXIT_FAILURE;
    if (StackPush(stacks[2], &d) != EXIT_FAILURE)
        return EXIT_FAILURE;

    if (StackPush(b1, &c) != EXIT_FAILURE)
        return EXIT_FAILURE;
    if (StackPush(b2, &i) != EXIT_FAILURE)
        return EXIT_FAILURE;
    if (StackPush(b3, &d) != EXIT_FAILURE)
        return EXIT_FAILURE;

    free(b1);
    free(b2);
    free(b3);
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int StackPopTest(void)
{
    while (!(StackSize(stacks[0]) == 1))
    {
        --c;
        StackPop(stacks[0]);
        StackTop(stacks[0], &c_compare);
        if (c != c_compare)
            return EXIT_FAILURE;
    }
    while (!(StackSize(stacks[1]) == 1))
    {
        --j;
        StackPop(stacks[1]);
        StackTop(stacks[1], &j_compare);
        if (j != j_compare)
            return EXIT_FAILURE;
    }
    while (!(StackSize(stacks[2]) == 1))
    {
        d = d - 1;
        StackPop(stacks[2]);
        StackTop(stacks[2], &d_compare);
        if (d - d_compare > 0.000001)
            return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int StackResizeTest(void)
{
    int k = 0;
    StackPop(stacks[2]);
    assert(StackIsEmpty(stacks[2]));
    StackPush(stacks[2], &d);
    StackPush(stacks[2], &d);
    if (StackSize(stacks[2]) != 2)
        return EXIT_FAILURE;
    StackResize(&stacks[2], 30);
    if (StackCapacity(stacks[2]) != 30)
        return EXIT_FAILURE;
    if (StackSize(stacks[2]) != 2)
        return EXIT_FAILURE;
    while (StackPush(stacks[2], &d) == EXIT_SUCCESS)
    {
        ++k;
    }
    if (k != 28)
        EXIT_FAILURE;
    StackResize(&stacks[2], 13);
    if (StackSize(stacks[2]) != 13)
        return EXIT_FAILURE;
    if (StackCapacity(stacks[2]) != 13)
        return EXIT_FAILURE;
    while (!StackIsEmpty(stacks[2]))
    {
        StackTop(stacks[2], &d_compare);
        if (d != d_compare)
            return EXIT_FAILURE;
        StackPop(stacks[2]);
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/*int Stack_Func5_Test(void)
{

}
/*******************************************************************************/
/*int Stack_Func6_Test(void)
{

}
/*******************************************************************************/

/*******************************************************************************/
/********************   END OF TEST FUNCTION DEFINITIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DEFINITIONS   ***********************/
/*******************************************************************************/
int init()
{
    int i = 0;
    /*for (; i < NUM_OF_STACKS_IN_TEST; ++i)
    {
        switch (i)
        {
        case 0:
            stacks[i] = StackCreate((i + 1) * CAPACITY_MULT, sizeof(char));
            if (NULL == stacks[i])
                return EXIT_FAILURE;
            break;
        case 1:
            stacks[i] = StackCopy(stacks[0]);
            if (NULL == stacks[i])
                return EXIT_FAILURE;

        default:
            break;
        }
    }*/
    for (; i < NUM_OF_STACKS_IN_TEST; ++i)
    {
        switch (i)
        {
        case 0:
            stacks[i] = StackCreate((i + 1) * CAPACITY_MULT, sizeof(char));
            if (stacks[i] == NULL)
                return EXIT_FAILURE;
            break;
        case 1:
            stacks[i] = StackCreate((i + 1) * CAPACITY_MULT, sizeof(int));
            if (NULL == stacks[i])
                return EXIT_FAILURE;
            break;
        case 2:
            stacks[i] = StackCreate((i + 1) * CAPACITY_MULT, sizeof(double));
            if (NULL == stacks[i])
                return EXIT_FAILURE;
            break;
        case 3:
            stacks[i] = StackCopy(stacks[0]);
            if (NULL == stacks[i])
                return EXIT_FAILURE;
            break;
        case 4:
            stacks[i] = StackCopy(stacks[1]);
            if (NULL == stacks[i])
                return EXIT_FAILURE;
            break;
        case 5:
            stacks[i] = StackCopy(stacks[2]);
            if (NULL == stacks[i])
                return EXIT_FAILURE;
            break;
        default:
            break;
        }
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
void end()
{
    size_t i;
    for (i = 0; i < NUM_OF_STACKS_IN_TEST; ++i)
    {
        free(stacks[i]);
    }
}
/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/

/*******************************************************************************/
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DEFINITIONS   *******************/
/*******************************************************************************/