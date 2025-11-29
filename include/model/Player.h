#pragma once
#include <string>
#include <vector>
#include "Types.h"

class Player {
    size_t x, y;
    int hp = 100;
    std::string status = "Тестовый";

public:
    Player(size_t x_, size_t y_);

    [[nodiscard]] size_t getX() const;
    [[nodiscard]] size_t getY() const;

    void setPositionAt(const Position& position);
    void setPositionAt(size_t new_x, size_t new_y);

    // void moveToLocation(const std::string& location_name, const Position& position);

    // Старые методы можно оставить для совместимости или удалить
    void moveUp(const std::vector<std::string>& map);
    void moveDown(const std::vector<std::string>& map);
    void moveLeft(const std::vector<std::string>& map);
    void moveRight(const std::vector<std::string>& map);
};
