#include "game.hpp"

Game::Game() {
    obstacles = CreateObstacles();
    aliens = CreateAliens();
}

Game::~Game() {}

void Game::Draw() {
    spaceship.Draw();

    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }

    for (auto& obstacle : obstacles) {
        obstacle.Draw();
    }

    for (auto& alien : aliens) {
        alien.Draw();
    }
}

void Game::Update() {
    for (auto& laser : spaceship.lasers) {
        laser.Update();
    }

    DeleteInactiveLasers();
}

void Game::HandleInput() {
    if (IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    } else if (IsKeyDown(KEY_SPACE)) {
        spaceship.FireLase();
    }
}

void Game::DeleteInactiveLasers() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->isActive) {
            spaceship.lasers.erase(it);
        } else {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens() {
    int NUMBER_OF_ROWS = 5;
    int NUMBER_OF_COLUMNS = 11;
    int CELL_SIZE = 55;

    std::vector<Alien> aliens;

    for (int row = 0; row < NUMBER_OF_ROWS; row++) {
        for (int column = 0; column < NUMBER_OF_COLUMNS; column++) {
            float x = column * CELL_SIZE;
            float y = row * CELL_SIZE;

            aliens.push_back(Alien(1, {x, y}));
        }
    }
    return aliens;
}
