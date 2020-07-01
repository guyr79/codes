/********************************************************
 * utils.c		                                        *
 *                                                      *
 * Implements utils' API 	                            *
 *													    *
 * Author: Guy Rosen									*
 * last update: 02.06.2020								*
 *******************************************************/
#include "utils.h"	/* utils */
#include <stdio.h>	/* puts */
#include <stdlib.h> /* size_t, malloc, free */
#include <string.h> /* memcpy */
#include <limits.h> /* CHAR_MAX, UINT_MAX*/

/************************   API FUNCTION DEFINITIONS   ***********************/
void Swap(void *a, void *b, size_t size)
{
	void *tmp = malloc(size); /*use malloc to allocate storage*/
	memcpy(tmp, a, size);	  /* copy contents of a to tmp using size */
	memcpy(a, b, size);
	memcpy(b, tmp, size);
	free(tmp);
}
/***********************************************************/
int *Char128CounttTableCreator(const char s[])
{
	int i = 0;
	int *char_count_table = (int *)calloc(CHAR_MAX, sizeof(int));

	if (NULL == char_count_table)
		return NULL;

	while (s[i] != '\0')
	{
		++char_count_table[(int)s[i++]];
	}

	return char_count_table;
}
/***********************************************************/
void PrintIntBinaryRepresantation(int x)
{
	int i = 0;
	unsigned int mask = 1 << (sizeof(int) * 8 - 1);
	char binary_rep_of_int[sizeof(int) * 8 + 1] = {0};

	while (mask != 0)
	{
		binary_rep_of_int[i++] = ((x & mask) == mask) ? '1' : '0';
		mask >>= 1;
	}
	puts(binary_rep_of_int);
}
/***********************************************************/
void ReadFullFile(char s[], char address[])
{
	int i = 0;
	FILE *fp = fopen(address, "r");
	while (fgets(s + i, MAX_STR_LEN - i, fp))
		i = strlen(s);
	fclose(fp);
}
/***********************************************************/
void reverse(char s[])
{
	int i;
	char c;
	int j = strlen(s) - 1;

	for (i = 0; i < j; ++i, --j)
	{
		c = s[j];
		s[j] = s[i];
		s[i] = c;
	}
}
/***********************************************************/
size_t GCD(size_t a, size_t b)
{
	if (b == 0)
		return a;
	else if (a == 0)
		return b;
	return GCD(b, a % b);
}
/***********************************************************/
void leftRotate(void *arr, size_t steps, size_t arr_size)
{
	char temp, *char_runner = (char *)arr;
	size_t gcd, i, k, m;

	if ((steps %= arr_size) == 0)
	{
		return;
	}
	gcd = GCD(arr_size, steps);
	for (i = 0; i < gcd; ++i)
	{
		temp = char_runner[i];
		k = i;
		m = (k + steps < arr_size) ? k + steps : arr_size - (k + steps);
		do
		{
			char_runner[k] = char_runner[m];
			k = m;
			m = (k + steps < arr_size) ? (k + steps) : (k + steps - arr_size);
		} while (m != i);
		char_runner[k] = temp;
	}
}
/*********************   END OF API FUNCTION DEFINITIONS   *******************/