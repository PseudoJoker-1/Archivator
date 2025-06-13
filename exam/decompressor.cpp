#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "decompressor.h"
#include <vector>
#include <cctype> 
#include <map>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <algorithm>
#include "Archivator.h"  
namespace fs = boost::filesystem;
using namespace fs;
using namespace std;


// 'a3b' -> 'aaab'
static string expand(const string& compressed) {
    string result;
    for (size_t i = 0; i < compressed.size(); ++i) {
        char ch = compressed[i];
        size_t j = i + 1;
        size_t count = 0;
        while (j < compressed.size() && isdigit(static_cast<unsigned char>(compressed[j]))) {
            count = count * 10 + (compressed[j] - '0');
            ++j;
        }
        if (count == 0) count = 1;
        result.append(count, ch);
        i = j - 1;
    }
    return result;
}


void Decompressor::decompressFile(const string& archiveFile, const string& relativePath, const string& outputFile) {
    Archivator archivator;
    archivator.loadFromFile(archiveFile);


    for (const auto& entry : archivator.getEntries()) {
        if (entry.relativePath == relativePath) {
            string decompressed = expand(entry.compressedData);
            ofstream out(outputFile, ios::binary);
            if (!out) {
                cout << "Cannot create output file: " << outputFile << endl;
                return;
            }
            out << decompressed;
            return;
        }
    }
    cerr << "Entry not found: " << relativePath << endl;
}


void Decompressor::decompressFolder(const string& archiveFile, const string& outputFolder) {
    Archivator archivator;
    archivator.loadFromFile(archiveFile);

    for (const auto& entry : archivator.getEntries()) {
        string decompressed = expand(entry.compressedData);
        path outPath = path(outputFolder) / path(entry.relativePath);
        path dir = outPath.parent_path();
        if (!dir.empty() && !exists(dir)) {
            create_directories(dir);
        }
        ofstream out(outPath.string(), ios::binary);
        if (!out) {
            cerr << "Cannot create file: " << outPath << endl;
            continue;
        }
        out << decompressed;
    }
}

