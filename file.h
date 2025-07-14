#pragma once
#include <filesystem> 


class File {
public:
    explicit File(const std::filesystem::path& path);

private:
    const std::filesystem::path _path;
};