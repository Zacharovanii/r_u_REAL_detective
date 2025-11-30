#pragma once
#include <string>
#include "model/Map.h"
#include "model/Player.h"
#include "model/DialogueManager.h"

class GameInitializer {
public:
    static void initGameWorld(Map& map, DialogueManager& dialogue_manager);
    static std::string loadStartLocation(Map& map, Player& player, const std::string& initial_location_name);
};
