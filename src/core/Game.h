#pragma once

#include <memory>

class TileMap;
class Renderer;

class Game
{
public:
    Game();
    ~Game();

    void Run();

private:
    void Initialize();
    void Update(float deltaTime);
    void Render();

    bool running_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<TileMap> tileMap_;
};
