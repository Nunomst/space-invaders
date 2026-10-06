#include "game.hpp"
#include <raylib.h>

int main() {
    Color grey = {29, 29, 29, 255};
    Color yellow = {243, 216, 63, 255};

    const int offset = 50;
    const int SCREENWIDTH = 750;
    const int SCREENHEIGHT = 700;

    InitWindow(SCREENWIDTH + offset, SCREENHEIGHT + (offset * 2), "Scape Invaders");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false) {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);

        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}
