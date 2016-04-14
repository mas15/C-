//
// Created by Mateusz Stankiewicz on 03.03.16.
//

#include <iostream>
#include "Grid.h"
#include <math.h>

#define PI 3.14159265

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::set;
using std::ifstream;

Grid::Grid() {
    for (int i = 0; i < xSize; i++) {
        for (int j = 0; j < ySize; j++)
            cells[i][j] = 0;
    }
}

Grid::~Grid(void) {
}

array2D Grid::getGrid(void) const {
    return cells;
}

void Grid::displayCells(void) const {
    for (int i = xSize - 1; i >= 0; i--) {
        for (int j = 0; j < ySize; j++) {
            if (cells[j][i] <= 0)
                cout << "  ";
            else if (cells[j][i] >= 5)
                cout << "XX";
            else cout << "__"; //probably not free
        }
        cout << endl;
    }

}

vector<RobotReadings> Grid::readGridFromFiles(const string &posesFile, const string &rangesFile) {
    vector<RobotReadings> posesFromFile;
    readPoses(posesFromFile, posesFile);
    readRanges(posesFromFile, rangesFile);
    return posesFromFile;
}


void Grid::markCells(const RobotReadings &robot) {

    for (vector<double>::size_type i = 0; i < robot.sensorReadings.size(); i++) {
        if (isReadingInRange(robot.sensorReadings.at(i))) {

            Coordinate obstacleCoordinates = calculateObstaclePosition(robot, i);

            Cell cellToMark = coordinateToCellIndex(obstacleCoordinates);

            //ignoring cells outside of the grid
            if (isCellInGrid(cellToMark)) {
                cells[cellToMark.x][cellToMark.y] += 4;
                markSurroundingCells(cellToMark);
                markAsFreeCellsOnTheWay(robot.coordinate, obstacleCoordinates, cellToMark);

            }

        }
    }

}

void Grid::markSurroundingCells(const Cell c) {
    for (int a = -1; a < 2; a++)
        for (int b = -1; b < 2; b++)
            if (a != c.x && b != c.y && !isCellFree(c))
                cells[c.x + a][c.y + b] += 1;
};

bool Grid::isReadingInRange(const double r) const {
    return r < MAXIMUM_RANGE_VALUE && r > 0;
}

bool Grid::isCellFree(Cell c) const {
    return cells[c.x][c.y] == -1;
}

bool Grid::isCellInGrid(Cell c) const {
    return c.x >= -CELL_PADDING && c.x <= xSize - CELL_PADDING
           && c.y >= -CELL_PADDING && c.y <= ySize - CELL_PADDING;
}

Coordinate Grid::calculateObstaclePosition(const RobotReadings &robot, vector<double>::size_type i) const {

    double angleBetweenSensors = 360 / robot.sensorReadings.size(); //45 for 8 sensors
    double angle = (robot.deg + i * angleBetweenSensors) * PI / 180;

    Coordinate pos;

    pos.x = robot.coordinate.x + robot.sensorReadings.at(i) * cos(angle);
    pos.y = robot.coordinate.y + robot.sensorReadings.at(i) * sin(angle);

    return pos;
}

void Grid::markAsFreeCellsOnTheWay(Coordinate begin, Coordinate end, Cell obstacle) {
    std::vector<Cell> setOfCellsToUnmark = findCellsOnTheWay(begin.x, begin.y, end.x, end.y);
    for (auto c: setOfCellsToUnmark) {
        if (c.x != obstacle.x && c.y != obstacle.y) {
            cells[c.x][c.y] = -1;
        }
    }
}

void Grid::addToMarkedAsFree(const double x, const double y, vector<Cell> &setOfCells) const {
    Cell c = coordinateToCellIndex(x, y);
    if (isCellInGrid(c)) {
        setOfCells.push_back(c);
    }
}

std::vector<Cell> Grid::findCellsOnTheWay(const double xA,const double yA, const double xB, const double yB) {

    vector<Cell> setOfCellsToMarkFree;
    //finding cells that are crossed by line A-B
    double xI, yI, t;

    if (xA < xB) {
        for (xI = coordinateToCellIndex(xA) * CELL_SIZE + CELL_PADDING;
             xI < xB; xI += CELL_SIZE) { //for each X axis
            t = (xI - xA) / (xB - xA);
            yI = yA + t * (yB - yA);
            //find coordinates that X axis is crossed by line from xA to xB inclusive
            addToMarkedAsFree(xI, yI, setOfCellsToMarkFree);
            //find coordinates that X axis is crossed by line from xA to xB exclusive
            addToMarkedAsFree(xI + CELL_PADDING, yI, setOfCellsToMarkFree);
        }
    }
    else {
        for (xI = coordinateToCellIndex(xA) * CELL_SIZE - CELL_PADDING;
             xI > xB; xI -= CELL_SIZE) { //for each X axis
            t = (xI - xA) / (xB - xA);
            yI = yA + t * (yB - yA);
            addToMarkedAsFree(xI, yI, setOfCellsToMarkFree);
            addToMarkedAsFree(xI + CELL_PADDING, yI, setOfCellsToMarkFree);
        }
    }

    if (yA < yB) {
        for (yI = coordinateToCellIndex(yA) * CELL_SIZE + CELL_PADDING;
             yI < yB; yI += CELL_SIZE) { //for each X axis
            t = (yI - yA) / (yB - yA);
            xI = xA + t * (xB - xA);
            addToMarkedAsFree(xI, yI, setOfCellsToMarkFree);
            addToMarkedAsFree(xI, yI + CELL_PADDING, setOfCellsToMarkFree);
        }
    } else {
        for (yI = coordinateToCellIndex(yA) * CELL_SIZE - CELL_PADDING;
             yI > yB; yI -= CELL_SIZE) { //for each X axis
            t = (yI - yA) / (yB - yA);
            xI = xA + t * (xB - xA);
            addToMarkedAsFree(xI, yI, setOfCellsToMarkFree);
            addToMarkedAsFree(xI, yI + CELL_PADDING, setOfCellsToMarkFree);
        }
    }
return setOfCellsToMarkFree;
}


Cell Grid::coordinateToCellIndex(Coordinate coordinate) const {
    return coordinateToCellIndex(coordinate.x , coordinate.y);
}

Cell Grid::coordinateToCellIndex(const double x, const double y) const {
    Cell c;
    c.x= coordinateToCellIndex(x);
    c.y= coordinateToCellIndex(y);
    return c;
}

cellIndexType Grid::coordinateToCellIndex(const double c) const{
    return (cellIndexType) ceil((c - CELL_PADDING) / CELL_SIZE);
}
