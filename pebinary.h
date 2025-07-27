#pragma once
#include <filesystem>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

class PeBinary {
   public:
    explicit PeBinary(std::filesystem::path path);

    const std::filesystem::path& path() const;
    const std::vector<std::string>& imports() const;
    const std::vector<std::string>& exports() const;

    std::deque<std::string> findMissingDependencies(
        const std::filesystem::path& searchDir) const;

   private:
    std::filesystem::path _path;
    std::vector<std::string> _imports;
    mutable std::optional<std::vector<std::string>> _export;
};