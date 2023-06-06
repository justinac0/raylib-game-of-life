#include "mouse_input.h"

#include <raylib.h>

void mouse_input_poll(MouseInputState *state) {
    if (IsMouseButtonDown(0)) {
        state->is_dragging = true;
    }

    if (IsMouseButtonReleased(0)) {
        state->is_dragging = false;
    }

    state->x = GetMouseX();
    state->y = GetMouseY();
}
