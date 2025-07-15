#include "dependency_walker.h"

DependencyWalker::DependencyWalker(FileSystemSearch searcher, const PeBinary& root)
    : _searcher(std::move(searcher)) {

    auto missing = root.findMissingDependencies(root.path().parent_path());
    _unresolved.assign(missing.begin(), missing.end());
}

std::deque<PeBinary> DependencyWalker::resolveNext() {
    if (!hasUnresolved()) return {};

    std::deque<PeBinary> resolvedBinaries;
    auto currentDep = _unresolved.front();
    _unresolved.pop_front();

    auto foundFiles = _searcher.findFile(currentDep);
    for (const auto& foundPath : foundFiles) {
        PeBinary binary(foundPath);
        _resolved.insert(currentDep);
        resolvedBinaries.push_back(binary);

        // Добавляем новые зависимости
        auto newDeps = binary.findMissingDependencies(_searcher.root());
        for (const auto& dep : newDeps) {
            if (_resolved.find(dep) == _resolved.end()) {
                _unresolved.push_back(dep);
            }
        }
    }

    return resolvedBinaries;
}