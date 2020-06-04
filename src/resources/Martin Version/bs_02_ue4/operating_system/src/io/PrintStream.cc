#include "io/PrintStream.h"
#include "io/OutputChannel.h"


// explicit one argument in constructor
// explicit get the one parameter 
// and convert the argument to another higher object with a function 
// initialisierungslisten because of explicit
PrintStream::PrintStream(OutputChannel* chan): channel(*chan)
{
	// already defined in private 
	// OutputChannel& channel;
	// zeige mit *chan auf den Zeiger von Outputchannel 
	// also die speicheradresse von einem Outputchannel 
	// this->channel = chan;
}

PrintStream::PrintStream(OutputChannel& chan): channel(chan)
{
	// this->channel = &chan;
}

// Ausgabe eines mit einem NULL-Byte terminierten Strings
void PrintStream::print(const char* str)
{
	// str is the pointer on a char
	// &str is the adress of the pointer of str
	// virtual int write(const char* data, int size) = 0;
	while(*str != 0) {
		// char value of pointer has always the size of 1 bytes so 1
		// print only one char, this char which the pointer shows on
		this->channel.write(*str);
		// sets the char pointer str 1 byte above 
		(char*) str++;
	}
}

void PrintStream::print(char ch)
{
	// THIS IS THE WRONG ONE int CgaChannel::write(const char* data, int size) 
	/*
	this is in OutputChannel.h implemented
	int write(char c)
	{
		return write(&c, sizeof(c));
	}
	*/
	this->channel.write(ch);
}

// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
void PrintStream::println(const char* str)
{
	// two chars so two bytes
	this->print(str);
	this->println();
}

// Zeilenvorschub
void PrintStream::println()
{
	this->channel.write('\n');
}


enum Base {
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
	// virtual int write(const char* data, int size) = 0;
	// print negative numbers with sign
	// 0xbla for hexadecimal base 16
	// 0bbla for binary base 2
	// bla has to be transfered before writing
	// signed hex and bin is not defined so - will be before 0x or 0b
/*	if ((x < 0 && base == BINARY) || (x < 0 && base == HEX)) {
		this->print("Negative binary or hex numbers not possible.");
	} else if ((base != BINARY) || (base != DECIMAL) || (base != HEX)) {
		this->print("Diese Basis ist nicht erlaubt!");
	} else {
		if (x < 0) {
		    x = -1 * x;
		    // does not work
		    // this->print(" -");
		    this->print('-');
		}
		if (base == BINARY) {
			this->print("0b");
		} else if (base == HEX) {
			this->print("0x");
		}
		this->print((unsigned) x, base);
	}*/
	if (x < 0) {
	    x = -1 * x;
	    this->print('-');
	    this->print((unsigned) x, base);
	} else {
		this->print((unsigned) x, base);
	}

	
}

void PrintStream::print(unsigned x, int base)
{
	// maximal reserved number chars length of 32 chars
	// for unsigned integer size of 32 numbers 
	// 4 Bytes for u integer -> 4 * 8 bit = 32 


	if (base == BINARY) {
		this->print("0b");
			
	} else if (base == HEX) {
		this->print("0x");
		
	} else if (base == DECIMAL) {
		
	} else {
		print("Eine erlaubte Basis aussuchen");
		return;
	}

	char output[32];
	// A = 10 , B = 11, C = 12 .....
	// will never change the field that is why const 
	const char characters[] = { "0123456789ABCDEF" };
	// BINARY = 2,
	// DECIMAL = 10,
	// HEX = 16
	// initializing dynamicLength and output array
	// TODO example x = 25
	// init array from 0 to length always!
	// dowhile because for output[0] you need a value 
	// inits with 0 IS VERY IMPORTANT
	int dynamicLength = 0;
	if (x == 0) {
		this->channel.write('0');
	}
	while(x) {
		// TODO 25 % 10 = 5
		// characters[5] = 5
		output[dynamicLength] = characters[(x % base)];
		// x  := x/base
		// divides and if it is not decimal it will be rounded down
		// x = 25 / 10 = 2,5 => 2 because unsigned int rounded down
		x /= base;
		dynamicLength += 1;
	}
	// reversed because needed output increase from 0 to length
	// COMPARISON WITH INT CAST IS VERY IMPORTANT
	while(dynamicLength) {
		/*
		this is in OutputChannel.h implemented
		int write(char c)
		{
			return write(&c, sizeof(c));
		}
		*/
		this->channel.write(output[dynamicLength - 1]);
		dynamicLength--;
	}

/*
if (base == DECIMAL || base == BINARY || base == HEX)
    {
        int zahl[32]; //Ein int hat maximal 32 Stellen
        if (base == BINARY)
        {
            print("0b");
        }
        else if (base == HEX)
        {
            print("0x");
        }

        if (x == 0)
        {
            print('0');
        }
        else
        {
            int i = 31;
            while (x != 0)
            {
                zahl[i] = (x % base) + 48; //ASCII beginnt mit 0 erst bei 48
                x = x / base;
                i--;
            }
            i++; //beim letzten Mal wurde eins zu weit zurück gegangen
            for (; i < 32; i++)
            {
                switch (zahl[i] - 48)
                {
                case 10:
                    print('a');
                    break;
                case 11:
                    print('b');
                    break;
                case 12:
                    print('c');
                    break;
                case 13:
                    print('d');
                    break;
                case 14:
                    print('e');
                    break;
                case 15:
                    print('f');
                    break;
                default:
                    this->channel.write((char)zahl[i]);
                }
            }
        }
    }
    else
    {
        print("Das ist keine schoene Basis!");
        return;
    }
*/
}

// Zeigertypen werden immer zur Basis 16 ausgegeben!
void PrintStream::print(void* p)
{
	// p is an address so we pass the pointer address 
  	this->print((unsigned) p, HEX);
}
