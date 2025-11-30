#pragma once
#include <vector>
#include <string>
#include "Types.h"

class MapLoader {
public:
    static MapTiles load(const std::string& path);
    static MapTiles loadByName(const std::string& name);
};
