#include <stdio.h>

//import the two funcs from the asm Code
extern int mainWithWhileLoop(unsigned int value);
extern void mainWithtForLoop(int value, int* result);

int main()
{
int num; //def the num of the entered Num 
int pointer=0; 
int *pointerAddress = &pointer;

//Intro
printf("***** Program: dividers Sum of a given Nummber ***** \n"); 

//Input num
printf("Enter the Number:  ");
scanf("%d", &num);

if (num<0 || num>2147483647){
    printf("ERROR 4711: wrong Input \n");
}else {
//Outtro the num 
printf("*****  the Sum of the Div. is *****  \n");
//output result of the two funcs

//while loop Func 
printf("with Whileloop: %d \n", mainWithWhileLoop(num));

//for loop Func
mainWithtForLoop (num, pointerAddress); 
printf("with Forloop: %u \n", *pointerAddress);
}
    return 0;
}

