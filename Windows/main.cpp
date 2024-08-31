#include <iostream>
#include "../IGFileDialog.h"
//for 
int main() {
    std::string dir = IGGetFile();
    std::cout << "Hello, World!" << dir << std::endl;
    dir = IGGetDirectory();
    std::cout << "Hello, World!" << dir << std::endl;
    return 0;
}