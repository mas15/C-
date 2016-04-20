//
// Created by stanek on 20.04.16.
//

#ifndef STRINGCLASS_STR_H
#define STRINGCLASS_STR_H

#include <memory>
#include <cstring>
#include <iostream>

using std::strlen;
using std::allocator;


class Str {
    friend std::ostream &operator<<(std::ostream &, const Str &);
    friend std::istream &operator>>(std::istream &, Str &);
    friend Str operator+(const Str &, const Str &);




public:
    typedef char* iterator;
    typedef size_t size_type;

    Str() { }

    Str(size_type n, char c) { create(n, c); }

    Str(const char *s) { create(s); }

    template<class In>
    Str(In b, In e) {create(b,e); }

    ~Str() {
        if (data) alloc.deallocate(data, length);
        data = 0;
        length = 0;
    }

    Str &operator+=(const Str &s) {
        size_type new_length = s.length + length - 1; //remove 1 because of 2 nulls
        char *new_data = alloc.allocate(new_length);
        strcpy(new_data, data);
        strcpy(new_data + length - 1, s.data); //overwrite null from s
        data = new_data;
        length = new_length;
        return *this;
    }

    Str &operator=(const Str &rhs) {
        if (&rhs != this) {
            if (data) alloc.deallocate(data, length);
            create(rhs.data);
        }

        return *this;
    }

    char &operator[](size_type i) { return data[i]; };

    const char &operator[](size_type i) const { return data[i]; };

    size_type size() { return length; }

    const size_type size() const { return length; }

    const char* c_str(){
        char* result = alloc.allocate(length);
        std::uninitialized_copy(data, data+length, result);
        return result;
    }

    const char* rawdata(){
        char* result = alloc.allocate(length-1);
        std::uninitialized_copy(data, data+length-1, result);
        return result;
    }

    void copy(char *p, size_type n){
        if(n>length)
            throw std::out_of_range("Out of range");
        std::copy(data, data+n, p);
    }

    char* begin(){return data;};
    char* end(){ return data+length;};

private:
    char *data;
    allocator<char> alloc;
    size_type length;

    void create(size_type n, char c) {
        length = n + 1;
        data = alloc.allocate(length);
        std::uninitialized_fill(data, data + length - 1, c);
        alloc.construct(data + length - 1, '\0');
    }

    void create(const char *s) {
        length = strlen(s) + 1;
        data = alloc.allocate(length);
        strcpy(data, s);
        alloc.construct(data + length - 1, '\0');
    }

    template<class In>
    void create(In b, In e){
        length = e - b + 1;
        data = alloc.allocate(length);
        size_type i = 0;
        while (b != e) {
            data[i++] = *(b++);
        }
        alloc.construct(data + length - 1, '\0');
    }
};

std::istream &operator>>(std::istream &is, Str &s) {
    std::vector<char> buf;
    char c;
    while (is.get(c) && isspace(c)) { ;
    }
    if (is) {
        do buf.push_back(c);
        while (is.get(c) && !isspace(c));
        if (is)
            is.unget();
    }
    s.create(buf.begin(), buf.end());
    return is;
}

std::ostream &operator<<(std::ostream &os, const Str &s) {
    os << s.data;
    return os;
}

Str operator+(const Str &s, const Str &t) {
    Str res;
    res.length = s.length + t.length - 1;
    res.data = res.alloc.allocate(res.length);
    strcpy(res.data, s.data);
    strcpy(res.data + s.length - 1, t.data);
    return res;
}

#endif //STRINGCLASS_STR_H
