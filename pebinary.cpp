#include "pebinary.h"
#include <codecvt>
#include <locale>
#include <string>
#ifdef __INTELLISENSE__
#include "libpe/libpe/libpe.ixx"
#else

import libpe;
#endif

PeBinary::PeBinary(std::filesystem::path path) : _path(std::filesystem::canonical(path)) {
    libpe::Clibpe pe(_path.generic_wstring().c_str());

    if (auto imports = pe.GetImport(); imports) {
        for (const auto& dll : *imports) {
            _imports.push_back(dll.strModuleName);
        }
    }
}

std::deque<std::string> PeBinary::findMissingDependencies(
    const std::filesystem::path& searchDir) const {
    std::deque<std::string> missing;
    for (const auto& dep : _imports) {
     if (!std::filesystem::exists(searchDir / dep)) {
            missing.push_back(dep);
        }
    }
    return missing;
}

const std::filesystem::path& PeBinary::path() const {
    return _path;
}