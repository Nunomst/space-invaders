#pragma once
#include <raylib.h>

class Alien
{
  public:
    enum AlienType
    {
        ALIEN_ONE,
        ALIEN_TWO,
        ALIEN_THREE
    };

    Alien(int type, Vector2 position);
    void Draw();
    void Update(int direction);
    int GetType();
    static void UnloadImages();
    Rectangle getRect();
    static Texture2D alienImages[3];
    int type;
    Vector2 position;

  private:
};
