#include "model/dialogue/DialogueManager.h"
#include <iostream>

void DialogueManager::registerDialogue(Dialogue&& dialogue) {
    dialogues[dialogue.getId()] = std::move(dialogue);
}

void DialogueManager::startDialogue(const std::string& dialogue_id) {
    auto it = dialogues.find(dialogue_id);
    if (it != dialogues.end()) {
        current_dialogue = &it->second;
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

void DialogueManager::endDialogue() {
    if (current_dialogue) {
        current_dialogue->end();
        current_dialogue = nullptr;
    }
}

bool DialogueManager::isInDialogue() const {
    bool result = current_dialogue && current_dialogue->isActive();
    return result;
}

Dialogue* DialogueManager::getCurrentDialogue() const {
    return current_dialogue;
}