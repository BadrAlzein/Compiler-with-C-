#include <iostream>
#include "hello.h"


Hello::Hello(const char* name) : name(name) {

	std::cout << name;
	std::cout << " ctor" << std::endl;

}

Hello::~Hello() {

	std::cout << name;
	std::cout << " dtor" << std::endl; 

}

void Hello::body() {

	std::cout << name;
	std::cout << " body" << std::endl;

}
