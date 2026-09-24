#include <raylib.h>

int main() {
    Color grey = {29, 29, 29, 255};

    const int SCREENWIDTH = 750;
    const int SCREENHEIGHT = 700;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Scape Invaders");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(grey);

        EndDrawing();
    }

    CloseWindow();
}
