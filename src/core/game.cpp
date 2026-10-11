#include "game.hpp"
#include <fstream>
#include <iostream>

Game::Game()
{
    music          = LoadMusicStream("sounds/music.ogg");
    explosionSound = LoadSound("sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

void Game::Draw()
{
    spaceship.Draw();

    for (auto& laser : spaceship.lasers)
    {
        laser.Draw();
    }

    for (auto& obstacle : obstacles)
    {
        obstacle.Draw();
    }

    for (auto& alien : aliens)
    {
        alien.Draw();
    }

    for (auto& alienLaser : alienLasers)
    {
        alienLaser.Draw();
    }

    mysteryship.Draw();
}

void Game::Update()
{

    if (run)
    {
        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval)
        {
            mysteryship.Spawn();
            timeLastSpawn            = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto& laser : spaceship.lasers)
        {
            laser.Update();
        }

        MoveAliens();

        AlienShootLaser();

        for (auto& alienLaser : alienLasers)
        {
            alienLaser.Update();
        }

        CheckForCollisions();
        DeleteInactiveLasers();

        mysteryship.Update();
    }
}

void Game::HandleInput()
{
    if (run)
    {
        if (IsKeyDown(KEY_LEFT))
        {
            spaceship.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            spaceship.MoveRight();
        }
        if (IsKeyDown(KEY_SPACE))
        {
            spaceship.FireLaser();
        }
    }
    else if (IsKeyDown(KEY_ENTER))
    {
        Reset();
    }
}

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->isActive)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->isActive)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap         = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    int NUMBER_OF_ROWS    = 5;
    int NUMBER_OF_COLUMNS = 11;
    int CELL_SIZE         = 55;
    int X_OFFSET          = 75;
    int Y_OFFSET          = 110;

    std::vector<Alien> aliens;

    for (int row = 0; row < NUMBER_OF_ROWS; row++)
    {
        for (int column = 0; column < NUMBER_OF_COLUMNS; column++)
        {
            int alienType;
            if (row == 0)
            {
                alienType = 3;
            }
            else if (row == 1 || row == 2)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }

            float x = X_OFFSET + column * CELL_SIZE;
            float y = Y_OFFSET + row * CELL_SIZE;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    bool hitEdge = false;

    for (auto& alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            hitEdge         = true;
        }
        if (alien.position.x < 25)
        {
            aliensDirection = 1;
            hitEdge         = true;
        }
    }
    if (hitEdge)
    {
        MoveDownAliens(4);
    }

    for (auto& alien : aliens)
    {
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto& alien : aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime();

    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien    = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width / 2,
                                     alien.position.y + alien.alienImages[alien.type - 1].height},
                                    6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{

    // SPACESHIP LASERS
    for (auto& laser : spaceship.lasers)
    {

        if (laser.isActive)
        {
            auto it = aliens.begin();

            while (it != aliens.end())
            {
                if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                {

                    PlaySound(explosionSound);

                    if (it->type == 1)
                    {
                        score += 100;
                    }
                    else if (it->type == 2)
                    {
                        score += 200;
                    }
                    else if (it->type == 3)
                    {
                        score += 300;
                    }
                    CheckForHighScore();

                    it             = aliens.erase(it);
                    laser.isActive = false;
                    break;
                }
                else
                {
                    it++;
                }
            }
        }

        if (laser.isActive)
        {
            for (auto& obstacle : obstacles)
            {
                auto best = obstacle.blocks.end();

                for (auto it = obstacle.blocks.begin(); it != obstacle.blocks.end(); it++)
                {
                    if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                    {
                        if (best == obstacle.blocks.end() || it->getRect().y > best->getRect().y)
                        {
                            best = it;
                        }
                    }
                }

                if (best != obstacle.blocks.end())
                {
                    obstacle.blocks.erase(best);
                    laser.isActive = false;
                }
            }
        }

        if (laser.isActive)
        {
            if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect()))
            {
                mysteryship.isVisible = false;
                laser.isActive        = false;
                score += 500;
                CheckForHighScore();
                PlaySound(explosionSound);
            }
        }
    }

    // ALLIEN LASERS
    for (auto& laser : alienLasers)
    {
        if (laser.isActive)
        {
            if (CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
            {
                lives--;
                laser.isActive = false;
                if (lives == 0)
                {
                    GameOver();
                }
            }
        }

        if (laser.isActive)
        {
            for (auto& obstacle : obstacles)
            {
                auto it = obstacle.blocks.begin();
                while (it != obstacle.blocks.end())
                {
                    if (CheckCollisionRecs(it->getRect(), laser.getRect()))
                    {
                        it             = obstacle.blocks.erase(it);
                        laser.isActive = false;
                        break;
                    }
                    else
                    {
                        it++;
                    }
                }
            }
        }
    }

    // ALLIEN COLISION WITH OBSTACLE
    for (auto& alien : aliens)
    {
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->getRect(), alien.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }

        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
        {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    run = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    InitGame();
}

void Game::InitGame()
{
    obstacles                = CreateObstacles();
    aliens                   = CreateAliens();
    aliensDirection          = 1;
    timeLastAlienFired       = GetTime();
    timeLastSpawn            = GetTime();
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    lives                    = 3;
    run                      = true;
    score                    = 0;
    highscore                = LoadHighScoreFromFile();
}

void Game::CheckForHighScore()
{
    if (score > highscore)
    {
        highscore = score;
        SaveHighScoreToFile(highscore);
    }
}

void Game::SaveHighScoreToFile(int highScore)
{
    std::ofstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open())
    {
        highScoreFile << highScore;
        highScoreFile.close();
    }
    else
    {
        std::cerr << "Failder to save highscore to file" << std::endl;
    }
}

int Game::LoadHighScoreFromFile()
{
    int loadedHighScore = 0;
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open())
    {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    }
    else
    {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighScore;
}
