#pragma once
#include "Interactable.h"
#include <string>
#include <functional>

class NPC : public Interactable {
private:
    std::string attitude;
    std::string dialogue_id;
    std::function<void(const std::string&)> start_dialogue_callback;

public:
    NPC(const Position& initial_pos,
        const std::string& name,
        const std::string& description,
        const std::string& attitude,
        const std::string& dialogue_id,
        const std::function<void(const std::string&)>& start_dialogue_callback);

    void interact(Player& player) override;

    std::string getDialogueId() const;
    std::string getAttitude() const;
    void setAttitude(const std::string& new_attitude);
};