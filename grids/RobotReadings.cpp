//
// Created by Mateusz Stankiewicz on 07.03.16.
//

#include "RobotReadings.h"
#include <sstream>
#include <fstream>

using std::string;
using std::vector;

std::ifstream open_file(const std::string filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Problem opening file");
    }
    else
        return infile;
}


void readPoses(vector<RobotReadings> &posesFromFile, const string &posesFile) {
    std::ifstream i = open_file(posesFile);
    readPoses(posesFromFile, i);
}

void readPoses(vector<RobotReadings> &posesFromFile, std::istream &posesStream) {
    RobotReadings p;
    while (posesStream >> p.coordinate.x >> p.coordinate.y >> p.deg) {
        posesFromFile.push_back(p);
    }
}

void readRanges(vector<RobotReadings> &posesFromFile, const string &rangesStream) {
    std::ifstream i = open_file(rangesStream);
    readRanges(posesFromFile, i);
}

void readRanges(vector<RobotReadings> &posesFromFile, std::istream &rangesStream) {
    vector<RobotReadings>::size_type posesCounter = 0;
    string line;
    while (getline(rangesStream, line)) {
        std::stringstream ss(line);

        double val;
        while (ss >> val) {
            posesFromFile.at(posesCounter).sensorReadings.push_back(val);
        }
        posesCounter++;
    }
}