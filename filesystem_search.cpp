#include "directory.h"
#include "file_system_search.h"

FileSystemSearch::FileSystemSearch(std::filesystem::path root)
    : _root(std::move(root)) {}

std::deque<std::filesystem::path> FileSystemSearch::findFile(const std::string& filename) const {
    std::deque<std::filesystem::path> foundPaths;
    Directory dir(_root);

    for (const auto& dirPath : dir) {
        auto filePath = dirPath / filename;
        if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath)) {
            foundPaths.push_back(filePath);
        }
    }

    return foundPaths;
}