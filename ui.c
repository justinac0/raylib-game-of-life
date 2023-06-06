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

void do_grid(int *grid, int x, int y, int rows, int cols, int cell_size) {
    const int border = 16;
    do_panel(x - border/2, y - border/2, cell_size * cols + border, cell_size * rows + border, GRAY);

    for (int i = 0; i < rows * cols; i++) {
        Color color = WHITE;

        if (grid[i] == 1) color = BLACK;

        DrawRectangle((i % cols) * cell_size + x, (i / rows) * cell_size + y, cell_size, cell_size, color);
    }
}
