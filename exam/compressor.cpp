#include <iostream>
#include <string>
#include "compressor.h"
#include <fstream>
using namespace std;

void compress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    std::ofstream out(outputFile, std::ios::binary);
    
    std::string content((std::istreambuf_iterator<char>(in)), {});
    string output;
    int cnt = 0;
    for (int i = 0; i < content.length(); i++) {
        for (int j = 0; j < content.length(); i++) {
            if(content[i])
        }
        if (i != 0) {
            if (content[i] == content[i - 1]) {
                cnt += 1;
                output += content[i];
                output += to_string(cnt);
                cout << content[i];
            }
        }
    }

    
}