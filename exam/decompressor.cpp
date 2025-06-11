#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "decompressor.h"
#include <vector>
#include <cctype> 
#include <map>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
using namespace fs;
using namespace std;



void Decompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
	ifstream in(inputFile, std::ios::binary);
	ofstream out(outputFile, std::ios::binary);
	string content((std::istreambuf_iterator<char>(in)), {});
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

void Decompressor::decompressFolder(const std::string& archiveFile, const std::string& outputFolder) {
	ifstream in(archiveFile, std::ios::binary);
	string line;
	while (getline(in, line)) {
		cout << line << endl;
		if (line.rfind("FILE ", 0) == 0) {
			cout << "True" << endl;
			string relPath = line.substr(5);
			string outPath = (fs::path(outputFolder) / relPath).string();
			fs::create_directories(fs::path(outPath).parent_path());

			string compressedContent;
			getline(in, compressedContent);


			map<string, vector<size_t>> duplicateIndices;
			string metaLine;
			while (getline(in, metaLine) && !metaLine.empty()) {
				istringstream iss(metaLine);
				string ch;
				size_t count, idx;
				if (!(iss >> ch >> count)) break;
				vector<size_t> indices;
				for (size_t i = 0; i < count; ++i) {
					if (!(iss >> idx)) break;
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
					}
				}
			}
			string output;
			for (const auto& s : Decompressed) {
				output += s;
			}

			ofstream outFile(outPath, std::ios::binary);
			outFile << output;
		}
	}
}
