#include <iostream>
#include "compressor.h"
#include "decompressor.h"


int main() {
    std::cout << "Hello! Archiver started." << std::endl;
	std::cout << "Compressing and decompressing 'asd' to test functionality." << std::endl;
    Compressor compressor;
    Decompressor decompressor;
	decompressor.decompressFolder("meta.txt", "asdf");
    return 0;
}