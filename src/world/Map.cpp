#include "world/Map.h"
#include <filesystem>
#include <fstream>


Map::Map() : loaded_(false) {}

Map::~Map() {
    Unload();
}

bool Map::Load(const std::string& mapPath) {
    // Tentar encontrar o arquivo em vários locais possíveis
    std::vector<std::string> possiblePaths = {
        mapPath,                                    // Caminho fornecido
        std::string("maps/") + mapPath,            // Relativo à raiz do projeto
        std::string("../") + mapPath,              // Um nível acima
        std::string("../../") + mapPath            // Dois níveis acima
    };

    std::string foundPath;
    for (const auto& path : possiblePaths) {
        if (std::filesystem::exists(path)) {
            foundPath = path;
            break;
        }
    }

    if (foundPath.empty()) {
        std::cerr << "Arquivo não encontrado: " << mapPath << std::endl;
        std::cerr << "Diretório atual: " << std::filesystem::current_path() << std::endl;
        return false;
    }

    // Usar Tileson para fazer parse do arquivo
    tson::Tileson tileson;
    tiledMap_ = tileson.parse(foundPath);
    
    if (tiledMap_->getStatus() != tson::ParseStatus::OK) {
        std::cerr << "Falha ao carregar o mapa: " << foundPath << std::endl;
        std::cerr << "Status: " << (int)tiledMap_->getStatus() << std::endl;
        // Status: 0=OK, 1=NotParsed, 2=MissingData, 3=DecodingFailed
        switch(tiledMap_->getStatus()) {
            case tson::ParseStatus::OK:
                std::cerr << "Descricao: OK" << std::endl;
                break;
            case tson::ParseStatus::ParseError:
                std::cerr << "Descricao: Nao foi feito parse" << std::endl;
                break;
            case tson::ParseStatus::MissingData:
                std::cerr << "Descricao: Dados faltando" << std::endl;
                break;
            case tson::ParseStatus::DecompressionError:
                std::cerr << "Descricao: Falha ao decodificar" << std::endl;
                break;
            default:
                std::cerr << "Descricao: Status desconhecido" << std::endl;
        }
        return false;
    }

    loaded_ = true;
    return true;
}

void Map::Unload() {
    tiledMap_.reset();
    loaded_ = false;
}
