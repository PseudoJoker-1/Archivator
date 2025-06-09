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
	if (content.empty()) {
		cout << "File is empty!" << endl;
		return;
	}
	map<string, vector<size_t>> duplicateIndices;


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



	size_t maxIndex = 0;
	for (const auto& pair : duplicateIndices) {
		for (size_t index : pair.second) {
			if (index > maxIndex) {
				maxIndex = index;
			}
		}
	}
	vector<string> Decompressed(maxIndex + 1, "");

	for (const auto& pair : duplicateIndices) {
		const string& character = pair.first;
		const vector<size_t>& indices = pair.second;
		for (size_t index : indices) {
			if (index < Decompressed.size()) {
				Decompressed[index] = character;
				cout << index << " : " << character << endl;
			}
			else {
				cout << "Index out of bounds: " << index << endl;
			}
		}
	}
	


	string output;
	for (const auto& s : Decompressed) {
		output += s;
		cout << output << endl;
	}
	out << output;
}