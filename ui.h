#ifndef UI_H
#define UI_H

#include "mouse_input.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct UIContext {
    bool active;
    bool hot;
} UIContext;


typedef struct MouseInfo {
    int x;
    int y;
    bool mouse_left_down;
} MouseInfo;


void ui_init(void);
void do_text(const char* label, int x, int y, int fontSize);
bool do_button(UIContext *context, const char* label, int x, int y);
bool do_button2(UIContext *context, const char* label, int x, int y, Color hot, Color cold);
bool do_checkbox(UIContext *context, const char* label, int x, int y);
void do_panel(int x, int y, int width, int height, Color color);
MouseInfo do_draw_grid(int x, int y, int cell_size, int rows, int cols);
void do_grid(int *grid, int x, int y, int rows, int cols, int cell_size);
int do_slider(int *value, int minv, int maxv, int x, int y);


#endif // UI_H
