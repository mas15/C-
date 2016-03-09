//
// Created by stanek on 09.03.16.
//

#ifndef PERMUTEDINDEX_INDEXENTRY_H
#define PERMUTEDINDEX_INDEXENTRY_H
#include<iostream>
#include<vector>
#include<sstream>

class indexEntry{
    std::string leftPart;
    std::string rightPart;
public:
    indexEntry(const std::vector<std::string> &, const std::string);
    std::string concatLeftAndRight(const std::string::size_type maxLengthOfLeftLine);
    std::string::size_type getLeftSize(void) const;
};




#endif //PERMUTEDINDEX_INDEXENTRY_H
