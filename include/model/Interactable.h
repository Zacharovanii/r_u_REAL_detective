#pragma once
#include <string>
#include "helpers/Types.h"
#include "Player.h"

class Interactable {
protected:
    Position position;
    std::string name;
    std::string description;

public:
    Interactable(const Position& initial_pos, const std::string& name, const std::string& description);
    virtual ~Interactable();

    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;

    virtual void interact(Player& player) = 0;

    [[nodiscard]] bool isIntersect(const Position& pos) const;
    [[nodiscard]] bool isIntersect(size_t x, size_t y) const;

    [[nodiscard]] size_t getX() const;
    [[nodiscard]] size_t getY() const;
    void setX(size_t new_value);
    void setY(size_t new_value);

    [[nodiscard]] Position getPosition() const;
    void setPosition(const Position& new_pos);
};
