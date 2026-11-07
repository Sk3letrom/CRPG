#include "rendering/Renderer.h"
#include "raylib.h"

void Renderer::BeginFrame()
{
    BeginDrawing();
    ClearBackground(BLACK);
}

void Renderer::EndFrame()
{
    EndDrawing();
}

void Renderer::DrawTile(Texture2D texture, Rectangle source, Rectangle dest)
{
    DrawTexturePro(texture, source, dest, {0, 0}, 0.0f, WHITE);
}

void Renderer::DrawRect(Rectangle rect, Color color)
{
    DrawRectangleRec(rect, color);
}
