#pragma once
#include <string>


class Decompressor {
public:
	void decompress(const std::string& inputFile, const std::string& outputFile);
	void decompressFolder(const std::string& inputFolder, const std::string& outputFile);
};

