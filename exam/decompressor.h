#pragma once
#include <string>
using namespace std;


class Decompressor {
public:
	void decompressFile(const string& archiveFile, const string& relPath, const string& outputFile);
	void decompressFolder(const std::string& inputFolder, const std::string& outputFile);
};

