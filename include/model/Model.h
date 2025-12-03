#pragma once
#include <string>
#include <memory>
#include "model/Player.h"
#include "model/Map.h"
#include "model/Location.h"
#include "model/dialogue/DialogueManager.h"
#include "helpers/Types.h"

class Model {
private:
    Player player;
    Map game_map;

    DialogueManager dialogue_manager;

    std::vector<const Interactable*> nearby_interactables;
    size_t detection_radius = 1;

    [[nodiscard]] size_t getScanStart(size_t n) const;
    [[nodiscard]] size_t getScanEnd(size_t n) const;

public:
    Model();

    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const Map& getMap() const;
    [[nodiscard]] const Location* getCurrentLocation() const;
    [[nodiscard]] const std::string& getCurrentLocationName() const;

    void movePlayer(Direction direction);
    void update();

    // Утилиты
    DialogueManager& getDialogueManager();
    const DialogueManager& getDialogueManager() const;
    bool isInDialogue() const;

    void scanAroundPlayer();
    const std::vector<const Interactable*>& getNearbyInteractables() const;
    void interactWithNearby(size_t index);
    size_t getDetectionRadius() const;
    void setDetectionRadius(size_t radius);
};