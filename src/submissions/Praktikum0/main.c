#include <stdio.h>

//import the two funcs from the asm Code
extern int mainWithWhileLoop(unsigned int value);
extern void mainWithtForLoop(int value, int* result);

int main()
{
long long num; //def the num of the entered Num   x64 Bit 
int sumWithPointers; // take the value of the two func from assm and display them
int pointer=0; // pointer
int *pointerAddress = &pointer; // pointer address
int numInteger; //the Integer Value of Entered Nummber

//Intro
printf("***** Program: dividers Sum of a given Nummber ***** \n"); 

//Input num
printf("Enter the Nummber \n ");
scanf("%llu", &num);
numInteger = (int) num; 

// giving the value of the two imported funcs from assm to the two vars
sumWithPointers = mainWithWhileLoop(numInteger);

//Outtro the num 
printf("*****  the Sum of the Div. is *****  \n");
//output result of the two funcs
printf("the Sum of the dividers without Pointers %d is \n", sumWithPointers);

mainWithtForLoop (num, pointerAddress);
printf("the Sum of the dividers with pointers %u is \n", *pointerAddress);
    return 0;
}
