//
// Created by stanek on 08.03.16.
//
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> concatLeftAndRight(const vector<string> &left, const vector<string> &right,
                                  const string::size_type maxLengthOfLeftLine) {
    vector<string> ret;
    for (vector<string>::size_type i = 0; i != left.size(); ++i) {
        std::stringstream ss;
        ss << string(maxLengthOfLeftLine - left[i].size(), ' ')
        << left[i] << "   " << right[i];
        ret.push_back(ss.str());
    }
    return ret;
}


vector<string> makePermutedIndex(const vector<string> &splitted) {

    vector<string> sorted(splitted);

    std::sort(sorted.begin(), sorted.end());

    string::size_type maxLengthOfLeftLine = 0;

    vector<string> left;
    vector<string> right;

    for (auto index : sorted) {
        string rightLine, leftLine;
        bool indexEncountered = false;

        for (auto word : splitted) {
            if ((index != word) && !indexEncountered) {
                leftLine += word;
                leftLine += " ";
            }
            else {
                indexEncountered = true;
                rightLine += word;
                rightLine += " ";
            }
        }
        maxLengthOfLeftLine = max(maxLengthOfLeftLine, leftLine.size());
        left.push_back(leftLine);
        right.push_back(rightLine);
    }
    return concatLeftAndRight(left, right, maxLengthOfLeftLine);
}
