#include <stdio.h> /* printing */
#include "utils.h" /* utils */

int main(void) 
{
	int a = 5;
	int b = 10;
	char *c1 = "hello";
	char *c2 = "there";
	
	
	printf("a is %d and b is %d\n", a, b);
	Swap(&a, &b, sizeof(a));	
	printf("a is %d and b is %d\n", a, b);
	
	printf("c1 is \"%s\" and c2 is \"%s\"\n", c1, c2);
	Swap (&c1, &c2, sizeof(c1));
	printf("c1 is \"%s\" and c2 is \"%s\"\n", c1, c2);
	
	return 0;
}
