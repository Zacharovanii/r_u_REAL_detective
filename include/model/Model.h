#pragma once
#include <vector>
#include <string>

class Model {
public:
    struct Player {
        int x;
        int y;
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

    const Player& getPlayer() const;
    const std::vector<std::string>& getMap() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
};
