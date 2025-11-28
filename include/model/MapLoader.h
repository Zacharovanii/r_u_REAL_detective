#pragma once
#include <vector>
#include <string>

class MapLoader {
public:
    static std::vector<std::string> load(const std::string& path);
};
