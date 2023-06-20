// TODO:
//  more efficient updating > 512x512 grid sim
//  mouse controls, drag, pan, etc...
//  re-write...

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mouse_input.h"
#include "ui.h"
#include "conway.h"

#include <raylib.h>


const int GRID_WIDTH = 256;
const int GRID_HEIGHT = 256;
const int CELL_SIZE = 2;


int main(void) {
    MouseInputState mouseState = {0};

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raylib-game-of-life");

    ui_init();
    UIContext btnStart = {0};
    UIContext btnStep = {0};
    UIContext btnGenerateNoise = {0};
    UIContext btnReset = {0};
    UIContext btnErase = {0};
    UIContext btnDraw = {0};
    UIContext chkBox = {0};

    // Setup Simulation Grid
    Conway simulation = create_life(GRID_WIDTH, GRID_HEIGHT);
    Conway simulation_copy = create_life(GRID_WIDTH, GRID_HEIGHT);
    reset_life(&simulation, 50);

    const int GRID_CENTER_X = WINDOW_WIDTH/2 - (CELL_SIZE*GRID_WIDTH)/2;
    const int GRID_CENTER_Y = WINDOW_HEIGHT/2 - (CELL_SIZE*GRID_WIDTH)/2;

    bool is_running = false;
    
    Camera2D camera = {0};
    camera.target = (Vector2){0,0};
    camera.offset = (Vector2){0, 0};
    camera.zoom = 1.0;

    DrawMode draw_mode = NONE;
    int slider = 25;
    float update_speed = 0;

    float last_time = GetTime();

    while (!WindowShouldClose()) {
        float current_time = GetTime();

        // Render
        BeginDrawing();
        ClearBackground(DARKGRAY);
 
        BeginMode2D(camera);
        do_grid(simulation.grid, GRID_CENTER_X, GRID_CENTER_Y, GRID_WIDTH, GRID_HEIGHT, CELL_SIZE);
        MouseInfo edit_info = do_draw_grid(GRID_CENTER_X, GRID_CENTER_Y, CELL_SIZE, GRID_HEIGHT, GRID_WIDTH);
        EndMode2D();

        if (chkBox.active) {
            do_panel(0, 0, WINDOW_WIDTH/3.5, WINDOW_HEIGHT, (Color){0, 0, 0, 125});
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

            if (do_button(&btnGenerateNoise, "Add Random Noise", 10, 40)) {
                reset_life(&simulation, 50);
            }

            if (do_button(&btnReset, "Clear Grid", 10, 180)) {
                clear_life(&simulation);
            }

            
            if (do_button(&btnReset, "Eraser", 10, 214)) {
                draw_mode = ERASE;
            }


            if (do_button(&btnDraw, "Pencil", 10, 248)) {
                draw_mode = DRAW;
            }

            do_text("Update Speed (per second)", 10, 300, 20);
            slider = do_slider(&slider, 0, 256, 10, 334);
            update_speed = slider;
        }

        do_text(is_running ? "RUNNING" : "PAUSED...", 10, WINDOW_HEIGHT - 32, 28);

        EndDrawing();

        // Update
        if (current_time - last_time > 1.0f/update_speed) {
            if (edit_info.mouse_left_down) {
                switch (draw_mode) {
                    case DRAW:
                        edit_grid(&simulation, edit_info.x, edit_info.y, 1);
                        break;
                    case ERASE:
                        edit_grid(&simulation, edit_info.x, edit_info.y, 0);
                        break;
                    default:
                        break;
                }
            }

            if (is_running) {
                step_life(&simulation, &simulation_copy, GRID_HEIGHT, GRID_WIDTH);
                mouse_input_poll(&mouseState);
            }            

            last_time = current_time;
        }
    }

    CloseWindow();
    destroy_life(&simulation);
    destroy_life(&simulation_copy);

    return 0;
}
