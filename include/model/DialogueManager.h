#pragma once
#include "Dialogue.h"
#include <unordered_map>

class DialogueManager {
private:
    std::unordered_map<std::string, Dialogue> dialogues;
    Dialogue* current_dialogue = nullptr;

public:
    void registerDialogue(Dialogue&& dialogue);
    void startDialogue(const std::string& dialogue_id);
    bool makeChoice(size_t choice_index);
    void endDialogue();

    bool isInDialogue() const;
    const Dialogue* getCurrentDialogue() const { return current_dialogue; }
};