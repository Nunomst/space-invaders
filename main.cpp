#include <raylib.h>

int main() {
    const int SCREENWIDTH = 750;
    const int SCREENHEIGHT = 700;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Scape Invaders");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
}
