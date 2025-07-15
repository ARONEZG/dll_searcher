#include "import_table.h"
#include <codecvt>
#include <locale>
#include <string>
#ifdef __INTELLISENSE__
#include "libpe/libpe/libpe.ixx"
#else

import libpe;
#endif

ImportTable::ImportTable(const std::filesystem::path& path) {
    libpe::Clibpe pe(path.generic_wstring().c_str());

    if (const auto imports = pe.GetImport(); imports.has_value()) {
        for (const auto& dll : imports.value()) {
            _dependecies.push_back(dll.strModuleName);
        }
    }
}

std::deque<std::string> ImportTable::unresoleved(
    std::filesystem::path dir) const {
    std::deque<std::string> result;
    for (const auto& dep : _dependecies) {
        if (!std::filesystem::exists(dir.append(dep))) {
            result.push_back(dep);
        }
    }

    return result;
}

PeBinary::PeBinary(std::filesystem::path path) : _path(std::filesystem::canonical(path)) {
    libpe::Clibpe pe(_path.generic_wstring().c_str());

    if (auto imports = pe.GetImport(); imports) {
        for (const auto& dll : *imports) {
            _imports.push_back(dll.strModuleName);
        }
    }
}

// const std::vector<std::string>& PeBinary::exports() const {
//     if (!_export) {
//         _export.emplace();

//         libpe::Clibpe pe(_path.generic_wstring().c_str());
//         if (auto exports = pe.GetExport(); exports) {
//             for (const auto& exp : *exports.value()) {
//                 _export.push_back(exp.strName);
//             }
//         }
//     }

//     return *_exports;
// }

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