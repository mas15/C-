//
// Created by stanek on 09.03.16.
//

#include "indexEntry.h"

using std::string;
using std::vector;

indexEntry::indexEntry(const vector<string> &splitted, const string indexWord){
    bool indexEncountered = false;
    for (auto word : splitted) {
        if ((indexWord != word) && !indexEncountered) {
            leftPart += word;
            leftPart += " ";
        }
        else {
            indexEncountered = true;
            rightPart += word;
            rightPart += " ";
        }
    }
}


string indexEntry::concatLeftAndRight(const string::size_type maxLengthOfLeftLine){
        std::stringstream ss;
        ss << string(maxLengthOfLeftLine - leftPart.size(), ' ')
        << leftPart << "   " << rightPart;
        return ss.str();
  }


string::size_type indexEntry::getLeftSize(void) const {
    return leftPart.size();
}
