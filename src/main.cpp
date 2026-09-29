#include "game.hpp"
#include <raylib.h>

int main() {
    Color grey = {29, 29, 29, 255};

    const int SCREENWIDTH = 750;
    const int SCREENHEIGHT = 700;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Scape Invaders");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false) {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}
