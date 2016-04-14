#include <iostream>
#include "Grid.h"
#include <chrono>
#include <thread>

#define DELAY_OF_DISPLAY_IN_MS 1000

using namespace std;

int main() {

    Grid g;

    string posesFile, rangesFile;

    cout << "Please give me a names for poses and ranges" << endl;
    cin >> posesFile;
    cin >> rangesFile;
    std::vector<RobotReadings> posesFromFile;
    try {
        posesFromFile = g.readGridFromFiles(posesFile, rangesFile);
    }
    catch (runtime_error e) {
        cout << e.what() << endl;
        return -1;
    }

    for (const auto i : posesFromFile) {
        g.markCells(i);
        system("clear");
        g.displayCells();
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY_OF_DISPLAY_IN_MS));
    }

    return 0;
}
