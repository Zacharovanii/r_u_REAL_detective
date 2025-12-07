#pragma once
#include <string>
#include <functional>
#include "Interactable.h"

class NPC : public Interactable {
private:
    std::string attitude;
    std::string dialogue_id;
    std::function<void(const std::string&)> start_dialogue_callback;

public:
    NPC(Position initial_pos,
        std::string name,
        std::string description,
        std::string attitude,
        std::string dialogue_id,
        const std::function<void(const std::string&)>& start_dialogue_callback);

    void interact() override;

    [[nodiscard]] std::string getDialogueId() const;
    [[nodiscard]] std::string getAttitude() const;
    void setAttitude(const std::string& new_attitude);
};
