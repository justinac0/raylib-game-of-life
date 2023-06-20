#ifndef CONWAY_H
#define CONWAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>


typedef enum DrawMode {
    ERASE,
    DRAW,
    NONE,
} DrawMode;


typedef struct Conway {
    int width;
    int height;
    int* grid;
} Conway;


Conway create_life(int width, int height);
void destroy_life(Conway* conway);
void reset_life(Conway* conway, int percent_fill);
void clear_life(Conway* conway);
void edit_grid(Conway* conway, int x, int y, int value);
void step_life(Conway* conway, Conway* previous_conway, int rows, int cols);

#endif // CONWAY_H
