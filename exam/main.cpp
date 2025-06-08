#include <iostream>
#include "compressor.h"
#include "decompressor.h"


int main() {
    std::cout << "Hello! Archiver started." << std::endl;
    
    compress("input.txt", "compressed.txt");
	decompress("compressed.txt", "decompressed.txt");
    return 0;
}