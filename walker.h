#pragma once
#include <filesystem>
#include "fs_visitor.h"

class Walker {
public:
    Walker(const std::filesystem::path& path);
    void walk(const FileSystemVisitor& visitor) const;


private:
    std::filesystem::path _path;
};