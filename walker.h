#pragma once
#include <deque>
#include <unordered_set>
#include "file_system_search.h"
#include "pe_binary.h"

class DependencyWalker {
    std::unordered_set<std::string> _resolved;
    std::deque<std::string> _unresolved;
    FileSystemSearch _searcher;

   public:
    DependencyWalker(FileSystemSearch searcher, const PeBinary& root);

    bool hasUnresolved() const { return !_unresolved.empty(); }
    std::deque<PeBinary> resolveNext();

    const auto& resolvedDeps() const { return _resolved; }
    const auto& unresolvedDeps() const { return _unresolved; }
};