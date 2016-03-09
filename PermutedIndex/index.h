//
// Created by stanek on 09.03.16.
//

#ifndef PERMUTEDINDEX_INDEX_H
#define PERMUTEDINDEX_INDEX_H
#include "indexEntry.h"
#include <vector>
class index{
    std::vector<indexEntry> indexEntries;
    std::vector<std::string> split(const std::string &s);
    std::string::size_type getMaxLengthOfLeftLine(void) const;
public:
    index(const std::string phrase);
    void display(void);
};



#endif //PERMUTEDINDEX_INDEX_H
