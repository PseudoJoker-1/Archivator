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

void compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    
    std::string content((std::istreambuf_iterator<char>(in)), {});
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

void compress_folder(const string folderPath, const string& outputFile) {
    ofstream out(outputFile, std::ios::binary);
    for (recursive_directory_iterator it(folderPath), end; it != end; ++it) {
        if (is_regular_file(*it)) {
            ifstream in(it->path().string(), std::ios::binary);
            std::string content((istreambuf_iterator<char>(in)), {});
			map<string, vector<size_t>> duplicateIndex;
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
            



            out << relative(it->path(), folderPath).string() << "\n";
            cout << content << "\n";
        }
    }
};