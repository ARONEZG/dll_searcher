#pragma once
#include <filesystem>
#include "directory.h"
class FileSystemVisitor {
public:
    FileSystemVisitor(const std::filesystem::path& entry, const std::filesystem::path& dst);

    void apply(const Directory& dir) const;
private:
    std::filesystem::path _entry;
    std::filesystem::path _dst;
};