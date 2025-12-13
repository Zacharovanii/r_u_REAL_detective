#pragma once
#include <string>
#include "helpers/Types.h"

class Player {
    Position position;

    int badges = 3;   // жетоны
    int money  = 2;   // деньги
    int health = 3;   // здоровье
    int flirt  = 2;   // флирт

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

    [[nodiscard]] int getBadges() const;
    [[nodiscard]] int getMoney()  const;
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] int getFlirt()  const;

    void changeBadges(int value);
    void changeMoney(int value);
    void changeHealth(int value);
    void changeFlirt(int value);
};
