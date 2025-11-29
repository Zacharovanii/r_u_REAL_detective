#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class Model {
public:
    struct Player {
        size_t x, y;
        int hp = 100;
        std::string status = "Тестовый";
    };

    struct Door {
        size_t door_x, door_y;
        std::string to_map;
        size_t to_x, to_y;
        std::string description;
    };

private:
    Player player;
    std::vector<std::string> map;
    std::string current_map = "hotel_1f";

    std::unordered_map<std::string, Door> doors;

public:
    Model();

    // Основные методы
    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const std::vector<std::string>& getMap() const;
    [[nodiscard]] const std::string& getCurrentMap() const;

    // Перемещение
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // Работа с картами
    void loadMap();
    void loadMap(const std::string& map_name);
    bool tryTransition();

    // Утилиты
    [[nodiscard]] size_t getMapSizeY() const;
    [[nodiscard]] size_t getMapSizeX() const;
    [[nodiscard]] size_t getMapSizeX(size_t y) const;

private:
    void initializeDoors();
};