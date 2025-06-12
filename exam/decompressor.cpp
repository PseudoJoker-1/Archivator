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


void Decompressor::decompressFolder(const string& archiveFile, const string& outputFolder) {
    ifstream in(archiveFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Cannot open archive: " << archiveFile << "\n";
        return;
    }

    string line;
    while (getline(in, line)) {
        if (line.rfind("FILE ", 0) != 0) {
            cout << "invalid file format: " << line << "\n";
            continue;
        }

        // восстановление и очистка относительного пути
        string relPath = line.substr(5);
        // убираем '\r' и пробельные символы на краях
        while (!relPath.empty() && isspace((unsigned char)relPath.back()))
            relPath.pop_back();
        while (!relPath.empty() && isspace((unsigned char)relPath.front()))
            relPath.erase(0, 1);
        // нормализуем разделители
        replace(relPath.begin(), relPath.end(), '\\', '/');

        path outPath = path(outputFolder) / path(relPath);
        path dir = path(outPath).parent_path();
        if (!dir.empty()) {
            boost::system::error_code ec;
            create_directories(dir, ec);
            if (ec)
                cerr << "mkdir error for " << dir << ": " << ec.message() << "\n";
            else
                cout << "created dirs: " << dir << "\n";
        }

        ofstream fout(outPath.string(), ios::binary);
        if (!fout.is_open()) {
            cerr << "file create error: '" << outPath << "': " << errno << "\n";
            continue;
        }

        cout << "Decompressing to: " << outPath << "\n";

        // чтение сжатого содержимого (игнорируем, если не нужно)
        string compressedContent;
        getline(in, compressedContent);

        // чтение метаданных
        map<string, vector<size_t>> dupIdx;
        string metaLine;
        while (getline(in, metaLine) && !metaLine.empty()) {
            istringstream iss(metaLine);
            string ch;
            size_t count;
            if (!(iss >> ch >> count)) break;
            vector<size_t> idxs(count);
            for (size_t i = 0; i < count; ++i)
                iss >> idxs[i];
            dupIdx[ch] = move(idxs);
        }

        // реконструкция содержимого
        size_t maxIndex = 0;
        for (auto& [ch, vec] : dupIdx)
            for (auto i : vec)
                maxIndex = max(maxIndex, i);

        vector<string> buffer(maxIndex + 1);
        for (auto& [ch, vec] : dupIdx)
            for (auto i : vec)
                buffer[i] = ch;

        // запись
        for (auto& s : buffer)
            fout << s;

        fout.close();
        cout << "Wrote to " << outPath << "\n";
    }
}


