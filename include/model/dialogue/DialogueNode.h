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

class DialogueNode {
private:
    std::string _id;
    std::string _speaker;
    std::string _text;
    std::vector<DialogueChoice> _choices;

public:
    DialogueNode() = default;

    [[nodiscard]] const std::string& id() const { return _id; }
    [[nodiscard]] const std::string& speaker() const { return _speaker; }
    [[nodiscard]] const std::string& text() const { return _text; }
    [[nodiscard]] const std::vector<DialogueChoice>& choices() const { return _choices; }

    DialogueNode* id(std::string value) {
        this->_id = std::move(value);
        return this;
    }
    DialogueNode* speaker(std::string value) {
        this->_speaker = std::move(value);
        return this;
    }
    DialogueNode* text(std::string value) {
        this->_text = std::move(value);
        return this;
    }
    DialogueNode* choice(DialogueChoice value) {
        this->_choices.push_back(std::move(value));
        return this;
    }
    DialogueNode* choices(DialogueChoice values[], int values_count) {
        for (auto i = 0; i < values_count; i++) {
            this->_choices.push_back(std::move(values[i]));
        }
        return this;
    }
};