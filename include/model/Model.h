#pragma once
#include <vector>
#include <string>

class Model {
public:
    struct Player {
        size_t x, y;
        int hp = 100;
        std::string status = "Тестовый";
    };


private:
    Player player;
    int rows = 15;
    int cols = 15;
    std::vector<std::string> map;

public:
    Model();

    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const std::vector<std::string>& getMap() const;

    [[nodiscard]] size_t getMapSizeY() const;
    [[nodiscard]] size_t getMapSizeX() const;
    [[nodiscard]] size_t getMapSizeX(size_t y) const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};
