#include "system/Console.h"
#include "device/Keyboard.h"

void Console :: attach() {
    onOff.wait();
}

void Console :: detach() {
    onOff.signal();
}

int Console::write(const char* data, int size) {
    return output.write(data,size);
}

int Console :: read(char* data, int size) {
    char c = 0;
    int temp = 0;
    while(size > temp) {
        if(c == '\n'){
            break;
        }
        c = this -> read();

        output.write(c);

        data[temp] = c;
        temp++;
    }

    return temp;
    
}

char Console :: read() {
    char bufferChar;

    char* location = &bufferChar;
    input.read(location, 1);
    return bufferChar;
}
