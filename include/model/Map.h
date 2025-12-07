#pragma once
#include <unordered_map>
#include <string>
#include "Location.h"

class Map {
private:
    std::unordered_map<std::string, Location> locations;
    std::string current_location;

public:
    Map() = default;

    void addLocation(const std::string& name, Location location);
    void setCurrentLocation(const std::string& location_name);

    [[nodiscard]] Location* getCurrentLocation();
    [[nodiscard]] const std::string& getCurrentLocationName() const;

    bool changeLocation(const std::string& new_location);
};