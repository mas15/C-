//
// Created by Mateusz Stankiewicz on 03.03.16.
//


#ifndef GRIDS_GRID_H
#define GRIDS_GRID_H

#include <set>
#include <array>
#include <vector>
#include "RobotReadings.h"
#include "Coordinate.h"

#define MAXIMUM_RANGE_VALUE 2.5
#define xSize 50
#define ySize 50
#define CELL_SIZE 0.2
#define CELL_PADDING 0.1


using cellIndexType = int8_t;

struct Cell {
    cellIndexType x, y;
};

using array2D = std::array<std::array<cellIndexType, ySize>, xSize>;

class Grid {
private:
    array2D cells;
public:
    Grid();

    ~Grid();

    /**
     * Function that displays grid on std output
     */
    void displayCells(void) const;

    /**
     * Function that returns a 2D array of cellIndexType type(uint8_t) that represents a grid
     */
    array2D getGrid(void) const;

    /**
     * Takes a RobotReadings object and marks cells depending on robot readings
     * @param robot readings object
     */
    void markCells(const RobotReadings &);

    void markSurroundingCells(const Cell);

    /**
     * @param cellIndexType x
     * @param cellIndexType y
     * @return true if is in the grid, otherwise false
     */
    bool isCellInGrid(Cell) const;

    Cell coordinateToCellIndex(Coordinate) const;

    Cell coordinateToCellIndex(const double, const double) const;

    cellIndexType coordinateToCellIndex(const double) const;

    /**
     * @return true if reading is bigger that 0, and smaller than maximum acceptable value
     * */
    bool isReadingInRange(const double) const;

    bool isCellFree(Cell) const;

    /**
     * Calculates coordinates based on robot position and its readings
     * @param object of robot readings
     * @param number of reading that we want to get coordinates
     * @return coordinate object of found obstacle
     */
    Coordinate calculateObstaclePosition(const RobotReadings &, std::vector<double>::size_type) const;

    void addToMarkedAsFree(const double x, const double y, std::vector<Cell> &) const;

    void markAsFreeCellsOnTheWay(Coordinate, Coordinate, Cell);

    /**
     * @param xA
     * @param yA
     * @param xB
     * @param yB
     */
    std::vector<Cell> findCellsOnTheWay(const double, const double, const double, const double);

    /**
     * @param poses filename
     * @param ranges filename
     * @return a vector of robot readings
     */
    std::vector<RobotReadings> readGridFromFiles(const std::string &, const std::string &);
};

#endif //GRIDS_GRID_H
