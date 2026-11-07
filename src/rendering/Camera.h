#pragma once

#include "raylib.h"

class GameCamera
{
public:
    GameCamera();

    void Follow(Vector2 target);
    void Begin();
    void End();

    Camera2D& GetRaylibCamera();

private:
    Camera2D camera_;
};
