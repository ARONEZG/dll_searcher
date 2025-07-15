#pragma once
#include <filesystem>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

class ImportTable {

   public:
    ImportTable(const std::filesystem::path& path);
    std::deque<std::string> unresoleved(std::filesystem::path dir) const;

   private:
    std::vector<std::string> _dependecies;
};

class PeBinary {
   public:
    explicit PeBinary(std::filesystem::path path);

    const std::filesystem::path& path() const;
    const std::vector<std::string>& imports() const;
    const std::vector<std::string>& exports() const;

    // Dependency operations
    std::deque<std::string> findMissingDependencies(
        const std::filesystem::path& searchDir) const;

   private:
    std::filesystem::path _path;
    std::vector<std::string> _imports;
    mutable std::optional<std::vector<std::string>> _export;
};