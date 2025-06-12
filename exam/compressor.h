#pragma once
#include <string>

#include "Archivator.h"

class Compressor {
public:
	void compressFile(const std::string& inputFile, const std::string& outputFile);
	void compressFolder(const std::string inputFolder, const std::string& outputFile, Archivator& archivator);
};