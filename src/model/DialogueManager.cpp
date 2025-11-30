#include "model/DialogueManager.h"
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

bool DialogueManager::makeChoice(size_t choice_index) {
    if (!isInDialogue()) return false;
    
    bool result = current_dialogue->makeChoice(choice_index);
    if (current_dialogue->isFinished()) {
        current_dialogue = nullptr;
    }
    return result;
}

void DialogueManager::endDialogue() {
    // std::cout << "Debug: DialogueManager::endDialogue() called" << std::endl;
    if (current_dialogue) {
        // std::cout << "Debug: Current dialogue: " << current_dialogue->getId() << std::endl;
        current_dialogue->end();
        current_dialogue = nullptr;
        // std::cout << "Debug: Dialogue ended and cleared" << std::endl;
    } else {
        // std::cout << "Debug: No current dialogue to end" << std::endl;
    }
}

bool DialogueManager::isInDialogue() const {
    bool result = current_dialogue && current_dialogue->isActive();
    // std::cout << "Debug: isInDialogue() = " << result << " (current_dialogue: " << (current_dialogue ? current_dialogue->getId() : "null") << ")" << std::endl;
    return result;
}