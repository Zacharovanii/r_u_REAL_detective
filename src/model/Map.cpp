#include "model/Map.h"

void Map::addLocation(const std::string& name, Location location) {
    locations.insert({name, std::move(location)});
}

const std::string& Map::getCurrentLocationName() const { return current_location;}

Location* Map::getCurrentLocation() {
    if (current_location.empty()) return nullptr;
    return &locations[current_location];
}

void Map::setCurrentLocation(const std::string& location_name) {
    if (locations.contains(location_name))
        current_location = location_name;
}

bool Map::changeLocation(const std::string& new_location) {
    if (locations.contains(new_location)) {
        current_location = new_location;
        return true;
    }
    return false;
}