#include<stdio.h>	//include i/o libary
#include<limits.h>	//include limits libary
/*
use to compile and run all at 
nasm -f elf -o nobasepointer.o main-nasm_nobasepointer.asm -g &&
nasm -f elf -o basepointer.o main-nasm_basepointer.asm -g && gcc -m32 -c -o c.o main.c -g && gcc -m32 -o run nobasepointer.o basepointer.o c.o && ./run
*/
extern int getDivisorCountNoPointer(unsigned int value); // assembly function prototype with while loop and no pointer definition
extern void getDivisorCountPointer(int value, int* result); // assembly function with for-loop and pointers definition
int main()		//main function declaration
{
	unsigned long long int value;
	signed long long int value1;
	int result, check;
	printf("Betriebssysteme 1 Aufgabe 0 \n");
	printf("Bitte Unsigend-Integer-Wert zwischen 1 und 2^32-1 eingeben: ");
	check = scanf("%llu", &value);
	while (value < 1 || value > UINT_MAX || check != 1 ) {
		while((value = getchar()) != '\n' && value != EOF) {
			getchar(); // Discard that extra character
		}
		printf("\nBitte Unsigend-Integer-Wert zwischen 1 und 2^32 eingeben: ");
		check = scanf("%llu", &value);
	}
	printf("\nDie Anzahl der Teiler von %lld lautet %u! (Variante1:int getDivisorCount(unsigned int value) \n", value, getDivisorCountNoPointer(value));

	printf("Bitte Sigend-Integer-Wert zwischen -2^32 und 2^32-1 eingeben: ");
	check = scanf("%lld", &value1);
	while (value1 < INT_MIN || value1 > INT_MAX || check != 1 || !value1 ) {
		while((value1 = getchar()) != '\n' && value1 != EOF) {
			getchar(); // Discard that extra character
		}
		printf("\nBitte Integer-Wert zwischen -2^32 und 2^32-1 eingeben: ");
		check = scanf("%llu", &value1);
	}
	if (value1 < 0) {
		value1 = value1*-1;
	}
	getDivisorCountPointer(value1, &result); // fail or overfow when input > 2147483647
	printf("\nDie Anzahl der Teiler von %lld lautet %d! (Variante2:void getDivisorCount(int value, int* result)\n", value1,  result);
	return 0;
}
