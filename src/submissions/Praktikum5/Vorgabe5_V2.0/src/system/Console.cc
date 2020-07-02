#include "system/Console.h"
#include "device/Keyboard.h"

/** Reserve the Console*/
void Console :: attach() {
    //block
    onOff.wait();
}

void Console :: detach() {
    //free
    onOff.signal();
}

// give the data to the console (Konsole Ausgabe)
int Console::write(const char* data, int size) {
    return output.write(data,size);
}
// every read keyboard charachter should be printed to the screen
int Console :: read(char* data, int size) {
    char c = 0;
    int temp = 0;
    while(size > temp) {
        if(c == '\n'){
            break;
        }
        //read the input char
        c = this -> read();
        //print the given charachter to the screen
        output.write(c);
        // add all the ASCII Charachters to the buffer
        data[temp] = c;
        // the length of the given charachter
        temp++;
    }

    return temp;
    
}
// this methode gives back a charachter from the keyboard buffer
// this methode will be blocked if the buffer is empty
char Console :: read() {
    char bufferChar;

    char* location = &bufferChar;
    input.read(location, 1);
    return bufferChar;
}
