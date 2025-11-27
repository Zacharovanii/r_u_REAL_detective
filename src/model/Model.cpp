#include "Model.h"

Model::Model() {
    map = std::vector<std::string>(rows, std::string(cols, '_'));
    player = {2, 2};
}

const Model::Player& Model::getPlayer() const {
    return player;
}

const std::vector<std::string>& Model::getMap() const {
    return map;
}

void Model::moveUp() {
    if (player.y > 0) player.y--;
}

void Model::moveDown() {
    if (player.y < rows - 1) player.y++;
}

void Model::moveLeft() {
    if (player.x > 0) player.x--;
}

void Model::moveRight() {
    if (player.x < cols - 1) player.x++;
}
