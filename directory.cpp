#include "directory.h"
#include <stdexcept>


Directory::Directory(const std::filesystem::path& path) : _path(std::filesystem::canonical(path)) {
    if (!std::filesystem::exists(_path)) {
        throw std::invalid_argument("Path does not exist!");
    }

    if (!std::filesystem::is_directory(_path)) {
        throw std::invalid_argument("Path " + _path.string() + " not directory");
    }
}

// std::filesystem::path root() const {

// }

Directory::BfsIterator::BfsIterator(const std::filesystem::path& path) {
    if (std::filesystem::is_directory(path)) {
        for (const auto& p : std::filesystem::directory_iterator(path)) {
            _current_level.push_back(p);
        }
    }
}

Directory::BfsIterator::reference Directory::BfsIterator::operator*() const {
    return _current_level;
}


Directory::BfsIterator::pointer Directory::BfsIterator::operator->() const {
    return &_current_level;
}

Directory::BfsIterator& Directory::BfsIterator::operator++() {
    if (_current_level.empty()) {
        return *this;
    }
    auto old_level = std::move(_current_level);

    for (const auto& dir : old_level) {
        std::error_code ec;
        auto dir_iter = std::filesystem::directory_iterator(dir, ec);
        for (auto path : std::filesystem::directory_iterator(dir)) {
            if (ec) {
                break;
            }
            if (std::filesystem::is_directory(path)) {
                _current_level.emplace_back(std::move(path));
            }
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
    return _current_level.empty() && other._current_level.empty();
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