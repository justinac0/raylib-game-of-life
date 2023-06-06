#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mouse_input.h"
#include "ui.h"
#include "conway.h"

#include <raylib.h>


const int GRID_WIDTH = 128;
const int GRID_HEIGHT = 128;
const int CELL_SIZE = 4;


int main(void) {
    MouseInputState mouseState = {0};

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib-game-of-life");

    ui_init();
    UIContext btnStart = {0};
    UIContext btnStep = {0};
    UIContext btnReset = {0};
    UIContext chkBox = {0};

    // Setup Simulation Grid
    Conway simulation = create_life(GRID_WIDTH, GRID_HEIGHT);
    Conway simulation_copy = create_life(GRID_WIDTH, GRID_HEIGHT);
    reset_life(&simulation, 50);

    const int GRID_CENTER_X = WINDOW_WIDTH/2 - (CELL_SIZE*GRID_WIDTH)/2;
    const int GRID_CENTER_Y = WINDOW_HEIGHT/2 - (CELL_SIZE*GRID_WIDTH)/2;

    bool is_running = false;
    
    while (!WindowShouldClose()) {
        // Render
        BeginDrawing();
        ClearBackground(DARKGRAY);
 
        do_grid(simulation.grid, GRID_CENTER_X, GRID_CENTER_Y, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE);

        if (chkBox.active) {
            do_panel(0, 0, WINDOW_WIDTH/4, WINDOW_HEIGHT, (Color){0, 0, 0, 125});
        }

        if (do_checkbox(&chkBox, "Toggle Simulation Controls", 10, 10)) {
            Color hot = is_running ? (Color){255, 82, 82, 255} : (Color){51, 217, 178, 255};
            Color cold = is_running ? (Color){179, 57, 57, 255} : (Color){33, 140, 116, 255};
            if (do_button2(&btnStart, is_running ? "Stop" : "Start", 10, 94, hot, cold)) {
                is_running = !is_running;
            }

            if (do_button(&btnStep, "Step", 10, 126) && !is_running) {
                step_life(&simulation, &simulation_copy, GRID_WIDTH, GRID_HEIGHT);                
            }

            if (do_button(&btnReset, "Reset Grid", 10, 40)) {
                reset_life(&simulation, 50);
            }
        }

        do_text(is_running ? "RUNNING" : "PAUSED...", 10, WINDOW_HEIGHT - 32, 28);

        EndDrawing();

        // Update
        if (is_running) {
            step_life(&simulation, &simulation_copy, GRID_WIDTH, GRID_HEIGHT);
        }
    }

    CloseWindow();
    destroy_life(&simulation);
    destroy_life(&simulation_copy);

    return 0;
}
