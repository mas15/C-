//
// Created by stanek on 20.04.16.
//

#ifndef STRINGCLASS_STR_H
#define STRINGCLASS_STR_H

#include <memory>
#include <cstring>
#include <iostream>


class Str {

    friend std::istream &operator>>(std::istream &, Str &);

    friend void swap(Str &s, Str &t) {
        std::swap(s.data, t.data);
        std::swap(s.length, t.length);
        std::swap(s.alloc, t.alloc);
    }


public:
    typedef char *iterator;
    typedef size_t size_type;

    Str() : data(nullptr), length(0), capacity(0) { }

    Str(size_type length, char char_to_fill) : Str() { create(length, char_to_fill); }

    Str(const char *s) : Str() { create(s); }

    template<class In>
    Str(In b, In e) : Str() { create(b, e); }

    ~Str() {
        if (data) alloc.deallocate(data, capacity);
        data = nullptr;
    }

    Str(const Str &s) {
        *this = s;
    }

    // move constructor?
    Str(Str &&other)
            : Str() {// initialize via default constructor, C++11 only
        swap(*this, other);
    }

    Str &operator+=(const Str &s) {
        size_type new_length = length + s.length - 1; //remove 1 because of 2 nulls
        if (new_length > capacity) {
            reallocate(new_length);
            strcpy(data + length - 1, s.data); //overwrite null from s
        }
        else {//if there was already enough space
            strcpy(data + length - 1, s.data);
        }
        length = new_length;
        return *this;
    }

    Str &operator=(Str rhs) {
        swap(*this, rhs);
        return *this;
    }

    char &operator[](size_type i) { return data[i]; };

    const char &operator[](size_type i) const { return data[i]; };

    size_type size() { return length; }

    const size_type size() const { return length; }

    const char *c_str() const {
        return data;
    }

    void copy(char *dest, size_type n) {
        if (n > length)
            throw std::out_of_range("Out of range");
        std::copy(data, data + n, dest);
        dest[n] = '\0';
    }

    char *begin() { return data; };

    char *end() { return data + length; };

    void push_back(char c) {
        if (length == capacity) {
            reallocate(capacity == 0 ? DEFAULT_CAPACITY : 2 * capacity);
        }
        data[length++ - 1] = c;
        data[length - 1] = 0;
    }

private:
    char *data;
    std::allocator<char> alloc;
    size_type length;
    size_type capacity;
    static const size_type DEFAULT_CAPACITY = 20;

    void create(size_type n, char character_to_fill) {
        capacity = length = n + 1;
        data = alloc.allocate(capacity);
        std::uninitialized_fill(data, data + length - 1, character_to_fill);
        data[length - 1] = '\0';
    }

    void create(const char *s) {
        capacity = length = strlen(s) + 1;
        data = alloc.allocate(capacity);
        strcpy(data, s);
        data[length - 1] = '\0';
    }

    template<class In>
    void create(In b, In e) {
        capacity = e - b + 1;
        data = alloc.allocate(capacity);
        while (b != e) {
            data[length++] = *(b++);
        }
        data[length++] = '\0';
    }

    void reallocate(size_t new_capacity) {
        char *new_data = alloc.allocate(new_capacity);
        std::copy(data, data + length, new_data);
        alloc.deallocate(data, length);
        data = new_data;
        capacity = new_capacity;
    }
};

std::istream &operator>>(std::istream &is, Str &s) {
    std::vector<char> buf;
    char actual_character;
    while (is.get(actual_character) && isspace(actual_character)) { ;
    }
    if (is) { //is it correct to check "is" ?
        do buf.push_back(actual_character);
        while (is.get(actual_character) && !isspace(actual_character));
        if (is)
            is.unget();
    }
    s.create(buf.begin(), buf.end());
    return is;
}

std::ostream &operator<<(std::ostream &os, const Str &s) {
    os << s.c_str();
    return os;
}

Str operator+(Str lhs, const Str &rhs) {
    lhs += rhs;
    return lhs;
}

#endif //STRINGCLASS_STR_H
