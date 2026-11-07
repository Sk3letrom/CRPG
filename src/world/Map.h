#pragma once

#include <string>
#include <algorithm>
#include <memory>
#include <cstdint>
#include "tileson.hpp"


class Map {

    public:
        Map();
        ~Map();

        bool Load(const std::string& mapPath);
        void Unload();
        bool IsLoaded() const { return loaded_; }

        tson::Map& GetTiledMap() { return *tiledMap_; }
        const tson::Map& GetTiledMap() const { return *tiledMap_; }


    private:
        std::unique_ptr<tson::Map> tiledMap_;
        bool loaded_;



};
