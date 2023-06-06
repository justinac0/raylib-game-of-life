#include "conway.h"


Conway create_life(int width, int height) {
    Conway conway;
    conway.width = width;
    conway.height = height;
    conway.grid = (int*)calloc(width * height, sizeof(int));
    assert(conway.grid != NULL);

    return conway;
}


void destroy_life(Conway* conway) {
    free(conway->grid);
}


void reset_life(Conway* conway, int percent_fill) {
    if (conway->grid == NULL) return;

    srand(time(NULL));
    for (int i = 0; i < conway->width * conway->height; i++) {
        conway->grid[i] = 0;
        if ((rand() % 100 + 1) > (100 - percent_fill)) conway->grid[i] = 1;
    }
}


void step_life(Conway* conway, Conway* previous_conway, int rows, int cols) {
    const int DIMENSIONS = rows * cols;

    for (int i = 0; i < DIMENSIONS; i++) {
        previous_conway->grid[i] = conway->grid[i];
        conway->grid[i] = 0;
    }

    for (int i = 0; i < DIMENSIONS; i++) {
        int n = 0;

        // Count Neighbours
        int NW = i - cols - 1;
        int N = i - cols;
        int NE = i - cols + 1;
        int E = i + 1;
        int W = i - 1;
        int SW = i + cols - 1;
        int S =  i + cols;
        int SE =  i + cols + 1;

        n += previous_conway->grid[NW] * (NW >= 0 && NW < DIMENSIONS);
        n += previous_conway->grid[N] * (N >= 0 && N < DIMENSIONS);
        n += previous_conway->grid[NE] * (NE >= 0 && NE < DIMENSIONS);
        n += previous_conway->grid[E] * (E >= 0 && E < DIMENSIONS);
        n += previous_conway->grid[W] * (W >= 0 && W < DIMENSIONS);
        n += previous_conway->grid[SW] * (SW >= 0 && SW < DIMENSIONS);
        n += previous_conway->grid[S] * (S >= 0 && S < DIMENSIONS);
        n += previous_conway->grid[SE] * (SE >= 0 && SE < DIMENSIONS);

        // Apply Rules
        bool is_alive = false;

        // Any live cell with fewer than two live neighbours dies, as if by
        // underpopulation
        if (previous_conway->grid[i] == 1 && n < 2) is_alive = false;

        // Any live cell with two or three live neighours lives on to the next
        // generation
        if (previous_conway->grid[i] == 1 && (n == 2 || n == 3)) is_alive = true;

        // Any dead cell with exactly three live neighbours becomes a live cell,
        // as if by reproduction
        if (previous_conway->grid[i] == 0 && n == 3) is_alive = true;

        conway->grid[i] = is_alive;
    }
}
