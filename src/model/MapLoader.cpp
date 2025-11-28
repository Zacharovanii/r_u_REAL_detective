#include "model/MapLoader.h"
#include <fstream>
#include <stdexcept>

std::vector<std::string> MapLoader::load(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw std::runtime_error("Failed to load map: " + path);

    std::vector<std::string> map;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty())
            map.push_back(line);
    }

    return map;
}
