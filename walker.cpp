#include "walker.h"
#include "directory.h"

void Walker::walk(const FileSystemVisitor& visitor) const {
    visitor.apply(Directory(_path));
}