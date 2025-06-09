#include <iostream>
#include <string>
#include "compressor.h"
#include "decompressor.h"
#include <vector>
using namespace std;

vector<string> archivedFiles;

void showMenu() {
    cout << "\n=== Архиватор ===\n";
    cout << "1. Архивировать файл\n";
    cout << "2. Разархивировать файл\n";
    cout << "3. Поиск по названию\n";
    cout << "4. Выход\n";
    cout << "Выберите опцию: ";
}

void archive() {
    string inputFile, outputFile;
    cout << "Введите имя файла для архивирования: ";
    cin >> inputFile;
    cout << "Введите имя архива: ";
    cin >> outputFile;

    compress(inputFile, outputFile);
    archivedFiles.push_back(outputFile);
    cout << "Файл архивирован как " << outputFile << endl;
}

void unarchive() {
    string inputFile, outputFile;
    cout << "Введите имя архива для разархивирования: ";
    cin >> inputFile;
    cout << "Введите имя выходного файла: ";
    cin >> outputFile;

    decompress(inputFile, outputFile);
    cout << "Файл разархивирован как " << outputFile << endl;
}

void search() {
    string name;
    cout << "Введите имя для поиска: ";
    cin >> name;

    bool found = false;
    for (const auto& f : archivedFiles) {
        if (f.find(name) != string::npos) {
            cout << "Найден архив: " << f << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Ничего не найдено.\n";
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
        case 4: cout << "Выход\n"; return 0;
        default: cout << "Неверный выбор. Попробуйте снова.\n"; break;
        }
    }

    return 0;
}