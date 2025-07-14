#pragma once
#include <filesystem>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>

class ImportTable {
public:
    ImportTable(const std::filesystem::path& path);
    std::queue<std::string> unresoleved(std::filesystem::path dir) const;

private:
    std::vector<std::string> _dependecies;
};