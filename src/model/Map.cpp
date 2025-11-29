#include "model/Map.h"
#include "model/Player.h"

void Map::addLocation(const std::string& name, const Location& location) {
    locations[name] = location;
}

void Map::setCurrentLocation(const std::string& location_name) {
    if (locations.find(location_name) != locations.end()) {
        current_location = location_name;
    }
}

Location* Map::getCurrentLocation() {
    if (current_location.empty()) return nullptr;
    return &locations[current_location];
}

const Location* Map::getCurrentLocation() const {
    if (current_location.empty()) return nullptr;
    auto it = locations.find(current_location);
    return it != locations.end() ? &it->second : nullptr;
}

Location* Map::getLocation(const std::string& name) {
    auto it = locations.find(name);
    return it != locations.end() ? &it->second : nullptr;
}

const std::string& Map::getCurrentLocationName() const {
    return current_location;
}

bool Map::changeLocation(const std::string& new_location) {
    if (locations.find(new_location) != locations.end()) {
        current_location = new_location;
        return true;
    }
    return false;
}

void Map::interactWithDoorAt(Player& player, size_t x, size_t y) {
    Location* current = getCurrentLocation();
    if (!current) return;

    Door* door = current->getDoorAt(x, y);
    if (door) {
        changeLocation(door->getTargetLocation());
        player.setPositionAt(door->getTargetPosition());
    }
}