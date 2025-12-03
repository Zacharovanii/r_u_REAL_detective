#pragma once
#include <string>
#include "helpers/Types.h"

class Player {
    Position position;
    std::string status = "Тестовый";

public:
    explicit Player(const Position& initial_position);
    Player(size_t x_, size_t y_);

    [[nodiscard]] size_t getX() const;
    [[nodiscard]] size_t getY() const;

    [[nodiscard]] Position getPosition() const;

    void setX(size_t new_x);
    void setY(size_t new_y);
    void setPositionAt(const Position& new_position);
    void setPositionAt(size_t new_x, size_t new_y);

    std::string getStatus() const;
    void setStatus(const std::string& new_status);
};
