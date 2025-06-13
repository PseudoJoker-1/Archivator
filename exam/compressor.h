#pragma once
#include <string>

#include "Archivator.h"

class Compressor {
public:
	void compressFile(const std::string& inputFile, Archivator& archivator);
	void compressFolder(const std::string& inputFolder, Archivator& archivator);
};