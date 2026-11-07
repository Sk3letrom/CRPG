#pragma once

#include <iostream>
#include <unordered_map>

#include "world/Map.h"
#include "raylib.h"
#include "tileson.hpp"

struct TileInstance {

    tson::LayerType type;
    uint32_t tileID;
    int gridX;
    int gridY;
    std::string imagePath;
    Rectangle tileImage;

};

struct TileCollision {
    std::string type;
    Rectangle rect;

};

struct SpawnPoint {
    tson::LayerType type;
    std::string name;
    Vector2 spawnPosition;

};


class TileMap {

    public:
        TileMap();
        ~TileMap();

        bool Load(const std::string& mapPath);
        void Unload();
        bool IsLoaded() const { return loaded_; }

        void Draw();


        const std::vector<Rectangle> GetCollisions() const { 
            std::vector<Rectangle> collisionRects;
            for (const auto& collision : collisions_) {
                collisionRects.push_back(collision.rect);
            }
            return collisionRects;
        }


    private:

        void ExtractTileLayers();
        void ExtractCollisions();
        void ExtractSpawnPoint();
        void LoadTilesets();

        Texture2D GetTileTexture(uint32_t tileID);
        
        bool loaded_;
        Map map_;

        tson::Vector2i TileSize;

        std::vector<TileInstance> tiles_;
        std::vector<TileCollision> collisions_;
        mutable std::unordered_map<int, Texture2D> tilesetTextures_;  // Cache de texturas carregadas
        SpawnPoint spawnPoint_;

};