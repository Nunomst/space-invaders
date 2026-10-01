#include "mysteryship.hpp"

Mysteryship::Mysteryship() {
    image = LoadTexture("graphics/mystery.png");
    isVisible = false;
}

Mysteryship::~Mysteryship() {
    UnloadTexture(image);
}

void Mysteryship::Update() {
    if (isVisible) {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width || position.x < 0) {
            isVisible = false;
        }
    }
}

void Mysteryship::Draw() {
    if (isVisible) {
        DrawTextureV(image, position, WHITE);
    }
}

void Mysteryship::Spawn() {
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if (side == 0) {
        position.x = 0;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }
    isVisible = true;
}

Rectangle Mysteryship::getRect() {
    if (isVisible) {
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}
