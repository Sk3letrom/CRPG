#include "TileMap.h"

TileMap::TileMap() : loaded_(false) {}

TileMap::~TileMap() {
    Unload();
}

bool TileMap::Load(const std::string& mapPath) {
    // Carregar o mapa usando a classe Map
    if (!map_.Load(mapPath)) {
        std::cerr << "Mapa não carregado! " << mapPath << std::endl;
        return false;
    }

    std::cout << "[DEBUG] Mapa carregado com sucesso" << std::endl;
    std::cout << "[DEBUG] Número de camadas: " << map_.GetTiledMap().getLayers().size() << std::endl;

    // Carregar tilesets
    LoadTilesets();

    // Extrair informações do mapa

    ExtractTileLayers();
    std::cout << "[DEBUG] Tiles extraídos: " << tiles_.size() << std::endl;
    
    ExtractCollisions();
    std::cout << "[DEBUG] Colisões extraídas: " << collisions_.size() << std::endl;
    
    ExtractSpawnPoint();
    
    loaded_ = true;
    return true;
}

void TileMap::Unload() {
    map_.Unload(); // deletar os tiles deleta o mapa
    
    // Descarregar texturas
    for (auto& [key, texture] : tilesetTextures_) {
        UnloadTexture(texture);
    }
    tilesetTextures_.clear();
    
    loaded_ = false;
}

void TileMap::LoadTilesets() {
    // Iterar sobre todos os tilesets do mapa
    for (const auto& tileset : map_.GetTiledMap().getTilesets()) {
        std::cout << "[DEBUG] Carregando tileset: " << tileset.getName() << " (firstgid: " << tileset.getFirstgid() << ")" << std::endl;
        
        // Tentar obter a imagem do tileset
        // Para tilesets de imagem (image collection), cada tile tem sua própria imagem
        // Para tilesets normais, há uma única imagem
        
        // Se é image collection, as imagens estão nos tiles individuais
        if (tileset.getTileCount()> 0) {
            // Para tilesets normais com atlas
            // Carregamos a imagem base do tileset (se houver)
            // Por enquanto, vamos retornar um placeholder
            
            std::cout << "[DEBUG]   Tileset tem " << tileset.getTileCount() << " tiles" << std::endl;
            
            // Armazenar informações do tileset para lookup posterior
            // Usando firstgid como chave
            // Por enquanto, deixar como placeholder cinzento (texture id 0)
        }
    }
}

void TileMap::ExtractTileLayers() {
    
    TileSize = map_.GetTiledMap().getTileSize();
    std::cout << "[DEBUG] TileSize: " << TileSize.x << " x " << TileSize.y << std::endl;

    for (auto& layer : map_.GetTiledMap().getLayers()) {
        std::cout << "[DEBUG] Processando camada: " << layer.getName() << " tipo: " << (int)layer.getType() << std::endl;
        // camada de tiles comum
        if (layer.getType() == tson::LayerType::TileLayer) {
            const auto& tileData = layer.getTileData();
            std::cout << "[DEBUG] Tiles nesta camada: " << tileData.size() << std::endl;
            for (const auto& [pos, tile] : tileData) {
                if (tile == nullptr) continue;
                
                TileInstance tileInstance;
                tileInstance.tileID = tile->getId();
                tileInstance.gridX = std::get<0>(pos);
                tileInstance.gridY = std::get<1>(pos);
                tileInstance.imagePath = tile->getImage();
                tileInstance.type = layer.getType();

                tiles_.push_back(tileInstance);
            }
        }
    }

}

void TileMap::ExtractCollisions() {
    for (auto& layer : map_.GetTiledMap().getLayers()) {

        if (layer.getType() == tson::LayerType::ObjectGroup && layer.getName() != "player_spawn") { // RETIRAR DPS!!!
            
            for (const auto& object : layer.getObjects()) {
                TileCollision collision;
                collision.type = object.getType();
                collision.rect = { (float)object.getPosition().x, (float)object.getPosition().y, (float)object.getSize().x, (float)object.getSize().y };
                collisions_.push_back(collision);
            }
        }
    }
}

void TileMap::ExtractSpawnPoint() {
    for (auto& layer : map_.GetTiledMap().getLayers()) {
        if (layer.getType() == tson::LayerType::ObjectGroup && layer.getName() == "player_spawn") {
            for (const auto& object : layer.getObjects()) {
                if (object.getType() == "spawn_point") {
                    spawnPoint_.type = layer.getType();
                    spawnPoint_.name = object.getName();
                    spawnPoint_.spawnPosition = { (float)object.getPosition().x, (float)object.getPosition().y };
                    return; // Encontrou o ponto de spawn, pode sair
                }
            }
        }
    }
}

void TileMap::Draw() {
    for (const auto& tileInstance : tiles_) {
        Texture2D texture = GetTileTexture(tileInstance.tileID);
        if (texture.id == 0) {
            std::cout <<"textura id 0" << std::endl;
            continue;
        } // Se a textura não foi carregada, pular
        std::cout <<"        TESTE       " << std::endl;
        Rectangle sourceRect = tileInstance.tileImage;
        Vector2 position = { static_cast<float>(tileInstance.gridX * TileSize.x), static_cast<float>(tileInstance.gridY * TileSize.y) };
        DrawTextureRec(texture, sourceRect, position, WHITE);
    }
}

Texture2D TileMap::GetTileTexture(uint32_t tileID) {
    // Encontrar o tileset que contém este tile ID
    for ( const auto& tileset : map_.GetTiledMap().getTilesets()) {
        uint32_t firstgid = tileset.getFirstgid();
        uint32_t lastgid = firstgid + tileset.getTileCount() - 1;
        
        if (tileID >= firstgid && tileID <= lastgid) {
            // Este tileset contém o tile
            uint32_t localTileID = tileID - firstgid;
            
            // Procurar pelo tile específico (getTiles() não é const, então fazer const_cast)
            auto& tiles = const_cast<tson::Tileset&>(tileset).getTiles();
            if (localTileID < tiles.size()) {
                const auto& tile = tiles[localTileID];
                
                // Para image collection, cada tile tem uma imagem
                auto imagePath = tile.getImage();
                if (!imagePath.empty()) {
                    // Construir o caminho completo da imagem
                    std::string fullPath = "maps/test1/tmx/" + std::string(imagePath.string());
                    
                    // Verificar se já foi carregado
                    auto it = tilesetTextures_.find(tileID);
                    if (it != tilesetTextures_.end()) {
                        return it->second;
                    }
                    
                    // Carregar a textura
                    if (FileExists(fullPath.c_str())) {
                        Texture2D texture = LoadTexture(fullPath.c_str());
                        tilesetTextures_[tileID] = texture;
                        return texture;
                    } else {
                        std::cerr << "[WARNING] Imagem não encontrada: " << fullPath << std::endl;
                    }
                }
            }
            break;
        }
    }
    
    // Se não encontrou, retornar textura vazia (0)
    return {0};
}