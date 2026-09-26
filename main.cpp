#include "game.hpp"
#include "laser.hpp"
#include <raylib.h>

int main() {
    Color grey = {29, 29, 29, 255};

    const int SCREENWIDTH = 750;
    const int SCREENHEIGHT = 700;

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Scape Invaders");
    SetTargetFPS(60);

    Game game;
    Laser laser = Laser({100, 100}, -7);

    while (WindowShouldClose() == false) {
        game.HandleInput();
        laser.Update();

        BeginDrawing();
        ClearBackground(grey);

        game.Draw();
        laser.Draw();

        EndDrawing();
    }

    CloseWindow();
}
