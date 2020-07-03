#include <stdio.h>

/*
Include external files with abstract function like below
it will find two assembly functions
*/
extern int getDivisorCount(unsigned int value);
extern void _getDivisorCount(int value, int* result);


int main(int argc, char** vargs) 
{
	long long value;
	printf("%s\n", "Please insert a number to calculate the sum of divisors of this number with an assembly program:");
	/* read an integer of the user and store the input at the adress of the number */
	scanf("%llu", &value);
	int* result;
	int x = 0;
	result = &x;
	if (value > 2147483647)
	{
		printf("%s\n", "Zahl ist zu groß");
	} else if (value < -2147483648) {
		printf("%s\n", "Zahl ist zu klein.");
	} else if (value >= 0) {
		int value2 = (int) value;
		int sumDivisors = getDivisorCount(value2);
		printf("My first result of sumDivisors "
		"from assembly function without pointer: %d\n", sumDivisors);

		_getDivisorCount(value, result);
		printf("Assembly with pointer: %u\n", *result);
	} else {
		printf("%s\n", "Zahl darf nicht negativ sein.");
	}
	/* 
	TODO Pass the number to the assembler function 
	After that print the result of the asm procedure to the screen
	*/
	return 0;
}
