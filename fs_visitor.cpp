#include "fs_visitor.h"
#include "import_table.h"

void FileSystemVisitor::apply(const Directory& dir) const {
    ImportTable table(_entry);
    auto unresolved = table.unresoleved(_dst);
    while(!unresolved.empty()) {
        auto dependence = unresolved.front();
        unresolved.pop();

        for (const auto& level : dir) {
            for (const auto& path : level) {
                //resolve(path)
            }
        }
    }
}