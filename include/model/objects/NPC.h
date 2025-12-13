#pragma once
#include <string>
#include "Interactable.h"

class NPC : public Interactable {
private:
    std::string attitude;
    std::string dialogue_id;
    bool alreadyTalked = false;

public:
    NPC(Position initial_pos,
        std::string name,
        std::string description,
        std::string attitude,
        std::string dialogue_id
        );

    dialogueID interact() override;

    [[nodiscard]] std::string getDialogueId() const;
    [[nodiscard]] std::string getAttitude() const;
    void setAttitude(const std::string& new_attitude);
};
