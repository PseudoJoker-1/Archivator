#include <iostream>
#include "compressor.h"
#include "decompressor.h"


int main() {
    std::cout << "Hello! Archiver started." << std::endl;
	std::cout << "Compressing and decompressing 'asd' to test functionality." << std::endl;
    Compressor compressor;
    Decompressor decompressor;
    compressor.compressFolder("asd", "compressed.txt");
	decompressor.decompressFolder("compressed.txt", "asd");
    return 0;
}