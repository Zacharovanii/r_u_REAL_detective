#pragma once
#include <string>
#include "model/Map.h"
#include "model/Player.h"
#include "model/dialogue/DialogueManager.h"

class GameInitializer {
public:
    static void initGameWorld(Map& map);
};
