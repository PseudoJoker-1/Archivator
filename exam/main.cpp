#include <iostream>
#include "compressor.h"

int main() {
    std::cout << "Hello! Archiver started." << std::endl;

    compress("input.txt", "compressed.txt");

    return 0;
}