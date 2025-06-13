#include "Archivator.h"
#include "Compressor.h"
#include "Decompressor.h"
#include <iostream>
#include <string>

using namespace std;

void printUsage() {
    cout << "Choose an action:\n"
        << "  1. compress file\n"
        << "  2. compress folder\n"
        << "  3. decompress file\n"
        << "  4. decompress folder\n"
        << "Enter number (1-4): ";
}

int main() {
    int choice;
    printUsage();
    if (!(cin >> choice)) {
        cerr << "Invalid input\n";
        return 1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Archivator archivator;
    Compressor compressor;
    Decompressor decompressor;

    switch (choice) {
    case 1: {
        string inputFile, archiveFile;
        cout << "Enter input file path: ";
        getline(cin, inputFile);
        cout << "Enter archive file path: ";
        getline(cin, archiveFile);
        compressor.compressFile(inputFile, archivator);
        archivator.saveToFile(archiveFile);
        break;
    }
    case 2: {
        string folderPath, archiveFile;
        cout << "Enter folder path: ";
        getline(cin, folderPath);
        cout << "Enter archive file path: ";
        getline(cin, archiveFile);
        compressor.compressFolder(folderPath, archivator);
        archivator.saveToFile(archiveFile);
        break;
    }
    case 3: {
        string archiveFile, relativePath, outputFile;
        cout << "Enter archive file path: ";
        getline(cin, archiveFile);
        cout << "Enter relative path in archive: ";
        getline(cin, relativePath);
        cout << "Enter output file path: ";
        getline(cin, outputFile);
        decompressor.decompressFile(archiveFile, relativePath, outputFile);
        break;
    }
    case 4: {
        string archiveFile, outputFolder;
        cout << "Enter archive file path: ";
        getline(cin, archiveFile);
        cout << "Enter output folder path: ";
        getline(cin, outputFolder);
        decompressor.decompressFolder(archiveFile, outputFolder);
        break;
    }
    default:
        cerr << "Unknown choice\n";
        return 1;
    }

    cout << "Done.\n";
    return 0;
}
