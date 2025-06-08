#include <string>
#include <fstream>
#include <iostream>
#include "decompressor.h"
#include <vector>
#include <cctype> 
#include <map>
using namespace std;



void decompress(const std::string& inputFile, const std::string& outputFile) {
	std::ifstream in(inputFile, std::ios::binary);
	std::ofstream out(outputFile, std::ios::binary);
	std::string content((std::istreambuf_iterator<char>(in)), {});
	string output;
	map<string, vector<size_t>> duplicateIndices;
	vector<string> Decompressed = {};

	ifstream meta("meta.txt");

	string ch;
	size_t count, idx;
	while (meta >> ch >> count) {
		vector<size_t> indices;
		for (size_t i = 0; i < count; ++i) {
			meta >> idx;
			indices.push_back(idx);
		}
		duplicateIndices[ch] = indices;
	}

	for (size_t i = 0; i < content.length(); i++) {
		string currentChar(1, content[i]);
		int j = i+1;
		if (isdigit(content[j])) {
			int newNum = content[j] - '0';
			cout << newNum << endl;
			for (int z = 0; z < newNum; z++) {
				
				
			}
		}
	}
	


	out << output;
	cout << output << endl;
}