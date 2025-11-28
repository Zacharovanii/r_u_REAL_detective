#include "model/Model.h"

Model::Model() {
    map = std::vector<std::string>(rows, std::string(cols, '.'));

    // Сгенерируем зоны травы
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {

            int r = rand() % 100;

            if (r < 55) map[y][x] = '.';        // земля
            else if (r < 80) map[y][x] = ',';   // трава
            else if (r < 90) map[y][x] = '~';   // вода
            else map[y][x] = '#';               // камень/дом
        }
    }

    // NPC
    map[4][6] = 'N';
    map[2][10] = 'N';

    // Items
    map[6][3] = 'I';
    map[8][8] = 'I';

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
