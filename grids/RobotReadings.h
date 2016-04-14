//
// Created by Mateusz Stankiewicz on 03.03.16.
//

#ifndef GRIDS_READINGS_H
#define GRIDS_READINGS_H


#include <iostream>
#include <vector>
#include "Coordinate.h"

/**
 * RobotReadings structure keeps X and Y coordinates of robot position,
 * degree of its rotation (0 angles is east)
 * and vector of sensor readings
 */
struct RobotReadings {
    Coordinate coordinate;
    short deg;
    std::vector<double> sensorReadings;
};

/**
 * Read from poses file
 */
void readPoses(std::vector<RobotReadings> &, const std::string &);

void readPoses(std::vector<RobotReadings> &, std::istream &);

/**
 * Read from ranges file
 */
void readRanges(std::vector<RobotReadings> &, const std::string &);

void readRanges(std::vector<RobotReadings> &, std::istream &);

/**
 * @return ifstream of opened file
 */
std::ifstream open_file(const std::string filename);
#endif //GRIDS_READINGS_H

