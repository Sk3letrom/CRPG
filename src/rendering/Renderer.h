#pragma once

#include "raylib.h"

class Renderer
{
public:
    void BeginFrame();
    void EndFrame();

    // Desenhar um tile na tela
    void DrawTile(Texture2D texture, Rectangle source, Rectangle dest);
    
    // Desenhar retângulo (debug de colisões)
    void DrawRect(Rectangle rect, Color color);
};
