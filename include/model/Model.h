#pragma once
#include <string>
#include <memory>
#include "model/Player.h"
#include "model/Map.h"
#include "model/Location.h"
#include "model/dialogue/DialogueManager.h"

class Model {
private:
    Player player;
    Map game_map;

    DialogueManager dialogue_manager;

    std::vector<const Interactable*> nearby_interactables;
    size_t detection_radius = 2;

public:
    Model();

    void debugEndDialogue() {
        dialogue_manager.endDialogue();
    }

    void debugStartDialogue() {
        dialogue_manager.startDialogue("robert_dialogue");
    }

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
    void update();

    // Утилиты
    [[nodiscard]] size_t getMapSizeY() const;
    [[nodiscard]] size_t getMapSizeX() const;
    [[nodiscard]] size_t getMapSizeX(size_t y) const;

    DialogueManager& getDialogueManager();
    const DialogueManager& getDialogueManager() const;
    bool isInDialogue() const;

    void scanAroundPlayer();
    const std::vector<const Interactable*>& getNearbyInteractables() const;
    void interactWithNearby(size_t index);
    size_t getDetectionRadius() const;
    void setDetectionRadius(size_t radius);
};