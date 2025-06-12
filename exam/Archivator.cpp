#include "Archivator.h"
#include <fstream>
#include <sstream>

void Archivator::add(const std::string& path, const std::string& data) {
    entries.push_back({ path, data });
}

void Archivator::saveToFile(const std::string& archiveFile) const {
    std::ofstream out(archiveFile, std::ios::binary);
    for (const auto& entry : entries) {
        out << "FILE " << entry.relativePath << "\n";
        out << entry.compressedData << "\n";
        out << "\n"; // Разделитель между файлами
    }
}

void Archivator::loadFromFile(const std::string& archiveFile) {
    entries.clear();
    std::ifstream in(archiveFile, std::ios::binary);
    std::string line;
    while (std::getline(in, line)) {
        if (line.rfind("FILE ", 0) == 0) {
            std::string relPath = line.substr(5);
            std::string data;
            std::getline(in, data);
            // Пропускаем пустую строку-разделитель
            std::getline(in, line);
            entries.push_back({ relPath, data });
        }
    }
}

const std::vector<ArchiveEntry>& Archivator::getEntries() const {
    return entries;
}
