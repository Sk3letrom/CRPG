#include "core/Game.h"
#include "world/TileMap.h"
#include "rendering/Renderer.h"

#include "raylib.h"
#include <iostream>
#include <memory>

Game::Game() : running_(false), renderer_(nullptr), tileMap_(nullptr) {}

Game::~Game()
{
    if (IsWindowReady())
        CloseWindow();
}

void Game::Initialize()
{
    InitWindow(1280, 720, "CRPG");
    SetTargetFPS(60);
    running_ = true;

    // Inicializar renderizador
    renderer_ = std::make_unique<Renderer>();

    // Inicializar e carregar mapa
    tileMap_ = std::make_unique<TileMap>();
    if (!tileMap_->Load("maps/test1/tmx/test1.json"))
    {
        running_ = false;
        return;
    }


}

void Game::Update(float deltaTime)
{
    (void)deltaTime;

    if (WindowShouldClose())
        running_ = false;
}

void Game::Render()
{
    renderer_->BeginFrame();

    // Renderizar mapa
    if (tileMap_ && tileMap_->IsLoaded())
    {
        tileMap_->Draw();
    } 
    // Debug: Desenhar colisões
    if (tileMap_)
    {
        auto& collisions = tileMap_->GetCollisions();
        for (auto& collision : collisions)
        {
            renderer_->DrawRect(collision, {255, 0, 0, 100});
        }
    }

    // UI
    DrawText("CRPG - raylib prototype", 30, 30, 28, RAYWHITE);
    DrawText("Carregando mapa...", 30, 70, 20, LIGHTGRAY);

    renderer_->EndFrame();
}

void Game::Run()
{
    Initialize();

    while (running_)
    {
        Update(GetFrameTime());
        Render();
    }
}
