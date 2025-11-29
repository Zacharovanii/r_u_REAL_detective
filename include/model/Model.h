#pragma once
#include <string>
#include <memory>
#include "model/Player.h"
#include "model/Map.h"
#include "model/Location.h"

class Model {
private:
    Player player;
    Map game_map;
    std::string current_location_name;

public:
    Model();

    // Основные методы
    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const Map& getMap() const;
    [[nodiscard]] const Location* getCurrentLocation() const;
    [[nodiscard]] const std::string& getCurrentLocationName() const;

    // Перемещение
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // Взаимодействие
    void interact();

    // Утилиты
    [[nodiscard]] size_t getMapSizeY() const;
    [[nodiscard]] size_t getMapSizeX() const;
    [[nodiscard]] size_t getMapSizeX(size_t y) const;

private:
    void initializeGameWorld();
    void loadInitialLocation();
};