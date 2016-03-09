#include "index.h"
using namespace std;

int main() {
    string phrase;
    cout << "Please give me some phrase" << endl;
    getline(cin, phrase);

    index permutedIndex = index(phrase);
    permutedIndex.display();
    return 0;
}
