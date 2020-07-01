#include "../include/io/PrintStream.h"
#include "../../include/device/CgaChannel.h"

//constructor defined using "constructor initilise list"
PrintStream::PrintStream(OutputChannel *chan)
        : channel(*chan) {};

PrintStream::PrintStream(OutputChannel &chan)
        : channel(chan) {};

// Ausgabe eines mit einem NULL-Byte terminierten Strings
void PrintStream::print(char *str) {
    channel.write(str);
};

void PrintStream::print(char ch) {
    channel.write((char *) &ch, 1);
};

void PrintStream::print(const char* str) {

    print((char *) str);

};

void PrintStream::println(const char* str) {

    print(str);
    println();

};

// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
void PrintStream::println(char *str) {
    channel.write(str);
    channel.write('\n');
};

// Zeilenvorschub
void PrintStream::println() {
    channel.write('\n');
};

// numerische Werte werden zur Basis 'base' Ausgegeben
// implementiere die Basen 2, 10 und 16
//removed default parameter from cc 
void PrintStream::print(int x, int base) {
    char szt[34];
    switch (base) {
        case 2: {
            int2CharBase2(x, (char *) &szt, 34);
            print((char *) "0b");
            channel.write((char *) &szt);
            break;
        }
        case 10: {
            int2Char(x, (char *) &szt, 34);
            channel.write((char *) &szt);
            break;
        }
        case 16: {
            int2CharHex(x, (char *) &szt, 34);
            print((char *) "0x");
            int2CharHex(x, (char *) &szt, 34);
            channel.write((char *) &szt);
            break;
        }
        default: {
            strcpy((char *) szt, "<base not supported>");
            channel.write((char *) &szt);
            break;
        }
    }
};

void PrintStream::print(unsigned x, int base) {
    char szt[34];
    switch (base) {
        case 2: {
            int2CharBase2((int) x, (char *) &szt, 34);
            print((char *) "0b");
            channel.write((char *) &szt);
            break;
        }
        case 10: {
            int2CharU(x, (char *) &szt, 34);
            channel.write((char *) &szt);
            break;
        }
        case 16: {
            int2CharHex((int) x, (char *) &szt, 34);
            print((char *) "0x");
            channel.write((char *) &szt);
            break;
        }
        default: {
            strcpy((char *) szt, "<base not supported>");
            channel.write((char *) &szt);
            break;
        }
    }
};

// Zeigertypen werden immer zur Basis 16 ausgegeben!
void PrintStream::print(void *p) {
    char szt[34];
    // 32 Bit
    print((char *) "0x");
    int2CharHex((int) p, (char *) &szt, 34);
    channel.write((char *) &szt);
};