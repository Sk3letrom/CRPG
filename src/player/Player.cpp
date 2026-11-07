#include "player/Player.h"
#include "raylib.h"
#include "raymath.h"

Player::Player()
    : position_{640.0f, 360.0f}
    , speed_(200.0f)
{
}

void Player::Update(float deltaTime)
{
    Vector2 direction{0.0f, 0.0f};

    if (IsKeyDown(KEY_W)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_S)) direction.y += 1.0f;
    if (IsKeyDown(KEY_A)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_D)) direction.x += 1.0f;

    if (Vector2Length(direction) > 0.0f)
    {
        direction = Vector2Normalize(direction);
        position_.x += direction.x * speed_ * deltaTime;
        position_.y += direction.y * speed_ * deltaTime;
    }
}

void Player::Draw() const
{
    DrawCircleV(position_, 16.0f, BLUE);
    DrawCircleLines(
        static_cast<int>(position_.x),
        static_cast<int>(position_.y),
        16.0f,
        RAYWHITE
    );
}

Vector2 Player::GetPosition() const
{
    return position_;
}

void Player::SetPosition(Vector2 position)
{
    position_ = position;
}
