#include "model/dialogue/DialogueManager.h"
#include <iostream>

void DialogueManager::registerDialogue(Dialogue&& dialogue) {
    dialogues[dialogue.getId()] = std::move(dialogue);
}

void DialogueManager::startDialogue(const std::string& dialogue_id) {
    if (dialogues.contains(dialogue_id)) {
        current_dialogue = &dialogues[dialogue_id];
        current_dialogue->start("start");
    }
}
bool DialogueManager::makeChoice(size_t choice_index, Player& player) {
    if (!isInDialogue()) return false;
    bool result = current_dialogue->makeChoice(choice_index, player);
    if (current_dialogue->isFinished()) {
        current_dialogue = nullptr;
    }
    return result;
}
bool DialogueManager::isInDialogue() const {
    bool result = current_dialogue && current_dialogue->isActive();
    return result;
}
Dialogue* DialogueManager::getCurrentDialogue() const {
    return current_dialogue;
}