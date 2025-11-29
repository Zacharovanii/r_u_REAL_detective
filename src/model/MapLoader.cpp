#include "model/MapLoader.h"
#include <fstream>
#include <stdexcept>

MapTiles MapLoader::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to load map: " + path);

    MapTiles map;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty())
            map.push_back(line);
    }

    return map;
}

MapTiles MapLoader::loadByName(const std::string& name) {
    std::string filename = "data/maps/" + name + ".map";
    MapTiles map = MapLoader::load(filename);

    if (map.empty()) {
        throw std::runtime_error("Loaded map is empty: " + filename);
    }

    return map;
}
