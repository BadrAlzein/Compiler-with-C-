#include <stdio.h>

//import the two funcs from the asm Code
extern int mainWithWhileLoop(unsigned int value);
extern void mainWithtForLoop(int value, int* result);

int main()
{

long long num, *adress; //def the var of the entered Num   x64 Bit 
long long *numAddress= &num; //his address of the nummber 
int numInteger = (int) num ; //the Integer Value of 
int sumWithPointers,sumWithoutPointers; // take the value of the two func from assm and display them
int pointer=0; // pointer
int *pointerAddress = &pointer; // pointer address

//Intro
printf("***** Program: dividers Sum of a given Nummber ***** \n"); 

//Input num
printf("Enter the Nummber ");
scanf("%llu",&num);

//test if the num in Range else err 
if (num>=0) {
// giving the value of the two imported funcs from assm to the two vars
sumWithPointers = mainWithWhileLoop(numInteger);
mainWithtForLoop (num, pointerAddress);
sumWithPointers = *pointerAddress;

//Outtro
printf("***** For the Nummber %llu is ***** \n" , num);

//output result of the two funcs
printf("the Sum of the dividers without Pointers %d is \n", sumWithoutPointers);

printf("the Sum of the dividers with pointers %d is \n", sumWithPointers);

}else {
    //if the num is too big or too small or negative throw an err 
    printf("Type mismatch. The inserted Nummber is out of Range! \n");
}

    return 0;
}
