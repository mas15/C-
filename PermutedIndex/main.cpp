#include "myImplementation.cpp"
#include "accelCppImplementation.cpp"

using namespace std;

vector<string> split(const string &s) {
    vector<string> ret;
    string::size_type i = 0;
    while (i != s.size()) {
        while (i != s.size() && isspace(s[i]))
            ++i;
        string::size_type j = i;
        while (j != s.size() && !isspace(s[j]))
            j++;
        if (i != j) {
            ret.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return ret;
}

int main() {
    string phrase;
    cout << "Please give me some phrase" << endl;
    getline(cin, phrase);

    vector <string> splitted = split(phrase);

    //First implementation

    vector<string> permuted1 = makePermutedIndex(splitted);

    for (const auto i : permuted1) {
        cout << i << endl;
    }


    //Second implementation

    vector<string> permuted2 = bookImplementation(splitted);

    for (const auto i : permuted2) {
        cout << i << endl;
    }

    return 0;
}
