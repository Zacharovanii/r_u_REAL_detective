#pragma once
#include "model/dialogue/DialogueManager.h"
#include "model/Player.h"

class DialogueInitializer {
public:
    static void initializeDialogues(DialogueManager& manager, Player& player);
};