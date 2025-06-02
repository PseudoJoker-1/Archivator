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
    int j;
    for (int i = 0; i < content.length(); i++) {
        cout << i << endl;
        for (int j = 0; j < content.length(); j++) {

            if (j != i) {
                cout << j << endl;
                if (content[i] == content[j]) {
                    cnt += 1;
                    output += content[i];
                    output += to_string(cnt);
                    
                    
                }
                
                cout << output << endl;
            }

        }
    }

    
}