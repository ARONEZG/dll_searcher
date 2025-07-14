#include "import_table.h"
#include <locale>
#include <codecvt>
#include <string>
#ifdef __INTELLISENSE__
// Для IntelliSense используем include (только для подсветки)
#include "libpe/libpe/libpe.ixx"
#else
// Для реальной компиляции используем import
import libpe;
#endif



ImportTable::ImportTable(const std::filesystem::path& path) {
    libpe::Clibpe pe(path.generic_wstring().c_str());

    if (const auto imports = pe.GetImport(); imports.has_value()) {
        std::wcout << L"\n[STANDARD IMPORTS]\n";
        for (const auto& dll : imports.value()) {
            _dependecies.push_back(dll.strModuleName);
        }
    }
}

std::queue<std::string> ImportTable::unresoleved(std::filesystem::path dir) const {
    std::queue<std::string> result;
    for (const auto& dep : _dependecies) {
        if (!std::filesystem::exists(dir.append(dep))) {
            result.push(dep);
        }
    }

    return result;
}