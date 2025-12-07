#include "model/objects/Door.h"
#include "model/Player.h"

Door::Door(
    Position initial_pos,
    std::string name,
    std::string description,
    std::string target_location,
    Position target_pos,
    bool open) :
        Triggerable(initial_pos, std::move(name), std::move(description)),
        target_location(std::move(target_location)),
        target_pos(target_pos),
        is_open(open)
{}

void Door::trigger(Player& player) {
    if (is_open) {
        player.setPositionAt(getTargetPosition());
    }
    // Можно добавить логику, если дверь закрыта ()
}

std::string Door::getTargetLocation() const { return target_location; }
Position Door::getTargetPosition() const { return target_pos; }
bool Door::isOpen() const { return is_open; }

void Door::open() { is_open = true; }
void Door::close() { is_open = false; }