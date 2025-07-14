#pragma once
#include <filesystem>
#include <optional>
#include <functional>
#include <variant>
#include <queue>
#include <vector>
#include <deque>

class Directory {
public:
    explicit Directory(const std::filesystem::path& path);

    std::filesystem::path root() const;

    class BfsIterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = std::filesystem::path;
        using difference_type = std::ptrdiff_t;
        using pointer = const std::deque<value_type>*;
        using reference = const std::deque<value_type>&;

        BfsIterator() = default;

        explicit BfsIterator(const std::filesystem::path& root);

        reference operator*() const;

        pointer operator->() const;

        BfsIterator& operator++();

        BfsIterator operator++(int);

        bool operator==(const BfsIterator& other) const;

        bool operator!=(const BfsIterator& other) const;

    private:
        std::deque<value_type> _current_level;
    };

    BfsIterator begin() const;
    BfsIterator end() const;
private:
    const std::filesystem::path _path;
};


