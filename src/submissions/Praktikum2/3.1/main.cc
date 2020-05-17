#include <iostream>
#include "hello.h"

int main() {
	
	std::cout << "main1; " << std::endl;
	Hello anton("Anton");
	Hello berta("Berta");
	std::cout << "main2;" << std::endl;
	anton.body();
	std::cout << "main3;" << std::endl;

};
