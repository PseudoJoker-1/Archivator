#pragma once
#include <string>
#include <vector>

struct ArchiveEntry {
    std::string relativePath;
    std::string compressedData;
};

class Archivator {
public:
    void add(const std::string& path, const std::string& data);
    void saveToFile(const std::string& archiveFile) const;
    void loadFromFile(const std::string& archiveFile);
    const std::vector<ArchiveEntry>& getEntries() const;
private:
    std::vector<ArchiveEntry> entries;
};
