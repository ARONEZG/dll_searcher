#pragma once
#include <deque>
#include <unordered_set>
#include "filesystem_search.h"
#include "pebinary.h"

class DependencyWalker {
   public:
    DependencyWalker(FileSystemSearch searcher, const PeBinary& root);

    bool hasUnresolved() const { return !_unresolved.empty(); }
    std::optional<PeBinary> resolveNext(const std::filesystem::path& target_dir);

    const auto& resolvedDeps() const { return _resolved; }
    const auto& unresolvedDeps() const { return _future_unresolved; }

private:
    FileSystemSearch _searcher;
    std::deque<std::string> _unresolved;
    std::unordered_set<std::string> _resolved;
    std::vector<std::string> _future_unresolved;  // Future unresolved dependencies
};