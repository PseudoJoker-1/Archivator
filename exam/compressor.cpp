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

void Compressor::compressFile(const string& inputFile, Archivator& archivator) {
    ifstream in(inputFile, ios::binary);
    if (!in) {
        cerr << "Cannot open file: " << inputFile << endl;
        return;
    }

    string content((istreambuf_iterator<char>(in)), {});
    string compressed;
    map<string, vector<size_t>> duplicateIndex;
    vector<string> alreadyChecked;

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

        if (count > 1) {
            cout << "Found duplicate: " << currentChar << " x" << count << endl;
            compressed += currentChar + to_string(count);
        }
        else {
            compressed += content[i];
        }

        duplicateIndex[currentChar] = indices;
        alreadyChecked.push_back(currentChar);
    }

    
    string relPath = path(inputFile).filename().string();
    archivator.add(relPath, compressed);
}

void Compressor::compressFolder(const string& folderPath, Archivator& archivator) {
    for (recursive_directory_iterator it(folderPath), end; it != end; ++it) {
        if (!is_regular_file(*it))
            continue;

        const auto& filePath = it->path().string();
        ifstream in(filePath, ios::binary);
        if (!in) {
            cerr << "Cannot open file: " << filePath << endl;
            continue;
        }

        string content((istreambuf_iterator<char>(in)), {});
        string compressed;
        map<string, vector<size_t>> duplicateIndex;
        vector<string> alreadyChecked;

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

            if (count > 1) {
                cout << "Found duplicate: " << currentChar << " x" << count << endl;
                compressed += currentChar + to_string(count);
            }
            else {
                compressed += content[i];
            }

            duplicateIndex[currentChar] = indices;
            alreadyChecked.push_back(currentChar);
        }

        // Compute path relative to folderPath
        path rel = path(filePath).lexically_relative(folderPath);
        string relPath = rel.string();
        archivator.add(relPath, compressed);
    }
}

