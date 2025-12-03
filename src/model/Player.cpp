#include "model/Player.h"


Player::Player(const Position& initial_position) : position(initial_position) {}
Player::Player(size_t x_, size_t y_) : position(x_, y_) {}

Position Player::getPosition() const {return position;}
size_t Player::getX() const {return position.first;}
size_t Player::getY() const {return position.second;}
std::string Player::getStatus() const { return status;}

void Player::setX(size_t new_x) { position.first = new_x; }
void Player::setY(size_t new_y) { position.second = new_y; }
void Player::setPositionAt(size_t new_x, size_t new_y) {
    position.first = new_x;
    position.second = new_y;
}
void Player::setPositionAt(const Position& new_position) {
    position = new_position;
}
void Player::setStatus(const std::string& new_status) {
    status = new_status;
}