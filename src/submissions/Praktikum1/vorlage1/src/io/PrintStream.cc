#include "io/PrintStream.h"
#include "io/OutputChannel.h"

/* TODO : Explain 
*/
PrintStream::PrintStream(OutputChannel *chan) : channel(*chan) {}
PrintStream::PrintStream(OutputChannel &chan) : channel(chan) {}

// Ausgabe eines mit einem NULL-Byte terminierten Strings
void PrintStream::print(const char *str)
{
}

// Ausgabe eines mit einem NULL-Byte terminierten Strings
void print(const char *str){

};
void print(char ch){

};

// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
void println(const char *str){

};

// Zeilenvorschub
void println(){

};


// numerische Werte werden zur Basis 'base' Ausgegeben
// implementiere die Basen 2, 10 und 16
void print(int x, int base = DECIMAL){

};
void print(unsigned x, int base = DECIMAL){

};

// Zeigertypen werden immer zur Basis 16 ausgegeben!
void print(void* p){
    
};