#pragma once

#include "raylib.h"

class Player
{
public:
    Player();

    void Update(float deltaTime);
    void Draw() const;

    Vector2 GetPosition() const;
    void SetPosition(Vector2 position);

private:
    Vector2 position_;
    float speed_;
};
