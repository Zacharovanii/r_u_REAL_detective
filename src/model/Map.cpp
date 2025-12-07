#include "model/Map.h"
#include "model/Player.h"

void Map::addLocation(const std::string& name, Location location) {
    locations.insert({name, std::move(location)});
}

const std::string& Map::getCurrentLocationName() const { return current_location;}

void Map::setCurrentLocation(const std::string& location_name) {
    if (locations.contains(location_name))
        current_location = location_name;
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

bool Map::changeLocation(const std::string& new_location) {
    if (locations.contains(new_location)) {
        current_location = new_location;
        return true;
    }
    return false;
}

void Map::interactAt(size_t x, size_t y) {
    if (Location* current = getCurrentLocation()) {
        current->interactAt(x, y);
    }
}


void Map::triggerDoorAt(Player& player, size_t x, size_t y) {
    Location* current = getCurrentLocation();
    if (!current) return;

    if (Door* door = current->getDoorAt(x, y)) {
        changeLocation(door->getTargetLocation());
        door->trigger(player);
    }
}