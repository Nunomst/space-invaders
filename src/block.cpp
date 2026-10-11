#include "block.hpp"

Block::Block(Vector2 position)
{
    this->position = position;
}

void Block::Draw()
{
    DrawRectangle(position.x, position.y, 3, 3, RED);
}

Rectangle Block::getRect()
{
    return {position.x, position.y, 3, 3};
}
