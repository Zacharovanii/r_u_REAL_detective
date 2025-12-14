#include "model/objects/Door.h"
#include "model/Player.h"

Door::Door(
    Position initial_pos,
    std::string target_location,
    Position target_pos,
    Position end_point,
    bool isLine
):
    Triggerable(initial_pos),
    target_location(std::move(target_location)),
    target_pos(target_pos),
    end_line_point(end_point),
    isLine(isLine)
{}

Door::Door(
    Position initial_pos,
    std::string target_location,
    Position target_pos
):
    Door(
        initial_pos,
        std::move(target_location),
        target_pos,
        {0 ,0},
        false)
{}

Door::Door(
    Position initial_pos,
    std::string target_location,
    Position target_pos,
    Position end_point
):
    Door(
        initial_pos,
        std::move(target_location),
        target_pos,
        end_point,
        true)
{}

void Door::trigger(Player& player) {
    player.setPositionAt(getTargetPosition());
}

bool Door::isTriggered(Position pos) const {
    if (!isLine) {
        return pos == getPosition();
    }

    const Position& a = getPosition();
    const Position& b = end_line_point;

    if (a.x == b.x) {
        return pos.x == a.x &&
               pos.y >= std::min(a.y, b.y) &&
               pos.y <= std::max(a.y, b.y);
    }

    if (a.y == b.y) {
        return pos.y == a.y &&
               pos.x >= std::min(a.x, b.x) &&
               pos.x <= std::max(a.x, b.x);
    }
    return false;
}


std::string Door::getTargetLocation() const { return target_location; }
Position Door::getTargetPosition() const { return target_pos; }