#ifndef MOUSE_INPUT
#define MOUSE_INPUT

#include <stdbool.h>

typedef struct MouseInputState {
    bool is_dragging;
    bool is_mouse_down;
    int x;
    int y;
} MouseInputState;

void mouse_input_poll(MouseInputState *state);

#endif // MOUSE_INPUT