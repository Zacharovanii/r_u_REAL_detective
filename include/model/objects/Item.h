#pragma once
#include <string>
#include "Interactable.h"

class Item : public Interactable {
private:
    std::string dialogue_id;

public:
    Item(Position initial_pos,
        std::string name,
        std::string description,
        std::string dialogue_id
        );

    dialogueID interact() override;

    [[nodiscard]] std::string getDialogueId() const;
    [[nodiscard]] std::string getAttitude() const;
    void setAttitude(const std::string& new_attitude);
};
