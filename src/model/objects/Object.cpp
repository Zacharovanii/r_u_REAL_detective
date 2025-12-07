#include "model/objects/Object.h"

Object::Object(
    const Position& initial_pos,
    const std::string& name,
    const std::string& description
    ) : position(initial_pos), name(name), description(description)
{}

std::string Object::getName() const { return name; }
std::string Object::getDescription() const { return description; }

size_t Object::getX() const { return position.first; }
size_t Object::getY() const { return position.second; }

void Object::setX(size_t new_value) { position.first = new_value; }
void Object::setY(size_t new_value) { position.second = new_value; }

Position Object::getPosition() const { return position; }
void Object::setPosition(const Position& new_pos) { position = new_pos; }

bool Object::isIntersect(const Position& pos) const {
    return position.first == pos.first && position.second == pos.second;
}
bool Object::isIntersect(size_t x, size_t y) const {
    return position.first == x && position.second == y;
}