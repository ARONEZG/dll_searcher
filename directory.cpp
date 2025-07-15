#include "directory.h"
#include <stdexcept>

Directory::Directory(const std::filesystem::path& path)
    : _path(std::filesystem::canonical(path)) {
    if (!std::filesystem::exists(_path)) {
        throw std::invalid_argument("Path does not exist!");
    }

    if (!std::filesystem::is_directory(_path)) {
        throw std::invalid_argument("Path " + _path.string() +
                                    " not directory");
    }
}

Directory::BfsIterator::BfsIterator(const std::filesystem::path& path) {
    if (std::filesystem::is_directory(path)) {
        _dirs_queue.push_back(path);
    }
}

Directory::BfsIterator::reference Directory::BfsIterator::operator*() const {
    return _dirs_queue.front();
}

Directory::BfsIterator::pointer Directory::BfsIterator::operator->() const {
    return &_dirs_queue.front();
}

Directory::BfsIterator& Directory::BfsIterator::operator++() {
    if (_dirs_queue.empty()) {
        return *this;
    }

    auto current = _dirs_queue.front();
    _dirs_queue.pop_front();

    std::error_code ec;
    auto dir_iter = std::filesystem::directory_iterator(current, ec);
    for (const auto& path : std::filesystem::directory_iterator(current)) {
        if (ec) {
            break;
        }
        if (std::filesystem::is_directory(path)) {
            _dirs_queue.emplace_back(std::move(path));
        }
    }

    return *this;
}

Directory::BfsIterator Directory::BfsIterator::operator++(int) {
    auto tmp = *this;
    ++(*this);
    return tmp;
}

bool Directory::BfsIterator::operator==(const BfsIterator& other) const {
    return _dirs_queue.empty() && other._dirs_queue.empty();
}

bool Directory::BfsIterator::operator!=(const BfsIterator& other) const {
    return !(*this == other);
}

Directory::BfsIterator Directory::begin() const {
    return BfsIterator(_path);
}

Directory::BfsIterator Directory::end() const {
    return BfsIterator();
}