/********************************************************************************
 * dvec_test.c		                                                            *
 *                                                                              *
 * Implements tests for dvec'S API                                          *
 *													                            *
 * Author: Guy Rosen								                            *
 * Reviewer: REVIEWER                                                     *
 * 27/06/2020           					    	                            *
 ********************************************************************************/
#include <stdio.h>  /* printf       */
#include <stdlib.h> /* EXIT_FAILURE/SUCCESS */
#include "dvec.h"   /* library      */
#include "utils.h"  /* RUN_TEST     */

/*******************************************************************************/
/***********************   MACROS AND TYPES DEFINITIONS   **********************/
/*******************************************************************************/
extern const size_t MIN_DVEC_SIZE;
dvec_t *dv1;
dvec_t *dv2;
dvec_t *dv3;
dvec_t *dv4;
unsigned char c;
double d = 0;
int i = 0;
/*******************************************************************************/
/*******************   END OF MACROS AND TYPES DEFINITIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DECLARATIONS   ************************/
/*******************************************************************************/

int DvecCreatAndDvecCapacityeTest(void);
int DvecPushBackAndGetItemAddressTest(void);
int DvecSizeTest(void);
int DVecPopBackTest(void);
/*******************************************************************************/
/*******************   END OF TEST FUNCTION DECLARATIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DECLARATIONS   **********************/
/*******************************************************************************/
void FreeDVs();
/*******************************************************************************/
/******************   END OF PRIVATE FUNCTION DECLARATIONS   *******************/
/*******************************************************************************/

/*******************************************************************************/
int main(void)
{
    RUN_TEST(DvecCreatAndDvecCapacityeTest);
    RUN_TEST(DvecPushBackAndGetItemAddressTest);
    RUN_TEST(DvecSizeTest);
    RUN_TEST(DVecPopBackTest);
    FreeDVs();
    return EXIT_SUCCESS;
}
/*******************************************************************************/

/*******************************************************************************/
/***********************   TEST FUNCTION DEFINITIONS   *************************/
/*******************************************************************************/
int DvecCreatAndDvecCapacityeTest(void)
{
    dv1 = DvecCreate(sizeof(char), 30);
    dv2 = DvecCreate(sizeof(char), 32);
    dv3 = DvecCreate(sizeof(double), 33);
    dv4 = DvecCreate(sizeof(int), 77);

    if (DVecCapacity(dv1) != MIN_DVEC_SIZE)
        return EXIT_FAILURE;
    if (DVecCapacity(dv2) != MIN_DVEC_SIZE)
        return EXIT_FAILURE;
    if (DVecCapacity(dv3) != MIN_DVEC_SIZE << 1)
        return EXIT_FAILURE;
    if (DVecCapacity(dv4) != MIN_DVEC_SIZE << 2)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int DvecPushBackAndGetItemAddressTest(void)
{
    for (c = 'a'; c < 'a' + 90; ++c)
    {
        DVecPushBack(dv1, &c);
        if (*((unsigned char *)DVecGetItemAddress(dv1, c - 'a')) != c)
            return EXIT_FAILURE;
    }

    for (; i < 10000; d = d + 1.0)
    {
        DVecPushBack(dv3, &d);
        if (*((double *)DVecGetItemAddress(dv3, i++)) != d)
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int DvecSizeTest(void)
{
    if (DVecSize(dv1) != (size_t)(c - 'a'))
        return EXIT_FAILURE;
    if (DVecSize(dv3) != (size_t)i)
        return EXIT_FAILURE;
    if (DVecSize(dv2) != 0)
        return EXIT_FAILURE;
    if (DVecSize(dv4) != 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
/*******************************************************************************/
int DVecPopBackTest(void)
{
    for (--c; c >= 'a'; --c)
    {
        if (*((unsigned char *)DVecGetItemAddress(dv1, c - 'a')) != c)
            return EXIT_FAILURE;
        DVecPopBack(dv1);
    }

    for (d = d - 1.0; i != 0; d = d - 1.0)
    {
        if (*((double *)DVecGetItemAddress(dv3, --i)) != d)
        {
            return EXIT_FAILURE;
        }
        DVecPopBack(dv3);
    }
    return EXIT_SUCCESS;
}
/*******************************************************************************/
/********************   END OF TEST FUNCTION DEFINITIONS   *********************/
/*******************************************************************************/

/*******************************************************************************/
/**********************   PRIVATE FUNCTION DEFINITIONS   ***********************/
/*******************************************************************************/
void FreeDVs()
{
    DvecDestroy(dv1);
    DvecDestroy(dv2);
    DvecDestroy(dv3);
    DvecDestroy(dv4);
}
/*******************************************************************************/
/*******************   END OF PRIVATE FUNCTION DEFINITIONS   *******************/
/*******************************************************************************/