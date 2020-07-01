#include "io/PrintStream.h"
#include "io/OutputChannel.h"

// initialisierungslisten because of explicit
PrintStream::PrintStream(OutputChannel *chan) : channel(*chan)
{
	// already defined in private
	// OutputChannel& channel is already defines in .h class
	//*chan declares a pointer to the outputchannel
}

PrintStream::PrintStream(OutputChannel &chan) : channel(chan)
{
	//&chan  declares a reference to output channel
	//takes the address of chan and calls outputchannel with that
}

// Ausgabe eines mit einem NULL-Byte terminierten Strings
//NULL-Byte terminierten Stringsalso called as c strings
// when we define an array of characters like char array[10];
void PrintStream::print(const char *str)
{
	// str is the pointer on a char
	// &str is the adress of the pointer of str
	//casting the str to char*
	//A "string" is really just an array of chars; a null-terminated string is
	// one where a null character '\0' marks the end of the string (not necessarily the
	//end of the array). All strings in code (delimited by double quotes "")
	// are automatically null-terminated by the compiler.
	//So for example, "hi" is the same as {'h', 'i', '\0'}.

	for (; *str != '\0'; (char *)str++)
   
	{

		//is str a null term character? no : then increament
		// if its a null term charc then terminate the functon
		this->channel.write(*str);

	
	}
}
// just write the char on channel
// like console.write() for example
void PrintStream::print(char ch)
{

	this->channel.write(ch);
}

// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
void PrintStream::println(const char *str)
{
	
	//setCursor(row+1,0);
	print(str);
	println();
}

// Zeilenvorschub
// '\n' calling a function that expects a character
//insert new line
void PrintStream::println()
{
	channel.write('\n');
}

enum Base
{
	BINARY = 2,
	DECIMAL = 10,
	HEX = 16
};
/**
Zahlen zur Basis 2 sowie zur Basis 16 sollten mit einem entsprechenden Praefix ausgegeben
werden, sodass die Gefahr eliminiert wird, später Adressen mit Dezimalzahlen zu verwechseln.
Darueberhinaus reicht es, wenn negative Zahlen mit Vorzeichen ausgegeben werden. Eine Um-
wandlung in das Zweierkomplement ist nicht nötig aber erlaubt.
*/
// numerische Werte werden zur Basis 'base' Ausgegeben
// implementiere die Basen 2, 10 und 16

// 1. Die Feststellung der Ziffern einer Zahl
// 2. Die Umwandlung der Ziffern in darstellbare Zeichen
void PrintStream::print(int x, int base)
{
	//0b is for binary its a binary prefix
	//0x is a prefix for HEX
	if (x < 0)
	{
		x *= (-1);
		print('-');
		print((unsigned)x, base);
	}
	else
	{
		this->print((unsigned)x, base);
	}
}


	// A = 10 , B = 11, C = 12 .....
	//const char characters[] = { "0123456789ABCDEF" };
	// BINARY = 2,
	// DECIMAL = 10,
	// HEX = 16
	// initializing Length and output array
	//  example x = 29
	// array starts from 0 
	//  output[0] 
	
	/*
	  29 % 2 = 1 (LSB), 14 % 2 = 0;..... so character [1]
	  29/2= 14,..
	  29 % 10 = 9
		// characters[9] = 9
		output[Length] = characters[(x % base)];
		// x  := x/base
		// divides and if it is not decimal it will be rounded down
		// example x = 25 / 10 = 2,5 => 2 because unsigned int rounded down
		x /= base;
		Length += 1;
	}
	// reversed because needed output increase from 0 to length
	// COMPARISON WITH INT CAST IS VERY IMPORTANT
	
*/

void PrintStream::print(unsigned x, int base)
{
	// maximal reserved number chars length of 32 chars
	// for unsigned integer size of 32 numbers
	// 4 Bytes for u integer -> 4 * 8 bit = 32
    char output[32];
	int length = 0;
	const char characters[] = {"0123456789ABCDEF"};

	// int has 32 bit max so we take aray of size 32
	
    if (base == BINARY){
        print("0b");
    
	if (x == 0)
	{
		channel.write('0');
	}
	while (x > 0)
	{
		output[length] = characters[(x % base)];
		x = x / base;
		length++;
	}
	while (length)
	{
		channel.write(output[length - 1]);
		length--;
	}
    }
///////////////////////////////////////////test for HEX//////////////////////////////
  else if (base == HEX){
        print("0x");
    
	if (x == 0)
	{
		channel.write('0');
	}
	while (x > 0)
	{
		output[length] = characters[(x % base)];
		x = x / base;
		length++;
	}
	while (length)
	{
		channel.write(output[length - 1]);
		length--;
	}
  }
	///////////////////////////////////////DEC///////////////////////
	 else if (base == DECIMAL){
    
	if (x == 0)
	{
		channel.write('0');
	}
	while (x > 0)
	{
		output[length] = characters[(x % base)];
		x = x / base;
		length++;
	}
	while (length)
	{
		channel.write(output[length - 1]);
		length--;
	}
     }
	else
	{
		print("pleae insert a valid base");
        return;
	}
}
// Zeigertypen werden immer zur Basis 16 ausgegeben!
void PrintStream::print(void *p)
{
	// p is an address so we pass the pointer address
	this->print((unsigned)p, HEX);
}



