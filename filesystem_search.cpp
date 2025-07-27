#include "directory.h"
#include "filesystem_search.h"

FileSystemSearch::FileSystemSearch(std::filesystem::path root)
    : _root(std::move(root)) {}

std::optional<std::filesystem::path> FileSystemSearch::findFile(const std::string& filename) const {
    std::deque<std::filesystem::path> foundPaths;
    Directory dir(_root);

    for (const auto& dirPath : dir) {
        auto filePath = dirPath / filename;
        if (std::filesystem::exists(filePath) && std::filesystem::is_regular_file(filePath)) {
            return filePath;  // Return the first found file
        }
    }

    return std::nullopt;  // No file found
}