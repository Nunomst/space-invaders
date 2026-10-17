#include "core/game.hpp"
#include "ui/hud.hpp"
#include <raylib.h>

int main()
{
    Color grey = {29, 29, 29, 255};

    const int offset       = 50;
    const int SCREENWIDTH  = 750;
    const int SCREENHEIGHT = 700;

    InitWindow(SCREENWIDTH + offset, SCREENHEIGHT + (offset * 2), "Space Invaders");
    InitAudioDevice();

    SetTargetFPS(60);

    Game game;
    Hud hud;

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);

        hud.Draw(game.score, game.highscore, game.lives, game.run);

        game.Draw();
        EndDrawing();
    }

    hud.Unload();
    CloseAudioDevice();
    CloseWindow();
}
