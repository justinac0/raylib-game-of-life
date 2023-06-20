#include <raylib.h>
#include <string.h>
#include "ui.h"


bool do_mouse_aabb(int x1, int y1, int x2, int y2, int width, int height) {
    bool colX = x1 + width >= x2 && x2 >= x1;
    bool colY = y1 + height >= y2 && y2 >= y1;

    return colX && colY;
}


Font defaultFont = {0};
void ui_init(void) {
    defaultFont = LoadFontEx("assets/roboto-mono.ttf", 92, 0, 0);
}


void do_text(const char* label, int x, int y, int fontSize) {
    DrawTextEx(defaultFont, label, (Vector2){x, y}, fontSize, 1, WHITE);
}

bool do_button(UIContext *context, const char* label, int x, int y) {
    const int labelLength = strlen(label);
    const int fontSize = 24;
    const int width = labelLength * (fontSize / 2);
    const int height = fontSize;
    const int border = 4;

    context->hot = do_mouse_aabb(x, y, GetMouseX(), GetMouseY(), width, height);

    Color color = DARKBLUE;
    if (context->hot) {
        color = BLUE;
        DrawRectangle(x - (border/2), y - (border/2), width + border, height + border, WHITE);
    }

    context->active = IsMouseButtonPressed(0) & context->hot;
    DrawRectangle(x, y, width, height, color);
    DrawTextEx(defaultFont, label, (Vector2){x, y}, fontSize, 1, WHITE);

    return context->active;
}


bool do_button2(UIContext *context, const char* label, int x, int y, Color hot, Color cold) {
    const int labelLength = strlen(label);
    const int fontSize = 24;
    const int width = labelLength * (fontSize / 2);
    const int height = fontSize;
    const int border = 4;

    context->hot = do_mouse_aabb(x, y, GetMouseX(), GetMouseY(), width, height);

    Color color = cold;
    if (context->hot) {
        color = hot;
        DrawRectangle(x - (border/2), y - (border/2), width + border, height + border, WHITE);
    }

    context->active = IsMouseButtonPressed(0) & context->hot;
    DrawRectangle(x, y, width, height, color);
    DrawTextEx(defaultFont, label, (Vector2){x, y}, fontSize, 1, WHITE);

    return context->active;
}


bool do_checkbox(UIContext *context, const char* label, int x, int y) {
    const int size = 16;
    const int border = 4;

    context->hot = do_mouse_aabb(x, y, GetMouseX(), GetMouseY(), size, size);

    DrawRectangle(x - (border/2), y - (border/2), size + border, size + border, GRAY);
    DrawRectangle(x, y, size, size, DARKGRAY);
    if (label) DrawTextEx(defaultFont, label, (Vector2){x + size + size/2, y}, size, 1, WHITE);

    if (IsMouseButtonPressed(0) && context->hot) {
        context->active = !context->active;
    }

    if (context->active) {
        DrawRectangle(x, y, size, size, WHITE);
    }

    return context->active;
}


void do_panel(int x, int y, int width, int height, Color color) {
    DrawRectangle(x, y, width, height, color);
}


MouseInfo do_draw_grid(int x, int y, int cell_size, int rows, int cols) {
    const int width = cell_size * cols;
    const int height = cell_size * rows;
    const int mouse_x = GetMouseX();
    const int mouse_y = GetMouseY();
    const int mouse_offset_x = (((mouse_x - x) / cell_size) % cols) * cell_size + x;
    const int mouse_offset_y = ((mouse_y - y) / cell_size) * cell_size + y;
    bool is_mouse_down = false;

    if (do_mouse_aabb(x, y, mouse_x, mouse_y, width, height)) {
        // DrawRectangle(x, y, width, height, (Color){255, 250, 155, 50});
        DrawRectangle(
            mouse_offset_x,
            mouse_offset_y,
            cell_size, cell_size, (Color){0, 255, 0, 150});
        is_mouse_down = IsMouseButtonDown(0);
    }

    return (MouseInfo) {
        (((mouse_x - x) / cell_size) % cols),
        ((mouse_y - y) / cell_size),
        is_mouse_down
    };
}


void do_grid(int *grid, int x, int y, int rows, int cols, int cell_size) {
    const int border = 16;
    do_panel(x - border/2, y - border/2, cell_size * cols + border, cell_size * rows + border, GRAY);

    for (int i = 0; i < rows * cols; i++) {
        Color color = WHITE;

        if (grid[i] == 1) color = BLACK;

        DrawRectangle((i % cols) * cell_size + x, (i / rows) * cell_size + y, cell_size, cell_size, color);
    }
}


int do_slider(int *value, int minv, int maxv, int x, int y) {
    const int mouse_x = GetMouseX();
    const int mouse_y = GetMouseY();

    DrawRectangle(x, y, maxv, 8, DARKGRAY);

    int newValue = *value;

    Color highlightColor = LIGHTGRAY;
    if (do_mouse_aabb(x, y, mouse_x, mouse_y, maxv, 8)) {
        highlightColor = WHITE;
        if (IsMouseButtonDown(0)) {
            newValue = mouse_x - x;
            if (newValue < minv) newValue = 0;
            if (newValue > maxv) newValue = maxv;
        }
    }

    DrawRectangle(newValue + x, y - 4, 16, 16, highlightColor);

    char buffer[16];
    sprintf(buffer,"%d", newValue);
    DrawText(buffer, x + maxv + 32, y - 5, 20, WHITE);

    return newValue;
}
