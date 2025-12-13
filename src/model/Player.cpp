#include "model/Player.h"

Player::Player(const Position& initial_position)
    : position(initial_position) {}

Player::Player(size_t x_, size_t y_)
    : position(Position{x_, y_}) {}

Position Player::getPosition() const { return position; }
size_t Player::getX() const { return position.x; }
size_t Player::getY() const { return position.y; }

void Player::setX(size_t new_x) { position.x = new_x; }
void Player::setY(size_t new_y) { position.y = new_y; }

void Player::setPositionAt(size_t new_x, size_t new_y) {
    position.x = new_x;
    position.y = new_y;
}

void Player::setPositionAt(const Position& new_position) {
    position = new_position;
}

int Player::getBadges() const { return badges; }
int Player::getMoney()  const { return money; }
int Player::getHealth() const { return health; }
int Player::getFlirt()  const { return flirt; }


void Player::changeBadges(int value) {
    badges += value;
    if (badges < 0) badges = 0;
}

void Player::changeMoney(int value) {
    money += value;
    if (money < 0) money = 0;
}

void Player::changeHealth(int value) {
    health += value;
    if (health < 0) health = 0;
}

void Player::changeFlirt(int value) {
    flirt += value;
    if (flirt < 0) flirt = 0;
}