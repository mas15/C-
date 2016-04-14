#include <iostream>
#include <vector>
#include "Grid.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#define CELL_WIDTH_PX 8
#define CELL_HEIGHT_PX 8

using namespace std;


void draw(const Grid &g, ALLEGRO_DISPLAY *display) {

    array2D cells = g.getGrid();

    al_set_window_title(display, "Assignment mas15");
    al_clear_to_color(al_map_rgb(255, 255, 155));

    static const unsigned char COLORS[] = {0, 200, 180, 140, 100, 60, 40, 20};

    for (int j = 0; j < ySize; j++) {
        for (int i = 0; i < xSize; i++) {
            cellIndexType value = cells[i][j];
            if (value != 0) {
                ALLEGRO_COLOR color;
                if (value < 0) {
                    color = al_map_rgb(255, 255, 255);
                }
                else {
                    unsigned char intensity =
                    value < 8 ? COLORS[value] : (unsigned char) 0;
                    color = al_map_rgb(intensity, intensity, intensity);
                }
                al_draw_filled_rectangle(i * CELL_WIDTH_PX, CELL_HEIGHT_PX * xSize - (j * CELL_HEIGHT_PX),
                                         i * CELL_WIDTH_PX + CELL_WIDTH_PX,
                                         CELL_HEIGHT_PX * ySize - (j * CELL_HEIGHT_PX + CELL_HEIGHT_PX),
                                         color);
            }
        }
    }

al_flip_display();

}

int main(int argc, char **argv) {

    Grid g;

    ALLEGRO_DISPLAY *display = NULL;

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

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    display = al_create_display(8 * xSize, 8 * ySize);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    ALLEGRO_EVENT_QUEUE *queue;
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));

    while (true) {
        for (const auto i : posesFromFile) {
            g.markCells(i);
            draw(g, display);
            al_rest(0.4);
        }

        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        al_rest(0.02);
    }

    al_destroy_display(display);
    return 0;
}

