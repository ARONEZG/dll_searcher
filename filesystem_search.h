#pragma once
#include <deque>
#include <filesystem>

class FileSystemSearch {
   public:
    explicit FileSystemSearch(std::filesystem::path root);

    std::optional<std::filesystem::path> findFile(const std::string& filename) const;
    const std::filesystem::path& root() const { return _root; }

private:
    std::filesystem::path _root;
};