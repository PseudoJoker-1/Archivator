#include <iostream>
#include <string>
#include "compressor.h"
#include <fstream>
#include <vector>
#include <map>
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
using namespace fs;
using namespace std;

void Compressor::compressFile(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ::ios::binary);
    ofstream out(outputFile, ios::binary);
    
    string content((istreambuf_iterator<char>(in)), {});
    string output;
    map<string, vector<size_t>> duplicateIndex;
    vector<string> alreadyChecked = {};
    for (size_t i = 0; i < content.length(); i++) {
        string currentChar(1, content[i]);


        if (find(alreadyChecked.begin(), alreadyChecked.end(), currentChar) != alreadyChecked.end())
            continue;

        int count = 1;
        vector<size_t> indicies = { i };

        for (size_t j = i + 1; j < content.length(); ++j) {
            if (content[i] == content[j]) {
                count++;
                indicies.push_back(j);
            }
        }
        if (count == 1) { 
            output += content[i]; 
            duplicateIndex[currentChar] = indicies;
        }

        if (count > 1) {
            cout << "Found duplicate: " << currentChar << " x" << count << endl;
            output += currentChar + to_string(count);
            duplicateIndex[currentChar] = indicies;
        }


        alreadyChecked.push_back(currentChar);
    }
    out << output;
	cout << output << endl;

    ofstream meta("meta.txt");

    for (const auto& pair : duplicateIndex) {
        meta << pair.first << " ";
		meta << pair.second.size();

        for (size_t idx : pair.second) {
            meta << " " << idx;
        }
        meta << endl;
    }
    meta.close();
    
}

void Compressor::compressFolder(const string folderPath, const string& outputFile) {
    ofstream out(outputFile, ios::binary);
    map<string, vector<size_t>> duplicateIndex;
    for (recursive_directory_iterator it(folderPath), end; it != end; ++it) {
        if (is_regular_file(*it)) {
            ifstream in(it->path().string(), ios::binary);
            string content((istreambuf_iterator<char>(in)), {});
            if (!in) {
                cerr << "Cannot open file: " << it->path() << endl;
                continue;
            }
			
			vector<string> alreadyChecked = {};
			for (size_t i = 0; i < content.length(); i++) {
				string currentChar(1, content[i]);
				if (find(alreadyChecked.begin(), alreadyChecked.end(), currentChar) != alreadyChecked.end())
					continue;
				int count = 1;
				vector<size_t> indices = { i };
				for (size_t j = i + 1; j < content.length(); ++j) {
					if (content[i] == content[j]) {
						count++;
						indices.push_back(j);
					}
				}
				if (count == 1) {
					out << content[i];
					duplicateIndex[currentChar] = indices;
				}
				if (count > 1) {
					cout << "Found duplicate: " << currentChar << " x" << count << endl;
					out << currentChar << count;
					duplicateIndex[currentChar] = indices;
				}
				alreadyChecked.push_back(currentChar);
			}
            

            string relPath = relative(it->path(), folderPath).string();
            out << "FILE " << relPath << "\n";
            cout << content << "\n";
        }
    }
    ofstream meta("meta.txt");

    for (const auto& pair : duplicateIndex) {
        meta << pair.first << " ";
        meta << pair.second.size();

        for (size_t idx : pair.second) {
            meta << " " << idx;
        }
        meta << endl;
    }
    meta.close();
};