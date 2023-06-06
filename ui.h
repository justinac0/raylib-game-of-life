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

void ui_init(void);
void do_text(const char* label, int x, int y, int fontSize);
bool do_button(UIContext *context, const char* label, int x, int y);
bool do_button2(UIContext *context, const char* label, int x, int y, Color hot, Color cold);
bool do_checkbox(UIContext *context, const char* label, int x, int y);
void do_panel(int x, int y, int width, int height, Color color);
void do_grid(int *grid, int x, int y, int rows, int cols, int cell_size);

#endif // UI_H
