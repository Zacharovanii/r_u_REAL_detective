#include "model/Door.h"

#include <iostream>

#include "model/Player.h"

Door::Door(const Position& initial_pos, const std::string& name, const std::string& description,
         const std::string& target_location, const Position& target_pos, bool open) :
        Interactable(initial_pos, name, description),
        target_location(std::move(target_location)),
        target_pos(target_pos),
        is_open(open)
{};

void Door::interact(Player& player) {
    if (is_open) {
        std::cout << player.getX();
    }
    // Можно добавить логику, если дверь закрыта ()
}

std::string Door::getTargetLocation() const { return target_location; }
Position Door::getTargetPosition() const { return target_pos; }
bool Door::isOpen() const { return is_open; }

void Door::open() { is_open = true; }
void Door::close() { is_open = false; }