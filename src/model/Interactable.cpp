#include "model/Interactable.h"

Interactable::Interactable(const Position& initial_pos, const std::string& name, const std::string& description) :
    position(initial_pos), name(std::move(name)), description(std::move(description)) {}

Interactable::~Interactable() {}

std::string Interactable::getName() const { return name; }
std::string Interactable::getDescription() const { return description; }

size_t Interactable::getX() const { return position.first; }
size_t Interactable::getY() const { return position.second; }

void Interactable::setX(size_t new_value) { position.first = new_value; }
void Interactable::setY(size_t new_value) { position.second = new_value; }

Position Interactable::getPosition() const { return position; }
void Interactable::setPosition(const Position& new_pos) { position = new_pos; }

bool Interactable::isIntersect(const Position& pos) const {
    return position.first == pos.first && position.second == pos.second;
}
bool Interactable::isIntersect(size_t x, size_t y) const {
    return position.first == x && position.second == y;
}