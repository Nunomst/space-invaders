#include "alien.hpp"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position)
{
    this->type     = type;
    this->position = position;

    if (alienImages[type].id == 0)
    {
        switch (type)
        {
        case ALIEN_ONE:
            alienImages[ALIEN_ONE] = LoadTexture("graphics/alien_1.png");
            break;
        case ALIEN_TWO:
            alienImages[ALIEN_TWO] = LoadTexture("graphics/alien_2.png");
            break;
        case ALIEN_THREE:
            alienImages[ALIEN_THREE] = LoadTexture("graphics/alien_3.png");
            break;
        }
    }
}

void Alien::Draw()
{
    DrawTextureV(alienImages[type], position, WHITE);
}

void Alien::Update(int direction)
{
    position.x += direction;
}

int Alien::GetType()
{
    return type;
}

void Alien::UnloadImages()
{
    for (Texture2D& image : alienImages)
    {
        UnloadTexture(image);
    }
}

Rectangle Alien::getRect()
{
    return {position.x, position.y, float(alienImages[type].width),
            float(alienImages[type].height)};
}
