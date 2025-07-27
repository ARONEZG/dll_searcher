#include "walker.h"

DependencyWalker::DependencyWalker(FileSystemSearch searcher, const PeBinary& root)
    : _searcher(std::move(searcher)) {

    auto missing = root.findMissingDependencies(root.path().parent_path());
    _unresolved.assign(missing.begin(), missing.end());
}
std::optional<PeBinary> DependencyWalker::resolveNext(const std::filesystem::path& target_dir) {
    if (_unresolved.empty()) {
        return {};
    }

    std::deque<PeBinary> resolved_bin;
    auto current = _unresolved.front();
    _unresolved.pop_front();

    auto founded = _searcher.findFile(current);

    if (!founded) {
        _future_unresolved.push_back(current);
        return std::nullopt;
    }
        PeBinary binary(founded.value());
        _resolved.insert(current);
        resolved_bin.push_back(binary);

        auto deps = binary.findMissingDependencies(target_dir);
        for (const auto& dep : deps) {
            if (_resolved.find(dep) == _resolved.end()) {
                _unresolved.push_back(dep);
            }
        }

    return binary;
}