//
// Created by stanek on 09.03.16.
//

#include "index.h"
#include <algorithm>

using std::string;
using std::vector;
using std::max;

index::index(const string phrase){
    vector<string> splitted = split(phrase);
    vector<string> sorted(splitted);

    std::sort(sorted.begin(), sorted.end());

    for (auto indexWord : sorted) {
        indexEntry e = indexEntry(splitted,indexWord);
        indexEntries.push_back(e);
    }
}

vector<string> index::split(const string &s) {
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


void index::display(void){
    const string::size_type maxLengthOfLeftLine = getMaxLengthOfLeftLine();
    for(auto & entry: indexEntries){ //WHY & here?
        std::cout << entry.concatLeftAndRight(maxLengthOfLeftLine) << std::endl;
    }
}

string::size_type index::getMaxLengthOfLeftLine(void) const{
    string::size_type maxLengthOfLeftLine = 0;
    for(auto & entry : indexEntries) {
        maxLengthOfLeftLine = max(maxLengthOfLeftLine, entry.getLeftSize());
    }
    return maxLengthOfLeftLine;
}