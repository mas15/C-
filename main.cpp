#include <iostream>
#include <vector>
#include "Str.h"

int main() {
    Str s("Siema");
    std::cout<<s.c_str()<<std::endl;

    s = "Hello";
    std::cout<<s<<std::endl;

    Str t = "World";
    std::cout<<s+t<<std::endl;

    s+=t;
    std::cout<<s<<std::endl;

    std::cout<<s[3]<<s[5]<<s[11]<<std::endl;

    std::cout<<s.size()<<std::endl;

    std::vector<char> v;
    v.push_back('a');
    v.push_back('b');
    v.push_back('c');

    Str u(v.begin(), v.end());
    std::cout<<u<<std::endl;
    std::cout<<u.size()<<std::endl;

    char copied[3];
    u.copy(copied, 4);
    std::cout<<copied<<std::endl;

    std::cin >> u;
    std::cout<<u<<std::endl;

    return 0;
}