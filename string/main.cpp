#include <iostream>
#include <vector>
#include "Str.h"

using std::cout;
using std::endl;

int main() {
    Str s("Siema");
    cout << s.c_str() << endl;

    s = "Hello";
    cout << s << endl;

    s.push_back('a');
    cout << s << endl;

    Str t = "World";

    s += t;
    cout << s << endl;

    cout << s[3] << s[5] << s[11] << endl;

    cout << s.size() << endl;
    cout << Str(s.begin() + 3, s.end() - 2) << endl;
    for (Str::iterator i = s.begin(); i < s.end(); i += 2) {
        cout << i << endl;
    }

    char copied[5];  //<-- was 3, not enough space
    t.copy(copied, 4);
    cout << copied << endl;

    return 0;
}