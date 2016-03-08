//
// Created by stanek on 08.03.16.
//

#include <iostream>
#include <vector>


using namespace std;


vector<string> generateRotations(const vector<string> &splitted) {
    vector<string> result;
    for (vector<string>::size_type i = 0; i != splitted.size(); ++i) {
        string oneLine;
        vector<string> temp(splitted);


        temp.insert(temp.begin(), temp.end() - i, temp.end());
        temp.erase(temp.end() - i, temp.end());

        for (vector<string>::size_type j = 0; j != temp.size(); ++j) {
            oneLine += " ";
            oneLine += temp[j];
        }
        result.push_back(oneLine);
    }
    return result;
}


vector<string> bookImplementation(const vector<string> &splitted) {
    vector<string> result;
    result = generateRotations(splitted);


}