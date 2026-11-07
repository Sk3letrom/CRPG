#include "rendering/Camera.h"
#include "raylib.h"

GameCamera::GameCamera()
{
    camera_.offset = {
        static_cast<float>(GetScreenWidth()) / 2.0f,
        static_cast<float>(GetScreenHeight()) / 2.0f
    };
    camera_.target = {0.0f, 0.0f};
    camera_.rotation = 0.0f;
    camera_.zoom = 1.0f;
}

void GameCamera::Follow(Vector2 target)
{
    camera_.target = target;
}

void GameCamera::Begin()
{
    BeginMode2D(camera_);
}

void GameCamera::End()
{
    EndMode2D();
}

Camera2D& GameCamera::GetRaylibCamera()
{
    return camera_;
}
