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
    DialogueManager dialogue_manager;
    Player player;
    Map game_map;
    std::vector<Interactable*> nearby_interactables;
    size_t detection_radius = 1;

    [[nodiscard]] size_t getScanStart(size_t n) const;
    [[nodiscard]] size_t getScanEnd(size_t n) const;

public:
    Model();

    [[nodiscard]] const Player& getPlayer() const;
    [[nodiscard]] const std::string& getCurrentLocationName() const;
    Location* getCurrentLocation();

    void movePlayer(Direction direction);
    void update();

    DialogueManager& getDialogueManager();
    bool isInDialogue() const;

    void scanAroundPlayer();
    std::vector<Interactable*> getNearbyInteractables() const;
    void interactWithNearby(size_t index) const;
};