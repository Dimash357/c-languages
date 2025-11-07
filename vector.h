#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_MEMORY_IMPLEMENTED

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

template <typename T>
class Vector {
public:
    using ValueType = T;
    using Pointer = T*;
    using ConstPointer = const T*;
    using Reference = T&;
    using ConstReference = const T&;
    using SizeType = size_t;
    using Iterator = T*;
    using ConstIterator = const T*;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

private:
    T* buffer_ = nullptr;
    SizeType size_ = 0;
    SizeType capacity_ = 0;

    void ExpandCapacity(SizeType new_cap) {
        if (new_cap <= capacity_) {
            return;
        }

        T* new_buffer = static_cast<T*>(::operator new(new_cap * sizeof(T)));
        SizeType new_size = 0;

        try {
            std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
            new_size = size_;
        } catch (...) {
            std::destroy(new_buffer, new_buffer + new_size);
            ::operator delete(new_buffer);
            throw;
        }

        std::destroy(buffer_, buffer_ + size_);
        ::operator delete(buffer_);

        buffer_ = new_buffer;
        capacity_ = new_cap;
        size_ = new_size;
    }

public:
    Vector() = default;

    explicit Vector(SizeType size) : buffer_(static_cast<T*>(::operator new(size * sizeof(T)))), size_(size), capacity_(size) {
        try {
            std::uninitialized_value_construct(buffer_, buffer_ + size_);
        } catch (...) {
            ::operator delete(buffer_);
            throw;
        }
    }

    Vector(SizeType size, const T& value) : buffer_(static_cast<T*>(::operator new(size * sizeof(T)))), size_(size), capacity_(size) {
        try {
            std::uninitialized_fill(buffer_, buffer_ + size_, value);
        } catch (...) {
            ::operator delete(buffer_);
            throw;
        }
    }

    Vector(std::initializer_list<T> init) : buffer_(static_cast<T*>(::operator new(init.size() * sizeof(T)))), size_(init.size()), capacity_(init.size()) {
        try {
            std::uninitialized_copy(init.begin(), init.end(), buffer_);
        } catch (...) {
            ::operator delete(buffer_);
            throw;
        }
    }

    template <class Iterator, class = std::enable_if_t<std::is_base_of_v<
        std::forward_iterator_tag,
        typename std::iterator_traits<Iterator>::iterator_category>>>
    Vector(Iterator first, Iterator last) {
        SizeType count = std::distance(first, last);
        if (count > 0) {
            buffer_ = static_cast<T*>(::operator new(count * sizeof(T)));
            capacity_ = count;
            try {
                std::uninitialized_copy(first, last, buffer_);
                size_ = count;
            } catch (...) {
                ::operator delete(buffer_);
                throw;
            }
        }
    }

    ~Vector() {
        std::destroy(buffer_, buffer_ + size_);
        ::operator delete(buffer_);
    }

    Vector(const Vector& other) : buffer_(other.size_ > 0 ? static_cast<T*>(::operator new(other.capacity_ * sizeof(T))) : nullptr), size_(other.size_), capacity_(other.capacity_) {
        try {
            std::uninitialized_copy(other.buffer_, other.buffer_ + other.size_, buffer_);
        } catch (...) {
            ::operator delete(buffer_);
            throw;
        }
    }

    Vector(Vector&& other) noexcept : buffer_(other.buffer_), size_(other.size_), capacity_(other.capacity_) {
        other.buffer_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        Vector temp(other);
        Swap(temp);
        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            std::destroy(buffer_, buffer_ + size_);
            ::operator delete(buffer_);

            buffer_ = other.buffer_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.buffer_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    SizeType Size() const noexcept { return size_; }
    SizeType Capacity() const noexcept { return capacity_; }
    bool Empty() const noexcept { return size_ == 0; }

    Reference operator[](SizeType index) { return buffer_[index]; }
    ConstReference operator[](SizeType index) const { return buffer_[index]; }

    Reference At(SizeType index) {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return buffer_[index];
    }

    ConstReference At(SizeType index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return buffer_[index];
    }

    Reference Front() { return buffer_[0]; }
    ConstReference Front() const { return buffer_[0]; }
    Reference Back() { return buffer_[size_ - 1]; }
    ConstReference Back() const { return buffer_[size_ - 1]; }
    Pointer Data() noexcept { return buffer_; }
    ConstPointer Data() const noexcept { return buffer_; }

    Iterator begin() noexcept { return buffer_; } // NOLINT
    ConstIterator begin() const noexcept { return buffer_; } // NOLINT
    ConstIterator cbegin() const noexcept { return buffer_; } // NOLINT
    Iterator end() noexcept { return buffer_ + size_; } // NOLINT
    ConstIterator end() const noexcept { return buffer_ + size_; } // NOLINT
    ConstIterator cend() const noexcept { return buffer_ + size_; } // NOLINT

    ReverseIterator rbegin() noexcept { return ReverseIterator(end()); } // NOLINT
    ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); } // NOLINT
    ConstReverseIterator crbegin() const noexcept { return ConstReverseIterator(cend()); } // NOLINT
    ReverseIterator rend() noexcept { return ReverseIterator(begin()); } // NOLINT
    ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); } // NOLINT
    ConstReverseIterator crend() const noexcept { return ConstReverseIterator(cbegin()); } // NOLINT

    void Swap(Vector& other) noexcept {
        std::swap(buffer_, other.buffer_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    void Resize(SizeType new_size) {
        if (new_size < size_) {
            std::destroy(buffer_ + new_size, buffer_ + size_);
            size_ = new_size;
            return;
        }

        if (new_size <= capacity_) {
            std::uninitialized_value_construct(buffer_ + size_, buffer_ + new_size);
            size_ = new_size;
            return;
        }

        SizeType new_cap = std::max(capacity_ * 2, new_size);
        T* new_buffer = static_cast<T*>(::operator new(new_cap * sizeof(T)));

        try {
            std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
            std::uninitialized_value_construct(new_buffer + size_, new_buffer + new_size);
        } catch (...) {
            std::destroy(new_buffer, new_buffer + size_);
            ::operator delete(new_buffer);
            throw;
        }

        std::destroy(buffer_, buffer_ + size_);
        ::operator delete(buffer_);

        buffer_ = new_buffer;
        size_ = new_size;
        capacity_ = new_cap;
    }

    void Resize(SizeType new_size, const T& value) {
        if (new_size < size_) {
            std::destroy(buffer_ + new_size, buffer_ + size_);
            size_ = new_size;
            return;
        }

        if (new_size <= capacity_) {
            std::uninitialized_fill(buffer_ + size_, buffer_ + new_size, value);
            size_ = new_size;
            return;
        }

        SizeType new_cap = std::max(capacity_ * 2, new_size);
        T* new_buffer = static_cast<T*>(::operator new(new_cap * sizeof(T)));

        try {
            std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
            std::uninitialized_fill(new_buffer + size_, new_buffer + new_size, value);
        } catch (...) {
            std::destroy(new_buffer, new_buffer + size_);
            ::operator delete(new_buffer);
            throw;
        }

        std::destroy(buffer_, buffer_ + size_);
        ::operator delete(buffer_);

        buffer_ = new_buffer;
        size_ = new_size;
        capacity_ = new_cap;
    }

    void Reserve(SizeType new_cap) {
        if (new_cap > capacity_) {
            ExpandCapacity(new_cap);
        }
    }

    void ShrinkToFit() {
        if (size_ < capacity_) {
            if (size_ == 0) {
                ::operator delete(buffer_);
                buffer_ = nullptr;
                capacity_ = 0;
                return;
            }

            T* new_buffer = static_cast<T*>(::operator new(size_ * sizeof(T)));
            try {
                std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
            } catch (...) {
                ::operator delete(new_buffer);
                throw;
            }

            std::destroy(buffer_, buffer_ + size_);
            ::operator delete(buffer_);

            buffer_ = new_buffer;
            capacity_ = size_;
        }
    }

    void Clear() noexcept {
        std::destroy(buffer_, buffer_ + size_);
        size_ = 0;
    }

    void PushBack(const T& value) {
        if (size_ == capacity_) {
            SizeType new_cap = capacity_ ? capacity_ * 2 : 1;
            T* new_buffer = static_cast<T*>(::operator new(new_cap * sizeof(T)));

            try {
                std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
                new (new_buffer + size_) T(value);
            } catch (...) {
                std::destroy(new_buffer, new_buffer + size_);
                ::operator delete(new_buffer);
                throw;
            }

            std::destroy(buffer_, buffer_ + size_);
            ::operator delete(buffer_);

            buffer_ = new_buffer;
            capacity_ = new_cap;
            ++size_;
        } else {
            new (buffer_ + size_) T(value);
            ++size_;
        }
    }

    void PushBack(T&& value) {
        if (size_ == capacity_) {
            SizeType new_cap = capacity_ ? capacity_ * 2 : 1;
            T* new_buffer = static_cast<T*>(::operator new(new_cap * sizeof(T)));

            try {
                std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
                new (new_buffer + size_) T(std::move(value));
            } catch (...) {
                std::destroy(new_buffer, new_buffer + size_);
                ::operator delete(new_buffer);
                throw;
            }

            std::destroy(buffer_, buffer_ + size_);
            ::operator delete(buffer_);

            buffer_ = new_buffer;
            capacity_ = new_cap;
            ++size_;
        } else {
            new (buffer_ + size_) T(std::move(value));
            ++size_;
        }
    }

    template <typename... Args>
    void EmplaceBack(Args&&... args) {
        if (size_ == capacity_) {
            SizeType new_cap = capacity_ ? capacity_ * 2 : 1;
            T* new_buffer = static_cast<T*>(::operator new(new_cap * sizeof(T)));

            try {
                std::uninitialized_move(buffer_, buffer_ + size_, new_buffer);
                new (new_buffer + size_) T(std::forward<Args>(args)...);
            } catch (...) {
                std::destroy(new_buffer, new_buffer + size_);
                ::operator delete(new_buffer);
                throw;
            }

            std::destroy(buffer_, buffer_ + size_);
            ::operator delete(buffer_);

            buffer_ = new_buffer;
            capacity_ = new_cap;
            ++size_;
        } else {
            new (buffer_ + size_) T(std::forward<Args>(args)...);
            ++size_;
        }
    }

    void PopBack() {
        if (size_ > 0) {
            std::destroy_at(buffer_ + size_ - 1);
            --size_;
        }
    }

    bool operator==(const Vector& other) const {
        if (size_ != other.size_) {
            return false;
        }
        return std::equal(buffer_, buffer_ + size_, other.buffer_);
    }

    bool operator!=(const Vector& other) const { return !(*this == other); }

    bool operator<(const Vector& other) const {
        return std::lexicographical_compare(buffer_, buffer_ + size_,
                                          other.buffer_, other.buffer_ + other.size_);
    }

    bool operator<=(const Vector& other) const { return !(other < *this); }
    bool operator>(const Vector& other) const { return other < *this; }
    bool operator>=(const Vector& other) const { return !(*this < other); }
};

#endif // VECTOR_H