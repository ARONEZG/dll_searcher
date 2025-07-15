#include <algorithm>
#include <codecvt>
#include <filesystem>
#include <iostream>
#include <locale>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#ifdef __INTELLISENSE__
// Для IntelliSense используем include (только для подсветки)
#include "libpe/libpe/libpe.ixx"
#else
// Для реальной компиляции используем import
import libpe;
#endif

#include "directory.h"
#include "import_table.h"

void PrintAllDependencies(const std::filesystem::path& filePath) {
    try {
        libpe::Clibpe pe(filePath.generic_wstring().c_str());

        if (const auto imports = pe.GetImport(); imports.has_value()) {
            std::wcout << L"\n[STANDARD IMPORTS]\n";
            for (const auto& dll : imports.value()) {
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>
                    converter;
                std::wstring wname = converter.from_bytes(dll.strModuleName);
                std::wcout << L"  " << wname << L"\n";
            }
        }

        // Delay-load импорты
        if (const auto delayImports = pe.GetDelayImport();
            delayImports.has_value()) {
            std::wcout << L"\n[DELAY-LOAD IMPORTS]\n";
            for (const auto& dll : delayImports.value()) {
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>
                    converter;
                std::wstring wname = converter.from_bytes(dll.strModuleName);
                std::wcout << L"  " << wname << L"\n";
            }
        }

        if (const auto boundImports = pe.GetBoundImport();
            boundImports.has_value()) {
            std::wcout << L"\n[BOUND IMPORTS]\n";
            for (const auto& dll : boundImports.value()) {
                std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>
                    converter;
                std::wstring wname = converter.from_bytes(dll.strBoundName);
                std::wcout << L"  " << wname << L"\n";
            }
        }

    } catch (const std::exception& e) {
        std::wcerr << L"Error: ";
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring werror = converter.from_bytes(e.what());
        std::wcerr << werror << L"\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::wcout << L"Usage: " << argv[0] << L" <path_to_exe>\n";
        return 1;
    }

    std::filesystem::path search_dir = "\\search_dir";
    std::filesystem::path target_path = "\\target_path";
    auto target_dir = target_path.root_directory();
    ImportTable table(target_path);

    auto dependencies = table.unresoleved(target_dir);
    std::queue<std::filesystem::path> missing_dependencies;

    while (!dependencies.empty()) {
        auto current = dependencies.front();
        dependencies.pop_front();
        Directory dir(search_dir);
        for (const auto& current_dir : dir) {
            auto path = current_dir;
            path.append(current);

            if (std::filesystem::exists(path) &&
                std::filesystem::is_regular_file(path)) {
                // copyTo(path, dst);

                auto unresolved = ImportTable(path).unresoleved(target_dir);

                for (const auto& dependency : unresolved) {
                    dependencies.push_back(dependency);
                }
            }
        }
    }

    try {
        // Преобразуем char* -> wstring с проверкой ошибок
        auto exe_path = std::filesystem::path(argv[0]);

        PrintAllDependencies(exe_path);
    } catch (const std::exception& e) {
        std::cerr << "Conversion error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}