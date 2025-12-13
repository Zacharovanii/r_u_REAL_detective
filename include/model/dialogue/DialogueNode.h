#pragma once
#include "model/Player.h"
#include <string>
#include <vector>
#include <functional>

struct DialogueChoice {
    std::string text;
    std::string next_node_id;
    std::string condition_id;
    std::string action_id;

    DialogueChoice(
        std::string t,
        std::string next,
        std::string c_id = "",
        std::string a_id = ""
    ):
        text(std::move(t)),
        next_node_id(std::move(next)),
        condition_id(std::move(c_id)),
        action_id(std::move(a_id))
    {}

    [[nodiscard]] bool checkCondition(const Player& player) const {
        if      (condition_id == "has_badge") return player.getBadges() >= 1;
        else if (condition_id == "has_money") return player.getMoney() >= 1;
        else if (condition_id == "has_flirt") return player.getFlirt() >= 1;
        else if (condition_id == "has_health") return player.getHealth() > 0;
        else return true;
    }

    void runAction(Player& player) const {
        if      (action_id == "remove_badge") player.changeBadges(-1);
        else if (action_id == "remove_money") player.changeMoney(-1);
        else if (action_id == "remove_flirt") player.changeFlirt(-1);
        else if (action_id == "take_damage") player.changeHealth(-1);
        else if (action_id == "heal") player.changeHealth(+1);
        else return;
    }
};

struct DialogueNode {
    std::string id;
    std::string speaker;
    std::string text;
    std::vector<DialogueChoice> choices;

    DialogueNode* setID(std::string value) {
        this->id = std::move(value);
        return this;
    }
    DialogueNode* setSpeaker(std::string value) {
        this->speaker = std::move(value);
        return this;
    }
    DialogueNode* setText(std::string value) {
        this->text = std::move(value);
        return this;
    }
    DialogueNode* addChoice(DialogueChoice value) {
        this->choices.push_back(std::move(value));
        return this;
    }
};