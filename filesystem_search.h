#pragma once
#include <deque>
#include <filesystem>

class FileSystemSearch {
    std::filesystem::path _root;

   public:
    explicit FileSystemSearch(std::filesystem::path root);

    std::deque<std::filesystem::path> findFile(const std::string& filename) const;
};