#include <iostream>
#include <string>
#include "compressor.h"
#include "decompressor.h"
#include <vector>
using namespace std;

vector<string> archivedFiles;

void showMenu() {
    cout << "\n=== ��������� ===\n";
    cout << "1. ������������ ����\n";
    cout << "2. ��������������� ����\n";
    cout << "3. ����� �� ��������\n";
    cout << "4. �����\n";
    cout << "�������� �����: ";
}

void archive() {
    string inputFile, outputFile;
    cout << "������� ��� ����� ��� �������������: ";
    cin >> inputFile;
    cout << "������� ��� ������: ";
    cin >> outputFile;

    compress(inputFile, outputFile);
    archivedFiles.push_back(outputFile);
    cout << "���� ����������� ��� " << outputFile << endl;
}

void unarchive() {
    string inputFile, outputFile;
    cout << "������� ��� ������ ��� ����������������: ";
    cin >> inputFile;
    cout << "������� ��� ��������� �����: ";
    cin >> outputFile;

    decompress(inputFile, outputFile);
    cout << "���� �������������� ��� " << outputFile << endl;
}

void search() {
    string name;
    cout << "������� ��� ��� ������: ";
    cin >> name;

    bool found = false;
    for (const auto& f : archivedFiles) {
        if (f.find(name) != string::npos) {
            cout << "������ �����: " << f << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "������ �� �������.\n";
    }
}


int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: archive(); break;
        case 2: unarchive(); break;
        case 3: search(); break;
        case 4: cout << "�����\n"; return 0;
        default: cout << "�������� �����. ���������� �����.\n"; break;
        }
    }

    return 0;
}