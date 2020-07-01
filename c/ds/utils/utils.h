/********************************************************
 * utils.c		                                        *
 *                                                      *
 * Declares utils' API	 	                            *
 *													    *
 * Author: Guy Rosen									*
 * last update: 02.06.2020								*
 *******************************************************/
#ifndef UTILS_H
#define UTILS_H

#include <stddef.h> /* size_t */
/*****************************************************************************/
/***************************   MACROS DEFINITIONS   **************************/
/*****************************************************************************/
#define BITS_IN_CHAR (8)
#define BYTES_IN_WORD (sizeof(size_t))
#define BITS_IN_WORD (BITS_IN_CHAR * BYTES_IN_WORD)
/* represent an unsigned long type first bit which set to ON */
#define ULONG_0_BIT (1ul)
/* UNUSED(x) deals with unused variables, eliminating compiler's warnings */
#define UNUSED(x) (void)(x)

/* ABS(x) returns the absolute value of x*/
#define ABS(x) ((x > 0) ? (x) : -(x)) /* important to note: (x) : (-x) is a bug!!! */

/* defines the length of an arbitrary str length - 29.03.2020 */
#define MAX_STR_LEN 1001

/* used to run test functions */
#define RUN_TEST(test) if(!test()) \
						{printf("%s is OK!\n", #test);} \
						else{printf("%s failed!\n", #test);}
/*****************************************************************************/						
/***********************   END OF MACROS DEFINITIONS   ***********************/
/*****************************************************************************/

/*****************************************************************************/
/***************************   TYPES DEFINITIONS   ***************************/
/*****************************************************************************/
typedef unsigned  char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
/*****************************************************************************/						
/***********************   END OF TYPES DEFINITIONS   ************************/
/*****************************************************************************/


/*****************************************************************************/
/***********************   API FUNCTION DECLARATIONS   ***********************/
/*****************************************************************************/

/* swaps contents of 2 variables of the same type
	* a , b: variables to swap
	* size: size of the memory allocation for either a or b */
void Swap (void *a, void *b, size_t size);

/*	Char128CounttTableCreator creates table of integers that counts frequencies of chars in s.
*	This function uses calloc, so its output MUST be released by the user */

int *Char128CounttTableCreator(const char s[]);

/* PrintIntBinaryRepresantation prints int variables binary's representation */

void PrintIntBinaryRepresantation(int x);

/*  ReadFullFile reads the file from address into string s 
*	Note: the maximum length to be read is defined by MAX_STR_LEN!!*/

void ReadFullFile(char s[], char address[]);

/* reverse takes char array and reverese it */

void reverse(char s[]);

/* returns greatest common divisor of a and b. a and b are positive */
size_t GCD(size_t a, size_t b);
/* left rotate arr by STEPS steps. The rotation happens byte by byte */
void leftRotate(void *arr, size_t steps, size_t arr_size);

#endif
/*****************************************************************************/
/********************   END OF API FUNCTION DECLARATIONS   *******************/
/*****************************************************************************/