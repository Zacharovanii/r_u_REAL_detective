#include "model/Player.h"

Player::Player(size_t x_, size_t y_) : x(x_), y(y_) {}

size_t Player::getX() const {return x;}
size_t Player::getY() const {return y;}

void Player::setPositionAt(size_t new_x, size_t new_y) {
    x = new_x;
    y = new_y;
}
void Player::setPositionAt(const Position& position) {
    x = position.first;
    y = position.second;
}

// void Player::moveToLocation(const std::string& location_name, const Position& position) {
//     // Этот метод будет вызываться Map для изменения позиции игрока
//     // Реальная логика перемещения между локациями будет в Map
//     setPositionAt(position);
//     // Дополнительная логика, если нужна
// }

void Player::moveUp(const std::vector<std::string>& map) {
    if (y > 0 && map[y - 1][x] != '#') y--;}

void Player::moveDown(const std::vector<std::string>& map) {
    if (y < map.size() - 1 && map[y + 1][x] != '#') y++;}

void Player::moveLeft(const std::vector<std::string>& map) {
    if (x > 0 && map[y][x - 1] != '#') x--;}

void Player::moveRight(const std::vector<std::string>& map) {
    if (x < map[0].size() - 1 && map[y][x + 1] != '#') x++;}