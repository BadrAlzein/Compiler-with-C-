#include <iostream>
using namespace std;
class Hello {
    public :
    Hello(const char* name) : name (name) {
        cout << (name);
        cout << (" ctor;");
    }
    ~Hello() {
        cout <<(name);
        cout << (" dtor;");
    }
    void body() {
        cout << (name);
        cout <<(" body;");
    }
    const char* name;

};

int main() {
    cout << ("main1;");
    Hello anton("Anton");
    Hello berta("Berta");
    cout << ("main2;");
    anton.body();
    cout <<("main3;");
}